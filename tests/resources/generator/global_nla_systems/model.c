/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 2;
const size_t CONSTANT_COUNT = 4;
const size_t COMPUTED_CONSTANT_COUNT = 1;
const size_t ALGEBRAIC_VARIABLE_COUNT = 16;

const VariableInfo VOI_INFO = {"t", "second", "main"};

const VariableInfo STATE_INFO[] = {
    {"q_2", "coulomb", "main"},
    {"x", "dimensionless", "main"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"C_q_2", "coulomb_squared_per_joule", "main"},
    {"R_R_1", "joule_second_per_coulomb_squared", "main"},
    {"R_R_3", "joule_second_per_coulomb_squared", "main"},
    {"u_S_u", "joule_per_coulomb", "main"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"u_0", "joule_per_coulomb", "main"}
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
    {"v_q_2", "coulomb_per_second", "main"},
    {"u_q_2", "joule_per_coulomb", "main"},
    {"u_R_1", "joule_per_coulomb", "main"},
    {"v_R_1", "coulomb_per_second", "main"},
    {"u_R_3", "joule_per_coulomb", "main"},
    {"v_R_3", "coulomb_per_second", "main"},
    {"v_0", "coulomb_per_second", "main"},
    {"v_S_u", "coulomb_per_second", "main"},
    {"u_2", "joule_per_coulomb", "main"},
    {"u_3", "joule_per_coulomb", "main"},
    {"v_1", "coulomb_per_second", "main"},
    {"time", "second", "main"},
    {"v_2", "coulomb_per_second", "main"},
    {"v_3", "coulomb_per_second", "main"},
    {"z_1", "dimensionless", "main"},
    {"z_0", "dimensionless", "main"}
};

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

    algebraicVariables[14] = u[0];

    f[0] = algebraicVariables[14]-(-1.0+pow(algebraicVariables[14], 2.0));
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraicVariables };
    double u[1];

    u[0] = algebraicVariables[14];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraicVariables[14] = u[0];
}

void initialiseArrays(double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    states[0] = 0.0;
    states[1] = 0.0;
    constants[0] = 4.0;
    constants[1] = 4.0;
    constants[2] = 4.0;
    constants[3] = 12.0;
    algebraicVariables[14] = 0.0;
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = constants[3];
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    algebraicVariables[11] = voi;
    algebraicVariables[1] = states[0]/constants[0];
    algebraicVariables[9] = algebraicVariables[1];
    algebraicVariables[2] = states[1]*algebraicVariables[9]*constants[1]/(-constants[2]-states[1]*constants[1])-states[1]*computedConstants[0]*constants[1]/(-constants[2]-states[1]*constants[1]);
    algebraicVariables[3] = algebraicVariables[2]/constants[1];
    algebraicVariables[10] = algebraicVariables[3]/states[1];
    algebraicVariables[13] = algebraicVariables[10];
    algebraicVariables[12] = algebraicVariables[13];
    algebraicVariables[0] = algebraicVariables[12]*algebraicVariables[11]/voi;
    rates[0] = algebraicVariables[0];
    rates[1] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    algebraicVariables[1] = states[0]/constants[0];
    algebraicVariables[9] = algebraicVariables[1];
    algebraicVariables[2] = states[1]*algebraicVariables[9]*constants[1]/(-constants[2]-states[1]*constants[1])-states[1]*computedConstants[0]*constants[1]/(-constants[2]-states[1]*constants[1]);
    algebraicVariables[3] = algebraicVariables[2]/constants[1];
    algebraicVariables[8] = computedConstants[0]-algebraicVariables[2];
    algebraicVariables[4] = algebraicVariables[8]-algebraicVariables[9];
    algebraicVariables[5] = algebraicVariables[4]/constants[2];
    algebraicVariables[10] = algebraicVariables[3]/states[1];
    algebraicVariables[6] = algebraicVariables[10];
    algebraicVariables[7] = -algebraicVariables[6];
    algebraicVariables[13] = algebraicVariables[10];
    algebraicVariables[12] = algebraicVariables[13];
    algebraicVariables[0] = algebraicVariables[12]*algebraicVariables[11]/voi;
    findRoot0(voi, states, rates, constants, computedConstants, algebraicVariables);
    algebraicVariables[15] = pow(algebraicVariables[14], 2.0);
}
