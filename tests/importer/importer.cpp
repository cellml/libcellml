/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License->
You may obtain a copy of the License at

    http://www.apache->org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License->
*/

#include "gtest/gtest.h"

#include <libcellml>

#include "test_utils.h"

TEST(Importer, create)
{
    auto importer = libcellml::Importer::create();
}

TEST(Importer, noWarningForkedImport)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("resolveimports/forkedImport.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("resolveimports/"));
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(Importer, noWarningDiamondImport)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("resolveimports/diamond.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("resolveimports/"));
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(Importer, warningCircularImportReferencesComponent)
{
    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve components in model 'circularImport1'. The dependency loop is:\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml',\n"
                                 "    component 'c2' imports 'c3' from 'circularImport_3.cellml',\n"
                                 "    component 'c3' imports 'i_am_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml'.";
    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("resolveimports/circularImport_1.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());
    importer->resolveImports(model, resourcePath("resolveimports/"));

    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(size_t(1), importer->warningCount());
    EXPECT_EQ(warningMessage, importer->warning(0)->description());
}

TEST(Importer, warningCircularImportReferencesUnits)
{
    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve units in model 'circularImport1'. The dependency loop is:\n"
                                 "    units 'i_am_cyclic' imports 'u2' from 'circularUnits_2.cellml',\n"
                                 "    units 'u2' imports 'u3' from 'circularUnits_3.cellml',\n"
                                 "    units 'u3' imports 'i_am_cyclic' from 'circularUnits_1.cellml',\n"
                                 "    units 'i_am_cyclic' imports 'u2' from 'circularUnits_2.cellml'.";
    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("resolveimports/circularUnits_1.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());
    importer->resolveImports(model, resourcePath("resolveimports/"));
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(size_t(1), importer->warningCount());
    EXPECT_EQ(warningMessage, importer->warning(0)->description());
}

TEST(Importer, warningUnrequiredCircularDependencyComponent)
{
    // This test is intended to show what happens when one model attempts to import a concrete component from a
    // second model, where the second model has unrelated circular dependencies:
    //   - model1 imports component1 from model2
    //   - model2 defines component1
    //   - model2 also defines a circular dependency unrelated to component1

    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve components in model 'circularImport3'. The dependency loop is:\n"
                                 "    component 'c' imports 'i_am_ok_but_my_sibling_is_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml',\n"
                                 "    component 'c2' imports 'c3' from 'circularImport_3.cellml',\n"
                                 "    component 'c3' imports 'i_am_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml'.";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("resolveimports/master1.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());
    importer->resolveImports(model, resourcePath("resolveimports/"));
    EXPECT_FALSE(model->hasUnresolvedImports());
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(size_t(1), importer->warningCount());
    EXPECT_EQ(warningMessage, importer->warning(0)->description());
}

TEST(Importer, missingUnitsFromImportOfCnTerms)
{
    // This test is intended to show that parsing a model and importing
    // it have the same end result.  Previously (see #519) any units
    // defined in the model but not used by a variable (ie: only used by <cn> tags)
    // were not imported.
    auto validator = libcellml::Validator::create();
    auto model = libcellml::Model::create("model_from_imports");
    auto c = libcellml::Component::create("c");
    auto importer = libcellml::Importer::create();

    auto imp = libcellml::ImportSource::create();
    imp->setUrl("units_in_cn.cellml");

    c->setImportReference("myComponent");
    c->setImportSource(imp);
    model->addComponent(c);

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flatten(model);

    // Confirm that the bug reported in #519 wherein units used solely by <cn> items
    // in imported components were not being imported is now fixed.
    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->errorCount());
    EXPECT_EQ(size_t(0), importer->issueCount());
}

TEST(Model, importingComponentWithCnUnitsThatAreAlreadyDefinedInImportingModel)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"myModel\">\n"
        "  <units name=\"myUnitsThatIUse\">\n"
        "    <unit units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"myUnitsThatIUse_1\">\n"
        "    <unit units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"a\" units=\"second\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>a</ci>\n"
        "        <cn cellml:units=\"myUnitsThatIUse_1\">1</cn>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";

    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"myModel\">\n"
        "  <units name=\"myUnitsThatIUse\">\n"
        "    <unit units=\"second\"/>\n"
        "  </units>\n"
        "   <component name=\"myComponent\">\n"
        "       <variable name=\"a\" units=\"second\"/>\n"
        "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "           <apply>"
        "             <eq/>\n"
        "             <ci>a</ci>\n"
        "             <cn cellml:units=\"myUnitsThatIUse\">1</cn>\n"
        "           </apply>\n"
        "       </math>\n"
        "   </component>\n"
        "</model>";

    // Create the model by parsing the string above.
    auto parser = libcellml::Parser::create();
    auto importedModel = parser->parseModel(in);

    auto validator = libcellml::Validator::create();
    auto importer = libcellml::Importer::create();

    // No problems with the imported model.
    validator->validateModel(importedModel);
    EXPECT_EQ(size_t(0), validator->errorCount());

    // The model myModel already has myUnitsThatIUse defined.
    auto model = libcellml::Model::create("myModel");
    auto u = libcellml::Units::create("myUnitsThatIUse");
    u->addUnit("metre");
    model->addUnits(u);

    auto c = libcellml::Component::create("c");

    auto importSource = libcellml::ImportSource::create();
    importSource->setUrl("not_required_resolving_import_manually");
    importSource->setModel(importedModel);

    c->setImportReference("myComponent");
    c->setImportSource(importSource);
    model->addComponent(c);

    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flatten(model);

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->errorCount());

    // I would expect that the name of the cn elements units would need
    // to change as the importing model already has units of that name.
    auto printer = libcellml::Printer::create();
    EXPECT_EQ(e, printer->printModel(model));
}

TEST(Model, importUnitsDuplicated)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model\">\n"
        "  <units name=\"millisecond\">\n"
        "    <unit prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <units name=\"per_millisecond\">\n"
        "    <unit exponent=\"-1\" units=\"millisecond\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"alpha_n\" units=\"per_millisecond\" initial_value=\"1\"/>\n"
        "    <variable name=\"beta_n\" units=\"per_millisecond\" initial_value=\"2\"/>\n"
        "  </component>\n"
        "</model>\n";

    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"myImportedModel\">\n"
        "  <units name=\"millisecond\">\n"
        "    <unit prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <units name=\"per_millisecond\">\n"
        "    <unit exponent=\"-1\" units=\"millisecond\"/>\n"
        "  </units>\n"
        "  <component name=\"myComponent\">\n"
        "    <variable name=\"alpha_n\" units=\"per_millisecond\" initial_value=\"1\"/>\n"
        "    <variable name=\"beta_n\" units=\"per_millisecond\" initial_value=\"2\"/>\n"
        "  </component>\n"
        "</model>";

    // Create the model by parsing the string above.
    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto importedModel = parser->parseModel(in);

    auto validator = libcellml::Validator::create();
    validator->validateModel(importedModel);
    EXPECT_EQ(size_t(0), validator->errorCount());

    auto model = libcellml::Model::create("model");
    auto c = libcellml::Component::create("c");

    auto importSource = libcellml::ImportSource::create();
    importSource->setUrl("not_required_resolving_import_manually");
    importSource->setModel(importedModel);

    c->setImportReference("myComponent");
    c->setImportSource(importSource);
    model->addComponent(c);

    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flatten(model);

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->errorCount());

    auto printer = libcellml::Printer::create();
    EXPECT_EQ(e, printer->printModel(model));
}

TEST(Importer, duplicatesImportedOnceOnly)
{
    std::string in = "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
                     "<model name=\"forked_import\" xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
                     "  <import xlink:href=\"prong.cellml\">\n"
                     "    <component name=\"left\" component_ref=\"component1\" />\n"
                     "  </import>\n"
                     "  <import xlink:href=\"prong.cellml\">\n"
                     "    <component name=\"right\" component_ref=\"component1\" />\n"
                     "  </import>\n"
                     "  <import xlink:href=\"prong.cellml\">\n"
                     "    <component name=\"centre\" component_ref=\"component1\" />\n"
                     "  </import>\n"
                     "</model>";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto importer = libcellml::Importer::create();

    importer->resolveImports(model, resourcePath("resolveimports/"));
    EXPECT_EQ(size_t(3), model->componentCount()); // Three imported components ...
    EXPECT_EQ(size_t(1), importer->libraryCount()); // ... but just one imported model.
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(Importer, accessImportedModelLibrary)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("resolveimports/diamond.cellml"));
    auto importer = libcellml::Importer::create();
    auto printer = libcellml::Printer::create();

    importer->resolveImports(model, resourcePath("resolveimports/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    // Library should contain left, right, and one instance (not two) of the point.
    EXPECT_EQ(size_t(3), importer->libraryCount());

    auto left = importer->library(resourcePath("resolveimports/diamond_left.cellml"));
    auto right = importer->library(resourcePath("resolveimports/diamond_right.cellml"));
    auto point = importer->library(resourcePath("resolveimports/diamond_point.cellml"));

    // Access library items by their URL.
    EXPECT_EQ(fileContents("resolveimports/diamond_left.cellml"), printer->printModel(left));
    EXPECT_EQ(fileContents("resolveimports/diamond_right.cellml"), printer->printModel(right));
    EXPECT_EQ(fileContents("resolveimports/diamond_point.cellml"), printer->printModel(point));
}

TEST(Importer, multipleModelResolution)
{
    // This test is intended to show how the Importer class can hold multitple imported models in its library, and that
    // these can be used to resolve the imports of more than one importing model.
    // The example give has three models A, B, C, each importing the same four components, a, b, c, d from a
    // fourth model D. We expect the that model D is parsed and instantiated just once, rather than 12 times.

    auto parser = libcellml::Parser::create();
    auto modelA = parser->parseModel(fileContents("resolveimports/generic.cellml"));
    auto modelB = parser->parseModel(fileContents("resolveimports/generic.cellml"));
    auto modelC = parser->parseModel(fileContents("resolveimports/generic.cellml"));

    // ModelD will be imorted into the library as it's included as a dependency in the models here.
    // Passing in one of the models for resolution will load modelD into the library.
    auto importer = libcellml::Importer::create();
    importer->resolveImports(modelA, resourcePath("resolveimports/"));

    EXPECT_EQ(size_t(1), importer->libraryCount());

    // Now resolve the other models and expect the library contents to be unchanged.
    importer->resolveImports(modelB, resourcePath("resolveimports/"));
    importer->resolveImports(modelC, resourcePath("resolveimports/"));

    EXPECT_EQ(size_t(1), importer->libraryCount());
}

TEST(Importer, addModelToLibrary)
{
    // This test shows how a model instance can be manually added to the import library by the user,
    // and will be used to resolve imports, rather than from an external file/url.
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("resolveimports/generic_no_source.cellml"));
    auto importer = libcellml::Importer::create();

    auto sourceModel = libcellml::Model::create("source");
    sourceModel->addComponent(libcellml::Component::create("a"));
    sourceModel->addComponent(libcellml::Component::create("b"));
    sourceModel->addComponent(libcellml::Component::create("c"));
    sourceModel->addComponent(libcellml::Component::create("d"));

    // Add a model manually to the library, including the URL that it will replace in future imports.
    EXPECT_TRUE(importer->addModel(sourceModel, "i_dont_exist.cellml"));

    // Can't add to the same url key more than once.
    EXPECT_FALSE(importer->addModel(sourceModel, "i_dont_exist.cellml"));

    importer->resolveImports(model, "");

    EXPECT_EQ(size_t(0), importer->issueCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(Importer, replaceModel)
{
    // This test shows how a model instance can be manually added to the import library by the user,
    // and will be used to resolve imports, rather than from an external file/url.
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("resolveimports/generic_no_source.cellml"));
    auto importer = libcellml::Importer::create();

    auto wrongSourceModel = libcellml::Model::create("wrong");

    auto rightSourceModel = libcellml::Model::create("source");
    rightSourceModel->addComponent(libcellml::Component::create("a"));
    rightSourceModel->addComponent(libcellml::Component::create("b"));
    rightSourceModel->addComponent(libcellml::Component::create("c"));
    rightSourceModel->addComponent(libcellml::Component::create("d"));

    // Add a model manually to the library, including the URL that it will replace in future imports.
    EXPECT_TRUE(importer->addModel(wrongSourceModel, "i_dont_exist.cellml"));
    // Can't add to the same url key more than once.
    EXPECT_FALSE(importer->addModel(rightSourceModel, "i_dont_exist.cellml"));

    // Use replaceModel instead.
    EXPECT_FALSE(importer->replaceModel(rightSourceModel, "not_in_library"));
    EXPECT_TRUE(importer->replaceModel(rightSourceModel, "i_dont_exist.cellml"));

    importer->resolveImports(model, "");

    EXPECT_EQ(size_t(0), importer->issueCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(Importer, getNonexistentModel)
{
    // For coverage.
    auto importer = libcellml::Importer::create();
    auto model = libcellml::Model::create("model");
    importer->addModel(model, "howdy");
    EXPECT_EQ(nullptr, importer->library("bonjour"));
}

TEST(Importer, getListOfDependencies)
{
    // This test shows how a model can be interrogated to return a list of its dependencies/urls.
    // These then become the url "keys" that must be supplied to the importer, if their actual location
    // should not be used or is inaccessible.

    // Note that in order to resolve the dependencies further than the first generation, the models will
    // need to be instantiated and saved anyway.  The external dependencies are those which, during the
    // resolution for this model, were sourced from locations outside the library.  They will have since
    // been saved to the importer library, and subsequent calls to resolveImports for those same imported
    // files will not change the dependencies list.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("resolveimports/diamond.cellml"));
    auto importer = libcellml::Importer::create();

    importer->resolveImports(model, resourcePath("resolveimports/"));

    EXPECT_EQ(size_t(3), importer->externalDependencyCount());
    for (size_t e = 0; e < importer->externalDependencyCount(); ++e) {
        auto info = importer->externalDependency(e);
        EXPECT_NE(nullptr, importer->library(info.first));
    }
    std::pair<std::string, std::string> empty;
    EXPECT_EQ(empty, importer->externalDependency(999));
}
