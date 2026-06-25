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

#include "gtest/gtest.h"

#include <libcellml>

TEST(AsString, issueLevel)
{
    EXPECT_EQ("error", libcellml::Issue::levelAsString(libcellml::Issue::Level::ERROR));
    EXPECT_EQ("message", libcellml::Issue::levelAsString(libcellml::Issue::Level::MESSAGE));
    EXPECT_EQ("warning", libcellml::Issue::levelAsString(libcellml::Issue::Level::WARNING));
}

TEST(AsString, issueReferenceRule)
{
    EXPECT_EQ("", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNDEFINED));
    EXPECT_EQ("xml", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::XML));
    EXPECT_EQ("xml_unexpected_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::XML_UNEXPECTED_ELEMENT));
    EXPECT_EQ("xml_unexpected_character", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::XML_UNEXPECTED_CHARACTER));
    EXPECT_EQ("xml_unexpected_namespace", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::XML_UNEXPECTED_NAMESPACE));
    EXPECT_EQ("xml_attribute_has_namespace", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::XML_ATTRIBUTE_HAS_NAMESPACE));
    EXPECT_EQ("xml_id_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::XML_ID_ATTRIBUTE));
    EXPECT_EQ("model_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MODEL_ELEMENT));
    EXPECT_EQ("model_name", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MODEL_NAME));
    EXPECT_EQ("model_name_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MODEL_NAME_VALUE));
    EXPECT_EQ("model_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MODEL_CHILD));
    EXPECT_EQ("model_more_than_one_encapsulation", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION));
    EXPECT_EQ("import_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_ELEMENT));
    EXPECT_EQ("import_href", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_HREF));
    EXPECT_EQ("import_href_locator", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_HREF_LOCATOR));
    EXPECT_EQ("import_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_CHILD));
    EXPECT_EQ("import_equivalent_infoset", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_EQUIVALENT_INFOSET));
    EXPECT_EQ("import_units_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_UNITS_ELEMENT));
    EXPECT_EQ("import_component_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_ELEMENT));
    EXPECT_EQ("import_component_name", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME));
    EXPECT_EQ("import_component_name_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME_VALUE));
    EXPECT_EQ("import_component_name_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME_UNIQUE));
    EXPECT_EQ("import_component_component_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REFERENCE));
    EXPECT_EQ("import_component_component_reference_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REFERENCE_VALUE));
    EXPECT_EQ("import_component_component_reference_target", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REFERENCE_TARGET));
    EXPECT_EQ("units_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNITS_ELEMENT));
    EXPECT_EQ("units_name", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNITS_NAME));
    EXPECT_EQ("units_name_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNITS_NAME_VALUE));
    EXPECT_EQ("units_standard", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNITS_STANDARD));
    EXPECT_EQ("units_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNITS_CHILD));
    EXPECT_EQ("unit_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_ELEMENT));
    EXPECT_EQ("unit_units", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_UNITS));
    EXPECT_EQ("unit_units_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_UNITS_REFERENCE));
    EXPECT_EQ("unit_units_circular_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_UNITS_CIRCULAR_REFERENCE));
    EXPECT_EQ("unit_attribute_optional", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_ATTRIBUTE_OPTIONAL));
    EXPECT_EQ("unit_attribute_prefix_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_ATTRIBUTE_PREFIX_VALUE));
    EXPECT_EQ("unit_attribute_multiplier_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_ATTRIBUTE_MULTIPLIER_VALUE));
    EXPECT_EQ("unit_attribute_exponent_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNIT_ATTRIBUTE_EXPONENT_VALUE));
    EXPECT_EQ("component_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_ELEMENT));
    EXPECT_EQ("component_name", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_NAME));
    EXPECT_EQ("component_name_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_NAME_VALUE));
    EXPECT_EQ("component_name_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_NAME_UNIQUE));
    EXPECT_EQ("component_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_CHILD));
    EXPECT_EQ("variable_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_ELEMENT));
    EXPECT_EQ("variable_attribute_required", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_ATTRIBUTE_REQUIRED));
    EXPECT_EQ("variable_name_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_NAME_VALUE));
    EXPECT_EQ("variable_name_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_NAME_UNIQUE));
    EXPECT_EQ("variable_units_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_UNITS_VALUE));
    EXPECT_EQ("variable_attribute_optional", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_ATTRIBUTE_OPTIONAL));
    EXPECT_EQ("variable_interface_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_INTERFACE_VALUE));
    EXPECT_EQ("variable_initial_value_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE_VALUE));
    EXPECT_EQ("reset_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_ELEMENT));
    EXPECT_EQ("reset_attribute_required", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_ATTRIBUTE_REQUIRED));
    EXPECT_EQ("reset_variable_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_VARIABLE_REFERENCE));
    EXPECT_EQ("reset_test_variable_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_TEST_VARIABLE_REFERENCE));
    EXPECT_EQ("reset_order_value", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_ORDER_VALUE));
    EXPECT_EQ("reset_order_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_ORDER_UNIQUE));
    EXPECT_EQ("reset_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_CHILD));
    EXPECT_EQ("reset_reset_value_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_RESET_VALUE_CHILD));
    EXPECT_EQ("reset_test_value_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_TEST_VALUE_CHILD));
    EXPECT_EQ("test_value_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::TEST_VALUE_ELEMENT));
    EXPECT_EQ("test_value_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::TEST_VALUE_CHILD));
    EXPECT_EQ("reset_value_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_VALUE_ELEMENT));
    EXPECT_EQ("reset_value_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::RESET_VALUE_CHILD));
    EXPECT_EQ("math_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_ELEMENT));
    EXPECT_EQ("math_mathml", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_MATHML));
    EXPECT_EQ("math_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_CHILD));
    EXPECT_EQ("math_ci_variable_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REFERENCE));
    EXPECT_EQ("math_cn_units_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_CN_UNITS_ATTRIBUTE));
    EXPECT_EQ("math_cn_units_attribute_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_CN_UNITS_ATTRIBUTE_REFERENCE));
    EXPECT_EQ("math_cn_base10", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_CN_BASE10));
    EXPECT_EQ("math_cn_format", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MATH_CN_FORMAT));
    EXPECT_EQ("encapsulation_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ENCAPSULATION_ELEMENT));
    EXPECT_EQ("encapsulation_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ENCAPSULATION_CHILD));
    EXPECT_EQ("component_ref_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_REF_ELEMENT));
    EXPECT_EQ("component_ref_component_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT_ATTRIBUTE));
    EXPECT_EQ("component_ref_component_attribute_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT_ATTRIBUTE_REFERENCE));
    EXPECT_EQ("component_ref_component_attribute_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT_ATTRIBUTE_UNIQUE));
    EXPECT_EQ("component_ref_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::COMPONENT_REF_CHILD));
    EXPECT_EQ("connection_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_ELEMENT));
    EXPECT_EQ("connection_component1_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT1_ATTRIBUTE));
    EXPECT_EQ("connection_component1_attribute_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT1_ATTRIBUTE_REFERENCE));
    EXPECT_EQ("connection_component2_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT2_ATTRIBUTE));
    EXPECT_EQ("connection_component2_attribute_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT2_ATTRIBUTE_REFERENCE));
    EXPECT_EQ("connection_exclude_self", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_EXCLUDE_SELF));
    EXPECT_EQ("connection_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_UNIQUE));
    EXPECT_EQ("connection_child", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::CONNECTION_CHILD));
    EXPECT_EQ("map_variables_element", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MAP_VARIABLES_ELEMENT));
    EXPECT_EQ("map_variables_variable1_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1_ATTRIBUTE));
    EXPECT_EQ("map_variables_variable1_attribute_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1_ATTRIBUTE_REFERENCE));
    EXPECT_EQ("map_variables_variable2_attribute", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2_ATTRIBUTE));
    EXPECT_EQ("map_variables_variable2_attribute_reference", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2_ATTRIBUTE_REFERENCE));
    EXPECT_EQ("map_variables_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::MAP_VARIABLES_UNIQUE));
    EXPECT_EQ("data_repr_identifier_at_least_one_alphanum", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM));
    EXPECT_EQ("data_repr_identifier_begin_euro_num", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM));
    EXPECT_EQ("data_repr_identifier_latin_alphanum", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM));
    EXPECT_EQ("invalid_argument", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::INVALID_ARGUMENT));
    EXPECT_EQ("importer_error_importing_units", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_ERROR_IMPORTING_UNITS));
    EXPECT_EQ("importer_missing_file", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_MISSING_FILE));
    EXPECT_EQ("importer_missing_component", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_MISSING_COMPONENT));
    EXPECT_EQ("importer_missing_units", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_MISSING_UNITS));
    EXPECT_EQ("importer_null_model", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_NULL_MODEL));
    EXPECT_EQ("importer_undefined_model", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_UNDEFINED_MODEL));
    EXPECT_EQ("importer_unresolved_imports", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::IMPORTER_UNRESOLVED_IMPORTS));
    EXPECT_EQ("analyser_equation_not_equality_statement", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_EQUATION_NOT_EQUALITY_STATEMENT));
    EXPECT_EQ("analyser_units", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_UNITS));
    EXPECT_EQ("analyser_unlinked_units", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_UNLINKED_UNITS));
    EXPECT_EQ("analyser_variable_initialised_more_than_once", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE));
    EXPECT_EQ("analyser_variable_initialised_using_algebraic_variable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_USING_ALGEBRAIC_VARIABLE));
    EXPECT_EQ("analyser_variable_initialised_using_variable_with_different_units", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_USING_VARIABLE_WITH_DIFFERENT_UNITS));
    EXPECT_EQ("analyser_voi_initialised", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VOI_INITIALISED));
    EXPECT_EQ("analyser_voi_several", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VOI_SEVERAL));
    EXPECT_EQ("analyser_ode_not_first_order", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER));
    EXPECT_EQ("analyser_variable_unused", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED));
    EXPECT_EQ("analyser_state_not_initialised", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_STATE_NOT_INITIALISED));
    EXPECT_EQ("analyser_state_rate_as_algebraic_variable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_STATE_RATE_AS_ALGEBRAIC_VARIABLE));
    EXPECT_EQ("analyser_variable_underconstrained", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNDERCONSTRAINED));
    EXPECT_EQ("analyser_variable_overconstrained", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_OVERCONSTRAINED));
    EXPECT_EQ("analyser_external_variable_different_model", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL));
    EXPECT_EQ("analyser_external_variable_voi", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI));
    EXPECT_EQ("analyser_external_variable_use_primary_variable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE));
    EXPECT_EQ("annotator_id_not_found", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANNOTATOR_ID_NOT_FOUND));
    EXPECT_EQ("annotator_id_not_unique", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANNOTATOR_ID_NOT_UNIQUE));
    EXPECT_EQ("annotator_no_model", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANNOTATOR_NO_MODEL));
    EXPECT_EQ("annotator_inconsistent_type", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANNOTATOR_INCONSISTENT_TYPE));
    EXPECT_EQ("annotator_null_model", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::ANNOTATOR_NULL_MODEL));
    EXPECT_EQ("generator_null_model", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_NULL_MODEL));
    EXPECT_EQ("generator_null_variable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_NULL_VARIABLE));
    EXPECT_EQ("generator_voi_variable_always_tracked", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_VOI_VARIABLE_ALWAYS_TRACKED));
    EXPECT_EQ("generator_voi_variable_not_untrackable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_VOI_VARIABLE_NOT_UNTRACKABLE));
    EXPECT_EQ("generator_state_variable_always_tracked", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_STATE_VARIABLE_ALWAYS_TRACKED));
    EXPECT_EQ("generator_state_variable_not_untrackable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_STATE_VARIABLE_NOT_UNTRACKABLE));
    EXPECT_EQ("generator_external_variable_always_tracked", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_EXTERNAL_VARIABLE_ALWAYS_TRACKED));
    EXPECT_EQ("generator_external_variable_not_untrackable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_EXTERNAL_VARIABLE_NOT_UNTRACKABLE));
    EXPECT_EQ("generator_nla_based_variable_always_tracked", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_ALWAYS_TRACKED));
    EXPECT_EQ("generator_nla_based_variable_not_untrackable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE));
    EXPECT_EQ("generator_externally_needed_variable_always_tracked", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_ALWAYS_TRACKED));
    EXPECT_EQ("generator_externally_needed_variable_not_untrackable", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE));
    EXPECT_EQ("unspecified", libcellml::Issue::referenceRuleAsString(libcellml::Issue::ReferenceRule::UNSPECIFIED));
}

TEST(AsString, unitsPrefix)
{
    EXPECT_EQ("atto", libcellml::Units::prefixAsString(libcellml::Units::Prefix::ATTO));
    EXPECT_EQ("centi", libcellml::Units::prefixAsString(libcellml::Units::Prefix::CENTI));
    EXPECT_EQ("deca", libcellml::Units::prefixAsString(libcellml::Units::Prefix::DECA));
    EXPECT_EQ("deci", libcellml::Units::prefixAsString(libcellml::Units::Prefix::DECI));
    EXPECT_EQ("exa", libcellml::Units::prefixAsString(libcellml::Units::Prefix::EXA));
    EXPECT_EQ("femto", libcellml::Units::prefixAsString(libcellml::Units::Prefix::FEMTO));
    EXPECT_EQ("giga", libcellml::Units::prefixAsString(libcellml::Units::Prefix::GIGA));
    EXPECT_EQ("hecto", libcellml::Units::prefixAsString(libcellml::Units::Prefix::HECTO));
    EXPECT_EQ("kilo", libcellml::Units::prefixAsString(libcellml::Units::Prefix::KILO));
    EXPECT_EQ("mega", libcellml::Units::prefixAsString(libcellml::Units::Prefix::MEGA));
    EXPECT_EQ("micro", libcellml::Units::prefixAsString(libcellml::Units::Prefix::MICRO));
    EXPECT_EQ("milli", libcellml::Units::prefixAsString(libcellml::Units::Prefix::MILLI));
    EXPECT_EQ("nano", libcellml::Units::prefixAsString(libcellml::Units::Prefix::NANO));
    EXPECT_EQ("peta", libcellml::Units::prefixAsString(libcellml::Units::Prefix::PETA));
    EXPECT_EQ("pico", libcellml::Units::prefixAsString(libcellml::Units::Prefix::PICO));
    EXPECT_EQ("tera", libcellml::Units::prefixAsString(libcellml::Units::Prefix::TERA));
    EXPECT_EQ("yocto", libcellml::Units::prefixAsString(libcellml::Units::Prefix::YOCTO));
    EXPECT_EQ("yotta", libcellml::Units::prefixAsString(libcellml::Units::Prefix::YOTTA));
    EXPECT_EQ("zepto", libcellml::Units::prefixAsString(libcellml::Units::Prefix::ZEPTO));
    EXPECT_EQ("zetta", libcellml::Units::prefixAsString(libcellml::Units::Prefix::ZETTA));
}

TEST(AsString, unitsStandardUnit)
{
    EXPECT_EQ("ampere", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::AMPERE));
    EXPECT_EQ("becquerel", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::BECQUEREL));
    EXPECT_EQ("candela", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::CANDELA));
    EXPECT_EQ("dimensionless", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::DIMENSIONLESS));
    EXPECT_EQ("kelvin", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::KELVIN));
    EXPECT_EQ("kilogram", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::KILOGRAM));
    EXPECT_EQ("metre", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::METRE));
    EXPECT_EQ("mole", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::MOLE));
    EXPECT_EQ("second", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::SECOND));
    EXPECT_EQ("coulomb", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::COULOMB));
    EXPECT_EQ("farad", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::FARAD));
    EXPECT_EQ("gram", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::GRAM));
    EXPECT_EQ("gray", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::GRAY));
    EXPECT_EQ("henry", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::HENRY));
    EXPECT_EQ("hertz", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::HERTZ));
    EXPECT_EQ("joule", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::JOULE));
    EXPECT_EQ("katal", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::KATAL));
    EXPECT_EQ("litre", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::LITRE));
    EXPECT_EQ("lumen", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::LUMEN));
    EXPECT_EQ("lux", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::LUX));
    EXPECT_EQ("radian", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::RADIAN));
    EXPECT_EQ("newton", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::NEWTON));
    EXPECT_EQ("ohm", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::OHM));
    EXPECT_EQ("pascal", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::PASCAL));
    EXPECT_EQ("siemens", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::SIEMENS));
    EXPECT_EQ("sievert", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::SIEVERT));
    EXPECT_EQ("steradian", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::STERADIAN));
    EXPECT_EQ("tesla", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::TESLA));
    EXPECT_EQ("volt", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::VOLT));
    EXPECT_EQ("watt", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::WATT));
    EXPECT_EQ("weber", libcellml::Units::standardUnitAsString(libcellml::Units::StandardUnit::WEBER));
}

TEST(AsString, variableInterfaceType)
{
    EXPECT_EQ("none", libcellml::Variable::interfaceTypeAsString(libcellml::Variable::InterfaceType::NONE));
    EXPECT_EQ("public", libcellml::Variable::interfaceTypeAsString(libcellml::Variable::InterfaceType::PUBLIC));
    EXPECT_EQ("private", libcellml::Variable::interfaceTypeAsString(libcellml::Variable::InterfaceType::PRIVATE));
    EXPECT_EQ("public_and_private", libcellml::Variable::interfaceTypeAsString(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE));
}
