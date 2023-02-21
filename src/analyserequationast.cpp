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

std::string AnalyserEquationAst::typeAsString(Type type)
{
    static const std::map<AnalyserEquationAst::Type, std::string> typeToString = {
        {Type::ASSIGNMENT, "assignment"},
        {Type::EQ, "eq"},
        {Type::NEQ, "neq"},
        {Type::LT, "lt"},
        {Type::LEQ, "leq"},
        {Type::GT, "gt"},
        {Type::GEQ, "geq"},
        {Type::AND, "and"},
        {Type::OR, "or"},
        {Type::XOR, "xor"},
        {Type::NOT, "not"},
        {Type::PLUS, "plus"},
        {Type::MINUS, "minus"},
        {Type::TIMES, "times"},
        {Type::DIVIDE, "divide"},
        {Type::POWER, "power"},
        {Type::ROOT, "root"},
        {Type::ABS, "abs"},
        {Type::EXP, "exp"},
        {Type::LN, "ln"},
        {Type::LOG, "log"},
        {Type::CEILING, "ceiling"},
        {Type::FLOOR, "floor"},
        {Type::MIN, "min"},
        {Type::MAX, "max"},
        {Type::REM, "rem"},
        {Type::DIFF, "diff"},
        {Type::SIN, "sin"},
        {Type::COS, "cos"},
        {Type::TAN, "tan"},
        {Type::SEC, "sec"},
        {Type::CSC, "csc"},
        {Type::COT, "cot"},
        {Type::SINH, "sinh"},
        {Type::COSH, "cosh"},
        {Type::TANH, "tanh"},
        {Type::SECH, "sech"},
        {Type::CSCH, "csch"},
        {Type::COTH, "coth"},
        {Type::ASIN, "asin"},
        {Type::ACOS, "acos"},
        {Type::ATAN, "atan"},
        {Type::ASEC, "asec"},
        {Type::ACSC, "acsc"},
        {Type::ACOT, "acot"},
        {Type::ASINH, "asinh"},
        {Type::ACOSH, "acosh"},
        {Type::ATANH, "atanh"},
        {Type::ASECH, "asech"},
        {Type::ACSCH, "acsch"},
        {Type::ACOTH, "acoth"},
        {Type::PIECEWISE, "piecewise"},
        {Type::PIECE, "piece"},
        {Type::OTHERWISE, "otherwise"},
        {Type::CI, "ci"},
        {Type::CN, "cn"},
        {Type::DEGREE, "degree"},
        {Type::LOGBASE, "logbase"},
        {Type::BVAR, "bvar"},
        {Type::TRUE, "true"},
        {Type::FALSE, "false"},
        {Type::E, "e"},
        {Type::PI, "pi"},
        {Type::INF, "inf"},
        {Type::NAN, "nan"}};

    return typeToString.at(type);
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
