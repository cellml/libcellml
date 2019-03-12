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

#include <fstream>
#include <iostream>

TEST(Generator, simpleModel) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
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
        "\n"
        "\n"
        "    Dy = (y + 4);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
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
        "\n"
        "\n"
        "\n"
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

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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

TEST(Generator, complexModel) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
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
        "\n"
        "\n"
        "    Dy = ((((50 * y) + (y + (y + (y + std::cos(std::abs(std::sin(y))))))) - (t * (t * (t * (t * t))))) - 1);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
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
        "\n"
        "\n"
        "\n"
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

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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

TEST(Generator, complexModelToFile) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "\n"
        "\n"
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

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();

    generator.writeCodeToFile("generatedCode.cpp");
    EXPECT_EQ(1u, generator.errorCount());
    EXPECT_EQ("No code was detected. The file 'generatedCode.cpp' was not written to. Please check that Generator::generateCode() is used before Generator::writeCodeToFile().", generator.getError(0)->getDescription());
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

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_y->setInitialValue(-2);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->setMath(math);

    model->addComponent(component);

    generator.generateCode(model);
    EXPECT_EQ(1u, generator.errorCount());
    EXPECT_EQ("Found node of type 'unknown' which is currently not supported.", generator.getError(0)->getDescription());
}

TEST(Generator, divisionAndPower) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
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
        "\n"
        "\n"
        "    Dy = (std::pow(y, 2) / 4);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
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
        "\n"
        "\n"
        "\n"
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

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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

TEST(Generator, twoStates) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "    double &z = *(states + 1);\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "    z = 1;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "    double &z = *(states + 1);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "    double &Dz = *(rates + 1);\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "    Dy = (y + 4);\n"
        "    Dz = (z - y);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "    double &z = *(states + 1);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "    double &Dz = *(rates + 1);\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
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
                    "<plus/>"
                    "<ci>y</ci>"
                    "<cn cellml:units=\"dimensionless\">4</cn>"
                "</apply>"
            "</apply>"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>z</ci>"
                "</apply>"
                "<apply>"
                    "<minus/>"
                    "<ci>z</ci>"
                    "<ci>y</ci>"
                "</apply>"
            "</apply>"
        "</math>";

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_z = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_z->setName("z");
    var_y->setInitialValue(-2);
    var_z->setInitialValue(1);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    var_z->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->addVariable(var_z);
    component->setMath(math);

    model->addComponent(component);

    const std::string a = generator.generateCode(model);

    EXPECT_EQ(e, a);
}

TEST(Generator, secondOrder) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "    double &z = *(states + 1);\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "    y = -2;\n"
        "    z = 1;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "    double &z = *(states + 1);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "    double &Dz = *(rates + 1);\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "    Dy = z;\n"
        "    Dz = t;\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &y = *(states + 0);\n"
        "    double &z = *(states + 1);\n"
        "\n"
        "\n"
        "    double &Dy = *(rates + 0);\n"
        "    double &Dz = *(rates + 1);\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
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
                "<ci>z</ci>"
            "</apply>"
            "<apply>"
                "<eq/>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>z</ci>"
                "</apply>"
                "<ci>t</ci>"
            "</apply>"
        "</math>";

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_z = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
    var_z->setName("z");
    var_y->setInitialValue(-2);
    var_z->setInitialValue(1);
    var_t->setUnits("dimensionless");
    var_y->setUnits("dimensionless");
    var_z->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_y);
    component->addVariable(var_z);
    component->setMath(math);

    model->addComponent(component);

    const std::string a = generator.generateCode(model);

    EXPECT_EQ(e, a);
}

TEST(Generator, algebraicEquation) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &v = *(states + 0);\n"
        "\n"
        "\n"
        "    double &x = *(algebraic + 0);\n"
        "\n"
        "\n"
        "    v = 2;\n"
        "    x = 3;\n"
        "\n"
        "}\n"
        "void computeRates(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &v = *(states + 0);\n"
        "\n"
        "\n"
        "    double &Dv = *(rates + 0);\n"
        "\n"
        "\n"
        "    double &x = *(algebraic + 0);\n"
        "\n"
        "\n"
        "    Dv = (v + 1);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    const double t = voi;\n"
        "\n"
        "\n"
        "    double &v = *(states + 0);\n"
        "\n"
        "\n"
        "    double &Dv = *(rates + 0);\n"
        "\n"
        "\n"
        "    double &x = *(algebraic + 0);\n"
        "\n"
        "\n"
        "    x = Dv;\n"
        "\n"
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
                    "<ci>v</ci>"
                "</apply>"
                "<apply>"
                    "<plus/>"
                    "<ci>v</ci>"
                    "<cn cellml:units=\"dimensionless\">1</cn>"
                "</apply>"
            "</apply>"
            "<apply>"
                "<eq/>"
                "<ci>x</ci>"
                "<apply>"
                    "<diff/>"
                    "<bvar>"
                        "<ci>t</ci>"
                    "</bvar>"
                    "<ci>v</ci>"
                "</apply>"
            "</apply>"
        "</math>";

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_v = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_x = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_v->setName("v");
    var_x->setName("x");
    var_v->setInitialValue(2);
    var_x->setInitialValue(3);
    var_t->setUnits("dimensionless");
    var_v->setUnits("dimensionless");
    var_x->setUnits("dimensionless");
    component->addVariable(var_t);
    component->addVariable(var_v);
    component->addVariable(var_x);
    component->setMath(math);

    model->addComponent(component);

    const std::string a = generator.generateCode(model);

    EXPECT_EQ(e, a);
}

TEST(Generator, piecewise) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
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
        "\n"
        "\n"
        "    Dy = (((y + (t + 2)) * (t < +(2))) + ((-((y + (t + 2))) * ((t > 2) && !((t >= 4)))) + (0 * !((t <= 4)))));\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
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
        "\n"
        "\n"
        "\n"
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
                "<piecewise>"
                    "<piece>"
                        "<apply>"
                            "<plus/>"
                            "<ci>y</ci>"
                            "<ci>t</ci>"
                            "<cn cellml:units=\"dimensionless\">2</cn>"
                        "</apply>"
                        "<apply>"
                            "<lt/>"
                            "<ci>t</ci>"
                            "<apply>"
                                "<plus/>"
                                "<cn cellml:units=\"dimensionless\">2</cn>"
                            "</apply>"
                        "</apply>"
                    "</piece>"
                    "<piece>"
                        "<apply>"
                            "<minus/>"
                            "<apply>"
                                "<plus/>"
                                "<ci>y</ci>"
                                "<ci>t</ci>"
                                "<cn cellml:units=\"dimensionless\">2</cn>"
                            "</apply>"
                        "</apply>"
                        "<apply>"
                            "<and/>"
                            "<apply>"
                                "<gt/>"
                                "<ci>t</ci>"
                                "<cn cellml:units=\"dimensionless\">2</cn>"
                            "</apply>"
                            "<apply>"
                                "<not/>"
                                "<apply>"
                                    "<geq/>"
                                    "<ci>t</ci>"
                                    "<cn cellml:units=\"dimensionless\">4</cn>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                    "</piece>"
                    "<piece>"
                        "<cn cellml:units=\"dimensionless\">0</cn>"
                        "<apply>"
                            "<not/>"
                            "<apply>"
                                "<leq/>"
                                "<ci>t</ci>"
                                "<cn cellml:units=\"dimensionless\">4</cn>"
                            "</apply>"
                        "</apply>"
                    "</piece>"
                "</piecewise>"
            "</apply>"
        "</math>";

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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

TEST(Generator, piecewise2) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
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
        "\n"
        "\n"
        "    Dy = (((y + (t + 2)) * (t < +(2))) + (0 * ((t > 2) || (t > 3))));\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
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
        "\n"
        "\n"
        "\n"
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
                "<piecewise>"
                    "<piece>"
                        "<apply>"
                            "<plus/>"
                            "<ci>y</ci>"
                            "<ci>t</ci>"
                            "<cn cellml:units=\"dimensionless\">2</cn>"
                        "</apply>"
                        "<apply>"
                            "<lt/>"
                            "<ci>t</ci>"
                            "<apply>"
                                "<plus/>"
                                "<cn cellml:units=\"dimensionless\">2</cn>"
                            "</apply>"
                        "</apply>"
                    "</piece>"
                    "<piece>"
                        "<cn cellml:units=\"dimensionless\">0</cn>"
                        "<apply>"
                            "<or/>"
                            "<apply>"
                                "<gt/>"
                                "<ci>t</ci>"
                                "<cn cellml:units=\"dimensionless\">2</cn>"
                            "</apply>"
                            "<apply>"
                                "<gt/>"
                                "<ci>t</ci>"
                                "<cn cellml:units=\"dimensionless\">3</cn>"
                            "</apply>"
                        "</apply>"
                    "</piece>"
                "</piecewise>"
            "</apply>"
        "</math>";

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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

TEST(Generator, floorPi) {
    const std::string e =
        "void initConsts(double *constants, double *rates, double *states, double *algebraic)\n"
        "{\n"
        "    double &y = *(states + 0);\n"
        "\n"
        "\n"
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
        "\n"
        "\n"
        "    Dy = std::floor(3.1415926535897931);\n"
        "\n"
        "}\n"
        "void computeVariables(double voi, double *constants, double *rates, double *states, double *algebraic)\n"
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
        "\n"
        "\n"
        "\n"
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
                    "<floor/>"
                    "<pi/>"
                "</apply>"
            "</apply>"
        "</math>";

    libcellml::Generator generator;

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var_t = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr var_y = std::make_shared<libcellml::Variable>();

    model->setName("my_model");
    component->setName("main");
    var_t->setName("t");
    var_y->setName("y");
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
