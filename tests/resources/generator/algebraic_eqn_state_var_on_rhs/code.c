#include <stddef.h>
#include <stdlib.h>
#include <math.h>

struct VARIABLE_INFO {
    char name[32];
    char units[32];
};

const size_t STATE_VECTOR_SIZE = 1;
const size_t VARIABLE_VECTOR_SIZE = 2;
const struct VARIABLE_INFO VOI = {"t", "second"};

const struct VARIABLE_INFO STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"x", "dimensionless"},
};

const struct VARIABLE_INFO VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"a", "per_s"},
    {"xx", "dimensionless"},
};

double *createStateVector()
{
    return (double *)malloc(1 * sizeof (double));
}

double *createRateVector()
{
    return (double *)malloc(1 * sizeof (double));
}

double *createVariableVector()
{
    return (double *)malloc(2 * sizeof (double));
}

void freeVector(double *array)
{
   free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 1.0;
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = 2.0*states[0];
}
