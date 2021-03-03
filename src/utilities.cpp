/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "utilities.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <limits>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/issue.h"
#include "libcellml/logger.h"
#include "libcellml/model.h"
#include "libcellml/namedentity.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "xmldoc.h"
#include "xmlutils.h"

namespace libcellml {

bool convertToDouble(const std::string &in, double &out)
{
    try {
        out = std::stod(in);
    } catch (...) {
        return false;
    }
    return true;
}

bool hasNonWhitespaceCharacters(const std::string &input)
{
    return input.find_first_not_of(" \t\n\v\f\r") != std::string::npos;
}

std::string convertToString(double value)
{
    std::ostringstream strs;
    strs << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return strs.str();
}

bool convertToInt(const std::string &in, int &out)
{
    try {
        out = std::stoi(in);
    } catch (...) {
        return false;
    }
    return true;
}

std::string convertToString(size_t value)
{
    std::ostringstream strs;
    strs << value;
    return strs.str();
}

std::string convertToString(int value)
{
    std::ostringstream strs;
    strs << value;
    return strs.str();
}

bool isEuropeanNumericCharacter(char c)
{
    const std::set<char> validIntegerCharacters = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    return validIntegerCharacters.find(c) != validIntegerCharacters.end();
}

bool isNonNegativeCellMLInteger(const std::string &candidate)
{
    if (candidate.empty()) {
        return false;
    }
    return std::all_of(candidate.begin(), candidate.end(), isEuropeanNumericCharacter);
}

bool isCellMLInteger(const std::string &candidate)
{
    if (!candidate.empty() && *candidate.begin() == '-') {
        return isNonNegativeCellMLInteger(candidate.substr(1));
    }
    return isNonNegativeCellMLInteger(candidate);
}

bool isCellMLExponent(const std::string &candidate)
{
    if (!candidate.empty() && *candidate.begin() == '+') {
        return isCellMLInteger(candidate.substr(1));
    }
    return isCellMLInteger(candidate);
}

std::vector<size_t> findOccurrences(const std::string &candidate, const std::string &sub)
{
    std::vector<size_t> occurrences;
    size_t pos = candidate.find(sub, 0);
    while (pos != std::string::npos) {
        occurrences.push_back(pos);
        pos = candidate.find(sub, pos + 1);
    }
    return occurrences;
}

bool isCellMLBasicReal(const std::string &candidate)
{
    if (!candidate.empty()) {
        std::vector<size_t> decimalOccurrences = findOccurrences(candidate, ".");
        if (decimalOccurrences.size() < 2) {
            bool beginsMinus = *candidate.begin() == '-';
            std::string numbersOnlyCandidate = candidate;
            if (decimalOccurrences.size() == 1) {
                numbersOnlyCandidate.erase(decimalOccurrences.at(0), 1);
            }
            if (beginsMinus) {
                numbersOnlyCandidate.erase(0, 1);
            }
            return std::all_of(numbersOnlyCandidate.begin(), numbersOnlyCandidate.end(), isEuropeanNumericCharacter);
        }
    }
    return false;
}

bool isCellMLReal(const std::string &candidate)
{
    bool isReal = false;
    if (!candidate.empty()) {
        std::string normalisedCandidate = candidate;
        std::vector<size_t> eOccurrences = findOccurrences(candidate, "E");
        for (const auto &ePos : eOccurrences) {
            normalisedCandidate.replace(ePos, 1, "e");
        }
        std::vector<size_t> lowerEOccurrences = findOccurrences(normalisedCandidate, "e");
        size_t eIndicatorCount = lowerEOccurrences.size();
        if (eIndicatorCount < 2) {
            if (eIndicatorCount == 1) {
                size_t ePos = lowerEOccurrences.at(0);
                std::string significand = normalisedCandidate.substr(0, ePos);
                std::string exponent = normalisedCandidate.substr(ePos + 1, std::string::npos);
                if (isCellMLBasicReal(significand) && isCellMLExponent(exponent)) {
                    isReal = true;
                }
            } else {
                isReal = isCellMLBasicReal(normalisedCandidate);
            }
        }
    }
    return isReal;
}

bool areEqual(double value1, double value2)
{
    return std::abs(value1 - value2) < std::numeric_limits<double>::epsilon();
}

// The below code is used to compute the SHA-1 value of a string, based on the
// code available at https://github.com/vog/sha1.

static const size_t BLOCK_INTS = 16;
static const size_t BLOCK_BYTES = BLOCK_INTS * 4;

static void bufferToBlock(const std::string &buffer,
                          std::array<uint32_t, BLOCK_INTS> &block)
{
    for (size_t i = 0; i < BLOCK_INTS; ++i) {
        block.at(i) = (uint32_t(buffer[4 * i + 3]) & 0xffU)
                      | (uint32_t(buffer[4 * i + 2]) & 0xffU) << 8U
                      | (uint32_t(buffer[4 * i + 1]) & 0xffU) << 16U
                      | (uint32_t(buffer[4 * i + 0]) & 0xffU) << 24U;
    }
}

static uint32_t rol(const uint32_t value, const size_t bits)
{
    return (value << bits) | (value >> (32 - bits));
}

static uint32_t blk(const std::array<uint32_t, BLOCK_INTS> block,
                    const size_t i)
{
    return rol(block.at((i + 13) & 15U) ^ block.at((i + 8) & 15U) ^ block.at((i + 2) & 15U) ^ block.at(i), 1);
}

static void r0(const std::array<uint32_t, BLOCK_INTS> block, const uint32_t v,
               uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z,
               const size_t i)
{
    z += ((w & (x ^ y)) ^ y) + block.at(i) + 0x5a827999U + rol(v, 5);
    w = rol(w, 30);
}

static void r1(std::array<uint32_t, BLOCK_INTS> &block, const uint32_t v,
               uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z,
               const size_t i)
{
    block.at(i) = blk(block, i);

    z += ((w & (x ^ y)) ^ y) + block.at(i) + 0x5a827999U + rol(v, 5);
    w = rol(w, 30);
}

static void r2(std::array<uint32_t, BLOCK_INTS> &block, const uint32_t v,
               uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z,
               const size_t i)
{
    block.at(i) = blk(block, i);

    z += (w ^ x ^ y) + block.at(i) + 0x6ed9eba1U + rol(v, 5);
    w = rol(w, 30);
}

static void r3(std::array<uint32_t, BLOCK_INTS> &block, const uint32_t v,
               uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z,
               const size_t i)
{
    block.at(i) = blk(block, i);

    z += (((w | x) & y) | (w & x)) + block.at(i) + 0x8f1bbcdcU + rol(v, 5);
    w = rol(w, 30);
}

static void r4(std::array<uint32_t, BLOCK_INTS> &block, const uint32_t v,
               uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z,
               const size_t i)
{
    block.at(i) = blk(block, i);

    z += (w ^ x ^ y) + block.at(i) + 0xca62c1d6U + rol(v, 5);
    w = rol(w, 30);
}

static void transform(std::array<uint32_t, 5> &digest,
                      std::array<uint32_t, BLOCK_INTS> &block,
                      uint64_t &transforms)
{
    uint32_t a = digest[0];
    uint32_t b = digest[1];
    uint32_t c = digest[2];
    uint32_t d = digest[3];
    uint32_t e = digest[4];

    r0(block, a, b, c, d, e, 0);
    r0(block, e, a, b, c, d, 1);
    r0(block, d, e, a, b, c, 2);
    r0(block, c, d, e, a, b, 3);
    r0(block, b, c, d, e, a, 4);
    r0(block, a, b, c, d, e, 5);
    r0(block, e, a, b, c, d, 6);
    r0(block, d, e, a, b, c, 7);
    r0(block, c, d, e, a, b, 8);
    r0(block, b, c, d, e, a, 9);
    r0(block, a, b, c, d, e, 10);
    r0(block, e, a, b, c, d, 11);
    r0(block, d, e, a, b, c, 12);
    r0(block, c, d, e, a, b, 13);
    r0(block, b, c, d, e, a, 14);
    r0(block, a, b, c, d, e, 15);
    r1(block, e, a, b, c, d, 0);
    r1(block, d, e, a, b, c, 1);
    r1(block, c, d, e, a, b, 2);
    r1(block, b, c, d, e, a, 3);
    r2(block, a, b, c, d, e, 4);
    r2(block, e, a, b, c, d, 5);
    r2(block, d, e, a, b, c, 6);
    r2(block, c, d, e, a, b, 7);
    r2(block, b, c, d, e, a, 8);
    r2(block, a, b, c, d, e, 9);
    r2(block, e, a, b, c, d, 10);
    r2(block, d, e, a, b, c, 11);
    r2(block, c, d, e, a, b, 12);
    r2(block, b, c, d, e, a, 13);
    r2(block, a, b, c, d, e, 14);
    r2(block, e, a, b, c, d, 15);
    r2(block, d, e, a, b, c, 0);
    r2(block, c, d, e, a, b, 1);
    r2(block, b, c, d, e, a, 2);
    r2(block, a, b, c, d, e, 3);
    r2(block, e, a, b, c, d, 4);
    r2(block, d, e, a, b, c, 5);
    r2(block, c, d, e, a, b, 6);
    r2(block, b, c, d, e, a, 7);
    r3(block, a, b, c, d, e, 8);
    r3(block, e, a, b, c, d, 9);
    r3(block, d, e, a, b, c, 10);
    r3(block, c, d, e, a, b, 11);
    r3(block, b, c, d, e, a, 12);
    r3(block, a, b, c, d, e, 13);
    r3(block, e, a, b, c, d, 14);
    r3(block, d, e, a, b, c, 15);
    r3(block, c, d, e, a, b, 0);
    r3(block, b, c, d, e, a, 1);
    r3(block, a, b, c, d, e, 2);
    r3(block, e, a, b, c, d, 3);
    r3(block, d, e, a, b, c, 4);
    r3(block, c, d, e, a, b, 5);
    r3(block, b, c, d, e, a, 6);
    r3(block, a, b, c, d, e, 7);
    r3(block, e, a, b, c, d, 8);
    r3(block, d, e, a, b, c, 9);
    r3(block, c, d, e, a, b, 10);
    r3(block, b, c, d, e, a, 11);
    r4(block, a, b, c, d, e, 12);
    r4(block, e, a, b, c, d, 13);
    r4(block, d, e, a, b, c, 14);
    r4(block, c, d, e, a, b, 15);
    r4(block, b, c, d, e, a, 0);
    r4(block, a, b, c, d, e, 1);
    r4(block, e, a, b, c, d, 2);
    r4(block, d, e, a, b, c, 3);
    r4(block, c, d, e, a, b, 4);
    r4(block, b, c, d, e, a, 5);
    r4(block, a, b, c, d, e, 6);
    r4(block, e, a, b, c, d, 7);
    r4(block, d, e, a, b, c, 8);
    r4(block, c, d, e, a, b, 9);
    r4(block, b, c, d, e, a, 10);
    r4(block, a, b, c, d, e, 11);
    r4(block, e, a, b, c, d, 12);
    r4(block, d, e, a, b, c, 13);
    r4(block, c, d, e, a, b, 14);
    r4(block, b, c, d, e, a, 15);

    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;

    ++transforms;
}

std::string sha1(const std::string &string)
{
    std::array<uint32_t, 5> digest = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};
    std::string buffer;
    uint64_t transforms = 0;
    std::istringstream is(string);

    while (true) {
        std::array<char, BLOCK_BYTES> sbuf = {};

        is.read(sbuf.data(), int64_t(BLOCK_BYTES - buffer.size()));

        buffer.append(sbuf.data(), size_t(is.gcount()));

        if (buffer.size() != BLOCK_BYTES) {
            break;
        }

        std::array<uint32_t, BLOCK_INTS> block = {};

        bufferToBlock(buffer, block);
        transform(digest, block, transforms);

        buffer.clear();
    }

    uint64_t totalBits = (transforms * BLOCK_BYTES + buffer.size()) * 8;

    buffer += "\x80";

    size_t origSize = buffer.size();

    while (buffer.size() < BLOCK_BYTES) {
        buffer += char(0x00);
    }

    std::array<uint32_t, BLOCK_INTS> block = {};

    bufferToBlock(buffer, block);

    if (origSize > BLOCK_BYTES - 8) {
        transform(digest, block, transforms);

        for (size_t i = 0; i < BLOCK_INTS - 2; ++i) {
            block.at(i) = 0;
        }
    }

    block[BLOCK_INTS - 1] = uint32_t(totalBits);
    block[BLOCK_INTS - 2] = uint32_t(totalBits >> 32U);

    transform(digest, block, transforms);

    std::ostringstream result;

    for (uint32_t d : digest) {
        result << std::hex << std::setfill('0') << std::setw(8);
        result << d;
    }

    return result.str();
}

bool isStandardUnitName(const std::string &name)
{
    return standardUnitsList.count(name) != 0;
}

bool isStandardUnit(const UnitsPtr &units)
{
    return (units != nullptr) && units->unitCount() == 0 && isStandardUnitName(units->name());
}

bool isStandardPrefixName(const std::string &name)
{
    return standardPrefixList.count(name) != 0;
}

void removeComponentFromEntity(const EntityPtr &entity, const ComponentPtr &component)
{
    auto componentEntity = std::dynamic_pointer_cast<ComponentEntity>(entity);
    componentEntity->removeComponent(component, false);
}

size_t getVariableIndexInComponent(const ComponentPtr &component, const VariablePtr &variable)
{
    size_t index = 0;
    bool found = false;
    while (index < component->variableCount() && !found) {
        if (component->variable(index) == variable) {
            found = true;
        } else {
            ++index;
        }
    }

    return index;
}

bool areEquivalentVariables(const VariablePtr &variable1,
                            const VariablePtr &variable2)
{
    return (variable1 == variable2) || variable1->hasEquivalentVariable(variable2, true);
}

bool isEntityChildOf(const EntityPtr &entity1, const EntityPtr &entity2)
{
    return entity1->parent() == entity2;
}

bool areEntitiesSiblings(const EntityPtr &entity1, const EntityPtr &entity2)
{
    auto entity1Parent = entity1->parent();
    return entity1Parent != nullptr && entity1Parent == entity2->parent();
}

using PublicPrivateRequiredPair = std::pair<bool, bool>;

/**
 * @brief Determine whether a public and/or private interface is required for the given @p variable.
 *
 * Determine whether a public and/or private interface is required for the given @p variable.  Returns
 * a pair of booleans where the first item in the pair indicates whether a public interface is required,
 * the second item in the pair indicates whether a private interface is required, and if both items
 * in the pair are @c false then this indicates an error has occurred and the interface type cannot be
 * determined.
 *
 * @param variable The variable to detect the interface type required.
 *
 * @return A pair of booleans.
 */
PublicPrivateRequiredPair publicAndOrPrivateInterfaceTypeRequired(const VariablePtr &variable)
{
    PublicPrivateRequiredPair pair = std::make_pair(false, false);
    for (size_t index = 0; index < variable->equivalentVariableCount() && !(pair.first && pair.second); ++index) {
        auto equivalentVariable = variable->equivalentVariable(index);
        auto componentOfVariable = variable->parent();
        auto componentOfEquivalentVariable = equivalentVariable->parent();
        if (componentOfVariable == nullptr || componentOfEquivalentVariable == nullptr) {
            return std::make_pair(false, false);
        }
        if (areEntitiesSiblings(componentOfVariable, componentOfEquivalentVariable)
            || isEntityChildOf(componentOfVariable, componentOfEquivalentVariable)) {
            pair.first = true;
        } else if (isEntityChildOf(componentOfEquivalentVariable, componentOfVariable)) {
            pair.second = true;
        } else {
            return std::make_pair(false, false);
        }
    }
    return pair;
}

/**
 * @brief Get the interface type for the given public private pair.
 *
 * Get the interface type for the @p pair.  The default return type is
 * Variable::InterfaceType::NONE.
 *
 * @param pair The pair for which the interface type is determined.
 *
 * @return The interface type as specified in the @p pair.
 */
Variable::InterfaceType interfaceTypeFor(const PublicPrivateRequiredPair &pair)
{
    Variable::InterfaceType interfaceType = Variable::InterfaceType::NONE;
    if (pair.first && pair.second) {
        interfaceType = Variable::InterfaceType::PUBLIC_AND_PRIVATE;
    } else if (pair.first) {
        interfaceType = Variable::InterfaceType::PUBLIC;
    } else if (pair.second) {
        interfaceType = Variable::InterfaceType::PRIVATE;
    }

    return interfaceType;
}

Variable::InterfaceType determineInterfaceType(const VariablePtr &variable)
{
    auto publicAndOrPrivatePair = publicAndOrPrivateInterfaceTypeRequired(variable);

    return interfaceTypeFor(publicAndOrPrivatePair);
}

void findAllVariablesWithEquivalences(const ComponentPtr &component, VariablePtrs &variables)
{
    for (size_t index = 0; index < component->variableCount(); ++index) {
        auto variable = component->variable(index);
        if (variable->equivalentVariableCount() > 0) {
            if (std::find(variables.begin(), variables.end(), variable) == variables.end()) {
                variables.push_back(variable);
            }
        }
    }
    for (size_t index = 0; index < component->componentCount(); ++index) {
        findAllVariablesWithEquivalences(component->component(index), variables);
    }
}

NameList findCnUnitsNames(const XmlNodePtr &node);
NameList findComponentCnUnitsNames(const ComponentPtr &component);
void findAndReplaceCnUnitsNames(const XmlNodePtr &node, const StringStringMap &replaceMap);
void findAndReplaceComponentCnUnitsNames(const ComponentPtr &component, const StringStringMap &replaceMap);
size_t getComponentIndexInComponentEntity(const ComponentEntityPtr &componentParent, const ComponentEntityPtr &component);
IndexStack reverseEngineerIndexStack(const VariablePtr &variable);
VariablePtr getVariableLocatedAt(const IndexStack &stack, const ModelPtr &model);
void makeEquivalence(const IndexStack &stack1, const IndexStack &stack2, const ModelPtr &model);
IndexStack rebaseIndexStack(const IndexStack &stack, const IndexStack &originStack, const IndexStack &destinationStack);
void componentNames(const ComponentPtr &component, NameList &names);
std::vector<UnitsPtr> referencedUnits(const ModelPtr &model, const UnitsPtr &units);

NameList findCnUnitsNames(const XmlNodePtr &node)
{
    NameList names;
    XmlNodePtr childNode = node->firstChild();
    while (childNode != nullptr) {
        if (childNode->isMathmlElement("cn")) {
            std::string u = childNode->attribute("units");
            if (!u.empty() && !isStandardUnitName(u)) {
                names.push_back(u);
            }
        }
        auto childNames = findCnUnitsNames(childNode);
        names.insert(names.end(), childNames.begin(), childNames.end());
        childNode = childNode->next();
    }

    return names;
}

NameList findComponentCnUnitsNames(const ComponentPtr &component)
{
    NameList names;
    // Inspect the MathML in this component for any specified constant <cn> units.
    std::string mathContent = component->math();
    if (mathContent.empty()) {
        return names;
    }
    std::vector<XmlDocPtr> mathDocs = multiRootXml(mathContent);
    for (const auto &doc : mathDocs) {
        auto rootNode = doc->rootNode();
        if (rootNode->isMathmlElement("math")) {
            auto nodesNames = findCnUnitsNames(rootNode);
            names.insert(names.end(), nodesNames.begin(), nodesNames.end());
        }
    }

    return names;
}

void findAndReplaceCnUnitsNames(const XmlNodePtr &node, const StringStringMap &replaceMap)
{
    XmlNodePtr childNode = node->firstChild();
    while (childNode != nullptr) {
        if (childNode->isMathmlElement("cn")) {
            std::string unitsName = childNode->attribute("units");
            auto foundNameIter = replaceMap.find(unitsName);
            if (foundNameIter != replaceMap.end()) {
                childNode->setAttribute("units", foundNameIter->second.c_str());
            }
        }
        findAndReplaceCnUnitsNames(childNode, replaceMap);
        childNode = childNode->next();
    }
}

void findAndReplaceComponentCnUnitsNames(const ComponentPtr &component, const StringStringMap &replaceMap)
{
    std::string mathContent = component->math();
    if (mathContent.empty()) {
        return;
    }
    bool contentModified = false;
    std::string newMathContent;
    std::vector<XmlDocPtr> mathDocs = multiRootXml(mathContent);
    for (const auto &doc : mathDocs) {
        auto rootNode = doc->rootNode();
        if (rootNode->isMathmlElement("math")) {
            auto originalMath = rootNode->convertToString();
            findAndReplaceCnUnitsNames(rootNode, replaceMap);
            auto newMath = rootNode->convertToString();
            newMathContent += newMath;
            if (newMath != originalMath) {
                contentModified = true;
            }
        }
    }

    if (contentModified) {
        component->setMath(newMathContent);
    }
}

void findAndReplaceComponentsCnUnitsNames(const ComponentPtr &component, const StringStringMap &replaceMap)
{
    findAndReplaceComponentCnUnitsNames(component, replaceMap);
    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto childComponent = component->component(index);
        findAndReplaceComponentCnUnitsNames(childComponent, replaceMap);
    }
}

size_t getComponentIndexInComponentEntity(const ComponentEntityPtr &componentParent, const ComponentEntityPtr &component)
{
    size_t index = 0;
    bool found = false;
    while ((index < componentParent->componentCount()) && !found) {
        if (componentParent->component(index) == component) {
            found = true;
        } else {
            ++index;
        }
    }

    return index;
}

IndexStack reverseEngineerIndexStack(const ComponentPtr &component)
{
    auto dummyVariable = Variable::create();
    component->addVariable(dummyVariable);
    IndexStack indexStack = reverseEngineerIndexStack(dummyVariable);
    indexStack.pop_back();
    component->removeVariable(dummyVariable);

    return indexStack;
}

IndexStack rebaseIndexStack(const IndexStack &stack, const IndexStack &originStack, const IndexStack &destinationStack)
{
    auto rebasedStack = stack;

    rebasedStack.resize(originStack.size(), SIZE_MAX);
    if (rebasedStack == originStack) {
        rebasedStack = destinationStack;
        auto offsetIt = stack.begin() + ptrdiff_t(originStack.size());
        rebasedStack.insert(rebasedStack.end(), offsetIt, stack.end());
    } else {
        rebasedStack.clear();
    }

    return rebasedStack;
}

EquivalenceMap rebaseEquivalenceMap(const EquivalenceMap &map, const IndexStack &originStack, const IndexStack &destinationStack)
{
    EquivalenceMap rebasedMap;
    for (const auto &entry : map) {
        auto key = entry.first;
        auto rebasedKey = rebaseIndexStack(key, originStack, destinationStack);
        if (!rebasedKey.empty()) {
            auto vector = entry.second;
            std::vector<IndexStack> rebasedVector;
            for (auto stack : vector) {
                // Temporarily remove the variable index whilst we rebase the component part of the stack.
                size_t variableIndex = stack.back();
                stack.pop_back();
                auto rebasedTarget = rebaseIndexStack(stack, originStack, destinationStack);
                if (!rebasedTarget.empty()) {
                    rebasedTarget.push_back(variableIndex);
                    rebasedVector.push_back(rebasedTarget);
                }
            }

            if (!rebasedVector.empty()) {
                rebasedMap[rebasedKey] = rebasedVector;
            }
        }
    }

    return rebasedMap;
}

void componentNames(const ComponentPtr &component, NameList &names)
{
    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto c = component->component(index);
        names.push_back(c->name());
        componentNames(c, names);
    }
}

NameList componentNames(const ModelPtr &model)
{
    NameList names;
    for (size_t index = 0; index < model->componentCount(); ++index) {
        auto component = model->component(index);
        names.push_back(component->name());
        componentNames(component, names);
    }
    return names;
}

ComponentNameMap createComponentNamesMap(const ComponentPtr &component)
{
    ComponentNameMap nameMap;
    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto c = component->component(index);
        nameMap[c->name()] = c;
        ComponentNameMap childrenNameMap = createComponentNamesMap(c);
        nameMap.insert(childrenNameMap.begin(), childrenNameMap.end());
    }

    return nameMap;
}

std::vector<UnitsPtr> referencedUnits(const ModelPtr &model, const UnitsPtr &units)
{
    std::vector<UnitsPtr> requiredUnits;

    std::string ref;
    std::string pre;
    std::string id;
    double expMult;
    double uExp;

    for (size_t index = 0; index < units->unitCount(); ++index) {
        units->unitAttributes(index, ref, pre, uExp, expMult, id);
        if (!isStandardUnitName(ref)) {
            auto refUnits = model->units(ref);
            if (refUnits != nullptr) {
                auto requiredUnitsUnits = referencedUnits(model, refUnits);
                requiredUnits.insert(requiredUnits.end(), requiredUnitsUnits.begin(), requiredUnitsUnits.end());
                requiredUnits.push_back(refUnits);
            }
        }
    }

    return requiredUnits;
}

std::vector<UnitsPtr> unitsUsed(const ModelPtr &model, const ComponentPtr &component)
{
    std::vector<UnitsPtr> usedUnits;
    for (size_t i = 0; i < component->variableCount(); ++i) {
        auto v = component->variable(i);
        auto u = v->units();
        if ((u != nullptr) && !isStandardUnitName(u->name())) {
            auto requiredUnits = referencedUnits(model, u);
            usedUnits.insert(usedUnits.end(), requiredUnits.begin(), requiredUnits.end());
            usedUnits.push_back(u);
        }
    }
    auto componentCnUnitsNames = findComponentCnUnitsNames(component);
    for (const auto &unitsName : componentCnUnitsNames) {
        auto u = model->units(unitsName);
        if ((u != nullptr) && !isStandardUnitName(u->name())) {
            auto requiredUnits = referencedUnits(model, u);
            usedUnits.insert(usedUnits.end(), requiredUnits.begin(), requiredUnits.end());
            usedUnits.push_back(u);
        }
    }

    for (size_t i = 0; i < component->componentCount(); ++i) {
        auto childComponent = component->component(i);
        auto childUsedUnits = unitsUsed(model, childComponent);
        usedUnits.insert(usedUnits.end(), childUsedUnits.begin(), childUsedUnits.end());
    }

    return usedUnits;
}

NameList unitsNamesUsed(const ComponentPtr &component)
{
    auto unitNames = findComponentCnUnitsNames(component);
    for (size_t i = 0; i < component->variableCount(); ++i) {
        auto u = component->variable(i)->units();
        if ((u != nullptr) && !isStandardUnitName(u->name())) {
            unitNames.push_back(u->name());
        }
    }
    return unitNames;
}

IndexStack reverseEngineerIndexStack(const VariablePtr &variable)
{
    IndexStack indexStack;
    ComponentPtr component = std::dynamic_pointer_cast<Component>(variable->parent());
    indexStack.push_back(getVariableIndexInComponent(component, variable));

    ComponentEntityPtr parent = component;
    ComponentEntityPtr grandParent = std::dynamic_pointer_cast<ComponentEntity>(parent->parent());
    while (grandParent != nullptr) {
        indexStack.push_back(getComponentIndexInComponentEntity(grandParent, parent));
        parent = grandParent;
        grandParent = std::dynamic_pointer_cast<ComponentEntity>(parent->parent());
    }

    std::reverse(std::begin(indexStack), std::end(indexStack));

    return indexStack;
}

void recordVariableEquivalences(const ComponentPtr &component, EquivalenceMap &equivalenceMap, IndexStack &indexStack)
{
    for (size_t index = 0; index < component->variableCount(); ++index) {
        auto variable = component->variable(index);
        for (size_t j = 0; j < variable->equivalentVariableCount(); ++j) {
            if (j == 0) {
                indexStack.push_back(index);
            }
            auto equivalentVariable = variable->equivalentVariable(j);
            auto equivalentVariableIndexStack = reverseEngineerIndexStack(equivalentVariable);
            if (equivalenceMap.count(indexStack) == 0) {
                equivalenceMap[indexStack] = std::vector<IndexStack>();
            }
            equivalenceMap[indexStack].push_back(equivalentVariableIndexStack);
        }
        if (variable->equivalentVariableCount() > 0) {
            indexStack.pop_back();
        }
    }
}

void generateEquivalenceMap(const ComponentPtr &component, EquivalenceMap &map, IndexStack &indexStack)
{
    for (size_t index = 0; index < component->componentCount(); ++index) {
        indexStack.push_back(index);
        auto c = component->component(index);
        recordVariableEquivalences(c, map, indexStack);
        generateEquivalenceMap(c, map, indexStack);
        indexStack.pop_back();
    }
}

VariablePtr getVariableLocatedAt(const IndexStack &stack, const ModelPtr &model)
{
    ComponentPtr component;
    for (size_t index = 0; index < stack.size() - 1; ++index) {
        if (index == 0) {
            component = model->component(stack.at(index));
        } else {
            component = component->component(stack.at(index));
        }
    }

    return component->variable(stack.back());
}

void makeEquivalence(const IndexStack &stack1, const IndexStack &stack2, const ModelPtr &model)
{
    auto v1 = getVariableLocatedAt(stack1, model);
    auto v2 = getVariableLocatedAt(stack2, model);
    Variable::addEquivalence(v1, v2);
}

void applyEquivalenceMapToModel(const EquivalenceMap &map, const ModelPtr &model)
{
    for (const auto &iter : map) {
        auto key = iter.first;
        auto vector = iter.second;
        for (auto vectorIter = vector.begin(); vectorIter < vector.end(); ++vectorIter) {
            makeEquivalence(key, *vectorIter, model);
        }
    }
}

void listComponentIds(const ComponentPtr &component, IdList &idList)
{
    std::string id = component->id();
    if (!id.empty()) {
        idList.insert(id);
    }
    // Imports.
    if (component->isImport()) {
        if (component->importSource() != nullptr) {
            id = component->importSource()->id();
            if (!id.empty()) {
                idList.insert(id);
            }
        }
    }
    // Component reference in encapsulation structure.
    id = component->encapsulationId();
    if (!id.empty()) {
        idList.insert(id);
    }
    // Variables.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        id = component->variable(v)->id();
        if (!id.empty()) {
            idList.insert(id);
        }

        for (size_t e = 0; e < component->variable(v)->equivalentVariableCount(); ++e) {
            // Equivalent variable mappings.
            id = Variable::equivalenceMappingId(component->variable(v), component->variable(v)->equivalentVariable(e));
            if (!id.empty()) {
                idList.insert(id);
            }
            // Connections.
            id = Variable::equivalenceConnectionId(component->variable(v), component->variable(v)->equivalentVariable(e));
            if (!id.empty()) {
                idList.insert(id);
            }
        }
    }
    // Resets.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        id = component->reset(r)->id();
        if (!id.empty()) {
            idList.insert(id);
        }
        id = component->reset(r)->testValueId();
        if (!id.empty()) {
            idList.insert(id);
        }
        id = component->reset(r)->resetValueId();
        if (!id.empty()) {
            idList.insert(id);
        }
    }

    // NB ids on component and reset MathML blocks and their children are not yet included.

    for (size_t c = 0; c < component->componentCount(); ++c) {
        listComponentIds(component->component(c), idList);
    }
}

IdList listIds(const ModelPtr &model)
{
    // Collect all existing ids in a list and return. NB can't use a map or a set as we need to be able to print
    // invalid models (with duplicated ids) too.

    std::unordered_set<std::string> idList;
    // Model.
    std::string id = model->id();
    if (!id.empty()) {
        idList.insert(id);
    }
    // Units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        auto units = model->units(u);
        id = units->id();
        if (!id.empty()) {
            idList.insert(id);
        }
        // Imports.
        if (units->isImport()) {
            if (units->importSource() != nullptr) {
                id = units->importSource()->id();
                if (!id.empty()) {
                    idList.insert(id);
                }
            }
        }
        for (size_t i = 0; i < model->units(u)->unitCount(); ++i) {
            std::string prefix;
            std::string reference;
            double exponent;
            double multiplier;
            model->units(u)->unitAttributes(i, reference, prefix, exponent, multiplier, id);
            if (!id.empty()) {
                idList.insert(id);
            }
        }
    }
    // Components.
    for (size_t c = 0; c < model->componentCount(); ++c) {
        listComponentIds(model->component(c), idList);
    }
    // Encapsulation.
    id = model->encapsulationId();
    if (!id.empty()) {
        idList.insert(id);
    }

    return idList;
}

std::string makeUniqueId(IdList &idList)
{
    // Because the hexadecimal counter starts high enough that it will always have a letter as the first character,
    // we don't need to prefix it with any other string to be valid.
    int counter = 0xb4da55;
    std::stringstream stream;
    stream << std::hex << counter;
    std::string id = stream.str();
    stream.str(std::string());

    while (idList.count(id) != 0) {
        ++counter;
        stream << std::hex << counter;
        id = stream.str();
        stream.str(std::string());
    }
    idList.insert(id);
    return id;
}

ConnectionMap createConnectionMap(const VariablePtr &variable1, const VariablePtr &variable2)
{
    ConnectionMap map;

    ComponentPtr component1 = owningComponent(variable1);
    ComponentPtr component2 = owningComponent(variable2);
    if ((component1 != nullptr) && (component2 != nullptr)) {
        for (size_t i = 0; i < component1->variableCount(); ++i) {
            auto v = component1->variable(i);
            for (const auto &vEquiv : equivalentVariables(v)) {
                if (owningComponent(vEquiv) == component2) {
                    map.insert(std::make_pair(v, vEquiv));
                }
            }
        }
    }

    return map;
}

void recursiveEquivalentVariables(const VariablePtr &variable, std::vector<VariablePtr> &equivalentVariables)
{
    for (size_t i = 0; i < variable->equivalentVariableCount(); ++i) {
        VariablePtr equivalentVariable = variable->equivalentVariable(i);

        if (std::find(equivalentVariables.begin(), equivalentVariables.end(), equivalentVariable) == equivalentVariables.end()) {
            equivalentVariables.push_back(equivalentVariable);

            recursiveEquivalentVariables(equivalentVariable, equivalentVariables);
        }
    }
}

std::vector<VariablePtr> equivalentVariables(const VariablePtr &variable)
{
    std::vector<VariablePtr> res = {variable};

    recursiveEquivalentVariables(variable, res);

    return res;
}

bool linkComponentVariableUnits(const ComponentPtr &component, std::vector<IssuePtr> &issueList)
{
    bool status = true;
    for (size_t index = 0; index < component->variableCount(); ++index) {
        auto v = component->variable(index);
        auto u = v->units();

        if (u != nullptr) {
            auto model = owningModel(u);
            if (model == owningModel(v)) {
                // Units are already linked, and exist in this model.
                continue;
            }
            if ((model == nullptr) && !isStandardUnit(u)) {
                model = owningModel(component);
                if (model->hasUnits(u->name())) {
                    v->setUnits(model->units(u->name()));
                } else {
                    auto issue = Issue::create();
                    issue->setDescription("Model does not contain the units '" + u->name() + "' required by variable '" + v->name() + "' in component '" + component->name() + "'.");
                    issue->setLevel(Issue::Level::WARNING);
                    issue->setVariable(v);
                    issueList.push_back(issue);
                    status = false;
                }
            } else if (model != nullptr) {
                auto issue = Issue::create();
                issue->setDescription("The units '" + u->name() + "' assigned to variable '" + v->name() + "' in component '" + component->name() + "' belong to a different model, '" + model->name() + "'.");
                issue->setLevel(Issue::Level::WARNING);
                issue->setVariable(v);
                issueList.push_back(issue);
                status = false;
            }
        }
    }
    return status;
}

bool traverseComponentEntityTreeLinkingUnits(const ComponentEntityPtr &componentEntity)
{
    std::vector<IssuePtr> issueList;
    return traverseComponentEntityTreeLinkingUnits(componentEntity, issueList);
}

bool traverseComponentEntityTreeLinkingUnits(const ComponentEntityPtr &componentEntity, std::vector<IssuePtr> &issueList)
{
    auto component = std::dynamic_pointer_cast<Component>(componentEntity);
    bool status = (component != nullptr) ?
                      linkComponentVariableUnits(component, issueList) :
                      true;
    for (size_t index = 0; index < componentEntity->componentCount(); ++index) {
        auto c = componentEntity->component(index);
        status = traverseComponentEntityTreeLinkingUnits(c, issueList) && status;
    }
    return status;
}

bool areComponentVariableUnitsUnlinked(const ComponentPtr &component)
{
    bool unlinked = false;
    for (size_t index = 0; index < component->variableCount() && !unlinked; ++index) {
        auto v = component->variable(index);
        auto u = v->units();
        if (u != nullptr) {
            auto model = owningModel(u);
            unlinked = ((model == nullptr) && !isStandardUnit(u)) || (owningModel(component) != model);
        }
    }
    return unlinked;
}

std::string replace(std::string string, const std::string &from, const std::string &to)
{
    auto index = string.find(from);

    return (index == std::string::npos) ?
               string :
               string.replace(index, from.length(), to);
}

bool equalEntities(const EntityPtr &owner, const std::vector<EntityPtr> &entities)
{
    std::vector<size_t> unmatchedIndex(entities.size());
    std::iota(unmatchedIndex.begin(), unmatchedIndex.end(), 0);
    for (const auto &entity : entities) {
        bool entityFound = false;
        size_t index = 0;
        for (index = 0; index < unmatchedIndex.size() && !entityFound; ++index) {
            size_t currentIndex = unmatchedIndex.at(index);
            auto model = std::dynamic_pointer_cast<Model>(owner);
            if (model != nullptr) {
                auto unitsOther = model->units(currentIndex);
                if (entity->equals(unitsOther)) {
                    entityFound = true;
                }
            } else {
                auto component = std::dynamic_pointer_cast<Component>(owner);
                auto variable = std::dynamic_pointer_cast<Variable>(entity);
                if (variable != nullptr) {
                    auto variableOther = component->variable(currentIndex);
                    if (variable->equals(variableOther)) {
                        entityFound = true;
                    }
                } else {
                    auto reset = std::dynamic_pointer_cast<Reset>(entity);
                    auto resetOther = component->reset(currentIndex);
                    if (reset->equals(resetOther)) {
                        entityFound = true;
                    }
                }
            }
        }
        if (entityFound && index < size_t(std::numeric_limits<ptrdiff_t>::max())) {
            // We are going to assume here that nobody is going to add more
            // than 2,147,483,647 units to this component. And much more than
            // that in a 64-bit environment.
            unmatchedIndex.erase(unmatchedIndex.begin() + ptrdiff_t(index) - 1);
        } else {
            return false;
        }
    }
    return true;
}

} // namespace libcellml
