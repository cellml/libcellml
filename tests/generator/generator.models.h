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

#pragma once

#if defined(_MSC_VER) && !defined(__clang__)
#    pragma warning(push)
#    pragma warning(disable : 4100)
#elif defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wunused-parameter"
#else
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wunused-parameter"
#    pragma clang diagnostic ignored "-Wunused-variable"
#endif

namespace algebraic_eqn_computed_var_on_rhs {
#include "../resources/generator/algebraic_eqn_computed_var_on_rhs/model.c"
} // namespace algebraic_eqn_computed_var_on_rhs

namespace algebraic_eqn_computed_var_on_rhs_external {
ALGEBRAIC_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/algebraic_eqn_computed_var_on_rhs/model.external.c"
} // namespace algebraic_eqn_computed_var_on_rhs_external

namespace algebraic_eqn_const_var_on_rhs {
#include "../resources/generator/algebraic_eqn_const_var_on_rhs/model.c"
} // namespace algebraic_eqn_const_var_on_rhs

namespace algebraic_eqn_constant_on_rhs {
#include "../resources/generator/algebraic_eqn_constant_on_rhs/model.c"
} // namespace algebraic_eqn_constant_on_rhs

namespace algebraic_eqn_derivative_on_rhs {
#include "../resources/generator/algebraic_eqn_derivative_on_rhs/model.c"
} // namespace algebraic_eqn_derivative_on_rhs

namespace algebraic_eqn_derivative_on_rhs_one_component {
#include "../resources/generator/algebraic_eqn_derivative_on_rhs_one_component/model.c"
} // namespace algebraic_eqn_derivative_on_rhs_one_component

namespace algebraic_eqn_state_var_on_rhs {
#include "../resources/generator/algebraic_eqn_state_var_on_rhs/model.c"
} // namespace algebraic_eqn_state_var_on_rhs

namespace algebraic_eqn_state_var_on_rhs_one_component {
#include "../resources/generator/algebraic_eqn_state_var_on_rhs_one_component/model.c"
} // namespace algebraic_eqn_state_var_on_rhs_one_component

namespace algebraic_unknown_var_on_rhs {
#include "../resources/generator/algebraic_unknown_var_on_rhs/model.c"
} // namespace algebraic_unknown_var_on_rhs

namespace algebraic_eqn_with_one_non_isolated_unknown {
NLA_SOLVE_METHOD
#include "../resources/generator/algebraic_eqn_with_one_non_isolated_unknown/model.c"
} // namespace algebraic_eqn_with_one_non_isolated_unknown

namespace algebraic_eqn_with_one_non_isolated_unknown_external {
NLA_SOLVE_METHOD
ALGEBRAIC_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.c"
} // namespace algebraic_eqn_with_one_non_isolated_unknown_external

namespace algebraic_system_with_three_linked_unknowns {
NLA_SOLVE_METHOD
#include "../resources/generator/algebraic_system_with_three_linked_unknowns/model.c"
} // namespace algebraic_system_with_three_linked_unknowns

namespace algebraic_system_with_three_linked_unknowns_external {
ALGEBRAIC_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/algebraic_system_with_three_linked_unknowns/model.external.c"
} // namespace algebraic_system_with_three_linked_unknowns_external

namespace algebraic_system_with_various_dependencies_ordered {
NLA_SOLVE_METHOD
#include "../resources/generator/algebraic_system_with_various_dependencies/model.ordered.c"
} // namespace algebraic_system_with_various_dependencies_ordered

namespace algebraic_system_with_various_dependencies_not_ordered {
NLA_SOLVE_METHOD
#include "../resources/generator/algebraic_system_with_various_dependencies/model.not.ordered.c"
} // namespace algebraic_system_with_various_dependencies_not_ordered

namespace ode_computed_var_on_rhs {
#include "../resources/generator/ode_computed_var_on_rhs/model.c"
} // namespace ode_computed_var_on_rhs

namespace ode_computed_var_on_rhs_one_component {
#include "../resources/generator/ode_computed_var_on_rhs_one_component/model.c"
} // namespace ode_computed_var_on_rhs_one_component

namespace ode_const_var_on_rhs {
#include "../resources/generator/ode_const_var_on_rhs/model.c"
} // namespace ode_const_var_on_rhs

namespace ode_const_var_on_rhs_one_component {
#include "../resources/generator/ode_const_var_on_rhs_one_component/model.c"
} // namespace ode_const_var_on_rhs_one_component

namespace ode_constant_on_rhs {
#include "../resources/generator/ode_constant_on_rhs/model.c"
} // namespace ode_constant_on_rhs

namespace ode_constant_on_rhs_one_component {
#include "../resources/generator/ode_constant_on_rhs_one_component/model.c"
} // namespace ode_constant_on_rhs_one_component

namespace ode_multiple_dependent_odes {
#include "../resources/generator/ode_multiple_dependent_odes/model.c"
} // namespace ode_multiple_dependent_odes

namespace ode_multiple_dependent_odes_one_component {
#include "../resources/generator/ode_multiple_dependent_odes_one_component/model.c"
} // namespace ode_multiple_dependent_odes_one_component

namespace ode_multiple_odes_with_same_name {
#include "../resources/generator/ode_multiple_odes_with_same_name/model.c"
} // namespace ode_multiple_odes_with_same_name

namespace ode_unknown_var_on_rhs {
#include "../resources/generator/ode_unknown_var_on_rhs/model.c"
} // namespace ode_unknown_var_on_rhs

namespace cellml_mappings_and_encapsulations {
#include "../resources/generator/cellml_mappings_and_encapsulations/model.c"
} // namespace cellml_mappings_and_encapsulations

namespace cellml_state_initialised_using_variable {
#include "../resources/generator/cellml_state_initialised_using_variable/model.c"
} // namespace cellml_state_initialised_using_variable

namespace cellml_unit_scaling_voi_indirect {
#include "../resources/generator/cellml_unit_scaling_voi_indirect/model.c"
} // namespace cellml_unit_scaling_voi_indirect

namespace cellml_unit_scaling_voi_direct {
#include "../resources/generator/cellml_unit_scaling_voi_direct/model.c"
} // namespace cellml_unit_scaling_voi_direct

namespace cellml_unit_scaling_constant {
#include "../resources/generator/cellml_unit_scaling_constant/model.c"
} // namespace cellml_unit_scaling_constant

namespace cellml_unit_scaling_state {
#include "../resources/generator/cellml_unit_scaling_state/model.c"
} // namespace cellml_unit_scaling_state

namespace cellml_unit_scaling_state_initialised_using_constant {
#include "../resources/generator/cellml_unit_scaling_state_initialised_using_constant/model.c"
} // namespace cellml_unit_scaling_state_initialised_using_constant

namespace cellml_unit_scaling_state_initialised_using_variable {
#include "../resources/generator/cellml_unit_scaling_state_initialised_using_variable/model.c"
} // namespace cellml_unit_scaling_state_initialised_using_variable

namespace cellml_unit_scaling_rate {
#include "../resources/generator/cellml_unit_scaling_rate/model.c"
} // namespace cellml_unit_scaling_rate

namespace dependent_eqns {
#include "../resources/generator/dependent_eqns/model.c"
} // namespace dependent_eqns

namespace cell_geometry_model {
#include "../resources/generator/cell_geometry_model/model.c"
} // namespace cell_geometry_model

namespace cell_geometry_model_external {
ALGEBRAIC_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/cell_geometry_model/model.external.c"
} // namespace cell_geometry_model_external

namespace fabbri_fantini_wilders_severi_human_san_model_2017 {
#include "../resources/generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"
} // namespace fabbri_fantini_wilders_severi_human_san_model_2017

namespace garny_kohl_hunter_boyett_noble_rabbit_san_model_2003 {
#include "../resources/generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"
} // namespace garny_kohl_hunter_boyett_noble_rabbit_san_model_2003

namespace hodgkin_huxley_squid_axon_model_1952 {
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.c"
} // namespace hodgkin_huxley_squid_axon_model_1952

namespace hodgkin_huxley_squid_axon_model_1952_state_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.state.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_state_external

namespace hodgkin_huxley_squid_axon_model_1952_dependent_state_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_dependent_state_external

namespace hodgkin_huxley_squid_axon_model_1952_constant_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.constant.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_constant_external

namespace hodgkin_huxley_squid_axon_model_1952_dependent_constant_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_dependent_constant_external

namespace hodgkin_huxley_squid_axon_model_1952_computed_constant_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_computed_constant_external

namespace hodgkin_huxley_squid_axon_model_1952_dependent_computed_constant_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_dependent_computed_constant_external

namespace hodgkin_huxley_squid_axon_model_1952_algebraic_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_algebraic_external

namespace hodgkin_huxley_squid_axon_model_1952_dependent_algebraic_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_dependent_algebraic_external

namespace hodgkin_huxley_squid_axon_model_1952_external {
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_external

namespace hodgkin_huxley_squid_axon_model_1952_dae {
NLA_SOLVE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.dae.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_dae

namespace hodgkin_huxley_squid_axon_model_1952_dae_external {
NLA_SOLVE_METHOD
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/hodgkin_huxley_squid_axon_model_1952/model.dae.external.c"
} // namespace hodgkin_huxley_squid_axon_model_1952_dae_external

namespace noble_model_1962 {
#include "../resources/generator/noble_model_1962/model.c"
} // namespace noble_model_1962

namespace robertson_model_1966_ode {
#include "../resources/generator/robertson_model_1966/model.ode.c"
} // namespace robertson_model_1966_ode

namespace robertson_model_1966_dae {
NLA_SOLVE_METHOD
#include "../resources/generator/robertson_model_1966/model.dae.c"
} // namespace robertson_model_1966_dae

namespace sine_model_imports {
#include "../resources/generator/sine_model_imports/model.c"
} // namespace sine_model_imports

namespace dae_cellml_1_1_model {
NLA_SOLVE_METHOD
#include "../resources/generator/dae_cellml_1_1_model/model.c"
} // namespace dae_cellml_1_1_model

namespace variable_initialised_using_a_constant {
NLA_SOLVE_METHOD
#include "../resources/generator/variable_initialised_using_a_constant/model.c"
} // namespace variable_initialised_using_a_constant

namespace unknown_variable_as_external_variable {
ALGEBRAIC_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/generator/unknown_variable_as_external_variable/model.c"
} // namespace unknown_variable_as_external_variable

namespace cellml_slc_example {
#include "../resources/generator/cellml_slc_example/model.c"
} // namespace cellml_slc_example

namespace coverage {
NLA_SOLVE_METHOD
DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD
#include "../resources/coverage/generator/model.xor.c"
} // namespace coverage

#if defined(_MSC_VER) && !defined(__clang__)
#    pragma warning(pop)
#elif defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic pop
#else
#    pragma clang diagnostic pop
#endif
