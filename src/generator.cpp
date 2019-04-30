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

#include "xmldoc.h"

#include <vector>

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/model.h"
#include "libcellml/validator.h"

namespace libcellml{

class GeneratorEquationBinTree;
typedef std::shared_ptr<GeneratorEquationBinTree> GeneratorEquationBinTreePtr;

class GeneratorEquationBinTree
{
public:
    explicit GeneratorEquationBinTree();

    GeneratorEquationBinTreePtr &left();
    GeneratorEquationBinTreePtr &right();

private:
    GeneratorEquationBinTreePtr mLeft;
    GeneratorEquationBinTreePtr mRight;
};

GeneratorEquationBinTree::GeneratorEquationBinTree()
    : mLeft(nullptr)
    , mRight(nullptr)
{
}

GeneratorEquationBinTreePtr &GeneratorEquationBinTree::left()
{
    return mLeft;
}

GeneratorEquationBinTreePtr &GeneratorEquationBinTree::right()
{
    return mRight;
}

class GeneratorEquation;
typedef std::shared_ptr<GeneratorEquation> GeneratorEquationPtr;

class GeneratorEquation
{
public:
    explicit GeneratorEquation();

    GeneratorEquationBinTreePtr &binTree();

private:
    GeneratorEquationBinTreePtr mBinTree;
};

GeneratorEquation::GeneratorEquation()
    : mBinTree(std::make_shared<GeneratorEquationBinTree>())
{
}

GeneratorEquationBinTreePtr &GeneratorEquation::binTree()
{
    return mBinTree;
}

struct GeneratorVariable
{
};

typedef std::shared_ptr<GeneratorVariable> GeneratorVariablePtr;

struct Generator::GeneratorImpl
{
    bool mWithNames;

    std::vector<GeneratorVariablePtr> mStates;
    std::vector<GeneratorVariablePtr> mVariables;

    size_t mathmlChildCount(const XmlNodePtr &node) const;
    XmlNodePtr mathmlChildNode(const XmlNodePtr &node, int index) const;

    void processNode(const XmlNodePtr &node);
};

size_t Generator::GeneratorImpl::mathmlChildCount(const XmlNodePtr &node) const
{
    // Return the number of child elements, in the MathML namespace, for the
    // given node

    size_t res = 0;
    XmlNodePtr childNode = node->getFirstChild();

    while (childNode != nullptr) {
        if (childNode->isMathmlElement()) {
            ++res;
        }

        childNode = childNode->getNext();
    }

    return res;
}

XmlNodePtr Generator::GeneratorImpl::mathmlChildNode(const XmlNodePtr &node, int index) const
{
    // Return the nth child element of the given node, skipping anything that is
    // not int he MathML namespace

    // Retrieve the first MathML node, if it exists

    XmlNodePtr res = node->getFirstChild();

    while (res && !res->isMathmlElement()) {
        res = res->getNext();
    }

    // Retrieve the nth MathML element, if it exists

    int nodeIndex = 0;

    while (res && (nodeIndex != index)) {
        while (res && !res->isMathmlElement()) {
            res = res->getNext();
        }

        ++nodeIndex;
    }

    return res;
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node)
{
(void) node;

//TODO
}

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
}

Generator::~Generator()
{
    delete mPimpl;
}

Generator::Generator(const Generator &rhs)
    : Logger(rhs)
    , mPimpl(new GeneratorImpl())
{
    mPimpl->mStates = rhs.mPimpl->mStates;
    mPimpl->mVariables = rhs.mPimpl->mVariables;
}

Generator::Generator(Generator &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Generator& Generator::operator=(Generator rhs)
{
    Logger::operator =(rhs);
    rhs.swap(*this);
    return *this;
}

void Generator::swap(Generator &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Generator::processModel(const ModelPtr &model)
{
    // Make sure that the model is valid before processing it

/*TODO: reenable the validation once it is known to work fine...
    libcellml::Validator validator;

    validator.validateModel(model);

    if (validator.errorCount() > 0) {
        // The model is not valid, so retrieve the validation errors and keep a
        // copy of them

        for (size_t i = 0; i < validator.errorCount(); ++i)
            addError(validator.getError(i));

        return;
    }
*/

    // Determine the order in which equations should be executed by processing
    // each of the components in the given model

    for (size_t i = 0; i < model->componentCount(); ++i) {
        // Retrieve the math string associated with the given component and
        // process it, one equation at a time
        // Note: at this stage, we know the model is valid, so no point in
        //       revalidating the math string...

        ComponentPtr component = model->getComponent(i);
        XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();
        std::string math = component->getMath();

        xmlDoc->parse(math);

        XmlNodePtr mathNode = xmlDoc->getRootNode();

        for (XmlNodePtr node = mathNode->getFirstChild();
             node != nullptr; node = node->getNext()) {
            mPimpl->processNode(node);
        }
    }
}

void Generator::setWithNames(bool withNames)
{
    mPimpl->mWithNames = withNames;
}

size_t Generator::stateCount() const
{
    return mPimpl->mStates.size();
}

size_t Generator::rateCount() const
{
    return stateCount();
}

size_t Generator::variableCount() const
{
    return mPimpl->mVariables.size();
}

std::string Generator::initializeVariables() const
{
    return "";
}

std::string Generator::computeConstantEquations() const
{
    return "";
}

std::string Generator::computeRateEquations() const
{
    return "";
}

std::string Generator::computeAlgebraicEquations() const
{
    return "";
}

}
