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

TEST(AnnotatorCoverage, automaticIdsUndefined)
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
    auto units = libcellml::Units::create("units");
    units->addUnit("second");

    auto unitsItemValid = libcellml::UnitsItem::create(units, 0);
    auto unitsItemInvalid = libcellml::UnitsItem::create(nullptr, 0);

    EXPECT_TRUE(unitsItemValid->isValid());
    EXPECT_FALSE(unitsItemInvalid->isValid());
}

TEST(Coverage, variablePair)
{
    auto v = libcellml::Variable::create("var");
    auto variablePair1 = libcellml::VariablePair::create(nullptr, v);
    auto variablePair2 = libcellml::VariablePair::create(v, nullptr);
    auto variablePair3 = libcellml::VariablePair::create(v, v);

    EXPECT_FALSE(variablePair1->isValid());
    EXPECT_FALSE(variablePair2->isValid());
    EXPECT_TRUE(variablePair3->isValid());
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

TEST(ImporterCoverage, importingComponentWithCnUnitsThatAreEmpty)
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
    EXPECT_EQ("unknown", libcellml::AnalyserModel::typeAsString(analyserModel->type()));

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

void checkAstTypeAsString(const libcellml::AnalyserEquationAstPtr &ast)
{
    if (ast != nullptr) {
        libcellml::AnalyserEquationAst::typeAsString(ast->type());

        checkAstTypeAsString(ast->leftChild());
        checkAstTypeAsString(ast->rightChild());
    }
}

TEST(Coverage, generator)
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
    EXPECT_EQ("ode", libcellml::AnalyserModel::typeAsString(analyserModel->type()));

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

    for (const auto &equation : analyserModel->equations()) {
        checkAstTypeAsString(equation->ast());
    }

    auto generator = libcellml::Generator::create();

    EXPECT_EQ(nullptr, analyserModel->voi()->initialisingVariable());

    for (size_t i = 0; i < analyserModel->stateCount(); ++i) {
        EXPECT_NE(nullptr, analyserModel->state(i)->initialisingVariable());
    }

    for (size_t i = 0; i < analyserModel->variableCount(); ++i) {
        EXPECT_EQ((i == 1) || (i == 2) || (i == 6) || (i == 18) || (i == 177) || (i == 178) || (i == 180),
                  analyserModel->variable(i)->initialisingVariable() != nullptr);
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

    // Coverage for the case where mProfile is equal to nullptr in Generator.

    generator->setProfile(nullptr);

    generator->interfaceCode();
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

libcellml::ValidatorPtr validateMathPreparation(const std::string &math)
{
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
    return validator;
}

TEST(CoverageValidator, unitsUsedByComponentMathNotFoundInModel)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <apply>"
        "    <eq/>\n"
        "    <ci>a</ci>\n"
        "    <cn cellml:units=\"bobs\">1</cn>\n"
        "  </apply>\n"
        "</math>\n";

    auto validator = validateMathPreparation(math);

    EXPECT_EQ(size_t(1), validator->errorCount());
    EXPECT_EQ("Units reference 'daves' in units 'bobs' is not a valid reference to a local units or a standard unit type.", validator->error(0)->description());
}

TEST(CoverageValidator, notMathMLMathNodesInComponentMath)
{
    const std::string math =
        "<notmath xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <apply>"
        "    <eq/>\n"
        "    <ci>a</ci>\n"
        "    <cn cellml:units=\"bobs\">1</cn>\n"
        "  </apply>\n"
        "</notmath>\n";

    auto validator = validateMathPreparation(math);

    EXPECT_EQ(size_t(2), validator->errorCount());
    EXPECT_EQ("Math root node is of invalid type 'notmath' on component 'c'. A valid math root node should be of type 'math'.", validator->error(0)->description());
    EXPECT_EQ("Units reference 'daves' in units 'bobs' is not a valid reference to a local units or a standard unit type.", validator->error(1)->description());
}

TEST(CoverageValidator, degreeElementWithOneSibling)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <root/>\n"
        "    <degree><ci>n</ci></degree>\n"
        "  </apply>\n"
        "</math>\n";

    auto parser = libcellml::Parser::create();
    auto model = libcellml::Model::create("degree");

    auto component = libcellml::Component::create("c");
    auto variable = libcellml::Variable::create("n");
    variable->setUnits("second");
    component->addVariable(variable);
    component->appendMath(math);

    model->addComponent(component);

    auto validator = libcellml::Validator::create();

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->errorCount());
}

TEST(CoverageValidator, invalidXmlIds)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("coverage/invalidxmlids.cellml"));

    auto validator = libcellml::Validator::create();

    validator->validateModel(model);
    EXPECT_EQ(size_t(1), validator->errorCount());
    EXPECT_EQ("Units 'bob8' does not have a valid 'id' attribute, '\xF3\xBF\xBF\xBFid'.", validator->error(0)->description());
}

TEST(CoverageValidator, componentMathWithRepeatedVariableNames)
{
    const std::vector<std::string> expectedIssues = {
        "Component 'componentName' contains multiple variables with the name 'A'. Valid variable names must be unique to their component.",
        "MathML ci element has the child text 'C' which does not correspond with any variable names present in component 'componentName'.",
        "Math has a 'ci' element with no identifier as a child.",
    };

    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>C</ci>\n"
        "<!-- valid comment in math -->\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>A</ci>\n"
        "      <ci id=\"ciid\" />\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("A");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);
    EXPECT_EQ(size_t(3), v->issueCount());
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(CoverageAnnotator, crossComponentConnectionAndMappingIds)
{
    auto model = libcellml::Model::create("model");

    auto component1 = libcellml::Component::create("component1");
    auto component2 = libcellml::Component::create("component2");
    auto component3 = libcellml::Component::create("component3");

    auto variable1 = libcellml::Variable::create("variable1");
    auto variable2 = libcellml::Variable::create("variable2");
    auto variable3 = libcellml::Variable::create("variable3");

    model->addComponent(component1);
    model->addComponent(component2);
    model->addComponent(component3);

    component1->addVariable(variable1);
    component2->addVariable(variable2);
    component3->addVariable(variable3);

    libcellml::Variable::addEquivalence(variable1, variable2);
    libcellml::Variable::addEquivalence(variable1, variable3);

    libcellml::Variable::setEquivalenceMappingId(variable1, variable2, "mapping_id");
    libcellml::Variable::setEquivalenceMappingId(variable1, variable3, "mapping_id");

    libcellml::Variable::setEquivalenceConnectionId(variable1, variable2, "connection_id");
    libcellml::Variable::setEquivalenceConnectionId(variable1, variable3, "connection_id");

    auto annotator = libcellml::Annotator::create();

    annotator->setModel(model);

    EXPECT_EQ(size_t(2), annotator->itemCount("mapping_id"));
    EXPECT_EQ(size_t(2), annotator->itemCount("connection_id"));
}
