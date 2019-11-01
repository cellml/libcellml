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
    libcellml::ResetPtr r = libcellml::Reset::create();

    EXPECT_NE(nullptr, r);
}

TEST(Reset, order)
{
    libcellml::ResetPtr r = libcellml::Reset::create();

    EXPECT_FALSE(r->isOrderSet());
    r->setOrder(1);

    EXPECT_EQ(1, r->order());
    EXPECT_TRUE(r->isOrderSet());

    r->unsetOrder();
    EXPECT_FALSE(r->isOrderSet());
}

TEST(Reset, addAndCountChildren)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr child1 = libcellml::When::create();
    libcellml::WhenPtr child2 = libcellml::When::create();
    libcellml::WhenPtr child3 = libcellml::When::create();
    libcellml::WhenPtr child4 = libcellml::When::create();

    EXPECT_EQ(size_t(0), r->whenCount());

    r->addWhen(child1);
    r->addWhen(child2);
    r->addWhen(child3);
    r->addWhen(child4);
    EXPECT_EQ(size_t(4), r->whenCount());

    r->addWhen(child3);
    EXPECT_EQ(size_t(5), r->whenCount());
}

TEST(Reset, contains)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr w1 = libcellml::When::create();
    libcellml::WhenPtr w2 = libcellml::When::create();

    EXPECT_FALSE(r->containsWhen(w1));

    r->addWhen(w1);
    r->addWhen(w2);
    EXPECT_TRUE(r->containsWhen(w1));
    EXPECT_TRUE(r->containsWhen(w2));
}

TEST(Reset, removeWhenMethods)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr w1 = libcellml::When::create();
    libcellml::WhenPtr w2 = libcellml::When::create();
    libcellml::WhenPtr w3 = libcellml::When::create();
    r->addWhen(w1);
    r->addWhen(w2);

    EXPECT_TRUE(r->removeWhen(0));
    EXPECT_EQ(size_t(1), r->whenCount());

    EXPECT_FALSE(r->removeWhen(1));

    r->addWhen(w1);
    r->addWhen(w1);
    r->addWhen(w1);
    r->removeWhen(w1);
    r->removeWhen(w1);
    EXPECT_EQ(size_t(2), r->whenCount());

    // Expect no change
    EXPECT_FALSE(r->removeWhen(w3));
    EXPECT_EQ(size_t(2), r->whenCount());

    r->removeAllWhens();
    EXPECT_EQ(size_t(0), r->whenCount());
}

TEST(Reset, whenMethods)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr c1 = libcellml::When::create();
    libcellml::WhenPtr c2 = libcellml::When::create();

    r->addWhen(c1);
    r->addWhen(c2);

    libcellml::WhenPtr cA = r->when(0);

    // Using const version of overloaded method
    const libcellml::WhenPtr cS = r->when(0);
    EXPECT_EQ(int(0), cS->order());

    // Can do this as we just have a const pointer
    EXPECT_EQ(nullptr, r->when(4));
}

TEST(Reset, takeWhenMethods)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr c1 = libcellml::When::create();
    libcellml::WhenPtr c2 = libcellml::When::create();

    r->addWhen(c1);
    r->addWhen(c2);

    libcellml::WhenPtr c02 = r->takeWhen(1);
    EXPECT_EQ(size_t(1), r->whenCount());
    EXPECT_EQ(int(0), c02->order());

    EXPECT_EQ(nullptr, r->takeWhen(4));
}

TEST(Reset, replaceWhenMethods)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr c1 = libcellml::When::create();
    libcellml::WhenPtr c2 = libcellml::When::create();
    libcellml::WhenPtr c3 = libcellml::When::create();

    r->addWhen(c1);
    r->addWhen(c2);

    EXPECT_FALSE(r->replaceWhen(5, c3));

    EXPECT_TRUE(r->replaceWhen(1, c3));
}

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
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::VariablePtr v = libcellml::Variable::create();

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
    libcellml::ResetPtr r = libcellml::Reset::create();

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
    libcellml::ResetPtr r = libcellml::Reset::create();

    libcellml::VariablePtr v = libcellml::Variable::create();

    v->setName("B");

    r->setVariable(v);
    r->setOrder(1);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithWhen)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset>\n"
        "      <when/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = libcellml::Reset::create();

    libcellml::WhenPtr w = libcellml::When::create();

    r->addWhen(w);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithMultipleWhens)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset>\n"
        "      <when/>\n"
        "      <when/>\n"
        "      <when/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = libcellml::Reset::create();

    libcellml::WhenPtr w1 = libcellml::When::create();
    libcellml::WhenPtr w2 = libcellml::When::create();
    libcellml::WhenPtr w3 = libcellml::When::create();

    r->addWhen(w1);
    r->addWhen(w2);
    r->addWhen(w3);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithWhenWithValueSet)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset>\n"
        "      <when>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          a value set\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  a value set\n"
        "</math>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr w = libcellml::When::create();

    w->setValue(math);
    r->addWhen(w);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithMultipleWhensWithValues)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset variable=\"A\">\n"
        "      <when order=\"2\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some mathml\n"
        "        </math>\n"
        "      </when>\n"
        "      <when order=\"-1\" id=\"wid\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::string condition1 =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  some mathml\n"
        "</math>\n";
    const std::string condition2 =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  some condition in mathml\n"
        "</math>\n";
    const std::string value2 =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  some value in mathml\n"
        "</math>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr w1 = libcellml::When::create();
    libcellml::WhenPtr w2 = libcellml::When::create();
    libcellml::VariablePtr v = libcellml::Variable::create();

    v->setName("A");
    w1->setOrder(2);
    w1->setCondition(condition1);

    w2->setOrder(-1);
    w2->setCondition(condition2);
    w2->setValue(value2);
    w2->setId("wid");

    r->setVariable(v);
    r->addWhen(w1);
    r->addWhen(w2);
    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, printResetWithMultipleWhensWithOrders)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component>\n"
        "    <reset>\n"
        "      <when order=\"7\"/>\n"
        "      <when order=\"-1\"/>\n"
        "      <when order=\"0\"/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::WhenPtr w1 = libcellml::When::create();
    libcellml::WhenPtr w2 = libcellml::When::create();
    libcellml::WhenPtr w3 = libcellml::When::create();

    r->addWhen(w1);
    r->addWhen(w2);
    r->addWhen(w3);

    w1->setOrder(7);
    w2->setOrder(-1);
    w3->setOrder(0);

    c->addReset(r);

    libcellml::Printer p;

    const std::string a = p.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Reset, addRemoveResetFromComponentMethods)
{
    const std::string in = "valid_name";
    const std::string e1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"V_na\"/>\n"
        "    <reset variable=\"V_na\">\n"
        "      <when order=\"3\"/>\n"
        "      <when order=\"0\"/>\n"
        "    </reset>\n"
        "    <reset variable=\"V_na\">\n"
        "      <when order=\"1\"/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::string e2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"V_na\"/>\n"
        "    <reset variable=\"V_na\">\n"
        "      <when order=\"3\"/>\n"
        "      <when order=\"0\"/>\n"
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
    const std::string e4 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"V_na\"/>\n"
        "    <reset variable=\"V_na\">\n"
        "      <when order=\"1\"/>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->component(0);
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();
    libcellml::ResetPtr r3 = libcellml::Reset::create();
    libcellml::WhenPtr w1 = libcellml::When::create();
    libcellml::WhenPtr w2 = libcellml::When::create();
    libcellml::WhenPtr w3 = libcellml::When::create();

    c->setName(in);
    v->setName("V_na");

    r1->setVariable(v);
    r2->setVariable(v);

    r1->addWhen(w1);
    r1->addWhen(w3);
    r2->addWhen(w2);

    w1->setOrder(3);
    w2->setOrder(1);
    w3->setOrder(0);

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
    libcellml::ComponentPtr c = libcellml::Component::create();
    c->setName(in);

    libcellml::ResetPtr r1 = libcellml::Reset::create();
    c->addReset(r1);
    libcellml::ResetPtr r2 = libcellml::Reset::create();
    c->addReset(r2);
    libcellml::ResetPtr r3 = libcellml::Reset::create();
    c->addReset(r3);
    libcellml::ResetPtr r4 = libcellml::Reset::create();
    c->addReset(r4);

    EXPECT_EQ(size_t(4), c->resetCount());

    // Get by index
    libcellml::ResetPtr rMethod1 = c->reset(1);
    EXPECT_EQ(r2.get(), rMethod1.get());

    // Get const by index
    const libcellml::ResetPtr vMethod2 = c->reset(3);
    EXPECT_EQ(r4.get(), vMethod2.get());

    // Get invalid index
    EXPECT_EQ(nullptr, c->reset(7));
}

TEST(Reset, hasResetFromComponentMethod)
{
    const std::string in = "valid_name";
    libcellml::ComponentPtr c = libcellml::Component::create();
    c->setName(in);

    libcellml::ResetPtr r1 = libcellml::Reset::create();
    c->addReset(r1);
    libcellml::ResetPtr r2 = libcellml::Reset::create();
    c->addReset(r2);
    libcellml::ResetPtr r3 = libcellml::Reset::create();

    EXPECT_TRUE(c->hasReset(r2));
    EXPECT_FALSE(c->hasReset(r3));
}
