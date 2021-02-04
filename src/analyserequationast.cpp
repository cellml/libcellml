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

void AnalyserEquationAst::AnalyserEquationAstImpl::populate(Type type,
                                                            const AnalyserEquationAstPtr &parent)
{
    mType = type;
    mParent = parent;
}

void AnalyserEquationAst::AnalyserEquationAstImpl::populate(Type type,
                                                            const std::string &value,
                                                            const UnitsPtr &units,
                                                            const AnalyserEquationAstPtr &parent)
{
    mType = type;
    mValue = value;
    mUnits = units;
    mParent = parent;
}

void AnalyserEquationAst::AnalyserEquationAstImpl::populate(Type type,
                                                            const VariablePtr &variable,
                                                            const UnitsPtr &units,
                                                            const AnalyserEquationAstPtr &parent)
{
    mType = type;
    mVariable = variable;
    mUnits = units;
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

} // namespace libcellml
