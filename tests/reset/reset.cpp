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

// TEST(Reset, removeWhenMethods)
// {
//     libcellml::Reset r;
//     libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();
//     r.addWhen(w1);
//     r.addWhen(w2);

//     EXPECT_TRUE(r.removeWhen(0));
//     EXPECT_EQ(size_t(1), r.whenCount());

//     EXPECT_FALSE(r.removeWhen(1));

//     r.addWhen(w1);
//     r.addWhen(w1);
//     r.addWhen(w1);
//     r.removeWhen(w1);
//     r.removeWhen(w1);
//     EXPECT_EQ(size_t(2), r.whenCount());

//     // Expect no change
//     EXPECT_FALSE(r.removeWhen(w3));
//     EXPECT_EQ(size_t(2), r.whenCount());

//     r.removeAllWhens();
//     EXPECT_EQ(size_t(0), r.whenCount());
// }

// TEST(Reset, whenMethods)
// {
//     libcellml::Reset r;
//     libcellml::WhenPtr c1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr c2 = std::make_shared<libcellml::When>();

//     r.addWhen(c1);
//     r.addWhen(c2);

//     libcellml::WhenPtr cA = r.when(0);

//     // Using const version of overloaded method
//     const libcellml::WhenPtr cS = static_cast<const libcellml::Reset>(r).when(0);
//     EXPECT_EQ(int(0), cS->order());

//     // Can do this as we just have a const pointer
//     EXPECT_EQ(nullptr, r.when(4));
// }

// TEST(Reset, takeWhenMethods)
// {
//     libcellml::Reset r;
//     libcellml::WhenPtr c1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr c2 = std::make_shared<libcellml::When>();

//     r.addWhen(c1);
//     r.addWhen(c2);

//     libcellml::WhenPtr c02 = r.takeWhen(1);
//     EXPECT_EQ(size_t(1), r.whenCount());
//     EXPECT_EQ(int(0), c02->order());

//     EXPECT_EQ(nullptr, r.takeWhen(4));
// }

// TEST(Reset, replaceWhenMethods)
// {
//     libcellml::Reset r;
//     libcellml::WhenPtr c1 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr c2 = std::make_shared<libcellml::When>();
//     libcellml::WhenPtr c3 = std::make_shared<libcellml::When>();

//     r.addWhen(c1);
//     r.addWhen(c2);

//     EXPECT_FALSE(r.replaceWhen(5, c3));

//     EXPECT_TRUE(r.replaceWhen(1, c3));
// }

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
    std::string a;
    const std::string in = "valid_name";
    static const std::string emptyMath =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n";
    const std::string e1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\"/>\n"
        "    <variable name=\"variable2\"/>\n"
        "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    const std::string e2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\"/>\n"
        "    <variable name=\"variable2\"/>\n"
        "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"2\">\n" // only difference is order of reset
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    const std::string e3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\"/>\n"
        "    <variable name=\"variable2\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    libcellml::Printer printer;

    c->setName(in);
    v1->setName("variable1");
    v2->setName("variable2");

    r1->setVariable(v1);
    r1->setTestVariable(v2);
    r1->setOrder(1);
    r1->setResetValue(emptyMath);
    r1->setTestValue(emptyMath);

    c->addReset(r1);
    c->addVariable(v1);
    c->addVariable(v2);

    a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    // Add another reset
    r2->setVariable(v1);
    r2->setTestVariable(v2);
    r2->setOrder(2);
    r2->setResetValue(emptyMath);
    r2->setTestValue(emptyMath);
    c->addReset(r2);

    // Remove the first one and print the model
    c->removeReset(r1);
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);

    // Remove the second one and print the model
    c->removeReset(0);
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);

    // Add them both back in and use removeAllResets to remove them
    c->addReset(r1);
    c->addReset(r2);
    c->removeAllResets();
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);

    // Try and remove the ones which don't exist so we trigger the 'false' return statement
    EXPECT_FALSE(c->removeReset(1));
    EXPECT_FALSE(c->removeReset(r1));
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
    const libcellml::ResetPtr vMethod2 = static_cast<const libcellml::Component>(c).reset(3);
    EXPECT_EQ(r4.get(), vMethod2.get());

    // Get invalid index
    EXPECT_EQ(nullptr, static_cast<const libcellml::Component>(c).reset(42));
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
