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
#include <memory>
#include <sstream>
#include <typeinfo>
#include <map>
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
    enum class types {void_t, double_t, double_ct, double_pt, double_rt};

    Generator *mGenerator;

    void findVOI(const std::string &math);
    void findVOIHelper(const XmlNodePtr &node);
    void findInitialValues(const ComponentPtr &component);
    std::vector<operators::RepresentablePtr> parseMathML(const std::string &math);
    operators::RepresentablePtr parseNode(const XmlNodePtr &node);
    std::string doGenerateCode(const ModelPtr &model);
    std::string generateInitConsts();
    std::string generateComputeRates(const std::vector<operators::RepresentablePtr> &representables);
    std::string generateComputeVariables(const std::vector<operators::RepresentablePtr> &representables);
    std::string generateStateAliases();
    std::string generateRateAliases();
    std::string generateAlgebraicAliases();
    std::string generateVoiAlias();

    std::string returnType(types t);
    std::string argType(types t);
    std::string argListOp() {return "(";}
    std::string argListCl() {return ")";}
    std::string funBodyOp() {return "{";}
    std::string funBodyCl() {return "}";}
    std::string instructionDelimiter() {return ";";}
    std::string dereferenceOp() {return "*";}

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
    std::string s;
    std::ostringstream oss(s);
    for (size_t i = 0; i < mStates.size(); i++)
    {
        oss << "    "
            << argType(types::double_rt) << mStates[i] << " = "
            << dereferenceOp() << "(states + " << i << ")"
            << instructionDelimiter() << std::endl;
    }
    oss << std::endl;
    return oss.str();
}

std::string Generator::GeneratorImpl::generateRateAliases()
{
    std::string s;
    std::ostringstream oss(s);
    for (size_t i = 0; i < mStates.size(); i++)
    {
        oss << "    "
            << argType(types::double_rt) << "D" << mStates[i] << " = "
            << dereferenceOp() << "(rates + " << i << ")"
            << instructionDelimiter() << std::endl;
    }
    oss << std::endl;
    return oss.str();
}

std::string Generator::GeneratorImpl::generateAlgebraicAliases()
{
    std::string s;
    std::ostringstream oss(s);
    for (size_t i = 0; i < mAlgebraic.size(); i++)
    {
        oss << "    "
            << argType(types::double_rt) << mAlgebraic[i] << " = "
            << dereferenceOp() << "(algebraic + " << i << ")"
            << instructionDelimiter() << std::endl;
    }
    oss << std::endl;
    return oss.str();
}

std::string Generator::GeneratorImpl::generateVoiAlias()
{
    std::string s;
    std::ostringstream oss(s);
    oss << "    "
        << argType(types::double_ct) << mVoi << " = voi" << instructionDelimiter() << std::endl;
    oss << std::endl;
    return oss.str();
}

std::string Generator::GeneratorImpl::generateInitConsts()
{
    std::string s;
    std::ostringstream oss(s);
    oss << returnType(types::void_t) << "initConsts"
        << argListOp()
        << argType(types::double_pt)
        << "constants, "
        << argType(types::double_pt)
        << "rates, "
        << argType(types::double_pt)
        << "states, "
        << argType(types::double_pt)
        << "algebraic"
        << argListCl() << std::endl
        << funBodyOp() << std::endl;

    oss << generateStateAliases() << std::endl;
    oss << generateAlgebraicAliases() << std::endl;
    for (auto s : mInitialValues)
    {
        oss << "    " << s.first << " = "
            << std::setprecision(16) << s.second << instructionDelimiter() << std::endl;
    }
    oss << std::endl << funBodyCl();
    return oss.str();
}

std::string Generator::GeneratorImpl::generateComputeRates(const std::vector<operators::RepresentablePtr> &representables)
{
    std::string s;
    std::ostringstream oss(s);
    oss << returnType(types::void_t) << "computeRates"
        << argListOp()
        << argType(types::double_t)
        << "voi, "
        << argType(types::double_pt)
        << "constants, "
        << argType(types::double_pt)
        << "rates, "
        << argType(types::double_pt)
        << "states, "
        << argType(types::double_pt)
        << "algebraic"
        << argListCl() << std::endl
        << funBodyOp() << std::endl;

    oss << generateVoiAlias() << std::endl;
    oss << generateStateAliases() << std::endl;
    oss << generateRateAliases() << std::endl;
    oss << generateAlgebraicAliases() << std::endl;

    for (auto representable : representables)
    {
        auto& p = *(static_cast<operators::Equation*>(&*representable)->getArg1());
        // Here I assume that the first node is always of type Equation, and use
        // this fact to distinguish ODEs from algebraic equations.
        if (typeid(p).hash_code() == typeid(operators::Derivative).hash_code()) {
            oss << "    "
                << representable->repr() << ";" << std::endl;
        }
    }

    oss << std::endl
        << funBodyCl();
    return oss.str();
}

std::string Generator::GeneratorImpl::generateComputeVariables(const std::vector<operators::RepresentablePtr> &representables)
{
    std::string s;
    std::ostringstream oss(s);
    oss << returnType(types::void_t) << "computeVariables"
        << argListOp()
        << argType(types::double_t)
        << "voi, "
        << argType(types::double_pt)
        << "constants, "
        << argType(types::double_pt)
        << "rates, "
        << argType(types::double_pt)
        << "states, "
        << argType(types::double_pt)
        << "algebraic"
        << argListCl()  << std::endl
        << funBodyOp() << std::endl;

    oss << generateVoiAlias() << std::endl;
    oss << generateStateAliases() << std::endl;
    oss << generateRateAliases() << std::endl;
    oss << generateAlgebraicAliases() << std::endl;

    for (auto representable : representables)
    {
        auto& p = *(static_cast<operators::Equation*>(&*representable)->getArg1());
        // Here I assume that the first node is always of type Equation, and use
        // this fact to distinguish ODEs from algebraic equations.
        if (typeid(p).hash_code() == typeid(operators::Variable).hash_code()) {
            oss << "    "
                << representable->repr() << ";" << std::endl;
        }
    }

    oss << std::endl
        << funBodyCl();
    return oss.str();
}

void Generator::GeneratorImpl::findInitialValues(const ComponentPtr &component)
{
    for (std::size_t i = 0; i < component->variableCount(); i++)
    {
        auto v = component->getVariable(i);
        if (v->getName() != mVoi) {
            mInitialValues[v->getName()] = std::stod(v->getInitialValue());
        }
    }
}

std::string Generator::GeneratorImpl::doGenerateCode(const ModelPtr &model)
{
    ComponentPtr component = model->getComponent(0);

    findVOI(component->getMath());
    findInitialValues(component);
    auto math = parseMathML(component->getMath());

    std::string generatedCode;
    std::ostringstream oss(generatedCode);
    oss << generateInitConsts() << std::endl;
    oss << generateComputeRates(math) << std::endl;
    oss << generateComputeVariables(math) << std::endl;

    mCode = oss.str();
    return mCode;
}

std::string Generator::GeneratorImpl::returnType(types t)
{
    static const std::unordered_map<types, std::string, EnumClassHash> returnTypes = {
        {types::void_t,"void "},
        {types::double_t, "double "},
        {types::double_ct, "const double "},
        {types::double_pt, "double *"},
        {types::double_rt, "double &"}
    };

    return returnTypes.at(t);
}

std::string Generator::GeneratorImpl::argType(types t)
{
    static const std::unordered_map<types, std::string, EnumClassHash> argTypes = {
        {types::void_t,"void "},
        {types::double_t, "double "},
        {types::double_ct, "const double "},
        {types::double_pt, "double *"},
        {types::double_rt, "double &"},
    };

    return argTypes.at(t);
}

std::string Generator::generateCode(const ModelPtr &model)
{
    return mPimpl->doGenerateCode(model);
}

void Generator::writeCodeToFile(const std::string &filename)
{
    if (mPimpl->mCode == "") {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("No code was detected. The file '"
                            + filename + "' was not written to. Please check that Generator::generateCode() is used before Generator::writeCodeToFile().");
        addError(err);
    } else {
        std::ofstream output(filename);
        output << mPimpl->mCode;
        output.close();
    }
}

operators::RepresentablePtr Generator::GeneratorImpl::parseNode(const XmlNodePtr &node)
{
    if (node->isElement("eq", MATHML_NS)) {
        auto c = std::make_shared<operators::Equation>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("apply", MATHML_NS)) {
        return parseNode(node->getFirstChild());
    } else if (node->isElement("plus", MATHML_NS)) {
        // Unary plus (positive) and binary plus (addition) have the same node
        // name, so we tell them apart by checking the number of arguments.
        if (node->getNext()->getNext()) {
            auto c = std::make_shared<operators::Addition>();
            auto s = node->getNext();
            c->setArg1(parseNode(s));
            s = s->getNext();
            if (!s->getNext()) {
                c->setArg2(parseNode(s));
            } else {
                auto pointer0 = c;
                while (s->getNext())
                {
                    auto pointer1 = std::make_shared<operators::Addition>();
                    pointer1->setArg1(parseNode(s));
                    pointer0->setArg2(pointer1);
                    s = s->getNext();
                    pointer0 = pointer1;
                }
                pointer0->setArg2(parseNode(s));
            }
            return c;
        } else {
            auto c = std::make_shared<operators::Positive>();
            c->setArg(parseNode(node->getNext()));
            return c;
        }
    }
    else if (node->isElement("minus", MATHML_NS)) {
        // Unary minus (negative) and binary minus (subtraction) have the same node
        // name, so we tell them apart by checking the number of arguments.
        if (node->getNext()->getNext()) {
            auto c = std::make_shared<operators::Subtraction>();
            auto s1 = node->getNext();
            c->setArg1(parseNode(s1));
            c->setArg2(parseNode(s1->getNext()));
            return c;
        } else {
            auto c = std::make_shared<operators::Negative>();
            c->setArg(parseNode(node->getNext()));
            return c;
        }
    }
    else if (node->isElement("times", MATHML_NS)) {
        auto c = std::make_shared<operators::Multiplication>();
        auto s = node->getNext();
        c->setArg1(parseNode(s));
        s = s->getNext();
        if (!s->getNext()) {
            c->setArg2(parseNode(s));
        } else {
            auto pointer0 = c;
            while (s->getNext())
            {
                auto pointer1 = std::make_shared<operators::Multiplication>();
                pointer1->setArg1(parseNode(s));
                pointer0->setArg2(pointer1);
                s = s->getNext();
                pointer0 = pointer1;
            }
            pointer0->setArg2(parseNode(s));
        }
        return c;
    } else if (node->isElement("divide", MATHML_NS)) {
        auto c = std::make_shared<operators::Division>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("piecewise", MATHML_NS)) {
        // A piecewise definition can be implemented as the sum of the products
        // of each piece's expression and its condition.
        auto c = std::make_shared<operators::Addition>();
        auto s = node->getFirstChild();
        c->setArg1(parseNode(s));
        s = s->getNext();
        if (!s->getNext()) {
            c->setArg2(parseNode(s));
        } else {
            auto pointer0 = c;
            while (s->getNext())
            {
                auto pointer1 = std::make_shared<operators::Addition>();
                pointer1->setArg1(parseNode(s));
                pointer0->setArg2(pointer1);
                s = s->getNext();
                pointer0 = pointer1;
            }
            pointer0->setArg2(parseNode(s));
        }
        return c;
    }
    else if (node->isElement("piece", MATHML_NS)) {
        // A piece of a piecewise definition can be implemented as the product
        // of its expression and its condition.
        auto c = std::make_shared<operators::Multiplication>();
        auto s1 = node->getFirstChild();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("and", MATHML_NS)) {
        auto c = std::make_shared<operators::And>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("or", MATHML_NS)) {
        auto c = std::make_shared<operators::Or>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("lt", MATHML_NS)) {
        auto c = std::make_shared<operators::Less>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("leq", MATHML_NS)) {
        auto c = std::make_shared<operators::LessOrEqual>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("geq", MATHML_NS)) {
        auto c = std::make_shared<operators::GreaterOrEqual>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("gt", MATHML_NS)) {
        auto c = std::make_shared<operators::Greater>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("power", MATHML_NS)) {
        auto c = std::make_shared<operators::Power>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    } else if (node->isElement("sin", MATHML_NS)) {
        auto c = std::make_shared<operators::Sine>();
        c->setArg(parseNode(node->getNext()));
        return c;
    } else if (node->isElement("cos", MATHML_NS)) {
        auto c = std::make_shared<operators::Cosine>();
        c->setArg(parseNode(node->getNext()));
        return c;
    } else if (node->isElement("floor", MATHML_NS)) {
        auto c = std::make_shared<operators::Floor>();
        c->setArg(parseNode(node->getNext()));
        return c;
    } else if (node->isElement("abs", MATHML_NS)) {
        auto c = std::make_shared<operators::AbsoluteValue>();
        c->setArg(parseNode(node->getNext()));
        return c;
    } else if (node->isElement("not", MATHML_NS)) {
        auto c = std::make_shared<operators::Not>();
        c->setArg(parseNode(node->getNext()));
        return c;
    } else if (node->isElement("ci", MATHML_NS)) {
        auto name = node->getFirstChild()->convertToString();
        auto c = std::make_shared<operators::Variable>(name);
        // All variables are in mAlgebraic unless they are in mStates already
        if (name != mVoi &&
                std::find(mStates.begin(),
                          mStates.end(),
                          name) == mStates.end() &&
                std::find(mAlgebraic.begin(),
                          mAlgebraic.end(),
                          name) == mAlgebraic.end()) {
            mAlgebraic.push_back(name);
        }
        return c;
    } else if (node->isElement("cn", MATHML_NS)) {
        double value;
        std::istringstream iss(node->getFirstChild()->convertToString());
        iss >> value;
        auto c = std::make_shared<operators::Constant>(value);
        return c;
    } else if (node->isElement("pi", MATHML_NS)) {
        auto c = std::make_shared<operators::Constant>(std::acos(-1));
        return c;
    } else if (node->isElement("diff", MATHML_NS)) {
        auto name = node->getNext()->getNext()->getFirstChild()->convertToString();
        auto c = std::make_shared<operators::Derivative>(name);
        // When we find the derivative of a variable, that variable goes in
        // mStates.
        if (std::find(mStates.begin(), mStates.end(), name) == mStates.end()) {
            mStates.push_back(name);
            // If it was previously put in mAlgebraic, it must be removed.
            auto p = std::find(mAlgebraic.begin(), mAlgebraic.end(), name);
            if (p != mAlgebraic.end()) {
                mAlgebraic.erase(p);
            }
        }
        return c;
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

    const XmlNodePtr root = mathDoc->getRootNode();

    XmlNodePtr childNode = root->getFirstChild();
    while (childNode)
    {
        nodes.push_back(parseNode(childNode));
        childNode = childNode->getNext();
    }

    return nodes;
}

void Generator::GeneratorImpl::findVOIHelper(const XmlNodePtr &node)
{
    if (node->isElement("bvar", MATHML_NS)) {
        mVoi = node->getFirstChild()->getFirstChild()->convertToString();
        return;
    } else {
        if (node->getFirstChild()) {
            findVOIHelper(node->getFirstChild());
        }
        if (node->getNext()) {
            findVOIHelper(node->getNext());
        }
    }
}

void Generator::GeneratorImpl::findVOI(const std::string &math)
{
    XmlDocPtr mathDoc = std::make_shared<XmlDoc>();
    mathDoc->parse(math);

    const XmlNodePtr root = mathDoc->getRootNode();
    XmlNodePtr node = root->getFirstChild();

    findVOIHelper(node);
}

}
