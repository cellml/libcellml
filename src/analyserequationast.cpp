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

#ifdef NAN
#    undef NAN
#endif

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
    static const std::map<AnalyserEquationAst::Type, std::string> typeToString = {
        {Type::ASSIGNMENT, "ASSIGNMENT"},
        {Type::EQ, "EQ"},
        {Type::NEQ, "NEQ"},
        {Type::LT, "LT"},
        {Type::LEQ, "LEQ"},
        {Type::GT, "GT"},
        {Type::GEQ, "GEQ"},
        {Type::AND, "AND"},
        {Type::OR, "OR"},
        {Type::XOR, "XOR"},
        {Type::NOT, "NOT"},
        {Type::PLUS, "PLUS"},
        {Type::MINUS, "MINUS"},
        {Type::TIMES, "TIMES"},
        {Type::DIVIDE, "DIVIDE"},
        {Type::POWER, "POWER"},
        {Type::ROOT, "ROOT"},
        {Type::ABS, "ABS"},
        {Type::EXP, "EXP"},
        {Type::LN, "LN"},
        {Type::LOG, "LOG"},
        {Type::CEILING, "CEILING"},
        {Type::FLOOR, "FLOOR"},
        {Type::MIN, "MIN"},
        {Type::MAX, "MAX"},
        {Type::REM, "REM"},
        {Type::DIFF, "DIFF"},
        {Type::SIN, "SIN"},
        {Type::COS, "COS"},
        {Type::TAN, "TAN"},
        {Type::SEC, "SEC"},
        {Type::CSC, "CSC"},
        {Type::COT, "COT"},
        {Type::SINH, "SINH"},
        {Type::COSH, "COSH"},
        {Type::TANH, "TANH"},
        {Type::SECH, "SECH"},
        {Type::CSCH, "CSCH"},
        {Type::COTH, "COTH"},
        {Type::ASIN, "ASIN"},
        {Type::ACOS, "ACOS"},
        {Type::ATAN, "ATAN"},
        {Type::ASEC, "ASEC"},
        {Type::ACSC, "ACSC"},
        {Type::ACOT, "ACOT"},
        {Type::ASINH, "ASINH"},
        {Type::ACOSH, "ACOSH"},
        {Type::ATANH, "ATANH"},
        {Type::ASECH, "ASECH"},
        {Type::ACSCH, "ACSCH"},
        {Type::ACOTH, "ACOTH"},
        {Type::PIECEWISE, "PIECEWISE"},
        {Type::PIECE, "PIECE"},
        {Type::OTHERWISE, "OTHERWISE"},
        {Type::CI, "CI"},
        {Type::CN, "CN"},
        {Type::DEGREE, "DEGREE"},
        {Type::LOGBASE, "LOGBASE"},
        {Type::BVAR, "BVAR"},
        {Type::TRUE, "TRUE"},
        {Type::FALSE, "FALSE"},
        {Type::E, "E"},
        {Type::PI, "PI"},
        {Type::INF, "INF"},
        {Type::NAN, "NAN"}};

    return typeToString.at(mPimpl->mType);
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
