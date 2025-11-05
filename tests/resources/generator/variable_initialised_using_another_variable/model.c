/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.7.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 22;
const size_t CONSTANT_COUNT = 2;
const size_t COMPUTED_CONSTANT_COUNT = 2;
const size_t ALGEBRAIC_COUNT = 22;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main"};

const VariableInfo STATE_INFO[] = {
    {"xStateStateCst", "dimensionless", "main"},
    {"kStateStateCst", "dimensionless", "main"},
    {"xStateStateCompCst", "dimensionless", "main"},
    {"kStateStateCompCst", "dimensionless", "main"},
    {"xStateStateState", "dimensionless", "main"},
    {"kStateStateState", "dimensionless", "main"},
    {"xStateStateNla", "dimensionless", "main"},
    {"kStateStateNla", "dimensionless", "main"},
    {"kNlaStateCst", "dimensionless", "main"},
    {"kNlaStateCompCst", "dimensionless", "main"},
    {"kNlaStateState", "dimensionless", "main"},
    {"kNlaStateNla", "dimensionless", "main"},
    {"xStateNlaCst", "dimensionless", "main"},
    {"xStateNlaCompCst", "dimensionless", "main"},
    {"xStateNlaState", "dimensionless", "main"},
    {"xStateNlaNla", "dimensionless", "main"},
    {"xStateCst", "dimensionless", "main"},
    {"xStateCompCst", "dimensionless", "main"},
    {"xStateState", "dimensionless", "main"},
    {"kStateState", "dimensionless", "main"},
    {"xStateNla", "dimensionless", "main"},
    {"kNlaState", "dimensionless", "main"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"kStateCst", "dimensionless", "main"},
    {"kNlaCst", "dimensionless", "main"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"kStateCompCst", "dimensionless", "main"},
    {"kNlaCompCst", "dimensionless", "main"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"xNlaStateCst", "dimensionless", "main"},
    {"xNlaStateCompCst", "dimensionless", "main"},
    {"xNlaStateState", "dimensionless", "main"},
    {"xNlaStateNla", "dimensionless", "main"},
    {"kStateNlaCst", "dimensionless", "main"},
    {"kStateNlaCompCst", "dimensionless", "main"},
    {"kStateNlaState", "dimensionless", "main"},
    {"kStateNlaNla", "dimensionless", "main"},
    {"xNlaNlaCst", "dimensionless", "main"},
    {"kNlaNlaCst", "dimensionless", "main"},
    {"xNlaNlaCompCst", "dimensionless", "main"},
    {"kNlaNlaCompCst", "dimensionless", "main"},
    {"xNlaNlaState", "dimensionless", "main"},
    {"kNlaNlaState", "dimensionless", "main"},
    {"xNlaNlaNla", "dimensionless", "main"},
    {"kNlaNlaNla", "dimensionless", "main"},
    {"kStateNla", "dimensionless", "main"},
    {"xNlaCst", "dimensionless", "main"},
    {"xNlaCompCst", "dimensionless", "main"},
    {"xNlaState", "dimensionless", "main"},
    {"xNlaNla", "dimensionless", "main"},
    {"kNlaNla", "dimensionless", "main"}
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

double * createAlgebraicArray()
{
    double *res = (double *) malloc(ALGEBRAIC_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_COUNT; ++i) {
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
    double *algebraic;
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
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[0] = u[0];

    f[0] = voi-algebraic[0];
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraic[0] = u[0];
}

void objectiveFunction1(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[1] = u[0];

    f[0] = voi-algebraic[1];
}

void findRoot1(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[1];

    nlaSolve(objectiveFunction1, u, 1, &rfi);

    algebraic[1] = u[0];
}

void objectiveFunction2(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[2] = u[0];

    f[0] = voi-algebraic[2];
}

void findRoot2(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[2];

    nlaSolve(objectiveFunction2, u, 1, &rfi);

    algebraic[2] = u[0];
}

void objectiveFunction3(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[3] = u[0];

    f[0] = voi-algebraic[3];
}

void findRoot3(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[3];

    nlaSolve(objectiveFunction3, u, 1, &rfi);

    algebraic[3] = u[0];
}

void objectiveFunction4(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[4] = u[0];

    f[0] = voi-algebraic[4];
}

void findRoot4(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[4];

    nlaSolve(objectiveFunction4, u, 1, &rfi);

    algebraic[4] = u[0];
}

void objectiveFunction5(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[5] = u[0];

    f[0] = voi-algebraic[5];
}

void findRoot5(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[5];

    nlaSolve(objectiveFunction5, u, 1, &rfi);

    algebraic[5] = u[0];
}

void objectiveFunction6(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[6] = u[0];

    f[0] = voi-algebraic[6];
}

void findRoot6(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[6];

    nlaSolve(objectiveFunction6, u, 1, &rfi);

    algebraic[6] = u[0];
}

void objectiveFunction7(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[7] = u[0];

    f[0] = voi-algebraic[7];
}

void findRoot7(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[7];

    nlaSolve(objectiveFunction7, u, 1, &rfi);

    algebraic[7] = u[0];
}

void objectiveFunction8(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[8] = u[0];

    f[0] = voi-algebraic[8];
}

void findRoot8(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[8];

    nlaSolve(objectiveFunction8, u, 1, &rfi);

    algebraic[8] = u[0];
}

void objectiveFunction9(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[9] = u[0];

    f[0] = voi-algebraic[9];
}

void findRoot9(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[9];

    nlaSolve(objectiveFunction9, u, 1, &rfi);

    algebraic[9] = u[0];
}

void objectiveFunction10(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[10] = u[0];

    f[0] = voi-algebraic[10];
}

void findRoot10(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[10];

    nlaSolve(objectiveFunction10, u, 1, &rfi);

    algebraic[10] = u[0];
}

void objectiveFunction11(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[11] = u[0];

    f[0] = voi-algebraic[11];
}

void findRoot11(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[11];

    nlaSolve(objectiveFunction11, u, 1, &rfi);

    algebraic[11] = u[0];
}

void objectiveFunction12(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[12] = u[0];

    f[0] = voi-algebraic[12];
}

void findRoot12(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[12];

    nlaSolve(objectiveFunction12, u, 1, &rfi);

    algebraic[12] = u[0];
}

void objectiveFunction13(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[13] = u[0];

    f[0] = voi-algebraic[13];
}

void findRoot13(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[13];

    nlaSolve(objectiveFunction13, u, 1, &rfi);

    algebraic[13] = u[0];
}

void objectiveFunction14(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[14] = u[0];

    f[0] = voi-algebraic[14];
}

void findRoot14(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[14];

    nlaSolve(objectiveFunction14, u, 1, &rfi);

    algebraic[14] = u[0];
}

void objectiveFunction15(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[15] = u[0];

    f[0] = voi-algebraic[15];
}

void findRoot15(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[15];

    nlaSolve(objectiveFunction15, u, 1, &rfi);

    algebraic[15] = u[0];
}

void objectiveFunction16(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[16] = u[0];

    f[0] = voi-algebraic[16];
}

void findRoot16(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[16];

    nlaSolve(objectiveFunction16, u, 1, &rfi);

    algebraic[16] = u[0];
}

void objectiveFunction17(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[17] = u[0];

    f[0] = voi-algebraic[17];
}

void findRoot17(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[17];

    nlaSolve(objectiveFunction17, u, 1, &rfi);

    algebraic[17] = u[0];
}

void objectiveFunction18(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[18] = u[0];

    f[0] = voi-algebraic[18];
}

void findRoot18(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[18];

    nlaSolve(objectiveFunction18, u, 1, &rfi);

    algebraic[18] = u[0];
}

void objectiveFunction19(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[19] = u[0];

    f[0] = voi-algebraic[19];
}

void findRoot19(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[19];

    nlaSolve(objectiveFunction19, u, 1, &rfi);

    algebraic[19] = u[0];
}

void objectiveFunction20(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[20] = u[0];

    f[0] = voi-algebraic[20];
}

void findRoot20(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[20];

    nlaSolve(objectiveFunction20, u, 1, &rfi);

    algebraic[20] = u[0];
}

void objectiveFunction21(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[21] = u[0];

    f[0] = voi-algebraic[21];
}

void findRoot21(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[21];

    nlaSolve(objectiveFunction21, u, 1, &rfi);

    algebraic[21] = u[0];
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    constants[0] = 3.0;
    states[1] = constants[0];
    states[0] = states[1];
    states[19] = 5.0;
    states[5] = states[19];
    states[4] = states[5];
    algebraic[16] = 7.0;
    states[7] = algebraic[16];
    states[6] = states[7];
    states[8] = constants[0];
    states[10] = states[19];
    states[11] = algebraic[16];
    constants[1] = 3.0;
    algebraic[4] = constants[1];
    states[12] = algebraic[4];
    states[21] = 5.0;
    algebraic[6] = states[21];
    states[14] = algebraic[6];
    algebraic[21] = 7.0;
    algebraic[7] = algebraic[21];
    states[15] = algebraic[7];
    states[16] = constants[0];
    states[18] = states[19];
    states[20] = algebraic[16];
    algebraic[0] = states[8];
    algebraic[2] = states[10];
    algebraic[3] = states[11];
    algebraic[9] = constants[1];
    algebraic[8] = algebraic[9];
    algebraic[13] = states[21];
    algebraic[12] = algebraic[13];
    algebraic[15] = algebraic[21];
    algebraic[14] = algebraic[15];
    algebraic[17] = constants[1];
    algebraic[19] = states[21];
    algebraic[20] = algebraic[21];
}

void computeComputedConstants(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    computedConstants[0] = 1.23*constants[0];
    states[3] = computedConstants[0];
    states[2] = states[3];
    states[9] = computedConstants[0];
    computedConstants[1] = 1.23*constants[1];
    algebraic[5] = computedConstants[1];
    states[13] = algebraic[5];
    states[17] = computedConstants[0];
    algebraic[1] = states[9];
    algebraic[11] = computedConstants[1];
    algebraic[10] = algebraic[11];
    algebraic[18] = computedConstants[1];
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    rates[0] = 1.23;
    rates[1] = 1.23;
    rates[2] = 1.23;
    rates[3] = 1.23;
    rates[4] = 1.23;
    rates[5] = 1.23;
    rates[6] = 1.23;
    rates[7] = 1.23;
    rates[8] = 1.23;
    rates[9] = 1.23;
    rates[10] = 1.23;
    rates[11] = 1.23;
    rates[12] = 1.23;
    rates[13] = 1.23;
    rates[14] = 1.23;
    rates[15] = 1.23;
    rates[16] = 1.23;
    rates[17] = 1.23;
    rates[18] = 1.23;
    rates[19] = 1.23;
    rates[20] = 1.23;
    rates[21] = 1.23;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, constants, computedConstants, algebraic);
    findRoot1(voi, states, rates, constants, computedConstants, algebraic);
    findRoot2(voi, states, rates, constants, computedConstants, algebraic);
    findRoot3(voi, states, rates, constants, computedConstants, algebraic);
    findRoot4(voi, states, rates, constants, computedConstants, algebraic);
    findRoot5(voi, states, rates, constants, computedConstants, algebraic);
    findRoot6(voi, states, rates, constants, computedConstants, algebraic);
    findRoot7(voi, states, rates, constants, computedConstants, algebraic);
    findRoot8(voi, states, rates, constants, computedConstants, algebraic);
    findRoot9(voi, states, rates, constants, computedConstants, algebraic);
    findRoot10(voi, states, rates, constants, computedConstants, algebraic);
    findRoot11(voi, states, rates, constants, computedConstants, algebraic);
    findRoot12(voi, states, rates, constants, computedConstants, algebraic);
    findRoot13(voi, states, rates, constants, computedConstants, algebraic);
    findRoot14(voi, states, rates, constants, computedConstants, algebraic);
    findRoot15(voi, states, rates, constants, computedConstants, algebraic);
    findRoot16(voi, states, rates, constants, computedConstants, algebraic);
    findRoot17(voi, states, rates, constants, computedConstants, algebraic);
    findRoot18(voi, states, rates, constants, computedConstants, algebraic);
    findRoot19(voi, states, rates, constants, computedConstants, algebraic);
    findRoot20(voi, states, rates, constants, computedConstants, algebraic);
    findRoot21(voi, states, rates, constants, computedConstants, algebraic);
}
