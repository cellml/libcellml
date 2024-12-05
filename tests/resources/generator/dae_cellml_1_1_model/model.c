/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 10;

const VariableInfo VOI_INFO = {"t", "second", "main", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"q_1", "coulomb", "main", STATE},
    {"v_3", "C_per_s", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"v_1", "C_per_s", "main", ALGEBRAIC},
    {"v_in", "C_per_s", "main", CONSTANT},
    {"v_2", "C_per_s", "main", ALGEBRAIC},
    {"v_out", "C_per_s", "main", CONSTANT},
    {"u_1", "J_per_C", "main", ALGEBRAIC},
    {"u_2", "J_per_C", "main", ALGEBRAIC},
    {"u_3", "J_per_C", "main", ALGEBRAIC},
    {"C", "C2_per_J", "main", CONSTANT},
    {"R", "Js_per_C2", "main", CONSTANT},
    {"L", "Js2_per_C2", "main", CONSTANT}
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createVariablesArray()
{
    double *res = (double *) malloc(VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
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
    double *variables;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[0] = u[0];

    f[0] = variables[1]-(variables[0]+variables[2]);
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    variables[0] = u[0];
}

void objectiveFunction1(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[6] = u[0];

    f[0] = variables[4]-(variables[5]+variables[6]);
}

void findRoot1(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[6];

    nlaSolve(objectiveFunction1, u, 1, &rfi);

    variables[6] = u[0];
}

void initialiseVariables(double *states, double *rates, double *variables)
{
    variables[0] = 0.0;
    variables[1] = 1.0;
    variables[3] = 1.0;
    variables[6] = 0.0;
    variables[7] = 20.0;
    variables[8] = 2.0;
    variables[9] = 10.0;
    states[0] = 1.0;
    states[1] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[2] = states[1]+variables[3];
    findRoot0(voi, states, rates, variables);
    rates[0] = variables[0];
    variables[4] = states[0]/variables[7];
    variables[5] = variables[8]*variables[2];
    findRoot1(voi, states, rates, variables);
    rates[1] = variables[6]/variables[9];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[2] = states[1]+variables[3];
    findRoot0(voi, states, rates, variables);
    variables[4] = states[0]/variables[7];
    variables[5] = variables[8]*variables[2];
    findRoot1(voi, states, rates, variables);
}
