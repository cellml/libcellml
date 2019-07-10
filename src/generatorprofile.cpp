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

    std::string mEqString = " = ";
    std::string mEqEqString = " == ";
    std::string mNeqString = " != ";
    std::string mLtString = " < ";
    std::string mLeqString = " <= ";
    std::string mGtString = " > ";
    std::string mGeqString = " >= ";
    std::string mAndString = " && ";
    std::string mOrString = " || ";
    std::string mXorString = "^";
    std::string mNotString = "!";

    bool mHasXorOperator = true;


    // Arithmetic operators

    std::string mPlusString = "+";
    std::string mMinusString = "-";
    std::string mTimesString = "*";
    std::string mDivideString = "/";
    std::string mPowerString = "pow";
    std::string mSquareRootString = "sqrt";
    std::string mSquareString = "sqr";
    std::string mAbsoluteValueString = "fabs";
    std::string mExponentialString = "exp";
    std::string mNapierianLogarithmString = "log";
    std::string mCommonLogarithmString = "log10";
    std::string mCeilingString = "ceil";
    std::string mFloorString = "floor";

    bool mHasPowerOperator = false;

    // Min/max operators

    std::string mMinString = "min";
    std::string mMaxString = "max";

    // Trigonometric operators

    std::string mSinString = "sin";
    std::string mCosString = "cos";
    std::string mTanString = "tan";
    std::string mSecString = "sec";
    std::string mCscString = "csc";
    std::string mCotString = "cot";
    std::string mSinhString = "sinh";
    std::string mCoshString = "cosh";
    std::string mTanhString = "tanh";
    std::string mSechString = "sech";
    std::string mCschString = "csch";
    std::string mCothString = "coth";
    std::string mAsinString = "asin";
    std::string mAcosString = "acos";
    std::string mAtanString = "atan";
    std::string mAsecString = "asec";
    std::string mAcscString = "acsc";
    std::string mAcotString = "acot";
    std::string mAsinhString = "asinh";
    std::string mAcoshString = "acosh";
    std::string mAtanhString = "atanh";
    std::string mAsechString = "asech";
    std::string mAcschString = "acsch";
    std::string mAcothString = "acoth";

    // Extra operators

    std::string mRemString = "fmod";

    // Piecewise statement
    // Note: the parentheses around #cond is not needed (because of precedence
    //       rules). It's just that it looks better/clearer to have them
    //       (somewhat subjective indeed).

    std::string mConditionalOperatorIfString = "(#cond)?#if";
    std::string mConditionalOperatorElseString = ":#else";
    std::string mPiecewiseIfString = "piecewise(#cond, #if";
    std::string mPiecewiseElseString = ", #else)";

    bool mHasConditionalOperator = true;

    // Constants

    std::string mTrueString = "true";
    std::string mFalseString = "false";
    std::string mEString = convertDoubleToString(exp(1.0));
    std::string mPiString = convertDoubleToString(M_PI);
    std::string mInfString = "1.0/0.0";
    std::string mNanString = "sqrt(-1.0)";

    // "Special" mathematical functions

    std::string mMinFunctionString = "double min(double x, double y)\n"
                                     "{\n"
                                     "     return (x < y)?x:y;\n"
                                     "}\n";
    std::string mMaxFunctionString = "double max(double x, double y)\n"
                                     "{\n"
                                     "     return (x > y)?x:y;\n"
                                     "}\n";

    // Miscellaneous

    std::string mVariableOfIntegrationString = "voi";

    std::string mStatesArrayString = "states";
    std::string mRatesArrayString = "rates";
    std::string mVariablesArrayString = "variables";

    std::string mBeginInitializeModelMethodString = "void initializeModel(double *states, double *variables)\n{\n";
    std::string mEndInitializeModelMethodString = "}\n";

    std::string mBeginComputeConstantEquationsMethodString = "void computeConstantEquations(double *variables)\n{\n";
    std::string mEndComputeConstantEquationsMethodString = "}\n";

    std::string mBeginComputeRateEquationsMethodString = "void computeRateEquations(double voi, double *states, double *rates, double *variables)\n{\n";
    std::string mEndComputeRateEquationsMethodString = "}\n";

    std::string mBeginComputeAlgebraicEquationsMethodString = "void computeAlgebraicEquations(double voi, double *states, double *rates, double *variables)\n{\n";
    std::string mEndComputeAlgebraicEquationsMethodString = "}\n";

    std::string mIndentString = "    ";

    std::string mOpenArrayString = "[";
    std::string mCloseArrayString = "]";

    std::string mCommandSeparatorString = ";";
};

GeneratorProfile::GeneratorProfile()
    : mPimpl(new GeneratorProfileImpl())
{
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

    mPimpl->mHasPowerOperator = rhs.mPimpl->mHasPowerOperator;

    // Min/max operators

    mPimpl->mMinString = rhs.mPimpl->mMinString;
    mPimpl->mMaxString = rhs.mPimpl->mMaxString;

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

    // Extra operators

    mPimpl->mRemString = rhs.mPimpl->mRemString;

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

    // "Special" mathematical functions

    mPimpl->mMinFunctionString = rhs.mPimpl->mMinFunctionString;
    mPimpl->mMaxFunctionString = rhs.mPimpl->mMaxFunctionString;

    // Miscellaneous

    mPimpl->mVariableOfIntegrationString = rhs.mPimpl->mVariableOfIntegrationString;

    mPimpl->mStatesArrayString = rhs.mPimpl->mStatesArrayString;
    mPimpl->mRatesArrayString = rhs.mPimpl->mRatesArrayString;
    mPimpl->mVariablesArrayString = rhs.mPimpl->mVariablesArrayString;

    mPimpl->mBeginInitializeModelMethodString = rhs.mPimpl->mBeginInitializeModelMethodString;
    mPimpl->mEndInitializeModelMethodString = rhs.mPimpl->mEndInitializeModelMethodString;

    mPimpl->mBeginComputeConstantEquationsMethodString = rhs.mPimpl->mBeginComputeConstantEquationsMethodString;
    mPimpl->mEndComputeConstantEquationsMethodString = rhs.mPimpl->mEndComputeConstantEquationsMethodString;

    mPimpl->mBeginComputeRateEquationsMethodString = rhs.mPimpl->mBeginComputeRateEquationsMethodString;
    mPimpl->mEndComputeRateEquationsMethodString = rhs.mPimpl->mEndComputeRateEquationsMethodString;

    mPimpl->mBeginComputeAlgebraicEquationsMethodString = rhs.mPimpl->mBeginComputeAlgebraicEquationsMethodString;
    mPimpl->mEndComputeAlgebraicEquationsMethodString = rhs.mPimpl->mEndComputeAlgebraicEquationsMethodString;

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

bool GeneratorProfile::hasPowerOperator() const
{
    return mPimpl->mHasPowerOperator;
}

void GeneratorProfile::setHasPowerOperator(bool hasPowerOperator)
{
    mPimpl->mHasPowerOperator = hasPowerOperator;
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

std::string GeneratorProfile::remString() const
{
    return mPimpl->mRemString;
}

void GeneratorProfile::setRemString(const std::string &remString)
{
    mPimpl->mRemString = remString;
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

std::string GeneratorProfile::beginInitializeModelMethodString() const
{
    return mPimpl->mBeginInitializeModelMethodString;
}

void GeneratorProfile::setBeginInitializeModelMethodString(const std::string &beginInitializeModelMethodString)
{
    mPimpl->mBeginInitializeModelMethodString = beginInitializeModelMethodString;
}

std::string GeneratorProfile::endInitializeModelMethodString() const
{
    return mPimpl->mEndInitializeModelMethodString;
}

void GeneratorProfile::setEndInitializeModelMethodString(const std::string &endInitializeModelMethodString)
{
    mPimpl->mEndInitializeModelMethodString = endInitializeModelMethodString;
}

std::string GeneratorProfile::beginComputeConstantEquationsMethodString() const
{
    return mPimpl->mBeginComputeConstantEquationsMethodString;
}

void GeneratorProfile::setBeginComputeConstantEquationsMethodString(const std::string &beginComputeConstantEquationsMethodString)
{
    mPimpl->mBeginComputeConstantEquationsMethodString = beginComputeConstantEquationsMethodString;
}

std::string GeneratorProfile::endComputeConstantEquationsMethodString() const
{
    return mPimpl->mEndComputeConstantEquationsMethodString;
}

void GeneratorProfile::setEndComputeConstantEquationsMethodString(const std::string &endComputeConstantEquationsMethodString)
{
    mPimpl->mEndComputeConstantEquationsMethodString = endComputeConstantEquationsMethodString;
}

std::string GeneratorProfile::beginComputeRateEquationsMethodString() const
{
    return mPimpl->mBeginComputeRateEquationsMethodString;
}

void GeneratorProfile::setBeginComputeRateEquationsMethodString(const std::string &beginComputeRateEquationsMethodString)
{
    mPimpl->mBeginComputeRateEquationsMethodString = beginComputeRateEquationsMethodString;
}

std::string GeneratorProfile::endComputeRateEquationsMethodString() const
{
    return mPimpl->mEndComputeRateEquationsMethodString;
}

void GeneratorProfile::setEndComputeRateEquationsMethodString(const std::string &endComputeRateEquationsMethodString)
{
    mPimpl->mEndComputeRateEquationsMethodString = endComputeRateEquationsMethodString;
}

std::string GeneratorProfile::beginComputeAlgebraicEquationsMethodString() const
{
    return mPimpl->mBeginComputeAlgebraicEquationsMethodString;
}

void GeneratorProfile::setBeginComputeAlgebraicEquationsMethodString(const std::string &beginComputeAlgebraicEquationsMethodString)
{
    mPimpl->mBeginComputeAlgebraicEquationsMethodString = beginComputeAlgebraicEquationsMethodString;
}

std::string GeneratorProfile::endComputeAlgebraicEquationsMethodString() const
{
    return mPimpl->mEndComputeAlgebraicEquationsMethodString;
}

void GeneratorProfile::setEndComputeAlgebraicEquationsMethodString(const std::string &endComputeAlgebraicEquationsMethodString)
{
    mPimpl->mEndComputeAlgebraicEquationsMethodString = endComputeAlgebraicEquationsMethodString;
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
