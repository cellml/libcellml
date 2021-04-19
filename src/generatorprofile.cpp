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

#include "libcellml/generatorprofile.h"

#include <cmath>

#include "utilities.h"

namespace libcellml {

/**
 * @brief The GeneratorProfile::GeneratorProfileImpl struct.
 *
 * The private implementation for the GeneratorProfile class.
 */
struct GeneratorProfile::GeneratorProfileImpl
{
    // Whether the profile is official.

    GeneratorProfile::Profile mProfile = Profile::C;

    // Whether the profile requires an interface to be generated.

    bool mHasInterface = true;

    // Assignment.

    std::string mAssignmentString;

    // Relational and logical operators.

    std::string mEqString;
    std::string mNeqString;
    std::string mLtString;
    std::string mLeqString;
    std::string mGtString;
    std::string mGeqString;
    std::string mAndString;
    std::string mOrString;
    std::string mXorString;
    std::string mNotString;

    bool mHasEqOperator = true;
    bool mHasNeqOperator = true;
    bool mHasLtOperator = true;
    bool mHasLeqOperator = true;
    bool mHasGtOperator = true;
    bool mHasGeqOperator = true;
    bool mHasAndOperator = true;
    bool mHasOrOperator = true;
    bool mHasXorOperator = true;
    bool mHasNotOperator = true;

    // Arithmetic operators.

    std::string mPlusString;
    std::string mMinusString;
    std::string mTimesString;
    std::string mDivideString;
    std::string mPowerString;
    std::string mSquareRootString;
    std::string mSquareString;
    std::string mAbsoluteValueString;
    std::string mExponentialString;
    std::string mNaturalLogarithmString;
    std::string mCommonLogarithmString;
    std::string mCeilingString;
    std::string mFloorString;
    std::string mMinString;
    std::string mMaxString;
    std::string mRemString;

    bool mHasPowerOperator = false;

    // Trigonometric operators.

    std::string mSinString;
    std::string mCosString;
    std::string mTanString;
    std::string mSecString;
    std::string mCscString;
    std::string mCotString;
    std::string mSinhString;
    std::string mCoshString;
    std::string mTanhString;
    std::string mSechString;
    std::string mCschString;
    std::string mCothString;
    std::string mAsinString;
    std::string mAcosString;
    std::string mAtanString;
    std::string mAsecString;
    std::string mAcscString;
    std::string mAcotString;
    std::string mAsinhString;
    std::string mAcoshString;
    std::string mAtanhString;
    std::string mAsechString;
    std::string mAcschString;
    std::string mAcothString;

    // Piecewise statement.

    std::string mConditionalOperatorIfString;
    std::string mConditionalOperatorElseString;
    std::string mPiecewiseIfString;
    std::string mPiecewiseElseString;

    bool mHasConditionalOperator = true;

    // Constants.

    std::string mTrueString;
    std::string mFalseString;
    std::string mEString;
    std::string mPiString;
    std::string mInfString;
    std::string mNanString;

    // Arithmetic functions.

    std::string mEqFunctionString;
    std::string mNeqFunctionString;
    std::string mLtFunctionString;
    std::string mLeqFunctionString;
    std::string mGtFunctionString;
    std::string mGeqFunctionString;
    std::string mAndFunctionString;
    std::string mOrFunctionString;
    std::string mXorFunctionString;
    std::string mNotFunctionString;
    std::string mMinFunctionString;
    std::string mMaxFunctionString;

    // Trigonometric functions.

    std::string mSecFunctionString;
    std::string mCscFunctionString;
    std::string mCotFunctionString;
    std::string mSechFunctionString;
    std::string mCschFunctionString;
    std::string mCothFunctionString;
    std::string mAsecFunctionString;
    std::string mAcscFunctionString;
    std::string mAcotFunctionString;
    std::string mAsechFunctionString;
    std::string mAcschFunctionString;
    std::string mAcothFunctionString;

    // Miscellaneous.

    std::string mCommentString;
    std::string mOriginCommentString;

    std::string mInterfaceFileNameString;

    std::string mInterfaceHeaderString;
    std::string mImplementationHeaderString;

    std::string mInterfaceVersionString;
    std::string mImplementationVersionString;

    std::string mInterfaceLibcellmlVersionString;
    std::string mImplementationLibcellmlVersionString;

    std::string mInterfaceStateCountString;
    std::string mImplementationStateCountString;

    std::string mInterfaceVariableCountString;
    std::string mImplementationVariableCountString;

    std::string mVariableTypeObjectString;
    std::string mVariableTypeObjectExternalTypeString;

    std::string mConstantVariableTypeString;
    std::string mComputedConstantVariableTypeString;
    std::string mAlgebraicVariableTypeString;
    std::string mExternalVariableTypeString;

    std::string mVariableInfoObjectString;
    std::string mVariableInfoWithTypeObjectString;

    std::string mInterfaceVoiInfoString;
    std::string mImplementationVoiInfoString;

    std::string mInterfaceStateInfoString;
    std::string mImplementationStateInfoString;

    std::string mInterfaceVariableInfoString;
    std::string mImplementationVariableInfoString;

    std::string mVariableInfoEntryString;
    std::string mVariableInfoWithTypeEntryString;

    std::string mVoiString;

    std::string mStatesArrayString;
    std::string mRatesArrayString;
    std::string mVariablesArrayString;

    std::string mExternalVariableMethodTypeDefinitionString;
    std::string mExternalVariableMethodParameterString;
    std::string mExternalVariableMethodCallString;

    std::string mInterfaceCreateStatesArrayMethodString;
    std::string mImplementationCreateStatesArrayMethodString;

    std::string mInterfaceCreateVariablesArrayMethodString;
    std::string mImplementationCreateVariablesArrayMethodString;

    std::string mInterfaceDeleteArrayMethodString;
    std::string mImplementationDeleteArrayMethodString;

    std::string mInterfaceInitialiseStatesAndConstantsMethodString;
    std::string mImplementationInitialiseStatesAndConstantsMethodString;

    std::string mInterfaceComputeComputedConstantsMethodString;
    std::string mImplementationComputeComputedConstantsMethodString;

    std::string mInterfaceComputeRatesMethodString;
    std::string mImplementationComputeRatesMethodString;

    std::string mInterfaceComputeVariablesMethodString;
    std::string mImplementationComputeVariablesMethodString;

    std::string mEmptyMethodString;

    std::string mIndentString;

    std::string mOpenArrayInitialiserString;
    std::string mCloseArrayInitialiserString;

    std::string mOpenArrayString;
    std::string mCloseArrayString;

    std::string mArrayElementSeparatorString;

    std::string mStringDelimiterString;

    std::string mCommandSeparatorString;

    void loadProfile(GeneratorProfile::Profile profile);
};

void GeneratorProfile::GeneratorProfileImpl::loadProfile(GeneratorProfile::Profile profile)
{
    mProfile = profile;

    if (profile == GeneratorProfile::Profile::C) {
        // Whether the profile requires an interface to be generated.

        mHasInterface = true;

        // Assignment.

        mAssignmentString = " = ";

        // Relational and logical operators.

        mEqString = " == ";
        mNeqString = " != ";
        mLtString = " < ";
        mLeqString = " <= ";
        mGtString = " > ";
        mGeqString = " >= ";
        mAndString = " && ";
        mOrString = " || ";
        mXorString = "xor";
        mNotString = "!";

        mHasEqOperator = true;
        mHasNeqOperator = true;
        mHasLtOperator = true;
        mHasLeqOperator = true;
        mHasGtOperator = true;
        mHasGeqOperator = true;
        mHasAndOperator = true;
        mHasOrOperator = true;
        mHasXorOperator = false;
        mHasNotOperator = true;

        // Arithmetic operators.

        mPlusString = "+";
        mMinusString = "-";
        mTimesString = "*";
        mDivideString = "/";
        mPowerString = "pow";
        mSquareRootString = "sqrt";
        mSquareString = "";
        mAbsoluteValueString = "fabs";
        mExponentialString = "exp";
        mNaturalLogarithmString = "log";
        mCommonLogarithmString = "log10";
        mCeilingString = "ceil";
        mFloorString = "floor";
        mMinString = "min";
        mMaxString = "max";
        mRemString = "fmod";

        mHasPowerOperator = false;

        // Trigonometric operators.

        mSinString = "sin";
        mCosString = "cos";
        mTanString = "tan";
        mSecString = "sec";
        mCscString = "csc";
        mCotString = "cot";
        mSinhString = "sinh";
        mCoshString = "cosh";
        mTanhString = "tanh";
        mSechString = "sech";
        mCschString = "csch";
        mCothString = "coth";
        mAsinString = "asin";
        mAcosString = "acos";
        mAtanString = "atan";
        mAsecString = "asec";
        mAcscString = "acsc";
        mAcotString = "acot";
        mAsinhString = "asinh";
        mAcoshString = "acosh";
        mAtanhString = "atanh";
        mAsechString = "asech";
        mAcschString = "acsch";
        mAcothString = "acoth";

        // Piecewise statement.

        mConditionalOperatorIfString = "(<CONDITION>)?<IF_STATEMENT>";
        mConditionalOperatorElseString = ":<ELSE_STATEMENT>";

        mHasConditionalOperator = true;

        // Constants.

        mTrueString = "1.0";
        mFalseString = "0.0";
        mEString = convertToString(exp(1.0));
        mPiString = convertToString(M_PI);
        mInfString = "INFINITY";
        mNanString = "NAN";

        // Arithmetic functions.

        mEqFunctionString = "";
        mNeqFunctionString = "";
        mLtFunctionString = "";
        mLeqFunctionString = "";
        mGtFunctionString = "";
        mGeqFunctionString = "";
        mAndFunctionString = "";
        mOrFunctionString = "";
        mXorFunctionString = "double xor(double x, double y)\n"
                             "{\n"
                             "    return (x != 0.0) ^ (y != 0.0);\n"
                             "}\n";
        mNotFunctionString = "";
        mMinFunctionString = "double min(double x, double y)\n"
                             "{\n"
                             "    return (x < y)?x:y;\n"
                             "}\n";
        mMaxFunctionString = "double max(double x, double y)\n"
                             "{\n"
                             "    return (x > y)?x:y;\n"
                             "}\n";

        // Trigonometric functions.

        mSecFunctionString = "double sec(double x)\n"
                             "{\n"
                             "    return 1.0/cos(x);\n"
                             "}\n";
        mCscFunctionString = "double csc(double x)\n"
                             "{\n"
                             "    return 1.0/sin(x);\n"
                             "}\n";
        mCotFunctionString = "double cot(double x)\n"
                             "{\n"
                             "    return 1.0/tan(x);\n"
                             "}\n";
        mSechFunctionString = "double sech(double x)\n"
                              "{\n"
                              "    return 1.0/cosh(x);\n"
                              "}\n";
        mCschFunctionString = "double csch(double x)\n"
                              "{\n"
                              "    return 1.0/sinh(x);\n"
                              "}\n";
        mCothFunctionString = "double coth(double x)\n"
                              "{\n"
                              "    return 1.0/tanh(x);\n"
                              "}\n";
        mAsecFunctionString = "double asec(double x)\n"
                              "{\n"
                              "    return acos(1.0/x);\n"
                              "}\n";
        mAcscFunctionString = "double acsc(double x)\n"
                              "{\n"
                              "    return asin(1.0/x);\n"
                              "}\n";
        mAcotFunctionString = "double acot(double x)\n"
                              "{\n"
                              "    return atan(1.0/x);\n"
                              "}\n";
        mAsechFunctionString = "double asech(double x)\n"
                               "{\n"
                               "    double oneOverX = 1.0/x;\n"
                               "\n"
                               "    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));\n"
                               "}\n";
        mAcschFunctionString = "double acsch(double x)\n"
                               "{\n"
                               "    double oneOverX = 1.0/x;\n"
                               "\n"
                               "    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));\n"
                               "}\n";
        mAcothFunctionString = "double acoth(double x)\n"
                               "{\n"
                               "    double oneOverX = 1.0/x;\n"
                               "\n"
                               "    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));\n"
                               "}\n";

        // Miscellaneous.

        mCommentString = "/* <CODE> */\n";
        mOriginCommentString = "The content of this file was generated using <PROFILE_INFORMATION> libCellML <LIBCELLML_VERSION>.";

        mInterfaceFileNameString = "model.h";

        mInterfaceHeaderString = "#pragma once\n"
                                 "\n"
                                 "#include <stddef.h>\n";
        mImplementationHeaderString = "#include \"<INTERFACE_FILE_NAME>\"\n"
                                      "\n"
                                      "#include <math.h>\n"
                                      "#include <stdlib.h>\n";

        mInterfaceVersionString = "extern const char VERSION[];\n";
        mImplementationVersionString = "const char VERSION[] = \"0.1.0\";\n";

        mInterfaceLibcellmlVersionString = "extern const char LIBCELLML_VERSION[];\n";
        mImplementationLibcellmlVersionString = "const char LIBCELLML_VERSION[] = \"<LIBCELLML_VERSION>\";\n";

        mInterfaceStateCountString = "extern const size_t STATE_COUNT;\n";
        mImplementationStateCountString = "const size_t STATE_COUNT = <STATE_COUNT>;\n";

        mInterfaceVariableCountString = "extern const size_t VARIABLE_COUNT;\n";
        mImplementationVariableCountString = "const size_t VARIABLE_COUNT = <VARIABLE_COUNT>;\n";

        mVariableTypeObjectString = "typedef enum {\n"
                                    "    CONSTANT,\n"
                                    "    COMPUTED_CONSTANT,\n"
                                    "    ALGEBRAIC<OPTIONAL_TYPE>\n"
                                    "} VariableType;\n";
        mVariableTypeObjectExternalTypeString = ",\n    EXTERNAL";

        mConstantVariableTypeString = "CONSTANT";
        mComputedConstantVariableTypeString = "COMPUTED_CONSTANT";
        mAlgebraicVariableTypeString = "ALGEBRAIC";
        mExternalVariableTypeString = "EXTERNAL";

        mVariableInfoObjectString = "typedef struct {\n"
                                    "    char name[<NAME_SIZE>];\n"
                                    "    char units[<UNITS_SIZE>];\n"
                                    "    char component[<COMPONENT_SIZE>];\n"
                                    "} VariableInfo;\n";
        mVariableInfoWithTypeObjectString = "typedef struct {\n"
                                            "    char name[<NAME_SIZE>];\n"
                                            "    char units[<UNITS_SIZE>];\n"
                                            "    char component[<COMPONENT_SIZE>];\n"
                                            "    VariableType type;\n"
                                            "} VariableInfoWithType;\n";

        mInterfaceVoiInfoString = "extern const VariableInfo VOI_INFO;\n";
        mImplementationVoiInfoString = "const VariableInfo VOI_INFO = <CODE>;\n";

        mInterfaceStateInfoString = "extern const VariableInfo STATE_INFO[];\n";
        mImplementationStateInfoString = "const VariableInfo STATE_INFO[] = {\n"
                                         "<CODE>"
                                         "};\n";

        mInterfaceVariableInfoString = "extern const VariableInfoWithType VARIABLE_INFO[];\n";
        mImplementationVariableInfoString = "const VariableInfoWithType VARIABLE_INFO[] = {\n"
                                            "<CODE>"
                                            "};\n";

        mVariableInfoEntryString = "{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\"}";
        mVariableInfoWithTypeEntryString = "{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\", <TYPE>}";

        mVoiString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mExternalVariableMethodTypeDefinitionString = "typedef double (* ExternalVariable)(double voi, double *states, double *rates, double *variables, size_t index);\n";
        mExternalVariableMethodParameterString = ", ExternalVariable externalVariable";
        mExternalVariableMethodCallString = "externalVariable(voi, states, rates, variables, <INDEX>)";

        mInterfaceCreateStatesArrayMethodString = "double * createStatesArray();\n";
        mImplementationCreateStatesArrayMethodString = "double * createStatesArray()\n"
                                                       "{\n"
                                                       "    return (double *) malloc(STATE_COUNT*sizeof(double));\n"
                                                       "}\n";

        mInterfaceCreateVariablesArrayMethodString = "double * createVariablesArray();\n";
        mImplementationCreateVariablesArrayMethodString = "double * createVariablesArray()\n"
                                                          "{\n"
                                                          "    return (double *) malloc(VARIABLE_COUNT*sizeof(double));\n"
                                                          "}\n";

        mInterfaceDeleteArrayMethodString = "void deleteArray(double *array);\n";
        mImplementationDeleteArrayMethodString = "void deleteArray(double *array)\n"
                                                 "{\n"
                                                 "    free(array);\n"
                                                 "}\n";

        mInterfaceInitialiseStatesAndConstantsMethodString = "void initialiseStatesAndConstants(double *states, double *variables);\n";
        mImplementationInitialiseStatesAndConstantsMethodString = "void initialiseStatesAndConstants(double *states, double *variables)\n"
                                                                  "{\n"
                                                                  "<CODE>"
                                                                  "}\n";

        mInterfaceComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables);\n";
        mImplementationComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables)\n"
                                                              "{\n"
                                                              "<CODE>"
                                                              "}\n";

        mInterfaceComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables<OPTIONAL_PARAMETER>);\n";
        mImplementationComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables<OPTIONAL_PARAMETER>)\n{\n"
                                                  "<CODE>"
                                                  "}\n";

        mInterfaceComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables<OPTIONAL_PARAMETER>);\n";
        mImplementationComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables<OPTIONAL_PARAMETER>)\n"
                                                      "{\n"
                                                      "<CODE>"
                                                      "}\n";

        mEmptyMethodString = "";

        mIndentString = "    ";

        mOpenArrayInitialiserString = "{";
        mCloseArrayInitialiserString = "}";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mArrayElementSeparatorString = ",";

        mStringDelimiterString = "\"";

        mCommandSeparatorString = ";";
    } else if (profile == GeneratorProfile::Profile::PYTHON) {
        // Whether the profile requires an interface to be generated.

        mHasInterface = false;

        // Assignment.

        mAssignmentString = " = ";

        // Relational and logical operators.

        mEqString = "eq_func";
        mNeqString = "neq_func";
        mLtString = "lt_func";
        mLeqString = "leq_func";
        mGtString = "gt_func";
        mGeqString = "geq_func";
        mAndString = "and_func";
        mOrString = "or_func";
        mXorString = "xor_func";
        mNotString = "not_func";

        mHasEqOperator = false;
        mHasNeqOperator = false;
        mHasLtOperator = false;
        mHasLeqOperator = false;
        mHasGtOperator = false;
        mHasGeqOperator = false;
        mHasAndOperator = false;
        mHasOrOperator = false;
        mHasXorOperator = false;
        mHasNotOperator = false;

        // Arithmetic operators.

        mPlusString = "+";
        mMinusString = "-";
        mTimesString = "*";
        mDivideString = "/";
        mPowerString = "pow";
        mSquareRootString = "sqrt";
        mSquareString = "";
        mAbsoluteValueString = "fabs";
        mExponentialString = "exp";
        mNaturalLogarithmString = "log";
        mCommonLogarithmString = "log10";
        mCeilingString = "ceil";
        mFloorString = "floor";
        mMinString = "min";
        mMaxString = "max";
        mRemString = "fmod";

        mHasPowerOperator = false;

        // Trigonometric operators.

        mSinString = "sin";
        mCosString = "cos";
        mTanString = "tan";
        mSecString = "sec";
        mCscString = "csc";
        mCotString = "cot";
        mSinhString = "sinh";
        mCoshString = "cosh";
        mTanhString = "tanh";
        mSechString = "sech";
        mCschString = "csch";
        mCothString = "coth";
        mAsinString = "asin";
        mAcosString = "acos";
        mAtanString = "atan";
        mAsecString = "asec";
        mAcscString = "acsc";
        mAcotString = "acot";
        mAsinhString = "asinh";
        mAcoshString = "acosh";
        mAtanhString = "atanh";
        mAsechString = "asech";
        mAcschString = "acsch";
        mAcothString = "acoth";

        // Piecewise statement.

        mConditionalOperatorIfString = "<IF_STATEMENT> if <CONDITION>";
        mConditionalOperatorElseString = " else <ELSE_STATEMENT>";

        mHasConditionalOperator = true;

        // Constants.

        mTrueString = "1.0";
        mFalseString = "0.0";
        mEString = convertToString(exp(1.0));
        mPiString = convertToString(M_PI);
        mInfString = "inf";
        mNanString = "nan";

        // Arithmetic functions.

        mEqFunctionString = "\n"
                            "def eq_func(x, y):\n"
                            "    return 1.0 if x == y else 0.0\n";
        mNeqFunctionString = "\n"
                             "def neq_func(x, y):\n"
                             "    return 1.0 if x != y else 0.0\n";
        mLtFunctionString = "\n"
                            "def lt_func(x, y):\n"
                            "    return 1.0 if x < y else 0.0\n";
        mLeqFunctionString = "\n"
                             "def leq_func(x, y):\n"
                             "    return 1.0 if x <= y else 0.0\n";
        mGtFunctionString = "\n"
                            "def gt_func(x, y):\n"
                            "    return 1.0 if x > y else 0.0\n";
        mGeqFunctionString = "\n"
                             "def geq_func(x, y):\n"
                             "    return 1.0 if x >= y else 0.0\n";
        mAndFunctionString = "\n"
                             "def and_func(x, y):\n"
                             "    return 1.0 if bool(x) & bool(y) else 0.0\n";
        mOrFunctionString = "\n"
                            "def or_func(x, y):\n"
                            "    return 1.0 if bool(x) | bool(y) else 0.0\n";
        mXorFunctionString = "\n"
                             "def xor_func(x, y):\n"
                             "    return 1.0 if bool(x) ^ bool(y) else 0.0\n";
        mNotFunctionString = "\n"
                             "def not_func(x):\n"
                             "    return 1.0 if not bool(x) else 0.0\n";
        mMinFunctionString = "\n"
                             "def min(x, y):\n"
                             "    return x if x < y else y\n";
        mMaxFunctionString = "\n"
                             "def max(x, y):\n"
                             "    return x if x > y else y\n";

        // Trigonometric functions.

        mSecFunctionString = "\n"
                             "def sec(x):\n"
                             "    return 1.0/cos(x)\n";
        mCscFunctionString = "\n"
                             "def csc(x):\n"
                             "    return 1.0/sin(x)\n";
        mCotFunctionString = "\n"
                             "def cot(x):\n"
                             "    return 1.0/tan(x)\n";
        mSechFunctionString = "\n"
                              "def sech(x):\n"
                              "    return 1.0/cosh(x)\n";
        mCschFunctionString = "\n"
                              "def csch(x):\n"
                              "    return 1.0/sinh(x)\n";
        mCothFunctionString = "\n"
                              "def coth(x):\n"
                              "    return 1.0/tanh(x)\n";
        mAsecFunctionString = "\n"
                              "def asec(x):\n"
                              "    return acos(1.0/x)\n";
        mAcscFunctionString = "\n"
                              "def acsc(x):\n"
                              "    return asin(1.0/x)\n";
        mAcotFunctionString = "\n"
                              "def acot(x):\n"
                              "    return atan(1.0/x)\n";
        mAsechFunctionString = "\n"
                               "def asech(x):\n"
                               "    one_over_x = 1.0/x\n"
                               "\n"
                               "    return log(one_over_x+sqrt(one_over_x*one_over_x-1.0))\n";
        mAcschFunctionString = "\n"
                               "def acsch(x):\n"
                               "    one_over_x = 1.0/x\n"
                               "\n"
                               "    return log(one_over_x+sqrt(one_over_x*one_over_x+1.0))\n";
        mAcothFunctionString = "\n"
                               "def acoth(x):\n"
                               "    one_over_x = 1.0/x\n"
                               "\n"
                               "    return 0.5*log((1.0+one_over_x)/(1.0-one_over_x))\n";

        // Miscellaneous.

        mCommentString = "# <CODE>\n";
        mOriginCommentString = "The content of this file was generated using <PROFILE_INFORMATION> libCellML <LIBCELLML_VERSION>.";

        mInterfaceFileNameString = "";

        mInterfaceHeaderString = "";
        mImplementationHeaderString = "from enum import Enum\n"
                                      "from math import *\n"
                                      "\n";

        mInterfaceVersionString = "";
        mImplementationVersionString = "__version__ = \"0.1.0\"\n";

        mInterfaceLibcellmlVersionString = "";
        mImplementationLibcellmlVersionString = "LIBCELLML_VERSION = \"<LIBCELLML_VERSION>\"\n";

        mInterfaceStateCountString = "";
        mImplementationStateCountString = "STATE_COUNT = <STATE_COUNT>\n";

        mInterfaceVariableCountString = "";
        mImplementationVariableCountString = "VARIABLE_COUNT = <VARIABLE_COUNT>\n";

        mVariableTypeObjectString = "\n"
                                    "class VariableType(Enum):\n"
                                    "    CONSTANT = 1\n"
                                    "    COMPUTED_CONSTANT = 2\n"
                                    "    ALGEBRAIC = 3<OPTIONAL_TYPE>\n"
                                    "\n";
        mVariableTypeObjectExternalTypeString = "\n    EXTERNAL = 4";

        mConstantVariableTypeString = "VariableType.CONSTANT";
        mComputedConstantVariableTypeString = "VariableType.COMPUTED_CONSTANT";
        mAlgebraicVariableTypeString = "VariableType.ALGEBRAIC";
        mExternalVariableTypeString = "VariableType.EXTERNAL";

        mVariableInfoObjectString = "";
        mVariableInfoWithTypeObjectString = "";

        mInterfaceVoiInfoString = "";
        mImplementationVoiInfoString = "VOI_INFO = <CODE>\n";

        mInterfaceStateInfoString = "";
        mImplementationStateInfoString = "STATE_INFO = [\n"
                                         "<CODE>"
                                         "]\n";

        mInterfaceVariableInfoString = "";
        mImplementationVariableInfoString = "VARIABLE_INFO = [\n"
                                            "<CODE>"
                                            "]\n";

        mVariableInfoEntryString = "{\"name\": \"<NAME>\", \"units\": \"<UNITS>\", \"component\": \"<COMPONENT>\"}";
        mVariableInfoWithTypeEntryString = "{\"name\": \"<NAME>\", \"units\": \"<UNITS>\", \"component\": \"<COMPONENT>\", \"type\": <TYPE>}";

        mVoiString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mExternalVariableMethodTypeDefinitionString = "";
        mExternalVariableMethodParameterString = ", external_variable";
        mExternalVariableMethodCallString = "external_variable(voi, states, rates, variables, <INDEX>)";

        mInterfaceCreateStatesArrayMethodString = "";
        mImplementationCreateStatesArrayMethodString = "\n"
                                                       "def create_states_array():\n"
                                                       "    return [nan]*STATE_COUNT\n";

        mInterfaceCreateVariablesArrayMethodString = "";
        mImplementationCreateVariablesArrayMethodString = "\n"
                                                          "def create_variables_array():\n"
                                                          "    return [nan]*VARIABLE_COUNT\n";

        mInterfaceDeleteArrayMethodString = "";
        mImplementationDeleteArrayMethodString = "";

        mInterfaceInitialiseStatesAndConstantsMethodString = "";
        mImplementationInitialiseStatesAndConstantsMethodString = "\n"
                                                                  "def initialise_states_and_constants(states, variables):\n"
                                                                  "<CODE>";

        mInterfaceComputeComputedConstantsMethodString = "";
        mImplementationComputeComputedConstantsMethodString = "\n"
                                                              "def compute_computed_constants(variables):\n"
                                                              "<CODE>";

        mInterfaceComputeRatesMethodString = "";
        mImplementationComputeRatesMethodString = "\n"
                                                  "def compute_rates(voi, states, rates, variables<OPTIONAL_PARAMETER>):\n"
                                                  "<CODE>";

        mInterfaceComputeVariablesMethodString = "";
        mImplementationComputeVariablesMethodString = "\n"
                                                      "def compute_variables(voi, states, rates, variables<OPTIONAL_PARAMETER>):\n"
                                                      "<CODE>";

        mEmptyMethodString = "pass\n";

        mIndentString = "    ";

        mOpenArrayInitialiserString = "[";
        mCloseArrayInitialiserString = "]";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mArrayElementSeparatorString = ",";

        mStringDelimiterString = "\"";

        mCommandSeparatorString = "";
    }
}

GeneratorProfile::GeneratorProfile(Profile profile)
    : mPimpl(new GeneratorProfileImpl())
{
    setProfile(profile);
}

GeneratorProfile::~GeneratorProfile()
{
    delete mPimpl;
}

GeneratorProfilePtr GeneratorProfile::create(Profile profile) noexcept
{
    return std::shared_ptr<GeneratorProfile> {new GeneratorProfile {profile}};
}

GeneratorProfile::Profile GeneratorProfile::profile() const
{
    return mPimpl->mProfile;
}

void GeneratorProfile::setProfile(Profile profile)
{
    mPimpl->loadProfile(profile);
}

bool GeneratorProfile::hasInterface() const
{
    return mPimpl->mHasInterface;
}

void GeneratorProfile::setHasInterface(bool hasInterface)
{
    mPimpl->mHasInterface = hasInterface;
}

std::string GeneratorProfile::assignmentString() const
{
    return mPimpl->mAssignmentString;
}

void GeneratorProfile::setAssignmentString(const std::string &assignmentString)
{
    mPimpl->mAssignmentString = assignmentString;
}

std::string GeneratorProfile::eqString() const
{
    return mPimpl->mEqString;
}

void GeneratorProfile::setEqString(const std::string &eqString)
{
    mPimpl->mEqString = eqString;
}

std::string GeneratorProfile::neqString() const
{
    return mPimpl->mNeqString;
}

void GeneratorProfile::setNeqString(const std::string &neqString)
{
    mPimpl->mNeqString = neqString;
}

std::string GeneratorProfile::ltString() const
{
    return mPimpl->mLtString;
}

void GeneratorProfile::setLtString(const std::string &ltString)
{
    mPimpl->mLtString = ltString;
}

std::string GeneratorProfile::leqString() const
{
    return mPimpl->mLeqString;
}

void GeneratorProfile::setLeqString(const std::string &leqString)
{
    mPimpl->mLeqString = leqString;
}

std::string GeneratorProfile::gtString() const
{
    return mPimpl->mGtString;
}

void GeneratorProfile::setGtString(const std::string &gtString)
{
    mPimpl->mGtString = gtString;
}

std::string GeneratorProfile::geqString() const
{
    return mPimpl->mGeqString;
}

void GeneratorProfile::setGeqString(const std::string &geqString)
{
    mPimpl->mGeqString = geqString;
}

std::string GeneratorProfile::andString() const
{
    return mPimpl->mAndString;
}

void GeneratorProfile::setAndString(const std::string &andString)
{
    mPimpl->mAndString = andString;
}

std::string GeneratorProfile::orString() const
{
    return mPimpl->mOrString;
}

void GeneratorProfile::setOrString(const std::string &orString)
{
    mPimpl->mOrString = orString;
}

std::string GeneratorProfile::xorString() const
{
    return mPimpl->mXorString;
}

void GeneratorProfile::setXorString(const std::string &xorString)
{
    mPimpl->mXorString = xorString;
}

std::string GeneratorProfile::notString() const
{
    return mPimpl->mNotString;
}

void GeneratorProfile::setNotString(const std::string &notString)
{
    mPimpl->mNotString = notString;
}

bool GeneratorProfile::hasEqOperator() const
{
    return mPimpl->mHasEqOperator;
}

void GeneratorProfile::setHasEqOperator(bool hasEqOperator)
{
    mPimpl->mHasEqOperator = hasEqOperator;
}

bool GeneratorProfile::hasNeqOperator() const
{
    return mPimpl->mHasNeqOperator;
}

void GeneratorProfile::setHasNeqOperator(bool hasNeqOperator)
{
    mPimpl->mHasNeqOperator = hasNeqOperator;
}

bool GeneratorProfile::hasLtOperator() const
{
    return mPimpl->mHasLtOperator;
}

void GeneratorProfile::setHasLtOperator(bool hasLtOperator)
{
    mPimpl->mHasLtOperator = hasLtOperator;
}

bool GeneratorProfile::hasLeqOperator() const
{
    return mPimpl->mHasLeqOperator;
}

void GeneratorProfile::setHasLeqOperator(bool hasLeqOperator)
{
    mPimpl->mHasLeqOperator = hasLeqOperator;
}

bool GeneratorProfile::hasGtOperator() const
{
    return mPimpl->mHasGtOperator;
}

void GeneratorProfile::setHasGtOperator(bool hasGtOperator)
{
    mPimpl->mHasGtOperator = hasGtOperator;
}

bool GeneratorProfile::hasGeqOperator() const
{
    return mPimpl->mHasGeqOperator;
}

void GeneratorProfile::setHasGeqOperator(bool hasGeqOperator)
{
    mPimpl->mHasGeqOperator = hasGeqOperator;
}

bool GeneratorProfile::hasAndOperator() const
{
    return mPimpl->mHasAndOperator;
}

void GeneratorProfile::setHasAndOperator(bool hasAndOperator)
{
    mPimpl->mHasAndOperator = hasAndOperator;
}

bool GeneratorProfile::hasOrOperator() const
{
    return mPimpl->mHasOrOperator;
}

void GeneratorProfile::setHasOrOperator(bool hasOrOperator)
{
    mPimpl->mHasOrOperator = hasOrOperator;
}

bool GeneratorProfile::hasXorOperator() const
{
    return mPimpl->mHasXorOperator;
}

void GeneratorProfile::setHasXorOperator(bool hasXorOperator)
{
    mPimpl->mHasXorOperator = hasXorOperator;
}

bool GeneratorProfile::hasNotOperator() const
{
    return mPimpl->mHasNotOperator;
}

void GeneratorProfile::setHasNotOperator(bool hasNotOperator)
{
    mPimpl->mHasNotOperator = hasNotOperator;
}

std::string GeneratorProfile::plusString() const
{
    return mPimpl->mPlusString;
}

void GeneratorProfile::setPlusString(const std::string &plusString)
{
    mPimpl->mPlusString = plusString;
}

std::string GeneratorProfile::minusString() const
{
    return mPimpl->mMinusString;
}

void GeneratorProfile::setMinusString(const std::string &minusString)
{
    mPimpl->mMinusString = minusString;
}

std::string GeneratorProfile::timesString() const
{
    return mPimpl->mTimesString;
}

void GeneratorProfile::setTimesString(const std::string &timesString)
{
    mPimpl->mTimesString = timesString;
}

std::string GeneratorProfile::divideString() const
{
    return mPimpl->mDivideString;
}

void GeneratorProfile::setDivideString(const std::string &divideString)
{
    mPimpl->mDivideString = divideString;
}

std::string GeneratorProfile::powerString() const
{
    return mPimpl->mPowerString;
}

void GeneratorProfile::setPowerString(const std::string &powerString)
{
    mPimpl->mPowerString = powerString;
}

std::string GeneratorProfile::squareRootString() const
{
    return mPimpl->mSquareRootString;
}

void GeneratorProfile::setSquareRootString(const std::string &squareRootString)
{
    mPimpl->mSquareRootString = squareRootString;
}

std::string GeneratorProfile::squareString() const
{
    return mPimpl->mSquareString;
}

void GeneratorProfile::setSquareString(const std::string &squareString)
{
    mPimpl->mSquareString = squareString;
}

std::string GeneratorProfile::absoluteValueString() const
{
    return mPimpl->mAbsoluteValueString;
}

void GeneratorProfile::setAbsoluteValueString(const std::string &absoluteValueString)
{
    mPimpl->mAbsoluteValueString = absoluteValueString;
}

std::string GeneratorProfile::exponentialString() const
{
    return mPimpl->mExponentialString;
}

void GeneratorProfile::setExponentialString(const std::string &exponentialString)
{
    mPimpl->mExponentialString = exponentialString;
}

std::string GeneratorProfile::naturalLogarithmString() const
{
    return mPimpl->mNaturalLogarithmString;
}

void GeneratorProfile::setNaturalLogarithmString(const std::string &naturalLogarithmString)
{
    mPimpl->mNaturalLogarithmString = naturalLogarithmString;
}

std::string GeneratorProfile::commonLogarithmString() const
{
    return mPimpl->mCommonLogarithmString;
}

void GeneratorProfile::setCommonLogarithmString(const std::string &commonLogarithmString)
{
    mPimpl->mCommonLogarithmString = commonLogarithmString;
}

std::string GeneratorProfile::ceilingString() const
{
    return mPimpl->mCeilingString;
}

void GeneratorProfile::setCeilingString(const std::string &ceilingString)
{
    mPimpl->mCeilingString = ceilingString;
}

std::string GeneratorProfile::floorString() const
{
    return mPimpl->mFloorString;
}

void GeneratorProfile::setFloorString(const std::string &floorString)
{
    mPimpl->mFloorString = floorString;
}

std::string GeneratorProfile::minString() const
{
    return mPimpl->mMinString;
}

void GeneratorProfile::setMinString(const std::string &minString)
{
    mPimpl->mMinString = minString;
}

std::string GeneratorProfile::maxString() const
{
    return mPimpl->mMaxString;
}

void GeneratorProfile::setMaxString(const std::string &maxString)
{
    mPimpl->mMaxString = maxString;
}

std::string GeneratorProfile::remString() const
{
    return mPimpl->mRemString;
}

void GeneratorProfile::setRemString(const std::string &remString)
{
    mPimpl->mRemString = remString;
}

bool GeneratorProfile::hasPowerOperator() const
{
    return mPimpl->mHasPowerOperator;
}

void GeneratorProfile::setHasPowerOperator(bool hasPowerOperator)
{
    mPimpl->mHasPowerOperator = hasPowerOperator;
}

std::string GeneratorProfile::sinString() const
{
    return mPimpl->mSinString;
}

void GeneratorProfile::setSinString(const std::string &sinString)
{
    mPimpl->mSinString = sinString;
}

std::string GeneratorProfile::cosString() const
{
    return mPimpl->mCosString;
}

void GeneratorProfile::setCosString(const std::string &cosString)
{
    mPimpl->mCosString = cosString;
}

std::string GeneratorProfile::tanString() const
{
    return mPimpl->mTanString;
}

void GeneratorProfile::setTanString(const std::string &tanString)
{
    mPimpl->mTanString = tanString;
}

std::string GeneratorProfile::secString() const
{
    return mPimpl->mSecString;
}

void GeneratorProfile::setSecString(const std::string &secString)
{
    mPimpl->mSecString = secString;
}

std::string GeneratorProfile::cscString() const
{
    return mPimpl->mCscString;
}

void GeneratorProfile::setCscString(const std::string &cscString)
{
    mPimpl->mCscString = cscString;
}

std::string GeneratorProfile::cotString() const
{
    return mPimpl->mCotString;
}

void GeneratorProfile::setCotString(const std::string &cotString)
{
    mPimpl->mCotString = cotString;
}

std::string GeneratorProfile::sinhString() const
{
    return mPimpl->mSinhString;
}

void GeneratorProfile::setSinhString(const std::string &sinhString)
{
    mPimpl->mSinhString = sinhString;
}

std::string GeneratorProfile::coshString() const
{
    return mPimpl->mCoshString;
}

void GeneratorProfile::setCoshString(const std::string &coshString)
{
    mPimpl->mCoshString = coshString;
}

std::string GeneratorProfile::tanhString() const
{
    return mPimpl->mTanhString;
}

void GeneratorProfile::setTanhString(const std::string &tanhString)
{
    mPimpl->mTanhString = tanhString;
}

std::string GeneratorProfile::sechString() const
{
    return mPimpl->mSechString;
}

void GeneratorProfile::setSechString(const std::string &sechString)
{
    mPimpl->mSechString = sechString;
}

std::string GeneratorProfile::cschString() const
{
    return mPimpl->mCschString;
}

void GeneratorProfile::setCschString(const std::string &cschString)
{
    mPimpl->mCschString = cschString;
}

std::string GeneratorProfile::cothString() const
{
    return mPimpl->mCothString;
}

void GeneratorProfile::setCothString(const std::string &cothString)
{
    mPimpl->mCothString = cothString;
}

std::string GeneratorProfile::asinString() const
{
    return mPimpl->mAsinString;
}

void GeneratorProfile::setAsinString(const std::string &asinString)
{
    mPimpl->mAsinString = asinString;
}

std::string GeneratorProfile::acosString() const
{
    return mPimpl->mAcosString;
}

void GeneratorProfile::setAcosString(const std::string &acosString)
{
    mPimpl->mAcosString = acosString;
}

std::string GeneratorProfile::atanString() const
{
    return mPimpl->mAtanString;
}

void GeneratorProfile::setAtanString(const std::string &atanString)
{
    mPimpl->mAtanString = atanString;
}

std::string GeneratorProfile::asecString() const
{
    return mPimpl->mAsecString;
}

void GeneratorProfile::setAsecString(const std::string &asecString)
{
    mPimpl->mAsecString = asecString;
}

std::string GeneratorProfile::acscString() const
{
    return mPimpl->mAcscString;
}

void GeneratorProfile::setAcscString(const std::string &acscString)
{
    mPimpl->mAcscString = acscString;
}

std::string GeneratorProfile::acotString() const
{
    return mPimpl->mAcotString;
}

void GeneratorProfile::setAcotString(const std::string &acotString)
{
    mPimpl->mAcotString = acotString;
}

std::string GeneratorProfile::asinhString() const
{
    return mPimpl->mAsinhString;
}

void GeneratorProfile::setAsinhString(const std::string &asinhString)
{
    mPimpl->mAsinhString = asinhString;
}

std::string GeneratorProfile::acoshString() const
{
    return mPimpl->mAcoshString;
}

void GeneratorProfile::setAcoshString(const std::string &acoshString)
{
    mPimpl->mAcoshString = acoshString;
}

std::string GeneratorProfile::atanhString() const
{
    return mPimpl->mAtanhString;
}

void GeneratorProfile::setAtanhString(const std::string &atanhString)
{
    mPimpl->mAtanhString = atanhString;
}

std::string GeneratorProfile::asechString() const
{
    return mPimpl->mAsechString;
}

void GeneratorProfile::setAsechString(const std::string &asechString)
{
    mPimpl->mAsechString = asechString;
}

std::string GeneratorProfile::acschString() const
{
    return mPimpl->mAcschString;
}

void GeneratorProfile::setAcschString(const std::string &acschString)
{
    mPimpl->mAcschString = acschString;
}

std::string GeneratorProfile::acothString() const
{
    return mPimpl->mAcothString;
}

void GeneratorProfile::setAcothString(const std::string &acothString)
{
    mPimpl->mAcothString = acothString;
}

std::string GeneratorProfile::conditionalOperatorIfString() const
{
    return mPimpl->mConditionalOperatorIfString;
}

void GeneratorProfile::setConditionalOperatorIfString(const std::string &conditionalOperatorIfString)
{
    mPimpl->mConditionalOperatorIfString = conditionalOperatorIfString;
}

std::string GeneratorProfile::conditionalOperatorElseString() const
{
    return mPimpl->mConditionalOperatorElseString;
}

void GeneratorProfile::setConditionalOperatorElseString(const std::string &conditionalOperatorElseString)
{
    mPimpl->mConditionalOperatorElseString = conditionalOperatorElseString;
}

std::string GeneratorProfile::piecewiseIfString() const
{
    return mPimpl->mPiecewiseIfString;
}

void GeneratorProfile::setPiecewiseIfString(const std::string &piecewiseIfString)
{
    mPimpl->mPiecewiseIfString = piecewiseIfString;
}

std::string GeneratorProfile::piecewiseElseString() const
{
    return mPimpl->mPiecewiseElseString;
}

void GeneratorProfile::setPiecewiseElseString(const std::string &piecewiseElseString)
{
    mPimpl->mPiecewiseElseString = piecewiseElseString;
}

bool GeneratorProfile::hasConditionalOperator() const
{
    return mPimpl->mHasConditionalOperator;
}

void GeneratorProfile::setHasConditionalOperator(bool hasConditionalOperator)
{
    mPimpl->mHasConditionalOperator = hasConditionalOperator;
}

std::string GeneratorProfile::trueString() const
{
    return mPimpl->mTrueString;
}

void GeneratorProfile::setTrueString(const std::string &trueString)
{
    mPimpl->mTrueString = trueString;
}

std::string GeneratorProfile::falseString() const
{
    return mPimpl->mFalseString;
}

void GeneratorProfile::setFalseString(const std::string &falseString)
{
    mPimpl->mFalseString = falseString;
}

std::string GeneratorProfile::eString() const
{
    return mPimpl->mEString;
}

void GeneratorProfile::setEString(const std::string &eString)
{
    mPimpl->mEString = eString;
}

std::string GeneratorProfile::piString() const
{
    return mPimpl->mPiString;
}

void GeneratorProfile::setPiString(const std::string &piString)
{
    mPimpl->mPiString = piString;
}

std::string GeneratorProfile::infString() const
{
    return mPimpl->mInfString;
}

void GeneratorProfile::setInfString(const std::string &infString)
{
    mPimpl->mInfString = infString;
}

std::string GeneratorProfile::nanString() const
{
    return mPimpl->mNanString;
}

void GeneratorProfile::setNanString(const std::string &nanString)
{
    mPimpl->mNanString = nanString;
}

std::string GeneratorProfile::eqFunctionString() const
{
    return mPimpl->mEqFunctionString;
}

void GeneratorProfile::setEqFunctionString(const std::string &eqFunctionString)
{
    mPimpl->mEqFunctionString = eqFunctionString;
}

std::string GeneratorProfile::neqFunctionString() const
{
    return mPimpl->mNeqFunctionString;
}

void GeneratorProfile::setNeqFunctionString(const std::string &neqFunctionString)
{
    mPimpl->mNeqFunctionString = neqFunctionString;
}

std::string GeneratorProfile::ltFunctionString() const
{
    return mPimpl->mLtFunctionString;
}

void GeneratorProfile::setLtFunctionString(const std::string &ltFunctionString)
{
    mPimpl->mLtFunctionString = ltFunctionString;
}

std::string GeneratorProfile::leqFunctionString() const
{
    return mPimpl->mLeqFunctionString;
}

void GeneratorProfile::setLeqFunctionString(const std::string &leqFunctionString)
{
    mPimpl->mLeqFunctionString = leqFunctionString;
}

std::string GeneratorProfile::gtFunctionString() const
{
    return mPimpl->mGtFunctionString;
}

void GeneratorProfile::setGtFunctionString(const std::string &gtFunctionString)
{
    mPimpl->mGtFunctionString = gtFunctionString;
}

std::string GeneratorProfile::geqFunctionString() const
{
    return mPimpl->mGeqFunctionString;
}

void GeneratorProfile::setGeqFunctionString(const std::string &geqFunctionString)
{
    mPimpl->mGeqFunctionString = geqFunctionString;
}

std::string GeneratorProfile::andFunctionString() const
{
    return mPimpl->mAndFunctionString;
}

void GeneratorProfile::setAndFunctionString(const std::string &andFunctionString)
{
    mPimpl->mAndFunctionString = andFunctionString;
}

std::string GeneratorProfile::orFunctionString() const
{
    return mPimpl->mOrFunctionString;
}

void GeneratorProfile::setOrFunctionString(const std::string &orFunctionString)
{
    mPimpl->mOrFunctionString = orFunctionString;
}

std::string GeneratorProfile::xorFunctionString() const
{
    return mPimpl->mXorFunctionString;
}

void GeneratorProfile::setXorFunctionString(const std::string &xorFunctionString)
{
    mPimpl->mXorFunctionString = xorFunctionString;
}

std::string GeneratorProfile::notFunctionString() const
{
    return mPimpl->mNotFunctionString;
}

void GeneratorProfile::setNotFunctionString(const std::string &notFunctionString)
{
    mPimpl->mNotFunctionString = notFunctionString;
}

std::string GeneratorProfile::minFunctionString() const
{
    return mPimpl->mMinFunctionString;
}

void GeneratorProfile::setMinFunctionString(const std::string &minFunctionString)
{
    mPimpl->mMinFunctionString = minFunctionString;
}

std::string GeneratorProfile::maxFunctionString() const
{
    return mPimpl->mMaxFunctionString;
}

void GeneratorProfile::setMaxFunctionString(const std::string &maxFunctionString)
{
    mPimpl->mMaxFunctionString = maxFunctionString;
}

std::string GeneratorProfile::secFunctionString() const
{
    return mPimpl->mSecFunctionString;
}

void GeneratorProfile::setSecFunctionString(const std::string &secFunctionString)
{
    mPimpl->mSecFunctionString = secFunctionString;
}

std::string GeneratorProfile::cscFunctionString() const
{
    return mPimpl->mCscFunctionString;
}

void GeneratorProfile::setCscFunctionString(const std::string &cscFunctionString)
{
    mPimpl->mCscFunctionString = cscFunctionString;
}

std::string GeneratorProfile::cotFunctionString() const
{
    return mPimpl->mCotFunctionString;
}

void GeneratorProfile::setCotFunctionString(const std::string &cotFunctionString)
{
    mPimpl->mCotFunctionString = cotFunctionString;
}

std::string GeneratorProfile::sechFunctionString() const
{
    return mPimpl->mSechFunctionString;
}

void GeneratorProfile::setSechFunctionString(const std::string &sechFunctionString)
{
    mPimpl->mSechFunctionString = sechFunctionString;
}

std::string GeneratorProfile::cschFunctionString() const
{
    return mPimpl->mCschFunctionString;
}

void GeneratorProfile::setCschFunctionString(const std::string &cschFunctionString)
{
    mPimpl->mCschFunctionString = cschFunctionString;
}

std::string GeneratorProfile::cothFunctionString() const
{
    return mPimpl->mCothFunctionString;
}

void GeneratorProfile::setCothFunctionString(const std::string &cothFunctionString)
{
    mPimpl->mCothFunctionString = cothFunctionString;
}

std::string GeneratorProfile::asecFunctionString() const
{
    return mPimpl->mAsecFunctionString;
}

void GeneratorProfile::setAsecFunctionString(const std::string &asecFunctionString)
{
    mPimpl->mAsecFunctionString = asecFunctionString;
}

std::string GeneratorProfile::acscFunctionString() const
{
    return mPimpl->mAcscFunctionString;
}

void GeneratorProfile::setAcscFunctionString(const std::string &acscFunctionString)
{
    mPimpl->mAcscFunctionString = acscFunctionString;
}

std::string GeneratorProfile::acotFunctionString() const
{
    return mPimpl->mAcotFunctionString;
}

void GeneratorProfile::setAcotFunctionString(const std::string &acotFunctionString)
{
    mPimpl->mAcotFunctionString = acotFunctionString;
}

std::string GeneratorProfile::asechFunctionString() const
{
    return mPimpl->mAsechFunctionString;
}

void GeneratorProfile::setAsechFunctionString(const std::string &asechFunctionString)
{
    mPimpl->mAsechFunctionString = asechFunctionString;
}

std::string GeneratorProfile::acschFunctionString() const
{
    return mPimpl->mAcschFunctionString;
}

void GeneratorProfile::setAcschFunctionString(const std::string &acschFunctionString)
{
    mPimpl->mAcschFunctionString = acschFunctionString;
}

std::string GeneratorProfile::acothFunctionString() const
{
    return mPimpl->mAcothFunctionString;
}

void GeneratorProfile::setAcothFunctionString(const std::string &acothFunctionString)
{
    mPimpl->mAcothFunctionString = acothFunctionString;
}

std::string GeneratorProfile::commentString() const
{
    return mPimpl->mCommentString;
}

void GeneratorProfile::setCommentString(const std::string &commentString)
{
    mPimpl->mCommentString = commentString;
}

std::string GeneratorProfile::originCommentString() const
{
    return mPimpl->mOriginCommentString;
}

void GeneratorProfile::setOriginCommentString(const std::string &originCommentString)
{
    mPimpl->mOriginCommentString = originCommentString;
}

std::string GeneratorProfile::interfaceFileNameString() const
{
    return mPimpl->mInterfaceFileNameString;
}

void GeneratorProfile::setInterfaceFileNameString(const std::string &interfaceFileNameString)
{
    mPimpl->mInterfaceFileNameString = interfaceFileNameString;
}

std::string GeneratorProfile::interfaceHeaderString() const
{
    return mPimpl->mInterfaceHeaderString;
}

void GeneratorProfile::setInterfaceHeaderString(const std::string &interfaceHeaderString)
{
    mPimpl->mInterfaceHeaderString = interfaceHeaderString;
}

std::string GeneratorProfile::implementationHeaderString() const
{
    return mPimpl->mImplementationHeaderString;
}

void GeneratorProfile::setImplementationHeaderString(const std::string &implementationHeaderString)
{
    mPimpl->mImplementationHeaderString = implementationHeaderString;
}

std::string GeneratorProfile::interfaceVersionString() const
{
    return mPimpl->mInterfaceVersionString;
}

void GeneratorProfile::setInterfaceVersionString(const std::string &interfaceVersionString)
{
    mPimpl->mInterfaceVersionString = interfaceVersionString;
}

std::string GeneratorProfile::implementationVersionString() const
{
    return mPimpl->mImplementationVersionString;
}

void GeneratorProfile::setImplementationVersionString(const std::string &implementationVersionString)
{
    mPimpl->mImplementationVersionString = implementationVersionString;
}

std::string GeneratorProfile::interfaceLibcellmlVersionString() const
{
    return mPimpl->mInterfaceLibcellmlVersionString;
}

void GeneratorProfile::setInterfaceLibcellmlVersionString(const std::string &interfaceLibcellmlVersionString)
{
    mPimpl->mInterfaceLibcellmlVersionString = interfaceLibcellmlVersionString;
}

std::string GeneratorProfile::implementationLibcellmlVersionString() const
{
    return mPimpl->mImplementationLibcellmlVersionString;
}

void GeneratorProfile::setImplementationLibcellmlVersionString(const std::string &implementationLibcellmlVersionString)
{
    mPimpl->mImplementationLibcellmlVersionString = implementationLibcellmlVersionString;
}

std::string GeneratorProfile::interfaceStateCountString() const
{
    return mPimpl->mInterfaceStateCountString;
}

void GeneratorProfile::setInterfaceStateCountString(const std::string &interfaceStateCountString)
{
    mPimpl->mInterfaceStateCountString = interfaceStateCountString;
}

std::string GeneratorProfile::implementationStateCountString() const
{
    return mPimpl->mImplementationStateCountString;
}

void GeneratorProfile::setImplementationStateCountString(const std::string &implementationStateCountString)
{
    mPimpl->mImplementationStateCountString = implementationStateCountString;
}

std::string GeneratorProfile::interfaceVariableCountString() const
{
    return mPimpl->mInterfaceVariableCountString;
}

void GeneratorProfile::setInterfaceVariableCountString(const std::string &interfaceVariableCountString)
{
    mPimpl->mInterfaceVariableCountString = interfaceVariableCountString;
}

std::string GeneratorProfile::implementationVariableCountString() const
{
    return mPimpl->mImplementationVariableCountString;
}

void GeneratorProfile::setImplementationVariableCountString(const std::string &implementationVariableCountString)
{
    mPimpl->mImplementationVariableCountString = implementationVariableCountString;
}

std::string GeneratorProfile::variableTypeObjectString() const
{
    return mPimpl->mVariableTypeObjectString;
}

void GeneratorProfile::setVariableTypeObjectString(const std::string &variableTypeObjectString)
{
    mPimpl->mVariableTypeObjectString = variableTypeObjectString;
}

std::string GeneratorProfile::variableTypeObjectExternalTypeString() const
{
    return mPimpl->mVariableTypeObjectExternalTypeString;
}

void GeneratorProfile::setVariableTypeObjectExternalTypeString(const std::string &variableTypeObjectExternalTypeString)
{
    mPimpl->mVariableTypeObjectExternalTypeString = variableTypeObjectExternalTypeString;
}

std::string GeneratorProfile::constantVariableTypeString() const
{
    return mPimpl->mConstantVariableTypeString;
}

void GeneratorProfile::setConstantVariableTypeString(const std::string &constantVariableTypeString)
{
    mPimpl->mConstantVariableTypeString = constantVariableTypeString;
}

std::string GeneratorProfile::computedConstantVariableTypeString() const
{
    return mPimpl->mComputedConstantVariableTypeString;
}

void GeneratorProfile::setComputedConstantVariableTypeString(const std::string &computedConstantVariableTypeString)
{
    mPimpl->mComputedConstantVariableTypeString = computedConstantVariableTypeString;
}

std::string GeneratorProfile::algebraicVariableTypeString() const
{
    return mPimpl->mAlgebraicVariableTypeString;
}

void GeneratorProfile::setAlgebraicVariableTypeString(const std::string &algebraicVariableTypeString)
{
    mPimpl->mAlgebraicVariableTypeString = algebraicVariableTypeString;
}

std::string GeneratorProfile::externalVariableTypeString() const
{
    return mPimpl->mExternalVariableTypeString;
}

void GeneratorProfile::setExternalVariableTypeString(const std::string &externalVariableTypeString)
{
    mPimpl->mExternalVariableTypeString = externalVariableTypeString;
}

std::string GeneratorProfile::variableInfoObjectString() const
{
    return mPimpl->mVariableInfoObjectString;
}

void GeneratorProfile::setVariableInfoObjectString(const std::string &variableInfoObjectString)
{
    mPimpl->mVariableInfoObjectString = variableInfoObjectString;
}

std::string GeneratorProfile::variableInfoWithTypeObjectString() const
{
    return mPimpl->mVariableInfoWithTypeObjectString;
}

void GeneratorProfile::setVariableInfoWithTypeObjectString(const std::string &variableInfoWithTypeObjectString)
{
    mPimpl->mVariableInfoWithTypeObjectString = variableInfoWithTypeObjectString;
}

std::string GeneratorProfile::interfaceVoiInfoString() const
{
    return mPimpl->mInterfaceVoiInfoString;
}

void GeneratorProfile::setInterfaceVoiInfoString(const std::string &interfaceVoiInfoString)
{
    mPimpl->mInterfaceVoiInfoString = interfaceVoiInfoString;
}

std::string GeneratorProfile::implementationVoiInfoString() const
{
    return mPimpl->mImplementationVoiInfoString;
}

void GeneratorProfile::setImplementationVoiInfoString(const std::string &implementationVoiInfoString)
{
    mPimpl->mImplementationVoiInfoString = implementationVoiInfoString;
}

std::string GeneratorProfile::interfaceStateInfoString() const
{
    return mPimpl->mInterfaceStateInfoString;
}

void GeneratorProfile::setInterfaceStateInfoString(const std::string &interfaceStateInfoString)
{
    mPimpl->mInterfaceStateInfoString = interfaceStateInfoString;
}

std::string GeneratorProfile::implementationStateInfoString() const
{
    return mPimpl->mImplementationStateInfoString;
}

void GeneratorProfile::setImplementationStateInfoString(const std::string &implementationStateInfoString)
{
    mPimpl->mImplementationStateInfoString = implementationStateInfoString;
}

std::string GeneratorProfile::interfaceVariableInfoString() const
{
    return mPimpl->mInterfaceVariableInfoString;
}

void GeneratorProfile::setInterfaceVariableInfoString(const std::string &interfaceVariableInfoString)
{
    mPimpl->mInterfaceVariableInfoString = interfaceVariableInfoString;
}

std::string GeneratorProfile::implementationVariableInfoString() const
{
    return mPimpl->mImplementationVariableInfoString;
}

void GeneratorProfile::setImplementationVariableInfoString(const std::string &implementationVariableInfoString)
{
    mPimpl->mImplementationVariableInfoString = implementationVariableInfoString;
}

std::string GeneratorProfile::variableInfoEntryString() const
{
    return mPimpl->mVariableInfoEntryString;
}

void GeneratorProfile::setVariableInfoEntryString(const std::string &variableInfoEntryString)
{
    mPimpl->mVariableInfoEntryString = variableInfoEntryString;
}

std::string GeneratorProfile::variableInfoWithTypeEntryString() const
{
    return mPimpl->mVariableInfoWithTypeEntryString;
}

void GeneratorProfile::setVariableInfoWithTypeEntryString(const std::string &variableInfoWithTypeEntryString)
{
    mPimpl->mVariableInfoWithTypeEntryString = variableInfoWithTypeEntryString;
}

std::string GeneratorProfile::voiString() const
{
    return mPimpl->mVoiString;
}

void GeneratorProfile::setVoiString(const std::string &voiString)
{
    mPimpl->mVoiString = voiString;
}

std::string GeneratorProfile::statesArrayString() const
{
    return mPimpl->mStatesArrayString;
}

void GeneratorProfile::setStatesArrayString(const std::string &statesArrayString)
{
    mPimpl->mStatesArrayString = statesArrayString;
}

std::string GeneratorProfile::ratesArrayString() const
{
    return mPimpl->mRatesArrayString;
}

void GeneratorProfile::setRatesArrayString(const std::string &ratesArrayString)
{
    mPimpl->mRatesArrayString = ratesArrayString;
}

std::string GeneratorProfile::variablesArrayString() const
{
    return mPimpl->mVariablesArrayString;
}

void GeneratorProfile::setVariablesArrayString(const std::string &variablesArrayString)
{
    mPimpl->mVariablesArrayString = variablesArrayString;
}

std::string GeneratorProfile::externalVariableMethodTypeDefinitionString() const
{
    return mPimpl->mExternalVariableMethodTypeDefinitionString;
}

void GeneratorProfile::setExternalVariableMethodTypeDefinitionString(const std::string &externalVariableMethodTypeDefinitionString)
{
    mPimpl->mExternalVariableMethodTypeDefinitionString = externalVariableMethodTypeDefinitionString;
}

std::string GeneratorProfile::externalVariableMethodParameterString() const
{
    return mPimpl->mExternalVariableMethodParameterString;
}

void GeneratorProfile::setExternalVariableMethodParameterString(const std::string &externalVariableMethodParameterString)
{
    mPimpl->mExternalVariableMethodParameterString = externalVariableMethodParameterString;
}

std::string GeneratorProfile::externalVariableMethodCallString() const
{
    return mPimpl->mExternalVariableMethodCallString;
}

void GeneratorProfile::setExternalVariableMethodCallString(const std::string &externalVariableMethodCallString)
{
    mPimpl->mExternalVariableMethodCallString = externalVariableMethodCallString;
}

std::string GeneratorProfile::interfaceCreateStatesArrayMethodString() const
{
    return mPimpl->mInterfaceCreateStatesArrayMethodString;
}

void GeneratorProfile::setInterfaceCreateStatesArrayMethodString(const std::string &interfaceCreateStatesArrayMethodString)
{
    mPimpl->mInterfaceCreateStatesArrayMethodString = interfaceCreateStatesArrayMethodString;
}

std::string GeneratorProfile::implementationCreateStatesArrayMethodString() const
{
    return mPimpl->mImplementationCreateStatesArrayMethodString;
}

void GeneratorProfile::setImplementationCreateStatesArrayMethodString(const std::string &implementationCreateStatesArrayMethodString)
{
    mPimpl->mImplementationCreateStatesArrayMethodString = implementationCreateStatesArrayMethodString;
}

std::string GeneratorProfile::interfaceCreateVariablesArrayMethodString() const
{
    return mPimpl->mInterfaceCreateVariablesArrayMethodString;
}

void GeneratorProfile::setInterfaceCreateVariablesArrayMethodString(const std::string &interfaceCreateVariablesArrayMethodString)
{
    mPimpl->mInterfaceCreateVariablesArrayMethodString = interfaceCreateVariablesArrayMethodString;
}

std::string GeneratorProfile::implementationCreateVariablesArrayMethodString() const
{
    return mPimpl->mImplementationCreateVariablesArrayMethodString;
}

void GeneratorProfile::setImplementationCreateVariablesArrayMethodString(const std::string &implementationCreateVariablesArrayMethodString)
{
    mPimpl->mImplementationCreateVariablesArrayMethodString = implementationCreateVariablesArrayMethodString;
}

std::string GeneratorProfile::interfaceDeleteArrayMethodString() const
{
    return mPimpl->mInterfaceDeleteArrayMethodString;
}

void GeneratorProfile::setInterfaceDeleteArrayMethodString(const std::string &interfaceDeleteArrayMethodString)
{
    mPimpl->mInterfaceDeleteArrayMethodString = interfaceDeleteArrayMethodString;
}

std::string GeneratorProfile::implementationDeleteArrayMethodString() const
{
    return mPimpl->mImplementationDeleteArrayMethodString;
}

void GeneratorProfile::setImplementationDeleteArrayMethodString(const std::string &implementationDeleteArrayMethodString)
{
    mPimpl->mImplementationDeleteArrayMethodString = implementationDeleteArrayMethodString;
}

std::string GeneratorProfile::interfaceInitialiseStatesAndConstantsMethodString() const
{
    return mPimpl->mInterfaceInitialiseStatesAndConstantsMethodString;
}

void GeneratorProfile::setInterfaceInitialiseStatesAndConstantsMethodString(const std::string &interfaceInitialiseStatesAndConstantsMethodString)
{
    mPimpl->mInterfaceInitialiseStatesAndConstantsMethodString = interfaceInitialiseStatesAndConstantsMethodString;
}

std::string GeneratorProfile::implementationInitialiseStatesAndConstantsMethodString() const
{
    return mPimpl->mImplementationInitialiseStatesAndConstantsMethodString;
}

void GeneratorProfile::setImplementationInitialiseStatesAndConstantsMethodString(const std::string &implementationInitialiseStatesAndConstantsMethodString)
{
    mPimpl->mImplementationInitialiseStatesAndConstantsMethodString = implementationInitialiseStatesAndConstantsMethodString;
}

std::string GeneratorProfile::interfaceComputeComputedConstantsMethodString() const
{
    return mPimpl->mInterfaceComputeComputedConstantsMethodString;
}

void GeneratorProfile::setInterfaceComputeComputedConstantsMethodString(const std::string &interfaceComputeComputedConstantsMethodString)
{
    mPimpl->mInterfaceComputeComputedConstantsMethodString = interfaceComputeComputedConstantsMethodString;
}

std::string GeneratorProfile::implementationComputeComputedConstantsMethodString() const
{
    return mPimpl->mImplementationComputeComputedConstantsMethodString;
}

void GeneratorProfile::setImplementationComputeComputedConstantsMethodString(const std::string &implementationComputeComputedConstantsMethodString)
{
    mPimpl->mImplementationComputeComputedConstantsMethodString = implementationComputeComputedConstantsMethodString;
}

std::string GeneratorProfile::interfaceComputeRatesMethodString() const
{
    return mPimpl->mInterfaceComputeRatesMethodString;
}

void GeneratorProfile::setInterfaceComputeRatesMethodString(const std::string &interfaceComputeRatesMethodString)
{
    mPimpl->mInterfaceComputeRatesMethodString = interfaceComputeRatesMethodString;
}

std::string GeneratorProfile::implementationComputeRatesMethodString() const
{
    return mPimpl->mImplementationComputeRatesMethodString;
}

void GeneratorProfile::setImplementationComputeRatesMethodString(const std::string &implementationComputeRatesMethodString)
{
    mPimpl->mImplementationComputeRatesMethodString = implementationComputeRatesMethodString;
}

std::string GeneratorProfile::interfaceComputeVariablesMethodString() const
{
    return mPimpl->mInterfaceComputeVariablesMethodString;
}

void GeneratorProfile::setInterfaceComputeVariablesMethodString(const std::string &interfaceComputeVariablesMethodString)
{
    mPimpl->mInterfaceComputeVariablesMethodString = interfaceComputeVariablesMethodString;
}

std::string GeneratorProfile::implementationComputeVariablesMethodString() const
{
    return mPimpl->mImplementationComputeVariablesMethodString;
}

void GeneratorProfile::setImplementationComputeVariablesMethodString(const std::string &implementationComputeVariablesMethodString)
{
    mPimpl->mImplementationComputeVariablesMethodString = implementationComputeVariablesMethodString;
}

std::string GeneratorProfile::emptyMethodString() const
{
    return mPimpl->mEmptyMethodString;
}

void GeneratorProfile::setEmptyMethodString(const std::string &emptyMethodString)
{
    mPimpl->mEmptyMethodString = emptyMethodString;
}

std::string GeneratorProfile::indentString() const
{
    return mPimpl->mIndentString;
}

void GeneratorProfile::setIndentString(const std::string &indentString)
{
    mPimpl->mIndentString = indentString;
}

std::string GeneratorProfile::openArrayInitialiserString() const
{
    return mPimpl->mOpenArrayInitialiserString;
}

void GeneratorProfile::setOpenArrayInitialiserString(const std::string &openArrayInitialiserString)
{
    mPimpl->mOpenArrayInitialiserString = openArrayInitialiserString;
}

std::string GeneratorProfile::closeArrayInitialiserString() const
{
    return mPimpl->mCloseArrayInitialiserString;
}

void GeneratorProfile::setCloseArrayInitialiserString(const std::string &closeArrayInitialiserString)
{
    mPimpl->mCloseArrayInitialiserString = closeArrayInitialiserString;
}

std::string GeneratorProfile::openArrayString() const
{
    return mPimpl->mOpenArrayString;
}

void GeneratorProfile::setOpenArrayString(const std::string &openArrayString)
{
    mPimpl->mOpenArrayString = openArrayString;
}

std::string GeneratorProfile::closeArrayString() const
{
    return mPimpl->mCloseArrayString;
}

void GeneratorProfile::setCloseArrayString(const std::string &closeArrayString)
{
    mPimpl->mCloseArrayString = closeArrayString;
}

std::string GeneratorProfile::arrayElementSeparatorString() const
{
    return mPimpl->mArrayElementSeparatorString;
}

void GeneratorProfile::setArrayElementSeparatorString(const std::string &arrayElementSeparatorString)
{
    mPimpl->mArrayElementSeparatorString = arrayElementSeparatorString;
}

std::string GeneratorProfile::stringDelimiterString() const
{
    return mPimpl->mStringDelimiterString;
}

void GeneratorProfile::setStringDelimiterString(const std::string &stringDelimiterString)
{
    mPimpl->mStringDelimiterString = stringDelimiterString;
}

std::string GeneratorProfile::commandSeparatorString() const
{
    return mPimpl->mCommandSeparatorString;
}

void GeneratorProfile::setCommandSeparatorString(const std::string &commandSeparatorString)
{
    mPimpl->mCommandSeparatorString = commandSeparatorString;
}

} // namespace libcellml
