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
limitations under the License.Some license of other
*/

#include "gtest/gtest.h"

#include <libcellml>


TEST(Variable, serialise) {
    const std::string e = "<variable/>";
    libcellml::Variable v;
    std::string a = v.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, validVariableName) {
    const std::string in = "valid_name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"dimensionless\" />"
              "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c->addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v->setUnits(u);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", v->getName());
}

TEST(Variable, invalidVariableName) {
    const std::string in = "invalid name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"dimensionless\" />"
              "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c->addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v->setUnits(u);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", v->getName());
}

TEST(Variable, invalidUnitsName) {
    const std::string in = "valid_name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"invalid name\" />"
              "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c->addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("invalid name");
    v->setUnits(u);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u->getName());
}



