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

#include "libcellml/error.h"

#include <map>
#include <string>

#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Error::ErrorImpl struct.
 *
 * The private implementation for the Error class.
 */
struct Error::ErrorImpl
{
    std::string mDescription; /**< The string description for why this entity error raised. */
    Error::Kind mKind = Error::Kind::UNDEFINED; /**< The Error::Kind enum value for this error. */
    SpecificationRule mRule = SpecificationRule::UNDEFINED; /**< The SpecificationRule enum value for this error. */
    ComponentPtr mComponent; /**< Pointer to the component that the error occurred in. */
    ImportSourcePtr mImportSource; /**< Pointer to the import source that the error occurred in. */
    ModelPtr mModel; /**< Pointer to the model that the error occurred in. */
    UnitsPtr mUnits; /**< Pointer to the units that the error occurred in. */
    VariablePtr mVariable; /**< Pointer to the variable that the error occurred in. */
};

Error::Error()
    : mPimpl(new ErrorImpl())
{
}

Error::~Error()
{
    delete mPimpl;
}

Error::Error(const Error& rhs)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mDescription = rhs.mPimpl->mDescription;
    mPimpl->mKind = rhs.mPimpl->mKind;
    mPimpl->mComponent = rhs.mPimpl->mComponent;
    mPimpl->mImportSource = rhs.mPimpl->mImportSource;
    mPimpl->mModel = rhs.mPimpl->mModel;
    mPimpl->mUnits = rhs.mPimpl->mUnits;
    mPimpl->mVariable = rhs.mPimpl->mVariable;
}

Error::Error(Error &&rhs)
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Error& Error::operator=(Error rhs)
{
    rhs.swap(*this);
    return *this;
}

void Error::swap(Error &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Error::setDescription(const std::string &description)
{
    mPimpl->mDescription = description;
}

std::string Error::getDescription() const
{
    return mPimpl->mDescription;
}

void Error::setKind(Error::Kind kind)
{
    mPimpl->mKind = kind;
}

Error::Kind Error::getKind() const
{
    return mPimpl->mKind;
}

bool Error::isKind(const Error::Kind &kind) const
{
    bool response = false;
    if (mPimpl->mKind == kind) {
        response = true;
    }
    return response;
}

void Error::setRule(SpecificationRule rule)
{
    mPimpl->mRule = rule;
}

SpecificationRule Error::getRule() const
{
    return mPimpl->mRule;
}

void Error::setComponent(const ComponentPtr &component)
{
    mPimpl->mComponent = component;
}

ComponentPtr Error::getComponent() const
{
    return mPimpl->mComponent;
}

void Error::setImportSource(const ImportSourcePtr &importSource)
{
    mPimpl->mImportSource = importSource;
}

ImportSourcePtr Error::getSourceImport() const
{
    return mPimpl->mImportSource;
}

void Error::setModel(const ModelPtr &model)
{
    mPimpl->mModel = model;
}

ModelPtr Error::getModel() const
{
    return mPimpl->mModel;
}

void Error::setUnits(const UnitsPtr &units)
{
    mPimpl->mUnits = units;
}

UnitsPtr Error::getUnits() const
{
    return mPimpl->mUnits;
}

void Error::setVariable(const VariablePtr &variable)
{
    mPimpl->mVariable = variable;
}

VariablePtr Error::getVariable() const
{
    return mPimpl->mVariable;
}

/**
 * @brief Map SpecificationRules to their section titles.
 *
 * An internal map used to convert a SpecificationRule into its heading string.
 */
std::map<SpecificationRule, const std::string> ruleToHeading =
{
    {SpecificationRule::UNDEFINED, ""},
    {SpecificationRule::MODEL_ELEMENT, "4.1"},
    {SpecificationRule::MODEL_NAME, "4.2.1"},
    {SpecificationRule::MODEL_CHILD, "4.2.2"},
    {SpecificationRule::IMPORT_HREF, "5.1.1"},
    {SpecificationRule::IMPORT_CHILD, "5.1.2"},
    {SpecificationRule::IMPORT_CIRCULAR, "5.1.3"}, // TODO: double-check meaning & implementation.
    {SpecificationRule::IMPORT_UNITS_NAME, "6.1.1"},
    {SpecificationRule::IMPORT_UNITS_REF, "6.1.2"},
    {SpecificationRule::IMPORT_COMPONENT_NAME, "7.1.1"},
    {SpecificationRule::IMPORT_COMPONENT_REF, "7.1.2"},
    {SpecificationRule::UNITS_NAME, "8.1.1"},
    {SpecificationRule::UNITS_MODEL_UNIQUE, "8.1.1.1"},
    {SpecificationRule::UNITS_COMPONENT_UNIQUE, "8.1.1.2"},
    {SpecificationRule::UNITS_STANDARD, "8.1.1.3"},
    {SpecificationRule::UNITS_BASE, "8.1.2"},
    {SpecificationRule::UNITS_CHILD, "8.1.3"},
    {SpecificationRule::UNIT_UNITS_REF, "9.1.1"},
    {SpecificationRule::UNIT_DIGRAPH, "9.1.1.1"}, // Assume we're skipping this for now.
    {SpecificationRule::UNIT_CIRCULAR_REF, "9.1.1.2"}, // TODO: double-check meaning & implementation.
    {SpecificationRule::UNIT_ATTRIBUTE, "9.1.2"},
    {SpecificationRule::UNIT_PREFIX, "9.1.2.1"},
    {SpecificationRule::UNIT_MULTIPLIER, "9.1.2.2"},
    {SpecificationRule::UNIT_EXPONENT, "9.1.2.3"},
    {SpecificationRule::COMPONENT_NAME, "10.1.1"},
    {SpecificationRule::COMPONENT_CHILD, "10.1.2"},
    {SpecificationRule::VARIABLE_ATTRIBUTE, "11.1"},
    {SpecificationRule::VARIABLE_NAME, "11.1.1.1"},
    {SpecificationRule::VARIABLE_UNITS, "11.1.1.2"},
    {SpecificationRule::VARIABLE_INTERFACE, "11.1.2.1"},
    {SpecificationRule::VARIABLE_INITIAL_VALUE, "11.1.2.2"},
    {SpecificationRule::ENCAPSULATION_COMPONENT_REF, "12.1.1"},
    {SpecificationRule::COMPONENT_REF_COMPONENT, "13.1.1"},
    {SpecificationRule::COMPONENT_REF_CHILD, "13.1.2"},
    {SpecificationRule::ENCAPSULATION_COMPONENT_REF_CHILD, "13.1.3"}, // Seems to be the same as 12.1.1?
    {SpecificationRule::CONNECTION_CHILD, "14.1"},
    {SpecificationRule::CONNECTION_MAP_COMPONENTS, "14.1.1"},
    {SpecificationRule::CONNECTION_MAP_VARIABLES, "14.1.2"},
    {SpecificationRule::MAP_COMPONENTS_COMPONENT1, "15.1.1"},
    {SpecificationRule::MAP_COMPONENTS_COMPONENT2, "15.1.2"},
    {SpecificationRule::MAP_VARIABLES_VARIABLE1, "16.1.1"},
    {SpecificationRule::MAP_VARIABLES_VARIABLE1, "16.1.2"},
};

std::string Error::getSpecificationHeading() const
{
    return ruleToHeading.find(getRule())->second;;
}

}
