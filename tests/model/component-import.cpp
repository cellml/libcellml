#include "gtest/gtest.h"

#include <libcellml>

/**
 * @todo Need a way to have resources which can be used in tests, such as the
 * source models used in these tests. But I guess not until we start validating
 * models...
 *
 * While this is needed eventually, for now we are not instantiating the imports
 * so don't need it just yet.
 */

TEST(ComponentImport, singleImport01) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<component component_ref=\"a_component_in_that_model\" "
                              "name=\"component_in_this_model\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::Import imp("some-other-model.xml");
    m.addImport(imp);
    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceComponent("a_component_in_that_model");
    imp.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(ComponentImport, singleImport02) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<component component_ref=\"a_component_in_that_model\" "
                              "name=\"component_in_this_model\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::Import imp("some-other-model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceComponent(imp, "a_component_in_that_model");
    m.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(ComponentImport, multipleImport02) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"cc1\" "
                               "name=\"c1"/>"
                    "<component component_ref=\"cc2\" "
                               "name=\"c2\"/>"
               "</import>"
                "<import xlink:href=\"some-other-model.xml\" "
                        "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                     "<component component_ref=\"cc1\" "
                                "name=\"c3\"/>"
                "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::Import imp("some-other-model.xml");
    m.addImport(imp);
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    c1->setName("c1");
    c1->setSourceComponent("cc1");
    imp.addComponent(c1);
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c2->setName("c2");
    c2->setSourceComponent("cc2");
    imp.addComponent(c2);

    libcellml::Import imp2("some-other-model.xml");
    m.addImport(imp2);
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    c3->setName("c3");
    c3->setSourceComponent("cc1");
    imp.addComponent(c3);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(ComponentImport, multipleImport01) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"cc1\" "
                               "name=\"c1"/>"
                    "<component component_ref=\"cc2\" "
                               "name=\"c2\"/>"
               "</import>"
                "<import xlink:href=\"some-other-model.xml\" "
                        "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                     "<component component_ref=\"cc1\" "
                                "name=\"c3\"/>"
                "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::Import imp("some-other-model.xml");
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    c1->setName("c1");
    c1->setSourceComponent(imp, "cc1");
    m.addComponent(c1);
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c2->setName("c2");
    c2->setSourceComponent(imp, "cc2");
    m.addComponent(c2);

    libcellml::Import imp2("some-other-model.xml");
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    c3->setName("c3");
    c3->setSourceComponent(imp2, "cc1");
    m.addComponent(c3);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}
