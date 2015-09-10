#include "gtest/gtest.h"

#include <libcellml>

/**
 * @todo Need a way to have resources which can be used in tests, such as the
 * source models used in these tests. But I guess not until we start validating
 * models...
 */

/*
 * Suggestion #1: adding more attributes to the existing component class.
 *
 * Problems/issues:
 * - how to handle importing multiple components/units from a single model instance?
 * - would serialising the component result in the full import construct?
 */
TEST(ComponentImport, suggestion01) {
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

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceModel("some-other-model.xml");
    importedComponent->setSourceComponent("a_component_in_that_model");
    m.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

/*
 * Suggestion #2: an explicit import class
 *
 * Problems/issues:
 * - introduces a class Andre really doesn't want to see in the API :)
 * - a special class of component
 */
TEST(ComponentImport, suggestion02) {
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

    libcellml::Import i;
    i.setSource("some-other-model.xml");
    m.addImport(i);

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceComponent("a_component_in_that_model");
    i.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

/*
 * Suggestion #3: adding more attributes to the existing component class attempt 2. Now using a model as the actual source, so that we can reuse it for more imports...
 *
 * Problems/issues:
 * - would serialising the component result in the full import construct?
 */
TEST(ComponentImport, suggestion03) {
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
    libcellml::Model src("some-other-model");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceModel(src);
    importedComponent->setSourceComponent("a_component_in_that_model");
    m.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

