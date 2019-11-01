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

#include "libcellml/component.h"
#include "libcellml/model.h"
#include "libcellml/namedentity.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <vector>

namespace libcellml {

double convertToDouble(const std::string &candidate)
{
    double value = 0.0;
    try {
        value = std::stod(candidate);
    } catch (...) {
        value = std::numeric_limits<double>::infinity();
    }
    return value;
}

bool hasNonWhitespaceCharacters(const std::string &input)
{
    return input.find_first_not_of(" \t\n\v\f\r") != std::string::npos;
}

std::string convertDoubleToString(double value)
{
    std::ostringstream strs;
    strs << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return strs.str();
}

int convertToInt(const std::string &candidate)
{
    return std::stoi(candidate);
}

std::string convertIntToString(int value)
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

std::vector<size_t> findOccurences(const std::string &candidate, const std::string &sub)
{
    std::vector<size_t> occurences;
    size_t pos = candidate.find(sub, 0);
    while (pos != std::string::npos) {
        occurences.push_back(pos);
        pos = candidate.find(sub, pos + 1);
    }
    return occurences;
}

bool isCellMLBasicReal(const std::string &candidate)
{
    if (!candidate.empty()) {
        std::vector<size_t> decimalOccurences = findOccurences(candidate, ".");
        if (decimalOccurences.size() < 2) {
            bool beginsMinus = *candidate.begin() == '-';
            std::string numbersOnlyCandidate = candidate;
            if (decimalOccurences.size() == 1) {
                numbersOnlyCandidate.erase(decimalOccurences.at(0), 1);
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
        std::vector<size_t> eOccurences = findOccurences(candidate, "E");
        for (const auto &ePos : eOccurences) {
            normalisedCandidate.replace(ePos, 1, "e");
        }
        std::vector<size_t> lowerEOccurences = findOccurences(normalisedCandidate, "e");
        size_t eIndicatorCount = lowerEOccurences.size();
        if (eIndicatorCount < 2) {
            if (eIndicatorCount == 1) {
                size_t ePos = lowerEOccurences.at(0);
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

std::string entityName(const EntityPtr &entity)
{
    std::string name;
    auto namedEntity = std::dynamic_pointer_cast<NamedEntity>(entity);
    if (namedEntity != nullptr) {
        name = namedEntity->name();
    }
    return name;
}

ModelPtr owningModel(const EntityPtr &entity)
{
    auto model = std::dynamic_pointer_cast<Model>(entity->parent());
    auto component = std::dynamic_pointer_cast<Component>(entity->parent());
    while (!model && component && component->parent()) {
        model = std::dynamic_pointer_cast<Model>(component->parent());
        component = std::dynamic_pointer_cast<Component>(component->parent());
    }

    return model;
}

void removeComponentFromEntity(const EntityPtr &entity, const ComponentPtr &component)
{
    auto componentEntity = std::dynamic_pointer_cast<ComponentEntity>(entity);
    componentEntity->removeComponent(component, false);
}

} // namespace libcellml
