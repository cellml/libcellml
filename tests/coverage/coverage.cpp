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

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */
TEST(Coverage, connectionComment)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelA\">\n"
        "  <component name=\"componentA\">\n"
        "    <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"component1\">\n"
        "    <!-- Comment on connection. -->\n"
        "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\">\n"
        "      <!-- Comment in a map variables. -->\n"
        "    </map_variables>\n"
        "  </connection>\n"
        "</model>\n";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(4), p.errorCount());
}

TEST(Coverage, importWithNonHrefXlink)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xlink:type=\"simple\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "    <!-- Comment in an import block -->\n"
        "  </import>\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"component_in_this_model\" component_1=\"component_bob\">\n"
        "    <map_variables variable_2=\"variable_import\" variable_1=\"variable_bob\"/>\n"
        "  </connection>\n"
        "</model>\n";

    // Parse
    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(size_t(0), parser.errorCount());
}

TEST(Coverage, printer)
{
    libcellml::Printer p;
    libcellml::Printer pm;

    libcellml::ErrorPtr error = libcellml::Error::create();

    p.addError(error);

    pm = std::move(p);

    libcellml::Printer pc(pm);

    EXPECT_EQ(size_t(1), pc.errorCount());
}

TEST(Coverage, generator)
{
    libcellml::Generator rg;
    libcellml::Generator ao;

    ao = rg;

    std::vector<libcellml::Generator> vec;

    vec.push_back(rg);
    vec.insert(vec.begin(), ao);

    rg.setProfile(std::make_shared<libcellml::GeneratorProfile>());
}

TEST(Coverage, generatorProfile)
{
    libcellml::GeneratorProfile rgp;
    libcellml::GeneratorProfile ao;

    ao = rgp;

    std::vector<libcellml::GeneratorProfile> vec;

    vec.push_back(rgp);
    vec.insert(vec.begin(), ao);

    auto gp = libcellml::GeneratorProfile::create();
}

TEST(Coverage, generatorVariable)
{
    libcellml::GeneratorVariable rgp;
    libcellml::GeneratorVariable ao;

    ao = rgp;

    std::vector<libcellml::GeneratorVariable> vec;

    vec.push_back(rgp);
    vec.insert(vec.begin(), ao);
}

TEST(Coverage, entityHasParent)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();
    libcellml::VariablePtr v = libcellml::Variable::create();

    c2->addVariable(v);
    c1->addComponent(c2);
    m->addComponent(c1);

    EXPECT_TRUE(v->hasParent());
    EXPECT_TRUE(c2->hasParent());
    EXPECT_TRUE(c1->hasParent());
    EXPECT_TRUE(c2->hasParent());
    EXPECT_FALSE(c3->hasParent());
}
