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

#include "libcellml/issue.h"

#include <map>
#include <string>

#include "libcellml/types.h"

#include "utilities.h"

namespace libcellml {

/**
 * @brief The Issue::IssueImpl struct.
 *
 * The private implementation for the Issue class.
 */
struct Issue::IssueImpl
{
    std::string mDescription; /**< The string description for why this issue was raised. */
    Issue::Cause mCause = Issue::Cause::UNDEFINED; /**< The Issue::Cause enum value for this issue. */
    Issue::Level mLevel = Issue::Level::ERROR; /**< The Issue::Level enum value for this issue. */
    Issue::ReferenceRule mReferenceRule = Issue::ReferenceRule::UNDEFINED; /**< The Issue::ReferenceRule enum value for this issue. */
    ComponentPtr mComponent; /**< Pointer to the component that the issue occurred in. */
    ImportSourcePtr mImportSource; /**< Pointer to the import source that the issue occurred in. */
    ModelPtr mModel; /**< Pointer to the model that the issue occurred in. */
    UnitsPtr mUnits; /**< Pointer to the units that the issue occurred in. */
    VariablePtr mVariable; /**< Pointer to the variable that the issue occurred in. */
    ResetPtr mReset; /**< Pointer to the reset that the issue ocurred in. */
};

Issue::Issue()
    : mPimpl(new IssueImpl())
{
}

Issue::~Issue()
{
    delete mPimpl;
}

Issue::Issue(const ModelPtr &model)
    : mPimpl(new IssueImpl())
{
    mPimpl->mModel = model;
    mPimpl->mCause = Issue::Cause::MODEL;
}

Issue::Issue(const ComponentPtr &component)
    : mPimpl(new IssueImpl())
{
    mPimpl->mComponent = component;
    mPimpl->mCause = Issue::Cause::COMPONENT;
}

Issue::Issue(const ImportSourcePtr &importSource)
    : mPimpl(new IssueImpl())
{
    mPimpl->mImportSource = importSource;
    mPimpl->mCause = Issue::Cause::IMPORT;
}

Issue::Issue(const UnitsPtr &units)
    : mPimpl(new IssueImpl())
{
    mPimpl->mUnits = units;
    mPimpl->mCause = Issue::Cause::UNITS;
}

Issue::Issue(const VariablePtr &variable)
    : mPimpl(new IssueImpl())
{
    mPimpl->mVariable = variable;
    mPimpl->mCause = Issue::Cause::VARIABLE;
}

Issue::Issue(const ResetPtr &reset)
    : mPimpl(new IssueImpl())
{
    mPimpl->mReset = reset;
    mPimpl->mCause = Issue::Cause::RESET;
}

IssuePtr Issue::create() noexcept
{
    return std::shared_ptr<Issue> {new Issue {}};
}

IssuePtr Issue::create(const ComponentPtr &component) noexcept
{
    return std::shared_ptr<Issue> {new Issue {component}};
}

IssuePtr Issue::create(const ImportSourcePtr &importSource) noexcept
{
    return std::shared_ptr<Issue> {new Issue {importSource}};
}

IssuePtr Issue::create(const ModelPtr &model) noexcept
{
    return std::shared_ptr<Issue> {new Issue {model}};
}

IssuePtr Issue::create(const ResetPtr &reset) noexcept
{
    return std::shared_ptr<Issue> {new Issue {reset}};
}

IssuePtr Issue::create(const UnitsPtr &units) noexcept
{
    return std::shared_ptr<Issue> {new Issue {units}};
}

IssuePtr Issue::create(const VariablePtr &variable) noexcept
{
    return std::shared_ptr<Issue> {new Issue {variable}};
}

void Issue::setDescription(const std::string &description)
{
    mPimpl->mDescription = description;
}

std::string Issue::description() const
{
    return mPimpl->mDescription;
}

void Issue::setCause(Issue::Cause cause)
{
    mPimpl->mCause = cause;
}

Issue::Cause Issue::cause() const
{
    return mPimpl->mCause;
}

void Issue::setLevel(Issue::Level level)
{
    mPimpl->mLevel = level;
}

Issue::Level Issue::level() const
{
    return mPimpl->mLevel;
}

void Issue::setReferenceRule(Issue::ReferenceRule referenceRule)
{
    mPimpl->mReferenceRule = referenceRule;
}

Issue::ReferenceRule Issue::referenceRule() const
{
    return mPimpl->mReferenceRule;
}

void Issue::setComponent(const ComponentPtr &component)
{
    mPimpl->mComponent = component;
    mPimpl->mCause = Issue::Cause::COMPONENT;
}

ComponentPtr Issue::component() const
{
    return mPimpl->mComponent;
}

void Issue::setImportSource(const ImportSourcePtr &importSource)
{
    mPimpl->mImportSource = importSource;
    mPimpl->mCause = Issue::Cause::IMPORT;
}

ImportSourcePtr Issue::importSource() const
{
    return mPimpl->mImportSource;
}

void Issue::setModel(const ModelPtr &model)
{
    mPimpl->mModel = model;
    mPimpl->mCause = Issue::Cause::MODEL;
}

ModelPtr Issue::model() const
{
    return mPimpl->mModel;
}

void Issue::setUnits(const UnitsPtr &units)
{
    mPimpl->mUnits = units;
    mPimpl->mCause = Issue::Cause::UNITS;
}

UnitsPtr Issue::units() const
{
    return mPimpl->mUnits;
}

void Issue::setVariable(const VariablePtr &variable)
{
    mPimpl->mVariable = variable;
    mPimpl->mCause = Issue::Cause::VARIABLE;
}

VariablePtr Issue::variable() const
{
    return mPimpl->mVariable;
}

void Issue::setReset(const ResetPtr &reset)
{
    mPimpl->mReset = reset;
    mPimpl->mCause = Issue::Cause::RESET;
}

ResetPtr Issue::reset() const
{
    return mPimpl->mReset;
}

/**
 * @brief Map ReferenceRules to their section titles.
 *
 * An internal map used to convert a Issue::ReferenceRule into its heading string.
 */
static const std::map<Issue::ReferenceRule, std::vector<std::string>> ruleToInformation = {
    {Issue::ReferenceRule::UNDEFINED, {"UNDEFINED", "", "", ""}},

    // Validation errors related to the CellML Specification:
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE, {"DATA_REPR_IDENTIFIER_UNICODE", "1.3.1.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, {"DATA_REPR_IDENTIFIER_LATIN_ALPHANUM", "1.3.1.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, {"DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM", "1.3.1.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, {"DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM", "1.3.1.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL, {"DATA_REPR_IDENTIFIER_IDENTICAL", "1.3.1.2", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_INT_BASE10, {"DATA_REPR_INT_BASE10", "1.3.2.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_INT_SIGN, {"DATA_REPR_INT_SIGN", "1.3.2.2", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_INT_DIGIT, {"DATA_REPR_INT_DIGIT", "1.3.2.3", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_BASE10, {"DATA_REPR_BASIC_REAL_BASE10", "1.3.3.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_SIGN, {"DATA_REPR_BASIC_REAL_SIGN", "1.3.3.2", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DECIMAL, {"DATA_REPR_BASIC_REAL_DECIMAL", "1.3.3.3", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DIGIT, {"DATA_REPR_BASIC_REAL_DIGIT", "1.3.3.4", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_BASE10, {"DATA_REPR_REAL_BASE10", "1.3.4.1", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_SIGNIFICAND, {"DATA_REPR_REAL_SIGNIFICAND", "1.3.4.3", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_EXPONENT, {"DATA_REPR_REAL_EXPONENT", "1.3.4.4", baseSpecificationUrl, "specA3"}},
    {Issue::ReferenceRule::MODEL_ELEMENT, {"MODEL_ELEMENT", "2.1", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_NAME, {"MODEL_NAME", "2.1.1", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_CHILD, {"MODEL_CHILD", "2.1.2", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION, {"MODEL_MORE_THAN_ONE_ENCAPSULATION", "2.1.3", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::IMPORT_HREF, {"IMPORT_HREF", "2.2.1", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_CHILD, {"IMPORT_CHILD", "2.2.2", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_EQUIVALENT, {"IMPORT_EQUIVALENT", "2.2.3", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_UNITS_NAME, {"IMPORT_UNITS_NAME", "2.3.1", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_UNITS_NAME_UNIQUE, {"IMPORT_UNITS_NAME_UNIQUE", "2.3.1", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_UNITS_REF, {"IMPORT_UNITS_REF", "2.3.2", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME, {"IMPORT_COMPONENT_NAME", "2.4.1", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME_UNIQUE, {"IMPORT_COMPONENT_NAME_UNIQUE", "2.4.1", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REF, {"IMPORT_COMPONENT_COMPONENT_REF", "2.4.2", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::UNITS_NAME, {"UNITS_NAME", "2.5.1", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_NAME_UNIQUE, {"UNITS_NAME_UNIQUE", "2.5.1", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_STANDARD, {"UNITS_STANDARD", "2.5.2", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_CHILD, {"UNITS_CHILD", "2.5.3", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNIT_UNITS_REF, {"UNIT_UNITS_REF", "2.6.1", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_CIRCULAR_REF, {"UNIT_CIRCULAR_REF", "2.6.1.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE, {"UNIT_OPTIONAL_ATTRIBUTE", "2.6.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_PREFIX, {"UNIT_PREFIX", "2.6.2.1", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_MULTIPLIER, {"UNIT_MULTIPLIER", "2.6.2.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_EXPONENT, {"UNIT_EXPONENT", "2.6.2.3", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::COMPONENT_NAME, {"COMPONENT_NAME", "2.7.1", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_NAME_UNIQUE, {"COMPONENT_NAME_UNIQUE", "2.7.1", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_CHILD, {"COMPONENT_CHILD", "2.7.2", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::VARIABLE_NAME, {"VARIABLE_NAME", "2.8.1.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_NAME_UNIQUE, {"VARIABLE_NAME_UNIQUE", "2.8.1.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_UNITS, {"VARIABLE_UNITS", "2.8.1.2", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_INTERFACE, {"VARIABLE_INTERFACE", "2.8.2.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_INITIAL_VALUE, {"VARIABLE_INITIAL_VALUE", "2.8.2.2", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::RESET_VARIABLE_REF, {"RESET_VARIABLE_REF", "2.9.1.1", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_TEST_VARIABLE_REF, {"RESET_TEST_VARIABLE_REF", "2.9.1.2", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_ORDER, {"RESET_ORDER", "2.9.1.3", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_CHILD, {"RESET_CHILD", "2.9.2", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_TEST_VALUE, {"RESET_TEST_VALUE", "2.10", baseSpecificationUrl, "specB10"}},
    {Issue::ReferenceRule::RESET_RESET_VALUE, {"RESET_RESET_VALUE", "2.11", baseSpecificationUrl, "specB11"}},
    {Issue::ReferenceRule::MATH_MATHML, {"MATH_MATHML", "2.12.1", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CHILD, {"MATH_CHILD", "2.12.2", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CI_VARIABLE_REF, {"MATH_CI_VARIABLE_REF", "2.12.3", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CN_UNITS, {"MATH_CN_UNITS", "2.13.4", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::MATH_CN_BASE10, {"MATH_CN_BASE10", "2.13.5", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::MATH_CN_FORMAT, {"MATH_CN_FORMAT", "2.13.5", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::ENCAPSULATION_CHILD, {"ENCAPSULATION_CHILD", "2.13.1", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::COMPONENT_REF_COMPONENT, {"COMPONENT_REF_COMPONENT", "2.14.1", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::COMPONENT_REF_CHILD, {"COMPONENT_REF_CHILD", "2.14.2", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::CONNECTION_COMPONENT1, {"CONNECTION_COMPONENT1", "2.15.1", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_COMPONENT2, {"CONNECTION_COMPONENT2", "2.15.2", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_EXCLUDE_SELF, {"CONNECTION_EXCLUDE_SELF", "2.15.3", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_UNIQUE, {"CONNECTION_UNIQUE", "2.15.4", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_CHILD, {"CONNECTION_CHILD", "2.15.5", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1, {"MAP_VARIABLES_VARIABLE1", "2.16.1", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2, {"MAP_VARIABLES_VARIABLE2", "2.16.2", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_UNIQUE, {"MAP_VARIABLES_UNIQUE", "2.16.3", baseSpecificationUrl, "specB16"}},

    // Issues outside the specification.
    {Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, {"MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION", "X.Y.Z", baseExampleUrl, "tbc"}},

};

std::string Issue::referenceHeading() const
{
    std::string heading = "X.Y.Z";
    auto search = ruleToInformation.find(referenceRule());
    if (search != ruleToInformation.end()) {
        heading = search->second.at(1);
    }
    return heading;
}

std::string Issue::url() const
{
    // {Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, {"x.y.z", baseExampleUrl, "tbc"}},
    // std::vector<std::string> parts = ruleToInformation.find(referenceRule());
    // std::string url = parts.at(1) + parts.at(2) + ".html?issue="+referenceRule;

    std::string issueUrl = "X.Y.Z";
    auto search = ruleToInformation.find(referenceRule());
    if (search != ruleToInformation.end()) {
        issueUrl = search->second.at(2) + search->second.at(3) + ".html?issue=" + search->second.at(0);
    }
    return issueUrl;
}

} // namespace libcellml
