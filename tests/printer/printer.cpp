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

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(Printer, printNullptrModel)
{
    const std::string e;

    libcellml::PrinterPtr p = libcellml::Printer::create();

    const std::string a = p->printModel(nullptr);

    EXPECT_EQ(e, a);
}

TEST(Printer, printEmptyModel)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>\n";
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::PrinterPtr p = libcellml::Printer::create();

    const std::string a = p->printModel(m);

    EXPECT_EQ(e, a);
}

TEST(Printer, printEmptyUnits)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units/>\n"
        "</model>\n";
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::UnitsPtr u = libcellml::Units::create();

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Printer, printEmptyVariable)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <variable/>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::VariablePtr v = libcellml::Variable::create();
    c->addVariable(v);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Printer, printEmptyComponent)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component/>\n"
        "</model>\n";

    libcellml::ModelPtr m = createModelWithComponent();

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Printer, printEmptyReset)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = libcellml::Reset::create();

    c->addReset(r);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Printer, printReset)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model\">\n"
        "  <component name=\"component\">\n"
        "    <variable name=\"variable1\"/>\n"
        "    <variable name=\"variable2\"/>\n"
        "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ModelPtr m = createModelWithComponent("model", "component");
    libcellml::ComponentPtr c = m->component(0);
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable1");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variable2");
    libcellml::ResetPtr r = libcellml::Reset::create();

    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(1);
    r->setResetValue(EMPTY_MATH);
    r->setTestValue(EMPTY_MATH);

    c->addVariable(v1);
    c->addVariable(v2);
    c->addReset(r);

    libcellml::PrinterPtr printer = libcellml::Printer::create();

    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Printer, printEncapsulation)
{
    const std::string e_parent =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component/>\n"
        "  <component/>\n"
        "  <encapsulation>\n"
        "    <component_ref>\n"
        "      <component_ref/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr parent = libcellml::Component::create();
    libcellml::ComponentPtr child = libcellml::Component::create();
    parent->addComponent(child);

    model->addComponent(parent);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a_parent = printer->printModel(model);
    EXPECT_EQ(e_parent, a_parent);
}

TEST(Printer, printEncapsulationWithNames)
{
    const std::string e_parent =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child_component\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child_component\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr parent = libcellml::Component::create();
    parent->setName("parent_component");
    libcellml::ComponentPtr child = libcellml::Component::create();
    child->setName("child_component");
    parent->addComponent(child);

    model->addComponent(parent);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a_parent = printer->printModel(model);
    EXPECT_EQ(e_parent, a_parent);
}

TEST(Printer, printModelWithImports)
{
    const std::string e_model =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"sin_approximations_import\" id=\"sin_approximations_import\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"sin.xml\">\n"
        "    <component component_ref=\"sin\" name=\"actual_sin\"/>\n"
        "  </import>\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"deriv_approx_sin.xml\">\n"
        "    <component component_ref=\"sin\" name=\"deriv_approx_sin\"/>\n"
        "  </import>\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"parabolic_approx_sin.xml\">\n"
        "    <component component_ref=\"sin\" name=\"parabolic_approx_sin\"/>\n"
        "  </import>\n"
        "  <component name=\"main\" id=\"main\">\n"
        "    <variable name=\"x\" units=\"dimensionless\" interface=\"public_and_private\" id=\"x\"/>\n"
        "    <variable name=\"sin1\" units=\"dimensionless\" interface=\"public_and_private\" id=\"sin\"/>\n"
        "    <variable name=\"sin2\" units=\"dimensionless\" interface=\"public_and_private\" id=\"deriv_approx\"/>\n"
        "    <variable name=\"deriv_approx_initial_value\" units=\"dimensionless\" initial_value=\"0\" interface=\"public_and_private\" id=\"deriv_approx_initial_value\"/>\n"
        "    <variable name=\"sin3\" units=\"dimensionless\" interface=\"public_and_private\" id=\"parabolic_approx\"/>\n"
        "    <variable name=\"C\" units=\"dimensionless\" initial_value=\"0.75\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"main\" component_2=\"actual_sin\">\n"
        "    <map_variables variable_1=\"x\" variable_2=\"x\"/>\n"
        "    <map_variables variable_1=\"sin1\" variable_2=\"sin\"/>\n"
        "  </connection>\n"
        "  <connection component_1=\"main\" component_2=\"deriv_approx_sin\">\n"
        "    <map_variables variable_1=\"x\" variable_2=\"x\"/>\n"
        "    <map_variables variable_1=\"sin2\" variable_2=\"sin\"/>\n"
        "    <map_variables variable_1=\"deriv_approx_initial_value\" variable_2=\"sin_initial_value\"/>\n"
        "  </connection>\n"
        "  <connection component_1=\"main\" component_2=\"parabolic_approx_sin\">\n"
        "    <map_variables variable_1=\"x\" variable_2=\"x\"/>\n"
        "    <map_variables variable_1=\"sin3\" variable_2=\"sin\"/>\n"
        "    <map_variables variable_1=\"C\" variable_2=\"C\"/>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main\">\n"
        "      <component_ref component=\"actual_sin\"/>\n"
        "      <component_ref component=\"deriv_approx_sin\"/>\n"
        "      <component_ref component=\"parabolic_approx_sin\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("sine_approximations_import.xml"));

    EXPECT_EQ(size_t(0), p->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a_model = printer->printModel(model);
    EXPECT_EQ(e_model, a_model);
}

TEST(Printer, printModelWithTabs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("printer/tabulated_model.cellml"));
    libcellml::PrinterPtr printer = libcellml::Printer::create();

    EXPECT_EQ(fileContents("printer/spaced_model.cellml"), printer->printModel(model));
}

TEST(Printer, printModelWithStandardUnitsAdded)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"my_model\"/>\n";

    libcellml::ModelPtr model = libcellml::Model::create("my_model");
    libcellml::UnitsPtr u = libcellml::Units::create("second");

    model->addUnits(u);

    EXPECT_EQ(size_t(1), model->unitsCount());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    EXPECT_EQ(e, printer->printModel(model));
}

TEST(Printer, printModelWithAutomaticIdsNoMaths)
{
    const std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\">\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
                           "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" />\n"
                           "  </import>\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
                           "    <units units_ref=\"a_units_in_that_model\" name=\"units1\"/>\n"
                           "  </import>\n"
                           "  <units name=\"units2\">\n"
                           "    <unit units=\"second\"/>\n"
                           "  </units>\n"
                           "  <units name=\"units3\"/>\n"
                           "  <units name=\"blob\"/>\n"
                           "  <component name=\"component2\">\n"
                           "    <variable name=\"variable1\" units=\"units2\" interface=\"private\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\"/>\n"
                           "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\">\n"
                           "      <test_value>\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">3.4</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </test_value>\n"
                           "      <reset_value>\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">9.0</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </reset_value>\n"
                           "    </reset>\n"
                           "  </component>\n"
                           "  <component name=\"component3\">\n"
                           "    <variable name=\"variable4\" units=\"units2\" interface=\"public\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" interface=\"public\"/>\n"
                           "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "      <apply>\n"
                           "        <eq/>\n"
                           "        <ci>variable4</ci>\n"
                           "        <cn cellml:units=\"units2\">9.0</cn>\n"
                           "      </apply>\n"
                           "    </math>\n"
                           "  </component>\n"
                           "  <connection component_1=\"component2\" component_2=\"component3\">\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\"/>\n"
                           "  </connection>\n"
                           "  <encapsulation>\n"
                           "    <component_ref component=\"component2\">\n"
                           "      <component_ref component=\"component3\"/>\n"
                           "    </component_ref>\n"
                           "  </encapsulation>\n"
                           "</model>\n";
    const std::string expectedOutString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                          "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"b4da55\">\n"
                                          "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"b4da56\">\n"
                                          "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"b4da57\"/>\n"
                                          "  </import>\n"
                                          "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"b4da58\">\n"
                                          "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"b4da59\"/>\n"
                                          "  </import>\n"
                                          "  <units name=\"units2\" id=\"b4da5a\">\n"
                                          "    <unit units=\"second\" id=\"b4da5b\"/>\n"
                                          "  </units>\n"
                                          "  <units name=\"units3\" id=\"b4da5c\"/>\n"
                                          "  <units name=\"blob\" id=\"b4da5d\"/>\n"
                                          "  <component name=\"component2\" id=\"b4da5e\">\n"
                                          "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"b4da5f\"/>\n"
                                          "    <variable name=\"variable2\" units=\"units2\" id=\"b4da60\"/>\n"
                                          "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"b4da61\">\n"
                                          "      <test_value id=\"b4da62\">\n"
                                          "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                          "          <apply>\n"
                                          "            <eq/>\n"
                                          "            <ci>variable1</ci>\n"
                                          "            <cn cellml:units=\"units2\">3.4</cn>\n"
                                          "          </apply>\n"
                                          "        </math>\n"
                                          "      </test_value>\n"
                                          "      <reset_value id=\"b4da63\">\n"
                                          "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                          "          <apply>\n"
                                          "            <eq/>\n"
                                          "            <ci>variable1</ci>\n"
                                          "            <cn cellml:units=\"units2\">9.0</cn>\n"
                                          "          </apply>\n"
                                          "        </math>\n"
                                          "      </reset_value>\n"
                                          "    </reset>\n"
                                          "  </component>\n"
                                          "  <component name=\"component3\" id=\"b4da64\">\n"
                                          "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"b4da65\"/>\n"
                                          "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"b4da66\"/>\n"
                                          "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                          "      <apply>\n"
                                          "        <eq/>\n"
                                          "        <ci>variable4</ci>\n"
                                          "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                          "      </apply>\n"
                                          "    </math>\n"
                                          "  </component>\n"
                                          "  <connection component_1=\"component2\" component_2=\"component3\" id=\"b4da6b\">\n"
                                          "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"b4da69\"/>\n"
                                          "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\" id=\"b4da6a\"/>\n"
                                          "  </connection>\n"
                                          "  <encapsulation id=\"b4da6c\">\n"
                                          "    <component_ref component=\"component2\" id=\"b4da67\">\n"
                                          "      <component_ref component=\"component3\" id=\"b4da68\"/>\n"
                                          "    </component_ref>\n"
                                          "  </encapsulation>\n"
                                          "</model>\n";

    auto parser = libcellml::Parser::create();
    auto printer = libcellml::Printer::create();

    auto model = parser->parseModel(in);
    bool includeAutomaticIds = true;
    auto out = printer->printModel(model, includeAutomaticIds);
    EXPECT_EQ(expectedOutString, out);
}

TEST(Printer, printModelWithAutomaticIdsSomeExistingNoMaths)
{
    const std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model\">\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_2\">\n"
                           "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_2\"/>\n"
                           "  </import>\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"i_was_skipped_before\">\n"
                           "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"b4d455\"/>\n"
                           "  </import>\n"
                           "  <units name=\"units2\">\n"
                           "    <unit units=\"second\" id=\"myUnitId\"/>\n"
                           "  </units>\n"
                           "  <units name=\"units3\"/>\n"
                           "  <units name=\"blob\" id=\"myUnitsId\"/>\n"
                           "  <component name=\"component2\">\n"
                           "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"variable_1\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" id=\"variable_2\"/>\n"
                           "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"reset_1\">\n"
                           "      <test_value>\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">3.4</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </test_value>\n"
                           "      <reset_value id=\"myResetValueId\">\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">9.0</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </reset_value>\n"
                           "    </reset>\n"
                           "  </component>\n"
                           "  <component name=\"component3\" id=\"component_1\">\n"
                           "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"myVariableId\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" interface=\"public\"/>\n"
                           "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "      <apply>\n"
                           "        <eq/>\n"
                           "        <ci>variable4</ci>\n"
                           "        <cn cellml:units=\"units2\">9.0</cn>\n"
                           "      </apply>\n"
                           "    </math>\n"
                           "  </component>\n"
                           "  <connection component_1=\"component2\" component_2=\"component3\" id=\"connection_0\">\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"map_variables_3\"/>\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\"/>\n"
                           "  </connection>\n"
                           "  <encapsulation id=\"encapsulation_1\">\n"
                           "    <component_ref component=\"component2\" id=\"component_ref_2\">\n"
                           "      <component_ref component=\"component3\"/>\n"
                           "    </component_ref>\n"
                           "  </encapsulation>\n"
                           "</model>\n";
    const std::string expectedOutString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                          "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model\">\n"
                                          "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_2\">\n"
                                          "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_2\"/>\n"
                                          "  </import>\n"
                                          "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"i_was_skipped_before\">\n"
                                          "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"b4d455\"/>\n"
                                          "  </import>\n"
                                          "  <units name=\"units2\" id=\"b4da55\">\n"
                                          "    <unit units=\"second\" id=\"myUnitId\"/>\n"
                                          "  </units>\n"
                                          "  <units name=\"units3\" id=\"b4da56\"/>\n"
                                          "  <units name=\"blob\" id=\"myUnitsId\"/>\n"
                                          "  <component name=\"component2\" id=\"b4da57\">\n"
                                          "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"variable_1\"/>\n"
                                          "    <variable name=\"variable2\" units=\"units2\" id=\"variable_2\"/>\n"
                                          "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"reset_1\">\n"
                                          "      <test_value id=\"b4da58\">\n"
                                          "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                          "          <apply>\n"
                                          "            <eq/>\n"
                                          "            <ci>variable1</ci>\n"
                                          "            <cn cellml:units=\"units2\">3.4</cn>\n"
                                          "          </apply>\n"
                                          "        </math>\n"
                                          "      </test_value>\n"
                                          "      <reset_value id=\"myResetValueId\">\n"
                                          "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                          "          <apply>\n"
                                          "            <eq/>\n"
                                          "            <ci>variable1</ci>\n"
                                          "            <cn cellml:units=\"units2\">9.0</cn>\n"
                                          "          </apply>\n"
                                          "        </math>\n"
                                          "      </reset_value>\n"
                                          "    </reset>\n"
                                          "  </component>\n"
                                          "  <component name=\"component3\" id=\"component_1\">\n"
                                          "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"myVariableId\"/>\n"
                                          "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"b4da59\"/>\n"
                                          "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                          "      <apply>\n"
                                          "        <eq/>\n"
                                          "        <ci>variable4</ci>\n"
                                          "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                          "      </apply>\n"
                                          "    </math>\n"
                                          "  </component>\n"
                                          "  <connection component_1=\"component2\" component_2=\"component3\" id=\"connection_0\">\n"
                                          "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"map_variables_3\"/>\n"
                                          "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\" id=\"b4da5b\"/>\n"
                                          "  </connection>\n"
                                          "  <encapsulation id=\"encapsulation_1\">\n"
                                          "    <component_ref component=\"component2\" id=\"component_ref_2\">\n"
                                          "      <component_ref component=\"component3\" id=\"b4da5a\"/>\n"
                                          "    </component_ref>\n"
                                          "  </encapsulation>\n"
                                          "</model>\n";

    auto parser = libcellml::Parser::create();
    auto printer = libcellml::Printer::create();

    auto model = parser->parseModel(in);
    bool includeAutomaticIds = true;
    auto out = printer->printModel(model, includeAutomaticIds);
    EXPECT_EQ(expectedOutString, out);
}

TEST(Printer, noChangeToAutoIds)
{
    // This test is for coverage.  All entities have ids already, no change to the printed model.
    const std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"b4da55\">\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"b4da56\">\n"
                           "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"b4da57\"/>\n"
                           "  </import>\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"hello\">\n"
                           "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"b4da59\"/>\n"
                           "  </import>\n"
                           "  <units name=\"units2\" id=\"b4da5a\">\n"
                           "    <unit units=\"second\" id=\"b4da5b\"/>\n"
                           "  </units>\n"
                           "  <units name=\"units3\" id=\"b4da5c\"/>\n"
                           "  <units name=\"blob\" id=\"b4da5d\"/>\n"
                           "  <component name=\"component2\" id=\"b4da5e\">\n"
                           "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"b4da5f\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" id=\"b4da60\"/>\n"
                           "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"b4da61\">\n"
                           "      <test_value id=\"b4da62\">\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">3.4</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </test_value>\n"
                           "      <reset_value id=\"b4da63\">\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">9.0</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </reset_value>\n"
                           "    </reset>\n"
                           "  </component>\n"
                           "  <component name=\"component3\" id=\"b4da64\">\n"
                           "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"b4da65\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"b4da66\"/>\n"
                           "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "      <apply>\n"
                           "        <eq/>\n"
                           "        <ci>variable4</ci>\n"
                           "        <cn cellml:units=\"units2\">9.0</cn>\n"
                           "      </apply>\n"
                           "    </math>\n"
                           "  </component>\n"
                           "  <connection component_1=\"component2\" component_2=\"component3\" id=\"b4da6b\">\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"b4da69\"/>\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\" id=\"b4da6a\"/>\n"
                           "  </connection>\n"
                           "  <encapsulation id=\"b4da6c\">\n"
                           "    <component_ref component=\"component2\" id=\"b4da67\">\n"
                           "      <component_ref component=\"component3\" id=\"b4da68\"/>\n"
                           "    </component_ref>\n"
                           "  </encapsulation>\n"
                           "</model>\n";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto printer = libcellml::Printer::create();
    EXPECT_EQ(in, printer->printModel(model));
}

TEST(Printer, printMultipleChildrenOfImports)
{
    std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
                     "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
                     "    <component component_ref=\"another_component_in_that_model\" name=\"component2\" id=\"component_2\"/>\n"
                     "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
                     "    <units units_ref=\"another_units_in_that_model\" name=\"units2\" id=\"units_2\"/>\n"
                     "    <units units_ref=\"yet_another_units_in_that_model\" name=\"units3\" id=\"units_3\"/>\n"
                     "  </import>\n"
                     "</model>\n";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto printer = libcellml::Printer::create();
    EXPECT_EQ(in, printer->printModel(model));
}

TEST(Printer, printMultipleChildrenOfImportsMixedOrder)
{
    std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
                     "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
                     "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
                     "    <units units_ref=\"another_units_in_that_model\" name=\"units2\" id=\"units_2\"/>\n"
                     "    <component component_ref=\"another_component_in_that_model\" name=\"component2\" id=\"component_2\"/>\n"
                     "    <units units_ref=\"yet_another_units_in_that_model\" name=\"units3\" id=\"units_3\"/>\n"
                     "  </import>\n"
                     "</model>\n";

    std::string out = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                      "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
                      "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
                      "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
                      "    <component component_ref=\"another_component_in_that_model\" name=\"component2\" id=\"component_2\"/>\n"
                      "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
                      "    <units units_ref=\"another_units_in_that_model\" name=\"units2\" id=\"units_2\"/>\n"
                      "    <units units_ref=\"yet_another_units_in_that_model\" name=\"units3\" id=\"units_3\"/>\n"
                      "  </import>\n"
                      "</model>\n";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto printer = libcellml::Printer::create();
    EXPECT_EQ(out, printer->printModel(model));
}

TEST(Printer, noChangeToManualIds)
{
    // This test is for coverage.  All entities have ids already, no change to the printed model.
    const std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"id_4da55\">\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"id_4da56\">\n"
                           "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"id_4da57\"/>\n"
                           "  </import>\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"hello\">\n"
                           "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"id_4da59\"/>\n"
                           "  </import>\n"
                           "  <units name=\"units2\" id=\"id_4da5a\">\n"
                           "    <unit units=\"second\" id=\"id_4da5b\"/>\n"
                           "  </units>\n"
                           "  <units name=\"units3\" id=\"id_4da5c\"/>\n"
                           "  <units name=\"blob\" id=\"id_4da5d\"/>\n"
                           "  <component name=\"component2\" id=\"id_4da5e\">\n"
                           "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"id_4da5f\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" id=\"id_4da60\"/>\n"
                           "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"id_4da61\">\n"
                           "      <test_value id=\"id_4da62\">\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">3.4</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </test_value>\n"
                           "      <reset_value id=\"id_4da63\">\n"
                           "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "          <apply>\n"
                           "            <eq/>\n"
                           "            <ci>variable1</ci>\n"
                           "            <cn cellml:units=\"units2\">9.0</cn>\n"
                           "          </apply>\n"
                           "        </math>\n"
                           "      </reset_value>\n"
                           "    </reset>\n"
                           "  </component>\n"
                           "  <component name=\"component3\" id=\"id_4da64\">\n"
                           "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"id_4da65\"/>\n"
                           "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"id_4da66\"/>\n"
                           "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                           "      <apply>\n"
                           "        <eq/>\n"
                           "        <ci>variable4</ci>\n"
                           "        <cn cellml:units=\"units2\">9.0</cn>\n"
                           "      </apply>\n"
                           "    </math>\n"
                           "  </component>\n"
                           "  <connection component_1=\"component2\" component_2=\"component3\" id=\"id_4da6b\">\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"id_4da69\"/>\n"
                           "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\" id=\"id_4da6a\"/>\n"
                           "  </connection>\n"
                           "  <encapsulation id=\"id_4da6c\">\n"
                           "    <component_ref component=\"component2\" id=\"id_4da67\">\n"
                           "      <component_ref component=\"component3\" id=\"id_4da68\"/>\n"
                           "    </component_ref>\n"
                           "  </encapsulation>\n"
                           "</model>\n";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto printer = libcellml::Printer::create();
    EXPECT_EQ(in, printer->printModel(model, true));
}
