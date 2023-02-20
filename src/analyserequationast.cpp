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

#include "libcellml/analyserequationast.h"

#include "analyserequationast_p.h"

namespace libcellml {

void AnalyserEquationAst::AnalyserEquationAstImpl::populate(AnalyserEquationAst::Type type,
                                                            const AnalyserEquationAstPtr &parent)
{
    mType = type;
    mParent = parent;
}

void AnalyserEquationAst::AnalyserEquationAstImpl::populate(AnalyserEquationAst::Type type,
                                                            const std::string &value,
                                                            const AnalyserEquationAstPtr &parent)
{
    mType = type;
    mValue = value;
    mParent = parent;
}

void AnalyserEquationAst::AnalyserEquationAstImpl::populate(AnalyserEquationAst::Type type,
                                                            const VariablePtr &variable,
                                                            const AnalyserEquationAstPtr &parent)
{
    mType = type;
    mVariable = variable;
    mParent = parent;
}

AnalyserEquationAst::AnalyserEquationAst()
    : mPimpl(new AnalyserEquationAstImpl())
{
}

AnalyserEquationAst::~AnalyserEquationAst()
{
    delete mPimpl;
}

AnalyserEquationAstPtr AnalyserEquationAst::create() noexcept
{
    return std::shared_ptr<AnalyserEquationAst> {new AnalyserEquationAst {}};
}

AnalyserEquationAst::Type AnalyserEquationAst::type() const
{
    return mPimpl->mType;
}

std::string AnalyserEquationAst::typeAsString() const
{
    if (mPimpl->mType == Type::ASSIGNMENT) {
        return "ASSIGNMENT";
    }

    if (mPimpl->mType == Type::EQ) {
        return "EQ";
    }

    if (mPimpl->mType == Type::NEQ) {
        return "NEQ";
    }

    if (mPimpl->mType == Type::LT) {
        return "LT";
    }

    if (mPimpl->mType == Type::LEQ) {
        return "LEQ";
    }

    if (mPimpl->mType == Type::GT) {
        return "GT";
    }

    if (mPimpl->mType == Type::GEQ) {
        return "GEQ";
    }

    if (mPimpl->mType == Type::AND) {
        return "AND";
    }

    if (mPimpl->mType == Type::OR) {
        return "OR";
    }

    if (mPimpl->mType == Type::XOR) {
        return "XOR";
    }

    if (mPimpl->mType == Type::NOT) {
        return "NOT";
    }

    if (mPimpl->mType == Type::PLUS) {
        return "PLUS";
    }

    if (mPimpl->mType == Type::MINUS) {
        return "MINUS";
    }

    if (mPimpl->mType == Type::TIMES) {
        return "TIMES";
    }

    if (mPimpl->mType == Type::DIVIDE) {
        return "DIVIDE";
    }

    if (mPimpl->mType == Type::POWER) {
        return "POWER";
    }

    if (mPimpl->mType == Type::ROOT) {
        return "ROOT";
    }

    if (mPimpl->mType == Type::ABS) {
        return "ABS";
    }

    if (mPimpl->mType == Type::EXP) {
        return "EXP";
    }

    if (mPimpl->mType == Type::LN) {
        return "LN";
    }

    if (mPimpl->mType == Type::LOG) {
        return "LOG";
    }

    if (mPimpl->mType == Type::CEILING) {
        return "CEILING";
    }

    if (mPimpl->mType == Type::FLOOR) {
        return "FLOOR";
    }

    if (mPimpl->mType == Type::MIN) {
        return "MIN";
    }

    if (mPimpl->mType == Type::MAX) {
        return "MAX";
    }

    if (mPimpl->mType == Type::REM) {
        return "REM";
    }

    if (mPimpl->mType == Type::DIFF) {
        return "DIFF";
    }

    if (mPimpl->mType == Type::SIN) {
        return "SIN";
    }

    if (mPimpl->mType == Type::COS) {
        return "COS";
    }

    if (mPimpl->mType == Type::TAN) {
        return "TAN";
    }

    if (mPimpl->mType == Type::SEC) {
        return "SEC";
    }

    if (mPimpl->mType == Type::CSC) {
        return "CSC";
    }

    if (mPimpl->mType == Type::COT) {
        return "COT";
    }

    if (mPimpl->mType == Type::SINH) {
        return "SINH";
    }

    if (mPimpl->mType == Type::COSH) {
        return "COSH";
    }

    if (mPimpl->mType == Type::TANH) {
        return "TANH";
    }

    if (mPimpl->mType == Type::SECH) {
        return "SECH";
    }

    if (mPimpl->mType == Type::CSCH) {
        return "CSCH";
    }

    if (mPimpl->mType == Type::COTH) {
        return "COTH";
    }

    if (mPimpl->mType == Type::ASIN) {
        return "ASIN";
    }

    if (mPimpl->mType == Type::ACOS) {
        return "ACOS";
    }

    if (mPimpl->mType == Type::ATAN) {
        return "ATAN";
    }

    if (mPimpl->mType == Type::ASEC) {
        return "ASEC";
    }

    if (mPimpl->mType == Type::ACSC) {
        return "ACSC";
    }

    if (mPimpl->mType == Type::ACOT) {
        return "ACOT";
    }

    if (mPimpl->mType == Type::ASINH) {
        return "ASINH";
    }

    if (mPimpl->mType == Type::ACOSH) {
        return "ACOSH";
    }

    if (mPimpl->mType == Type::ATANH) {
        return "ATANH";
    }

    if (mPimpl->mType == Type::ASECH) {
        return "ASECH";
    }

    if (mPimpl->mType == Type::ACSCH) {
        return "ACSCH";
    }

    if (mPimpl->mType == Type::ACOTH) {
        return "ACOTH";
    }

    if (mPimpl->mType == Type::PIECEWISE) {
        return "PIECEWISE";
    }

    if (mPimpl->mType == Type::PIECE) {
        return "PIECE";
    }

    if (mPimpl->mType == Type::OTHERWISE) {
        return "OTHERWISE";
    }

    if (mPimpl->mType == Type::CI) {
        return "CI";
    }

    if (mPimpl->mType == Type::CN) {
        return "CN";
    }

    if (mPimpl->mType == Type::DEGREE) {
        return "DEGREE";
    }

    if (mPimpl->mType == Type::LOGBASE) {
        return "LOGBASE";
    }

    if (mPimpl->mType == Type::BVAR) {
        return "BVAR";
    }

    if (mPimpl->mType == Type::TRUE) {
        return "TRUE";
    }

    if (mPimpl->mType == Type::FALSE) {
        return "FALSE";
    }

    if (mPimpl->mType == Type::E) {
        return "E";
    }

    if (mPimpl->mType == Type::PI) {
        return "PI";
    }

    if (mPimpl->mType == Type::INF) {
        return "INF";
    }

    // mPimpl->mType == Type::NAN:

    return "NAN";
}

void AnalyserEquationAst::setType(Type type)
{
    mPimpl->mType = type;
}

std::string AnalyserEquationAst::value() const
{
    return mPimpl->mValue;
}

void AnalyserEquationAst::setValue(const std::string &value)
{
    mPimpl->mValue = value;
}

VariablePtr AnalyserEquationAst::variable() const
{
    return mPimpl->mVariable.lock();
}

void AnalyserEquationAst::setVariable(const VariablePtr &variable)
{
    mPimpl->mVariable = variable;
}

AnalyserEquationAstPtr AnalyserEquationAst::parent() const
{
    return mPimpl->mParent.lock();
}

void AnalyserEquationAst::setParent(const AnalyserEquationAstPtr &parent)
{
    mPimpl->mParent = parent;
}

AnalyserEquationAstPtr AnalyserEquationAst::leftChild() const
{
    if (mPimpl->mOwnedLeftChild != nullptr) {
        return mPimpl->mOwnedLeftChild;
    }

    return mPimpl->mLeftChild.lock();
}

void AnalyserEquationAst::setLeftChild(const AnalyserEquationAstPtr &leftChild)
{
    mPimpl->mOwnedLeftChild = nullptr;
    mPimpl->mLeftChild = leftChild;
}

AnalyserEquationAstPtr AnalyserEquationAst::rightChild() const
{
    if (mPimpl->mOwnedRightChild != nullptr) {
        return mPimpl->mOwnedRightChild;
    }

    return mPimpl->mRightChild.lock();
}

void AnalyserEquationAst::setRightChild(const AnalyserEquationAstPtr &rightChild)
{
    mPimpl->mOwnedRightChild = nullptr;
    mPimpl->mRightChild = rightChild;
}

void AnalyserEquationAst::swapLeftAndRightChildren()
{
    auto oldOwnedLeftChild = mPimpl->mOwnedLeftChild;
    auto oldOwnedRightChild = mPimpl->mOwnedRightChild;

    mPimpl->mOwnedLeftChild = oldOwnedRightChild;
    mPimpl->mOwnedRightChild = oldOwnedLeftChild;

    auto oldLeftChild = mPimpl->mLeftChild;
    auto oldRightChild = mPimpl->mRightChild;

    mPimpl->mLeftChild = oldRightChild;
    mPimpl->mRightChild = oldLeftChild;
}

} // namespace libcellml
