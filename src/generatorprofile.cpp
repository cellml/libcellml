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

#include "utilities.h"

#include "libcellml/generatorprofile.h"

#include <cmath>
#include <string>

namespace libcellml {

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
    std::string mNapierianLogarithmString;
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

    // Mathematical functions.

    std::string mInterfaceEqFunctionString;
    std::string mImplementationEqFunctionString;

    std::string mInterfaceNeqFunctionString;
    std::string mImplementationNeqFunctionString;

    std::string mInterfaceLtFunctionString;
    std::string mImplementationLtFunctionString;

    std::string mInterfaceLeqFunctionString;
    std::string mImplementationLeqFunctionString;

    std::string mInterfaceGtFunctionString;
    std::string mImplementationGtFunctionString;

    std::string mInterfaceGeqFunctionString;
    std::string mImplementationGeqFunctionString;

    std::string mInterfaceAndFunctionString;
    std::string mImplementationAndFunctionString;

    std::string mInterfaceOrFunctionString;
    std::string mImplementationOrFunctionString;

    std::string mInterfaceXorFunctionString;
    std::string mImplementationXorFunctionString;

    std::string mInterfaceNotFunctionString;
    std::string mImplementationNotFunctionString;

    std::string mInterfaceMinFunctionString;
    std::string mImplementationMinFunctionString;

    std::string mInterfaceMaxFunctionString;
    std::string mImplementationMaxFunctionString;

    std::string mInterfaceSecFunctionString;
    std::string mImplementationSecFunctionString;

    std::string mInterfaceCscFunctionString;
    std::string mImplementationCscFunctionString;

    std::string mInterfaceCotFunctionString;
    std::string mImplementationCotFunctionString;

    std::string mInterfaceSechFunctionString;
    std::string mImplementationSechFunctionString;

    std::string mInterfaceCschFunctionString;
    std::string mImplementationCschFunctionString;

    std::string mInterfaceCothFunctionString;
    std::string mImplementationCothFunctionString;

    std::string mInterfaceAsecFunctionString;
    std::string mImplementationAsecFunctionString;

    std::string mInterfaceAcscFunctionString;
    std::string mImplementationAcscFunctionString;

    std::string mInterfaceAcotFunctionString;
    std::string mImplementationAcotFunctionString;

    std::string mInterfaceAsechFunctionString;
    std::string mImplementationAsechFunctionString;

    std::string mInterfaceAcschFunctionString;
    std::string mImplementationAcschFunctionString;

    std::string mInterfaceAcothFunctionString;
    std::string mImplementationAcothFunctionString;

    // Miscellaneous.

    std::string mCommentString;
    std::string mOriginCommentString;

    std::string mInterfaceHeaderString;
    std::string mImplementationHeaderString;

    std::string mInterfaceLibcellmlVersionString;
    std::string mImplementationLibcellmlVersionString;

    std::string mInterfaceStateCountString;
    std::string mImplementationStateCountString;

    std::string mInterfaceVariableCountString;
    std::string mImplementationVariableCountString;

    std::string mVariableTypeObjectString;

    std::string mConstantVariableType;
    std::string mComputedConstantVariableType;
    std::string mAlgebraicVariableType;

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

    std::string mReturnCreatedArrayString;

    std::string mInterfaceCreateStatesArrayMethodString;
    std::string mImplementationCreateStatesArrayMethodString;

    std::string mInterfaceCreateVariablesArrayMethodString;
    std::string mImplementationCreateVariablesArrayMethodString;

    std::string mInterfaceDeleteArrayMethodString;
    std::string mImplementationDeleteArrayMethodString;

    std::string mInterfaceInitializeStatesAndConstantsMethodString;
    std::string mImplementationInitializeStatesAndConstantsMethodString;

    std::string mInterfaceComputeComputedConstantsMethodString;
    std::string mImplementationComputeComputedConstantsMethodString;

    std::string mInterfaceComputeRatesMethodString;
    std::string mImplementationComputeRatesMethodString;

    std::string mInterfaceComputeVariablesMethodString;
    std::string mImplementationComputeVariablesMethodString;

    std::string mEmptyMethodString;

    std::string mIndentString;

    std::string mOpenArrayInitializerString;
    std::string mCloseArrayInitializerString;

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
        mNapierianLogarithmString = "log";
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
        mEString = convertDoubleToString(exp(1.0));
        mPiString = convertDoubleToString(M_PI);
        mInfString = "1.0/0.0";
        mNanString = "sqrt(-1.0)";

        // Mathematical functions.

        mInterfaceEqFunctionString = "";
        mImplementationEqFunctionString = "";

        mInterfaceNeqFunctionString = "";
        mImplementationNeqFunctionString = "";

        mInterfaceLtFunctionString = "";
        mImplementationLtFunctionString = "";

        mInterfaceLeqFunctionString = "";
        mImplementationLeqFunctionString = "";

        mInterfaceGtFunctionString = "";
        mImplementationGtFunctionString = "";

        mInterfaceGeqFunctionString = "";
        mImplementationGeqFunctionString = "";

        mInterfaceAndFunctionString = "";
        mImplementationAndFunctionString = "";

        mInterfaceOrFunctionString = "";
        mImplementationOrFunctionString = "";

        mInterfaceXorFunctionString = "extern double xor(double x, double y);\n";
        mImplementationXorFunctionString = "double xor(double x, double y)\n"
                                           "{\n"
                                           "    return (x != 0.0) ^ (y != 0.0);\n"
                                           "}\n";

        mInterfaceNotFunctionString = "";
        mImplementationNotFunctionString = "";

        mInterfaceMinFunctionString = "extern double min(double x, double y);\n";
        mImplementationMinFunctionString = "double min(double x, double y)\n"
                                           "{\n"
                                           "    return (x < y)?x:y;\n"
                                           "}\n";

        mInterfaceMaxFunctionString = "extern double max(double x, double y);\n";
        mImplementationMaxFunctionString = "double max(double x, double y)\n"
                                           "{\n"
                                           "    return (x > y)?x:y;\n"
                                           "}\n";

        mInterfaceSecFunctionString = "extern double sec(double x);\n";
        mImplementationSecFunctionString = "double sec(double x)\n"
                                           "{\n"
                                           "    return 1.0/cos(x);\n"
                                           "}\n";

        mInterfaceCscFunctionString = "extern double csc(double x);\n";
        mImplementationCscFunctionString = "double csc(double x)\n"
                                           "{\n"
                                           "    return 1.0/sin(x);\n"
                                           "}\n";

        mInterfaceCotFunctionString = "extern double cot(double x);\n";
        mImplementationCotFunctionString = "double cot(double x)\n"
                                           "{\n"
                                           "    return 1.0/tan(x);\n"
                                           "}\n";

        mInterfaceSechFunctionString = "extern double sech(double x);\n";
        mImplementationSechFunctionString = "double sech(double x)\n"
                                            "{\n"
                                            "    return 1.0/cosh(x);\n"
                                            "}\n";

        mInterfaceCschFunctionString = "extern double csch(double x);\n";
        mImplementationCschFunctionString = "double csch(double x)\n"
                                            "{\n"
                                            "    return 1.0/sinh(x);\n"
                                            "}\n";

        mInterfaceCothFunctionString = "extern double coth(double x);\n";
        mImplementationCothFunctionString = "double coth(double x)\n"
                                            "{\n"
                                            "    return 1.0/tanh(x);\n"
                                            "}\n";

        mInterfaceAsecFunctionString = "extern double asec(double x);\n";
        mImplementationAsecFunctionString = "double asec(double x)\n"
                                            "{\n"
                                            "    return acos(1.0/x);\n"
                                            "}\n";

        mInterfaceAcscFunctionString = "extern double acsc(double x);\n";
        mImplementationAcscFunctionString = "double acsc(double x)\n"
                                            "{\n"
                                            "    return asin(1.0/x);\n"
                                            "}\n";

        mInterfaceAcotFunctionString = "extern double acot(double x);\n";
        mImplementationAcotFunctionString = "double acot(double x)\n"
                                            "{\n"
                                            "    return atan(1.0/x);\n"
                                            "}\n";

        mInterfaceAsechFunctionString = "extern double asech(double x);\n";
        mImplementationAsechFunctionString = "double asech(double x)\n"
                                             "{\n"
                                             "    double oneOverX = 1.0/x;\n"
                                             "\n"
                                             "    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));\n"
                                             "}\n";

        mInterfaceAcschFunctionString = "extern double acsch(double x);\n";
        mImplementationAcschFunctionString = "double acsch(double x)\n"
                                             "{\n"
                                             "    double oneOverX = 1.0/x;\n"
                                             "\n"
                                             "    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));\n"
                                             "}\n";

        mInterfaceAcothFunctionString = "extern double acoth(double x);\n";
        mImplementationAcothFunctionString = "double acoth(double x)\n"
                                             "{\n"
                                             "    double oneOverX = 1.0/x;\n"
                                             "\n"
                                             "    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));\n"
                                             "}\n";

        // Miscellaneous.

        mCommentString = "/* <CODE> */\n";
        mOriginCommentString = "The content of this file was generated using <PROFILE_INFORMATION> libCellML <LIBCELLML_VERSION>.";

        mInterfaceHeaderString = "#pragma once\n"
                                 "\n"
                                 "#include <stddef.h>\n";
        mImplementationHeaderString = "#include \"model.h\"\n"
                                      "\n"
                                      "#include <math.h>\n"
                                      "#include <stdlib.h>\n";

        mInterfaceLibcellmlVersionString = "extern const char LIBCELLML_VERSION[];\n";
        mImplementationLibcellmlVersionString = "const char LIBCELLML_VERSION[] = \"<LIBCELLML_VERSION>\";\n";

        mInterfaceStateCountString = "extern const size_t STATE_COUNT;\n";
        mImplementationStateCountString = "const size_t STATE_COUNT = <STATE_COUNT>;\n";

        mInterfaceVariableCountString = "extern const size_t VARIABLE_COUNT;\n";
        mImplementationVariableCountString = "const size_t VARIABLE_COUNT = <VARIABLE_COUNT>;\n";

        mVariableTypeObjectString = "typedef enum {\n"
                                    "    CONSTANT,\n"
                                    "    COMPUTED_CONSTANT,\n"
                                    "    ALGEBRAIC\n"
                                    "} VariableType;\n";

        mConstantVariableType = "CONSTANT";
        mComputedConstantVariableType = "COMPUTED_CONSTANT";
        mAlgebraicVariableType = "ALGEBRAIC";

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

        mReturnCreatedArrayString = "return (double *) malloc(<ARRAY_SIZE>*sizeof(double));\n";

        mInterfaceCreateStatesArrayMethodString = "double * createStatesArray();\n";
        mImplementationCreateStatesArrayMethodString = "double * createStatesArray()\n"
                                                       "{\n"
                                                       "<CODE>"
                                                       "}\n";

        mInterfaceCreateVariablesArrayMethodString = "double * createVariablesArray();\n";
        mImplementationCreateVariablesArrayMethodString = "double * createVariablesArray()\n"
                                                          "{\n"
                                                          "<CODE>"
                                                          "}\n";

        mInterfaceDeleteArrayMethodString = "void deleteArray(double *array);\n";
        mImplementationDeleteArrayMethodString = "void deleteArray(double *array)\n"
                                                 "{\n"
                                                 "    free(array);\n"
                                                 "}\n";

        mInterfaceInitializeStatesAndConstantsMethodString = "void initializeStatesAndConstants(double *states, double *variables);\n";
        mImplementationInitializeStatesAndConstantsMethodString = "void initializeStatesAndConstants(double *states, double *variables)\n"
                                                                  "{\n"
                                                                  "<CODE>"
                                                                  "}\n";

        mInterfaceComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables);\n";
        mImplementationComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables)\n"
                                                              "{\n"
                                                              "<CODE>"
                                                              "}\n";

        mInterfaceComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables);\n";
        mImplementationComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables)\n{\n"
                                                  "<CODE>"
                                                  "}\n";

        mInterfaceComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables);\n";
        mImplementationComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables)\n"
                                                      "{\n"
                                                      "<CODE>"
                                                      "}\n";

        mEmptyMethodString = "";

        mIndentString = "    ";

        mOpenArrayInitializerString = "{";
        mCloseArrayInitializerString = "}";

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
        mNapierianLogarithmString = "log";
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
        mEString = convertDoubleToString(exp(1.0));
        mPiString = convertDoubleToString(M_PI);
        mInfString = "inf";
        mNanString = "nan";

        // Mathematical functions.

        mInterfaceEqFunctionString = "";
        mImplementationEqFunctionString = "\n"
                                          "def eq_func(x, y):\n"
                                          "    return 1.0 if x == y else 0.0\n";

        mInterfaceNeqFunctionString = "";
        mImplementationNeqFunctionString = "\n"
                                           "def neq_func(x, y):\n"
                                           "    return 1.0 if x != y else 0.0\n";

        mInterfaceLtFunctionString = "";
        mImplementationLtFunctionString = "\n"
                                          "def lt_func(x, y):\n"
                                          "    return 1.0 if x < y else 0.0\n";

        mInterfaceLeqFunctionString = "";
        mImplementationLeqFunctionString = "\n"
                                           "def leq_func(x, y):\n"
                                           "    return 1.0 if x <= y else 0.0\n";

        mInterfaceGtFunctionString = "";
        mImplementationGtFunctionString = "\n"
                                          "def gt_func(x, y):\n"
                                          "    return 1.0 if x > y else 0.0\n";

        mInterfaceGeqFunctionString = "";
        mImplementationGeqFunctionString = "\n"
                                           "def geq_func(x, y):\n"
                                           "    return 1.0 if x >= y else 0.0\n";

        mInterfaceAndFunctionString = "";
        mImplementationAndFunctionString = "\n"
                                           "def and_func(x, y):\n"
                                           "    return 1.0 if bool(x) & bool(y) else 0.0\n";

        mInterfaceOrFunctionString = "";
        mImplementationOrFunctionString = "\n"
                                          "def or_func(x, y):\n"
                                          "    return 1.0 if bool(x) | bool(y) else 0.0\n";

        mInterfaceXorFunctionString = "";
        mImplementationXorFunctionString = "\n"
                                           "def xor_func(x, y):\n"
                                           "    return 1.0 if bool(x) ^ bool(y) else 0.0\n";

        mInterfaceNotFunctionString = "";
        mImplementationNotFunctionString = "\n"
                                           "def not_func(x):\n"
                                           "    return 1.0 if not bool(x) else 0.0\n";

        mInterfaceMinFunctionString = "";
        mImplementationMinFunctionString = "\n"
                                           "def min(x, y):\n"
                                           "    return x if x < y else y\n";

        mInterfaceMaxFunctionString = "";
        mImplementationMaxFunctionString = "\n"
                                           "def max(x, y):\n"
                                           "    return x if x > y else y\n";

        mInterfaceSecFunctionString = "";
        mImplementationSecFunctionString = "\n"
                                           "def sec(x):\n"
                                           "    return 1.0/cos(x)\n";

        mInterfaceCscFunctionString = "";
        mImplementationCscFunctionString = "\n"
                                           "def csc(x):\n"
                                           "    return 1.0/sin(x)\n";

        mInterfaceCotFunctionString = "";
        mImplementationCotFunctionString = "\n"
                                           "def cot(x):\n"
                                           "    return 1.0/tan(x)\n";

        mInterfaceSechFunctionString = "";
        mImplementationSechFunctionString = "\n"
                                            "def sech(x):\n"
                                            "    return 1.0/cosh(x)\n";

        mInterfaceCschFunctionString = "";
        mImplementationCschFunctionString = "\n"
                                            "def csch(x):\n"
                                            "    return 1.0/sinh(x)\n";

        mInterfaceCothFunctionString = "";
        mImplementationCothFunctionString = "\n"
                                            "def coth(x):\n"
                                            "    return 1.0/tanh(x)\n";

        mInterfaceAsecFunctionString = "";
        mImplementationAsecFunctionString = "\n"
                                            "def asec(x):\n"
                                            "    return acos(1.0/x)\n";

        mInterfaceAcscFunctionString = "";
        mImplementationAcscFunctionString = "\n"
                                            "def acsc(x):\n"
                                            "    return asin(1.0/x)\n";

        mInterfaceAcotFunctionString = "";
        mImplementationAcotFunctionString = "\n"
                                            "def acot(x):\n"
                                            "    return atan(1.0/x)\n";

        mInterfaceAsechFunctionString = "";
        mImplementationAsechFunctionString = "\n"
                                             "def asech(x):\n"
                                             "    one_over_x = 1.0/x\n"
                                             "\n"
                                             "    return log(one_over_x+sqrt(one_over_x*one_over_x-1.0))\n";

        mInterfaceAcschFunctionString = "";
        mImplementationAcschFunctionString = "\n"
                                             "def acsch(x):\n"
                                             "    one_over_x = 1.0/x\n"
                                             "\n"
                                             "    return log(one_over_x+sqrt(one_over_x*one_over_x+1.0))\n";

        mInterfaceAcothFunctionString = "";
        mImplementationAcothFunctionString = "\n"
                                             "def acoth(x):\n"
                                             "    one_over_x = 1.0/x\n"
                                             "\n"
                                             "    return 0.5*log((1.0+one_over_x)/(1.0-one_over_x))\n";

        // Miscellaneous.

        mCommentString = "# <CODE>\n";
        mOriginCommentString = "The content of this file was generated using <PROFILE_INFORMATION> libCellML <LIBCELLML_VERSION>.";

        mInterfaceHeaderString = "";
        mImplementationHeaderString = "from enum import Enum\n"
                                      "from math import *\n"
                                      "\n";

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
                                    "    ALGEBRAIC = 3\n"
                                    "\n";

        mConstantVariableType = "VariableType.CONSTANT";
        mComputedConstantVariableType = "VariableType.COMPUTED_CONSTANT";
        mAlgebraicVariableType = "VariableType.ALGEBRAIC";

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

        mReturnCreatedArrayString = "return [nan]*<ARRAY_SIZE>\n";

        mInterfaceCreateStatesArrayMethodString = "";
        mImplementationCreateStatesArrayMethodString = "\n"
                                                       "def create_states_array():\n"
                                                       "<CODE>";

        mInterfaceCreateVariablesArrayMethodString = "";
        mImplementationCreateVariablesArrayMethodString = "\n"
                                                          "def create_variables_array():\n"
                                                          "<CODE>";

        mInterfaceDeleteArrayMethodString = "";
        mImplementationDeleteArrayMethodString = "";

        mInterfaceInitializeStatesAndConstantsMethodString = "";
        mImplementationInitializeStatesAndConstantsMethodString = "\n"
                                                                  "def initialize_states_and_constants(states, variables):\n"
                                                                  "<CODE>";

        mInterfaceComputeComputedConstantsMethodString = "";
        mImplementationComputeComputedConstantsMethodString = "\n"
                                                              "def compute_computed_constants(variables):\n"
                                                              "<CODE>";

        mInterfaceComputeRatesMethodString = "";
        mImplementationComputeRatesMethodString = "\n"
                                                  "def compute_rates(voi, states, rates, variables):\n"
                                                  "<CODE>";

        mInterfaceComputeVariablesMethodString = "";
        mImplementationComputeVariablesMethodString = "\n"
                                                      "def compute_variables(voi, states, rates, variables):\n"
                                                      "<CODE>";

        mEmptyMethodString = "pass\n";

        mIndentString = "    ";

        mOpenArrayInitializerString = "[";
        mCloseArrayInitializerString = "]";

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

GeneratorProfile::GeneratorProfile(const GeneratorProfile &rhs)
    : mPimpl(new GeneratorProfileImpl())
{
    // Whether the profile is official.

    mPimpl->mProfile = rhs.mPimpl->mProfile;

    // Whether the profile requires an interface to be generated.

    mPimpl->mHasInterface = rhs.mPimpl->mHasInterface;

    // Assignment.

    mPimpl->mAssignmentString = rhs.mPimpl->mAssignmentString;

    // Relational and logical operators.

    mPimpl->mEqString = rhs.mPimpl->mEqString;
    mPimpl->mNeqString = rhs.mPimpl->mNeqString;
    mPimpl->mLtString = rhs.mPimpl->mLtString;
    mPimpl->mLeqString = rhs.mPimpl->mLeqString;
    mPimpl->mGtString = rhs.mPimpl->mGtString;
    mPimpl->mGeqString = rhs.mPimpl->mGeqString;
    mPimpl->mAndString = rhs.mPimpl->mAndString;
    mPimpl->mOrString = rhs.mPimpl->mOrString;
    mPimpl->mXorString = rhs.mPimpl->mXorString;
    mPimpl->mNotString = rhs.mPimpl->mNotString;

    mPimpl->mHasEqOperator = rhs.mPimpl->mHasEqOperator;
    mPimpl->mHasNeqOperator = rhs.mPimpl->mHasNeqOperator;
    mPimpl->mHasLtOperator = rhs.mPimpl->mHasLtOperator;
    mPimpl->mHasLeqOperator = rhs.mPimpl->mHasLeqOperator;
    mPimpl->mHasGtOperator = rhs.mPimpl->mHasGtOperator;
    mPimpl->mHasGeqOperator = rhs.mPimpl->mHasGeqOperator;
    mPimpl->mHasAndOperator = rhs.mPimpl->mHasAndOperator;
    mPimpl->mHasOrOperator = rhs.mPimpl->mHasOrOperator;
    mPimpl->mHasXorOperator = rhs.mPimpl->mHasXorOperator;
    mPimpl->mHasNotOperator = rhs.mPimpl->mHasNotOperator;

    // Arithmetic operators.

    mPimpl->mPlusString = rhs.mPimpl->mPlusString;
    mPimpl->mMinusString = rhs.mPimpl->mMinusString;
    mPimpl->mTimesString = rhs.mPimpl->mTimesString;
    mPimpl->mDivideString = rhs.mPimpl->mDivideString;
    mPimpl->mPowerString = rhs.mPimpl->mPowerString;
    mPimpl->mSquareRootString = rhs.mPimpl->mSquareRootString;
    mPimpl->mSquareString = rhs.mPimpl->mSquareString;
    mPimpl->mAbsoluteValueString = rhs.mPimpl->mAbsoluteValueString;
    mPimpl->mExponentialString = rhs.mPimpl->mExponentialString;
    mPimpl->mNapierianLogarithmString = rhs.mPimpl->mNapierianLogarithmString;
    mPimpl->mCommonLogarithmString = rhs.mPimpl->mCommonLogarithmString;
    mPimpl->mCeilingString = rhs.mPimpl->mCeilingString;
    mPimpl->mFloorString = rhs.mPimpl->mFloorString;
    mPimpl->mMinString = rhs.mPimpl->mMinString;
    mPimpl->mMaxString = rhs.mPimpl->mMaxString;
    mPimpl->mRemString = rhs.mPimpl->mRemString;

    mPimpl->mHasPowerOperator = rhs.mPimpl->mHasPowerOperator;

    // Trigonometric operators.

    mPimpl->mSinString = rhs.mPimpl->mSinString;
    mPimpl->mCosString = rhs.mPimpl->mCosString;
    mPimpl->mTanString = rhs.mPimpl->mTanString;
    mPimpl->mSecString = rhs.mPimpl->mSecString;
    mPimpl->mCscString = rhs.mPimpl->mCscString;
    mPimpl->mCotString = rhs.mPimpl->mCotString;
    mPimpl->mSinhString = rhs.mPimpl->mSinhString;
    mPimpl->mCoshString = rhs.mPimpl->mCoshString;
    mPimpl->mTanhString = rhs.mPimpl->mTanhString;
    mPimpl->mSechString = rhs.mPimpl->mSechString;
    mPimpl->mCschString = rhs.mPimpl->mCschString;
    mPimpl->mCothString = rhs.mPimpl->mCothString;
    mPimpl->mAsinString = rhs.mPimpl->mAsinString;
    mPimpl->mAcosString = rhs.mPimpl->mAcosString;
    mPimpl->mAtanString = rhs.mPimpl->mAtanString;
    mPimpl->mAsecString = rhs.mPimpl->mAsecString;
    mPimpl->mAcscString = rhs.mPimpl->mAcscString;
    mPimpl->mAcotString = rhs.mPimpl->mAcotString;
    mPimpl->mAsinhString = rhs.mPimpl->mAsinhString;
    mPimpl->mAcoshString = rhs.mPimpl->mAcoshString;
    mPimpl->mAtanhString = rhs.mPimpl->mAtanhString;
    mPimpl->mAsechString = rhs.mPimpl->mAsechString;
    mPimpl->mAcschString = rhs.mPimpl->mAcschString;
    mPimpl->mAcothString = rhs.mPimpl->mAcothString;

    // Piecewise statement.

    mPimpl->mConditionalOperatorIfString = rhs.mPimpl->mConditionalOperatorIfString;
    mPimpl->mConditionalOperatorElseString = rhs.mPimpl->mConditionalOperatorElseString;
    mPimpl->mPiecewiseIfString = rhs.mPimpl->mPiecewiseIfString;
    mPimpl->mPiecewiseElseString = rhs.mPimpl->mPiecewiseElseString;

    mPimpl->mHasConditionalOperator = rhs.mPimpl->mHasConditionalOperator;

    // Constants.

    mPimpl->mTrueString = rhs.mPimpl->mTrueString;
    mPimpl->mFalseString = rhs.mPimpl->mFalseString;
    mPimpl->mEString = rhs.mPimpl->mEString;
    mPimpl->mPiString = rhs.mPimpl->mPiString;
    mPimpl->mInfString = rhs.mPimpl->mInfString;
    mPimpl->mNanString = rhs.mPimpl->mNanString;

    // Mathematical functions.

    mPimpl->mInterfaceEqFunctionString = rhs.mPimpl->mInterfaceEqFunctionString;
    mPimpl->mImplementationEqFunctionString = rhs.mPimpl->mImplementationEqFunctionString;

    mPimpl->mInterfaceNeqFunctionString = rhs.mPimpl->mInterfaceNeqFunctionString;
    mPimpl->mImplementationNeqFunctionString = rhs.mPimpl->mImplementationNeqFunctionString;

    mPimpl->mInterfaceLtFunctionString = rhs.mPimpl->mInterfaceLtFunctionString;
    mPimpl->mImplementationLtFunctionString = rhs.mPimpl->mImplementationLtFunctionString;

    mPimpl->mInterfaceLeqFunctionString = rhs.mPimpl->mInterfaceLeqFunctionString;
    mPimpl->mImplementationLeqFunctionString = rhs.mPimpl->mImplementationLeqFunctionString;

    mPimpl->mInterfaceGtFunctionString = rhs.mPimpl->mInterfaceGtFunctionString;
    mPimpl->mImplementationGtFunctionString = rhs.mPimpl->mImplementationGtFunctionString;

    mPimpl->mInterfaceGeqFunctionString = rhs.mPimpl->mInterfaceGeqFunctionString;
    mPimpl->mImplementationGeqFunctionString = rhs.mPimpl->mImplementationGeqFunctionString;

    mPimpl->mInterfaceAndFunctionString = rhs.mPimpl->mInterfaceAndFunctionString;
    mPimpl->mImplementationAndFunctionString = rhs.mPimpl->mImplementationAndFunctionString;

    mPimpl->mInterfaceOrFunctionString = rhs.mPimpl->mInterfaceOrFunctionString;
    mPimpl->mImplementationOrFunctionString = rhs.mPimpl->mImplementationOrFunctionString;

    mPimpl->mInterfaceXorFunctionString = rhs.mPimpl->mInterfaceXorFunctionString;
    mPimpl->mImplementationXorFunctionString = rhs.mPimpl->mImplementationXorFunctionString;

    mPimpl->mInterfaceNotFunctionString = rhs.mPimpl->mInterfaceNotFunctionString;
    mPimpl->mImplementationNotFunctionString = rhs.mPimpl->mImplementationNotFunctionString;

    mPimpl->mInterfaceMinFunctionString = rhs.mPimpl->mInterfaceMinFunctionString;
    mPimpl->mImplementationMinFunctionString = rhs.mPimpl->mImplementationMinFunctionString;

    mPimpl->mInterfaceMaxFunctionString = rhs.mPimpl->mInterfaceMaxFunctionString;
    mPimpl->mImplementationMaxFunctionString = rhs.mPimpl->mImplementationMaxFunctionString;

    mPimpl->mInterfaceSecFunctionString = rhs.mPimpl->mInterfaceSecFunctionString;
    mPimpl->mImplementationSecFunctionString = rhs.mPimpl->mImplementationSecFunctionString;

    mPimpl->mInterfaceCscFunctionString = rhs.mPimpl->mInterfaceCscFunctionString;
    mPimpl->mImplementationCscFunctionString = rhs.mPimpl->mImplementationCscFunctionString;

    mPimpl->mInterfaceCotFunctionString = rhs.mPimpl->mInterfaceCotFunctionString;
    mPimpl->mImplementationCotFunctionString = rhs.mPimpl->mImplementationCotFunctionString;

    mPimpl->mInterfaceSechFunctionString = rhs.mPimpl->mInterfaceSechFunctionString;
    mPimpl->mImplementationSechFunctionString = rhs.mPimpl->mImplementationSechFunctionString;

    mPimpl->mInterfaceCschFunctionString = rhs.mPimpl->mInterfaceCschFunctionString;
    mPimpl->mImplementationCschFunctionString = rhs.mPimpl->mImplementationCschFunctionString;

    mPimpl->mInterfaceCothFunctionString = rhs.mPimpl->mInterfaceCothFunctionString;
    mPimpl->mImplementationCothFunctionString = rhs.mPimpl->mImplementationCothFunctionString;

    mPimpl->mInterfaceAsecFunctionString = rhs.mPimpl->mInterfaceAsecFunctionString;
    mPimpl->mImplementationAsecFunctionString = rhs.mPimpl->mImplementationAsecFunctionString;

    mPimpl->mInterfaceAcscFunctionString = rhs.mPimpl->mInterfaceAcscFunctionString;
    mPimpl->mImplementationAcscFunctionString = rhs.mPimpl->mImplementationAcscFunctionString;

    mPimpl->mInterfaceAcotFunctionString = rhs.mPimpl->mInterfaceAcotFunctionString;
    mPimpl->mImplementationAcotFunctionString = rhs.mPimpl->mImplementationAcotFunctionString;

    mPimpl->mInterfaceAsechFunctionString = rhs.mPimpl->mInterfaceAsechFunctionString;
    mPimpl->mImplementationAsechFunctionString = rhs.mPimpl->mImplementationAsechFunctionString;

    mPimpl->mInterfaceAcschFunctionString = rhs.mPimpl->mInterfaceAcschFunctionString;
    mPimpl->mImplementationAcschFunctionString = rhs.mPimpl->mImplementationAcschFunctionString;

    mPimpl->mInterfaceAcothFunctionString = rhs.mPimpl->mInterfaceAcothFunctionString;
    mPimpl->mImplementationAcothFunctionString = rhs.mPimpl->mImplementationAcothFunctionString;

    // Miscellaneous.

    mPimpl->mCommentString = rhs.mPimpl->mCommentString;
    mPimpl->mOriginCommentString = rhs.mPimpl->mOriginCommentString;

    mPimpl->mInterfaceHeaderString = rhs.mPimpl->mInterfaceHeaderString;
    mPimpl->mImplementationHeaderString = rhs.mPimpl->mImplementationHeaderString;

    mPimpl->mInterfaceLibcellmlVersionString = rhs.mPimpl->mInterfaceLibcellmlVersionString;
    mPimpl->mImplementationLibcellmlVersionString = rhs.mPimpl->mImplementationLibcellmlVersionString;

    mPimpl->mInterfaceStateCountString = rhs.mPimpl->mInterfaceStateCountString;
    mPimpl->mImplementationStateCountString = rhs.mPimpl->mImplementationStateCountString;

    mPimpl->mInterfaceVariableCountString = rhs.mPimpl->mInterfaceVariableCountString;
    mPimpl->mImplementationVariableCountString = rhs.mPimpl->mImplementationVariableCountString;

    mPimpl->mVariableTypeObjectString = rhs.mPimpl->mVariableTypeObjectString;

    mPimpl->mConstantVariableType = rhs.mPimpl->mConstantVariableType;
    mPimpl->mComputedConstantVariableType = rhs.mPimpl->mComputedConstantVariableType;
    mPimpl->mAlgebraicVariableType = rhs.mPimpl->mAlgebraicVariableType;

    mPimpl->mVariableInfoObjectString = rhs.mPimpl->mVariableInfoObjectString;
    mPimpl->mVariableInfoWithTypeObjectString = rhs.mPimpl->mVariableInfoWithTypeObjectString;

    mPimpl->mInterfaceVoiInfoString = rhs.mPimpl->mInterfaceVoiInfoString;
    mPimpl->mImplementationVoiInfoString = rhs.mPimpl->mImplementationVoiInfoString;

    mPimpl->mInterfaceStateInfoString = rhs.mPimpl->mInterfaceStateInfoString;
    mPimpl->mImplementationStateInfoString = rhs.mPimpl->mImplementationStateInfoString;

    mPimpl->mInterfaceVariableInfoString = rhs.mPimpl->mInterfaceVariableInfoString;
    mPimpl->mImplementationVariableInfoString = rhs.mPimpl->mImplementationVariableInfoString;

    mPimpl->mVariableInfoEntryString = rhs.mPimpl->mVariableInfoEntryString;
    mPimpl->mVariableInfoWithTypeEntryString = rhs.mPimpl->mVariableInfoWithTypeEntryString;

    mPimpl->mVoiString = rhs.mPimpl->mVoiString;

    mPimpl->mStatesArrayString = rhs.mPimpl->mStatesArrayString;
    mPimpl->mRatesArrayString = rhs.mPimpl->mRatesArrayString;
    mPimpl->mVariablesArrayString = rhs.mPimpl->mVariablesArrayString;

    mPimpl->mReturnCreatedArrayString = rhs.mPimpl->mReturnCreatedArrayString;

    mPimpl->mInterfaceCreateStatesArrayMethodString = rhs.mPimpl->mInterfaceCreateStatesArrayMethodString;
    mPimpl->mImplementationCreateStatesArrayMethodString = rhs.mPimpl->mImplementationCreateStatesArrayMethodString;

    mPimpl->mInterfaceCreateVariablesArrayMethodString = rhs.mPimpl->mInterfaceCreateVariablesArrayMethodString;
    mPimpl->mImplementationCreateVariablesArrayMethodString = rhs.mPimpl->mImplementationCreateVariablesArrayMethodString;

    mPimpl->mInterfaceDeleteArrayMethodString = rhs.mPimpl->mInterfaceDeleteArrayMethodString;
    mPimpl->mImplementationDeleteArrayMethodString = rhs.mPimpl->mImplementationDeleteArrayMethodString;

    mPimpl->mInterfaceInitializeStatesAndConstantsMethodString = rhs.mPimpl->mInterfaceInitializeStatesAndConstantsMethodString;
    mPimpl->mImplementationInitializeStatesAndConstantsMethodString = rhs.mPimpl->mImplementationInitializeStatesAndConstantsMethodString;

    mPimpl->mInterfaceComputeComputedConstantsMethodString = rhs.mPimpl->mInterfaceComputeComputedConstantsMethodString;
    mPimpl->mImplementationComputeComputedConstantsMethodString = rhs.mPimpl->mImplementationComputeComputedConstantsMethodString;

    mPimpl->mInterfaceComputeRatesMethodString = rhs.mPimpl->mInterfaceComputeRatesMethodString;
    mPimpl->mImplementationComputeRatesMethodString = rhs.mPimpl->mImplementationComputeRatesMethodString;

    mPimpl->mInterfaceComputeVariablesMethodString = rhs.mPimpl->mInterfaceComputeVariablesMethodString;
    mPimpl->mImplementationComputeVariablesMethodString = rhs.mPimpl->mImplementationComputeVariablesMethodString;

    mPimpl->mEmptyMethodString = rhs.mPimpl->mEmptyMethodString;

    mPimpl->mIndentString = rhs.mPimpl->mIndentString;

    mPimpl->mOpenArrayInitializerString = rhs.mPimpl->mOpenArrayInitializerString;
    mPimpl->mCloseArrayInitializerString = rhs.mPimpl->mCloseArrayInitializerString;

    mPimpl->mOpenArrayString = rhs.mPimpl->mOpenArrayString;
    mPimpl->mCloseArrayString = rhs.mPimpl->mCloseArrayString;

    mPimpl->mArrayElementSeparatorString = rhs.mPimpl->mArrayElementSeparatorString;

    mPimpl->mStringDelimiterString = rhs.mPimpl->mStringDelimiterString;

    mPimpl->mCommandSeparatorString = rhs.mPimpl->mCommandSeparatorString;
}

GeneratorProfile::GeneratorProfile(GeneratorProfile &&rhs) noexcept
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

GeneratorProfile &GeneratorProfile::operator=(GeneratorProfile rhs)
{
    rhs.swap(*this);
    return *this;
}

void GeneratorProfile::swap(GeneratorProfile &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
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
    if (mPimpl->mHasInterface != hasInterface) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasInterface = hasInterface;
}

std::string GeneratorProfile::assignmentString() const
{
    return mPimpl->mAssignmentString;
}

void GeneratorProfile::setAssignmentString(const std::string &assignmentString)
{
    if (mPimpl->mAssignmentString != assignmentString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAssignmentString = assignmentString;
}

std::string GeneratorProfile::eqString() const
{
    return mPimpl->mEqString;
}

void GeneratorProfile::setEqString(const std::string &eqString)
{
    if (mPimpl->mEqString != eqString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mEqString = eqString;
}

std::string GeneratorProfile::neqString() const
{
    return mPimpl->mNeqString;
}

void GeneratorProfile::setNeqString(const std::string &neqString)
{
    if (mPimpl->mNeqString != neqString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mNeqString = neqString;
}

std::string GeneratorProfile::ltString() const
{
    return mPimpl->mLtString;
}

void GeneratorProfile::setLtString(const std::string &ltString)
{
    if (mPimpl->mLtString != ltString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mLtString = ltString;
}

std::string GeneratorProfile::leqString() const
{
    return mPimpl->mLeqString;
}

void GeneratorProfile::setLeqString(const std::string &leqString)
{
    if (mPimpl->mLeqString != leqString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mLeqString = leqString;
}

std::string GeneratorProfile::gtString() const
{
    return mPimpl->mGtString;
}

void GeneratorProfile::setGtString(const std::string &gtString)
{
    if (mPimpl->mGtString != gtString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mGtString = gtString;
}

std::string GeneratorProfile::geqString() const
{
    return mPimpl->mGeqString;
}

void GeneratorProfile::setGeqString(const std::string &geqString)
{
    if (mPimpl->mGeqString != geqString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mGeqString = geqString;
}

std::string GeneratorProfile::andString() const
{
    return mPimpl->mAndString;
}

void GeneratorProfile::setAndString(const std::string &andString)
{
    if (mPimpl->mAndString != andString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAndString = andString;
}

std::string GeneratorProfile::orString() const
{
    return mPimpl->mOrString;
}

void GeneratorProfile::setOrString(const std::string &orString)
{
    if (mPimpl->mOrString != orString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mOrString = orString;
}

std::string GeneratorProfile::xorString() const
{
    return mPimpl->mXorString;
}

void GeneratorProfile::setXorString(const std::string &xorString)
{
    if (mPimpl->mXorString != xorString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mXorString = xorString;
}

std::string GeneratorProfile::notString() const
{
    return mPimpl->mNotString;
}

void GeneratorProfile::setNotString(const std::string &notString)
{
    if (mPimpl->mNotString != notString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mNotString = notString;
}

bool GeneratorProfile::hasEqOperator() const
{
    return mPimpl->mHasEqOperator;
}

void GeneratorProfile::setHasEqOperator(bool hasEqOperator)
{
    if (mPimpl->mHasEqOperator != hasEqOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasEqOperator = hasEqOperator;
}

bool GeneratorProfile::hasNeqOperator() const
{
    return mPimpl->mHasNeqOperator;
}

void GeneratorProfile::setHasNeqOperator(bool hasNeqOperator)
{
    if (mPimpl->mHasNeqOperator != hasNeqOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasNeqOperator = hasNeqOperator;
}

bool GeneratorProfile::hasLtOperator() const
{
    return mPimpl->mHasLtOperator;
}

void GeneratorProfile::setHasLtOperator(bool hasLtOperator)
{
    if (mPimpl->mHasLtOperator != hasLtOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasLtOperator = hasLtOperator;
}

bool GeneratorProfile::hasLeqOperator() const
{
    return mPimpl->mHasLeqOperator;
}

void GeneratorProfile::setHasLeqOperator(bool hasLeqOperator)
{
    if (mPimpl->mHasLeqOperator != hasLeqOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasLeqOperator = hasLeqOperator;
}

bool GeneratorProfile::hasGtOperator() const
{
    return mPimpl->mHasGtOperator;
}

void GeneratorProfile::setHasGtOperator(bool hasGtOperator)
{
    if (mPimpl->mHasGtOperator != hasGtOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasGtOperator = hasGtOperator;
}

bool GeneratorProfile::hasGeqOperator() const
{
    return mPimpl->mHasGeqOperator;
}

void GeneratorProfile::setHasGeqOperator(bool hasGeqOperator)
{
    if (mPimpl->mHasGeqOperator != hasGeqOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasGeqOperator = hasGeqOperator;
}

bool GeneratorProfile::hasAndOperator() const
{
    return mPimpl->mHasAndOperator;
}

void GeneratorProfile::setHasAndOperator(bool hasAndOperator)
{
    if (mPimpl->mHasAndOperator != hasAndOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasAndOperator = hasAndOperator;
}

bool GeneratorProfile::hasOrOperator() const
{
    return mPimpl->mHasOrOperator;
}

void GeneratorProfile::setHasOrOperator(bool hasOrOperator)
{
    if (mPimpl->mHasOrOperator != hasOrOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasOrOperator = hasOrOperator;
}

bool GeneratorProfile::hasXorOperator() const
{
    return mPimpl->mHasXorOperator;
}

void GeneratorProfile::setHasXorOperator(bool hasXorOperator)
{
    if (mPimpl->mHasXorOperator != hasXorOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasXorOperator = hasXorOperator;
}

bool GeneratorProfile::hasNotOperator() const
{
    return mPimpl->mHasNotOperator;
}

void GeneratorProfile::setHasNotOperator(bool hasNotOperator)
{
    if (mPimpl->mHasNotOperator != hasNotOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasNotOperator = hasNotOperator;
}

std::string GeneratorProfile::plusString() const
{
    return mPimpl->mPlusString;
}

void GeneratorProfile::setPlusString(const std::string &plusString)
{
    if (mPimpl->mPlusString != plusString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mPlusString = plusString;
}

std::string GeneratorProfile::minusString() const
{
    return mPimpl->mMinusString;
}

void GeneratorProfile::setMinusString(const std::string &minusString)
{
    if (mPimpl->mMinusString != minusString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mMinusString = minusString;
}

std::string GeneratorProfile::timesString() const
{
    return mPimpl->mTimesString;
}

void GeneratorProfile::setTimesString(const std::string &timesString)
{
    if (mPimpl->mTimesString != timesString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mTimesString = timesString;
}

std::string GeneratorProfile::divideString() const
{
    return mPimpl->mDivideString;
}

void GeneratorProfile::setDivideString(const std::string &divideString)
{
    if (mPimpl->mDivideString != divideString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mDivideString = divideString;
}

std::string GeneratorProfile::powerString() const
{
    return mPimpl->mPowerString;
}

void GeneratorProfile::setPowerString(const std::string &powerString)
{
    if (mPimpl->mPowerString != powerString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mPowerString = powerString;
}

std::string GeneratorProfile::squareRootString() const
{
    return mPimpl->mSquareRootString;
}

void GeneratorProfile::setSquareRootString(const std::string &squareRootString)
{
    if (mPimpl->mSquareRootString != squareRootString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSquareRootString = squareRootString;
}

std::string GeneratorProfile::squareString() const
{
    return mPimpl->mSquareString;
}

void GeneratorProfile::setSquareString(const std::string &squareString)
{
    if (mPimpl->mSquareString != squareString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSquareString = squareString;
}

std::string GeneratorProfile::absoluteValueString() const
{
    return mPimpl->mAbsoluteValueString;
}

void GeneratorProfile::setAbsoluteValueString(const std::string &absoluteValueString)
{
    if (mPimpl->mAbsoluteValueString != absoluteValueString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAbsoluteValueString = absoluteValueString;
}

std::string GeneratorProfile::exponentialString() const
{
    return mPimpl->mExponentialString;
}

void GeneratorProfile::setExponentialString(const std::string &exponentialString)
{
    if (mPimpl->mExponentialString != exponentialString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mExponentialString = exponentialString;
}

std::string GeneratorProfile::napierianLogarithmString() const
{
    return mPimpl->mNapierianLogarithmString;
}

void GeneratorProfile::setNapierianLogarithmString(const std::string &napierianLogarithmString)
{
    if (mPimpl->mNapierianLogarithmString != napierianLogarithmString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mNapierianLogarithmString = napierianLogarithmString;
}

std::string GeneratorProfile::commonLogarithmString() const
{
    return mPimpl->mCommonLogarithmString;
}

void GeneratorProfile::setCommonLogarithmString(const std::string &commonLogarithmString)
{
    if (mPimpl->mCommonLogarithmString != commonLogarithmString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCommonLogarithmString = commonLogarithmString;
}

std::string GeneratorProfile::ceilingString() const
{
    return mPimpl->mCeilingString;
}

void GeneratorProfile::setCeilingString(const std::string &ceilingString)
{
    if (mPimpl->mCeilingString != ceilingString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCeilingString = ceilingString;
}

std::string GeneratorProfile::floorString() const
{
    return mPimpl->mFloorString;
}

void GeneratorProfile::setFloorString(const std::string &floorString)
{
    if (mPimpl->mFloorString != floorString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mFloorString = floorString;
}

std::string GeneratorProfile::minString() const
{
    return mPimpl->mMinString;
}

void GeneratorProfile::setMinString(const std::string &minString)
{
    if (mPimpl->mMinString != minString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mMinString = minString;
}

std::string GeneratorProfile::maxString() const
{
    return mPimpl->mMaxString;
}

void GeneratorProfile::setMaxString(const std::string &maxString)
{
    if (mPimpl->mMaxString != maxString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mMaxString = maxString;
}

std::string GeneratorProfile::remString() const
{
    return mPimpl->mRemString;
}

void GeneratorProfile::setRemString(const std::string &remString)
{
    if (mPimpl->mRemString != remString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mRemString = remString;
}

bool GeneratorProfile::hasPowerOperator() const
{
    return mPimpl->mHasPowerOperator;
}

void GeneratorProfile::setHasPowerOperator(bool hasPowerOperator)
{
    if (mPimpl->mHasPowerOperator != hasPowerOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasPowerOperator = hasPowerOperator;
}

std::string GeneratorProfile::sinString() const
{
    return mPimpl->mSinString;
}

void GeneratorProfile::setSinString(const std::string &sinString)
{
    if (mPimpl->mSinString != sinString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSinString = sinString;
}

std::string GeneratorProfile::cosString() const
{
    return mPimpl->mCosString;
}

void GeneratorProfile::setCosString(const std::string &cosString)
{
    if (mPimpl->mCosString != cosString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCosString = cosString;
}

std::string GeneratorProfile::tanString() const
{
    return mPimpl->mTanString;
}

void GeneratorProfile::setTanString(const std::string &tanString)
{
    if (mPimpl->mTanString != tanString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mTanString = tanString;
}

std::string GeneratorProfile::secString() const
{
    return mPimpl->mSecString;
}

void GeneratorProfile::setSecString(const std::string &secString)
{
    if (mPimpl->mSecString != secString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSecString = secString;
}

std::string GeneratorProfile::cscString() const
{
    return mPimpl->mCscString;
}

void GeneratorProfile::setCscString(const std::string &cscString)
{
    if (mPimpl->mCscString != cscString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCscString = cscString;
}

std::string GeneratorProfile::cotString() const
{
    return mPimpl->mCotString;
}

void GeneratorProfile::setCotString(const std::string &cotString)
{
    if (mPimpl->mCotString != cotString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCotString = cotString;
}

std::string GeneratorProfile::sinhString() const
{
    return mPimpl->mSinhString;
}

void GeneratorProfile::setSinhString(const std::string &sinhString)
{
    if (mPimpl->mSinhString != sinhString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSinhString = sinhString;
}

std::string GeneratorProfile::coshString() const
{
    return mPimpl->mCoshString;
}

void GeneratorProfile::setCoshString(const std::string &coshString)
{
    if (mPimpl->mCoshString != coshString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCoshString = coshString;
}

std::string GeneratorProfile::tanhString() const
{
    return mPimpl->mTanhString;
}

void GeneratorProfile::setTanhString(const std::string &tanhString)
{
    if (mPimpl->mTanhString != tanhString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mTanhString = tanhString;
}

std::string GeneratorProfile::sechString() const
{
    return mPimpl->mSechString;
}

void GeneratorProfile::setSechString(const std::string &sechString)
{
    if (mPimpl->mSechString != sechString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSechString = sechString;
}

std::string GeneratorProfile::cschString() const
{
    return mPimpl->mCschString;
}

void GeneratorProfile::setCschString(const std::string &cschString)
{
    if (mPimpl->mCschString != cschString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCschString = cschString;
}

std::string GeneratorProfile::cothString() const
{
    return mPimpl->mCothString;
}

void GeneratorProfile::setCothString(const std::string &cothString)
{
    if (mPimpl->mCothString != cothString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCothString = cothString;
}

std::string GeneratorProfile::asinString() const
{
    return mPimpl->mAsinString;
}

void GeneratorProfile::setAsinString(const std::string &asinString)
{
    if (mPimpl->mAsinString != asinString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAsinString = asinString;
}

std::string GeneratorProfile::acosString() const
{
    return mPimpl->mAcosString;
}

void GeneratorProfile::setAcosString(const std::string &acosString)
{
    if (mPimpl->mAcosString != acosString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcosString = acosString;
}

std::string GeneratorProfile::atanString() const
{
    return mPimpl->mAtanString;
}

void GeneratorProfile::setAtanString(const std::string &atanString)
{
    if (mPimpl->mAtanString != atanString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAtanString = atanString;
}

std::string GeneratorProfile::asecString() const
{
    return mPimpl->mAsecString;
}

void GeneratorProfile::setAsecString(const std::string &asecString)
{
    if (mPimpl->mAsecString != asecString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAsecString = asecString;
}

std::string GeneratorProfile::acscString() const
{
    return mPimpl->mAcscString;
}

void GeneratorProfile::setAcscString(const std::string &acscString)
{
    if (mPimpl->mAcscString != acscString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcscString = acscString;
}

std::string GeneratorProfile::acotString() const
{
    return mPimpl->mAcotString;
}

void GeneratorProfile::setAcotString(const std::string &acotString)
{
    if (mPimpl->mAcotString != acotString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcotString = acotString;
}

std::string GeneratorProfile::asinhString() const
{
    return mPimpl->mAsinhString;
}

void GeneratorProfile::setAsinhString(const std::string &asinhString)
{
    if (mPimpl->mAsinhString != asinhString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAsinhString = asinhString;
}

std::string GeneratorProfile::acoshString() const
{
    return mPimpl->mAcoshString;
}

void GeneratorProfile::setAcoshString(const std::string &acoshString)
{
    if (mPimpl->mAcoshString != acoshString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcoshString = acoshString;
}

std::string GeneratorProfile::atanhString() const
{
    return mPimpl->mAtanhString;
}

void GeneratorProfile::setAtanhString(const std::string &atanhString)
{
    if (mPimpl->mAtanhString != atanhString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAtanhString = atanhString;
}

std::string GeneratorProfile::asechString() const
{
    return mPimpl->mAsechString;
}

void GeneratorProfile::setAsechString(const std::string &asechString)
{
    if (mPimpl->mAsechString != asechString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAsechString = asechString;
}

std::string GeneratorProfile::acschString() const
{
    return mPimpl->mAcschString;
}

void GeneratorProfile::setAcschString(const std::string &acschString)
{
    if (mPimpl->mAcschString != acschString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcschString = acschString;
}

std::string GeneratorProfile::acothString() const
{
    return mPimpl->mAcothString;
}

void GeneratorProfile::setAcothString(const std::string &acothString)
{
    if (mPimpl->mAcothString != acothString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcothString = acothString;
}

std::string GeneratorProfile::conditionalOperatorIfString() const
{
    return mPimpl->mConditionalOperatorIfString;
}

void GeneratorProfile::setConditionalOperatorIfString(const std::string &conditionalOperatorIfString)
{
    if (mPimpl->mConditionalOperatorIfString != conditionalOperatorIfString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mConditionalOperatorIfString = conditionalOperatorIfString;
}

std::string GeneratorProfile::conditionalOperatorElseString() const
{
    return mPimpl->mConditionalOperatorElseString;
}

void GeneratorProfile::setConditionalOperatorElseString(const std::string &conditionalOperatorElseString)
{
    if (mPimpl->mConditionalOperatorElseString != conditionalOperatorElseString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mConditionalOperatorElseString = conditionalOperatorElseString;
}

std::string GeneratorProfile::piecewiseIfString() const
{
    return mPimpl->mPiecewiseIfString;
}

void GeneratorProfile::setPiecewiseIfString(const std::string &piecewiseIfString)
{
    if (mPimpl->mPiecewiseIfString != piecewiseIfString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mPiecewiseIfString = piecewiseIfString;
}

std::string GeneratorProfile::piecewiseElseString() const
{
    return mPimpl->mPiecewiseElseString;
}

void GeneratorProfile::setPiecewiseElseString(const std::string &piecewiseElseString)
{
    if (mPimpl->mPiecewiseElseString != piecewiseElseString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mPiecewiseElseString = piecewiseElseString;
}

bool GeneratorProfile::hasConditionalOperator() const
{
    return mPimpl->mHasConditionalOperator;
}

void GeneratorProfile::setHasConditionalOperator(bool hasConditionalOperator)
{
    if (mPimpl->mHasConditionalOperator != hasConditionalOperator) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mHasConditionalOperator = hasConditionalOperator;
}

std::string GeneratorProfile::trueString() const
{
    return mPimpl->mTrueString;
}

void GeneratorProfile::setTrueString(const std::string &trueString)
{
    if (mPimpl->mTrueString != trueString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mTrueString = trueString;
}

std::string GeneratorProfile::falseString() const
{
    return mPimpl->mFalseString;
}

void GeneratorProfile::setFalseString(const std::string &falseString)
{
    if (mPimpl->mFalseString != falseString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mFalseString = falseString;
}

std::string GeneratorProfile::eString() const
{
    return mPimpl->mEString;
}

void GeneratorProfile::setEString(const std::string &eString)
{
    if (mPimpl->mEString != eString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mEString = eString;
}

std::string GeneratorProfile::piString() const
{
    return mPimpl->mPiString;
}

void GeneratorProfile::setPiString(const std::string &piString)
{
    if (mPimpl->mPiString != piString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mPiString = piString;
}

std::string GeneratorProfile::infString() const
{
    return mPimpl->mInfString;
}

void GeneratorProfile::setInfString(const std::string &infString)
{
    if (mPimpl->mInfString != infString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInfString = infString;
}

std::string GeneratorProfile::nanString() const
{
    return mPimpl->mNanString;
}

void GeneratorProfile::setNanString(const std::string &nanString)
{
    if (mPimpl->mNanString != nanString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mNanString = nanString;
}

std::string GeneratorProfile::interfaceEqFunctionString() const
{
    return mPimpl->mInterfaceEqFunctionString;
}

void GeneratorProfile::setInterfaceEqFunctionString(const std::string &interfaceEqFunctionString)
{
    if (mPimpl->mInterfaceEqFunctionString != interfaceEqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceEqFunctionString = interfaceEqFunctionString;
}

std::string GeneratorProfile::implementationEqFunctionString() const
{
    return mPimpl->mImplementationEqFunctionString;
}

void GeneratorProfile::setImplementationEqFunctionString(const std::string &implementationEqFunctionString)
{
    if (mPimpl->mImplementationEqFunctionString != implementationEqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationEqFunctionString = implementationEqFunctionString;
}

std::string GeneratorProfile::interfaceNeqFunctionString() const
{
    return mPimpl->mInterfaceNeqFunctionString;
}

void GeneratorProfile::setInterfaceNeqFunctionString(const std::string &interfaceNeqFunctionString)
{
    if (mPimpl->mInterfaceNeqFunctionString != interfaceNeqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceNeqFunctionString = interfaceNeqFunctionString;
}

std::string GeneratorProfile::implementationNeqFunctionString() const
{
    return mPimpl->mImplementationNeqFunctionString;
}

void GeneratorProfile::setImplementationNeqFunctionString(const std::string &implementationNeqFunctionString)
{
    if (mPimpl->mImplementationNeqFunctionString != implementationNeqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationNeqFunctionString = implementationNeqFunctionString;
}

std::string GeneratorProfile::interfaceLtFunctionString() const
{
    return mPimpl->mInterfaceLtFunctionString;
}

void GeneratorProfile::setInterfaceLtFunctionString(const std::string &interfaceLtFunctionString)
{
    if (mPimpl->mInterfaceLtFunctionString != interfaceLtFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceLtFunctionString = interfaceLtFunctionString;
}

std::string GeneratorProfile::implementationLtFunctionString() const
{
    return mPimpl->mImplementationLtFunctionString;
}

void GeneratorProfile::setImplementationLtFunctionString(const std::string &implementationLtFunctionString)
{
    if (mPimpl->mImplementationLtFunctionString != implementationLtFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationLtFunctionString = implementationLtFunctionString;
}

std::string GeneratorProfile::interfaceLeqFunctionString() const
{
    return mPimpl->mInterfaceLeqFunctionString;
}

void GeneratorProfile::setInterfaceLeqFunctionString(const std::string &interfaceLeqFunctionString)
{
    if (mPimpl->mInterfaceLeqFunctionString != interfaceLeqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceLeqFunctionString = interfaceLeqFunctionString;
}

std::string GeneratorProfile::implementationLeqFunctionString() const
{
    return mPimpl->mImplementationLeqFunctionString;
}

void GeneratorProfile::setImplementationLeqFunctionString(const std::string &implementationLeqFunctionString)
{
    if (mPimpl->mImplementationLeqFunctionString != implementationLeqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationLeqFunctionString = implementationLeqFunctionString;
}

std::string GeneratorProfile::interfaceGtFunctionString() const
{
    return mPimpl->mInterfaceGtFunctionString;
}

void GeneratorProfile::setInterfaceGtFunctionString(const std::string &interfaceGtFunctionString)
{
    if (mPimpl->mInterfaceGtFunctionString != interfaceGtFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceGtFunctionString = interfaceGtFunctionString;
}

std::string GeneratorProfile::implementationGtFunctionString() const
{
    return mPimpl->mImplementationGtFunctionString;
}

void GeneratorProfile::setImplementationGtFunctionString(const std::string &implementationGtFunctionString)
{
    if (mPimpl->mImplementationGtFunctionString != implementationGtFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationGtFunctionString = implementationGtFunctionString;
}

std::string GeneratorProfile::interfaceGeqFunctionString() const
{
    return mPimpl->mInterfaceGeqFunctionString;
}

void GeneratorProfile::setInterfaceGeqFunctionString(const std::string &interfaceGeqFunctionString)
{
    if (mPimpl->mInterfaceGeqFunctionString != interfaceGeqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceGeqFunctionString = interfaceGeqFunctionString;
}

std::string GeneratorProfile::implementationGeqFunctionString() const
{
    return mPimpl->mImplementationGeqFunctionString;
}

void GeneratorProfile::setImplementationGeqFunctionString(const std::string &implementationGeqFunctionString)
{
    if (mPimpl->mImplementationGeqFunctionString != implementationGeqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationGeqFunctionString = implementationGeqFunctionString;
}

std::string GeneratorProfile::interfaceAndFunctionString() const
{
    return mPimpl->mInterfaceAndFunctionString;
}

void GeneratorProfile::setInterfaceAndFunctionString(const std::string &interfaceAndFunctionString)
{
    if (mPimpl->mInterfaceAndFunctionString != interfaceAndFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAndFunctionString = interfaceAndFunctionString;
}

std::string GeneratorProfile::implementationAndFunctionString() const
{
    return mPimpl->mImplementationAndFunctionString;
}

void GeneratorProfile::setImplementationAndFunctionString(const std::string &implementationAndFunctionString)
{
    if (mPimpl->mImplementationAndFunctionString != implementationAndFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAndFunctionString = implementationAndFunctionString;
}

std::string GeneratorProfile::interfaceOrFunctionString() const
{
    return mPimpl->mInterfaceOrFunctionString;
}

void GeneratorProfile::setInterfaceOrFunctionString(const std::string &interfaceOrFunctionString)
{
    if (mPimpl->mInterfaceOrFunctionString != interfaceOrFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceOrFunctionString = interfaceOrFunctionString;
}

std::string GeneratorProfile::implementationOrFunctionString() const
{
    return mPimpl->mImplementationOrFunctionString;
}

void GeneratorProfile::setImplementationOrFunctionString(const std::string &implementationOrFunctionString)
{
    if (mPimpl->mImplementationOrFunctionString != implementationOrFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationOrFunctionString = implementationOrFunctionString;
}

std::string GeneratorProfile::interfaceXorFunctionString() const
{
    return mPimpl->mInterfaceXorFunctionString;
}

void GeneratorProfile::setInterfaceXorFunctionString(const std::string &interfaceXorFunctionString)
{
    if (mPimpl->mInterfaceXorFunctionString != interfaceXorFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceXorFunctionString = interfaceXorFunctionString;
}

std::string GeneratorProfile::implementationXorFunctionString() const
{
    return mPimpl->mImplementationXorFunctionString;
}

void GeneratorProfile::setImplementationXorFunctionString(const std::string &implementationXorFunctionString)
{
    if (mPimpl->mImplementationXorFunctionString != implementationXorFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationXorFunctionString = implementationXorFunctionString;
}

std::string GeneratorProfile::interfaceNotFunctionString() const
{
    return mPimpl->mInterfaceNotFunctionString;
}

void GeneratorProfile::setInterfaceNotFunctionString(const std::string &interfaceNotFunctionString)
{
    if (mPimpl->mInterfaceNotFunctionString != interfaceNotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceNotFunctionString = interfaceNotFunctionString;
}

std::string GeneratorProfile::implementationNotFunctionString() const
{
    return mPimpl->mImplementationNotFunctionString;
}

void GeneratorProfile::setImplementationNotFunctionString(const std::string &implementationNotFunctionString)
{
    if (mPimpl->mImplementationNotFunctionString != implementationNotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationNotFunctionString = implementationNotFunctionString;
}

std::string GeneratorProfile::interfaceMinFunctionString() const
{
    return mPimpl->mInterfaceMinFunctionString;
}

void GeneratorProfile::setInterfaceMinFunctionString(const std::string &interfaceMinFunctionString)
{
    if (mPimpl->mInterfaceMinFunctionString != interfaceMinFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceMinFunctionString = interfaceMinFunctionString;
}

std::string GeneratorProfile::implementationMinFunctionString() const
{
    return mPimpl->mImplementationMinFunctionString;
}

void GeneratorProfile::setImplementationMinFunctionString(const std::string &implementationMinFunctionString)
{
    if (mPimpl->mImplementationMinFunctionString != implementationMinFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationMinFunctionString = implementationMinFunctionString;
}

std::string GeneratorProfile::interfaceMaxFunctionString() const
{
    return mPimpl->mInterfaceMaxFunctionString;
}

void GeneratorProfile::setInterfaceMaxFunctionString(const std::string &interfaceMaxFunctionString)
{
    if (mPimpl->mInterfaceMaxFunctionString != interfaceMaxFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceMaxFunctionString = interfaceMaxFunctionString;
}

std::string GeneratorProfile::implementationMaxFunctionString() const
{
    return mPimpl->mImplementationMaxFunctionString;
}

void GeneratorProfile::setImplementationMaxFunctionString(const std::string &implementationMaxFunctionString)
{
    if (mPimpl->mImplementationMaxFunctionString != implementationMaxFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationMaxFunctionString = implementationMaxFunctionString;
}

std::string GeneratorProfile::interfaceSecFunctionString() const
{
    return mPimpl->mInterfaceSecFunctionString;
}

void GeneratorProfile::setInterfaceSecFunctionString(const std::string &interfaceSecFunctionString)
{
    if (mPimpl->mInterfaceSecFunctionString != interfaceSecFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceSecFunctionString = interfaceSecFunctionString;
}

std::string GeneratorProfile::implementationSecFunctionString() const
{
    return mPimpl->mImplementationSecFunctionString;
}

void GeneratorProfile::setImplementationSecFunctionString(const std::string &implementationSecFunctionString)
{
    if (mPimpl->mImplementationSecFunctionString != implementationSecFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationSecFunctionString = implementationSecFunctionString;
}

std::string GeneratorProfile::interfaceCscFunctionString() const
{
    return mPimpl->mInterfaceCscFunctionString;
}

void GeneratorProfile::setInterfaceCscFunctionString(const std::string &interfaceCscFunctionString)
{
    if (mPimpl->mInterfaceCscFunctionString != interfaceCscFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceCscFunctionString = interfaceCscFunctionString;
}

std::string GeneratorProfile::implementationCscFunctionString() const
{
    return mPimpl->mImplementationCscFunctionString;
}

void GeneratorProfile::setImplementationCscFunctionString(const std::string &implementationCscFunctionString)
{
    if (mPimpl->mImplementationCscFunctionString != implementationCscFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationCscFunctionString = implementationCscFunctionString;
}

std::string GeneratorProfile::interfaceCotFunctionString() const
{
    return mPimpl->mInterfaceCotFunctionString;
}

void GeneratorProfile::setInterfaceCotFunctionString(const std::string &interfaceCotFunctionString)
{
    if (mPimpl->mInterfaceCotFunctionString != interfaceCotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceCotFunctionString = interfaceCotFunctionString;
}

std::string GeneratorProfile::implementationCotFunctionString() const
{
    return mPimpl->mImplementationCotFunctionString;
}

void GeneratorProfile::setImplementationCotFunctionString(const std::string &implementationCotFunctionString)
{
    if (mPimpl->mImplementationCotFunctionString != implementationCotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationCotFunctionString = implementationCotFunctionString;
}

std::string GeneratorProfile::interfaceSechFunctionString() const
{
    return mPimpl->mInterfaceSechFunctionString;
}

void GeneratorProfile::setInterfaceSechFunctionString(const std::string &interfaceSechFunctionString)
{
    if (mPimpl->mInterfaceSechFunctionString != interfaceSechFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceSechFunctionString = interfaceSechFunctionString;
}

std::string GeneratorProfile::implementationSechFunctionString() const
{
    return mPimpl->mImplementationSechFunctionString;
}

void GeneratorProfile::setImplementationSechFunctionString(const std::string &implementationSechFunctionString)
{
    if (mPimpl->mImplementationSechFunctionString != implementationSechFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationSechFunctionString = implementationSechFunctionString;
}

std::string GeneratorProfile::interfaceCschFunctionString() const
{
    return mPimpl->mInterfaceCschFunctionString;
}

void GeneratorProfile::setInterfaceCschFunctionString(const std::string &interfaceCschFunctionString)
{
    if (mPimpl->mInterfaceCschFunctionString != interfaceCschFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceCschFunctionString = interfaceCschFunctionString;
}

std::string GeneratorProfile::implementationCschFunctionString() const
{
    return mPimpl->mImplementationCschFunctionString;
}

void GeneratorProfile::setImplementationCschFunctionString(const std::string &implementationCschFunctionString)
{
    if (mPimpl->mImplementationCschFunctionString != implementationCschFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationCschFunctionString = implementationCschFunctionString;
}

std::string GeneratorProfile::interfaceCothFunctionString() const
{
    return mPimpl->mInterfaceCothFunctionString;
}

void GeneratorProfile::setInterfaceCothFunctionString(const std::string &interfaceCothFunctionString)
{
    if (mPimpl->mInterfaceCothFunctionString != interfaceCothFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceCothFunctionString = interfaceCothFunctionString;
}

std::string GeneratorProfile::implementationCothFunctionString() const
{
    return mPimpl->mImplementationCothFunctionString;
}

void GeneratorProfile::setImplementationCothFunctionString(const std::string &implementationCothFunctionString)
{
    if (mPimpl->mImplementationCothFunctionString != implementationCothFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationCothFunctionString = implementationCothFunctionString;
}

std::string GeneratorProfile::interfaceAsecFunctionString() const
{
    return mPimpl->mInterfaceAsecFunctionString;
}

void GeneratorProfile::setInterfaceAsecFunctionString(const std::string &interfaceAsecFunctionString)
{
    if (mPimpl->mInterfaceAsecFunctionString != interfaceAsecFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAsecFunctionString = interfaceAsecFunctionString;
}

std::string GeneratorProfile::implementationAsecFunctionString() const
{
    return mPimpl->mImplementationAsecFunctionString;
}

void GeneratorProfile::setImplementationAsecFunctionString(const std::string &implementationAsecFunctionString)
{
    if (mPimpl->mImplementationAsecFunctionString != implementationAsecFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAsecFunctionString = implementationAsecFunctionString;
}

std::string GeneratorProfile::interfaceAcscFunctionString() const
{
    return mPimpl->mInterfaceAcscFunctionString;
}

void GeneratorProfile::setInterfaceAcscFunctionString(const std::string &interfaceAcscFunctionString)
{
    if (mPimpl->mInterfaceAcscFunctionString != interfaceAcscFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAcscFunctionString = interfaceAcscFunctionString;
}

std::string GeneratorProfile::implementationAcscFunctionString() const
{
    return mPimpl->mImplementationAcscFunctionString;
}

void GeneratorProfile::setImplementationAcscFunctionString(const std::string &implementationAcscFunctionString)
{
    if (mPimpl->mImplementationAcscFunctionString != implementationAcscFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAcscFunctionString = implementationAcscFunctionString;
}

std::string GeneratorProfile::interfaceAcotFunctionString() const
{
    return mPimpl->mInterfaceAcotFunctionString;
}

void GeneratorProfile::setInterfaceAcotFunctionString(const std::string &interfaceAcotFunctionString)
{
    if (mPimpl->mInterfaceAcotFunctionString != interfaceAcotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAcotFunctionString = interfaceAcotFunctionString;
}

std::string GeneratorProfile::implementationAcotFunctionString() const
{
    return mPimpl->mImplementationAcotFunctionString;
}

void GeneratorProfile::setImplementationAcotFunctionString(const std::string &implementationAcotFunctionString)
{
    if (mPimpl->mImplementationAcotFunctionString != implementationAcotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAcotFunctionString = implementationAcotFunctionString;
}

std::string GeneratorProfile::interfaceAsechFunctionString() const
{
    return mPimpl->mInterfaceAsechFunctionString;
}

void GeneratorProfile::setInterfaceAsechFunctionString(const std::string &interfaceAsechFunctionString)
{
    if (mPimpl->mInterfaceAsechFunctionString != interfaceAsechFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAsechFunctionString = interfaceAsechFunctionString;
}

std::string GeneratorProfile::implementationAsechFunctionString() const
{
    return mPimpl->mImplementationAsechFunctionString;
}

void GeneratorProfile::setImplementationAsechFunctionString(const std::string &implementationAsechFunctionString)
{
    if (mPimpl->mImplementationAsechFunctionString != implementationAsechFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAsechFunctionString = implementationAsechFunctionString;
}

std::string GeneratorProfile::interfaceAcschFunctionString() const
{
    return mPimpl->mInterfaceAcschFunctionString;
}

void GeneratorProfile::setInterfaceAcschFunctionString(const std::string &interfaceAcschFunctionString)
{
    if (mPimpl->mInterfaceAcschFunctionString != interfaceAcschFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAcschFunctionString = interfaceAcschFunctionString;
}

std::string GeneratorProfile::implementationAcschFunctionString() const
{
    return mPimpl->mImplementationAcschFunctionString;
}

void GeneratorProfile::setImplementationAcschFunctionString(const std::string &implementationAcschFunctionString)
{
    if (mPimpl->mImplementationAcschFunctionString != implementationAcschFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAcschFunctionString = implementationAcschFunctionString;
}

std::string GeneratorProfile::interfaceAcothFunctionString() const
{
    return mPimpl->mInterfaceAcothFunctionString;
}

void GeneratorProfile::setInterfaceAcothFunctionString(const std::string &interfaceAcothFunctionString)
{
    if (mPimpl->mInterfaceAcothFunctionString != interfaceAcothFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceAcothFunctionString = interfaceAcothFunctionString;
}

std::string GeneratorProfile::implementationAcothFunctionString() const
{
    return mPimpl->mImplementationAcothFunctionString;
}

void GeneratorProfile::setImplementationAcothFunctionString(const std::string &implementationAcothFunctionString)
{
    if (mPimpl->mImplementationAcothFunctionString != implementationAcothFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationAcothFunctionString = implementationAcothFunctionString;
}

std::string GeneratorProfile::commentString() const
{
    return mPimpl->mCommentString;
}

void GeneratorProfile::setCommentString(const std::string &commentString)
{
    if (mPimpl->mCommentString != commentString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCommentString = commentString;
}

std::string GeneratorProfile::originCommentString() const
{
    return mPimpl->mOriginCommentString;
}

void GeneratorProfile::setOriginCommentString(const std::string &originCommentString)
{
    if (mPimpl->mOriginCommentString != originCommentString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mOriginCommentString = originCommentString;
}

std::string GeneratorProfile::interfaceHeaderString() const
{
    return mPimpl->mInterfaceHeaderString;
}

void GeneratorProfile::setInterfaceHeaderString(const std::string &interfaceHeaderString)
{
    if (mPimpl->mInterfaceHeaderString != interfaceHeaderString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceHeaderString = interfaceHeaderString;
}

std::string GeneratorProfile::implementationHeaderString() const
{
    return mPimpl->mImplementationHeaderString;
}

void GeneratorProfile::setImplementationHeaderString(const std::string &implementationHeaderString)
{
    if (mPimpl->mImplementationHeaderString != implementationHeaderString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationHeaderString = implementationHeaderString;
}

std::string GeneratorProfile::interfaceLibcellmlVersionString() const
{
    return mPimpl->mInterfaceLibcellmlVersionString;
}

void GeneratorProfile::setInterfaceLibcellmlVersionString(const std::string &interfaceLibcellmlVersionString)
{
    if (mPimpl->mInterfaceLibcellmlVersionString != interfaceLibcellmlVersionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceLibcellmlVersionString = interfaceLibcellmlVersionString;
}

std::string GeneratorProfile::implementationLibcellmlVersionString() const
{
    return mPimpl->mImplementationLibcellmlVersionString;
}

void GeneratorProfile::setImplementationLibcellmlVersionString(const std::string &implementationLibcellmlVersionString)
{
    if (mPimpl->mImplementationLibcellmlVersionString != implementationLibcellmlVersionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationLibcellmlVersionString = implementationLibcellmlVersionString;
}

std::string GeneratorProfile::interfaceStateCountString() const
{
    return mPimpl->mInterfaceStateCountString;
}

void GeneratorProfile::setInterfaceStateCountString(const std::string &interfaceStateCountString)
{
    if (mPimpl->mInterfaceStateCountString != interfaceStateCountString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceStateCountString = interfaceStateCountString;
}

std::string GeneratorProfile::implementationStateCountString() const
{
    return mPimpl->mImplementationStateCountString;
}

void GeneratorProfile::setImplementationStateCountString(const std::string &implementationStateCountString)
{
    if (mPimpl->mImplementationStateCountString != implementationStateCountString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationStateCountString = implementationStateCountString;
}

std::string GeneratorProfile::interfaceVariableCountString() const
{
    return mPimpl->mInterfaceVariableCountString;
}

void GeneratorProfile::setInterfaceVariableCountString(const std::string &interfaceVariableCountString)
{
    if (mPimpl->mInterfaceVariableCountString != interfaceVariableCountString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceVariableCountString = interfaceVariableCountString;
}

std::string GeneratorProfile::implementationVariableCountString() const
{
    return mPimpl->mImplementationVariableCountString;
}

void GeneratorProfile::setImplementationVariableCountString(const std::string &implementationVariableCountString)
{
    if (mPimpl->mImplementationVariableCountString != implementationVariableCountString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationVariableCountString = implementationVariableCountString;
}

std::string GeneratorProfile::variableTypeObjectString() const
{
    return mPimpl->mVariableTypeObjectString;
}

void GeneratorProfile::setVariableTypeObjectString(const std::string &variableTypeObjectString)
{
    if (mPimpl->mVariableTypeObjectString != variableTypeObjectString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableTypeObjectString = variableTypeObjectString;
}

std::string GeneratorProfile::constantVariableTypeString() const
{
    return mPimpl->mConstantVariableType;
}

void GeneratorProfile::setConstantVariableTypeString(const std::string &constantVariableTypeString)
{
    if (mPimpl->mConstantVariableType != constantVariableTypeString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mConstantVariableType = constantVariableTypeString;
}

std::string GeneratorProfile::computedConstantVariableTypeString() const
{
    return mPimpl->mComputedConstantVariableType;
}

void GeneratorProfile::setComputedConstantVariableTypeString(const std::string &computedConstantVariableTypeString)
{
    if (mPimpl->mComputedConstantVariableType != computedConstantVariableTypeString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mComputedConstantVariableType = computedConstantVariableTypeString;
}

std::string GeneratorProfile::algebraicVariableTypeString() const
{
    return mPimpl->mAlgebraicVariableType;
}

void GeneratorProfile::setAlgebraicVariableTypeString(const std::string &algebraicVariableTypeString)
{
    if (mPimpl->mAlgebraicVariableType != algebraicVariableTypeString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAlgebraicVariableType = algebraicVariableTypeString;
}

std::string GeneratorProfile::variableInfoObjectString() const
{
    return mPimpl->mVariableInfoObjectString;
}

void GeneratorProfile::setVariableInfoObjectString(const std::string &variableInfoObjectString)
{
    if (mPimpl->mVariableInfoObjectString != variableInfoObjectString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableInfoObjectString = variableInfoObjectString;
}

std::string GeneratorProfile::variableInfoWithTypeObjectString() const
{
    return mPimpl->mVariableInfoWithTypeObjectString;
}

void GeneratorProfile::setVariableInfoWithTypeObjectString(const std::string &variableInfoWithTypeObjectString)
{
    if (mPimpl->mVariableInfoWithTypeObjectString != variableInfoWithTypeObjectString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableInfoWithTypeObjectString = variableInfoWithTypeObjectString;
}

std::string GeneratorProfile::interfaceVoiInfoString() const
{
    return mPimpl->mInterfaceVoiInfoString;
}

void GeneratorProfile::setInterfaceVoiInfoString(const std::string &interfaceVoiInfoString)
{
    if (mPimpl->mInterfaceVoiInfoString != interfaceVoiInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceVoiInfoString = interfaceVoiInfoString;
}

std::string GeneratorProfile::implementationVoiInfoString() const
{
    return mPimpl->mImplementationVoiInfoString;
}

void GeneratorProfile::setImplementationVoiInfoString(const std::string &implementationVoiInfoString)
{
    if (mPimpl->mImplementationVoiInfoString != implementationVoiInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationVoiInfoString = implementationVoiInfoString;
}

std::string GeneratorProfile::interfaceStateInfoString() const
{
    return mPimpl->mInterfaceStateInfoString;
}

void GeneratorProfile::setInterfaceStateInfoString(const std::string &interfaceStateInfoString)
{
    if (mPimpl->mInterfaceStateInfoString != interfaceStateInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceStateInfoString = interfaceStateInfoString;
}

std::string GeneratorProfile::implementationStateInfoString() const
{
    return mPimpl->mImplementationStateInfoString;
}

void GeneratorProfile::setImplementationStateInfoString(const std::string &implementationStateInfoString)
{
    if (mPimpl->mImplementationStateInfoString != implementationStateInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationStateInfoString = implementationStateInfoString;
}

std::string GeneratorProfile::interfaceVariableInfoString() const
{
    return mPimpl->mInterfaceVariableInfoString;
}

void GeneratorProfile::setInterfaceVariableInfoString(const std::string &interfaceVariableInfoString)
{
    if (mPimpl->mInterfaceVariableInfoString != interfaceVariableInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceVariableInfoString = interfaceVariableInfoString;
}

std::string GeneratorProfile::implementationVariableInfoString() const
{
    return mPimpl->mImplementationVariableInfoString;
}

void GeneratorProfile::setImplementationVariableInfoString(const std::string &implementationVariableInfoString)
{
    if (mPimpl->mImplementationVariableInfoString != implementationVariableInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationVariableInfoString = implementationVariableInfoString;
}

std::string GeneratorProfile::variableInfoEntryString() const
{
    return mPimpl->mVariableInfoEntryString;
}

void GeneratorProfile::setVariableInfoEntryString(const std::string &variableInfoEntryString)
{
    if (mPimpl->mVariableInfoEntryString != variableInfoEntryString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableInfoEntryString = variableInfoEntryString;
}

std::string GeneratorProfile::variableInfoWithTypeEntryString() const
{
    return mPimpl->mVariableInfoWithTypeEntryString;
}

void GeneratorProfile::setVariableInfoWithTypeEntryString(const std::string &variableInfoWithTypeEntryString)
{
    if (mPimpl->mVariableInfoWithTypeEntryString != variableInfoWithTypeEntryString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableInfoWithTypeEntryString = variableInfoWithTypeEntryString;
}

std::string GeneratorProfile::voiString() const
{
    return mPimpl->mVoiString;
}

void GeneratorProfile::setVoiString(const std::string &voiString)
{
    if (mPimpl->mVoiString != voiString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVoiString = voiString;
}

std::string GeneratorProfile::statesArrayString() const
{
    return mPimpl->mStatesArrayString;
}

void GeneratorProfile::setStatesArrayString(const std::string &statesArrayString)
{
    if (mPimpl->mStatesArrayString != statesArrayString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mStatesArrayString = statesArrayString;
}

std::string GeneratorProfile::ratesArrayString() const
{
    return mPimpl->mRatesArrayString;
}

void GeneratorProfile::setRatesArrayString(const std::string &ratesArrayString)
{
    if (mPimpl->mRatesArrayString != ratesArrayString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mRatesArrayString = ratesArrayString;
}

std::string GeneratorProfile::variablesArrayString() const
{
    return mPimpl->mVariablesArrayString;
}

void GeneratorProfile::setVariablesArrayString(const std::string &variablesArrayString)
{
    if (mPimpl->mVariablesArrayString != variablesArrayString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariablesArrayString = variablesArrayString;
}

std::string GeneratorProfile::returnCreatedArrayString() const
{
    return mPimpl->mReturnCreatedArrayString;
}

void GeneratorProfile::setReturnCreatedArrayString(const std::string &returnCreatedArrayString)
{
    if (mPimpl->mReturnCreatedArrayString != returnCreatedArrayString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mReturnCreatedArrayString = returnCreatedArrayString;
}

std::string GeneratorProfile::interfaceCreateStatesArrayMethodString() const
{
    return mPimpl->mInterfaceCreateStatesArrayMethodString;
}

void GeneratorProfile::setInterfaceCreateStatesArrayMethodString(const std::string &interfaceCreateStatesArrayMethodString)
{
    if (mPimpl->mInterfaceCreateStatesArrayMethodString != interfaceCreateStatesArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceCreateStatesArrayMethodString = interfaceCreateStatesArrayMethodString;
}

std::string GeneratorProfile::implementationCreateStatesArrayMethodString() const
{
    return mPimpl->mImplementationCreateStatesArrayMethodString;
}

void GeneratorProfile::setImplementationCreateStatesArrayMethodString(const std::string &implementationCreateStatesArrayMethodString)
{
    if (mPimpl->mImplementationCreateStatesArrayMethodString != implementationCreateStatesArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationCreateStatesArrayMethodString = implementationCreateStatesArrayMethodString;
}

std::string GeneratorProfile::interfaceCreateVariablesArrayMethodString() const
{
    return mPimpl->mInterfaceCreateVariablesArrayMethodString;
}

void GeneratorProfile::setInterfaceCreateVariablesArrayMethodString(const std::string &interfaceCreateVariablesArrayMethodString)
{
    if (mPimpl->mInterfaceCreateVariablesArrayMethodString != interfaceCreateVariablesArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceCreateVariablesArrayMethodString = interfaceCreateVariablesArrayMethodString;
}

std::string GeneratorProfile::implementationCreateVariablesArrayMethodString() const
{
    return mPimpl->mImplementationCreateVariablesArrayMethodString;
}

void GeneratorProfile::setImplementationCreateVariablesArrayMethodString(const std::string &implementationCreateVariablesArrayMethodString)
{
    if (mPimpl->mImplementationCreateVariablesArrayMethodString != implementationCreateVariablesArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationCreateVariablesArrayMethodString = implementationCreateVariablesArrayMethodString;
}

std::string GeneratorProfile::interfaceDeleteArrayMethodString() const
{
    return mPimpl->mInterfaceDeleteArrayMethodString;
}

void GeneratorProfile::setInterfaceDeleteArrayMethodString(const std::string &interfaceDeleteArrayMethodString)
{
    if (mPimpl->mInterfaceDeleteArrayMethodString != interfaceDeleteArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceDeleteArrayMethodString = interfaceDeleteArrayMethodString;
}

std::string GeneratorProfile::implementationDeleteArrayMethodString() const
{
    return mPimpl->mImplementationDeleteArrayMethodString;
}

void GeneratorProfile::setImplementationDeleteArrayMethodString(const std::string &implementationDeleteArrayMethodString)
{
    if (mPimpl->mImplementationDeleteArrayMethodString != implementationDeleteArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationDeleteArrayMethodString = implementationDeleteArrayMethodString;
}

std::string GeneratorProfile::interfaceInitializeStatesAndConstantsMethodString() const
{
    return mPimpl->mInterfaceInitializeStatesAndConstantsMethodString;
}

void GeneratorProfile::setInterfaceInitializeStatesAndConstantsMethodString(const std::string &interfaceInitializeStatesAndConstantsMethodString)
{
    if (mPimpl->mInterfaceInitializeStatesAndConstantsMethodString != interfaceInitializeStatesAndConstantsMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceInitializeStatesAndConstantsMethodString = interfaceInitializeStatesAndConstantsMethodString;
}

std::string GeneratorProfile::implementationInitializeStatesAndConstantsMethodString() const
{
    return mPimpl->mImplementationInitializeStatesAndConstantsMethodString;
}

void GeneratorProfile::setImplementationInitializeStatesAndConstantsMethodString(const std::string &implementationInitializeStatesAndConstantsMethodString)
{
    if (mPimpl->mImplementationInitializeStatesAndConstantsMethodString != implementationInitializeStatesAndConstantsMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationInitializeStatesAndConstantsMethodString = implementationInitializeStatesAndConstantsMethodString;
}

std::string GeneratorProfile::interfaceComputeComputedConstantsMethodString() const
{
    return mPimpl->mInterfaceComputeComputedConstantsMethodString;
}

void GeneratorProfile::setInterfaceComputeComputedConstantsMethodString(const std::string &interfaceComputeComputedConstantsMethodString)
{
    if (mPimpl->mInterfaceComputeComputedConstantsMethodString != interfaceComputeComputedConstantsMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceComputeComputedConstantsMethodString = interfaceComputeComputedConstantsMethodString;
}

std::string GeneratorProfile::implementationComputeComputedConstantsMethodString() const
{
    return mPimpl->mImplementationComputeComputedConstantsMethodString;
}

void GeneratorProfile::setImplementationComputeComputedConstantsMethodString(const std::string &implementationComputeComputedConstantsMethodString)
{
    if (mPimpl->mImplementationComputeComputedConstantsMethodString != implementationComputeComputedConstantsMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationComputeComputedConstantsMethodString = implementationComputeComputedConstantsMethodString;
}

std::string GeneratorProfile::interfaceComputeRatesMethodString() const
{
    return mPimpl->mInterfaceComputeRatesMethodString;
}

void GeneratorProfile::setInterfaceComputeRatesMethodString(const std::string &interfaceComputeRatesMethodString)
{
    if (mPimpl->mInterfaceComputeRatesMethodString != interfaceComputeRatesMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceComputeRatesMethodString = interfaceComputeRatesMethodString;
}

std::string GeneratorProfile::implementationComputeRatesMethodString() const
{
    return mPimpl->mImplementationComputeRatesMethodString;
}

void GeneratorProfile::setImplementationComputeRatesMethodString(const std::string &implementationComputeRatesMethodString)
{
    if (mPimpl->mImplementationComputeRatesMethodString != implementationComputeRatesMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationComputeRatesMethodString = implementationComputeRatesMethodString;
}

std::string GeneratorProfile::interfaceComputeVariablesMethodString() const
{
    return mPimpl->mInterfaceComputeVariablesMethodString;
}

void GeneratorProfile::setInterfaceComputeVariablesMethodString(const std::string &interfaceComputeVariablesMethodString)
{
    if (mPimpl->mInterfaceComputeVariablesMethodString != interfaceComputeVariablesMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInterfaceComputeVariablesMethodString = interfaceComputeVariablesMethodString;
}

std::string GeneratorProfile::implementationComputeVariablesMethodString() const
{
    return mPimpl->mImplementationComputeVariablesMethodString;
}

void GeneratorProfile::setImplementationComputeVariablesMethodString(const std::string &implementationComputeVariablesMethodString)
{
    if (mPimpl->mImplementationComputeVariablesMethodString != implementationComputeVariablesMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mImplementationComputeVariablesMethodString = implementationComputeVariablesMethodString;
}

std::string GeneratorProfile::emptyMethodString() const
{
    return mPimpl->mEmptyMethodString;
}

void GeneratorProfile::setEmptyMethodString(const std::string &emptyMethodString)
{
    if (mPimpl->mEmptyMethodString != emptyMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mEmptyMethodString = emptyMethodString;
}

std::string GeneratorProfile::indentString() const
{
    return mPimpl->mIndentString;
}

void GeneratorProfile::setIndentString(const std::string &indentString)
{
    if (mPimpl->mIndentString != indentString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mIndentString = indentString;
}

std::string GeneratorProfile::openArrayInitializerString() const
{
    return mPimpl->mOpenArrayInitializerString;
}

void GeneratorProfile::setOpenArrayInitializerString(const std::string &openArrayInitializerString)
{
    if (mPimpl->mOpenArrayInitializerString != openArrayInitializerString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mOpenArrayInitializerString = openArrayInitializerString;
}

std::string GeneratorProfile::closeArrayInitializerString() const
{
    return mPimpl->mCloseArrayInitializerString;
}

void GeneratorProfile::setCloseArrayInitializerString(const std::string &closeArrayInitializerString)
{
    if (mPimpl->mCloseArrayInitializerString != closeArrayInitializerString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCloseArrayInitializerString = closeArrayInitializerString;
}

std::string GeneratorProfile::openArrayString() const
{
    return mPimpl->mOpenArrayString;
}

void GeneratorProfile::setOpenArrayString(const std::string &openArrayString)
{
    if (mPimpl->mOpenArrayString != openArrayString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mOpenArrayString = openArrayString;
}

std::string GeneratorProfile::closeArrayString() const
{
    return mPimpl->mCloseArrayString;
}

void GeneratorProfile::setCloseArrayString(const std::string &closeArrayString)
{
    if (mPimpl->mCloseArrayString != closeArrayString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCloseArrayString = closeArrayString;
}

std::string GeneratorProfile::arrayElementSeparatorString() const
{
    return mPimpl->mArrayElementSeparatorString;
}

void GeneratorProfile::setArrayElementSeparatorString(const std::string &arrayElementSeparatorString)
{
    if (mPimpl->mArrayElementSeparatorString != arrayElementSeparatorString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mArrayElementSeparatorString = arrayElementSeparatorString;
}

std::string GeneratorProfile::stringDelimiterString() const
{
    return mPimpl->mStringDelimiterString;
}

void GeneratorProfile::setStringDelimiterString(const std::string &stringDelimiterString)
{
    if (mPimpl->mStringDelimiterString != stringDelimiterString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mStringDelimiterString = stringDelimiterString;
}

std::string GeneratorProfile::commandSeparatorString() const
{
    return mPimpl->mCommandSeparatorString;
}

void GeneratorProfile::setCommandSeparatorString(const std::string &commandSeparatorString)
{
    if (mPimpl->mCommandSeparatorString != commandSeparatorString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCommandSeparatorString = commandSeparatorString;
}

} // namespace libcellml
