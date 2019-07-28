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

    bool mHasXorOperator = true;

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

    std::string mHeaderString;

    std::string mVariableOfIntegrationString;

    std::string mStatesArrayString;
    std::string mRatesArrayString;
    std::string mVariablesArrayString;

    std::string mBeginInitializeConstantsMethodString;
    std::string mEndInitializeConstantsMethodString;

    std::string mBeginComputeComputedConstantsMethodString;
    std::string mEndComputeComputedConstantsMethodString;

    std::string mBeginComputeRatesMethodString;
    std::string mEndComputeRatesMethodString;

    std::string mBeginComputeVariablesMethodString;
    std::string mEndComputeVariablesMethodString;

    std::string mEmptyMethodString;

    std::string mIndentString;

    std::string mOpenArrayString;
    std::string mCloseArrayString;

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
        mXorString = "^";
        mNotString = "!";

        mHasXorOperator = true;

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
        // Note: the parentheses around #cond is not needed (because of precedence
        //       rules). It's just that it looks better/clearer to have them
        //       (somewhat subjective indeed).

        mConditionalOperatorIfString = "(#cond)?#if";
        mConditionalOperatorElseString = ":#else";

        mHasConditionalOperator = true;

        // Constants

        mTrueString = "true";
        mFalseString = "false";
        mEString = convertDoubleToString(exp(1.0));
        mPiString = convertDoubleToString(M_PI);
        mInfString = "1.0/0.0";
        mNanString = "sqrt(-1.0)";

        // Mathematical functions

        mMinFunctionString = "double min(double x, double y)\n"
                             "{\n"
                             "     return (x < y)?x:y;\n"
                             "}\n";
        mMaxFunctionString = "double max(double x, double y)\n"
                             "{\n"
                             "     return (x > y)?x:y;\n"
                             "}\n";

        mSecFunctionString = "double sec(double x)\n"
                             "{\n"
                             "     return 1.0/cos(x);\n"
                             "}\n";
        mCscFunctionString = "double csc(double x)\n"
                             "{\n"
                             "     return 1.0/sin(x);\n"
                             "}\n";
        mCotFunctionString = "double cot(double x)\n"
                             "{\n"
                             "     return 1.0/tan(x);\n"
                             "}\n";
        mSechFunctionString = "double sech(double x)\n"
                              "{\n"
                              "     return 1.0/cosh(x);\n"
                              "}\n";
        mCschFunctionString = "double csch(double x)\n"
                              "{\n"
                              "     return 1.0/sinh(x);\n"
                              "}\n";
        mCothFunctionString = "double coth(double x)\n"
                              "{\n"
                              "     return 1.0/tanh(x);\n"
                              "}\n";
        mAsecFunctionString = "double asec(double x)\n"
                              "{\n"
                              "     return acos(1.0/x);\n"
                              "}\n";
        mAcscFunctionString = "double acsc(double x)\n"
                              "{\n"
                              "     return asin(1.0/x);\n"
                              "}\n";
        mAcotFunctionString = "double acot(double x)\n"
                              "{\n"
                              "     return atan(1.0/x);\n"
                              "}\n";
        mAsechFunctionString = "double asech(double x)\n"
                               "{\n"
                               "     double oneOverX = 1.0/x;\n"
                               "\n"
                               "     return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));\n"
                               "}\n";
        mAcschFunctionString = "double acsch(double x)\n"
                               "{\n"
                               "     double oneOverX = 1.0/x;\n"
                               "\n"
                               "     return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));\n"
                               "}\n";
        mAcothFunctionString = "double acoth(double x)\n"
                               "{\n"
                               "     double oneOverX = 1.0/x;\n"
                               "\n"
                               "     return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));\n"
                               "}\n";

        // Miscellaneous

        mHeaderString = "#include <math.h>\n";

        mVariableOfIntegrationString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mBeginInitializeConstantsMethodString = "void initializeConstants(double *states, double *variables)\n{\n";
        mEndInitializeConstantsMethodString = "}\n";

        mBeginComputeComputedConstantsMethodString = "void computeComputedConstants(double *variables)\n{\n";
        mEndComputeComputedConstantsMethodString = "}\n";

        mBeginComputeRatesMethodString = "void computeRates(double voi, double *states, double *rates, double *variables)\n{\n";
        mEndComputeRatesMethodString = "}\n";

        mBeginComputeVariablesMethodString = "void computeVariables(double voi, double *states, double *rates, double *variables)\n{\n";
        mEndComputeVariablesMethodString = "}\n";

        mEmptyMethodString = "";

        mIndentString = "    ";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mCommandSeparatorString = ";";

        break;
    case GeneratorProfile::Profile::PYTHON:
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
        mXorString = "^";
        mNotString = "!";

        mHasXorOperator = true;

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
        // Note: the parentheses around #cond is not needed (because of precedence
        //       rules). It's just that it looks better/clearer to have them
        //       (somewhat subjective indeed).

        mConditionalOperatorIfString = "(#cond) if #if";
        mConditionalOperatorElseString = " else #else";

        mHasConditionalOperator = true;

        // Constants

        mTrueString = "true";
        mFalseString = "false";
        mEString = convertDoubleToString(exp(1.0));
        mPiString = convertDoubleToString(M_PI);
        mInfString = "1.0/0.0";
        mNanString = "sqrt(-1.0)";

        // Mathematical functions

        mMinFunctionString = "def min(x, y):\n"
                             "     return (x < y) if x else y\n";
        mMaxFunctionString = "def max(x, y):\n"
                             "     return (x > y) if x else y\n";

        mSecFunctionString = "def sec(x):\n"
                             "     return 1.0/cos(x)\n";
        mCscFunctionString = "def csc(x):\n"
                             "     return 1.0/sin(x)\n";
        mCotFunctionString = "def cot(x):\n"
                             "     return 1.0/tan(x)\n";
        mSechFunctionString = "def sech(x):\n"
                              "     return 1.0/cosh(x)\n";
        mCschFunctionString = "def csch(x):\n"
                              "     return 1.0/sinh(x)\n";
        mCothFunctionString = "def coth(x):\n"
                              "     return 1.0/tanh(x)\n";
        mAsecFunctionString = "def asec(x):\n"
                              "     return acos(1.0/x)\n";
        mAcscFunctionString = "def acsc(x):\n"
                              "     return asin(1.0/x)\n";
        mAcotFunctionString = "def acot(x):\n"
                              "     return atan(1.0/x)\n";
        mAsechFunctionString = "def asech(x):\n"
                               "     oneOverX = 1.0/x\n"
                               "\n"
                               "     return log(oneOverX+sqrt(oneOverX*oneOverX-1.0))\n";
        mAcschFunctionString = "def acsch(x):\n"
                               "     oneOverX = 1.0/x\n"
                               "\n"
                               "     return log(oneOverX+sqrt(oneOverX*oneOverX+1.0))\n";
        mAcothFunctionString = "def acoth(x):\n"
                               "     oneOverX = 1.0/x\n"
                               "\n"
                               "     return 0.5*log((1.0+oneOverX)/(1.0-oneOverX))\n";

        // Miscellaneous

        mHeaderString = "from math import *\n";

        mVariableOfIntegrationString = "voi";

        mStatesArrayString = "states";
        mRatesArrayString = "rates";
        mVariablesArrayString = "variables";

        mBeginInitializeConstantsMethodString = "def initializeConstants(states, variables):\n";
        mEndInitializeConstantsMethodString = "";

        mBeginComputeComputedConstantsMethodString = "def computeComputedConstants(variables):\n";
        mEndComputeComputedConstantsMethodString = "";

        mBeginComputeRatesMethodString = "def computeRates(voi, states, rates, variables):\n";
        mEndComputeRatesMethodString = "";

        mBeginComputeVariablesMethodString = "def computeVariables(voi, states, rates, variables):\n";
        mEndComputeVariablesMethodString = "";

        mEmptyMethodString = "pass\n";

        mIndentString = "    ";

        mOpenArrayString = "[";
        mCloseArrayString = "]";

        mCommandSeparatorString = "";

        break;
    }
}

GeneratorProfile::GeneratorProfile(Profile profile)
    : mPimpl(new GeneratorProfileImpl())
{
    loadProfile(profile);
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

    mPimpl->mHeaderString = rhs.mPimpl->mHeaderString;

    mPimpl->mVariableOfIntegrationString = rhs.mPimpl->mVariableOfIntegrationString;

    mPimpl->mStatesArrayString = rhs.mPimpl->mStatesArrayString;
    mPimpl->mRatesArrayString = rhs.mPimpl->mRatesArrayString;
    mPimpl->mVariablesArrayString = rhs.mPimpl->mVariablesArrayString;

    mPimpl->mBeginInitializeConstantsMethodString = rhs.mPimpl->mBeginInitializeConstantsMethodString;
    mPimpl->mEndInitializeConstantsMethodString = rhs.mPimpl->mEndInitializeConstantsMethodString;

    mPimpl->mBeginComputeComputedConstantsMethodString = rhs.mPimpl->mBeginComputeComputedConstantsMethodString;
    mPimpl->mEndComputeComputedConstantsMethodString = rhs.mPimpl->mEndComputeComputedConstantsMethodString;

    mPimpl->mBeginComputeRatesMethodString = rhs.mPimpl->mBeginComputeRatesMethodString;
    mPimpl->mEndComputeRatesMethodString = rhs.mPimpl->mEndComputeRatesMethodString;

    mPimpl->mBeginComputeVariablesMethodString = rhs.mPimpl->mBeginComputeVariablesMethodString;
    mPimpl->mEndComputeVariablesMethodString = rhs.mPimpl->mEndComputeVariablesMethodString;

    mPimpl->mEmptyMethodString = rhs.mPimpl->mEmptyMethodString;

    mPimpl->mIndentString = rhs.mPimpl->mIndentString;

    mPimpl->mOpenArrayString = rhs.mPimpl->mOpenArrayString;
    mPimpl->mCloseArrayString = rhs.mPimpl->mCloseArrayString;

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

void GeneratorProfile::loadProfile(Profile profile)
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

bool GeneratorProfile::hasXorOperator() const
{
    return mPimpl->mHasXorOperator;
}

void GeneratorProfile::setHasXorOperator(bool hasXorOperator)
{
    mPimpl->mHasXorOperator = hasXorOperator;
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

std::string GeneratorProfile::commandSeparatorString() const
{
    return mPimpl->mCommandSeparatorString;
}

void GeneratorProfile::setCommandSeparatorString(const std::string &commandSeparatorString)
{
    mPimpl->mCommandSeparatorString = commandSeparatorString;
}

} // namespace libcellml
