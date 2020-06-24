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
    auto parser = libcellml::Parser::create();
    // auto model = parser->parseModel(fileContents());
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
    printIssues(importer);
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
    printIssues(importer);
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
    // This test in intended to show what happens when one model attempts to import a concrete component from a
    // second model, where the second model has unrelated circular dependencies:
    //   - model1 imports component1 from model2
    //   - model2 defines component1
    //   - model2 also defines a circular dependency unrelated to component1

    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve components in model 'circularImport1'. The dependency loop is:\n"
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
