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


TEST(Printer, printEmptyModel) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>";
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();

    libcellml::Printer p(libcellml::Format::XML);

    std::string a = p.printModel(m);

    EXPECT_EQ(e, a);
}

TEST(Model, printEmptyModelAllocatePointer) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>";
    libcellml::Model* m = new libcellml::Model();
    std::string a = m->serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
    delete m;
}

TEST(Printer, printEmptyUnits) {
    const std::string e = "";
    libcellml::Units u;
    std::string a = u.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Printer, printEmptyVariable) {
    const std::string e = "<variable/>";
    libcellml::Variable v;
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Printer, printEncapsulation) {
    const std::string e_parent =
            "<component/>"
            "<component/>"
            "<encapsulation>"
                "<component_ref>"
                    "<component_ref/>"
                "</component_ref>"
            "</encapsulation>";
    const std::string e_child = "<component/>";
    libcellml::Component parent;
    libcellml::ComponentPtr child = std::make_shared<libcellml::Component>();
    parent.addComponent(child);
    std::string a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent, a_parent);
    std::string a_child = child->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Printer, printEncapsulationWithNames) {
    const std::string e_parent =
            "<component name=\"parent_component\"/>"
            "<component name=\"child_component\"/>"
            "<encapsulation>"
                "<component_ref component=\"parent_component\">"
                    "<component_ref component=\"child_component\"/>"
                "</component_ref>"
            "</encapsulation>";
    const std::string e_child= "<component name=\"child_component\"/>";
    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::ComponentPtr child = std::make_shared<libcellml::Component>();
    child->setName("child_component");
    parent.addComponent(child);
    std::string a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent, a_parent);
    std::string a_child = child->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_child, a_child);
}


