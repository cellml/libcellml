/*
Copyright 2015 University of Auckland

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
#include <iostream>
/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

TEST(Coverage, import) {
    std::string e = "";
    libcellml::Import i, im;

    im = std::move(i);

    // Copy constructor
    libcellml::Import ic(im);

    EXPECT_EQ(e, ic.serialise(libcellml::Format::XML));
}

TEST(Coverage, entity) {
    std::string ex = "";

    libcellml::Entity e, em;

    EXPECT_EQ(ex, e.serialise(libcellml::Format::XML));
    em = std::move(e);

    libcellml::Model m;
    e.setParent(&m);

    EXPECT_EQ(&m, e.getParent());

    libcellml::Component c;
    e.setParent(&c);

    EXPECT_EQ(&c, e.getParent());
}

TEST(Coverage, units) {
    std::string e = "<units name=\"dimensionless\" base_unit=\"yes\"/>";
    libcellml::Units u, um;

    u.setName("dimensionless");
    u.setBaseUnit();

    um = std::move(u);

    // Copy constructor
    libcellml::Units uc(um);

    EXPECT_EQ(e, uc.serialise(libcellml::Format::XML));
}

TEST(Coverage, unitsGetVariations) {
    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("a_unit");

    u->addUnit(libcellml::STANDARD_UNIT_AMPERE, "micro");
    m.addUnits(u);

    libcellml::UnitsPtr un = m.getUnits(0);
    EXPECT_EQ("a_unit", un->getName());
    libcellml::UnitsPtr uSn = static_cast<const libcellml::Model>(m).getUnits(0);
    EXPECT_EQ("a_unit", uSn->getName());

    libcellml::UnitsPtr uns = m.getUnits("a_unit");
    EXPECT_EQ("a_unit", uns->getName());
    libcellml::UnitsPtr uSns = static_cast<const libcellml::Model>(m).getUnits("a_unit");
    EXPECT_EQ("a_unit", uSns->getName());
}

TEST(Coverage, prefixToString) {
    libcellml::Model m;

    std::vector<std::string> prefix_str =
        {"atto",
         "centi",
         "deca",
         "deci",
         "exa",
         "femto",
         "giga",
         "hecto",
         "kilo",
         "mega",
         "micro",
         "milli",
         "nano",
         "peta",
         "pico",
         "tera",
         "yocto",
         "yotta",
         "zepto",
         "zetta"
        };
    std::vector<libcellml::Prefix> prefix_enum =
        {libcellml::Prefix::ATTO,
         libcellml::Prefix::CENTI,
         libcellml::Prefix::DECA,
         libcellml::Prefix::DECI,
         libcellml::Prefix::EXA,
         libcellml::Prefix::FEMTO,
         libcellml::Prefix::GIGA,
         libcellml::Prefix::HECTO,
         libcellml::Prefix::KILO,
         libcellml::Prefix::MEGA,
         libcellml::Prefix::MICRO,
         libcellml::Prefix::MILLI,
         libcellml::Prefix::NANO,
         libcellml::Prefix::PETA,
         libcellml::Prefix::PICO,
         libcellml::Prefix::TERA,
         libcellml::Prefix::YOCTO,
         libcellml::Prefix::YOTTA,
         libcellml::Prefix::ZEPTO,
         libcellml::Prefix::ZETTA
        };
    for (std::vector<std::string>::size_type i = 0; i != prefix_str.size(); ++i) {
        std::string prefix = prefix_str[i];
        libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
        u->setName("abcdefg");
        u->addUnit("empty", prefix_enum[i]);

        m.addUnits(u);

        std::string a = m.serialise(libcellml::Format::XML);
        std::size_t found = a.find(prefix);
        EXPECT_NE(std::string::npos, found);
    }
}

TEST(Coverage, variable) {
    std::string e = "<variable units=\"dimensionless\" initial_value=\"1\" interface=\"public\"/>";
    libcellml::Variable v, vm;
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    v.setInitialValue(1.0);
    v.setInterfaceType("public");
    u->setName("dimensionless");
    v.setUnits(u);

    vm = std::move(v);

    // Copy constructor
    libcellml::Variable vc(vm);

    EXPECT_EQ(e, vc.serialise(libcellml::Format::XML));
}

TEST(Coverage, component) {
    std::string e = "<component name=\"name\"><variable/><1+1=2></component>";
    libcellml::Component c, cm;
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    c.setName("name");
    c.addVariable(v);
    c.setMath("<1+1=2>");
    EXPECT_EQ(e, c.serialise(libcellml::Format::XML));

    cm = std::move(c);
    EXPECT_EQ(e, cm.serialise(libcellml::Format::XML));

    // Copy constructor
    libcellml::Component cc(cm);
    EXPECT_EQ(e, cc.serialise(libcellml::Format::XML));
}

TEST(Coverage, componentEntity) {
    const std::string e = "<component/><component/><encapsulation><component_ref><component_ref/></component_ref></encapsulation>";
    libcellml::Component p, pm;
    libcellml::ComponentPtr child = std::make_shared<libcellml::Component>();
    p.addComponent(child);
    EXPECT_EQ(e, p.serialise(libcellml::Format::XML));

    pm = std::move(p);
    EXPECT_EQ(e, pm.serialise(libcellml::Format::XML));

    libcellml::Component pc(pm);
    EXPECT_EQ(e, pc.serialise(libcellml::Format::XML));
}

TEST(Coverage, parser) {
    libcellml::Parser p(libcellml::Format::XML), pm(libcellml::Format::XML), pa(libcellml::Format::XML);
    pa = p;
    pm = std::move(p);

    libcellml::Parser pc(pm);
}

TEST(Coverage, entityError) {
    std::string ex = "";

    libcellml::EntityErrorPtr e = std::make_shared<libcellml::EntityError>();

    EXPECT_EQ(ex, e->serialise());
}

TEST(Coverage, parserWithEmptyString) {
    std::string ex = "";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(ex), std::invalid_argument);
}

TEST(Coverage, parserWithNonXmlString) {
    std::string ex = "Not an xml string.";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(ex), std::invalid_argument);
}

TEST(Coverage, parseModelWithNamedComponentWithUnits) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\" base_unit=\"no\"/>"
              "</component>"
            "</model>";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
              "</component>"
            "</model>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Coverage, parseModelWithNamedComponentWithInvalidUnits) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit multiplier=\"Z\" offset=\"MM\" exponent=\"35.0E+310\" units=\"celsius\"/>"
                  "<bobshouse address=\"34 Rich Lane\"/>"
                "</units>"
                "<units name=\"dimensionless\" base_unit=\"no\"/>"
              "</component>"
            "</model>";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
              "</component>"
            "</model>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(4, parser.errorCount());

    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_TRUE(parser.getError(i)->serialise().length() > 0);
    }

    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Coverage, parseModelInvalidUnitsAttribute) {
    const std::string in1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
                "<units name=\"fahrenheit\">"
                    "<unit poofset=\"2.0\" units=\"celsius\"/>"
                    "</units>"
                "<units name=\"dimensionless\" base_unit=\"no\"/>"
            "</model>";
    const std::string expectedErrorMessage1 = "Invalid attribute 'poofset' found in units 'fahrenheit'.";
    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(in1);

    ASSERT_EQ(1, parser.errorCount());

    EXPECT_EQ(expectedErrorMessage1, parser.getError(0)->serialise());

    const std::string in2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
                "<units roofset=\"2.0\">"
                    "<unit/>"
                    "</units>"
                "<units name=\"dimensionless\" base_unit=\"no\"/>"
            "</model>";
    const std::string expectedErrorMessage2 = "Invalid attribute 'roofset' found in unnamed units.";

    parser.clearErrors();
    parser.parseModel(in2);

    ASSERT_EQ(1, parser.errorCount());

    EXPECT_EQ(expectedErrorMessage2, parser.getError(0)->serialise());
}

TEST(Coverage, parserWithEmptyEncapsulation) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(48, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserNoComponentAttribute) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_ref></component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(57, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserNoComponentRef) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_free></component_free>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(47, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserNoComponent) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
                "<component_ref></component_ref>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
//    EXPECT_EQ("", p.getError(1)->serialise());
    EXPECT_EQ(82, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserMissingComponent) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
                "<component_ref component=\"dave\"></component_ref>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(83, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserNoComponentChild) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(43, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserNoChildComponentRef) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
            "<component_free/>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(47, p.getError(0)->serialise().length());
}

TEST(Coverage, encapsulationParserGrandchild) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
            "<component_free/>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(47, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithEmptyConnection) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<connection>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(47, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithConnectionErrorNoComponent1Existing) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component1\"/>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(85, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithConnectionErrorNoComponent2Existing) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component1\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component1\"  component_2=\"component2\"/>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(85, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithConnectionErrorNoComponent1) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"componentA\"/>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(57, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithConnectionErrorNoMapComponents) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(45, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithConnectionErrorNoMapVariables) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"componentA\" component_1=\"componentA\"/>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(61, p.getError(0)->serialise().length());
}

TEST(Coverage, importedComponent2ConnectionAndParse) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
          "<import xlink:href=\"some-other-model.xml\" "
              "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
              "<component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>"
          "</import>"
          "<component name=\"component_bob\">"
            "<variable name=\"variable_bob\"/>"
          "</component>"
          "<connection>"
            "<map_components component_2=\"component_in_this_model\" component_1=\"component_bob\"/>"
            "<map_variables variable_2=\"variable_import\" variable_1=\"variable_bob\"/>"
          "</connection>"
        "</model>";

    // Parse
    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(e);
    EXPECT_EQ(0, parser.errorCount());
}

TEST(Coverage, component2ConnectionVariableMissing) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"component_dave\" component_1=\"component_bob\"/>"
                "<map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>"
            "</connection>"
        "</model>";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(65, p.getError(0)->serialise().length());
}

TEST(Coverage, component2InConnectionMissing) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component_bob\"/>"
                "<map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>"
            "</connection>"
        "</model>";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
        "</model>";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr m = p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(e, m->serialise(libcellml::Format::XML));
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(136, p.getError(0)->serialise().length());
}

TEST(Coverage, connectionVariable2Missing) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"component_dave\" component_1=\"component_bob\"/>"
                "<map_variables variable_1=\"variable_bob\"/>"
            "</connection>"
        "</model>";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(55, p.getError(0)->serialise().length());
}

TEST(Coverage, connectionVariable1Missing) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"component_dave\" component_1=\"component_bob\"/>"
                "<map_variables variable_2=\"variable_dave\"/>"
            "</connection>"
        "</model>";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(55, p.getError(0)->serialise().length());
}

TEST(Coverage, parserWithConnectionErrorNoMapVariablesType) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component1\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<component name=\"component2\">"
                "<variable name=\"variable2\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component1\"  component_2=\"component2\"/>"
                "<map_variabels variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(67, p.getError(0)->serialise().length());
}

TEST(Coverage, parserInvalidRootNode) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<yodel xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
        "</yodel>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(42, p.getError(0)->serialise().length());
}

TEST(Coverage, parserModelAttribute) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" game=\"model_name\">"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(57, p.getError(0)->serialise().length());
}

TEST(Coverage, parserModelElement) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<uknits/>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(54, p.getError(0)->serialise().length());
}

TEST(Coverage, parserUnitsAttributeError) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<units name=\"pH\" base_unit=\"yes\" invalid_attribute=\"yes\"/>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
//    EXPECT_EQ("", p.getError(0)->serialise());
    EXPECT_EQ(58, p.getError(0)->serialise().length());
}

TEST(Coverage, parserComponentAttributeErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component lame=\"randy\"/>"
        "</model>";
    std::string expectError1 = "Invalid attribute 'lame' found in unnamed component.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"randy\" son=\"stan\"/>"
        "</model>";
    std::string expectError2 = "Invalid attribute 'son' found in component 'randy'.";

    std::string input3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component son=\"stan\" name=\"randy\"/>"
        "</model>";
    std::string expectError3 = "Invalid attribute 'son' found in component 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->serialise());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->serialise());

    p.clearErrors();
    p.parseModel(input3);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError3, p.getError(0)->serialise());
}

TEST(Coverage, parserComponentElementErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component>"
            "<son name=\"stan\"/>"
          "</component>"
        "</model>";
    std::string expectError1 = "Invalid child element 'son' found in unnamed component.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"randy\">"
            "<son name=\"stan\"/>"
          "</component>"
        "</model>";
    std::string expectError2 = "Invalid child element 'son' found in component 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->serialise());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->serialise());
}

TEST(Coverage, parserVariableAttributeErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"randy\">"
                "<variable lame=\"randy\"/>"
            "</component>"
        "</model>";
    std::string expectError1 = "Invalid attribute 'lame' found in unnamed variable.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"randy\">"
                "<variable name=\"randy\" son=\"stan\"/>"
            "</component>"
        "</model>";
    std::string expectError2 = "Invalid attribute 'son' found in variable 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->serialise());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->serialise());
}

TEST(Coverage, parserUnitsElementErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<units>"
            "<son name=\"stan\"/>"
          "</units>"
        "</model>";
    std::string expectError1 = "Invalid child element 'son' found in unnamed units.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<units name=\"randy\">"
            "<son name=\"stan\"/>"
          "</units>"
        "</model>";
    std::string expectError2 = "Invalid child element 'son' found in units 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->serialise());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->serialise());
}
