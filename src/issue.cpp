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

#include "libcellml/component.h"
#include "libcellml/enums.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/types.h"
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
    Issue::Level mLevel = Issue::Level::ERROR; /**< The Issue::Level enum value for this issue. */
    Issue::ReferenceRule mReferenceRule = Issue::ReferenceRule::UNDEFINED; /**< The Issue::ReferenceRule enum value for this issue. */
    std::any mItem;
    CellMLElement mItemType = CellMLElement::UNDEFINED;

    void clearItem();
};

void Issue::IssueImpl::clearItem()
{
    mItemType = CellMLElement::UNDEFINED;
    mItem = nullptr;
}

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
    mPimpl->mItemType = CellMLElement::MODEL;
}

Issue::Issue(const ComponentPtr &component)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<ComponentPtr>(component);
    mPimpl->mItemType = CellMLElement::COMPONENT;
}

Issue::Issue(const ImportSourcePtr &importSource)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<ImportSourcePtr>(importSource);
    mPimpl->mItemType = CellMLElement::IMPORT;
}

Issue::Issue(const UnitsPtr &units)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<UnitsPtr>(units);
    mPimpl->mItemType = CellMLElement::UNITS;
}

Issue::Issue(const VariablePtr &variable)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<VariablePtr>(variable);
    mPimpl->mItemType = CellMLElement::VARIABLE;
}

Issue::Issue(const ResetPtr &reset)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<ResetPtr>(reset);
    mPimpl->mItemType = CellMLElement::RESET;
}

Issue::Issue(const UnitItem &unit)
    : mPimpl(new IssueImpl())
{
    mPimpl->mItem = std::make_any<UnitItem>(unit);
    mPimpl->mItemType = CellMLElement::UNIT;
}

IssuePtr Issue::create() noexcept
{
    return std::shared_ptr<Issue> {new Issue {}};
}

IssuePtr Issue::create(const ComponentPtr &component, CellMLElement type) noexcept
{
    if ((component != nullptr) && ((type == CellMLElement::COMPONENT) || (type == CellMLElement::COMPONENT_REF) || (type == CellMLElement::MATHML))) {
        auto issue = std::shared_ptr<Issue> {new Issue {component}};
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const ImportSourcePtr &importSource) noexcept
{
    if (importSource != nullptr) {
        auto issue = std::shared_ptr<Issue> {new Issue {importSource}};
        issue->mPimpl->mItemType = CellMLElement::IMPORT;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const ModelPtr &model, CellMLElement type) noexcept
{
    // Acceptable type values are: ENCAPSULATION, MODEL.
    if ((model != nullptr) && ((type == CellMLElement::MODEL) || (type == CellMLElement::ENCAPSULATION))) {
        auto issue = std::shared_ptr<Issue> {new Issue {model}};
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const ResetPtr &reset, CellMLElement type) noexcept
{
    // Acceptable type values are: RESET, TEST_VALUE, RESET_VALUE.
    if ((reset != nullptr) && ((type == CellMLElement::RESET) || (type == CellMLElement::RESET_VALUE) || (type == CellMLElement::TEST_VALUE))) {
        auto issue = std::shared_ptr<Issue> {new Issue {reset}};
        issue->mPimpl->mItemType = type;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const UnitsPtr &units) noexcept
{
    if (units != nullptr) {
        auto issue = std::shared_ptr<Issue> {new Issue {units}};
        issue->mPimpl->mItemType = CellMLElement::UNITS;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const VariablePtr &variable) noexcept
{
    if (variable != nullptr) {
        auto issue = std::shared_ptr<Issue> {new Issue {variable}};
        issue->mPimpl->mItemType = CellMLElement::VARIABLE;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const UnitItem &unitItem) noexcept
{
    if (unitItem.first != nullptr) {
        auto issue = std::shared_ptr<Issue> {new Issue {unitItem}};
        issue->mPimpl->mItemType = CellMLElement::UNIT;
        return issue;
    }
    return nullptr;
}

IssuePtr Issue::create(const VariablePair &variablePair, CellMLElement type) noexcept
{
    if ((variablePair.first != nullptr) && (variablePair.second != nullptr) && ((type == CellMLElement::CONNECTION) || (type == CellMLElement::MAP_VARIABLES))) {
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

CellMLElement Issue::itemType() const
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

void Issue::setItem(CellMLElement type, const std::any &item)
{
    mPimpl->mItemType = type;
    try {
        switch (type) {
        case CellMLElement::COMPONENT:
        case CellMLElement::COMPONENT_REF:
        case CellMLElement::MATHML:
            mPimpl->mItem = std::any_cast<ComponentPtr>(item);
            break;
        case CellMLElement::CONNECTION:
        case CellMLElement::MAP_VARIABLES:
            mPimpl->mItem = std::any_cast<VariablePair>(item);
            break;
        case CellMLElement::ENCAPSULATION:
        case CellMLElement::MODEL:
            mPimpl->mItem = std::any_cast<ModelPtr>(item);
            break;
        case CellMLElement::IMPORT:
            mPimpl->mItem = std::any_cast<ImportSourcePtr>(item);
            break;
        case CellMLElement::RESET:
        case CellMLElement::RESET_VALUE:
        case CellMLElement::TEST_VALUE:
            mPimpl->mItem = std::any_cast<ResetPtr>(item);
            break;
        case CellMLElement::UNDEFINED:
            mPimpl->clearItem();
            break;
        case CellMLElement::UNIT:
            mPimpl->mItem = std::any_cast<UnitItem>(item);
            break;
        case CellMLElement::UNITS:
            mPimpl->mItem = std::any_cast<UnitsPtr>(item);
            break;
        case CellMLElement::VARIABLE:
            mPimpl->mItem = std::any_cast<VariablePtr>(item);
            break;
        }
    } catch (std::bad_any_cast &) {
        mPimpl->clearItem();
    }
}

std::any Issue::item() const
{
    return mPimpl->mItem;
}

void Issue::setComponent(const ComponentPtr &component)
{
    if (component != nullptr) {
        setItem(CellMLElement::COMPONENT, component);
    } else if (mPimpl->mItemType == CellMLElement::COMPONENT) {
        mPimpl->clearItem();
    }
}

ComponentPtr Issue::component() const
{
    if (mPimpl->mItemType != CellMLElement::COMPONENT) {
        return nullptr;
    }
    return std::any_cast<ComponentPtr>(mPimpl->mItem);
}

void Issue::setComponentRef(const ComponentPtr &component)
{
    if (component != nullptr) {
        setItem(CellMLElement::COMPONENT_REF, component);
    } else if (mPimpl->mItemType == CellMLElement::COMPONENT_REF) {
        mPimpl->clearItem();
    }
}

ComponentPtr Issue::componentRef() const
{
    if (mPimpl->mItemType != CellMLElement::COMPONENT_REF) {
        return nullptr;
    }
    return std::any_cast<ComponentPtr>(mPimpl->mItem);
}

void Issue::setMath(const ComponentPtr &component)
{
    if (component != nullptr) {
        setItem(CellMLElement::MATHML, component);
    } else if (mPimpl->mItemType == CellMLElement::MATHML) {
        mPimpl->clearItem();
    }
}

ComponentPtr Issue::math() const
{
    if (mPimpl->mItemType != CellMLElement::MATHML) {
        return nullptr;
    }
    return std::any_cast<ComponentPtr>(mPimpl->mItem);
}

void Issue::setImportSource(const ImportSourcePtr &importSource)
{
    if (importSource != nullptr) {
        setItem(CellMLElement::IMPORT, importSource);
    } else if (mPimpl->mItemType == CellMLElement::IMPORT) {
        mPimpl->clearItem();
    }
}

ImportSourcePtr Issue::importSource() const
{
    if (mPimpl->mItemType != CellMLElement::IMPORT) {
        return nullptr;
    }
    return std::any_cast<ImportSourcePtr>(mPimpl->mItem);
}

void Issue::setModel(const ModelPtr &model)
{
    if (model != nullptr) {
        setItem(CellMLElement::MODEL, model);
    } else if (mPimpl->mItemType == CellMLElement::MODEL) {
        mPimpl->clearItem();
    }
}

ModelPtr Issue::model() const
{
    if (mPimpl->mItemType != CellMLElement::MODEL) {
        return nullptr;
    }
    return std::any_cast<ModelPtr>(mPimpl->mItem);
}

void Issue::setEncapsulation(const ModelPtr &model)
{
    if (model != nullptr) {
        setItem(CellMLElement::ENCAPSULATION, model);
    } else if (mPimpl->mItemType == CellMLElement::ENCAPSULATION) {
        mPimpl->clearItem();
    }
}

ModelPtr Issue::encapsulation() const
{
    if (mPimpl->mItemType != CellMLElement::ENCAPSULATION) {
        return nullptr;
    }
    return std::any_cast<ModelPtr>(mPimpl->mItem);
}

void Issue::setUnits(const UnitsPtr &units)
{
    if (units != nullptr) {
        setItem(CellMLElement::UNITS, units);
    } else if (mPimpl->mItemType == CellMLElement::UNITS) {
        mPimpl->clearItem();
    }
}

UnitsPtr Issue::units() const
{
    if (mPimpl->mItemType != CellMLElement::UNITS) {
        return nullptr;
    }
    return std::any_cast<UnitsPtr>(mPimpl->mItem);
}

void Issue::setUnit(const UnitItem &unit)
{
    if (unit.first != nullptr) {
        setItem(CellMLElement::UNIT, unit);
    } else if (mPimpl->mItemType == CellMLElement::UNIT) {
        mPimpl->clearItem();
    }
}

UnitItem Issue::unit() const
{
    if (mPimpl->mItemType != CellMLElement::UNIT) {
        return std::make_pair(nullptr, 0);
    }
    return std::any_cast<UnitItem>(mPimpl->mItem);
}

void Issue::setConnection(const VariablePair &pair)
{
    if ((pair.first != nullptr) && (pair.second != nullptr)) {
        setItem(CellMLElement::CONNECTION, pair);
    } else if (mPimpl->mItemType == CellMLElement::CONNECTION) {
        mPimpl->clearItem();
    }
}

VariablePair Issue::connection() const
{
    if (mPimpl->mItemType != CellMLElement::CONNECTION) {
        return std::make_pair(nullptr, nullptr);
    }
    return std::any_cast<VariablePair>(mPimpl->mItem);
}

void Issue::setMapVariables(const VariablePair &pair)
{
    if ((pair.first != nullptr) && (pair.second != nullptr)) {
        setItem(CellMLElement::MAP_VARIABLES, pair);
    } else if (mPimpl->mItemType == CellMLElement::MAP_VARIABLES) {
        mPimpl->clearItem();
    }
}

VariablePair Issue::mapVariables() const
{
    if (mPimpl->mItemType != CellMLElement::MAP_VARIABLES) {
        return std::make_pair(nullptr, nullptr);
    }
    return std::any_cast<VariablePair>(mPimpl->mItem);
}

void Issue::setVariable(const VariablePtr &variable)
{
    if (variable != nullptr) {
        setItem(CellMLElement::VARIABLE, variable);
    } else if (mPimpl->mItemType == CellMLElement::VARIABLE) {
        mPimpl->clearItem();
    }
}

VariablePtr Issue::variable() const
{
    if (mPimpl->mItemType != CellMLElement::VARIABLE) {
        return nullptr;
    }
    return std::any_cast<VariablePtr>(mPimpl->mItem);
}

void Issue::setReset(const ResetPtr &reset)
{
    if (reset != nullptr) {
        setItem(CellMLElement::RESET, reset);
    } else if (mPimpl->mItemType == CellMLElement::RESET) {
        mPimpl->clearItem();
    }
}

ResetPtr Issue::reset() const
{
    if (mPimpl->mItemType != CellMLElement::RESET) {
        return nullptr;
    }
    return std::any_cast<ResetPtr>(mPimpl->mItem);
}

void Issue::setResetValue(const ResetPtr &reset)
{
    if (reset != nullptr) {
        setItem(CellMLElement::RESET_VALUE, reset);
    } else if (mPimpl->mItemType == CellMLElement::RESET_VALUE) {
        mPimpl->clearItem();
    }
}

ResetPtr Issue::resetValue() const
{
    if (mPimpl->mItemType != CellMLElement::RESET_VALUE) {
        return nullptr;
    }
    return std::any_cast<ResetPtr>(mPimpl->mItem);
}

void Issue::setTestValue(const ResetPtr &reset)
{
    if (reset != nullptr) {
        setItem(CellMLElement::TEST_VALUE, reset);
    } else if (mPimpl->mItemType == CellMLElement::TEST_VALUE) {
        mPimpl->clearItem();
    }
}

ResetPtr Issue::testValue() const
{
    if (mPimpl->mItemType != CellMLElement::TEST_VALUE) {
        return nullptr;
    }
    return std::any_cast<ResetPtr>(mPimpl->mItem);
}

void Issue::clear()
{
    mPimpl->clearItem();
    mPimpl->mDescription = "";
    mPimpl->mLevel = Issue::Level::ERROR;
    mPimpl->mReferenceRule = Issue::ReferenceRule::UNDEFINED;
}

/**
 * @brief Map ReferenceRules to their section titles.
 *
 * An internal map used to convert a Issue::ReferenceRule into its heading string.
 */
static const std::map<Issue::ReferenceRule, std::vector<std::string>> ruleToInformation = {
    {Issue::ReferenceRule::UNDEFINED, {"", "", ""}},

    // Validation errors related to the CellML Specification:
    {Issue::ReferenceRule::XML, {"1.2.1", baseSpecificationUrl, "specA02"}},
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
    {Issue::ReferenceRule::MAP_VARIABLES_AVAILABLE_INTERFACE, {"3.10.8", baseSpecificationUrl, "specC10"}},
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
