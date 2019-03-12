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

// Declare _USE_MATH_DEFINES so that MSVC can find M_PI.
#define _USE_MATH_DEFINES

#include "libcellml/generator.h"
#include "libcellml/component.h"
#include "libcellml/model.h"
#include "libcellml/namespaces.h"
#include "libcellml/variable.h"

#include "operatorlibrary.h"
#include "xmlnode.h"
#include "xmldoc.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace libcellml{

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

struct Generator::GeneratorImpl
{
    enum class DataType {
        Void,
        Double,
        DoubleCst,
        DoublePtr,
        DoubleRef
    };

    Generator *mGenerator;

    void findVoi(const std::string &math);
    void findVoiHelper(const XmlNodePtr &node);
    void findInitialValues(const ComponentPtr &component);
    std::vector<operators::RepresentablePtr> parseMathML(const std::string &math);
    operators::RepresentablePtr parseNode(const XmlNodePtr &node);
    std::string generateCode(const ModelPtr &model);
    std::string generateInitConsts();
    std::string generateComputeRates(const std::vector<operators::RepresentablePtr> &representables);
    std::string generateComputeVariables(const std::vector<operators::RepresentablePtr> &representables);
    std::string generateStateAliases();
    std::string generateRateAliases();
    std::string generateAlgebraicAliases();
    std::string generateVoiAlias();

    std::string dataType(DataType dataType);
    std::string beginArgList() { return "("; }
    std::string endArgList() { return ")"; }
    std::string beginFunction() { return "{"; }
    std::string endFunction() { return "}"; }
    std::string endInstruction() { return ";"; }
    std::string dereferenceOp() { return "*"; }

    std::string mVoi;
    std::vector<std::string> mStates;
    std::vector<std::string> mAlgebraic;
    std::map<std::string, double> mInitialValues;
    std::string mCode = "";
};

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
    mPimpl->mGenerator = this;
}

Generator::~Generator()
{
    delete mPimpl;
}

std::string Generator::GeneratorImpl::generateStateAliases()
{
    std::string repr = "";
    for (size_t i = 0; i < mStates.size(); ++i) {
        repr +=   "    "
                + dataType(DataType::DoubleRef) + mStates[i] + " = "
                + dereferenceOp() + "(states + " + std::to_string(i) + ")"
                + endInstruction() + "\n";
    }
    return repr + "\n";
}

std::string Generator::GeneratorImpl::generateRateAliases()
{
    std::string repr = "";
    for (size_t i = 0; i < mStates.size(); ++i) {
        repr +=   "    "
                + dataType(DataType::DoubleRef) + "D" + mStates[i] + " = "
                + dereferenceOp() + "(rates + " + std::to_string(i) + ")"
                + endInstruction() + "\n";
    }
    return repr + "\n";
}

std::string Generator::GeneratorImpl::generateAlgebraicAliases()
{
    std::string repr = "";
    for (size_t i = 0; i < mAlgebraic.size(); ++i) {
        repr +=   "    "
                + dataType(DataType::DoubleRef) + mAlgebraic[i] + " = "
                + dereferenceOp() + "(algebraic + " + std::to_string(i) + ")"
                + endInstruction() + "\n";
    }
    return repr + "\n";
}

std::string Generator::GeneratorImpl::generateVoiAlias()
{
    return   "    "
           + dataType(DataType::DoubleCst) + mVoi + " = voi"
           + endInstruction() + "\n\n";
}

std::string Generator::GeneratorImpl::generateInitConsts()
{
    std::string repr =   dataType(DataType::Void) + "initConsts"
                       + beginArgList()
                       + dataType(DataType::DoublePtr)
                       + "constants, "
                       + dataType(DataType::DoublePtr)
                       + "rates, "
                       + dataType(DataType::DoublePtr)
                       + "states, "
                       + dataType(DataType::DoublePtr)
                       + "algebraic"
                       + endArgList() + "\n"
                       + beginFunction() + "\n"
                       + generateStateAliases() + "\n"
                       + generateAlgebraicAliases() + "\n";
    for (auto initialValue : mInitialValues) {
        repr +=   "    " + initialValue.first + " = "
                + operators::Constant::repr(initialValue.second)
                + endInstruction() + "\n";
    }
    return repr + "\n" + endFunction();
}

std::string Generator::GeneratorImpl::generateComputeRates(const std::vector<operators::RepresentablePtr> &representables)
{
    std::string repr =   dataType(DataType::Void) + "computeRates"
                       + beginArgList()
                       + dataType(DataType::Double)
                       + "voi, "
                       + dataType(DataType::DoublePtr)
                       + "constants, "
                       + dataType(DataType::DoublePtr)
                       + "rates, "
                       + dataType(DataType::DoublePtr)
                       + "states, "
                       + dataType(DataType::DoublePtr)
                       + "algebraic"
                       + endArgList() + "\n"
                       + beginFunction() + "\n"
                       + generateVoiAlias() + "\n"
                       + generateStateAliases() + "\n"
                       + generateRateAliases() + "\n"
                       + generateAlgebraicAliases() + "\n";
    for (auto representable : representables) {
        auto &arg1 = *(static_cast<operators::Equation*>(&*representable)->getArg1());
        // Here, we assume that the first node is always of type Equation and
        // use this fact to distinguish ODEs from algebraic equations.
        if (typeid(arg1).hash_code() == typeid(operators::Derivative).hash_code()) {
            repr +=   "    "
                    + representable->repr()
                    + endInstruction() + "\n";
        }
    }
    return repr + "\n" + endFunction();
}

std::string Generator::GeneratorImpl::generateComputeVariables(const std::vector<operators::RepresentablePtr> &representables)
{
    std::string repr =   dataType(DataType::Void) + "computeVariables"
                       + beginArgList()
                       + dataType(DataType::Double)
                       + "voi, "
                       + dataType(DataType::DoublePtr)
                       + "constants, "
                       + dataType(DataType::DoublePtr)
                       + "rates, "
                       + dataType(DataType::DoublePtr)
                       + "states, "
                       + dataType(DataType::DoublePtr)
                       + "algebraic"
                       + endArgList()  + "\n"
                       + beginFunction() + "\n"
                       + generateVoiAlias() + "\n"
                       + generateStateAliases() + "\n"
                       + generateRateAliases() + "\n"
                       + generateAlgebraicAliases() + "\n";
    for (auto representable : representables) {
        auto &arg1 = *(static_cast<operators::Equation*>(&*representable)->getArg1());
        // Here, we assume that the first node is always of type Equation and
        // use this fact to distinguish ODEs from algebraic equations.
        if (typeid(arg1).hash_code() == typeid(operators::Variable).hash_code()) {
            repr +=   "    "
                    + representable->repr()
                    + endInstruction() + "\n";
        }
    }
    return repr + "\n" + endFunction();
}

void Generator::GeneratorImpl::findInitialValues(const ComponentPtr &component)
{
    for (std::size_t i = 0; i < component->variableCount(); ++i) {
        auto variable = component->getVariable(i);
        if (variable->getName() != mVoi) {
            mInitialValues[variable->getName()] = std::stod(variable->getInitialValue());
        }
    }
}

std::string Generator::GeneratorImpl::generateCode(const ModelPtr &model)
{
    ComponentPtr component = model->getComponent(0);

    findVoi(component->getMath());
    findInitialValues(component);
    auto math = parseMathML(component->getMath());

    mCode =   generateInitConsts() + "\n"
            + generateComputeRates(math) + "\n"
            + generateComputeVariables(math) + "\n";

    return mCode;
}

std::string Generator::GeneratorImpl::dataType(DataType dataType)
{
    static const std::unordered_map<DataType, std::string, EnumClassHash> dataTypes = {
        { DataType::Void, "void " },
        { DataType::Double, "double " },
        { DataType::DoubleCst, "const double " },
        { DataType::DoublePtr, "double *" },
        { DataType::DoubleRef, "double &" }
    };

    return dataTypes.at(dataType);
}

std::string Generator::generateCode(const ModelPtr &model)
{
    return mPimpl->generateCode(model);
}

void Generator::writeCodeToFile(const std::string &filename)
{
    if (mPimpl->mCode.empty()) {
        ErrorPtr error = std::make_shared<Error>();
        error->setDescription("No code was detected. The file '"
                              + filename + "' was not written to. Please check that Generator::generateCode() is used before Generator::writeCodeToFile().");
        addError(error);
    } else {
        std::ofstream output(filename);
        output << mPimpl->mCode;
        output.close();
    }
}

operators::RepresentablePtr Generator::GeneratorImpl::parseNode(const XmlNodePtr &node)
{
    if (node->isElement("eq", MATHML_NS)) {
        auto r = std::make_shared<operators::Equation>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("apply", MATHML_NS)) {
        return parseNode(node->getFirstChild());
    } else if (node->isElement("plus", MATHML_NS)) {
        // Unary plus (positive) and binary plus (addition) have the same node
        // name, so we tell them apart by checking their number of arguments.
        if (node->getNext()->getNext()) {
            auto r = std::make_shared<operators::Addition>();
            auto n = node->getNext();
            r->setArg1(parseNode(n));
            n = n->getNext();
            if (!n->getNext()) {
                r->setArg2(parseNode(n));
            } else {
                auto p0 = r;
                while (n->getNext()) {
                    auto p1 = std::make_shared<operators::Addition>();
                    p1->setArg1(parseNode(n));
                    p0->setArg2(p1);
                    n = n->getNext();
                    p0 = p1;
                }
                p0->setArg2(parseNode(n));
            }
            return r;
        } else {
            auto r = std::make_shared<operators::Positive>();
            r->setArg(parseNode(node->getNext()));
            return r;
        }
    }
    else if (node->isElement("minus", MATHML_NS)) {
        // Unary minus (negative) and binary minus (subtraction) have the same node
        // name, so we tell them apart by checking the number of arguments.
        if (node->getNext()->getNext()) {
            auto r = std::make_shared<operators::Subtraction>();
            auto n = node->getNext();
            r->setArg1(parseNode(n));
            r->setArg2(parseNode(n->getNext()));
            return r;
        } else {
            auto r = std::make_shared<operators::Negative>();
            r->setArg(parseNode(node->getNext()));
            return r;
        }
    }
    else if (node->isElement("times", MATHML_NS)) {
        auto r = std::make_shared<operators::Multiplication>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        n = n->getNext();
        if (!n->getNext()) {
            r->setArg2(parseNode(n));
        } else {
            auto p0 = r;
            while (n->getNext()) {
                auto p1 = std::make_shared<operators::Multiplication>();
                p1->setArg1(parseNode(n));
                p0->setArg2(p1);
                n = n->getNext();
                p0 = p1;
            }
            p0->setArg2(parseNode(n));
        }
        return r;
    } else if (node->isElement("divide", MATHML_NS)) {
        auto r = std::make_shared<operators::Division>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("piecewise", MATHML_NS)) {
        // A piecewise definition can be implemented as the sum of the products
        // of each piece's expression and its condition.
        auto r = std::make_shared<operators::Addition>();
        auto n = node->getFirstChild();
        r->setArg1(parseNode(n));
        n = n->getNext();
        if (!n->getNext()) {
            r->setArg2(parseNode(n));
        } else {
            auto p0 = r;
            while (n->getNext()) {
                auto p1 = std::make_shared<operators::Addition>();
                p1->setArg1(parseNode(n));
                p0->setArg2(p1);
                n = n->getNext();
                p0 = p1;
            }
            p0->setArg2(parseNode(n));
        }
        return r;
    }
    else if (node->isElement("piece", MATHML_NS)) {
        // A piece of a piecewise definition can be implemented as the product
        // of its expression and its condition.
        auto r = std::make_shared<operators::Multiplication>();
        auto n = node->getFirstChild();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("and", MATHML_NS)) {
        auto r = std::make_shared<operators::And>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("or", MATHML_NS)) {
        auto r = std::make_shared<operators::Or>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("lt", MATHML_NS)) {
        auto r = std::make_shared<operators::Less>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("leq", MATHML_NS)) {
        auto r = std::make_shared<operators::LessOrEqual>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("geq", MATHML_NS)) {
        auto r = std::make_shared<operators::GreaterOrEqual>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("gt", MATHML_NS)) {
        auto r = std::make_shared<operators::Greater>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("power", MATHML_NS)) {
        auto r = std::make_shared<operators::Power>();
        auto n = node->getNext();
        r->setArg1(parseNode(n));
        r->setArg2(parseNode(n->getNext()));
        return r;
    } else if (node->isElement("sin", MATHML_NS)) {
        auto r = std::make_shared<operators::Sine>();
        r->setArg(parseNode(node->getNext()));
        return r;
    } else if (node->isElement("cos", MATHML_NS)) {
        auto r = std::make_shared<operators::Cosine>();
        r->setArg(parseNode(node->getNext()));
        return r;
    } else if (node->isElement("floor", MATHML_NS)) {
        auto r = std::make_shared<operators::Floor>();
        r->setArg(parseNode(node->getNext()));
        return r;
    } else if (node->isElement("abs", MATHML_NS)) {
        auto r = std::make_shared<operators::AbsoluteValue>();
        r->setArg(parseNode(node->getNext()));
        return r;
    } else if (node->isElement("not", MATHML_NS)) {
        auto r = std::make_shared<operators::Not>();
        r->setArg(parseNode(node->getNext()));
        return r;
    } else if (node->isElement("ci", MATHML_NS)) {
        auto name = node->getFirstChild()->convertToString();
        auto r = std::make_shared<operators::Variable>(name);
        // All variables are in mAlgebraic unless they are in mStates already
        if (   (name != mVoi)
            && std::find(mStates.begin(), mStates.end(), name) == mStates.end()
            && std::find(mAlgebraic.begin(), mAlgebraic.end(), name) == mAlgebraic.end()) {
            mAlgebraic.push_back(name);
        }
        return r;
    } else if (node->isElement("cn", MATHML_NS)) {
        return std::make_shared<operators::Constant>(std::stod(node->getFirstChild()->convertToString()));
    } else if (node->isElement("pi", MATHML_NS)) {
        return std::make_shared<operators::Constant>(M_PI);
    } else if (node->isElement("diff", MATHML_NS)) {
        auto name = node->getNext()->getNext()->getFirstChild()->convertToString();
        auto r = std::make_shared<operators::Derivative>(name);
        // When we find the derivative of a variable, that variable goes in
        // mStates.
        if (std::find(mStates.begin(), mStates.end(), name) == mStates.end()) {
            mStates.push_back(name);
            // If it was previously put in mAlgebraic, it must be removed.
            auto algebraic = std::find(mAlgebraic.begin(), mAlgebraic.end(), name);
            if (algebraic != mAlgebraic.end()) {
                mAlgebraic.erase(algebraic);
            }
        }
        return r;
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Found node of type '"
                + node->getName() +
                "' which is currently not supported.");
        mGenerator->addError(err);

        return std::make_shared<operators::Constant>(0);
    }
}

std::vector<operators::RepresentablePtr> Generator::GeneratorImpl::parseMathML(const std::string &math)
{
    std::vector<operators::RepresentablePtr> nodes;

    XmlDocPtr mathDoc = std::make_shared<XmlDoc>();
    mathDoc->parse(math);

    XmlNodePtr childNode = mathDoc->getRootNode()->getFirstChild();
    while (childNode) {
        nodes.push_back(parseNode(childNode));
        childNode = childNode->getNext();
    }

    return nodes;
}

void Generator::GeneratorImpl::findVoiHelper(const XmlNodePtr &node)
{
    if (node->isElement("bvar", MATHML_NS)) {
        mVoi = node->getFirstChild()->getFirstChild()->convertToString();
        return;
    } else {
        if (node->getFirstChild()) {
            findVoiHelper(node->getFirstChild());
        }
        if (node->getNext()) {
            findVoiHelper(node->getNext());
        }
    }
}

void Generator::GeneratorImpl::findVoi(const std::string &math)
{
    XmlDocPtr mathDoc = std::make_shared<XmlDoc>();
    mathDoc->parse(math);

    findVoiHelper(mathDoc->getRootNode()->getFirstChild());
}

}
