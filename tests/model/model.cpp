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


TEST(Model, serialise) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>";
    libcellml::Model m;
    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(Model, serialiseAllocatePointer) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>";
    libcellml::Model* m = new libcellml::Model();
    std::string a = m->serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
    delete m;
}

TEST(Model, name) {
    std::string n = "name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + n + "\"/>";

    libcellml::Model m;
    m.setName(n);

    EXPECT_EQ("name", m.getName());

    EXPECT_EQ(e, m.serialise(libcellml::Format::XML));
}

TEST(Model, unsetName) {
    std::string n = "name";
    const std::string eName = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + n + "\"/>";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>";

    libcellml::Model m;
    m.setName(n);
    EXPECT_EQ("name", m.getName());
    EXPECT_EQ(eName, m.serialise(libcellml::Format::XML));

    m.setName("");
    EXPECT_EQ("", m.getName());
    EXPECT_EQ(e, m.serialise(libcellml::Format::XML));
}

TEST(Model, invalidName) {
    std::string in = "invalid name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + in + "\"/>";

    libcellml::Model m;
    m.setName(in);

    EXPECT_EQ("invalid name", m.getName());

    EXPECT_EQ(e, m.serialise(libcellml::Format::XML));
}

TEST(Model, addComponent) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component/></model>";
    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    m.addComponent(c);
    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(Model, addValidNamedComponent) {
    const std::string in = "valid_name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"" + in + "\"/></model>";
    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(Model, addInvalidNamedComponent) {
    const std::string in = "invalid name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"" + in + "\"/></model>";
    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(Model, addTwoNamedComponents) {
    const std::string name1 = "component_1";
    const std::string name2 = "component_2";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"" + name1 + "\"/><component name=\"" + name2 + "\"/></model>";
    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    c1->setName(name1);
    m.addComponent(c1);
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    m.addComponent(c2);
    // once the component is added, we should be able to change the handle to the component and have those changes
    // reflected in the model? Yes we are using shared pointers.
    c2->setName(name2); // so should this give an error? Nope
    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(Model, countComponents) {
    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");

    EXPECT_EQ(0, m.componentCount());

    m.addComponent(c1);
    m.addComponent(c2);
    EXPECT_EQ(2, m.componentCount());
}

TEST(Model, containsComponent) {
    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");

    EXPECT_FALSE(m.containsComponent("child1"));

    m.addComponent(c1);
    m.addComponent(c2);
    EXPECT_TRUE(m.containsComponent("child2"));
}

TEST(Model, removeComponent) {
    const std::string e1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"child2\"/></model>";
    const std::string e2 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"child2\"/><component name=\"child1\"/></model>";
    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    m.addComponent(c1);
    m.addComponent(c2);

    m.removeComponent(0);
    EXPECT_EQ(1, m.componentCount());
    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e1, a);
    EXPECT_THROW(m.removeComponent(1), std::out_of_range);

    m.addComponent(c1);
    m.addComponent(c1);
    // Remove the first occurence of "child1".
    m.removeComponent("child1");
    EXPECT_EQ(2, m.componentCount());
    a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e2, a);
    EXPECT_THROW(m.removeComponent("child3"), std::out_of_range);
}

TEST(Model, getComponentMethods) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"childA\"/></model>";
    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    m.addComponent(c1);

    libcellml::ComponentPtr cA = m.getComponent(0);
    cA->setName("childA");

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);

    // Using const version of overloaded method
    const libcellml::ComponentPtr cB = static_cast<const libcellml::Model>(m).getComponent(0);
    // Can do this as we just have a const pointer
    cB->setName("gus");
    EXPECT_EQ("gus", cB->getName());

    EXPECT_THROW(m.getComponent(4), std::out_of_range);
}

TEST(Model, takeComponentMethods) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>";
    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    m.addComponent(c1);
    m.addComponent(c2);

    libcellml::ComponentPtr c02 = m.takeComponent(1);
    EXPECT_EQ(1, m.componentCount());

    EXPECT_THROW(m.takeComponent(4), std::out_of_range);

    EXPECT_EQ("child2", c02->getName());

    libcellml::ComponentPtr c01 = m.takeComponent("child1");
    EXPECT_EQ(0, m.componentCount());

    EXPECT_EQ("child1", c01->getName());
    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);

    EXPECT_THROW(m.takeComponent("child4"), std::out_of_range);
}

static int count = 0;
class big_and_complicated {
   // lots of complicated code
public:
    int id;
    big_and_complicated()
        : id(count+101)
    {
        count++;
    }

    ~big_and_complicated()
    {
        count--;
    }
};

struct structure
{
    structure()
      : m_data{new big_and_complicated{}}
    {
        std::cout << "structure constructor: " << m_data->id << std::endl;
    }

    structure(const structure& rhs)
        : m_data{new big_and_complicated{}}
    {
        std::cout << "structure copy constructor: " << rhs.m_data->id << std::endl;
        m_data->id = rhs.m_data->id;
    }

    structure(structure&& rhs)
      : m_data(rhs.m_data)
    {
        std::cout << "structure move constructor: " << m_data->id << std::endl;
        rhs.m_data = nullptr;
    }

    structure &operator=(structure r)
    {
        r.swap(*this);
        return *this;
    }

    void swap(structure &r) throw()
    {
        std::swap(this->m_data, r.m_data);
    }

    ~structure()
    {
        std::cout << "structure destructor: ";
        if (m_data) {
            std::cout << m_data->id << std::endl;
        } else {
            std::cout << std::endl;
        }
        delete m_data;
    }

private:
    big_and_complicated* m_data;
};

//TEST(Model, simplified_replace) {
//    std::vector<structure> ss;
//    structure s1, s2, s3;
//    ss.push_back(s1);
//    ss.push_back(s2);
//    ss.erase(ss.begin());
//    ss.insert(ss.begin(), s3);

//}

TEST(Model, replaceComponent) {
    const std::string e_orig = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"child1\"/><component name=\"child2\"/></model>";
    const std::string e_after = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"child1\"/><component name=\"child3\"/></model>";
    const std::string e_post = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"child4\"/><component name=\"child3\"/></model>";

    libcellml::Model m;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c4 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    c3->setName("child3");
    c4->setName("child4");
    m.addComponent(c1);
    m.addComponent(c2);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_orig, a);
    EXPECT_THROW(m.replaceComponent(5, c3), std::out_of_range);

    m.replaceComponent(1, c3);

    a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_after, a);

    EXPECT_THROW(m.replaceComponent("child5", c4), std::out_of_range);

    m.replaceComponent("child1", c4);

    a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_post, a);
}

TEST(Model, constructors) {
    const std::string n = "my_name";
    libcellml::Model m, m1, m2;
    m.setName(n);
    m.addComponent(std::make_shared<libcellml::Component>());
    std::string a = m.serialise(libcellml::Format::XML);

    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"my_name\"><component/></model>";
    EXPECT_EQ(e, a);

    //Testing copy constructor
    libcellml::Model m3(m);
    EXPECT_EQ("my_name", m3.getName());

    // Testing model assignment
    m1 = m;
    EXPECT_EQ("my_name", m.getName());

    // Testing move assignment for model
    m2 = std::move(m1);
    EXPECT_EQ("my_name", m2.getName());
    EXPECT_EQ("", m1.getName());

    // Testing move constructor for component
    libcellml::Model m4 = std::move(m2);
    EXPECT_EQ("my_name", m4.getName());
    EXPECT_EQ("", m2.getName());

}

