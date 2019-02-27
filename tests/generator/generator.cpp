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

#include "gtest/gtest.h"

#include <libcellml>

using namespace libcellml;


TEST(Generator, generateSimpleModel) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "\n"
        "\n"
        "    Dy = (y + 4);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "}\n";

    const std::string math =
       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>y</ci>"
                "</apply>"
                   "<plus/>"
                   "<ci>y</ci>"
                   "<cn cellml:units=\"dimensionless\">4</cn>"
            "</apply>"
        "</math>";


    Generator generator;

    auto model = std::make_shared<Model>();
    ComponentPtr component = std::make_shared<Component>();
    VariablePtr var_t = std::make_shared<libcellml::Variable>();
    VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_t->setInitialValue(0);
    var_y->setInitialValue(-2);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->setMath(math);

    model->addComponent(component);

    const std::string a = generator.generateCode(model);

    EXPECT_EQ(e, a);
}

TEST(Generator, generateComplexModel) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "\n"
        "\n"
        "    Dy = ((((50 * y) + (y + (y + (y + std::cos(std::abs(std::sin(y))))))) - (t * (t * (t * (t * t))))) - 1);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "}\n";

    const std::string math =
       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>y</ci>"
                "</apply>"
                "<apply>"
                    "<minus/>"
                    "<apply>"
                        "<minus/>"
                        "<apply>"
                            "<plus/>"
                            "<apply>"
                                "<times/>"
                                "<cn cellml:units=\"dimensionless\">50</cn>"
                                "<ci>y</ci>"
                            "</apply>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<apply>"
                                "<cos/>"
                                "<apply>"
                                    "<abs/>"
                                    "<apply>"
                                        "<sin/>"
                                        "<ci>y</ci>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                        "<apply>"
                            "<times/>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                        "</apply>"
                    "</apply>"
                    "<cn cellml:units=\"dimensionless\">1</cn>"
                "</apply>"
            "</apply>"
        "</math>";


    Generator generator;

    auto model = std::make_shared<Model>();
    ComponentPtr component = std::make_shared<Component>();
    VariablePtr var_t = std::make_shared<libcellml::Variable>();
    VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_t->setInitialValue(0);
    var_y->setInitialValue(-2);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->setMath(math);

    model->addComponent(component);

    const std::string a = generator.generateCode(model);

    EXPECT_EQ(e, a);
}

TEST(Generator, generateComplexModelToFile) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    rates[0] = ((((50 * y) + (y + (y + (y + std::cos(std::abs(std::sin(y))))))) - (t * (t * (t * (t * t))))) - 1);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "}\n";

    const std::string math =
       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>y</ci>"
                "</apply>"
                "<apply>"
                    "<minus/>"
                    "<apply>"
                        "<minus/>"
                        "<apply>"
                            "<plus/>"
                            "<apply>"
                                "<times/>"
                                "<cn cellml:units=\"dimensionless\">50</cn>"
                                "<ci>y</ci>"
                            "</apply>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<apply>"
                                "<cos/>"
                                "<apply>"
                                    "<abs/>"
                                    "<apply>"
                                        "<sin/>"
                                        "<ci>y</ci>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                        "<apply>"
                            "<times/>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                        "</apply>"
                    "</apply>"
                    "<cn cellml:units=\"dimensionless\">1</cn>"
                "</apply>"
            "</apply>"
        "</math>";

    Generator generator;

    auto model = std::make_shared<Model>();
    ComponentPtr component = std::make_shared<Component>();
    VariablePtr var_t = std::make_shared<libcellml::Variable>();
    VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_t->setInitialValue(0);
    var_y->setInitialValue(-2);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->setMath(math);

    model->addComponent(component);

    generator.generateCode(model);
    generator.writeCodeToFile("generatedCode.cpp");

    std::ofstream output("generateComplexModelToFile.ref");
    output << e;
    output.close();

    std::ifstream in("generateComplexModelToFile.ref");
    std::string referenceCode;
    in >> referenceCode;
    in.close();

    std::ifstream input("generatedCode.cpp");
    std::string generatedCode;
    input >> generatedCode;
    input.close();

    EXPECT_EQ(referenceCode, generatedCode);
}

TEST(Generator, writeWithoutGenerating) {
    const std::string math =
       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>y</ci>"
                "</apply>"
                "<apply>"
                    "<minus/>"
                    "<apply>"
                        "<minus/>"
                        "<apply>"
                            "<plus/>"
                            "<apply>"
                                "<times/>"
                                "<cn cellml:units=\"dimensionless\">50</cn>"
                                "<ci>y</ci>"
                            "</apply>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<apply>"
                                "<cos/>"
                                "<apply>"
                                    "<abs/>"
                                    "<apply>"
                                        "<sin/>"
                                        "<ci>y</ci>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                        "<apply>"
                            "<times/>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                        "</apply>"
                    "</apply>"
                    "<cn cellml:units=\"dimensionless\">1</cn>"
                "</apply>"
            "</apply>"
        "</math>";

    Generator generator;

    auto model = std::make_shared<Model>();

    try
    {
        generator.writeCodeToFile("generatedCode.cpp");
        FAIL() << "Expected CodeNotGenerated exception";
    }
    catch (const CodeNotGenerated &e)
    {
        std::cout << "Caught error: " << e.what() << std::endl;
    }
}

TEST(Generator, unknownNode) {
    const std::string math =
       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>y</ci>"
                "</apply>"
                "<apply>"
                    "<minus/>"
                    "<apply>"
                        "<minus/>"
                        "<apply>"
                            "<plus/>"
                            "<apply>"
                                "<times/>"
                                "<cn cellml:units=\"dimensionless\">50</cn>"
                                "<ci>y</ci>"
                            "</apply>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<ci>y</ci>"
                            "<apply>"
                                "<cos/>"
                                "<apply>"
                                    "<abs/>"
                                    "<apply>"
                                        "<unknown/>"
                                        "<ci>y</ci>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                        "<apply>"
                            "<times/>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                            "<ci>t</ci>"
                        "</apply>"
                    "</apply>"
                    "<cn cellml:units=\"dimensionless\">1</cn>"
                "</apply>"
            "</apply>"
        "</math>";

    Generator generator;

    auto model = std::make_shared<Model>();
    ComponentPtr component = std::make_shared<Component>();
    VariablePtr var_t = std::make_shared<libcellml::Variable>();
    VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_t->setInitialValue(0);
    var_y->setInitialValue(-2);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->setMath(math);

    model->addComponent(component);

    try
    {
        generator.generateCode(model);
        FAIL() << "Expected UnknownNode";
    }
    catch (const UnknownNode &e)
    {
        std::cout << "Caught error: " << e.what() << std::endl;
    }
}

TEST(Generator, divisionAndPower) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "\n"
        "\n"
        "    Dy = (std::pow(y, 2) / 4);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "}\n";

    const std::string math =
       "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>y</ci>"
                "</apply>"
                   "<divide/>"
                   "<apply>"
                        "<power/>"
                        "<ci>y</ci>"
                        "<cn cellml:units=\"dimensionless\">2</cn>"
                    "</apply>"
                   "<cn cellml:units=\"dimensionless\">4</cn>"
            "</apply>"
        "</math>";


    Generator generator;

    auto model = std::make_shared<Model>();
    ComponentPtr component = std::make_shared<Component>();
    VariablePtr var_t = std::make_shared<libcellml::Variable>();
    VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_t->setInitialValue(0);
    var_y->setInitialValue(-2);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->setMath(math);

    model->addComponent(component);

    const std::string a = generator.generateCode(model);

    EXPECT_EQ(e, a);
}
