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

#include <typeinfo>

#include "libcellml/generator.h"
#include "libcellml/namespaces.h"

namespace libcellml{

using namespace libcellml::operators;

struct Generator::GeneratorImpl
{
    enum class types {void_t, double_t, double_ct, double_pt, double_rt};

    Generator* mGenerator;

    void findVOI(std::string math);
    void findVOIHelper(XmlNodePtr node);
    void findInitialValues(ComponentPtr c);
    std::vector<std::shared_ptr<libcellml::operators::Representable>> parseMathML(std::string math);
    std::shared_ptr<libcellml::operators::Representable> parseNode(XmlNodePtr node);
    std::string doGenerateCode(ModelPtr m);
    std::string generateInitConsts();
    std::string generateComputeRates(std::vector<std::shared_ptr<libcellml::operators::Representable>> r);
    std::string generateComputeVariables(std::vector<std::shared_ptr<libcellml::operators::Representable>> r);
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
    std::map<std::string,double> mInitialValues;
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
        << "states"
        << argListCl() << std::endl
        << funBodyOp() << std::endl;

    oss << generateStateAliases() << std::endl;
    for (auto s : mInitialValues)
    {
        // Only states get an initial value
        if (std::find(mStates.begin(), mStates.end(), s.first) != mStates.end())
        {
            oss << "    " << s.first << " = "
                << std::setprecision(16) << s.second << instructionDelimiter() << std::endl;
        }
    }
    oss << std::endl << funBodyCl();
    return oss.str();
}

std::string Generator::GeneratorImpl::generateComputeRates(std::vector<std::shared_ptr<Representable>> representables)
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

    for (auto r : representables)
    {
        auto& p = *(static_cast<Equation*>(&*r)->getArg1());
        // Here I assume that the first node is always of type Equation, and use
        // this fact to distinguish ODEs from algebraic equations.
        if (typeid(p).hash_code() == typeid(Derivative).hash_code())
        {
            oss << "    "
                << r->repr() << ";" << std::endl;
        }
    }

    oss << std::endl
        << funBodyCl();
    return oss.str();
}

std::string Generator::GeneratorImpl::generateComputeVariables(std::vector<std::shared_ptr<Representable>> representables)
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

    for (auto r : representables)
    {
        auto& p = *(static_cast<Equation*>(&*r)->getArg1());
        // Here I assume that the first node is always of type Equation, and use
        // this fact to distinguish ODEs from algebraic equations.
        if (typeid(p).hash_code() == typeid(libcellml::operators::Variable).hash_code())
        {
            oss << "    "
                << r->repr() << ";" << std::endl;
        }
    }

    oss << std::endl
        << funBodyCl();
    return oss.str();
}

void Generator::GeneratorImpl::findInitialValues(ComponentPtr c)
{
    for (std::size_t i = 0; i < c->variableCount(); i++)
    {
        auto v = c->getVariable(i);
        if (v->getName() != mVoi)
        {
            mInitialValues[v->getName()] = std::stod(v->getInitialValue());
        }
    }
}

std::string Generator::GeneratorImpl::doGenerateCode(ModelPtr m)
{
    ComponentPtr c = m->getComponent(0);

    findVOI(c->getMath());
    findInitialValues(c);
    auto r = parseMathML(c->getMath());

    std::string generatedCode;
    std::ostringstream oss(generatedCode);
    oss << generateInitConsts() << std::endl;
    oss << generateComputeRates(r) << std::endl;
    oss << generateComputeVariables(r) << std::endl;

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

std::string Generator::generateCode(ModelPtr m)
{
    return mPimpl->doGenerateCode(m);
}

void Generator::writeCodeToFile(std::string filename)
{
    if (mPimpl->mCode == "")
    {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("No code was generated yet, you should call "
                "Generator::generateCode before calling this method.");
        addError(err);
        throw CodeNotGenerated();
    }

    std::ofstream output(filename);
    output << mPimpl->mCode;
    output.close();
}

std::shared_ptr<Representable> Generator::GeneratorImpl::parseNode(XmlNodePtr node)
{
    if (node->isElement("eq", MATHML_NS))
    {
        auto c = std::make_shared<Equation>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    }
    else if (node->isElement("apply", MATHML_NS))
    {
        return parseNode(node->getFirstChild());
    }
    else if (node->isElement("plus", MATHML_NS))
    {
        auto c = std::make_shared<Addition>();
        auto s = node->getNext();
        c->setArg1(parseNode(s));
        s = s->getNext();
        if (!s->getNext())
        {
            c->setArg2(parseNode(s));
        }
        else
        {
            auto pointer0 = c;
            while (s->getNext())
            {
                auto pointer1 = std::make_shared<Addition>();
                pointer1->setArg1(parseNode(s));
                pointer0->setArg2(pointer1);
                s = s->getNext();
                pointer0 = pointer1;
            }
            pointer0->setArg2(parseNode(s));
        }
        return c;
    }
    else if (node->isElement("minus", MATHML_NS))
    {
        auto c = std::make_shared<Subtraction>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    }
    else if (node->isElement("times", MATHML_NS))
    {
        auto c = std::make_shared<Multiplication>();
        auto s = node->getNext();
        c->setArg1(parseNode(s));
        s = s->getNext();
        if (!s->getNext())
        {
            c->setArg2(parseNode(s));
        }
        else
        {
            auto pointer0 = c;
            while (s->getNext())
            {
                auto pointer1 = std::make_shared<Multiplication>();
                pointer1->setArg1(parseNode(s));
                pointer0->setArg2(pointer1);
                s = s->getNext();
                pointer0 = pointer1;
            }
            pointer0->setArg2(parseNode(s));
        }
        return c;
    }
    else if (node->isElement("divide", MATHML_NS))
    {
        auto c = std::make_shared<Division>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    }
    else if (node->isElement("power", MATHML_NS))
    {
        auto c = std::make_shared<Power>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    }
    else if (node->isElement("sin", MATHML_NS))
    {
        auto c = std::make_shared<Sine>();
        c->setArg(parseNode(node->getNext()));
        return c;
    }
    else if (node->isElement("cos", MATHML_NS))
    {
        auto c = std::make_shared<Cosine>();
        c->setArg(parseNode(node->getNext()));
        return c;
    }
    else if (node->isElement("abs", MATHML_NS))
    {
        auto c = std::make_shared<AbsoluteValue>();
        c->setArg(parseNode(node->getNext()));
        return c;
    }
    else if (node->isElement("ci", MATHML_NS))
    {
        auto name = node->getFirstChild()->convertToString();
        auto c = std::make_shared<libcellml::operators::Variable>(name);
        // All variables are in mAlgebraic unless they are in mStates already
        if (name != mVoi &&
                std::find(mStates.begin(), mStates.end(), name) == mStates.end())
        {
            mAlgebraic.push_back(name);
        }
        return c;
    }
    else if (node->isElement("cn", MATHML_NS))
    {
        double value;
        std::istringstream iss(node->getFirstChild()->convertToString());
        iss >> value;
        auto c = std::make_shared<Constant>(value);
        return c;
    }
    else if (node->isElement("diff", MATHML_NS))
    {
        auto name = node->getNext()->getNext()->getFirstChild()->convertToString();
        auto c = std::make_shared<libcellml::operators::Derivative>(name);
        // When we find the derivative of a variable, that variable goes in
        // mStates.
        if (std::find(mStates.begin(), mStates.end(), name) == mStates.end())
        {
            mStates.push_back(name);

            // If it was previously put in mAlgebraic, it must be removed.
            auto p = std::find(mAlgebraic.begin(), mAlgebraic.end(), name);
            if (p != mAlgebraic.end())
            {
                mAlgebraic.erase(p);
            }
        }
        return c;
    }
    else
    {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Found node of type "
                + node->getName() +
                " which is currently not supported by the Generator class.");
        mGenerator->addError(err);
        throw UnknownNode();

        return std::make_shared<Constant>(0);
    }
}

std::vector<std::shared_ptr<Representable>> Generator::GeneratorImpl::parseMathML(std::string math)
{
    std::vector<std::shared_ptr<Representable>> nodes;

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

void Generator::GeneratorImpl::findVOIHelper(XmlNodePtr node)
{
    if (node->isElement("bvar", MATHML_NS))
    {
        mVoi = node->getFirstChild()->getFirstChild()->convertToString();
        return;
    }
    else
    {
        if (node->getFirstChild())
        {
            findVOIHelper(node->getFirstChild());
        }
        else if (node->getNext())
        {
            findVOIHelper(node->getNext());
        }
    }
}

void Generator::GeneratorImpl::findVOI(std::string math)
{
    XmlDocPtr mathDoc = std::make_shared<XmlDoc>();
    mathDoc->parse(math);

    const XmlNodePtr root = mathDoc->getRootNode();
    XmlNodePtr node = root->getFirstChild();

    findVOIHelper(node);
}

const char * CodeNotGenerated::what () const throw ()
{
    return "No code was generated yet, you should call "
        "Generator::generateCode before calling this method.";
}

const char * UnknownNode::what () const throw ()
{
    return "Found node of unknown type";
}

}
