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

#include "libcellml/enums.h"
#include "libcellml/types.h"

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

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
    ItemType mCause = ItemType::UNDEFINED; /**< The ItemType enum value for the cause of this issue. */
    Issue::Level mLevel = Issue::Level::ERROR; /**< The Issue::Level enum value for this issue. */
    Issue::ReferenceRule mReferenceRule = Issue::ReferenceRule::UNDEFINED; /**< The Issue::ReferenceRule enum value for this issue. */
    std::any mItem;
    ItemType mItemType = ItemType::UNDEFINED;
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
    mPimpl->mItem = std::make_any<ModelPtr>(model);
    mPimpl->mItemType = ItemType::MODEL;
}

Issue::Issue(const ComponentPtr &component)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<ComponentPtr>(component);
    mPimpl->mItemType = ItemType::COMPONENT;
}

Issue::Issue(const ImportSourcePtr &importSource)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<ImportSourcePtr>(importSource);
    mPimpl->mItemType = ItemType::IMPORT;
}

Issue::Issue(const UnitsPtr &units)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<UnitsPtr>(units);
    mPimpl->mItemType = ItemType::UNITS;
}

Issue::Issue(const VariablePtr &variable)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<VariablePtr>(variable);
    mPimpl->mItemType = ItemType::VARIABLE;
}

Issue::Issue(const ResetPtr &reset)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<ResetPtr>(reset);
    mPimpl->mItemType = ItemType::RESET;
}

Issue::Issue(const UnitItem &unit)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<UnitItem>(unit);
    mPimpl->mItemType = ItemType::UNIT;
}

IssuePtr Issue::create() noexcept
{
    return std::shared_ptr<Issue> {new Issue {}};
}

IssuePtr Issue::create(const ComponentPtr &component) noexcept
{
    // Defaults to COMPONENT type.
    return create(ItemType::COMPONENT, component);
}

IssuePtr Issue::create(ItemType type, const ComponentPtr &component) noexcept
{
    // Acceptable types: COMPONENT, COMPONENT_REF.
    if ((type == ItemType::COMPONENT) || (type == ItemType::COMPONENT_REF)) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<ComponentPtr>(component);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const ImportSourcePtr &importSource) noexcept
{
    // Defaults to IMPORT type.
    return create(ItemType::IMPORT, importSource);
}

IssuePtr Issue::create(ItemType type, const ImportSourcePtr &importSource) noexcept
{
    if (type == ItemType::IMPORT) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<ImportSourcePtr>(importSource);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const ModelPtr &model) noexcept
{
    // Defaults to MODEL type.
    return create(ItemType::MODEL, model);
}

IssuePtr Issue::create(ItemType type, const ModelPtr &model) noexcept
{
    // Acceptable type values are: ENCAPSULATION, MODEL.
    if ((type == ItemType::MODEL) || (type == ItemType::ENCAPSULATION)) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<ModelPtr>(model);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const ResetPtr &reset) noexcept
{
    // Defaults to RESET type.
    return create(ItemType::RESET, reset);
}

IssuePtr Issue::create(ItemType type, const ResetPtr &reset) noexcept
{
    // Acceptable type values are: RESET, TEST_VALUE, RESET_VALUE.
    if ((type == ItemType::RESET) || (type == ItemType::RESET_VALUE) || (type == ItemType::TEST_VALUE)) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<ResetPtr>(reset);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const UnitsPtr &units) noexcept
{
    // Defaults to UNITS type.
    return create(ItemType::UNITS, units);
}

IssuePtr Issue::create(ItemType type, const UnitsPtr &units) noexcept
{
    // Acceptable type values are: UNITS.
    if (type == ItemType::UNITS) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<UnitsPtr>(units);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const VariablePtr &variable) noexcept
{
    return create(ItemType::VARIABLE, variable);
}

IssuePtr Issue::create(ItemType type, const VariablePtr &variable) noexcept
{
    // No difference here, VARIABLE is not overloaded.
    if (type == ItemType::VARIABLE) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<VariablePtr>(variable);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const UnitItem &unit) noexcept
{
    return create(ItemType::UNIT, unit);
}

IssuePtr Issue::create(ItemType type, const UnitItem &unit) noexcept
{
    // Acceptable type values are: UNIT.
    if (type == ItemType::UNIT) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<UnitItem>(unit);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(ItemType type, const VariablePair &variablePair) noexcept
{
    // Acceptable type values are: CONNECTION, MAP_VARIABLES.
    if ((type == ItemType::CONNECTION) || (type == ItemType::MAP_VARIABLES)) {
        auto issue = std::shared_ptr<Issue> {new Issue {}};
        issue->mPimpl->mItem = std::make_any<VariablePair>(variablePair);
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

void Issue::setDescription(const std::string &description)
{
    mPimpl->mDescription = description;
}

std::string Issue::description() const
{
    return mPimpl->mDescription;
}

void Issue::setCause(ItemType cause)
{
    mPimpl->mCause = cause;
}

ItemType Issue::cause() const
{
    // Returns the cause, if set independently, or the stored item type if not.
    if (mPimpl->mCause != ItemType::UNDEFINED) {
        return mPimpl->mCause;
    }
    return mPimpl->mItemType;
}

ItemType Issue::itemType() const
{
    return mPimpl->mItemType;
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

void Issue::setItem(ItemType type, const std::any &item)
{
    mPimpl->mItem = item;
    mPimpl->mItemType = type;
}

std::any Issue::item() const
{
    return mPimpl->mItem;
}

void Issue::setComponent(const ComponentPtr &component)
{
    setItem(ItemType::COMPONENT, component);
}

ComponentPtr Issue::component() const
{
    if (mPimpl->mItemType != ItemType::COMPONENT) {
        return nullptr;
    }
    try {
        return std::any_cast<ComponentPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setComponentRef(const ComponentPtr &component)
{
    setItem(ItemType::COMPONENT_REF, component);
}

ComponentPtr Issue::componentRef() const
{
    if (mPimpl->mItemType != ItemType::COMPONENT_REF) {
        return nullptr;
    }
    try {
        return std::any_cast<ComponentPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setMath(const ComponentPtr &component)
{
    setItem(ItemType::MATHML, component);
}

ComponentPtr Issue::math() const
{
    if (mPimpl->mItemType != ItemType::MATHML) {
        return nullptr;
    }
    try {
        return std::any_cast<ComponentPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setImportSource(const ImportSourcePtr &importSource)
{
    setItem(ItemType::IMPORT, importSource);
}

ImportSourcePtr Issue::importSource() const
{
    if (mPimpl->mItemType != ItemType::IMPORT) {
        return nullptr;
    }
    try {
        return std::any_cast<ImportSourcePtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setModel(const ModelPtr &model)
{
    setItem(ItemType::MODEL, model);
}

ModelPtr Issue::model() const
{
    if (mPimpl->mItemType != ItemType::MODEL) {
        return nullptr;
    }
    try {
        return std::any_cast<ModelPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setEncapsulation(const ModelPtr &model)
{
    setItem(ItemType::ENCAPSULATION, model);
}

ModelPtr Issue::encapsulation() const
{
    if (mPimpl->mItemType != ItemType::ENCAPSULATION) {
        return nullptr;
    }
    try {
        return std::any_cast<ModelPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setUnits(const UnitsPtr &units)
{
    setItem(ItemType::UNITS, units);
}

UnitsPtr Issue::units() const
{
    if (mPimpl->mItemType != ItemType::UNITS) {
        return nullptr;
    }
    try {
        return std::any_cast<UnitsPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setUnit(const UnitItem &unit)
{
    setItem(ItemType::UNIT, unit);
}

UnitItem Issue::unit() const
{
    if (mPimpl->mItemType != ItemType::UNIT) {
        return std::make_pair(nullptr, 0);
    }
    try {
        return std::any_cast<UnitItem>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, 0);
    }
}

void Issue::setConnection(const VariablePair &pair)
{
    setItem(ItemType::CONNECTION, pair);
}

VariablePair Issue::connection() const
{
    if (mPimpl->mItemType != ItemType::CONNECTION) {
        return std::make_pair(nullptr, nullptr);
    }
    try {
        return std::any_cast<VariablePair>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

void Issue::setMapVariables(const VariablePair &pair)
{
    setItem(ItemType::MAP_VARIABLES, pair);
}

VariablePair Issue::mapVariables() const
{
    if (mPimpl->mItemType != ItemType::MAP_VARIABLES) {
        return std::make_pair(nullptr, nullptr);
    }
    try {
        return std::any_cast<VariablePair>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

void Issue::setVariable(const VariablePtr &variable)
{
    setItem(ItemType::VARIABLE, variable);
}

VariablePtr Issue::variable() const
{
    if (mPimpl->mItemType != ItemType::VARIABLE) {
        return nullptr;
    }
    try {
        return std::any_cast<VariablePtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setReset(const ResetPtr &reset)
{
    setItem(ItemType::RESET, reset);
}

ResetPtr Issue::reset() const
{
    if (mPimpl->mItemType != ItemType::RESET) {
        return nullptr;
    }
    try {
        return std::any_cast<ResetPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setResetValue(const ResetPtr &reset)
{
    setItem(ItemType::RESET_VALUE, reset);
}

ResetPtr Issue::resetValue() const
{
    if (mPimpl->mItemType != ItemType::RESET_VALUE) {
        return nullptr;
    }
    try {
        return std::any_cast<ResetPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Issue::setTestValue(const ResetPtr &reset)
{
    setItem(ItemType::TEST_VALUE, reset);
}

ResetPtr Issue::testValue() const
{
    if (mPimpl->mItemType != ItemType::TEST_VALUE) {
        return nullptr;
    }
    try {
        return std::any_cast<ResetPtr>(mPimpl->mItem);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

/**
 * @brief Map ReferenceRules to their section titles.
 *
 * An internal map used to convert a Issue::ReferenceRule into its heading string.
 */
static const std::map<Issue::ReferenceRule, std::vector<std::string>> ruleToInformation = {
    {Issue::ReferenceRule::UNDEFINED, {"", "", ""}},

    // Validation errors related to the CellML Specification:
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE, {"1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, {"1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, {"1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, {"1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL, {"1.3.1.2", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_INT_BASE10, {"1.3.2.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_INT_SIGN, {"1.3.2.2", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_INT_DIGIT, {"1.3.2.3", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_BASE10, {"1.3.3.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_SIGN, {"1.3.3.2", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DECIMAL, {"1.3.3.3", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DIGIT, {"1.3.3.4", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_BASE10, {"1.3.4.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_SIGNIFICAND, {"1.3.4.3", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_EXPONENT, {"1.3.4.4", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::MODEL_ELEMENT, {"2.1", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_NAME, {"2.1.1", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_CHILD, {"2.1.2", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION, {"2.1.3", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::IMPORT_HREF, {"2.2.1", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_CHILD, {"2.2.2", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_EQUIVALENT, {"2.2.3", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_UNITS_NAME, {"2.3.1", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_UNITS_NAME_UNIQUE, {"2.3.1", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_UNITS_REF, {"2.3.2", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME, {"2.4.1", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME_UNIQUE, {"2.4.1", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REF, {"2.4.2", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::UNITS_NAME, {"2.5.1", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_NAME_UNIQUE, {"2.5.1", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_STANDARD, {"2.5.2", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_CHILD, {"2.5.3", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNIT_UNITS_REF, {"2.6.1", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_CIRCULAR_REF, {"2.6.1.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE, {"2.6.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_PREFIX, {"2.6.2.1", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_MULTIPLIER, {"2.6.2.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_EXPONENT, {"2.6.2.3", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::COMPONENT_NAME, {"2.7.1", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_NAME_UNIQUE, {"2.7.1", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_CHILD, {"2.7.2", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::VARIABLE_NAME, {"2.8.1.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_NAME_UNIQUE, {"2.8.1.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_UNITS, {"2.8.1.2", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_INTERFACE, {"2.8.2.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_INITIAL_VALUE, {"2.8.2.2", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::RESET_VARIABLE_REF, {"2.9.1.1", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_TEST_VARIABLE_REF, {"2.9.1.2", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_ORDER, {"2.9.1.3", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_CHILD, {"2.9.2", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_TEST_VALUE, {"2.10", baseSpecificationUrl, "specB10"}},
    {Issue::ReferenceRule::RESET_RESET_VALUE, {"2.11", baseSpecificationUrl, "specB11"}},
    {Issue::ReferenceRule::MATH_MATHML, {"2.12.1", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CHILD, {"2.12.2", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CI_VARIABLE_REF, {"2.12.3", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CN_UNITS, {"2.13.4", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::MATH_CN_BASE10, {"2.13.5", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::MATH_CN_FORMAT, {"2.13.5", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::ENCAPSULATION_CHILD, {"2.13.1", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::COMPONENT_REF_COMPONENT, {"2.14.1", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::COMPONENT_REF_CHILD, {"2.14.2", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::CONNECTION_COMPONENT1, {"2.15.1", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_COMPONENT2, {"2.15.2", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_EXCLUDE_SELF, {"2.15.3", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_UNIQUE, {"2.15.4", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_CHILD, {"2.15.5", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1, {"2.16.1", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2, {"2.16.2", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_UNIQUE, {"2.16.3", baseSpecificationUrl, "specB16"}},
};

std::string Issue::referenceHeading() const
{
    auto search = ruleToInformation.find(referenceRule());
    if (search != ruleToInformation.end()) {
        return search->second[0];
    }
    return {};
}

std::string Issue::url() const
{
    auto search = ruleToInformation.find(referenceRule());
    if (referenceRule() != Issue::ReferenceRule::UNDEFINED && search != ruleToInformation.end()) {
        return search->second[1] + search->second[2] + ".html?issue=" + search->second[0];
    }
    return {};
}

} // namespace libcellml
