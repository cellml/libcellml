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

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(in);
}

TEST(Coverage, importWithNonHrefXlink)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" xlink:type=\"simple\">\n"
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
    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(e);
    EXPECT_EQ(size_t(0), parser->issueCount());
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

TEST(Annotator, automaticIdsUndefined)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();

    annotator->setModel(model);

    annotator->assignIds(libcellml::CellmlElementType::UNDEFINED);
    EXPECT_TRUE(annotator->hasModel());

    EXPECT_EQ("", model->id());
}

TEST(Coverage, unitsItem)
{
    auto unitsItem = libcellml::UnitsItem::create(nullptr, 0);

    EXPECT_FALSE(unitsItem->isValid());
}

TEST(Coverage, variablePair)
{
    auto v = libcellml::Variable::create("var");
    auto unitsItem1 = libcellml::VariablePair::create(nullptr, v);
    auto unitsItem2 = libcellml::VariablePair::create(v, nullptr);

    EXPECT_FALSE(unitsItem1->isValid());
    EXPECT_FALSE(unitsItem2->isValid());
}

TEST(Coverage, parserBranchesCellml10RelationshipRef)
{
    libcellml::ParserPtr parser = libcellml::Parser::create(false);
    auto model = parser->parseModel(fileContents("coverage/cellml1x_relationshipref.xml"));

    EXPECT_EQ(size_t(0), model->unitsCount());
    EXPECT_EQ(size_t(1), model->componentCount());
}

TEST(Coverage, parserBranchesCMetaIdCellml2)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("coverage/cmeta_id_cellml2.xml"));

    EXPECT_EQ(size_t(0), model->unitsCount());
    EXPECT_EQ(size_t(0), model->componentCount());
}

TEST(Coverage, parserBranchesCellml1XImportComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->setStrict(false);
    auto model = parser->parseModel(fileContents("coverage/cellml1x_import_component.xml"));

    EXPECT_EQ(size_t(0), model->unitsCount());
    EXPECT_EQ(size_t(1), model->componentCount());
}

TEST(Coverage, cellMl20ImportInPermissiveMode)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("importer/component_importer.cellml"));
    auto importer = libcellml::Importer::create(false);

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("importer/"));
    EXPECT_EQ(size_t(0), importer->issueCount());
}

TEST(Coverage, issueRetrieval)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model name=\"bob\" xmlns=\"http://www.cellml.org/cellml/2.0#\"/>\n";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);

    EXPECT_EQ(size_t(0), parser->issueCount());

    EXPECT_EQ(nullptr, parser->error(3));
    EXPECT_EQ(nullptr, parser->warning(4));
}

TEST(Coverage, strictParsingWithEmptyModel)
{
    auto parser = libcellml::Parser::create(false);
    auto model = parser->parseModel("");

    EXPECT_EQ(size_t(1), parser->issueCount());
}

TEST(Coverage, strictParsingWithNonXmlModel)
{
    auto parser = libcellml::Parser::create(false);
    auto model = parser->parseModel("not an xml document.");

    EXPECT_EQ(size_t(2), parser->issueCount());
}

TEST(Coverage, sha1)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();
    auto generatorProfile = libcellml::GeneratorProfile::create();

    generator->setModel(analyserModel);
    generator->setProfile(generatorProfile);

    std::string xs = {};

    for (int i = 0; i < 64; ++i) {
        xs += "x";
        // Note: the x's eventually ensure 100% coverage in our SHA-1 utility.

        generatorProfile->setVoiString(xs);

        generator->implementationCode();
    }
}

TEST(Importer, importingComponentWithCnUnitsThatAreEmpty)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"myModel\">\n"
        "  <units name=\"a\">\n"
        "    <unit units=\"\"/>\n"
        "  </units>\n"
        "   <component name=\"myComponent\">\n"
        "       <variable name=\"a\" units=\"\"/>\n"
        "       <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "           <apply>"
        "             <eq/>\n"
        "             <ci>a</ci>\n"
        "             <cn cellml:bobs=\"\">1</cn>\n"
        "           </apply>\n"
        "       </math>\n"
        "   </component>\n"
        "</model>";

    // Create the model by parsing the string above.
    auto parser = libcellml::Parser::create();
    auto importedModel = parser->parseModel(in);
    auto importer = libcellml::Importer::create();
    auto validator = libcellml::Validator::create();

    auto model = libcellml::Model::create("myModel");
    auto u = libcellml::Units::create("");
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
    model = importer->flattenModel(model);

    validator->validateModel(model);
    EXPECT_EQ(size_t(3), validator->errorCount());
}

TEST(Coverage, analyser)
{
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(nullptr);

    EXPECT_EQ(size_t(1), analyser->issueCount());

    auto analyserModel = analyser->model();

    EXPECT_FALSE(analyserModel->isValid());

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNKNOWN, analyserModel->type());

    EXPECT_EQ(nullptr, analyserModel->voi());

    EXPECT_FALSE(analyserModel->hasExternalVariables());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->states().size());
    EXPECT_EQ(nullptr, analyserModel->state(0));

    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(0), analyserModel->variables().size());
    EXPECT_EQ(nullptr, analyserModel->variable(0));

    EXPECT_EQ(size_t(0), analyserModel->equationCount());
    EXPECT_EQ(size_t(0), analyserModel->equations().size());
    EXPECT_EQ(nullptr, analyserModel->equation(0));

    EXPECT_FALSE(analyserModel->needEqFunction());
    EXPECT_FALSE(analyserModel->needNeqFunction());
    EXPECT_FALSE(analyserModel->needLtFunction());
    EXPECT_FALSE(analyserModel->needLeqFunction());
    EXPECT_FALSE(analyserModel->needGtFunction());
    EXPECT_FALSE(analyserModel->needGeqFunction());
    EXPECT_FALSE(analyserModel->needAndFunction());
    EXPECT_FALSE(analyserModel->needOrFunction());
    EXPECT_FALSE(analyserModel->needXorFunction());
    EXPECT_FALSE(analyserModel->needNotFunction());
    EXPECT_FALSE(analyserModel->needMinFunction());
    EXPECT_FALSE(analyserModel->needMaxFunction());
    EXPECT_FALSE(analyserModel->needSecFunction());
    EXPECT_FALSE(analyserModel->needCscFunction());
    EXPECT_FALSE(analyserModel->needCotFunction());
    EXPECT_FALSE(analyserModel->needSechFunction());
    EXPECT_FALSE(analyserModel->needCschFunction());
    EXPECT_FALSE(analyserModel->needCothFunction());
    EXPECT_FALSE(analyserModel->needAsecFunction());
    EXPECT_FALSE(analyserModel->needAcscFunction());
    EXPECT_FALSE(analyserModel->needAcotFunction());
    EXPECT_FALSE(analyserModel->needAsechFunction());
    EXPECT_FALSE(analyserModel->needAcschFunction());
    EXPECT_FALSE(analyserModel->needAcothFunction());

    auto ast = libcellml::AnalyserEquationAst::create();

    EXPECT_NE(nullptr, ast);

    ast->setType(libcellml::AnalyserEquationAst::Type::ASSIGNMENT);
    ast->setValue({});
    ast->setVariable(libcellml::Variable::create());
    ast->setParent(libcellml::AnalyserEquationAst::create());

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("coverage/analyser.cellml"));

    analyser->analyseModel(model);
}

TEST(Coverage, analyserConvertToInt)
{
    auto analyser = libcellml::Analyser::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("coverage/converttoint.cellml"));

    auto printer = libcellml::Printer::create();

    analyser->analyseModel(model);
}

TEST(Coverage, analyserConvertToDouble)
{
    auto analyser = libcellml::Analyser::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("coverage/converttodouble.cellml"));

    analyser->analyseModel(model);
}

TEST(Coverage, analyserExternalVariable)
{
    auto externalVariable = libcellml::AnalyserExternalVariable::create(nullptr);

    EXPECT_EQ(nullptr, externalVariable->variable());
    EXPECT_EQ(false, externalVariable->addDependency(nullptr));

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto other_model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    externalVariable = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V"));

    externalVariable->addDependency(model->component("membrane")->variable("Cm"));

    EXPECT_EQ(false, externalVariable->removeDependency(nullptr, "membrane", "Cm"));
    EXPECT_EQ(false, externalVariable->removeDependency(model, "not_membrane", "Cm"));
}

TEST(Generator, coverage)
{
    static const std::string EMPTY_STRING;

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("coverage/generator/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(203), analyserModel->variableCount());
    EXPECT_EQ(size_t(197), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->voi()->equation());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->state(0)->equation());
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_NE(nullptr, analyserModel->equation(0)->variable());
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    EXPECT_EQ(nullptr, analyserModel->voi()->initialisingVariable());

    for (size_t i = 0; i < analyserModel->stateCount(); ++i) {
        EXPECT_NE(nullptr, analyserModel->state(i)->initialisingVariable());
    }

    for (size_t i = 0; i < analyserModel->variableCount(); ++i) {
        EXPECT_EQ(i < 7, analyserModel->variable(i)->initialisingVariable() != nullptr);
    }

    EXPECT_EQ(nullptr, generator->model());
    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator->implementationCode());

    generator->setModel(analyserModel);

    EXPECT_EQ(analyserModel, generator->model());
    EXPECT_EQ(fileContents("coverage/generator/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("coverage/generator/model.c"), generator->implementationCode());

    auto profile = generator->profile();

    profile->setInterfaceCreateStatesArrayMethodString("double * createStatesVector();\n");
    profile->setImplementationCreateStatesArrayMethodString("double * createStatesVector()\n"
                                                            "{\n"
                                                            "    return (double *) malloc(STATE_COUNT*sizeof(double));\n"
                                                            "}\n");

    EXPECT_EQ(fileContents("coverage/generator/model.modified.profile.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("coverage/generator/model.modified.profile.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create();

    generator->setProfile(profile);

    profile->setHasInterface(false);

    profile->setXorString("^");
    profile->setHasXorOperator(true);

    profile->setPowerString("^^");
    profile->setSquareString("sqr");
    profile->setHasPowerOperator(true);

    profile->setPiecewiseIfString("piecewise([CONDITION], [IF_STATEMENT]");
    profile->setPiecewiseElseString(", [ELSE_STATEMENT])");
    profile->setHasConditionalOperator(false);

    profile->setInterfaceFileNameString("customheaderfile.h");

    profile->setImplementationHeaderString("#include \"[INTERFACE_FILE_NAME]\"\n");

    profile->setImplementationVersionString("");

    profile->setImplementationLibcellmlVersionString("");

    profile->setImplementationStateCountString("");

    profile->setImplementationVariableCountString("");

    profile->setVariableTypeObjectString(false, false, "");
    profile->setVariableTypeObjectString(false, true, "");
    profile->setVariableTypeObjectString(true, false, "");
    profile->setVariableTypeObjectString(true, true, "");

    profile->setVariableOfIntegrationVariableTypeString("");
    profile->setStateVariableTypeString("");
    profile->setConstantVariableTypeString("");
    profile->setComputedConstantVariableTypeString("");
    profile->setAlgebraicVariableTypeString("");
    profile->setExternalVariableTypeString("");

    profile->setVariableInfoObjectString("");

    profile->setImplementationVoiInfoString("");

    profile->setImplementationStateInfoString("");

    profile->setImplementationVariableInfoString("");

    profile->setVariableInfoEntryString("");

    profile->setImplementationCreateStatesArrayMethodString("");

    profile->setImplementationCreateVariablesArrayMethodString("");

    profile->setImplementationDeleteArrayMethodString("");

    profile->setImplementationComputeVariablesMethodString(false, false, "");
    profile->setImplementationComputeVariablesMethodString(false, true, "");
    profile->setImplementationComputeVariablesMethodString(true, false, "");
    profile->setImplementationComputeVariablesMethodString(true, true, "");

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("coverage/generator/model.out"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create();

    generator->setProfile(profile);

    profile->setHasInterface(true);

    profile->setEqString("eq");
    profile->setNeqString("neq");
    profile->setLtString("lt");
    profile->setLeqString("leq");
    profile->setGtString("gt");
    profile->setGeqString("geq");
    profile->setAndString("and");
    profile->setOrString("or");
    profile->setNotString("not");

    profile->setHasEqOperator(false);
    profile->setHasNeqOperator(false);
    profile->setHasLtOperator(false);
    profile->setHasLeqOperator(false);
    profile->setHasGtOperator(false);
    profile->setHasGeqOperator(false);
    profile->setHasAndOperator(false);
    profile->setHasOrOperator(false);
    profile->setHasNotOperator(false);

    profile->setImplementationHeaderString("");

    profile->setInterfaceVersionString("");
    profile->setImplementationVersionString("");

    profile->setInterfaceLibcellmlVersionString("");
    profile->setImplementationLibcellmlVersionString("");

    profile->setInterfaceStateCountString("");
    profile->setImplementationStateCountString("");

    profile->setInterfaceVariableCountString("");
    profile->setImplementationVariableCountString("");

    profile->setVariableTypeObjectString(false, false, "");
    profile->setVariableTypeObjectString(false, true, "");
    profile->setVariableTypeObjectString(true, false, "");
    profile->setVariableTypeObjectString(true, true, "");

    profile->setVariableOfIntegrationVariableTypeString("");
    profile->setStateVariableTypeString("");
    profile->setConstantVariableTypeString("");
    profile->setComputedConstantVariableTypeString("");
    profile->setAlgebraicVariableTypeString("");
    profile->setExternalVariableTypeString("");

    profile->setVariableInfoObjectString("");

    profile->setInterfaceVoiInfoString("");
    profile->setImplementationVoiInfoString("");

    profile->setInterfaceStateInfoString("");
    profile->setImplementationStateInfoString("");

    profile->setInterfaceVariableInfoString("");
    profile->setImplementationVariableInfoString("");

    profile->setVariableInfoEntryString("");

    EXPECT_EQ(fileContents("coverage/generator/model.interface.out"), generator->interfaceCode());
    EXPECT_EQ(fileContents("coverage/generator/model.implementation.out"), generator->implementationCode());

    profile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("coverage/generator/model.py"), generator->implementationCode());

    profile->setImplementationCreateStatesArrayMethodString("\n"
                                                            "def create_states_vector():\n"
                                                            "    return [nan]*STATE_COUNT\n");

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("coverage/generator/model.modified.profile.py"), generator->implementationCode());

    // Coverage for the case where mLockedProfile is equal to nullptr in
    // Generator::GeneratorImpl::retrieveLockedModelAndProfile().

    generator->setProfile(nullptr);

    generator->implementationCode();

    // Coverage for various profile settings.

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_component")->variable("eqnEq")));

    analyser->analyseModel(model);

    generator->setModel(analyser->model());
    generator->setProfile(profile);

    profile->setAcotFunctionString("");
    profile->setAcothFunctionString("");
    profile->setAcscFunctionString("");
    profile->setAcschFunctionString("");
    profile->setAsecFunctionString("");
    profile->setAsechFunctionString("");
    profile->setCommentString("");
    profile->setCotFunctionString("");
    profile->setCothFunctionString("");
    profile->setCscFunctionString("");
    profile->setCschFunctionString("");
    profile->setExternalVariableMethodTypeDefinitionString(true, "");
    profile->setHasConditionalOperator(true);
    profile->setHasInterface(true);
    profile->setHasPowerOperator(true);
    profile->setHasXorOperator(true);
    profile->setImplementationComputeComputedConstantsMethodString("");
    profile->setImplementationComputeRatesMethodString(true, "");
    profile->setImplementationHeaderString("[INTERFACE_FILE_NAME]");
    profile->setImplementationInitialiseVariablesMethodString(true, true, "");
    profile->setInterfaceFileNameString("");
    profile->setInterfaceHeaderString("");
    profile->setMaxFunctionString("");
    profile->setMinFunctionString("");
    profile->setSecFunctionString("");
    profile->setSechFunctionString("");
    profile->setVariableInfoEntryString("");

    generator->interfaceCode();
    generator->implementationCode();

    profile->setArrayElementSeparatorString("");
    profile->setCommentString("xxx");
    profile->setOriginCommentString("");
    profile->setVariableInfoEntryString("xxx");

    generator->implementationCode();

    profile->setArrayElementSeparatorString("xxx");
    profile->setVariableOfIntegrationVariableTypeString("");

    generator->implementationCode();

    profile->setStateVariableTypeString("");
    profile->setVariableOfIntegrationVariableTypeString("xxx");

    generator->implementationCode();

    profile->setConstantVariableTypeString("");
    profile->setStateVariableTypeString("xxx");

    generator->implementationCode();

    profile->setComputedConstantVariableTypeString("");
    profile->setConstantVariableTypeString("xxx");

    generator->implementationCode();

    profile->setComputedConstantVariableTypeString("xxx");
    profile->setAlgebraicVariableTypeString("");

    generator->implementationCode();

    profile->setAlgebraicVariableTypeString("xxx");
    profile->setExternalVariableTypeString("");

    generator->implementationCode();

    profile->setHasXorOperator(false);
    profile->setXorFunctionString("");

    generator->implementationCode();
}

TEST(Importer, unitsUsedByComponentMathNotFoundInModel)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <apply>"
        "    <eq/>\n"
        "    <ci>a</ci>\n"
        "    <cn cellml:units=\"bobs\">1</cn>\n"
        "  </apply>\n"
        "</math>\n";

    auto variable = libcellml::Variable::create("a");
    auto uBobs = libcellml::Units::create("bobs");
    uBobs->addUnit("daves");
    variable->setUnits(uBobs);
    auto component = libcellml::Component::create("myComponent");
    component->addVariable(variable);
    component->appendMath(math);
    auto importedModel = libcellml::Model::create("myImportedModel");
    importedModel->addComponent(component);

    auto importer = libcellml::Importer::create();
    auto validator = libcellml::Validator::create();

    importer->addModel(importedModel, "myImportedModel.cellml");

    auto model = libcellml::Model::create("myModel");
    auto u = libcellml::Units::create("meter");
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
    model = importer->flattenModel(model);

    validator->validateModel(model);
    EXPECT_EQ(size_t(1), validator->errorCount());
}

TEST(Importer, notMathMLMathNodesInComponentMath)
{
    const std::string math =
        "<notmath xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <apply>"
        "    <eq/>\n"
        "    <ci>a</ci>\n"
        "    <cn cellml:units=\"bobs\">1</cn>\n"
        "  </apply>\n"
        "</notmath>\n";

    auto variable = libcellml::Variable::create("a");
    auto uBobs = libcellml::Units::create("bobs");
    uBobs->addUnit("daves");
    variable->setUnits(uBobs);
    auto component = libcellml::Component::create("myComponent");
    component->addVariable(variable);
    component->appendMath(math);
    auto importedModel = libcellml::Model::create("myImportedModel");
    importedModel->addComponent(component);

    auto importer = libcellml::Importer::create();
    auto validator = libcellml::Validator::create();

    importer->addModel(importedModel, "myImportedModel.cellml");

    auto model = libcellml::Model::create("myModel");
    auto u = libcellml::Units::create("meter");
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
    model = importer->flattenModel(model);

    validator->validateModel(model);
    EXPECT_EQ(size_t(2), validator->errorCount());
}
