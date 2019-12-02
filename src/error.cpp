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
#include "libcellml/types.h"

#include <map>
#include <string>

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
    ResetPtr mReset; /**< Pointer to the reset that the error ocurred in. */
};

Error::Error()
    : mPimpl(new ErrorImpl())
{
}

Error::~Error()
{
    delete mPimpl;
}

Error::Error(const ModelPtr &model)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mModel = model;
    mPimpl->mKind = Error::Kind::MODEL;
}

Error::Error(const ComponentPtr &component)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mComponent = component;
    mPimpl->mKind = Error::Kind::COMPONENT;
}

Error::Error(const ImportSourcePtr &importSource)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mImportSource = importSource;
    mPimpl->mKind = Error::Kind::IMPORT;
}

Error::Error(const UnitsPtr &units)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mUnits = units;
    mPimpl->mKind = Error::Kind::UNITS;
}

Error::Error(const VariablePtr &variable)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mVariable = variable;
    mPimpl->mKind = Error::Kind::VARIABLE;
}

Error::Error(const ResetPtr &reset)
    : mPimpl(new ErrorImpl())
{
    mPimpl->mReset = reset;
    mPimpl->mKind = Error::Kind::RESET;
}

ErrorPtr Error::create() noexcept
{
    return std::shared_ptr<Error> {new Error {}};
}

ErrorPtr Error::create(const ComponentPtr &component) noexcept
{
    return std::shared_ptr<Error> {new Error {component}};
}

ErrorPtr Error::create(const ImportSourcePtr &importSource) noexcept
{
    return std::shared_ptr<Error> {new Error {importSource}};
}

ErrorPtr Error::create(const ModelPtr &model) noexcept
{
    return std::shared_ptr<Error> {new Error {model}};
}

ErrorPtr Error::create(const ResetPtr &reset) noexcept
{
    return std::shared_ptr<Error> {new Error {reset}};
}

ErrorPtr Error::create(const UnitsPtr &units) noexcept
{
    return std::shared_ptr<Error> {new Error {units}};
}

ErrorPtr Error::create(const VariablePtr &variable) noexcept
{
    return std::shared_ptr<Error> {new Error {variable}};
}

void Error::setDescription(const std::string &description)
{
    mPimpl->mDescription = description;
}

std::string Error::description() const
{
    return mPimpl->mDescription;
}

void Error::setKind(Error::Kind kind)
{
    mPimpl->mKind = kind;
}

Error::Kind Error::kind() const
{
    return mPimpl->mKind;
}

bool Error::isKind(Kind kind) const
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

SpecificationRule Error::rule() const
{
    return mPimpl->mRule;
}

void Error::setComponent(const ComponentPtr &component)
{
    mPimpl->mComponent = component;
    mPimpl->mKind = Error::Kind::COMPONENT;
}

ComponentPtr Error::component() const
{
    return mPimpl->mComponent;
}

void Error::setImportSource(const ImportSourcePtr &importSource)
{
    mPimpl->mImportSource = importSource;
    mPimpl->mKind = Error::Kind::IMPORT;
}

ImportSourcePtr Error::importSource() const
{
    return mPimpl->mImportSource;
}

void Error::setModel(const ModelPtr &model)
{
    mPimpl->mModel = model;
    mPimpl->mKind = Error::Kind::MODEL;
}

ModelPtr Error::model() const
{
    return mPimpl->mModel;
}

void Error::setUnits(const UnitsPtr &units)
{
    mPimpl->mUnits = units;
    mPimpl->mKind = Error::Kind::UNITS;
}

UnitsPtr Error::units() const
{
    return mPimpl->mUnits;
}

void Error::setVariable(const VariablePtr &variable)
{
    mPimpl->mVariable = variable;
    mPimpl->mKind = Error::Kind::VARIABLE;
}

VariablePtr Error::variable() const
{
    return mPimpl->mVariable;
}

void Error::setReset(const ResetPtr &reset)
{
    mPimpl->mReset = reset;
    mPimpl->mKind = Error::Kind::RESET;
}

ResetPtr Error::reset() const
{
    return mPimpl->mReset;
}

/**
 * @brief Map SpecificationRules to their section titles.
 *
 * An internal map used to convert a SpecificationRule into its heading string.
 */
static const std::map<SpecificationRule, const std::string> ruleToHeading = {
    {SpecificationRule::UNDEFINED, ""},
    {SpecificationRule::DATA_REPR_IDENTIFIER_UNICODE, "3.1.1"},
    {SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, "3.1.2"},
    {SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, "3.1.3"},
    {SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, "3.1.4"},
    {SpecificationRule::DATA_REPR_IDENTIFIER_IDENTICAL, "3.1.5"},
    {SpecificationRule::DATA_REPR_NNEG_INT_BASE10, "3.2.1"},
    {SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM, "3.2.2"},
    {SpecificationRule::MODEL_ELEMENT, "4.1"},
    {SpecificationRule::MODEL_NAME, "4.2.1"},
    {SpecificationRule::MODEL_CHILD, "4.2.2"},
    {SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION, "4.2.3"},
    {SpecificationRule::IMPORT_HREF, "5.1.1"},
    {SpecificationRule::IMPORT_CHILD, "5.1.2"},
    {SpecificationRule::IMPORT_CIRCULAR, "5.1.3"}, // TODO: double-check meaning & implementation.
    {SpecificationRule::IMPORT_UNITS_NAME, "6.1.1"},
    {SpecificationRule::IMPORT_UNITS_REF, "6.1.2"},
    {SpecificationRule::IMPORT_COMPONENT_NAME, "7.1.1"},
    {SpecificationRule::IMPORT_COMPONENT_REF, "7.1.2"},
    {SpecificationRule::UNITS_NAME, "8.1.1"},
    {SpecificationRule::UNITS_NAME_UNIQUE, "8.1.2"},
    {SpecificationRule::UNITS_STANDARD, "8.1.3"},
    {SpecificationRule::UNITS_CHILD, "8.1.4"},
    {SpecificationRule::UNIT_UNITS_REF, "9.1.1"},
    {SpecificationRule::UNIT_DIGRAPH, "9.1.1.1"}, // Assume we're skipping this for now.
    {SpecificationRule::UNIT_CIRCULAR_REF, "9.1.1.2"}, // TODO: double-check meaning & implementation.
    {SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE, "9.1.2"},
    {SpecificationRule::UNIT_PREFIX, "9.1.2.1"},
    {SpecificationRule::UNIT_MULTIPLIER, "9.1.2.2"},
    {SpecificationRule::UNIT_EXPONENT, "9.1.2.3"},
    {SpecificationRule::COMPONENT_NAME, "10.1.1"},
    {SpecificationRule::COMPONENT_CHILD, "10.1.2"},
    {SpecificationRule::VARIABLE_NAME, "11.1.1.1"},
    {SpecificationRule::VARIABLE_UNITS, "11.1.1.2"},
    {SpecificationRule::VARIABLE_INTERFACE, "11.1.2.1"},
    {SpecificationRule::VARIABLE_INITIAL_VALUE, "11.1.2.2"},
    {SpecificationRule::RESET_VARIABLE_REFERENCE, "12.1.1.1"},
    {SpecificationRule::RESET_TEST_VARIABLE_REFERENCE, "12.1.1.1"},
    {SpecificationRule::RESET_ORDER, "12.1.1.2"},
    {SpecificationRule::RESET_CHILD, "12.1.2"},
    {SpecificationRule::RESET_TEST_VALUE, "12.1.2"},
    {SpecificationRule::RESET_RESET_VALUE, "12.1.2"},
    {SpecificationRule::MATH_MATHML, "14.1.1"},
    {SpecificationRule::MATH_CHILD, "14.1.2"},
    {SpecificationRule::MATH_CI_VARIABLE_REFERENCE, "14.1.3"},
    {SpecificationRule::MATH_CN_UNITS_ATTRIBUTE, "14.1.4"},
    {SpecificationRule::ENCAPSULATION_COMPONENT_REF, "15.1.1"},
    {SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE, "16.1.1"},
    {SpecificationRule::COMPONENT_REF_CHILD, "16.1.2"},
    {SpecificationRule::COMPONENT_REF_ENCAPSULATION, "16.1.3"}, // Seems to be the same as 12.1.1?
    {SpecificationRule::CONNECTION_COMPONENT1, "17.1.1"},
    {SpecificationRule::CONNECTION_COMPONENT2, "17.1.2"},
    {SpecificationRule::CONNECTION_UNIQUE_TRANSITIVE, "17.1.3"},
    {SpecificationRule::CONNECTION_MAP_VARIABLES, "17.1.4"},
    {SpecificationRule::MAP_VARIABLES_VARIABLE1, "18.1.1"},
    {SpecificationRule::MAP_VARIABLES_VARIABLE2, "18.1.2"},
    {SpecificationRule::MAP_VARIABLES_UNIQUE, "18.1.3"},
    {SpecificationRule::MAP_VARIABLES_EQUIVALENT, "19.10.6"}};

std::string Error::specificationHeading() const
{
    std::string heading = "X.Y.Z";
    auto search = ruleToHeading.find(rule());
    if (search != ruleToHeading.end()) {
        heading = search->second;
    }
    return heading;
}

} // namespace libcellml
