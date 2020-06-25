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

AnalyserEquationAstPtr AnalyserEquationAst::create(Type type,
                                                   const AnalyserEquationAstPtr &parent) noexcept
{
    auto res = std::shared_ptr<AnalyserEquationAst> {new AnalyserEquationAst {}};

    res->mPimpl->mType = type;
    res->mPimpl->mParent = parent;

    return res;
}

AnalyserEquationAstPtr AnalyserEquationAst::create(Type type,
                                                   const std::string &value,
                                                   const AnalyserEquationAstPtr &parent) noexcept
{
    auto res = std::shared_ptr<AnalyserEquationAst> {new AnalyserEquationAst {}};

    res->mPimpl->mType = type;
    res->mPimpl->mValue = value;
    res->mPimpl->mParent = parent;

    return res;
}

AnalyserEquationAstPtr AnalyserEquationAst::create(Type type,
                                                   const VariablePtr &variable,
                                                   const AnalyserEquationAstPtr &parent) noexcept
{
    auto res = std::shared_ptr<AnalyserEquationAst> {new AnalyserEquationAst {}};

    res->mPimpl->mType = type;
    res->mPimpl->mVariable = variable;
    res->mPimpl->mParent = parent;

    return res;
}

AnalyserEquationAstPtr AnalyserEquationAst::create(const AnalyserEquationAstPtr &ast,
                                                   const AnalyserEquationAstPtr &parent) noexcept
{
    auto res = std::shared_ptr<AnalyserEquationAst> {new AnalyserEquationAst {}};

    res->mPimpl->mType = ast->mPimpl->mType;
    res->mPimpl->mVariable = ast->mPimpl->mVariable;
    res->mPimpl->mParent = parent;
    res->mPimpl->mLeftChild = ast->mPimpl->mLeftChild;
    res->mPimpl->mRightChild = ast->mPimpl->mRightChild;

    return res;
}

AnalyserEquationAst::Type AnalyserEquationAst::type() const
{
    return mPimpl->mType;
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
    return mPimpl->mVariable;
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
    return mPimpl->mLeftChild;
}

void AnalyserEquationAst::setLeftChild(const AnalyserEquationAstPtr &leftChild)
{
    mPimpl->mLeftChild = leftChild;
}

AnalyserEquationAstPtr AnalyserEquationAst::rightChild() const
{
    return mPimpl->mRightChild;
}

void AnalyserEquationAst::setRightChild(const AnalyserEquationAstPtr &rightChild)
{
    mPimpl->mRightChild = rightChild;
}

} // namespace libcellml
