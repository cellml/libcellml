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

TEST(Reset, create)
{
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    EXPECT_NE(nullptr, r);
}

TEST(Reset, order)
{
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    EXPECT_FALSE(r->isOrderSet());
    r->setOrder(1);

    EXPECT_EQ(1, r->order());
    EXPECT_TRUE(r->isOrderSet());

    r->unsetOrder();
    EXPECT_FALSE(r->isOrderSet());
}

// TEST(Reset, constructors)
// {
//     libcellml::Reset r;
//     libcellml::Reset r1;
//     libcellml::Reset r2;

//     r.addWhen(std::make_shared<libcellml::When>());

//     // Testing assignment for Reset
//     r1 = r;
//     EXPECT_EQ(size_t(1), r1.whenCount());

//     // Testing move assignment for Reset
//     r2 = std::move(r1);
//     EXPECT_EQ(size_t(1), r2.whenCount());

//     // Testing move constructor for Reset
//     libcellml::Reset r3 = std::move(r2);
//     EXPECT_EQ(size_t(1), r3.whenCount());
// }

TEST(Reset, printResetWithVariable)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset variable=\"A\"/>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    v->setName("A");

    r->setVariable(v);

    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithOrder)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset order=\"1\"/>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    r->setOrder(1);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithOrderAndVariable)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset variable=\"B\" order=\"1\"/>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    v->setName("B");

    r->setVariable(v);
    r->setOrder(1);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

// TEST(Reset, printResetWithWhen)
// {
//     const std::string e =
//         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//         "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
//         "  <component>\n"
//         "    <reset>\n"
//         "      <when/>\n"
//         "    </reset>\n"
//         "  </component>\n"
//         "</model>\n";
//     libcellml::ModelPtr m = createModelWithComponent();
//     libcellml::ComponentPtr c = m->component(0);
//     libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

//     libcellml::WhenPtr w = std::make_shared<libcellml::When>();

//     r->addWhen(w);
//     c->addReset(r);

//     libcellml::Printer p;

//     const std::string a = p.printModel(m);
//     EXPECT_EQ(e, a);
// }

// TEST(Reset, printResetWithMultipleWhens)
// {
//     const std::string e =
//         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//         "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
//         "  <component>\n"
//         "    <reset>\n"
//         "      <when/>\n"
//         "      <when/>\n"
//         "      <when/>\n"
//         "    </reset>\n"
//         "  </component>\n"
//         "</model>\n";
//     libcellml::ModelPtr m = createModelWithComponent();
//     libcellml::ComponentPtr c = m->component(0);
//     libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

//     libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

//     r->addWhen(w1);
//     r->addWhen(w2);
//     r->addWhen(w3);
//     c->addReset(r);

//     libcellml::Printer p;

//     const std::string a = p.printModel(m);
//     EXPECT_EQ(e, a);
// }

// TEST(Reset, printResetWithWhenWithValueSet)
// {
//     const std::string e =
//         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//         "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
//         "  <component>\n"
//         "    <reset>\n"
//         "      <when>\n"
//         "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "          a value set\n"
//         "        </math>\n"
//         "      </when>\n"
//         "    </reset>\n"
//         "  </component>\n"
//         "</model>\n";
//     const std::string math =
//         "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "  a value set\n"
//         "</math>\n";

//     libcellml::ModelPtr m = createModelWithComponent();
//     libcellml::ComponentPtr c = m->component(0);
//     libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
//     libcellml::WhenPtr w = std::make_shared<libcellml::When>();

//     w->setValue(math);
//     r->addWhen(w);
//     c->addReset(r);

//     libcellml::Printer p;

//     const std::string a = p.printModel(m);
//     EXPECT_EQ(e, a);
// }

// TEST(Reset, printResetWithMultipleWhensWithValues)
// {
//     const std::string e =
//         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//         "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
//         "  <component>\n"
//         "    <reset variable=\"A\">\n"
//         "      <when order=\"2\">\n"
//         "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "          some mathml\n"
//         "        </math>\n"
//         "      </when>\n"
//         "      <when order=\"-1\" id=\"wid\">\n"
//         "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "          some condition in mathml\n"
//         "        </math>\n"
//         "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "          some value in mathml\n"
//         "        </math>\n"
//         "      </when>\n"
//         "    </reset>\n"
//         "  </component>\n"
//         "</model>\n";
//     const std::string condition1 =
//         "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "  some mathml\n"
//         "</math>\n";
//     const std::string condition2 =
//         "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "  some condition in mathml\n"
//         "</math>\n";
//     const std::string value2 =
//         "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
//         "  some value in mathml\n"
//         "</math>\n";

//     libcellml::ModelPtr m = createModelWithComponent();
//     libcellml::ComponentPtr c = m->component(0);
//     libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
//     libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
//     libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

//     v->setName("A");
//     w1->setOrder(2);
//     w1->setCondition(condition1);

//     w2->setOrder(-1);
//     w2->setCondition(condition2);
//     w2->setValue(value2);
//     w2->setId("wid");

//     r->setVariable(v);
//     r->addWhen(w1);
//     r->addWhen(w2);
//     c->addReset(r);

//     libcellml::Printer p;

//     const std::string a = p.printModel(m);
//     EXPECT_EQ(e, a);
// }

// TEST(Reset, printResetWithMultipleWhensWithOrders)
// {
//     const std::string e =
//         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//         "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
//         "  <component>\n"
//         "    <reset>\n"
//         "      <when order=\"7\"/>\n"
//         "      <when order=\"-1\"/>\n"
//         "      <when order=\"0\"/>\n"
//         "    </reset>\n"
//         "  </component>\n"
//         "</model>\n";
//     libcellml::ModelPtr m = createModelWithComponent();
//     libcellml::ComponentPtr c = m->component(0);
//     libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
//     libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

//     r->addWhen(w1);
//     r->addWhen(w2);
//     r->addWhen(w3);

//     w1->setOrder(7);
//     w2->setOrder(-1);
//     w3->setOrder(0);

//     c->addReset(r);

//     libcellml::Printer p;

//     const std::string a = p.printModel(m);
//     EXPECT_EQ(e, a);
// }

TEST(Reset, addRemoveResetFromComponentMethods)
{
    const std::string in = "valid_name";
    const std::string e1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"V_na\"/>\n"
        "    <reset variable=\"V_na\">\n"
        // "      <when order=\"3\"/>\n"
        // "      <when order=\"0\"/>\n"
        "    </reset>\n"
        "    <reset variable=\"V_na\">\n"
        // "      <when order=\"1\"/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::string e2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"V_na\"/>\n"
        "    <reset variable=\"V_na\">\n"
        // "      <when order=\"3\"/>\n"
        // "      <when order=\"0\"/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::string e3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"V_na\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    // libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    // libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    // libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
    // libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

    c->setName(in);
    v->setName("V_na");

    r1->setVariable(v);
    r2->setVariable(v);

    // r1->addWhen(w1);
    // r1->addWhen(w3);
    // r2->addWhen(w2);

    // w1->setOrder(3);
    // w2->setOrder(1);
    // w3->setOrder(0);

    c->addReset(r1);
    c->addReset(r2);
    c->addVariable(v);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    EXPECT_TRUE(c->removeReset(r2));
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);
    EXPECT_FALSE(c->removeReset(r3));

    c->addReset(r2);
    c->addReset(r2);
    c->removeAllResets();
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);

    c->addReset(r1);
    c->addReset(r2);
    c->addReset(r3);

    EXPECT_TRUE(c->removeReset(0)); // r1
    EXPECT_TRUE(c->removeReset(1)); // new index of r3
    a = printer.printModel(m);
    EXPECT_EQ(e4, a);
    EXPECT_FALSE(c->removeReset(1));
}

TEST(Reset, resetFromComponentMethod)
{
    const std::string in = "valid_name";
    libcellml::Component c;
    c.setName(in);

    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    c.addReset(r1);
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    c.addReset(r2);
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    c.addReset(r3);
    libcellml::ResetPtr r4 = std::make_shared<libcellml::Reset>();
    c.addReset(r4);

    EXPECT_EQ(size_t(4), c.resetCount());

    // Get by index
    libcellml::ResetPtr rMethod1 = c.reset(1);
    EXPECT_EQ(r2.get(), rMethod1.get());

    // Get const by index
    const libcellml::ResetPtr vMethod2 = c.reset(3);
    EXPECT_EQ(r4.get(), vMethod2.get());

    // Get invalid index
    EXPECT_EQ(nullptr, c.reset(7));
}

TEST(Reset, hasResetFromComponentMethod)
{
    const std::string in = "valid_name";
    libcellml::Component c;
    c.setName(in);

    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    c.addReset(r1);
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    c.addReset(r2);
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();

    EXPECT_TRUE(c.hasReset(r2));
    EXPECT_FALSE(c.hasReset(r3));
}
