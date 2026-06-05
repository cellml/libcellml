/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 1;
const size_t CONSTANT_COUNT = 15;
const size_t COMPUTED_CONSTANT_COUNT = 26;
const size_t ALGEBRAIC_VARIABLE_COUNT = 2;

const VariableInfo VOI_INFO = {"t", "dimensionless", "nla_with_variable_of_integration"};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "nla_with_variable_of_integration"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"b", "dimensionless", "not_greater_than_rearrangement"},
    {"a", "dimensionless", "not_greater_than_rearrangement"},
    {"b", "dimensionless", "opaque_logical_equation"},
    {"a", "dimensionless", "opaque_logical_equation"},
    {"a", "dimensionless", "non_integer_power_rearrangement"},
    {"b", "dimensionless", "boolean_rearrangement"},
    {"a", "dimensionless", "boolean_rearrangement"},
    {"y", "dimensionless", "nan_rearrangement"},
    {"c", "dimensionless", "not_xor_rearrangement"},
    {"b", "dimensionless", "not_xor_rearrangement"},
    {"a", "dimensionless", "not_xor_rearrangement"},
    {"a", "dimensionless", "nested_equality_convert_to_eq_type"},
    {"b", "dimensionless", "nested_equality_convert_to_eq_type"},
    {"u", "dimensionless", "tearing_variable_tiebreaker_uses_match_making"},
    {"v", "dimensionless", "tearing_variable_tiebreaker_uses_match_making"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"x", "dimensionless", "not_greater_than_rearrangement"},
    {"x", "dimensionless", "non_integer_power_rearrangement"},
    {"x", "dimensionless", "piecewise_substitution"},
    {"b", "dimensionless", "piecewise_substitution"},
    {"y1", "dimensionless", "boolean_rearrangement"},
    {"y2", "dimensionless", "boolean_rearrangement"},
    {"y3", "dimensionless", "boolean_rearrangement"},
    {"y4", "dimensionless", "boolean_rearrangement"},
    {"y5", "dimensionless", "boolean_rearrangement"},
    {"y6", "dimensionless", "boolean_rearrangement"},
    {"x", "dimensionless", "nan_rearrangement"},
    {"x", "dimensionless", "not_xor_rearrangement"},
    {"y", "dimensionless", "nested_equality_convert_to_eq_type"},
    {"e", "dimensionless", "invert_simple_odd_power_edge_cases"},
    {"w", "dimensionless", "invert_simple_odd_power_edge_cases"},
    {"z", "dimensionless", "invert_simple_odd_power_edge_cases"},
    {"y", "dimensionless", "invert_simple_odd_power_edge_cases"},
    {"g", "dimensionless", "invert_simple_odd_power_edge_cases"},
    {"a", "dimensionless", "scientific_notation"},
    {"x", "dimensionless", "power_with_pi_base"},
    {"a", "dimensionless", "power_with_pi_base"},
    {"x", "dimensionless", "swap_rhs_variable_piecewise"},
    {"w", "dimensionless", "tearing_variable_tiebreaker_uses_match_making"},
    {"z", "dimensionless", "tearing_variable_tiebreaker_uses_match_making"},
    {"x", "dimensionless", "tearing_variable_tiebreaker_uses_match_making"},
    {"y", "dimensionless", "tearing_variable_tiebreaker_uses_match_making"}
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
    {"y", "dimensionless", "opaque_logical_equation"},
    {"y", "dimensionless", "nla_with_variable_of_integration"}
};

double xor(double x, double y)
{
    return (x != 0.0) ^ (y != 0.0);
}

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createConstantsArray()
{
    double *res = (double *) malloc(CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createComputedConstantsArray()
{
    double *res = (double *) malloc(COMPUTED_CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < COMPUTED_CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createAlgebraicVariablesArray()
{
    double *res = (double *) malloc(ALGEBRAIC_VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

typedef struct {
    double voi;
    double *states;
    double *rates;
    double *constants;
    double *computedConstants;
    double *algebraicVariables;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraicVariables = ((RootFindingInfo *) data)->algebraicVariables;

    algebraicVariables[0] = u[0];

    f[0] = (constants[3] && constants[2])-(algebraicVariables[0]+1.0);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraicVariables };
    double u[1];

    u[0] = algebraicVariables[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraicVariables[0] = u[0];
}

void objectiveFunction1(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraicVariables = ((RootFindingInfo *) data)->algebraicVariables;

    algebraicVariables[1] = u[0];

    f[0] = sin(algebraicVariables[1])+voi+algebraicVariables[1]-1.0;
}

void findRoot1(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraicVariables };
    double u[1];

    u[0] = algebraicVariables[1];

    nlaSolve(objectiveFunction1, u, 1, &rfi);

    algebraicVariables[1] = u[0];
}

void initialiseArrays(double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    states[0] = 0.0;
    constants[0] = 3.0;
    constants[1] = 1.0;
    constants[2] = 1.0;
    constants[3] = 0.0;
    constants[4] = 4.0;
    constants[5] = 2.0;
    constants[6] = 1.0;
    constants[7] = 1.0;
    constants[8] = 3.0;
    constants[9] = 2.0;
    constants[10] = 1.0;
    constants[11] = 1.0;
    constants[12] = 1.0;
    constants[13] = 1.0;
    constants[14] = 2.0;
    computedConstants[2] = (1.0)?2.0:0.0;
    computedConstants[3] = 1.0+((1.0)?2.0:0.0);
    computedConstants[14] = 3.0;
    computedConstants[16] = 2.0;
    computedConstants[18] = -1.0e+18;
    computedConstants[19] = 2.0;
    computedConstants[21] = (1.0)?2.0:0.0;
    algebraicVariables[0] = 0.0;
    algebraicVariables[1] = 0.0;
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = constants[1] <= constants[0];
    computedConstants[1] = pow(constants[4], 2.5);
    computedConstants[4] = constants[6] != constants[5];
    computedConstants[5] = constants[6] < constants[5];
    computedConstants[6] = constants[6] <= constants[5];
    computedConstants[7] = (0.0 < constants[6]) && (0.0 < constants[5]);
    computedConstants[8] = (0.0 < constants[6]) || (0.0 < constants[5]);
    computedConstants[9] = xor(0.0 < constants[6], 0.0 < constants[5]);
    constants[7]/(-1.0+NAN) = computedConstants[10];
    computedConstants[11] = !xor(constants[9] < constants[8], constants[9] < constants[10]);
    computedConstants[12] = (0.0 < constants[11]) && (constants[11] == constants[12]);
    computedConstants[13] = -5.0+pow(2.0, computedConstants[14]);
    computedConstants[15] = -5.0+pow(computedConstants[16], 3.0);
    computedConstants[17] = 1.0/computedConstants[14];
    computedConstants[20] = -pow(3.14159265358979, computedConstants[19]);
    computedConstants[25] = 3.0-constants[14];
    computedConstants[22] = 4.0-computedConstants[25]-constants[13];
    computedConstants[24] = 2.0-constants[14]-constants[13];
    computedConstants[23] = -computedConstants[24]-computedConstants[22];
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    findRoot0(voi, states, rates, constants, computedConstants, algebraicVariables);
    findRoot1(voi, states, rates, constants, computedConstants, algebraicVariables);
}
