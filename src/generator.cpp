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

class Representable
{
public:
    virtual std::string repr() = 0;
};

class BinaryOperator : public Representable
{
public:
    BinaryOperator() :
        arg1(std::shared_ptr<Representable>()),
        arg2(std::shared_ptr<Representable>())
    {}

    BinaryOperator(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2) :
        arg1(arg1),
        arg2(arg2)
    {}

    std::shared_ptr<Representable> getArg1() const {return arg1;}
    void setArg1(const std::shared_ptr<Representable> a1) {arg1 = a1;}
    std::shared_ptr<Representable> getArg2() const {return arg2;}
    void setArg2(const std::shared_ptr<Representable> a2) {arg2 = a2;}

protected:
    std::shared_ptr<Representable> arg1;
    std::shared_ptr<Representable> arg2;
};

class ArithmeticOperator : public BinaryOperator
{
public:
    ArithmeticOperator(std::string opr) :
        BinaryOperator(),
        operatorRepresentation(opr)
    {}

    ArithmeticOperator(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2,
            std::string opr) :
        BinaryOperator(arg1,arg2),
        operatorRepresentation(opr)
    {}

    virtual std::string repr() override
    {
        std::ostringstream oss;
        oss << "(" << arg1->repr();
        oss << " " << operatorRepresentation << " ";
        oss << arg2->repr() << ")";
        return oss.str();
    }

private:
    std::string operatorRepresentation;
};

class Addition : public ArithmeticOperator
{
public:
    Addition() :
        ArithmeticOperator(std::string("+"))
    {}

    Addition(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2) :
        ArithmeticOperator(arg1,arg2,std::string("+"))
    {}
};

class Subtraction : public ArithmeticOperator
{
public:
    Subtraction() :
        ArithmeticOperator(std::string("-"))
    {}

    Subtraction(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2) :
        ArithmeticOperator(arg1,arg2,std::string("-"))
    {}
};

class Multiplication : public ArithmeticOperator
{
public:
    Multiplication() :
        ArithmeticOperator(std::string("*"))
    {}

    Multiplication(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2) :
        ArithmeticOperator(arg1,arg2,std::string("*"))
    {}
};

class Division : public ArithmeticOperator
{
public:
    Division() :
        ArithmeticOperator(std::string("/"))
    {}

    Division(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2) :
        ArithmeticOperator(arg1,arg2,std::string("/"))
    {}
};

class Power : public BinaryOperator
{
public:
    Power(std::shared_ptr<Representable> b,
            std::shared_ptr<Representable> e) :
        BinaryOperator(b,e)
    {}

    virtual std::string repr() override
    {
        std::ostringstream oss;
        oss << "std::pow(" << arg1->repr() << ", " << arg2->repr() << ")";
        return oss.str();
    }
};

class UnaryOperator : public Representable
{
public:
    UnaryOperator() :
        arg(std::shared_ptr<Representable>())
    {}

    UnaryOperator(std::shared_ptr<Representable> arg) :
        arg(arg)
    {}

    std::shared_ptr<Representable> getArg() const {return arg;}
    void setArg(const std::shared_ptr<Representable> a) {arg = a;}

protected:
    std::shared_ptr<Representable> arg;
};

class STDOperator : public UnaryOperator
{
public:
    STDOperator(std::string fun) :
        UnaryOperator(),
        fun(fun)
    {}

    STDOperator(std::shared_ptr<Representable> arg,
            std::string fun) :
        UnaryOperator(arg),
        fun(fun)
    {}

    virtual std::string repr() override
    {
        std::ostringstream oss;
        oss << "std::" << fun << "(" << arg->repr() << ")";
        return oss.str();
    }

private:
    std::string fun;
};

class AbsoluteValue : public STDOperator
{
public:
    AbsoluteValue() :
        STDOperator(std::string("abs"))
    {}

    AbsoluteValue(std::shared_ptr<Representable> arg) :
        STDOperator(arg,std::string("abs"))
    {}
};

class Sine : public STDOperator
{
public:
    Sine() :
        STDOperator(std::string("sin"))
    {}

    Sine(std::shared_ptr<Representable> arg) :
        STDOperator(arg,std::string("sin"))
    {}
};

class Cosine : public STDOperator
{
public:
    Cosine() :
        STDOperator(std::string("cos"))
    {}

    Cosine(std::shared_ptr<Representable> arg) :
        STDOperator(arg,std::string("cos"))
    {}
};

class Variable : public Representable
{
public:
    Variable() = default;
    Variable(std::string name) : name(name) {}

    virtual std::string repr() override
    {
        return name;
    }

private:
    std::string name;
};

class Constant : public Representable
{
public:
    Constant() = default;
    Constant (double val) : value(val) {}

    virtual std::string repr() override
    {
        std::ostringstream oss;
        oss << std::setprecision(16) << value;
        return oss.str();
    }

private:
    double value;
};

namespace libcellml{

std::string Generator::generateStateAliases()
{
    std::string s;
    std::ostringstream oss(s);
    for (size_t i = 0; i < states.size(); i++)
    {
        oss << "    double& " << states[i] << " = *(states + " << i
            << ");" << std::endl;
    }
    oss << std::endl;
    return oss.str();
}

std::string Generator::generateVoiAlias()
{
    std::string s;
    std::ostringstream oss(s);
    oss << "    const double " << voi << " = voi" << ";" << std::endl;
    oss << std::endl;
    return oss.str();
}

std::string Generator::generateInitConsts()
{
    std::string s;
    std::ostringstream oss(s);
    oss << "void initConsts(double* constants, "
                           "double* rates, "
                           "double* states)" << std::endl
        << "{" << std::endl;
    oss << generateStateAliases() << std::endl;
    for (auto s : initialValues)
    {
        oss << "    " << s.first << " = "
            << std::setprecision(16) << s.second << ";" << std::endl;
    }
    oss << std::endl << "}";
    return oss.str();
}

std::string Generator::generateComputeRates(std::shared_ptr<Representable> r)
{
    std::string s;
    std::ostringstream oss(s);
    oss << "void computeRates(double voi, "
                             "double* constants, "
                             "double* rates, "
                             "double* states, "
                             "double* algebraic)" << std::endl
        << "{" << std::endl;
    oss << generateVoiAlias() << std::endl;
    oss << generateStateAliases() << std::endl;

    oss << "    rates[0] = "
        << r->repr() << ";" << std::endl;

    oss << std::endl << "}";
    return oss.str();
}

std::string Generator::generateComputeVariables()
{
    std::string s;
    std::ostringstream oss(s);
    oss << "void computeVariables(double voi, "
                                 "double* constants, "
                                 "double* rates, "
                                 "double* states, "
                                 "double* algebraic)" << std::endl
        << "{" << std::endl << "}";
    return oss.str();
}

void Generator::findInitialValues(ComponentPtr c)
{
    for (std::size_t i = 0; i < c->variableCount(); i++)
    {
        auto v = c->getVariable(i);
        if (v->getName() != voi)
        {
            initialValues[v->getName()] = std::stod(v->getInitialValue());
        }
    }
}

std::string Generator::generateCode(ModelPtr m)
{
    ComponentPtr c = m->getComponent(0);

    findVOI(c->getMath());
    findInitialValues(c);
    auto r = parseMathML(c->getMath());
    
    std::string generatedCode;
    std::ostringstream oss(generatedCode);
    oss << generateInitConsts() << std::endl;
    oss << generateComputeRates(r) << std::endl;
    oss << generateComputeVariables() << std::endl;

    code = oss.str();
    return code;
}

void Generator::writeCodeToFile(std::string filename)
{
    if (code == "")
    {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("No code was generated yet, you should call "
                "Generator::generateCode before calling this method.");
        addError(err);
        throw CodeNotGenerated();
    }

    std::ofstream output(filename);
    output << code;
    output.close();
}

std::shared_ptr<Representable> Generator::parseNode(XmlNodePtr node)
{
    if (node->isType("apply"))
    {
        return parseNode(node->getFirstChild());
    }
    else if (node->isType("plus"))
    {
        auto c = std::make_shared<Addition>();
        auto s = node->getNext();
        c->setArg1(parseNode(s));
        s = s->getNext();
        if (not s->getNext())
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
    else if (node->isType("minus"))
    {
        auto c = std::make_shared<Subtraction>();
        auto s1 = node->getNext();
        c->setArg1(parseNode(s1));
        c->setArg2(parseNode(s1->getNext()));
        return c;
    }
    else if (node->isType("times"))
    {
        auto c = std::make_shared<Multiplication>();
        auto s = node->getNext();
        c->setArg1(parseNode(s));
        s = s->getNext();
        if (not s->getNext())
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
    else if (node->isType("sin"))
    {
        auto c = std::make_shared<Sine>();
        c->setArg(parseNode(node->getNext()));
        return c;
    }
    else if (node->isType("cos"))
    {
        auto c = std::make_shared<Cosine>();
        c->setArg(parseNode(node->getNext()));
        return c;
    }
    else if (node->isType("abs"))
    {
        auto c = std::make_shared<AbsoluteValue>();
        c->setArg(parseNode(node->getNext()));
        return c;
    }
    else if (node->isType("ci"))
    {
        auto name = node->getFirstChild()->convertToString();
        auto c = std::make_shared<::Variable>(name);
        if (name != voi and
                std::find(states.begin(), states.end(), name) == states.end())
        {
            states.push_back(name);
        }
        return c;
    }
    else if (node->isType("cn"))
    {
        double value;
        std::istringstream iss(node->getFirstChild()->convertToString());
        iss >> value;
        auto c = std::make_shared<Constant>(value);
        return c;
    }
    else
    {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Found node of type "
                + node->getType() +
                " which is currently not supported by the Generator class.");
        addError(err);
        throw UnknownNode();

        return std::make_shared<Constant>(0);
    }
}

std::shared_ptr<Representable> Generator::parseMathML(std::string math)
{
    XmlDocPtr mathDoc = std::make_shared<XmlDoc>();
    mathDoc->parse(math);

    const XmlNodePtr root = mathDoc->getRootNode();

    XmlNodePtr childNode = root->getFirstChild();
    childNode = childNode->getFirstChild();
    childNode = childNode->getNext();
    childNode = childNode->getNext();

    return parseNode(childNode);
}

void Generator::findVOIHelper(XmlNodePtr node)
{
    if (node->isType("bvar"))
    {
        voi = node->getFirstChild()->getFirstChild()->convertToString();
        return;
    }
    else
    {
        if (node->getFirstChild())
        {
            findVOIHelper(node->getFirstChild());
        }
        if (node->getNext())
        {
            findVOIHelper(node->getNext());
        }
    }
}

void Generator::findVOI(std::string math)
{
    XmlDocPtr mathDoc = std::make_shared<XmlDoc>();
    mathDoc->parse(math);

    const XmlNodePtr root = mathDoc->getRootNode();
    XmlNodePtr node = root->getFirstChild();

    findVOIHelper(node);
}

}

//using namespace libcellml;
//
//int main()
//{
//    std::string math =
//       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
//            "<apply>"
//                "<eq/>"
//                "<apply>"
//                    "<diff/>"
//                    "<bvar>"
//                        "<ci>t</ci>"
//                    "</bvar>"
//                    "<ci>y</ci>"
//                "</apply>"
//                   "<plus/>"
//                   "<ci>y</ci>"
//                   "<cn cellml:units=\"dimensionless\">4</cn>"
//            "</apply>"
//        "</math>";
//
//    const std::string math2 =
//       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
//            "<apply>"
//                "<eq/>"
//                "<apply>"
//                    "<diff/>"
//                    "<bvar>"
//                        "<ci>t</ci>"
//                    "</bvar>"
//                    "<ci>z</ci>"
//                "</apply>"
//                "<apply>"
//                    "<minus/>"
//                    "<apply>"
//                        "<minus/>"
//                        "<apply>"
//                            "<plus/>"
//                            "<apply>"
//                                "<times/>"
//                                "<cn cellml:units=\"dimensionless\">50</cn>"
//                                "<ci>y</ci>"
//                            "</apply>"
//                            "<ci>y</ci>"
//                            "<ci>y</ci>"
//                            "<ci>y</ci>"
//                            "<apply>"
//                                "<cos/>"
//                                "<apply>"
//                                    "<abs/>"
//                                    "<apply>"
//                                        "<sin/>"
//                                        "<ci>y</ci>"
//                                    "</apply>"
//                                "</apply>"
//                            "</apply>"
//                        "</apply>"
//                        "<apply>"
//                            "<times/>"
//                            "<ci>t</ci>"
//                            "<ci>t</ci>"
//                            "<ci>t</ci>"
//                            "<ci>t</ci>"
//                            "<ci>t</ci>"
//                        "</apply>"
//                    "</apply>"
//                    "<cn cellml:units=\"dimensionless\">1</cn>"
//                "</apply>"
//            "</apply>"
//        "</math>";
//
//
//    Generator generator;
//
//    auto model = std::make_shared<Model>();
//    ComponentPtr component = std::make_shared<Component>();
//    VariablePtr var_t = std::make_shared<libcellml::Variable>();
//    VariablePtr var_y = std::make_shared<libcellml::Variable>();
//
//    model->setName("my_model");
//    component->setName("main");
//    var_t->setName("t");
//    var_y->setName("y");
//    var_t->setInitialValue(0);
//    var_y->setInitialValue(-2);
//    var_t->setUnits("dimensionless");
//    var_y->setUnits("dimensionless");
//    component->addVariable(var_t);
//    component->addVariable(var_y);
//    component->setMath(math);
//
//    model->addComponent(component);
//
//
//    std::cout << generator.parseModel(model);
//
//
//    return 0;
//}
//
//
