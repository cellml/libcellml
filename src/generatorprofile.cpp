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

    std::string mInterfaceHeaderString;
    std::string mImplementationHeaderString;

    std::string mLibcellmlVersionString;

    std::string mStateCountString;
    std::string mVariableCountString;

    std::string mVariableTypeObjectString;

    std::string mConstantVariableType;
    std::string mComputedConstantVariableType;
    std::string mAlgebraicVariableType;

    std::string mVariableInfoObjectString;
    std::string mVariableInfoWithTypeObjectString;

    std::string mVoiInfoString;
    std::string mStateInfoString;
    std::string mVariableInfoString;

    std::string mVariableInfoEntryString;
    std::string mVariableInfoWithTypeEntryString;

    std::string mVoiString;

    std::string mStatesArrayString;
    std::string mRatesArrayString;
    std::string mVariablesArrayString;

    std::string mReturnCreatedArrayString;

    std::string mCreateStatesArrayMethodString;
    std::string mCreateVariablesArrayMethodString;
    std::string mDeleteArrayMethodString;

    std::string mInitializeStatesAndConstantsMethodString;
    std::string mComputeComputedConstantsMethodString;
    std::string mComputeRatesMethodString;
    std::string mComputeVariablesMethodString;

    std::string mEmptyMethodString;

    std::string mIndentString;

    std::string mOpenArrayString;
    std::string mCloseArrayString;

    std::string mArrayElementSeparatorString;
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

        mInterfaceHeaderString = "#include <stddef.h>\n";
        mImplementationHeaderString = "#include <math.h>\n"
                                      "#include <stdlib.h>\n";

        mLibcellmlVersionString = "const char LIBCELLML_VERSION[] = \"<LIBCELLML_VERSION>\";\n";

        mStateCountString = "const size_t STATE_COUNT = <STATE_COUNT>;\n";
        mVariableCountString = "const size_t VARIABLE_COUNT = <VARIABLE_COUNT>;\n";

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

        mVoiInfoString = "const VariableInfo VOI_INFO = <CODE>;\n";
        mStateInfoString = "const VariableInfo STATE_INFO[] = {\n"
                           "<CODE>"
                           "};\n";
        mVariableInfoString = "const VariableInfoWithType VARIABLE_INFO[] = {\n"
                              "<CODE>"
                              "};\n";

        mVariableInfoEntryString = "{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\"}";
        mVariableInfoWithTypeEntryString = "{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\", <TYPE>}";

        mVoiString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mReturnCreatedArrayString = "return (double *) malloc(<ARRAY_SIZE>*sizeof(double));\n";

        mCreateStatesArrayMethodString = "double * createStatesArray()\n{\n"
                                         "<CODE>"
                                         "}\n";
        mCreateVariablesArrayMethodString = "double * createVariablesArray()\n{\n"
                                            "<CODE>"
                                            "}\n";
        mDeleteArrayMethodString = "void deleteArray(double *array)\n"
                                   "{\n"
                                   "    free(array);\n"
                                   "}\n";

        mInitializeStatesAndConstantsMethodString = "void initializeStatesAndConstants(double *states, double *variables)\n{\n"
                                                    "<CODE>"
                                                    "}\n";
        mComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables)\n{\n"
                                                "<CODE>"
                                                "}\n";
        mComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables)\n{\n"
                                    "<CODE>"
                                    "}\n";
        mComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables)\n{\n"
                                        "<CODE>"
                                        "}\n";

        mEmptyMethodString = "";

        mIndentString = "    ";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mArrayElementSeparatorString = ",";
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

        mInterfaceHeaderString = "";
        mImplementationHeaderString = "from enum import Enum\n"
                                      "from math import *\n"
                                      "\n";

        mLibcellmlVersionString = "LIBCELLML_VERSION = \"<LIBCELLML_VERSION>\"\n";

        mStateCountString = "STATE_COUNT = <STATE_COUNT>\n";
        mVariableCountString = "VARIABLE_COUNT = <VARIABLE_COUNT>\n";

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

        mVoiInfoString = "VOI_INFO = <CODE>\n";
        mStateInfoString = "STATE_INFO = [\n"
                           "<CODE>"
                           "]\n";
        mVariableInfoString = "VARIABLE_INFO = [\n"
                              "<CODE>"
                              "]\n";

        mVariableInfoEntryString = "{\"name\": \"<NAME>\", \"units\": \"<UNITS>\", \"component\": \"<COMPONENT>\"}";
        mVariableInfoWithTypeEntryString = "{\"name\": \"<NAME>\", \"units\": \"<UNITS>\", \"component\": \"<COMPONENT>\", \"type\": <TYPE>}";

        mVoiString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mReturnCreatedArrayString = "return [nan]*<ARRAY_SIZE>\n";

        mCreateStatesArrayMethodString = "\n"
                                         "def create_states_array():\n"
                                         "<CODE>";
        mCreateVariablesArrayMethodString = "\n"
                                            "def create_variables_array():\n"
                                            "<CODE>";
        mDeleteArrayMethodString = "";

        mInitializeStatesAndConstantsMethodString = "\n"
                                                    "def initialize_states_and_constants(states, variables):\n"
                                                    "<CODE>";
        mComputeComputedConstantsMethodString = "\n"
                                                "def compute_computed_constants(variables):\n"
                                                "<CODE>";
        mComputeRatesMethodString = "\n"
                                    "def compute_rates(voi, states, rates, variables):\n"
                                    "<CODE>";
        mComputeVariablesMethodString = "\n"
                                        "def compute_variables(voi, states, rates, variables):\n"
                                        "<CODE>";

        mEmptyMethodString = "pass\n";

        mIndentString = "    ";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mArrayElementSeparatorString = ",";
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

    mPimpl->mEqFunctionString = rhs.mPimpl->mEqFunctionString;
    mPimpl->mNeqFunctionString = rhs.mPimpl->mNeqFunctionString;
    mPimpl->mLtFunctionString = rhs.mPimpl->mLtFunctionString;
    mPimpl->mLeqFunctionString = rhs.mPimpl->mLeqFunctionString;
    mPimpl->mGtFunctionString = rhs.mPimpl->mGtFunctionString;
    mPimpl->mGeqFunctionString = rhs.mPimpl->mGeqFunctionString;
    mPimpl->mAndFunctionString = rhs.mPimpl->mAndFunctionString;
    mPimpl->mOrFunctionString = rhs.mPimpl->mOrFunctionString;
    mPimpl->mXorFunctionString = rhs.mPimpl->mXorFunctionString;
    mPimpl->mNotFunctionString = rhs.mPimpl->mNotFunctionString;

    mPimpl->mMinFunctionString = rhs.mPimpl->mMinFunctionString;
    mPimpl->mMaxFunctionString = rhs.mPimpl->mMaxFunctionString;

    mPimpl->mSecFunctionString = rhs.mPimpl->mSecFunctionString;
    mPimpl->mCscFunctionString = rhs.mPimpl->mCscFunctionString;
    mPimpl->mCotFunctionString = rhs.mPimpl->mCotFunctionString;
    mPimpl->mSechFunctionString = rhs.mPimpl->mSechFunctionString;
    mPimpl->mCschFunctionString = rhs.mPimpl->mCschFunctionString;
    mPimpl->mCothFunctionString = rhs.mPimpl->mCothFunctionString;
    mPimpl->mAsecFunctionString = rhs.mPimpl->mAsecFunctionString;
    mPimpl->mAcscFunctionString = rhs.mPimpl->mAcscFunctionString;
    mPimpl->mAcotFunctionString = rhs.mPimpl->mAcotFunctionString;
    mPimpl->mAsechFunctionString = rhs.mPimpl->mAsechFunctionString;
    mPimpl->mAcschFunctionString = rhs.mPimpl->mAcschFunctionString;
    mPimpl->mAcothFunctionString = rhs.mPimpl->mAcothFunctionString;

    // Miscellaneous.

    mPimpl->mCommentString = rhs.mPimpl->mCommentString;
    mPimpl->mOriginCommentString = rhs.mPimpl->mOriginCommentString;

    mPimpl->mInterfaceHeaderString = rhs.mPimpl->mInterfaceHeaderString;
    mPimpl->mImplementationHeaderString = rhs.mPimpl->mImplementationHeaderString;

    mPimpl->mLibcellmlVersionString = rhs.mPimpl->mLibcellmlVersionString;

    mPimpl->mStateCountString = rhs.mPimpl->mStateCountString;
    mPimpl->mVariableCountString = rhs.mPimpl->mVariableCountString;

    mPimpl->mVariableTypeObjectString = rhs.mPimpl->mVariableTypeObjectString;

    mPimpl->mConstantVariableType = rhs.mPimpl->mConstantVariableType;
    mPimpl->mComputedConstantVariableType = rhs.mPimpl->mComputedConstantVariableType;
    mPimpl->mAlgebraicVariableType = rhs.mPimpl->mAlgebraicVariableType;

    mPimpl->mVariableInfoObjectString = rhs.mPimpl->mVariableInfoObjectString;
    mPimpl->mVariableInfoWithTypeObjectString = rhs.mPimpl->mVariableInfoWithTypeObjectString;

    mPimpl->mVoiInfoString = rhs.mPimpl->mVoiInfoString;
    mPimpl->mStateInfoString = rhs.mPimpl->mStateInfoString;
    mPimpl->mVariableInfoString = rhs.mPimpl->mVariableInfoString;

    mPimpl->mVariableInfoEntryString = rhs.mPimpl->mVariableInfoEntryString;
    mPimpl->mVariableInfoWithTypeEntryString = rhs.mPimpl->mVariableInfoWithTypeEntryString;

    mPimpl->mVoiString = rhs.mPimpl->mVoiString;

    mPimpl->mStatesArrayString = rhs.mPimpl->mStatesArrayString;
    mPimpl->mRatesArrayString = rhs.mPimpl->mRatesArrayString;
    mPimpl->mVariablesArrayString = rhs.mPimpl->mVariablesArrayString;

    mPimpl->mReturnCreatedArrayString = rhs.mPimpl->mReturnCreatedArrayString;

    mPimpl->mCreateStatesArrayMethodString = rhs.mPimpl->mCreateStatesArrayMethodString;
    mPimpl->mCreateVariablesArrayMethodString = rhs.mPimpl->mCreateVariablesArrayMethodString;
    mPimpl->mDeleteArrayMethodString = rhs.mPimpl->mDeleteArrayMethodString;

    mPimpl->mInitializeStatesAndConstantsMethodString = rhs.mPimpl->mInitializeStatesAndConstantsMethodString;
    mPimpl->mComputeComputedConstantsMethodString = rhs.mPimpl->mComputeComputedConstantsMethodString;
    mPimpl->mComputeRatesMethodString = rhs.mPimpl->mComputeRatesMethodString;
    mPimpl->mComputeVariablesMethodString = rhs.mPimpl->mComputeVariablesMethodString;

    mPimpl->mEmptyMethodString = rhs.mPimpl->mEmptyMethodString;

    mPimpl->mIndentString = rhs.mPimpl->mIndentString;

    mPimpl->mOpenArrayString = rhs.mPimpl->mOpenArrayString;
    mPimpl->mCloseArrayString = rhs.mPimpl->mCloseArrayString;

    mPimpl->mArrayElementSeparatorString = rhs.mPimpl->mArrayElementSeparatorString;
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

std::string GeneratorProfile::eqFunctionString() const
{
    return mPimpl->mEqFunctionString;
}

void GeneratorProfile::setEqFunctionString(const std::string &eqFunctionString)
{
    if (mPimpl->mEqFunctionString != eqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mEqFunctionString = eqFunctionString;
}

std::string GeneratorProfile::neqFunctionString() const
{
    return mPimpl->mNeqFunctionString;
}

void GeneratorProfile::setNeqFunctionString(const std::string &neqFunctionString)
{
    if (mPimpl->mNeqFunctionString != neqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mNeqFunctionString = neqFunctionString;
}

std::string GeneratorProfile::ltFunctionString() const
{
    return mPimpl->mLtFunctionString;
}

void GeneratorProfile::setLtFunctionString(const std::string &ltFunctionString)
{
    if (mPimpl->mLtFunctionString != ltFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mLtFunctionString = ltFunctionString;
}

std::string GeneratorProfile::leqFunctionString() const
{
    return mPimpl->mLeqFunctionString;
}

void GeneratorProfile::setLeqFunctionString(const std::string &leqFunctionString)
{
    if (mPimpl->mLeqFunctionString != leqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mLeqFunctionString = leqFunctionString;
}

std::string GeneratorProfile::gtFunctionString() const
{
    return mPimpl->mGtFunctionString;
}

void GeneratorProfile::setGtFunctionString(const std::string &gtFunctionString)
{
    if (mPimpl->mGtFunctionString != gtFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mGtFunctionString = gtFunctionString;
}

std::string GeneratorProfile::geqFunctionString() const
{
    return mPimpl->mGeqFunctionString;
}

void GeneratorProfile::setGeqFunctionString(const std::string &geqFunctionString)
{
    if (mPimpl->mGeqFunctionString != geqFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mGeqFunctionString = geqFunctionString;
}

std::string GeneratorProfile::andFunctionString() const
{
    return mPimpl->mAndFunctionString;
}

void GeneratorProfile::setAndFunctionString(const std::string &andFunctionString)
{
    if (mPimpl->mAndFunctionString != andFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAndFunctionString = andFunctionString;
}

std::string GeneratorProfile::orFunctionString() const
{
    return mPimpl->mOrFunctionString;
}

void GeneratorProfile::setOrFunctionString(const std::string &orFunctionString)
{
    if (mPimpl->mOrFunctionString != orFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mOrFunctionString = orFunctionString;
}

std::string GeneratorProfile::xorFunctionString() const
{
    return mPimpl->mXorFunctionString;
}

void GeneratorProfile::setXorFunctionString(const std::string &xorFunctionString)
{
    if (mPimpl->mXorFunctionString != xorFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mXorFunctionString = xorFunctionString;
}

std::string GeneratorProfile::notFunctionString() const
{
    return mPimpl->mNotFunctionString;
}

void GeneratorProfile::setNotFunctionString(const std::string &notFunctionString)
{
    if (mPimpl->mNotFunctionString != notFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mNotFunctionString = notFunctionString;
}

std::string GeneratorProfile::minFunctionString() const
{
    return mPimpl->mMinFunctionString;
}

void GeneratorProfile::setMinFunctionString(const std::string &minFunctionString)
{
    if (mPimpl->mMinFunctionString != minFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mMinFunctionString = minFunctionString;
}

std::string GeneratorProfile::maxFunctionString() const
{
    return mPimpl->mMaxFunctionString;
}

void GeneratorProfile::setMaxFunctionString(const std::string &maxFunctionString)
{
    if (mPimpl->mMaxFunctionString != maxFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mMaxFunctionString = maxFunctionString;
}

std::string GeneratorProfile::secFunctionString() const
{
    return mPimpl->mSecFunctionString;
}

void GeneratorProfile::setSecFunctionString(const std::string &secFunctionString)
{
    if (mPimpl->mSecFunctionString != secFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSecFunctionString = secFunctionString;
}

std::string GeneratorProfile::cscFunctionString() const
{
    return mPimpl->mCscFunctionString;
}

void GeneratorProfile::setCscFunctionString(const std::string &cscFunctionString)
{
    if (mPimpl->mCscFunctionString != cscFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCscFunctionString = cscFunctionString;
}

std::string GeneratorProfile::cotFunctionString() const
{
    return mPimpl->mCotFunctionString;
}

void GeneratorProfile::setCotFunctionString(const std::string &cotFunctionString)
{
    if (mPimpl->mCotFunctionString != cotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCotFunctionString = cotFunctionString;
}

std::string GeneratorProfile::sechFunctionString() const
{
    return mPimpl->mSechFunctionString;
}

void GeneratorProfile::setSechFunctionString(const std::string &sechFunctionString)
{
    if (mPimpl->mSechFunctionString != sechFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mSechFunctionString = sechFunctionString;
}

std::string GeneratorProfile::cschFunctionString() const
{
    return mPimpl->mCschFunctionString;
}

void GeneratorProfile::setCschFunctionString(const std::string &cschFunctionString)
{
    if (mPimpl->mCschFunctionString != cschFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCschFunctionString = cschFunctionString;
}

std::string GeneratorProfile::cothFunctionString() const
{
    return mPimpl->mCothFunctionString;
}

void GeneratorProfile::setCothFunctionString(const std::string &cothFunctionString)
{
    if (mPimpl->mCothFunctionString != cothFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCothFunctionString = cothFunctionString;
}

std::string GeneratorProfile::asecFunctionString() const
{
    return mPimpl->mAsecFunctionString;
}

void GeneratorProfile::setAsecFunctionString(const std::string &asecFunctionString)
{
    if (mPimpl->mAsecFunctionString != asecFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAsecFunctionString = asecFunctionString;
}

std::string GeneratorProfile::acscFunctionString() const
{
    return mPimpl->mAcscFunctionString;
}

void GeneratorProfile::setAcscFunctionString(const std::string &acscFunctionString)
{
    if (mPimpl->mAcscFunctionString != acscFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcscFunctionString = acscFunctionString;
}

std::string GeneratorProfile::acotFunctionString() const
{
    return mPimpl->mAcotFunctionString;
}

void GeneratorProfile::setAcotFunctionString(const std::string &acotFunctionString)
{
    if (mPimpl->mAcotFunctionString != acotFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcotFunctionString = acotFunctionString;
}

std::string GeneratorProfile::asechFunctionString() const
{
    return mPimpl->mAsechFunctionString;
}

void GeneratorProfile::setAsechFunctionString(const std::string &asechFunctionString)
{
    if (mPimpl->mAsechFunctionString != asechFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAsechFunctionString = asechFunctionString;
}

std::string GeneratorProfile::acschFunctionString() const
{
    return mPimpl->mAcschFunctionString;
}

void GeneratorProfile::setAcschFunctionString(const std::string &acschFunctionString)
{
    if (mPimpl->mAcschFunctionString != acschFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcschFunctionString = acschFunctionString;
}

std::string GeneratorProfile::acothFunctionString() const
{
    return mPimpl->mAcothFunctionString;
}

void GeneratorProfile::setAcothFunctionString(const std::string &acothFunctionString)
{
    if (mPimpl->mAcothFunctionString != acothFunctionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mAcothFunctionString = acothFunctionString;
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

std::string GeneratorProfile::libcellmlVersionString() const
{
    return mPimpl->mLibcellmlVersionString;
}

void GeneratorProfile::setLibcellmlVersionString(const std::string &libcellmlVersionString)
{
    if (mPimpl->mLibcellmlVersionString != libcellmlVersionString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mLibcellmlVersionString = libcellmlVersionString;
}

std::string GeneratorProfile::stateCountString() const
{
    return mPimpl->mStateCountString;
}

void GeneratorProfile::setStateCountString(const std::string &stateCountString)
{
    if (mPimpl->mStateCountString != stateCountString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mStateCountString = stateCountString;
}

std::string GeneratorProfile::variableCountString() const
{
    return mPimpl->mVariableCountString;
}

void GeneratorProfile::setVariableCountString(const std::string &variableCountString)
{
    if (mPimpl->mVariableCountString != variableCountString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableCountString = variableCountString;
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

std::string GeneratorProfile::voiInfoString() const
{
    return mPimpl->mVoiInfoString;
}

void GeneratorProfile::setVoiInfoString(const std::string &voiInfoString)
{
    if (mPimpl->mVoiInfoString != voiInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVoiInfoString = voiInfoString;
}

std::string GeneratorProfile::stateInfoString() const
{
    return mPimpl->mStateInfoString;
}

void GeneratorProfile::setStateInfoString(const std::string &stateInfoString)
{
    if (mPimpl->mStateInfoString != stateInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mStateInfoString = stateInfoString;
}

std::string GeneratorProfile::variableInfoString() const
{
    return mPimpl->mVariableInfoString;
}

void GeneratorProfile::setVariableInfoString(const std::string &variableInfoString)
{
    if (mPimpl->mVariableInfoString != variableInfoString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mVariableInfoString = variableInfoString;
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

std::string GeneratorProfile::createStatesArrayMethodString() const
{
    return mPimpl->mCreateStatesArrayMethodString;
}

void GeneratorProfile::setCreateStatesArrayMethodString(const std::string &createStatesArrayMethodString)
{
    if (mPimpl->mCreateStatesArrayMethodString != createStatesArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCreateStatesArrayMethodString = createStatesArrayMethodString;
}

std::string GeneratorProfile::createVariablesArrayMethodString() const
{
    return mPimpl->mCreateVariablesArrayMethodString;
}

void GeneratorProfile::setCreateVariablesArrayMethodString(const std::string &createVariablesArrayMethodString)
{
    if (mPimpl->mCreateVariablesArrayMethodString != createVariablesArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mCreateVariablesArrayMethodString = createVariablesArrayMethodString;
}

std::string GeneratorProfile::deleteArrayMethodString() const
{
    return mPimpl->mDeleteArrayMethodString;
}

void GeneratorProfile::setDeleteArrayMethodString(const std::string &deleteArrayMethodString)
{
    if (mPimpl->mDeleteArrayMethodString != deleteArrayMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mDeleteArrayMethodString = deleteArrayMethodString;
}

std::string GeneratorProfile::initializeStatesAndConstantsMethodString() const
{
    return mPimpl->mInitializeStatesAndConstantsMethodString;
}

void GeneratorProfile::setInitializeStatesAndConstantsMethodString(const std::string &initializeStatesAndConstantsMethodString)
{
    if (mPimpl->mInitializeStatesAndConstantsMethodString != initializeStatesAndConstantsMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mInitializeStatesAndConstantsMethodString = initializeStatesAndConstantsMethodString;
}

std::string GeneratorProfile::computeComputedConstantsMethodString() const
{
    return mPimpl->mComputeComputedConstantsMethodString;
}

void GeneratorProfile::setComputeComputedConstantsMethodString(const std::string &computeComputedConstantsMethodString)
{
    if (mPimpl->mComputeComputedConstantsMethodString != computeComputedConstantsMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mComputeComputedConstantsMethodString = computeComputedConstantsMethodString;
}

std::string GeneratorProfile::computeRatesMethodString() const
{
    return mPimpl->mComputeRatesMethodString;
}

void GeneratorProfile::setComputeRatesMethodString(const std::string &computeRatesMethodString)
{
    if (mPimpl->mComputeRatesMethodString != computeRatesMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mComputeRatesMethodString = computeRatesMethodString;
}

std::string GeneratorProfile::computeVariablesMethodString() const
{
    return mPimpl->mComputeVariablesMethodString;
}

void GeneratorProfile::setComputeVariablesMethodString(const std::string &computeVariablesMethodString)
{
    if (mPimpl->mComputeVariablesMethodString != computeVariablesMethodString) {
        mPimpl->mProfile = Profile::CUSTOM;
    }

    mPimpl->mComputeVariablesMethodString = computeVariablesMethodString;
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
