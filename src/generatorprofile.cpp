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
    // Relational and logical operators

    std::string mEqString;
    std::string mEqEqString;
    std::string mNeqString;
    std::string mLtString;
    std::string mLeqString;
    std::string mGtString;
    std::string mGeqString;
    std::string mAndString;
    std::string mOrString;
    std::string mXorString;
    std::string mNotString;

    bool mHasEqEqOperator = true;
    bool mHasNeqOperator = true;
    bool mHasLtOperator = true;
    bool mHasLeqOperator = true;
    bool mHasGtOperator = true;
    bool mHasGeqOperator = true;
    bool mHasAndOperator = true;
    bool mHasOrOperator = true;
    bool mHasXorOperator = true;
    bool mHasNotOperator = true;

    // Arithmetic operators

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

    // Trigonometric operators

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

    // Piecewise statement

    std::string mConditionalOperatorIfString;
    std::string mConditionalOperatorElseString;
    std::string mPiecewiseIfString;
    std::string mPiecewiseElseString;

    bool mHasConditionalOperator = true;

    // Constants

    std::string mTrueString;
    std::string mFalseString;
    std::string mEString;
    std::string mPiString;
    std::string mInfString;
    std::string mNanString;

    // Mathematical functions

    std::string mEqEqFunctionString;
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

    // Miscellaneous

    std::string mFreeVectorFunctionString;
    std::string mHeaderString;

    std::string mVariableOfIntegrationString;

    std::string mStatesArrayString;
    std::string mRatesArrayString;
    std::string mVariablesArrayString;

    std::string mBeginCreateStatesMethodString;
    std::string mEndCreateStatesMethodString;

    std::string mBeginCreateVariablesMethodString;
    std::string mEndCreateVariablesMethodString;

    std::string mBeginInitializeConstantsMethodString;
    std::string mEndInitializeConstantsMethodString;

    std::string mBeginComputeComputedConstantsMethodString;
    std::string mEndComputeComputedConstantsMethodString;

    std::string mBeginComputeRatesMethodString;
    std::string mEndComputeRatesMethodString;

    std::string mBeginComputeVariablesMethodString;
    std::string mEndComputeVariablesMethodString;

    std::string mBeginCommentString;
    std::string mEndCommentString;

    std::string mEmptyMethodString;
    std::string mTemplateReplacementString;
    std::string mTemplateReturnCreatedArrayString;
    std::string mTemplateStateVectorSizeConstantString;
    std::string mTemplateVariableVectorSizeConstantString;
    std::string mTemplateVoiConstantString;
    std::string mTemplateVersionString;
    std::string mTemplateOriginCommentString;

    std::string mTemplateVariableInformationObjectString;
    std::string mTemplateVariableInformationEntryString;
    std::string mBeginStateVectorInformationArrayString;
    std::string mEndStateVectorInformationArrayString;
    std::string mBeginVariableVectorInformationArrayString;
    std::string mEndVariableVectorInformationArrayString;

    std::string mIndentString;

    std::string mOpenArrayString;
    std::string mCloseArrayString;

    std::string mArrayElementSeparatorString;
    std::string mCommandSeparatorString;

    void loadProfile(GeneratorProfile::Profile profile);
};

void GeneratorProfile::GeneratorProfileImpl::loadProfile(GeneratorProfile::Profile profile)
{
    switch (profile) {
    case GeneratorProfile::Profile::C:
        // Relational and logical operators

        mEqString = " = ";
        mEqEqString = " == ";
        mNeqString = " != ";
        mLtString = " < ";
        mLeqString = " <= ";
        mGtString = " > ";
        mGeqString = " >= ";
        mAndString = " && ";
        mOrString = " || ";
        mXorString = "xor";
        mNotString = "!";

        mHasEqEqOperator = true;
        mHasNeqOperator = true;
        mHasLtOperator = true;
        mHasLeqOperator = true;
        mHasGtOperator = true;
        mHasGeqOperator = true;
        mHasAndOperator = true;
        mHasOrOperator = true;
        mHasXorOperator = false;
        mHasNotOperator = true;

        // Arithmetic operators

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

        // Trigonometric operators

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

        // Piecewise statement

        mConditionalOperatorIfString = "(#cond)?#if";
        mConditionalOperatorElseString = ":#else";

        mHasConditionalOperator = true;

        // Constants

        mTrueString = "1.0";
        mFalseString = "0.0";
        mEString = convertDoubleToString(exp(1.0));
        mPiString = convertDoubleToString(M_PI);
        mInfString = "1.0/0.0";
        mNanString = "sqrt(-1.0)";

        // Mathematical functions

        mEqEqFunctionString = "";
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

        // Miscellaneous

        mFreeVectorFunctionString = "void freeVector(double *array)\n"
                                    "{\n"
                                    "   free(array);\n"
                                    "}\n";

        mHeaderString = "#include <math.h>\n#include <stddef.h>\n#include <stdlib.h>\n";

        mVariableOfIntegrationString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mBeginCreateStatesMethodString = "double * createStates()\n{\n";
        mEndCreateStatesMethodString = "}\n";

        mBeginCreateVariablesMethodString = "double * createVariables()\n{\n";
        mEndCreateVariablesMethodString = "}\n";

        mBeginInitializeConstantsMethodString = "void initializeConstants(double *states, double *variables)\n{\n";
        mEndInitializeConstantsMethodString = "}\n";

        mBeginComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables)\n{\n";
        mEndComputeComputedConstantsMethodString = "}\n";

        mBeginComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables)\n{\n";
        mEndComputeRatesMethodString = "}\n";

        mBeginComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables)\n{\n";
        mEndComputeVariablesMethodString = "}\n";

        mEmptyMethodString = "";

        mBeginStateVectorInformationArrayString = "const struct VariableInfo STATE_VECTOR_INFORMATION_ARRAY[] = {\n";
        mEndStateVectorInformationArrayString = "};\n";
        mBeginVariableVectorInformationArrayString = "const struct VariableInfo VARIABLE_VECTOR_INFORMATION_ARRAY[] = {\n";
        mEndVariableVectorInformationArrayString = "};\n";

        mIndentString = "    ";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mArrayElementSeparatorString = ",";
        mCommandSeparatorString = ";";

        mBeginCommentString = "/* ";
        mEndCommentString = " */\n";

        // Templated

        mTemplateReplacementString = "VALUE";

        mTemplateReturnCreatedArrayString = "return (double *) malloc(VALUE * sizeof(double));\n";
        mTemplateStateVectorSizeConstantString = "const size_t STATE_VECTOR_SIZE = VALUE;\n";
        mTemplateVariableVectorSizeConstantString = "const size_t VARIABLE_VECTOR_SIZE = VALUE;\n";
        mTemplateVoiConstantString = "const struct VariableInfo VOI_INFORMATION = {\"VALUE\", \"VALUE\", \"VALUE\"};\n";
        mTemplateVersionString = "const char VERSION[] = \"VALUE\";\n";
        mTemplateOriginCommentString = "The contents of this file was generated from version VALUE of libCellML.";
        mTemplateVariableInformationObjectString = "struct VariableInfo {\n"
                                                   "    char component[VALUE];\n"
                                                   "    char name[VALUE];\n"
                                                   "    char units[VALUE];\n"
                                                   "};\n";
        mTemplateVariableInformationEntryString = "{\"VALUE\", \"VALUE\", \"VALUE\"}";

        break;
    case GeneratorProfile::Profile::PYTHON:
        // Relational and logical operators

        mEqString = " = ";
        mEqEqString = "eq_eq_func";
        mNeqString = "neq_func";
        mLtString = "lt_func";
        mLeqString = "leq_func";
        mGtString = "gt_func";
        mGeqString = "geq_func";
        mAndString = "and_func";
        mOrString = "or_func";
        mXorString = "xor_func";
        mNotString = "not_func";

        mHasEqEqOperator = false;
        mHasNeqOperator = false;
        mHasLtOperator = false;
        mHasLeqOperator = false;
        mHasGtOperator = false;
        mHasGeqOperator = false;
        mHasAndOperator = false;
        mHasOrOperator = false;
        mHasXorOperator = false;
        mHasNotOperator = false;

        // Arithmetic operators

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

        // Trigonometric operators

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

        // Piecewise statement

        mConditionalOperatorIfString = "#if if #cond";
        mConditionalOperatorElseString = " else #else";

        mHasConditionalOperator = true;

        // Constants

        mTrueString = "1.0";
        mFalseString = "0.0";
        mEString = convertDoubleToString(exp(1.0));
        mPiString = convertDoubleToString(M_PI);
        mInfString = "inf";
        mNanString = "nan";

        // Mathematical functions

        mEqEqFunctionString = "def eq_eq_func(x, y):\n"
                              "    return 1.0 if x == y else 0.0\n\n";
        mNeqFunctionString = "def neq_func(x, y):\n"
                             "    return 1.0 if x != y else 0.0\n\n";
        mLtFunctionString = "def lt_func(x, y):\n"
                            "    return 1.0 if x < y else 0.0\n\n";
        mLeqFunctionString = "def leq_func(x, y):\n"
                             "    return 1.0 if x <= y else 0.0\n\n";
        mGtFunctionString = "def gt_func(x, y):\n"
                            "    return 1.0 if x > y else 0.0\n\n";
        mGeqFunctionString = "def geq_func(x, y):\n"
                             "    return 1.0 if x >= y else 0.0\n\n";
        mAndFunctionString = "def and_func(x, y):\n"
                             "    return 1.0 if bool(x) & bool(y) else 0.0\n\n";
        mOrFunctionString = "def or_func(x, y):\n"
                            "    return 1.0 if bool(x) | bool(y) else 0.0\n\n";
        mXorFunctionString = "def xor_func(x, y):\n"
                             "    return 1.0 if bool(x) ^ bool(y) else 0.0\n\n";
        mNotFunctionString = "def not_func(x):\n"
                             "    return 1.0 if not bool(x) else 0.0\n\n";

        mMinFunctionString = "def min(x, y):\n"
                             "    return x if x < y else y\n\n";
        mMaxFunctionString = "def max(x, y):\n"
                             "    return x if x > y else y\n\n";

        mSecFunctionString = "def sec(x):\n"
                             "    return 1.0/cos(x)\n\n";
        mCscFunctionString = "def csc(x):\n"
                             "    return 1.0/sin(x)\n\n";
        mCotFunctionString = "def cot(x):\n"
                             "    return 1.0/tan(x)\n\n";
        mSechFunctionString = "def sech(x):\n"
                              "    return 1.0/cosh(x)\n\n";
        mCschFunctionString = "def csch(x):\n"
                              "    return 1.0/sinh(x)\n\n";
        mCothFunctionString = "def coth(x):\n"
                              "    return 1.0/tanh(x)\n\n";
        mAsecFunctionString = "def asec(x):\n"
                              "    return acos(1.0/x)\n\n";
        mAcscFunctionString = "def acsc(x):\n"
                              "    return asin(1.0/x)\n\n";
        mAcotFunctionString = "def acot(x):\n"
                              "    return atan(1.0/x)\n\n";
        mAsechFunctionString = "def asech(x):\n"
                               "    one_over_x = 1.0/x\n"
                               "\n"
                               "    return log(one_over_x+sqrt(one_over_x*one_over_x-1.0))\n\n";
        mAcschFunctionString = "def acsch(x):\n"
                               "    one_over_x = 1.0/x\n"
                               "\n"
                               "    return log(one_over_x+sqrt(one_over_x*one_over_x+1.0))\n\n";
        mAcothFunctionString = "def acoth(x):\n"
                               "    one_over_x = 1.0/x\n"
                               "\n"
                               "    return 0.5*log((1.0+one_over_x)/(1.0-one_over_x))\n\n";

        // Miscellaneous

        mFreeVectorFunctionString = "";
        mHeaderString = "from math import *\n\n";

        mVariableOfIntegrationString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mBeginCreateStatesMethodString = "def create_states():\n";
        mEndCreateStatesMethodString = "\n";

        mBeginCreateVariablesMethodString = "def create_variables():\n";
        mEndCreateVariablesMethodString = "\n";

        mBeginInitializeConstantsMethodString = "def initialize_constants(states, variables):\n";
        mEndInitializeConstantsMethodString = "\n";

        mBeginComputeComputedConstantsMethodString = "def compute_computed_constants(variables):\n";
        mEndComputeComputedConstantsMethodString = "\n";

        mBeginComputeRatesMethodString = "def compute_rates(voi, states, rates, variables):\n";
        mEndComputeRatesMethodString = "\n";

        mBeginComputeVariablesMethodString = "def compute_variables(voi, states, rates, variables):\n";
        mEndComputeVariablesMethodString = "";

        mEmptyMethodString = "pass\n";

        mBeginStateVectorInformationArrayString = "STATE_VECTOR_INFORMATION_ARRAY = [\n";
        mEndStateVectorInformationArrayString = "]\n";
        mBeginVariableVectorInformationArrayString = "VARIABLE_VECTOR_INFORMATION_ARRAY = [\n";
        mEndVariableVectorInformationArrayString = "]\n\n";

        mIndentString = "    ";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mArrayElementSeparatorString = ",";
        mCommandSeparatorString = "";

        mBeginCommentString = "# ";
        mEndCommentString = "\n";

        // Templated

        mTemplateReplacementString = "VALUE";

        mTemplateReturnCreatedArrayString = "return [nan]*VALUE\n";
        mTemplateStateVectorSizeConstantString = "STATE_VECTOR_SIZE = VALUE\n";
        mTemplateVariableVectorSizeConstantString = "VARIABLE_VECTOR_SIZE = VALUE\n";
        mTemplateVoiConstantString = "VOI_INFORMATION = {\"component\": \"VALUE\", \"name\": \"VALUE\", \"units\": \"VALUE\"}\n";
        mTemplateVersionString = "__version__ = \"VALUE\"\n";
        mTemplateOriginCommentString = "The contents of this file was generated from version VALUE of libCellML.";
        mTemplateVariableInformationObjectString = "";
        mTemplateVariableInformationEntryString = "{\"component\": \"VALUE\", \"name\": \"VALUE\", \"units\": \"VALUE\"}";

        break;
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
    // Relational and logical operators

    mPimpl->mEqString = rhs.mPimpl->mEqString;
    mPimpl->mEqEqString = rhs.mPimpl->mEqEqString;
    mPimpl->mNeqString = rhs.mPimpl->mNeqString;
    mPimpl->mLtString = rhs.mPimpl->mLtString;
    mPimpl->mLeqString = rhs.mPimpl->mLeqString;
    mPimpl->mGtString = rhs.mPimpl->mGtString;
    mPimpl->mGeqString = rhs.mPimpl->mGeqString;
    mPimpl->mAndString = rhs.mPimpl->mAndString;
    mPimpl->mOrString = rhs.mPimpl->mOrString;
    mPimpl->mXorString = rhs.mPimpl->mXorString;
    mPimpl->mNotString = rhs.mPimpl->mNotString;

    mPimpl->mHasXorOperator = rhs.mPimpl->mHasXorOperator;
    mPimpl->mHasNotOperator = rhs.mPimpl->mHasNotOperator;

    // Arithmetic operators

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

    // Trigonometric operators

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

    // Piecewise statement

    mPimpl->mConditionalOperatorIfString = rhs.mPimpl->mConditionalOperatorIfString;
    mPimpl->mConditionalOperatorElseString = rhs.mPimpl->mConditionalOperatorElseString;
    mPimpl->mPiecewiseIfString = rhs.mPimpl->mPiecewiseIfString;
    mPimpl->mPiecewiseElseString = rhs.mPimpl->mPiecewiseElseString;

    mPimpl->mHasConditionalOperator = rhs.mPimpl->mHasConditionalOperator;

    // Constants

    mPimpl->mTrueString = rhs.mPimpl->mTrueString;
    mPimpl->mFalseString = rhs.mPimpl->mFalseString;
    mPimpl->mEString = rhs.mPimpl->mEString;
    mPimpl->mPiString = rhs.mPimpl->mPiString;
    mPimpl->mInfString = rhs.mPimpl->mInfString;
    mPimpl->mNanString = rhs.mPimpl->mNanString;

    // Mathematical functions

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

    // Miscellaneous

    mPimpl->mFreeVectorFunctionString = rhs.mPimpl->mFreeVectorFunctionString;
    mPimpl->mHeaderString = rhs.mPimpl->mHeaderString;

    mPimpl->mVariableOfIntegrationString = rhs.mPimpl->mVariableOfIntegrationString;

    mPimpl->mStatesArrayString = rhs.mPimpl->mStatesArrayString;
    mPimpl->mRatesArrayString = rhs.mPimpl->mRatesArrayString;
    mPimpl->mVariablesArrayString = rhs.mPimpl->mVariablesArrayString;

    mPimpl->mBeginCreateStatesMethodString = rhs.mPimpl->mBeginCreateStatesMethodString;
    mPimpl->mEndCreateStatesMethodString = rhs.mPimpl->mEndCreateStatesMethodString;

    mPimpl->mBeginCreateVariablesMethodString = rhs.mPimpl->mBeginCreateVariablesMethodString;
    mPimpl->mEndCreateVariablesMethodString = rhs.mPimpl->mEndCreateVariablesMethodString;

    mPimpl->mBeginInitializeConstantsMethodString = rhs.mPimpl->mBeginInitializeConstantsMethodString;
    mPimpl->mEndInitializeConstantsMethodString = rhs.mPimpl->mEndInitializeConstantsMethodString;

    mPimpl->mBeginComputeComputedConstantsMethodString = rhs.mPimpl->mBeginComputeComputedConstantsMethodString;
    mPimpl->mEndComputeComputedConstantsMethodString = rhs.mPimpl->mEndComputeComputedConstantsMethodString;

    mPimpl->mBeginComputeRatesMethodString = rhs.mPimpl->mBeginComputeRatesMethodString;
    mPimpl->mEndComputeRatesMethodString = rhs.mPimpl->mEndComputeRatesMethodString;

    mPimpl->mBeginComputeVariablesMethodString = rhs.mPimpl->mBeginComputeVariablesMethodString;
    mPimpl->mEndComputeVariablesMethodString = rhs.mPimpl->mEndComputeVariablesMethodString;
    mPimpl->mTemplateStateVectorSizeConstantString = rhs.mPimpl->mTemplateStateVectorSizeConstantString;
    mPimpl->mTemplateVariableVectorSizeConstantString = rhs.mPimpl->mTemplateVariableVectorSizeConstantString;
    mPimpl->mTemplateVoiConstantString = rhs.mPimpl->mTemplateVoiConstantString;
    mPimpl->mTemplateVersionString = rhs.mPimpl->mTemplateVersionString;

    mPimpl->mEmptyMethodString = rhs.mPimpl->mEmptyMethodString;
    mPimpl->mTemplateReplacementString = rhs.mPimpl->mTemplateReplacementString;
    mPimpl->mTemplateReturnCreatedArrayString = rhs.mPimpl->mTemplateReturnCreatedArrayString;

    mPimpl->mTemplateVariableInformationObjectString = rhs.mPimpl->mTemplateVariableInformationObjectString;
    mPimpl->mTemplateVariableInformationEntryString = rhs.mPimpl->mTemplateVariableInformationEntryString;
    mPimpl->mBeginStateVectorInformationArrayString = rhs.mPimpl->mBeginStateVectorInformationArrayString;
    mPimpl->mEndStateVectorInformationArrayString = rhs.mPimpl->mEndStateVectorInformationArrayString;
    mPimpl->mBeginVariableVectorInformationArrayString = rhs.mPimpl->mBeginVariableVectorInformationArrayString;
    mPimpl->mEndVariableVectorInformationArrayString = rhs.mPimpl->mEndVariableVectorInformationArrayString;

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

void GeneratorProfile::setProfile(Profile profile)
{
    mPimpl->loadProfile(profile);
}

std::string GeneratorProfile::eqString() const
{
    return mPimpl->mEqString;
}

void GeneratorProfile::setEqString(const std::string &eqString)
{
    mPimpl->mEqString = eqString;
}

std::string GeneratorProfile::eqEqString() const
{
    return mPimpl->mEqEqString;
}

void GeneratorProfile::setEqEqString(const std::string &eqEqString)
{
    mPimpl->mEqEqString = eqEqString;
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

bool GeneratorProfile::hasEqEqOperator() const
{
    return mPimpl->mHasEqEqOperator;
}

void GeneratorProfile::setHasEqEqOperator(bool hasEqEqOperator)
{
    mPimpl->mHasEqEqOperator = hasEqEqOperator;
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

std::string GeneratorProfile::napierianLogarithmString() const
{
    return mPimpl->mNapierianLogarithmString;
}

void GeneratorProfile::setNapierianLogarithmString(const std::string &napierianLogarithmString)
{
    mPimpl->mNapierianLogarithmString = napierianLogarithmString;
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

std::string GeneratorProfile::eqEqFunctionString() const
{
    return mPimpl->mEqEqFunctionString;
}

void GeneratorProfile::setEqEqFunctionString(const std::string &eqEqFunctionString)
{
    mPimpl->mEqEqFunctionString = eqEqFunctionString;
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

std::string GeneratorProfile::freeVectorFunctionString() const
{
    return mPimpl->mFreeVectorFunctionString;
}

void GeneratorProfile::setFreeVectorFunctionString(const std::string &freeVectorFunctionString)
{
    mPimpl->mFreeVectorFunctionString = freeVectorFunctionString;
}

std::string GeneratorProfile::headerString() const
{
    return mPimpl->mHeaderString;
}

void GeneratorProfile::setHeaderString(const std::string &headerString)
{
    mPimpl->mHeaderString = headerString;
}

std::string GeneratorProfile::variableOfIntegrationString() const
{
    return mPimpl->mVariableOfIntegrationString;
}

void GeneratorProfile::setVariableOfIntegrationString(const std::string &variableOfIntegrationString)
{
    mPimpl->mVariableOfIntegrationString = variableOfIntegrationString;
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

std::string GeneratorProfile::beginInitializeConstantsMethodString() const
{
    return mPimpl->mBeginInitializeConstantsMethodString;
}

std::string GeneratorProfile::beginCreateStatesMethodString() const
{
    return mPimpl->mBeginCreateStatesMethodString;
}

void GeneratorProfile::setBeginCreateStatesMethodString(const std::string &beginCreateStatesMethodString)
{
    mPimpl->mBeginCreateStatesMethodString = beginCreateStatesMethodString;
}

std::string GeneratorProfile::endCreateStatesMethodString() const
{
    return mPimpl->mEndCreateStatesMethodString;
}

void GeneratorProfile::setEndCreateStatesMethodString(const std::string &endCreateStatesMethodString)
{
    mPimpl->mEndCreateStatesMethodString = endCreateStatesMethodString;
}

std::string GeneratorProfile::beginCreateVariablesMethodString() const
{
    return mPimpl->mBeginCreateVariablesMethodString;
}

void GeneratorProfile::setBeginCreateVariablesMethodString(const std::string &beginCreateVariablesMethodString)
{
    mPimpl->mBeginCreateVariablesMethodString = beginCreateVariablesMethodString;
}

std::string GeneratorProfile::endCreateVariablesMethodString() const
{
    return mPimpl->mEndCreateVariablesMethodString;
}

void GeneratorProfile::setEndCreateVariablesMethodString(const std::string &endCreateVariablesMethodString)
{
    mPimpl->mEndCreateVariablesMethodString = endCreateVariablesMethodString;
}

void GeneratorProfile::setBeginInitializeConstantsMethodString(const std::string &beginInitializeConstantsMethodString)
{
    mPimpl->mBeginInitializeConstantsMethodString = beginInitializeConstantsMethodString;
}

std::string GeneratorProfile::endInitializeConstantsMethodString() const
{
    return mPimpl->mEndInitializeConstantsMethodString;
}

void GeneratorProfile::setEndInitializeConstantsMethodString(const std::string &endInitializeConstantsMethodString)
{
    mPimpl->mEndInitializeConstantsMethodString = endInitializeConstantsMethodString;
}

std::string GeneratorProfile::beginComputeComputedConstantsMethodString() const
{
    return mPimpl->mBeginComputeComputedConstantsMethodString;
}

void GeneratorProfile::setBeginComputeComputedConstantsMethodString(const std::string &beginComputeComputedConstantsMethodString)
{
    mPimpl->mBeginComputeComputedConstantsMethodString = beginComputeComputedConstantsMethodString;
}

std::string GeneratorProfile::endComputeComputedConstantsMethodString() const
{
    return mPimpl->mEndComputeComputedConstantsMethodString;
}

void GeneratorProfile::setEndComputeComputedConstantsMethodString(const std::string &endComputeComputedConstantsMethodString)
{
    mPimpl->mEndComputeComputedConstantsMethodString = endComputeComputedConstantsMethodString;
}

std::string GeneratorProfile::beginComputeRatesMethodString() const
{
    return mPimpl->mBeginComputeRatesMethodString;
}

void GeneratorProfile::setBeginComputeRatesMethodString(const std::string &beginComputeRatesMethodString)
{
    mPimpl->mBeginComputeRatesMethodString = beginComputeRatesMethodString;
}

std::string GeneratorProfile::endComputeRatesMethodString() const
{
    return mPimpl->mEndComputeRatesMethodString;
}

void GeneratorProfile::setEndComputeRatesMethodString(const std::string &endComputeRatesMethodString)
{
    mPimpl->mEndComputeRatesMethodString = endComputeRatesMethodString;
}

std::string GeneratorProfile::beginComputeVariablesMethodString() const
{
    return mPimpl->mBeginComputeVariablesMethodString;
}

void GeneratorProfile::setBeginComputeVariablesMethodString(const std::string &beginComputeVariablesMethodString)
{
    mPimpl->mBeginComputeVariablesMethodString = beginComputeVariablesMethodString;
}

std::string GeneratorProfile::endComputeVariablesMethodString() const
{
    return mPimpl->mEndComputeVariablesMethodString;
}

void GeneratorProfile::setEndComputeVariablesMethodString(const std::string &endComputeVariablesMethodString)
{
    mPimpl->mEndComputeVariablesMethodString = endComputeVariablesMethodString;
}

std::string GeneratorProfile::emptyMethodString() const
{
    return mPimpl->mEmptyMethodString;
}

void GeneratorProfile::setEmptyMethodString(const std::string &emptyMethodString)
{
    mPimpl->mEmptyMethodString = emptyMethodString;
}

std::string GeneratorProfile::templateReplacementString() const
{
    return mPimpl->mTemplateReplacementString;
}

void GeneratorProfile::setTemplateReplacementString(const std::string &templateReplacementString)
{
    mPimpl->mTemplateReplacementString = templateReplacementString;
}

std::string GeneratorProfile::templateStateVectorSizeConstantString() const
{
    return mPimpl->mTemplateStateVectorSizeConstantString;
}

void GeneratorProfile::setTemplateStateVectorSizeConstantString(const std::string &templateStateVectorSizeConstantString)
{
    mPimpl->mTemplateStateVectorSizeConstantString = templateStateVectorSizeConstantString;
}

std::string GeneratorProfile::templateVariableVectorSizeConstantString() const
{
    return mPimpl->mTemplateVariableVectorSizeConstantString;
}

void GeneratorProfile::setTemplateVariableVectorSizeConstantString(const std::string &templateVariableVectorSizeConstantString)
{
    mPimpl->mTemplateVariableVectorSizeConstantString = templateVariableVectorSizeConstantString;
}

std::string GeneratorProfile::templateVoiConstantString() const
{
    return mPimpl->mTemplateVoiConstantString;
}

void GeneratorProfile::setTemplateVoiConstantString(const std::string &templateVoiConstantString)
{
    mPimpl->mTemplateVoiConstantString = templateVoiConstantString;
}

std::string GeneratorProfile::templateVersionString() const
{
    return mPimpl->mTemplateVersionString;
}

void GeneratorProfile::setTemplateVersionString(const std::string &templateVersionString)
{
    mPimpl->mTemplateVersionString = templateVersionString;
}

std::string GeneratorProfile::templateOriginCommentString() const
{
    return mPimpl->mTemplateOriginCommentString;
}

void GeneratorProfile::setTemplateOriginCommentString(const std::string &templateOriginCommentString)
{
    mPimpl->mTemplateOriginCommentString = templateOriginCommentString;
}

std::string GeneratorProfile::templateReturnCreatedArrayString() const
{
    return mPimpl->mTemplateReturnCreatedArrayString;
}

void GeneratorProfile::setTemplateReturnCreatedArrayString(const std::string &templateReturnCreatedArrayString)
{
    mPimpl->mTemplateReturnCreatedArrayString = templateReturnCreatedArrayString;
}

std::string GeneratorProfile::templateVariableInformationObjectString() const
{
    return mPimpl->mTemplateVariableInformationObjectString;
}

void GeneratorProfile::setTemplateVariableInformationObjectString(const std::string &templateVariableInformationObjectString)
{
    mPimpl->mTemplateVariableInformationObjectString = templateVariableInformationObjectString;
}

std::string GeneratorProfile::templateVariableInformationEntryString() const
{
    return mPimpl->mTemplateVariableInformationEntryString;
}

void GeneratorProfile::setTemplateVariableInformationEntryString(const std::string &templateVariableInformationEntryString)
{
    mPimpl->mTemplateVariableInformationEntryString = templateVariableInformationEntryString;
}

std::string GeneratorProfile::beginStateVectorInformationArrayString() const
{
    return mPimpl->mBeginStateVectorInformationArrayString;
}

void GeneratorProfile::setBeginStateVectorInformationArrayString(const std::string &beginStateVectorInformationArrayString)
{
    mPimpl->mBeginStateVectorInformationArrayString = beginStateVectorInformationArrayString;
}

std::string GeneratorProfile::endStateVectorInformationArrayString() const
{
    return mPimpl->mEndStateVectorInformationArrayString;
}

void GeneratorProfile::setEndStateVectorInformationArrayString(const std::string &endStateVectorInformationArrayString)
{
    mPimpl->mEndStateVectorInformationArrayString = endStateVectorInformationArrayString;
}

std::string GeneratorProfile::beginVariableVectorInformationArrayString() const
{
    return mPimpl->mBeginVariableVectorInformationArrayString;
}

void GeneratorProfile::setBeginVariableVectorInformationArrayString(const std::string &beginVariableVectorInformationArrayString)
{
    mPimpl->mBeginVariableVectorInformationArrayString = beginVariableVectorInformationArrayString;
}

std::string GeneratorProfile::endVariableVectorInformationArrayString() const
{
    return mPimpl->mEndVariableVectorInformationArrayString;
}

void GeneratorProfile::setEndVariableVectorInformationArrayString(const std::string &endVariableVectorInformationArrayString)
{
    mPimpl->mEndVariableVectorInformationArrayString = endVariableVectorInformationArrayString;
}

std::string GeneratorProfile::indentString() const
{
    return mPimpl->mIndentString;
}

void GeneratorProfile::setIndentString(const std::string &indentString)
{
    mPimpl->mIndentString = indentString;
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

std::string GeneratorProfile::commandSeparatorString() const
{
    return mPimpl->mCommandSeparatorString;
}

void GeneratorProfile::setCommandSeparatorString(const std::string &commandSeparatorString)
{
    mPimpl->mCommandSeparatorString = commandSeparatorString;
}

std::string GeneratorProfile::beginCommentString() const
{
    return mPimpl->mBeginCommentString;
}

void GeneratorProfile::setBeginCommentString(const std::string &beginCommentString)
{
    mPimpl->mBeginCommentString = beginCommentString;
}

std::string GeneratorProfile::endCommentString() const
{
    return mPimpl->mEndCommentString;
}

void GeneratorProfile::setEndCommentString(const std::string &endCommentString)
{
    mPimpl->mEndCommentString = endCommentString;
}

} // namespace libcellml
