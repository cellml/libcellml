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

#include <libcellml/model.h>
#define private public
#include <libcellml/printer.h>
#undef private
#include <libcellml/component.h>
#include <libcellml/when.h>

TEST(PrinterInternal, printEncapsulationOnly) {
    const std::string e =
            "<component name=\"child_component\"/>"
            "<encapsulation>"
                "<component_ref component=\"parent_component\">"
                    "<component_ref component=\"child_component\"/>"
                "</component_ref>"
            "</encapsulation>";
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    parent->setName("parent_component");
    libcellml::ComponentPtr child = std::make_shared<libcellml::Component>();
    child->setName("child_component");
    parent->addComponent(child);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printEncapsulation(parent);

    EXPECT_EQ(e, a);
}

TEST(PrinterInternal, printEmptyWhen) {
    const std::string e = "<when/>";
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    libcellml::Printer printer(libcellml::Format::XML);
    const std::string a = printer.printWhen(w);
    EXPECT_EQ(e, a);
}

TEST(PrinterInternal, printWhenWithOrder) {
    std::string e = "<when order=\"1\"/>";

    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    libcellml::Printer printer(libcellml::Format::XML);
    std::string a = printer.printWhen(w);
    EXPECT_EQ(e, a);
}

TEST(PrinterInternal, printWhenWithOrderConditionValue) {
    std::string e = "<when order=\"3\">"
                        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "<apply><lt/><ci>B</ci><cn cellml:units=\"ms\">-5</cn></apply>"
                        "</math>"
                        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "<apply><plus/><ci>B</ci><cn cellml:units=\"ms\">10</cn></apply>"
                        "</math>"
                    "</when>";

    libcellml::WhenPtr w = std::make_shared<libcellml::When>();
    w->setOrder(3);
    w->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"><apply><lt/><ci>B</ci><cn cellml:units=\"ms\">-5</cn></apply></math>");
    w->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"><apply><plus/><ci>B</ci><cn cellml:units=\"ms\">10</cn></apply></math>");

    libcellml::Printer printer(libcellml::Format::XML);
    std::string a = printer.printWhen(w);
    EXPECT_EQ(e, a);
}

