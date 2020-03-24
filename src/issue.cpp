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
static const std::map<Issue::ReferenceRule, const std::string> ruleToHeading = {
    {Issue::ReferenceRule::UNDEFINED, ""},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE, "3.1.1"},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, "3.1.2"},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, "3.1.3"},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, "3.1.4"},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL, "3.1.5"},
    {Issue::ReferenceRule::DATA_REPR_NNEG_INT_BASE10, "3.2.1"},
    {Issue::ReferenceRule::DATA_REPR_NNEG_INT_EURO_NUM, "3.2.2"},
    {Issue::ReferenceRule::MODEL_ELEMENT, "4.1"},
    {Issue::ReferenceRule::MODEL_NAME, "4.2.1"},
    {Issue::ReferenceRule::MODEL_CHILD, "4.2.2"},
    {Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION, "4.2.3"},
    {Issue::ReferenceRule::IMPORT_HREF, "5.1.1"},
    {Issue::ReferenceRule::IMPORT_CHILD, "5.1.2"},
    {Issue::ReferenceRule::IMPORT_CIRCULAR, "5.1.3"}, // TODO: double-check meaning & implementation.
    {Issue::ReferenceRule::IMPORT_UNITS_NAME, "6.1.1"},
    {Issue::ReferenceRule::IMPORT_UNITS_REF, "6.1.2"},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME, "7.1.1"},
    {Issue::ReferenceRule::IMPORT_COMPONENT_REF, "7.1.2"},
    {Issue::ReferenceRule::UNITS_NAME, "8.1.1"},
    {Issue::ReferenceRule::UNITS_NAME_UNIQUE, "8.1.2"},
    {Issue::ReferenceRule::UNITS_STANDARD, "8.1.3"},
    {Issue::ReferenceRule::UNITS_CHILD, "8.1.4"},
    {Issue::ReferenceRule::UNIT_UNITS_REF, "9.1.1"},
    {Issue::ReferenceRule::UNIT_DIGRAPH, "9.1.1.1"}, // Assume we're skipping this for now.
    {Issue::ReferenceRule::UNIT_CIRCULAR_REF, "9.1.1.2"}, // TODO: double-check meaning & implementation.
    {Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE, "9.1.2"},
    {Issue::ReferenceRule::UNIT_PREFIX, "9.1.2.1"},
    {Issue::ReferenceRule::UNIT_MULTIPLIER, "9.1.2.2"},
    {Issue::ReferenceRule::UNIT_EXPONENT, "9.1.2.3"},
    {Issue::ReferenceRule::COMPONENT_NAME, "10.1.1"},
    {Issue::ReferenceRule::COMPONENT_CHILD, "10.1.2"},
    {Issue::ReferenceRule::VARIABLE_NAME, "11.1.1.1"},
    {Issue::ReferenceRule::VARIABLE_UNITS, "11.1.1.2"},
    {Issue::ReferenceRule::VARIABLE_INTERFACE, "11.1.2.1"},
    {Issue::ReferenceRule::VARIABLE_INITIAL_VALUE, "11.1.2.2"},
    {Issue::ReferenceRule::RESET_VARIABLE_REFERENCE, "12.1.1.1"},
    {Issue::ReferenceRule::RESET_TEST_VARIABLE_REFERENCE, "12.1.1.1"},
    {Issue::ReferenceRule::RESET_ORDER, "12.1.1.2"},
    {Issue::ReferenceRule::RESET_CHILD, "12.1.2"},
    {Issue::ReferenceRule::RESET_TEST_VALUE, "12.1.2"},
    {Issue::ReferenceRule::RESET_RESET_VALUE, "12.1.2"},
    {Issue::ReferenceRule::MATH_MATHML, "14.1.1"},
    {Issue::ReferenceRule::MATH_CHILD, "14.1.2"},
    {Issue::ReferenceRule::MATH_CI_VARIABLE_REFERENCE, "14.1.3"},
    {Issue::ReferenceRule::MATH_CN_UNITS_ATTRIBUTE, "14.1.4"},
    {Issue::ReferenceRule::ENCAPSULATION_COMPONENT_REF, "15.1.1"},
    {Issue::ReferenceRule::COMPONENT_REF_COMPONENT_ATTRIBUTE, "16.1.1"},
    {Issue::ReferenceRule::COMPONENT_REF_CHILD, "16.1.2"},
    {Issue::ReferenceRule::COMPONENT_REF_ENCAPSULATION, "16.1.3"}, // Seems to be the same as 12.1.1?
    {Issue::ReferenceRule::CONNECTION_COMPONENT1, "17.1.1"},
    {Issue::ReferenceRule::CONNECTION_COMPONENT2, "17.1.2"},
    {Issue::ReferenceRule::CONNECTION_UNIQUE_TRANSITIVE, "17.1.3"},
    {Issue::ReferenceRule::CONNECTION_MAP_VARIABLES, "17.1.4"},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1, "18.1.1"},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2, "18.1.2"},
    {Issue::ReferenceRule::MAP_VARIABLES_UNIQUE, "18.1.3"}};

std::string Issue::referenceHeading() const
{
    std::string heading = "X.Y.Z";
    auto search = ruleToHeading.find(referenceRule());
    if (search != ruleToHeading.end()) {
        heading = search->second;
    }
    return heading;
}

} // namespace libcellml
