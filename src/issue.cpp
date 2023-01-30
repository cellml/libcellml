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

#include "anycellmlelement_p.h"
#include "issue_p.h"
#include "utilities.h"

namespace libcellml {

IssuePtr Issue::IssueImpl::create()
{
    return std::shared_ptr<Issue> {new Issue {}};
}

void Issue::IssueImpl::setDescription(const std::string &description)
{
    mDescription = description;
}

void Issue::IssueImpl::setLevel(Issue::Level level)
{
    mLevel = level;
}

void Issue::IssueImpl::setReferenceRule(Issue::ReferenceRule referenceRule)
{
    mReferenceRule = referenceRule;
}

Issue::Issue()
    : mPimpl(new IssueImpl())
{
}

Issue::~Issue()
{
    delete mPimpl;
}

std::string Issue::description() const
{
    return mPimpl->mDescription;
}

Issue::Level Issue::level() const
{
    return mPimpl->mLevel;
}

Issue::ReferenceRule Issue::referenceRule() const
{
    return mPimpl->mReferenceRule;
}

AnyCellmlElementPtr Issue::item() const
{
    return mPimpl->mItem;
}

/**
 * @brief Map ReferenceRules to their section titles.
 *
 * An internal map used to convert a Issue::ReferenceRule into its heading string.
 */
static const std::map<Issue::ReferenceRule, std::vector<std::string>> ruleToInformation = {
    {Issue::ReferenceRule::UNDEFINED, {"", "", "", ""}},

    // Validation errors related to the CellML Specification:
    {Issue::ReferenceRule::XML, {"XML", "1.2.1", baseSpecificationUrl, "specA02"}},
    {Issue::ReferenceRule::XML_ID_ATTRIBUTE, {"XML", "1.2.5", baseSpecificationUrl, "specA02"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE, {"DATA_REPR_IDENTIFIER_UNICODE", "1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, {"DATA_REPR_IDENTIFIER_LATIN_ALPHANUM", "1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, {"DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM", "1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, {"DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM", "1.3.1.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL, {"DATA_REPR_IDENTIFIER_IDENTICAL", "1.3.1.2", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_INT_BASE10, {"DATA_REPR_INT_BASE10", "1.3.2.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_INT_SIGN, {"DATA_REPR_INT_SIGN", "1.3.2.2", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_INT_DIGIT, {"DATA_REPR_INT_DIGIT", "1.3.2.3", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_BASE10, {"DATA_REPR_BASIC_REAL_BASE10", "1.3.3.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_SIGN, {"DATA_REPR_BASIC_REAL_SIGN", "1.3.3.2", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DECIMAL, {"DATA_REPR_BASIC_REAL_DECIMAL", "1.3.3.3", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DIGIT, {"DATA_REPR_BASIC_REAL_DIGIT", "1.3.3.4", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_BASE10, {"DATA_REPR_REAL_BASE10", "1.3.4.1", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_SIGNIFICAND, {"DATA_REPR_REAL_SIGNIFICAND", "1.3.4.3", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::DATA_REPR_REAL_EXPONENT, {"DATA_REPR_REAL_EXPONENT", "1.3.4.4", baseSpecificationUrl, "specA03"}},
    {Issue::ReferenceRule::MODEL_ELEMENT, {"MODEL_ELEMENT", "2.1", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_NAME, {"MODEL_NAME", "2.1.1", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_CHILD, {"MODEL_CHILD", "2.1.2", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION, {"MODEL_MORE_THAN_ONE_ENCAPSULATION", "2.1.3", baseSpecificationUrl, "specB01"}},
    {Issue::ReferenceRule::IMPORT_ATTRIBUTE, {"IMPORT_ATTRIBUTE", "2.2", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_HREF, {"IMPORT_HREF", "2.2.1", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_CHILD, {"IMPORT_CHILD", "2.2.2", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_EQUIVALENT, {"IMPORT_EQUIVALENT", "2.2.3", baseSpecificationUrl, "specB02"}},
    {Issue::ReferenceRule::IMPORT_UNITS_NAME, {"IMPORT_UNITS_NAME", "2.3.1", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_UNITS_NAME_UNIQUE, {"IMPORT_UNITS_NAME_UNIQUE", "2.3.1", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_UNITS_REF, {"IMPORT_UNITS_REF", "2.3.2", baseSpecificationUrl, "specB03"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME, {"IMPORT_COMPONENT_NAME", "2.4.1", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_NAME_UNIQUE, {"IMPORT_COMPONENT_NAME_UNIQUE", "2.4.1", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REF, {"IMPORT_COMPONENT_COMPONENT_REF", "2.4.2", baseSpecificationUrl, "specB04"}},
    {Issue::ReferenceRule::UNITS_ATTRIBUTE, {"UNITS_ATTRIBUTE", "2.5", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_NAME, {"UNITS_NAME", "2.5.1", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_NAME_UNIQUE, {"UNITS_NAME_UNIQUE", "2.5.1", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_STANDARD, {"UNITS_STANDARD", "2.5.2", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNITS_CHILD, {"UNITS_CHILD", "2.5.3", baseSpecificationUrl, "specB05"}},
    {Issue::ReferenceRule::UNIT_ATTRIBUTE, {"UNIT_ATTRIBUTE", "2.6", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_UNITS_REF, {"UNIT_UNITS_REF", "2.6.1", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_CIRCULAR_REF, {"UNIT_CIRCULAR_REF", "2.6.1.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE, {"UNIT_OPTIONAL_ATTRIBUTE", "2.6.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_PREFIX, {"UNIT_PREFIX", "2.6.2.1", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_MULTIPLIER, {"UNIT_MULTIPLIER", "2.6.2.2", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::UNIT_EXPONENT, {"UNIT_EXPONENT", "2.6.2.3", baseSpecificationUrl, "specB06"}},
    {Issue::ReferenceRule::COMPONENT_ATTRIBUTE, {"COMPONENT_ATTRIBUTE", "2.7", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_NAME, {"COMPONENT_NAME", "2.7.1", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_NAME_UNIQUE, {"COMPONENT_NAME_UNIQUE", "2.7.1", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::COMPONENT_CHILD, {"COMPONENT_CHILD", "2.7.2", baseSpecificationUrl, "specB07"}},
    {Issue::ReferenceRule::VARIABLE_ATTRIBUTE, {"VARIABLE_ATTRIBUTE", "2.8", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_CHILD, {"VARIABLE_CHILD", "2.8", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_NAME, {"VARIABLE_NAME", "2.8.1.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_NAME_UNIQUE, {"VARIABLE_NAME_UNIQUE", "2.8.1.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_UNITS, {"VARIABLE_UNITS", "2.8.1.2", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_INTERFACE, {"VARIABLE_INTERFACE", "2.8.2.1", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::VARIABLE_INITIAL_VALUE, {"VARIABLE_INITIAL_VALUE", "2.8.2.2", baseSpecificationUrl, "specB08"}},
    {Issue::ReferenceRule::RESET_ATTRIBUTE, {"RESET_ATTRIBUTE", "2.9", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_VARIABLE_REF, {"RESET_VARIABLE_REF", "2.9.1.1", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_TEST_VARIABLE_REF, {"RESET_TEST_VARIABLE_REF", "2.9.1.2", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_ORDER, {"RESET_ORDER", "2.9.1.3", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_CHILD, {"RESET_CHILD", "2.9.2", baseSpecificationUrl, "specB09"}},
    {Issue::ReferenceRule::RESET_TEST_VALUE, {"RESET_TEST_VALUE", "2.10", baseSpecificationUrl, "specB10"}},
    {Issue::ReferenceRule::RESET_RESET_VALUE, {"RESET_RESET_VALUE", "2.11", baseSpecificationUrl, "specB11"}},
    {Issue::ReferenceRule::MATH_MATHML, {"MATH_MATHML", "2.12.1", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CHILD, {"MATH_CHILD", "2.12.2", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CI, {"MATH_CI", "2.12.3", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CI_VARIABLE_REF, {"MATH_CI_VARIABLE_REF", "2.12.3", baseSpecificationUrl, "specB12"}},
    {Issue::ReferenceRule::MATH_CN_UNITS, {"MATH_CN_UNITS", "2.12.4", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::MATH_CN_BASE10, {"MATH_CN_BASE10", "2.12.5", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::MATH_CN_FORMAT, {"MATH_CN_FORMAT", "2.12.5", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::ENCAPSULATION_ATTRIBUTE, {"ENCAPSULATION_ATTRIBUTE", "2.13", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::ENCAPSULATION_CHILD, {"ENCAPSULATION_CHILD", "2.13.1", baseSpecificationUrl, "specB13"}},
    {Issue::ReferenceRule::COMPONENT_REF_COMPONENT, {"COMPONENT_REF_COMPONENT", "2.14.1", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::COMPONENT_REF_CHILD, {"COMPONENT_REF_CHILD", "2.14.2", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::CONNECTION_ATTRIBUTE, {"CONNECTION_ATTRIBUTE", "2.15", baseSpecificationUrl, "specB14"}},
    {Issue::ReferenceRule::CONNECTION_COMPONENT1, {"CONNECTION_COMPONENT1", "2.15.1", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_COMPONENT2, {"CONNECTION_COMPONENT2", "2.15.2", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_EXCLUDE_SELF, {"CONNECTION_EXCLUDE_SELF", "2.15.3", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_UNIQUE, {"CONNECTION_UNIQUE", "2.15.4", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::CONNECTION_CHILD, {"CONNECTION_CHILD", "2.15.5", baseSpecificationUrl, "specB15"}},
    {Issue::ReferenceRule::MAP_VARIABLES_ATTRIBUTE, {"MAP_VARIABLES_ATTRIBUTE", "2.16", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1, {"MAP_VARIABLES_VARIABLE1", "2.16.1", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2, {"MAP_VARIABLES_VARIABLE2", "2.16.2", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_UNIQUE, {"MAP_VARIABLES_UNIQUE", "2.16.3", baseSpecificationUrl, "specB16"}},
    {Issue::ReferenceRule::MAP_VARIABLES_AVAILABLE_INTERFACE, {"MAP_VARIABLES_AVAILABLE_INTERFACE", "3.10.8", baseSpecificationUrl, "specC10"}},
    {Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, {"MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION", "3.10.9", baseSpecificationUrl, "specC10"}},

    // Importer and Validator
    {Issue::ReferenceRule::INVALID_ARGUMENT, {"INVALID_ARGUMENT", "", docsUrl, ""}},

    // Importer class issues:
    {Issue::ReferenceRule::IMPORTER_ERROR_IMPORTING_UNITS, {"IMPORTER_ERROR_IMPORTING_UNITS", "", docsUrl, ""}},
    {Issue::ReferenceRule::IMPORTER_MISSING_FILE, {"IMPORTER_MISSING_FILE", "", docsUrl, ""}},
    {Issue::ReferenceRule::IMPORTER_MISSING_COMPONENT, {"IMPORTER_MISSING_COMPONENT", "", docsUrl, ""}},
    {Issue::ReferenceRule::IMPORTER_MISSING_UNITS, {"IMPORTER_MISSING_UNITS", "", docsUrl, ""}},
    {Issue::ReferenceRule::IMPORTER_NULL_MODEL, {"IMPORTER_NULL_MODEL", "", docsUrl, ""}},

    // Analyser issues:
    {Issue::ReferenceRule::ANALYSER_UNITS, {"ANALYSER_UNITS", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_UNLINKED_UNITS, {"ANALYSER_UNLINKED_UNITS", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE, {"ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION, {"ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_VOI_INITIALISED, {"ANALYSER_VOI_INITIALISED", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_VOI_SEVERAL, {"ANALYSER_VOI_SEVERAL", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER, {"ANALYSER_ODE_NOT_FIRST_ORDER", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED, {"ANALYSER_VARIABLE_UNUSED", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_STATE_NOT_INITIALISED, {"ANALYSER_STATE_NOT_INITIALISED", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE, {"ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL, {"ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI, {"ANALYSER_EXTERNAL_VARIABLE_VOI", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE, {"ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE", "", docsUrl, ""}},

    // Annotator issues:
    {Issue::ReferenceRule::ANNOTATOR_ID_NOT_FOUND, {"ANNOTATOR_ID_NOT_FOUND", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANNOTATOR_ID_NOT_UNIQUE, {"ANNOTATOR_ID_NOT_UNIQUE", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANNOTATOR_NO_MODEL, {"ANNOTATOR_NO_MODEL", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANNOTATOR_INCONSISTENT_TYPE, {"ANNOTATOR_INCONSISTENT_TYPE", "", docsUrl, ""}},
    {Issue::ReferenceRule::ANNOTATOR_NULL_MODEL, {"ANNOTATOR_NULL_MODEL", "", docsUrl, ""}},

};

std::string Issue::referenceHeading() const
{
    return ruleToInformation.find(referenceRule())->second[1];
}

std::string Issue::url() const
{
    auto search = ruleToInformation.find(referenceRule());

    if (search->second[1].empty()) {
        return search->second[2] + "?issue=" + search->second[0];
    }

    return search->second[2] + search->second[3] + ".html?issue=" + search->second[0];
}

} // namespace libcellml
