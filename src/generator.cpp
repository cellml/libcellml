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

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/model.h"

#include <vector>

namespace libcellml{

struct GeneratorVariable
{
};

typedef std::shared_ptr<GeneratorVariable> GeneratorVariablePtr;

struct Generator::GeneratorImpl
{
    bool mWithNames;

    std::vector<GeneratorVariablePtr> mStates;
    std::vector<GeneratorVariablePtr> mVariables;
};

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

void Generator::analyzeModel(const ModelPtr &model)
{
    // Determine the order in which equations should be executed by analysing
    // each of the components in the given model

    static const std::string fromString = "<math";
    static const std::string toString = R"(<math xmlns:cellml="http://www.cellml.org/cellml/2.0#")";
    static const size_t fromStringSize = fromString.size();
    static const size_t toStringSize = toString.size();

    for (size_t i = 0; i < model->componentCount(); ++i) {
        // Retrieve the math string associated with the given component and add
        // the CellML namespace to its math element, so that it can then be
        // parsed without any problems

        ComponentPtr component = model->getComponent(i);
        XmlDocPtr mathmlDoc = std::make_shared<XmlDoc>();
        std::string math = component->getMath();
        size_t pos = math.find(fromString);

        while (pos != std::string::npos) {
            math.replace(pos, fromStringSize, toString);

            pos = math.find(fromString, pos + toStringSize);
        }

        // Parse the math string and generate errors, if any

        mathmlDoc->parse(math);

        if (mathmlDoc->xmlErrorCount() > 0) {
            // There are errors, so report them

            for (size_t i = 0; i < mathmlDoc->xmlErrorCount(); ++i) {
                ErrorPtr error = std::make_shared<Error>();

                error->setDescription(mathmlDoc->getXmlError(i));
                error->setComponent(component);
                error->setKind(Error::Kind::MATHML);

                addError(error);
            }
        } else {
            // There are no errors, so process our MahtML document

//TODO
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
