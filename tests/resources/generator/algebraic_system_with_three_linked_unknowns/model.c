/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 3;

const VariableInfo CONSTANT_INFO[] = {
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"z", "dimensionless", "my_algebraic_system"},
    {"y", "dimensionless", "my_algebraic_system"},
    {"x", "dimensionless", "my_algebraic_system"}
};

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
    double *constants;
    double *computedConstants;
    double *algebraic;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;

    algebraic[0] = u[0];
    algebraic[1] = u[1];
    algebraic[2] = u[2];

    f[0] = 2.0*algebraic[2]+algebraic[1]-2.0*algebraic[0]-(-1.0);
    f[1] = 3.0*algebraic[2]-3.0*algebraic[1]-algebraic[0]-5.0;
    f[2] = algebraic[2]-2.0*algebraic[1]+3.0*algebraic[0]-6.0;
}

void findRoot0(double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { constants, computedConstants, algebraic };
    double u[3];

    u[0] = algebraic[0];
    u[1] = algebraic[1];
    u[2] = algebraic[2];

    nlaSolve(objectiveFunction0, u, 3, &rfi);

    algebraic[0] = u[0];
    algebraic[1] = u[1];
    algebraic[2] = u[2];
}

void initialiseVariables(double *constants, double *computedConstants, double *algebraic)
{
    algebraic[0] = 1.0;
    algebraic[1] = 1.0;
    algebraic[2] = 1.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(constants, computedConstants, algebraic);
}
