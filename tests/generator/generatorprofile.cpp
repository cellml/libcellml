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

#ifdef _WIN32
#    define _USE_MATH_DEFINES
#endif

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

#include <cmath>

std::string convertToString(double value)
{
    std::ostringstream strs;
    strs << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return strs.str();
}

TEST(GeneratorProfile, defaultGeneralValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ(libcellml::GeneratorProfile::Profile::C, generatorProfile->profile());
    EXPECT_EQ("c", libcellml::GeneratorProfile::profileAsString(generatorProfile->profile()));

    EXPECT_EQ(true, generatorProfile->hasInterface());
}

TEST(GeneratorProfile, defaultRelationalAndLogicalOperatorValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ(" = ", generatorProfile->equalityString());
    EXPECT_EQ(" == ", generatorProfile->eqString());
    EXPECT_EQ(" != ", generatorProfile->neqString());
    EXPECT_EQ(" < ", generatorProfile->ltString());
    EXPECT_EQ(" <= ", generatorProfile->leqString());
    EXPECT_EQ(" > ", generatorProfile->gtString());
    EXPECT_EQ(" >= ", generatorProfile->geqString());
    EXPECT_EQ(" && ", generatorProfile->andString());
    EXPECT_EQ(" || ", generatorProfile->orString());
    EXPECT_EQ("xor", generatorProfile->xorString());
    EXPECT_EQ("!", generatorProfile->notString());

    EXPECT_EQ(true, generatorProfile->hasEqOperator());
    EXPECT_EQ(true, generatorProfile->hasNeqOperator());
    EXPECT_EQ(true, generatorProfile->hasLtOperator());
    EXPECT_EQ(true, generatorProfile->hasLeqOperator());
    EXPECT_EQ(true, generatorProfile->hasGtOperator());
    EXPECT_EQ(true, generatorProfile->hasGeqOperator());
    EXPECT_EQ(true, generatorProfile->hasAndOperator());
    EXPECT_EQ(true, generatorProfile->hasOrOperator());
    EXPECT_EQ(false, generatorProfile->hasXorOperator());
    EXPECT_EQ(true, generatorProfile->hasNotOperator());
}

TEST(GeneratorProfile, defaultArithmeticOperatorValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("+", generatorProfile->plusString());
    EXPECT_EQ("-", generatorProfile->minusString());
    EXPECT_EQ("*", generatorProfile->timesString());
    EXPECT_EQ("/", generatorProfile->divideString());
    EXPECT_EQ("pow", generatorProfile->powerString());
    EXPECT_EQ("sqrt", generatorProfile->squareRootString());
    EXPECT_EQ("", generatorProfile->squareString());
    EXPECT_EQ("fabs", generatorProfile->absoluteValueString());
    EXPECT_EQ("exp", generatorProfile->exponentialString());
    EXPECT_EQ("log", generatorProfile->naturalLogarithmString());
    EXPECT_EQ("log10", generatorProfile->commonLogarithmString());
    EXPECT_EQ("ceil", generatorProfile->ceilingString());
    EXPECT_EQ("floor", generatorProfile->floorString());
    EXPECT_EQ("min", generatorProfile->minString());
    EXPECT_EQ("max", generatorProfile->maxString());
    EXPECT_EQ("fmod", generatorProfile->remString());

    EXPECT_EQ(false, generatorProfile->hasPowerOperator());
}

TEST(GeneratorProfile, defaultTrigonometricOperatorValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("sin", generatorProfile->sinString());
    EXPECT_EQ("cos", generatorProfile->cosString());
    EXPECT_EQ("tan", generatorProfile->tanString());
    EXPECT_EQ("sec", generatorProfile->secString());
    EXPECT_EQ("csc", generatorProfile->cscString());
    EXPECT_EQ("cot", generatorProfile->cotString());
    EXPECT_EQ("sinh", generatorProfile->sinhString());
    EXPECT_EQ("cosh", generatorProfile->coshString());
    EXPECT_EQ("tanh", generatorProfile->tanhString());
    EXPECT_EQ("sech", generatorProfile->sechString());
    EXPECT_EQ("csch", generatorProfile->cschString());
    EXPECT_EQ("coth", generatorProfile->cothString());
    EXPECT_EQ("asin", generatorProfile->asinString());
    EXPECT_EQ("acos", generatorProfile->acosString());
    EXPECT_EQ("atan", generatorProfile->atanString());
    EXPECT_EQ("asec", generatorProfile->asecString());
    EXPECT_EQ("acsc", generatorProfile->acscString());
    EXPECT_EQ("acot", generatorProfile->acotString());
    EXPECT_EQ("asinh", generatorProfile->asinhString());
    EXPECT_EQ("acosh", generatorProfile->acoshString());
    EXPECT_EQ("atanh", generatorProfile->atanhString());
    EXPECT_EQ("asech", generatorProfile->asechString());
    EXPECT_EQ("acsch", generatorProfile->acschString());
    EXPECT_EQ("acoth", generatorProfile->acothString());
}

TEST(GeneratorProfile, defaultPiecewiseStatementValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("([CONDITION])?[IF_STATEMENT]", generatorProfile->conditionalOperatorIfString());
    EXPECT_EQ(":[ELSE_STATEMENT]", generatorProfile->conditionalOperatorElseString());
    EXPECT_EQ("", generatorProfile->piecewiseIfString());
    EXPECT_EQ("", generatorProfile->piecewiseElseString());

    EXPECT_EQ(true, generatorProfile->hasConditionalOperator());
}

TEST(GeneratorProfile, defaultConstantValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("1.0", generatorProfile->trueString());
    EXPECT_EQ("0.0", generatorProfile->falseString());
    EXPECT_EQ(convertToString(exp(1.0)), generatorProfile->eString());
    EXPECT_EQ(convertToString(M_PI), generatorProfile->piString());
    EXPECT_EQ("INFINITY", generatorProfile->infString());
    EXPECT_EQ("NAN", generatorProfile->nanString());
}

TEST(GeneratorProfile, defaultArithmeticFunctionValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("", generatorProfile->eqFunctionString());
    EXPECT_EQ("", generatorProfile->neqFunctionString());
    EXPECT_EQ("", generatorProfile->ltFunctionString());
    EXPECT_EQ("", generatorProfile->leqFunctionString());
    EXPECT_EQ("", generatorProfile->gtFunctionString());
    EXPECT_EQ("", generatorProfile->geqFunctionString());
    EXPECT_EQ("", generatorProfile->andFunctionString());
    EXPECT_EQ("", generatorProfile->orFunctionString());
    EXPECT_EQ("double xor(double x, double y)\n"
              "{\n"
              "    return (x != 0.0) ^ (y != 0.0);\n"
              "}\n",
              generatorProfile->xorFunctionString());
    EXPECT_EQ("", generatorProfile->notFunctionString());
    EXPECT_EQ("double min(double x, double y)\n"
              "{\n"
              "    return (x < y)?x:y;\n"
              "}\n",
              generatorProfile->minFunctionString());
    EXPECT_EQ("double max(double x, double y)\n"
              "{\n"
              "    return (x > y)?x:y;\n"
              "}\n",
              generatorProfile->maxFunctionString());
}

TEST(GeneratorProfile, defaultTrigonometricFunctionValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("double sec(double x)\n"
              "{\n"
              "    return 1.0/cos(x);\n"
              "}\n",
              generatorProfile->secFunctionString());
    EXPECT_EQ("double csc(double x)\n"
              "{\n"
              "    return 1.0/sin(x);\n"
              "}\n",
              generatorProfile->cscFunctionString());
    EXPECT_EQ("double cot(double x)\n"
              "{\n"
              "    return 1.0/tan(x);\n"
              "}\n",
              generatorProfile->cotFunctionString());
    EXPECT_EQ("double sech(double x)\n"
              "{\n"
              "    return 1.0/cosh(x);\n"
              "}\n",
              generatorProfile->sechFunctionString());
    EXPECT_EQ("double csch(double x)\n"
              "{\n"
              "    return 1.0/sinh(x);\n"
              "}\n",
              generatorProfile->cschFunctionString());
    EXPECT_EQ("double coth(double x)\n"
              "{\n"
              "    return 1.0/tanh(x);\n"
              "}\n",
              generatorProfile->cothFunctionString());
    EXPECT_EQ("double asec(double x)\n"
              "{\n"
              "    return acos(1.0/x);\n"
              "}\n",
              generatorProfile->asecFunctionString());
    EXPECT_EQ("double acsc(double x)\n"
              "{\n"
              "    return asin(1.0/x);\n"
              "}\n",
              generatorProfile->acscFunctionString());
    EXPECT_EQ("double acot(double x)\n"
              "{\n"
              "    return atan(1.0/x);\n"
              "}\n",
              generatorProfile->acotFunctionString());
    EXPECT_EQ("double asech(double x)\n"
              "{\n"
              "    double oneOverX = 1.0/x;\n"
              "\n"
              "    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));\n"
              "}\n",
              generatorProfile->asechFunctionString());
    EXPECT_EQ("double acsch(double x)\n"
              "{\n"
              "    double oneOverX = 1.0/x;\n"
              "\n"
              "    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));\n"
              "}\n",
              generatorProfile->acschFunctionString());
    EXPECT_EQ("double acoth(double x)\n"
              "{\n"
              "    double oneOverX = 1.0/x;\n"
              "\n"
              "    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));\n"
              "}\n",
              generatorProfile->acothFunctionString());
}

TEST(GeneratorProfile, defaultMiscellaneousValues)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    EXPECT_EQ("/* [CODE] */\n", generatorProfile->commentString());
    EXPECT_EQ("The content of this file was generated using [PROFILE_INFORMATION] libCellML [LIBCELLML_VERSION].", generatorProfile->originCommentString());

    EXPECT_EQ("model.h", generatorProfile->interfaceFileNameString());

    EXPECT_EQ("#pragma once\n"
              "\n"
              "#include <stddef.h>\n",
              generatorProfile->interfaceHeaderString());
    EXPECT_EQ("#include \"[INTERFACE_FILE_NAME]\"\n"
              "\n"
              "#include <math.h>\n"
              "#include <stdlib.h>\n",
              generatorProfile->implementationHeaderString());

    EXPECT_EQ("extern const char VERSION[];\n", generatorProfile->interfaceVersionString());
    EXPECT_EQ("const char VERSION[] = \"0.6.0\";\n", generatorProfile->implementationVersionString());

    EXPECT_EQ("extern const char LIBCELLML_VERSION[];\n", generatorProfile->interfaceLibcellmlVersionString());
    EXPECT_EQ("const char LIBCELLML_VERSION[] = \"[LIBCELLML_VERSION]\";\n", generatorProfile->implementationLibcellmlVersionString());

    EXPECT_EQ("extern const size_t STATE_COUNT;\n", generatorProfile->interfaceStateCountString());
    EXPECT_EQ("const size_t STATE_COUNT = [STATE_COUNT];\n", generatorProfile->implementationStateCountString());

    EXPECT_EQ("extern const size_t CONSTANT_COUNT;\n", generatorProfile->interfaceConstantCountString());
    EXPECT_EQ("const size_t CONSTANT_COUNT = [CONSTANT_COUNT];\n", generatorProfile->implementationConstantCountString());

    EXPECT_EQ("extern const size_t COMPUTED_CONSTANT_COUNT;\n", generatorProfile->interfaceComputedConstantCountString());
    EXPECT_EQ("const size_t COMPUTED_CONSTANT_COUNT = [COMPUTED_CONSTANT_COUNT];\n", generatorProfile->implementationComputedConstantCountString());

    EXPECT_EQ("extern const size_t ALGEBRAIC_COUNT;\n", generatorProfile->interfaceAlgebraicCountString());
    EXPECT_EQ("const size_t ALGEBRAIC_COUNT = [ALGEBRAIC_COUNT];\n", generatorProfile->implementationAlgebraicCountString());

    EXPECT_EQ("extern const size_t EXTERNAL_COUNT;\n", generatorProfile->interfaceExternalCountString());
    EXPECT_EQ("const size_t EXTERNAL_COUNT = [EXTERNAL_COUNT];\n", generatorProfile->implementationExternalCountString());

    EXPECT_EQ("typedef struct {\n"
              "    char name[[NAME_SIZE]];\n"
              "    char units[[UNITS_SIZE]];\n"
              "    char component[[COMPONENT_SIZE]];\n"
              "} VariableInfo;\n",
              generatorProfile->variableInfoObjectString());

    EXPECT_EQ("extern const VariableInfo VOI_INFO;\n", generatorProfile->interfaceVoiInfoString());
    EXPECT_EQ("const VariableInfo VOI_INFO = [CODE];\n", generatorProfile->implementationVoiInfoString());

    EXPECT_EQ("extern const VariableInfo STATE_INFO[];\n", generatorProfile->interfaceStateInfoString());
    EXPECT_EQ("const VariableInfo STATE_INFO[] = {\n"
              "[CODE]"
              "};\n",
              generatorProfile->implementationStateInfoString());

    EXPECT_EQ("extern const VariableInfo CONSTANT_INFO[];\n", generatorProfile->interfaceConstantInfoString());
    EXPECT_EQ("const VariableInfo CONSTANT_INFO[] = {\n"
              "[CODE]"
              "};\n",
              generatorProfile->implementationConstantInfoString());

    EXPECT_EQ("extern const VariableInfo COMPUTED_CONSTANT_INFO[];\n", generatorProfile->interfaceComputedConstantInfoString());
    EXPECT_EQ("const VariableInfo COMPUTED_CONSTANT_INFO[] = {\n"
              "[CODE]"
              "};\n",
              generatorProfile->implementationComputedConstantInfoString());

    EXPECT_EQ("extern const VariableInfo ALGEBRAIC_INFO[];\n", generatorProfile->interfaceAlgebraicInfoString());
    EXPECT_EQ("const VariableInfo ALGEBRAIC_INFO[] = {\n"
              "[CODE]"
              "};\n",
              generatorProfile->implementationAlgebraicInfoString());

    EXPECT_EQ("extern const VariableInfo EXTERNAL_INFO[];\n", generatorProfile->interfaceExternalInfoString());
    EXPECT_EQ("const VariableInfo EXTERNAL_INFO[] = {\n"
              "[CODE]"
              "};\n",
              generatorProfile->implementationExternalInfoString());

    EXPECT_EQ("{\"[NAME]\", \"[UNITS]\", \"[COMPONENT]\"}", generatorProfile->variableInfoEntryString());

    EXPECT_EQ("voi", generatorProfile->voiString());

    EXPECT_EQ("states", generatorProfile->statesArrayString());
    EXPECT_EQ("rates", generatorProfile->ratesArrayString());
    EXPECT_EQ("constants", generatorProfile->constantsArrayString());
    EXPECT_EQ("computedConstants", generatorProfile->computedConstantsArrayString());
    EXPECT_EQ("algebraic", generatorProfile->algebraicArrayString());
    EXPECT_EQ("externals", generatorProfile->externalArrayString());

    EXPECT_EQ("typedef double (* ExternalVariable)(double *constants, double *computedConstants, double *algebraic, double *externals, size_t index);\n", generatorProfile->externalVariableMethodTypeDefinitionString(false));
    EXPECT_EQ("typedef double (* ExternalVariable)(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, size_t index);\n", generatorProfile->externalVariableMethodTypeDefinitionString(true));

    EXPECT_EQ("externalVariable(constants, computedConstants, algebraic, externals, [INDEX])", generatorProfile->externalVariableMethodCallString(false));
    EXPECT_EQ("externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, [INDEX])", generatorProfile->externalVariableMethodCallString(true));

    EXPECT_EQ("typedef struct {\n"
              "    double *constants;\n"
              "    double *computedConstants;\n"
              "    double *algebraic;\n"
              "} RootFindingInfo;\n",
              generatorProfile->rootFindingInfoObjectString(false, false));
    EXPECT_EQ("typedef struct {\n"
              "    double *constants;\n"
              "    double *computedConstants;\n"
              "    double *algebraic;\n"
              "    double *externals;\n"
              "} RootFindingInfo;\n",
              generatorProfile->rootFindingInfoObjectString(false, true));
    EXPECT_EQ("typedef struct {\n"
              "    double voi;\n"
              "    double *states;\n"
              "    double *rates;\n"
              "    double *constants;\n"
              "    double *computedConstants;\n"
              "    double *algebraic;\n"
              "} RootFindingInfo;\n",
              generatorProfile->rootFindingInfoObjectString(true, false));
    EXPECT_EQ("typedef struct {\n"
              "    double voi;\n"
              "    double *states;\n"
              "    double *rates;\n"
              "    double *constants;\n"
              "    double *computedConstants;\n"
              "    double *algebraic;\n"
              "    double *externals;\n"
              "} RootFindingInfo;\n",
              generatorProfile->rootFindingInfoObjectString(true, true));
    EXPECT_EQ("extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),\n"
              "                     double *u, size_t n, void *data);\n",
              generatorProfile->externNlaSolveMethodString());
    EXPECT_EQ("findRoot[INDEX](constants, computedConstants, algebraic);\n",
              generatorProfile->findRootCallString(false, false));
    EXPECT_EQ("findRoot[INDEX](constants, computedConstants, algebraic, externals);\n",
              generatorProfile->findRootCallString(false, true));
    EXPECT_EQ("findRoot[INDEX](voi, states, rates, constants, computedConstants, algebraic);\n",
              generatorProfile->findRootCallString(true, false));
    EXPECT_EQ("findRoot[INDEX](voi, states, rates, constants, computedConstants, algebraic, externals);\n",
              generatorProfile->findRootCallString(true, true));
    EXPECT_EQ("void findRoot[INDEX](double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "    RootFindingInfo rfi = { constants, computedConstants, algebraic };\n"
              "    double u[[SIZE]];\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->findRootMethodString(false, false));
    EXPECT_EQ("void findRoot[INDEX](double *constants, double *computedConstants, double *algebraic, double *externals)\n"
              "{\n"
              "    RootFindingInfo rfi = { constants, computedConstants, algebraic, externals };\n"
              "    double u[[SIZE]];\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->findRootMethodString(false, true));
    EXPECT_EQ("void findRoot[INDEX](double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };\n"
              "    double u[[SIZE]];\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->findRootMethodString(true, false));
    EXPECT_EQ("void findRoot[INDEX](double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)\n"
              "{\n"
              "    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };\n"
              "    double u[[SIZE]];\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->findRootMethodString(true, true));
    EXPECT_EQ("nlaSolve(objectiveFunction[INDEX], u, [SIZE], &rfi);\n",
              generatorProfile->nlaSolveCallString(false, false));
    EXPECT_EQ("nlaSolve(objectiveFunction[INDEX], u, [SIZE], &rfi);\n",
              generatorProfile->nlaSolveCallString(false, true));
    EXPECT_EQ("nlaSolve(objectiveFunction[INDEX], u, [SIZE], &rfi);\n",
              generatorProfile->nlaSolveCallString(true, false));
    EXPECT_EQ("nlaSolve(objectiveFunction[INDEX], u, [SIZE], &rfi);\n",
              generatorProfile->nlaSolveCallString(true, true));
    EXPECT_EQ("void objectiveFunction[INDEX](double *u, double *f, void *data)\n"
              "{\n"
              "    double *constants = ((RootFindingInfo *) data)->constants;\n"
              "    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;\n"
              "    double *algebraic = ((RootFindingInfo *) data)->algebraic;\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->objectiveFunctionMethodString(false, false));
    EXPECT_EQ("void objectiveFunction[INDEX](double *u, double *f, void *data)\n"
              "{\n"
              "    double *constants = ((RootFindingInfo *) data)->constants;\n"
              "    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;\n"
              "    double *algebraic = ((RootFindingInfo *) data)->algebraic;\n"
              "    double *externals = ((RootFindingInfo *) data)->externals;\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->objectiveFunctionMethodString(false, true));
    EXPECT_EQ("void objectiveFunction[INDEX](double *u, double *f, void *data)\n"
              "{\n"
              "    double voi = ((RootFindingInfo *) data)->voi;\n"
              "    double *states = ((RootFindingInfo *) data)->states;\n"
              "    double *rates = ((RootFindingInfo *) data)->rates;\n"
              "    double *constants = ((RootFindingInfo *) data)->constants;\n"
              "    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;\n"
              "    double *algebraic = ((RootFindingInfo *) data)->algebraic;\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->objectiveFunctionMethodString(true, false));
    EXPECT_EQ("void objectiveFunction[INDEX](double *u, double *f, void *data)\n"
              "{\n"
              "    double voi = ((RootFindingInfo *) data)->voi;\n"
              "    double *states = ((RootFindingInfo *) data)->states;\n"
              "    double *rates = ((RootFindingInfo *) data)->rates;\n"
              "    double *constants = ((RootFindingInfo *) data)->constants;\n"
              "    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;\n"
              "    double *algebraic = ((RootFindingInfo *) data)->algebraic;\n"
              "    double *externals = ((RootFindingInfo *) data)->externals;\n"
              "\n"
              "[CODE]"
              "}\n",
              generatorProfile->objectiveFunctionMethodString(true, true));
    EXPECT_EQ("u",
              generatorProfile->uArrayString());
    EXPECT_EQ("f",
              generatorProfile->fArrayString());

    EXPECT_EQ("double * createStatesArray();\n",
              generatorProfile->interfaceCreateStatesArrayMethodString());
    EXPECT_EQ("double * createStatesArray()\n"
              "{\n"
              "    double *res = (double *) malloc(STATE_COUNT*sizeof(double));\n"
              "\n"
              "    for (size_t i = 0; i < STATE_COUNT; ++i) {\n"
              "        res[i] = NAN;\n"
              "    }\n"
              "\n"
              "    return res;\n"
              "}\n",
              generatorProfile->implementationCreateStatesArrayMethodString());

    EXPECT_EQ("double * createConstantsArray();\n",
              generatorProfile->interfaceCreateConstantsArrayMethodString());
    EXPECT_EQ("double * createConstantsArray()\n"
              "{\n"
              "    double *res = (double *) malloc(CONSTANT_COUNT*sizeof(double));\n"
              "\n"
              "    for (size_t i = 0; i < CONSTANT_COUNT; ++i) {\n"
              "        res[i] = NAN;\n"
              "    }\n"
              "\n"
              "    return res;\n"
              "}\n",
              generatorProfile->implementationCreateConstantsArrayMethodString());

    EXPECT_EQ("double * createComputedConstantsArray();\n",
              generatorProfile->interfaceCreateComputedConstantsArrayMethodString());
    EXPECT_EQ("double * createComputedConstantsArray()\n"
              "{\n"
              "    double *res = (double *) malloc(COMPUTED_CONSTANT_COUNT*sizeof(double));\n"
              "\n"
              "    for (size_t i = 0; i < COMPUTED_CONSTANT_COUNT; ++i) {\n"
              "        res[i] = NAN;\n"
              "    }\n"
              "\n"
              "    return res;\n"
              "}\n",
              generatorProfile->implementationCreateComputedConstantsArrayMethodString());

    EXPECT_EQ("double * createAlgebraicArray();\n",
              generatorProfile->interfaceCreateAlgebraicArrayMethodString());
    EXPECT_EQ("double * createAlgebraicArray()\n"
              "{\n"
              "    double *res = (double *) malloc(ALGEBRAIC_COUNT*sizeof(double));\n"
              "\n"
              "    for (size_t i = 0; i < ALGEBRAIC_COUNT; ++i) {\n"
              "        res[i] = NAN;\n"
              "    }\n"
              "\n"
              "    return res;\n"
              "}\n",
              generatorProfile->implementationCreateAlgebraicArrayMethodString());

    EXPECT_EQ("double * createExternalsArray();\n",
              generatorProfile->interfaceCreateExternalsArrayMethodString());
    EXPECT_EQ("double * createExternalsArray()\n"
              "{\n"
              "    double *res = (double *) malloc(EXTERNAL_COUNT*sizeof(double));\n"
              "\n"
              "    for (size_t i = 0; i < EXTERNAL_COUNT; ++i) {\n"
              "        res[i] = NAN;\n"
              "    }\n"
              "\n"
              "    return res;\n"
              "}\n",
              generatorProfile->implementationCreateExternalsArrayMethodString());

    EXPECT_EQ("void deleteArray(double *array);\n",
              generatorProfile->interfaceDeleteArrayMethodString());
    EXPECT_EQ("void deleteArray(double *array)\n"
              "{\n"
              "    free(array);\n"
              "}\n",
              generatorProfile->implementationDeleteArrayMethodString());

    EXPECT_EQ("void initialiseVariables(double *constants, double *computedConstants, double *algebraic);\n",
              generatorProfile->interfaceInitialiseVariablesMethodString(false));
    EXPECT_EQ("void initialiseVariables(double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationInitialiseVariablesMethodString(false));

    EXPECT_EQ("void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic);\n",
              generatorProfile->interfaceInitialiseVariablesMethodString(true));
    EXPECT_EQ("void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationInitialiseVariablesMethodString(true));

    EXPECT_EQ("void computeComputedConstants(double *constants, double *computedConstants);\n",
              generatorProfile->interfaceComputeComputedConstantsMethodString());
    EXPECT_EQ("void computeComputedConstants(double *constants, double *computedConstants)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeComputedConstantsMethodString());

    EXPECT_EQ("void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic);\n",
              generatorProfile->interfaceComputeRatesMethodString(false));
    EXPECT_EQ("void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeRatesMethodString(false));

    EXPECT_EQ("void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable);\n",
              generatorProfile->interfaceComputeRatesMethodString(true));
    EXPECT_EQ("void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeRatesMethodString(true));

    EXPECT_EQ("void computeVariables(double *constants, double *computedConstants, double *algebraic);\n",
              generatorProfile->interfaceComputeVariablesMethodString(false, false));
    EXPECT_EQ("void computeVariables(double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeVariablesMethodString(false, false));

    EXPECT_EQ("void computeVariables(double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable);\n",
              generatorProfile->interfaceComputeVariablesMethodString(false, true));
    EXPECT_EQ("void computeVariables(double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeVariablesMethodString(false, true));

    EXPECT_EQ("void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic);\n",
              generatorProfile->interfaceComputeVariablesMethodString(true, false));
    EXPECT_EQ("void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeVariablesMethodString(true, false));

    EXPECT_EQ("void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable);\n",
              generatorProfile->interfaceComputeVariablesMethodString(true, true));
    EXPECT_EQ("void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)\n"
              "{\n"
              "[CODE]"
              "}\n",
              generatorProfile->implementationComputeVariablesMethodString(true, true));

    EXPECT_EQ("", generatorProfile->emptyMethodString());

    EXPECT_EQ("    ", generatorProfile->indentString());

    EXPECT_EQ("double [CODE]", generatorProfile->variableDeclarationString());

    EXPECT_EQ("[", generatorProfile->openArrayString());
    EXPECT_EQ("]", generatorProfile->closeArrayString());

    EXPECT_EQ(",", generatorProfile->arrayElementSeparatorString());

    EXPECT_EQ(";", generatorProfile->commandSeparatorString());
}

TEST(GeneratorProfile, generalSettings)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const libcellml::GeneratorProfile::Profile profile = libcellml::GeneratorProfile::Profile::PYTHON;
    const bool falseValue = false;

    generatorProfile->setProfile(profile);

    generatorProfile->setHasInterface(falseValue);

    EXPECT_EQ(profile, generatorProfile->profile());
    EXPECT_EQ("python", libcellml::GeneratorProfile::profileAsString(generatorProfile->profile()));

    EXPECT_EQ(falseValue, generatorProfile->hasInterface());
}

TEST(GeneratorProfile, relationalAndLogicalOperators)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";
    const bool trueValue = true;
    const bool falseValue = false;

    generatorProfile->setEqualityString(value);
    generatorProfile->setEqString(value);
    generatorProfile->setNeqString(value);
    generatorProfile->setLtString(value);
    generatorProfile->setLeqString(value);
    generatorProfile->setGtString(value);
    generatorProfile->setGeqString(value);
    generatorProfile->setAndString(value);
    generatorProfile->setOrString(value);
    generatorProfile->setXorString(value);
    generatorProfile->setNotString(value);

    generatorProfile->setHasEqOperator(falseValue);
    generatorProfile->setHasNeqOperator(falseValue);
    generatorProfile->setHasLtOperator(falseValue);
    generatorProfile->setHasLeqOperator(falseValue);
    generatorProfile->setHasGtOperator(falseValue);
    generatorProfile->setHasGeqOperator(falseValue);
    generatorProfile->setHasAndOperator(falseValue);
    generatorProfile->setHasOrOperator(falseValue);
    generatorProfile->setHasXorOperator(trueValue);
    generatorProfile->setHasNotOperator(falseValue);

    EXPECT_EQ(value, generatorProfile->equalityString());
    EXPECT_EQ(value, generatorProfile->eqString());
    EXPECT_EQ(value, generatorProfile->neqString());
    EXPECT_EQ(value, generatorProfile->ltString());
    EXPECT_EQ(value, generatorProfile->leqString());
    EXPECT_EQ(value, generatorProfile->gtString());
    EXPECT_EQ(value, generatorProfile->geqString());
    EXPECT_EQ(value, generatorProfile->andString());
    EXPECT_EQ(value, generatorProfile->orString());
    EXPECT_EQ(value, generatorProfile->xorString());
    EXPECT_EQ(value, generatorProfile->notString());

    EXPECT_EQ(falseValue, generatorProfile->hasEqOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasNeqOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasLtOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasLeqOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasGtOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasGeqOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasAndOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasOrOperator());
    EXPECT_EQ(trueValue, generatorProfile->hasXorOperator());
    EXPECT_EQ(falseValue, generatorProfile->hasNotOperator());
}

TEST(GeneratorProfile, arithmeticOperators)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";
    const bool trueValue = true;

    generatorProfile->setPlusString(value);
    generatorProfile->setMinusString(value);
    generatorProfile->setTimesString(value);
    generatorProfile->setDivideString(value);
    generatorProfile->setPowerString(value);
    generatorProfile->setSquareRootString(value);
    generatorProfile->setSquareString(value);
    generatorProfile->setAbsoluteValueString(value);
    generatorProfile->setExponentialString(value);
    generatorProfile->setNaturalLogarithmString(value);
    generatorProfile->setCommonLogarithmString(value);
    generatorProfile->setCeilingString(value);
    generatorProfile->setFloorString(value);
    generatorProfile->setMinString(value);
    generatorProfile->setMaxString(value);
    generatorProfile->setRemString(value);

    generatorProfile->setHasPowerOperator(trueValue);

    EXPECT_EQ(value, generatorProfile->plusString());
    EXPECT_EQ(value, generatorProfile->minusString());
    EXPECT_EQ(value, generatorProfile->timesString());
    EXPECT_EQ(value, generatorProfile->divideString());
    EXPECT_EQ(value, generatorProfile->powerString());
    EXPECT_EQ(value, generatorProfile->squareRootString());
    EXPECT_EQ(value, generatorProfile->squareString());
    EXPECT_EQ(value, generatorProfile->absoluteValueString());
    EXPECT_EQ(value, generatorProfile->exponentialString());
    EXPECT_EQ(value, generatorProfile->naturalLogarithmString());
    EXPECT_EQ(value, generatorProfile->commonLogarithmString());
    EXPECT_EQ(value, generatorProfile->ceilingString());
    EXPECT_EQ(value, generatorProfile->floorString());
    EXPECT_EQ(value, generatorProfile->minString());
    EXPECT_EQ(value, generatorProfile->maxString());
    EXPECT_EQ(value, generatorProfile->remString());

    EXPECT_EQ(trueValue, generatorProfile->hasPowerOperator());
}

TEST(GeneratorProfile, trigonometricOperators)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";

    generatorProfile->setSinString(value);
    generatorProfile->setCosString(value);
    generatorProfile->setTanString(value);
    generatorProfile->setSecString(value);
    generatorProfile->setCscString(value);
    generatorProfile->setCotString(value);
    generatorProfile->setSinhString(value);
    generatorProfile->setCoshString(value);
    generatorProfile->setTanhString(value);
    generatorProfile->setSechString(value);
    generatorProfile->setCschString(value);
    generatorProfile->setCothString(value);
    generatorProfile->setAsinString(value);
    generatorProfile->setAcosString(value);
    generatorProfile->setAtanString(value);
    generatorProfile->setAsecString(value);
    generatorProfile->setAcscString(value);
    generatorProfile->setAcotString(value);
    generatorProfile->setAsinhString(value);
    generatorProfile->setAcoshString(value);
    generatorProfile->setAtanhString(value);
    generatorProfile->setAsechString(value);
    generatorProfile->setAcschString(value);
    generatorProfile->setAcothString(value);

    EXPECT_EQ(value, generatorProfile->sinString());
    EXPECT_EQ(value, generatorProfile->cosString());
    EXPECT_EQ(value, generatorProfile->tanString());
    EXPECT_EQ(value, generatorProfile->secString());
    EXPECT_EQ(value, generatorProfile->cscString());
    EXPECT_EQ(value, generatorProfile->cotString());
    EXPECT_EQ(value, generatorProfile->sinhString());
    EXPECT_EQ(value, generatorProfile->coshString());
    EXPECT_EQ(value, generatorProfile->tanhString());
    EXPECT_EQ(value, generatorProfile->sechString());
    EXPECT_EQ(value, generatorProfile->cschString());
    EXPECT_EQ(value, generatorProfile->cothString());
    EXPECT_EQ(value, generatorProfile->asinString());
    EXPECT_EQ(value, generatorProfile->acosString());
    EXPECT_EQ(value, generatorProfile->atanString());
    EXPECT_EQ(value, generatorProfile->asecString());
    EXPECT_EQ(value, generatorProfile->acscString());
    EXPECT_EQ(value, generatorProfile->acotString());
    EXPECT_EQ(value, generatorProfile->asinhString());
    EXPECT_EQ(value, generatorProfile->acoshString());
    EXPECT_EQ(value, generatorProfile->atanhString());
    EXPECT_EQ(value, generatorProfile->asechString());
    EXPECT_EQ(value, generatorProfile->acschString());
    EXPECT_EQ(value, generatorProfile->acothString());
}

TEST(GeneratorProfile, piecewiseStatement)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";
    const bool falseValue = true;

    generatorProfile->setConditionalOperatorIfString(value);
    generatorProfile->setConditionalOperatorElseString(value);
    generatorProfile->setPiecewiseIfString(value);
    generatorProfile->setPiecewiseElseString(value);

    generatorProfile->setHasConditionalOperator(falseValue);

    EXPECT_EQ(value, generatorProfile->conditionalOperatorIfString());
    EXPECT_EQ(value, generatorProfile->conditionalOperatorElseString());
    EXPECT_EQ(value, generatorProfile->piecewiseIfString());
    EXPECT_EQ(value, generatorProfile->piecewiseElseString());

    EXPECT_EQ(falseValue, generatorProfile->hasConditionalOperator());
}

TEST(GeneratorProfile, constants)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";

    generatorProfile->setTrueString(value);
    generatorProfile->setFalseString(value);
    generatorProfile->setEString(value);
    generatorProfile->setPiString(value);
    generatorProfile->setInfString(value);
    generatorProfile->setNanString(value);

    EXPECT_EQ(value, generatorProfile->trueString());
    EXPECT_EQ(value, generatorProfile->falseString());
    EXPECT_EQ(value, generatorProfile->eString());
    EXPECT_EQ(value, generatorProfile->piString());
    EXPECT_EQ(value, generatorProfile->infString());
    EXPECT_EQ(value, generatorProfile->nanString());
}

TEST(GeneratorProfile, arithmeticFunctions)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";

    generatorProfile->setEqFunctionString(value);
    generatorProfile->setNeqFunctionString(value);
    generatorProfile->setLtFunctionString(value);
    generatorProfile->setLeqFunctionString(value);
    generatorProfile->setGtFunctionString(value);
    generatorProfile->setGeqFunctionString(value);
    generatorProfile->setAndFunctionString(value);
    generatorProfile->setOrFunctionString(value);
    generatorProfile->setXorFunctionString(value);
    generatorProfile->setNotFunctionString(value);
    generatorProfile->setMinFunctionString(value);
    generatorProfile->setMaxFunctionString(value);

    EXPECT_EQ(value, generatorProfile->eqFunctionString());
    EXPECT_EQ(value, generatorProfile->neqFunctionString());
    EXPECT_EQ(value, generatorProfile->ltFunctionString());
    EXPECT_EQ(value, generatorProfile->leqFunctionString());
    EXPECT_EQ(value, generatorProfile->gtFunctionString());
    EXPECT_EQ(value, generatorProfile->geqFunctionString());
    EXPECT_EQ(value, generatorProfile->andFunctionString());
    EXPECT_EQ(value, generatorProfile->orFunctionString());
    EXPECT_EQ(value, generatorProfile->xorFunctionString());
    EXPECT_EQ(value, generatorProfile->notFunctionString());
    EXPECT_EQ(value, generatorProfile->minFunctionString());
    EXPECT_EQ(value, generatorProfile->maxFunctionString());
}

TEST(GeneratorProfile, trigonometricFunctions)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";

    generatorProfile->setSecFunctionString(value);
    generatorProfile->setCscFunctionString(value);
    generatorProfile->setCotFunctionString(value);
    generatorProfile->setSechFunctionString(value);
    generatorProfile->setCschFunctionString(value);
    generatorProfile->setCothFunctionString(value);
    generatorProfile->setAsecFunctionString(value);
    generatorProfile->setAcscFunctionString(value);
    generatorProfile->setAcotFunctionString(value);
    generatorProfile->setAsechFunctionString(value);
    generatorProfile->setAcschFunctionString(value);
    generatorProfile->setAcothFunctionString(value);

    EXPECT_EQ(value, generatorProfile->secFunctionString());
    EXPECT_EQ(value, generatorProfile->cscFunctionString());
    EXPECT_EQ(value, generatorProfile->cotFunctionString());
    EXPECT_EQ(value, generatorProfile->sechFunctionString());
    EXPECT_EQ(value, generatorProfile->cschFunctionString());
    EXPECT_EQ(value, generatorProfile->cothFunctionString());
    EXPECT_EQ(value, generatorProfile->asecFunctionString());
    EXPECT_EQ(value, generatorProfile->acscFunctionString());
    EXPECT_EQ(value, generatorProfile->acotFunctionString());
    EXPECT_EQ(value, generatorProfile->asechFunctionString());
    EXPECT_EQ(value, generatorProfile->acschFunctionString());
    EXPECT_EQ(value, generatorProfile->acothFunctionString());
}

TEST(GeneratorProfile, miscellaneous)
{
    libcellml::GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();

    const std::string value = "value";

    generatorProfile->setCommentString(value);
    generatorProfile->setOriginCommentString(value);

    generatorProfile->setInterfaceFileNameString(value);

    generatorProfile->setInterfaceHeaderString(value);
    generatorProfile->setImplementationHeaderString(value);

    generatorProfile->setInterfaceVersionString(value);
    generatorProfile->setImplementationVersionString(value);

    generatorProfile->setInterfaceLibcellmlVersionString(value);
    generatorProfile->setImplementationLibcellmlVersionString(value);

    generatorProfile->setInterfaceStateCountString(value);
    generatorProfile->setImplementationStateCountString(value);

    generatorProfile->setInterfaceConstantCountString(value);
    generatorProfile->setImplementationConstantCountString(value);

    generatorProfile->setInterfaceComputedConstantCountString(value);
    generatorProfile->setImplementationComputedConstantCountString(value);

    generatorProfile->setInterfaceAlgebraicCountString(value);
    generatorProfile->setImplementationAlgebraicCountString(value);

    generatorProfile->setInterfaceExternalCountString(value);
    generatorProfile->setImplementationExternalCountString(value);

    generatorProfile->setVariableInfoObjectString(value);

    generatorProfile->setInterfaceVoiInfoString(value);
    generatorProfile->setImplementationVoiInfoString(value);

    generatorProfile->setInterfaceStateInfoString(value);
    generatorProfile->setImplementationStateInfoString(value);

    generatorProfile->setInterfaceConstantInfoString(value);
    generatorProfile->setImplementationConstantInfoString(value);

    generatorProfile->setInterfaceComputedConstantInfoString(value);
    generatorProfile->setImplementationComputedConstantInfoString(value);

    generatorProfile->setInterfaceAlgebraicInfoString(value);
    generatorProfile->setImplementationAlgebraicInfoString(value);

    generatorProfile->setInterfaceExternalInfoString(value);
    generatorProfile->setImplementationExternalInfoString(value);

    generatorProfile->setVariableInfoEntryString(value);

    generatorProfile->setVoiString(value);

    generatorProfile->setStatesArrayString(value);
    generatorProfile->setRatesArrayString(value);
    generatorProfile->setConstantsArrayString(value);
    generatorProfile->setComputedConstantsArrayString(value);
    generatorProfile->setAlgebraicArrayString(value);
    generatorProfile->setExternalArrayString(value);

    generatorProfile->setExternalVariableMethodTypeDefinitionString(false, value);
    generatorProfile->setExternalVariableMethodTypeDefinitionString(true, value);

    generatorProfile->setExternalVariableMethodCallString(false, value);
    generatorProfile->setExternalVariableMethodCallString(true, value);

    generatorProfile->setRootFindingInfoObjectString(false, false, value);
    generatorProfile->setRootFindingInfoObjectString(false, true, value);
    generatorProfile->setRootFindingInfoObjectString(true, false, value);
    generatorProfile->setRootFindingInfoObjectString(true, true, value);

    generatorProfile->setExternNlaSolveMethodString(value);

    generatorProfile->setFindRootCallString(false, false, value);
    generatorProfile->setFindRootCallString(false, true, value);
    generatorProfile->setFindRootCallString(true, false, value);
    generatorProfile->setFindRootCallString(true, true, value);

    generatorProfile->setFindRootMethodString(false, false, value);
    generatorProfile->setFindRootMethodString(false, true, value);
    generatorProfile->setFindRootMethodString(true, false, value);
    generatorProfile->setFindRootMethodString(true, true, value);

    generatorProfile->setNlaSolveCallString(false, false, value);
    generatorProfile->setNlaSolveCallString(false, true, value);
    generatorProfile->setNlaSolveCallString(true, false, value);
    generatorProfile->setNlaSolveCallString(true, true, value);

    generatorProfile->setObjectiveFunctionMethodString(false, false, value);
    generatorProfile->setObjectiveFunctionMethodString(false, true, value);
    generatorProfile->setObjectiveFunctionMethodString(true, false, value);
    generatorProfile->setObjectiveFunctionMethodString(true, true, value);

    generatorProfile->setUArrayString(value);
    generatorProfile->setFArrayString(value);

    generatorProfile->setInterfaceCreateStatesArrayMethodString(value);
    generatorProfile->setImplementationCreateStatesArrayMethodString(value);

    generatorProfile->setInterfaceCreateConstantsArrayMethodString(value);
    generatorProfile->setImplementationCreateConstantsArrayMethodString(value);

    generatorProfile->setInterfaceCreateComputedConstantsArrayMethodString(value);
    generatorProfile->setImplementationCreateComputedConstantsArrayMethodString(value);

    generatorProfile->setInterfaceCreateAlgebraicArrayMethodString(value);
    generatorProfile->setImplementationCreateAlgebraicArrayMethodString(value);

    generatorProfile->setInterfaceCreateExternalsArrayMethodString(value);
    generatorProfile->setImplementationCreateExternalsArrayMethodString(value);

    generatorProfile->setInterfaceDeleteArrayMethodString(value);
    generatorProfile->setImplementationDeleteArrayMethodString(value);

    generatorProfile->setInterfaceInitialiseVariablesMethodString(false, value);
    generatorProfile->setInterfaceInitialiseVariablesMethodString(true, value);

    generatorProfile->setImplementationInitialiseVariablesMethodString(false, value);
    generatorProfile->setImplementationInitialiseVariablesMethodString(true, value);

    generatorProfile->setInterfaceComputeComputedConstantsMethodString(value);
    generatorProfile->setImplementationComputeComputedConstantsMethodString(value);

    generatorProfile->setInterfaceComputeRatesMethodString(false, value);
    generatorProfile->setInterfaceComputeRatesMethodString(true, value);

    generatorProfile->setImplementationComputeRatesMethodString(false, value);
    generatorProfile->setImplementationComputeRatesMethodString(true, value);

    generatorProfile->setInterfaceComputeVariablesMethodString(false, false, value);
    generatorProfile->setInterfaceComputeVariablesMethodString(false, true, value);
    generatorProfile->setInterfaceComputeVariablesMethodString(true, false, value);
    generatorProfile->setInterfaceComputeVariablesMethodString(true, true, value);

    generatorProfile->setImplementationComputeVariablesMethodString(false, false, value);
    generatorProfile->setImplementationComputeVariablesMethodString(false, true, value);
    generatorProfile->setImplementationComputeVariablesMethodString(true, false, value);
    generatorProfile->setImplementationComputeVariablesMethodString(true, true, value);

    generatorProfile->setEmptyMethodString(value);

    generatorProfile->setIndentString(value);

    generatorProfile->setVariableDeclarationString(value);

    generatorProfile->setOpenArrayString(value);
    generatorProfile->setCloseArrayString(value);

    generatorProfile->setArrayElementSeparatorString(value);

    generatorProfile->setCommandSeparatorString(value);

    EXPECT_EQ(value, generatorProfile->commentString());
    EXPECT_EQ(value, generatorProfile->originCommentString());

    EXPECT_EQ(value, generatorProfile->interfaceFileNameString());

    EXPECT_EQ(value, generatorProfile->interfaceHeaderString());
    EXPECT_EQ(value, generatorProfile->implementationHeaderString());

    EXPECT_EQ(value, generatorProfile->interfaceVersionString());
    EXPECT_EQ(value, generatorProfile->implementationVersionString());

    EXPECT_EQ(value, generatorProfile->interfaceLibcellmlVersionString());
    EXPECT_EQ(value, generatorProfile->implementationLibcellmlVersionString());

    EXPECT_EQ(value, generatorProfile->interfaceStateCountString());
    EXPECT_EQ(value, generatorProfile->implementationStateCountString());

    EXPECT_EQ(value, generatorProfile->interfaceConstantCountString());
    EXPECT_EQ(value, generatorProfile->implementationConstantCountString());

    EXPECT_EQ(value, generatorProfile->interfaceComputedConstantCountString());
    EXPECT_EQ(value, generatorProfile->implementationComputedConstantCountString());

    EXPECT_EQ(value, generatorProfile->interfaceAlgebraicCountString());
    EXPECT_EQ(value, generatorProfile->implementationAlgebraicCountString());

    EXPECT_EQ(value, generatorProfile->interfaceExternalCountString());
    EXPECT_EQ(value, generatorProfile->implementationExternalCountString());

    EXPECT_EQ(value, generatorProfile->variableInfoObjectString());

    EXPECT_EQ(value, generatorProfile->interfaceVoiInfoString());
    EXPECT_EQ(value, generatorProfile->implementationVoiInfoString());

    EXPECT_EQ(value, generatorProfile->interfaceStateInfoString());
    EXPECT_EQ(value, generatorProfile->implementationStateInfoString());

    EXPECT_EQ(value, generatorProfile->interfaceConstantInfoString());
    EXPECT_EQ(value, generatorProfile->implementationConstantInfoString());

    EXPECT_EQ(value, generatorProfile->interfaceComputedConstantInfoString());
    EXPECT_EQ(value, generatorProfile->implementationComputedConstantInfoString());

    EXPECT_EQ(value, generatorProfile->interfaceAlgebraicInfoString());
    EXPECT_EQ(value, generatorProfile->implementationAlgebraicInfoString());

    EXPECT_EQ(value, generatorProfile->interfaceExternalInfoString());
    EXPECT_EQ(value, generatorProfile->implementationExternalInfoString());

    EXPECT_EQ(value, generatorProfile->variableInfoEntryString());

    EXPECT_EQ(value, generatorProfile->voiString());

    EXPECT_EQ(value, generatorProfile->statesArrayString());
    EXPECT_EQ(value, generatorProfile->ratesArrayString());
    EXPECT_EQ(value, generatorProfile->constantsArrayString());
    EXPECT_EQ(value, generatorProfile->computedConstantsArrayString());
    EXPECT_EQ(value, generatorProfile->algebraicArrayString());
    EXPECT_EQ(value, generatorProfile->externalArrayString());

    EXPECT_EQ(value, generatorProfile->externalVariableMethodTypeDefinitionString(false));
    EXPECT_EQ(value, generatorProfile->externalVariableMethodTypeDefinitionString(true));

    EXPECT_EQ(value, generatorProfile->externalVariableMethodCallString(false));
    EXPECT_EQ(value, generatorProfile->externalVariableMethodCallString(true));

    EXPECT_EQ(value, generatorProfile->rootFindingInfoObjectString(false, false));
    EXPECT_EQ(value, generatorProfile->rootFindingInfoObjectString(false, true));
    EXPECT_EQ(value, generatorProfile->rootFindingInfoObjectString(true, false));
    EXPECT_EQ(value, generatorProfile->rootFindingInfoObjectString(true, true));

    EXPECT_EQ(value, generatorProfile->externNlaSolveMethodString());

    EXPECT_EQ(value, generatorProfile->findRootCallString(false, false));
    EXPECT_EQ(value, generatorProfile->findRootCallString(false, true));
    EXPECT_EQ(value, generatorProfile->findRootCallString(true, false));
    EXPECT_EQ(value, generatorProfile->findRootCallString(true, true));

    EXPECT_EQ(value, generatorProfile->findRootMethodString(false, false));
    EXPECT_EQ(value, generatorProfile->findRootMethodString(false, true));
    EXPECT_EQ(value, generatorProfile->findRootMethodString(true, false));
    EXPECT_EQ(value, generatorProfile->findRootMethodString(true, true));

    EXPECT_EQ(value, generatorProfile->nlaSolveCallString(false, false));
    EXPECT_EQ(value, generatorProfile->nlaSolveCallString(false, true));
    EXPECT_EQ(value, generatorProfile->nlaSolveCallString(true, false));
    EXPECT_EQ(value, generatorProfile->nlaSolveCallString(true, true));

    EXPECT_EQ(value, generatorProfile->objectiveFunctionMethodString(false, false));
    EXPECT_EQ(value, generatorProfile->objectiveFunctionMethodString(false, true));
    EXPECT_EQ(value, generatorProfile->objectiveFunctionMethodString(true, false));
    EXPECT_EQ(value, generatorProfile->objectiveFunctionMethodString(true, true));

    EXPECT_EQ(value, generatorProfile->uArrayString());
    EXPECT_EQ(value, generatorProfile->fArrayString());

    EXPECT_EQ(value, generatorProfile->interfaceCreateStatesArrayMethodString());
    EXPECT_EQ(value, generatorProfile->implementationCreateStatesArrayMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceCreateConstantsArrayMethodString());
    EXPECT_EQ(value, generatorProfile->implementationCreateConstantsArrayMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceCreateComputedConstantsArrayMethodString());
    EXPECT_EQ(value, generatorProfile->implementationCreateComputedConstantsArrayMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceCreateAlgebraicArrayMethodString());
    EXPECT_EQ(value, generatorProfile->implementationCreateAlgebraicArrayMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceCreateExternalsArrayMethodString());
    EXPECT_EQ(value, generatorProfile->implementationCreateExternalsArrayMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceDeleteArrayMethodString());
    EXPECT_EQ(value, generatorProfile->implementationDeleteArrayMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceInitialiseVariablesMethodString(false));
    EXPECT_EQ(value, generatorProfile->implementationInitialiseVariablesMethodString(false));

    EXPECT_EQ(value, generatorProfile->interfaceInitialiseVariablesMethodString(true));
    EXPECT_EQ(value, generatorProfile->implementationInitialiseVariablesMethodString(true));

    EXPECT_EQ(value, generatorProfile->interfaceComputeComputedConstantsMethodString());
    EXPECT_EQ(value, generatorProfile->implementationComputeComputedConstantsMethodString());

    EXPECT_EQ(value, generatorProfile->interfaceComputeRatesMethodString(false));
    EXPECT_EQ(value, generatorProfile->implementationComputeRatesMethodString(false));

    EXPECT_EQ(value, generatorProfile->interfaceComputeRatesMethodString(true));
    EXPECT_EQ(value, generatorProfile->implementationComputeRatesMethodString(true));

    EXPECT_EQ(value, generatorProfile->interfaceComputeVariablesMethodString(false, false));
    EXPECT_EQ(value, generatorProfile->implementationComputeVariablesMethodString(false, false));

    EXPECT_EQ(value, generatorProfile->interfaceComputeVariablesMethodString(false, true));
    EXPECT_EQ(value, generatorProfile->implementationComputeVariablesMethodString(false, true));

    EXPECT_EQ(value, generatorProfile->interfaceComputeVariablesMethodString(true, false));
    EXPECT_EQ(value, generatorProfile->implementationComputeVariablesMethodString(true, false));

    EXPECT_EQ(value, generatorProfile->interfaceComputeVariablesMethodString(true, true));
    EXPECT_EQ(value, generatorProfile->implementationComputeVariablesMethodString(true, true));

    EXPECT_EQ(value, generatorProfile->emptyMethodString());

    EXPECT_EQ(value, generatorProfile->indentString());

    EXPECT_EQ(value, generatorProfile->variableDeclarationString());

    EXPECT_EQ(value, generatorProfile->openArrayString());
    EXPECT_EQ(value, generatorProfile->closeArrayString());

    EXPECT_EQ(value, generatorProfile->arrayElementSeparatorString());

    EXPECT_EQ(value, generatorProfile->commandSeparatorString());
}
