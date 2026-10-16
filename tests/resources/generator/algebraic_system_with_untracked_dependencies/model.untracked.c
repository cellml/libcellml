/* The content of this file was generated using the C profile of libCellML 0.7.1. */

#include "model.untracked.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.7.1";

const size_t STATE_COUNT = 3;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_VARIABLE_COUNT = 3;

const VariableInfo VOI_INFO = {"t", "dimensionless", "my_component"};

const VariableInfo STATE_INFO[] = {
    {"z", "dimensionless", "my_component"},
    {"v", "dimensionless", "my_component"},
    {"x", "dimensionless", "my_component"}
};

const VariableInfo CONSTANT_INFO[] = {
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
    {"y", "dimensionless", "my_component"},
    {"a", "dimensionless", "my_component"},
    {"w", "dimensionless", "my_component"}
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

    algebraicVariables[2] = u[0];
    algebraicVariables[0] = u[1];

    double my_component_k = 2.0;
    double my_component_kc = 2.0*my_component_k;
    double my_component_kc2 = 3.0*my_component_kc;
    double my_component_r = 3.0*rates[2]+states[2];
    double my_component_q = my_component_r+1.0;

    f[0] = algebraicVariables[0]+algebraicVariables[2]-(3.0*states[2]+my_component_kc2);
    f[1] = algebraicVariables[0]-algebraicVariables[2]*exp(algebraicVariables[2])-(my_component_q+states[2]);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraicVariables };
    double u[2];

    u[0] = algebraicVariables[2];
    u[1] = algebraicVariables[0];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraicVariables[2] = u[0];
    algebraicVariables[0] = u[1];
}

void initialiseArrays(double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    states[0] = 0.0;
    states[1] = 0.0;
    states[2] = 1.0;
    algebraicVariables[0] = 0.0;
    algebraicVariables[2] = 0.0;
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    rates[2] = -states[2];
    findRoot0(voi, states, rates, constants, computedConstants, algebraicVariables);
    rates[0] = algebraicVariables[0];
    double my_component_l = states[2]+1.0;
    algebraicVariables[1] = 2.0*my_component_l+algebraicVariables[0];
    rates[1] = algebraicVariables[1];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
}
