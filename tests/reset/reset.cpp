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

TEST(Reset, create) {
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    EXPECT_NE(nullptr, r);
}

TEST(Reset, order) {
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    r->setOrder(1);

    EXPECT_EQ(1, r->getOrder());
}

TEST(Reset, addAndCountChildren) {
    libcellml::Reset r;
    libcellml::WhenPtr child1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr child2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr child3 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr child4 = std::make_shared<libcellml::When>();

    EXPECT_EQ(0, r.whenCount());

    r.addWhen(child1);
    r.addWhen(child2);
    r.addWhen(child3);
    r.addWhen(child4);
    EXPECT_EQ(4, r.whenCount());

    r.addWhen(child3);
    EXPECT_EQ(5, r.whenCount());
}

TEST(Reset, contains) {
    libcellml::Reset r;
    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();

    EXPECT_FALSE(r.containsWhen(w1));

    r.addWhen(w1);
    r.addWhen(w2);
    EXPECT_TRUE(r.containsWhen(w1));
    EXPECT_TRUE(r.containsWhen(w2));
}

TEST(Reset, removeWhenMethods) {
    libcellml::Reset r;
    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();
    r.addWhen(w1);
    r.addWhen(w2);

    EXPECT_TRUE(r.removeWhen(0));
    EXPECT_EQ(1, r.whenCount());

    EXPECT_FALSE(r.removeWhen(1));

    r.addWhen(w1);
    r.addWhen(w1);
    r.addWhen(w1);
    r.removeWhen(w1);
    r.removeWhen(w1);
    EXPECT_EQ(2, r.whenCount());

    // Expect no change
    EXPECT_FALSE(r.removeWhen(w3));
    EXPECT_EQ(2, r.whenCount());

    r.removeAllWhens();
    EXPECT_EQ(0, r.whenCount());
}

TEST(Reset, getWhenMethods) {
    libcellml::Reset r;
    libcellml::WhenPtr c1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr c2 = std::make_shared<libcellml::When>();

    r.addWhen(c1);
    r.addWhen(c2);

    libcellml::WhenPtr cA = r.getWhen(0);

    // Using const version of overloaded method
    const libcellml::WhenPtr cS = static_cast<const libcellml::Reset>(r).getWhen(0);
    EXPECT_EQ(0, cS->getOrder());

    // Can do this as we just have a const pointer
    EXPECT_EQ(nullptr, r.getWhen(4));
}

TEST(Reset, takeWhenMethods) {
    libcellml::Reset r;
    libcellml::WhenPtr c1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr c2 = std::make_shared<libcellml::When>();

    r.addWhen(c1);
    r.addWhen(c2);

    libcellml::WhenPtr c02 = r.takeWhen(1);
    EXPECT_EQ(1, r.whenCount());
    EXPECT_EQ(0, c02->getOrder());

    EXPECT_EQ(nullptr, r.takeWhen(4));
}

TEST(Reset, replaceWhenMethods) {
    libcellml::Reset r;
    libcellml::WhenPtr c1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr c2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr c3 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr c4 = std::make_shared<libcellml::When>();

    r.addWhen(c1);
    r.addWhen(c2);

    EXPECT_FALSE(r.replaceWhen(5, c3));

    EXPECT_TRUE(r.replaceWhen(1, c3));
}

TEST(Reset, constructors) {
    libcellml::Reset r, r1, r2;

    r.addWhen(std::make_shared<libcellml::When>());

    // Testing assignment for Reset
    r1 = r;
    EXPECT_EQ(1, r1.whenCount());

    // Testing move assignment for Reset
    r2 = std::move(r1);
    EXPECT_EQ(1, r2.whenCount());

    // Testing move constructor for Reset
    libcellml::Reset r3 = std::move(r2);
    EXPECT_EQ(1, r3.whenCount());
}

TEST(Reset, printResetWithVariable) {
    std::string e = "<reset variable=\"A\"/>";
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    v->setName("A");

    r->setVariable(v);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printReset(r);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithOrder) {
    std::string e = "<reset order=\"1\"/>";
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    r->setOrder(1);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printReset(r);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithOrderAndVariable) {
    std::string e = "<reset variable=\"B\" order=\"1\"/>";
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    v->setName("B");

    r->setVariable(v);
    r->setOrder(1);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printReset(r);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithWhen) {
    std::string e = "<reset>"
                        "<when/>"
                    "</reset>";
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    r->addWhen(w);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printReset(r);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithMultipleWhens) {
    std::string e = "<reset>"
                        "<when/>"
                        "<when/>"
                        "<when/>"
                    "</reset>";
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

    r->addWhen(w1);
    r->addWhen(w2);
    r->addWhen(w3);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printReset(r);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithMultipleWhensWithValues) {
    std::string e = "<reset variable=\"A\">"
                        "<when order=\"2\">"
                            "<math  xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                                "some mathml"
                            "</math>"
                        "</when>"
                        "<when order=\"1\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                                "some condition in mathml"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                                "some value in mathml"
                            "</math>"
                        "</when>"
                    "</reset>";

    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();

    w1->setOrder(2);
    w1->setCondition("some mathml");

    w2->setOrder(1);
    w2->setCondition("some condition in mathml");
    w2->setValue("some value in mathml");

    r->addWhen(w1);
    r->addWhen(w2);

    libcellml::Printer p(libcellml::Format::XML);

    const std::string a = p.printReset(r);
    EXPECT_EQ(e, a);
}

