/* The contents of this file was generated from version 0.2.0 of libCellML. */
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

const char version[] = "0.2.0";

struct VARIABLE_INFO {
    char name[2];
    char units[14];
};

const size_t STATE_VECTOR_SIZE = 0;
const size_t VARIABLE_VECTOR_SIZE = 1;

const struct VARIABLE_INFO STATE_VECTOR_INFORMATION_ARRAY[] = {
};

const struct VARIABLE_INFO VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"x", "dimensionless"},
};

double *createStateVector()
{
    return (double *)malloc(0 * sizeof (double));
}

double *createRateVector()
{
    return (double *)malloc(0 * sizeof (double));
}

double *createVariableVector()
{
    return (double *)malloc(1 * sizeof (double));
}

void freeVector(double *array)
{
   free(array);
}

void initializeConstants(double *states, double *variables)
{
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}
