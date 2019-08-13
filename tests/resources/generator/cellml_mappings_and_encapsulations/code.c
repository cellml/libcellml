#include <stddef.h>
#include <stdlib.h>
#include <math.h>

const char version[] = "0.2.0";

struct VARIABLE_INFO {
    char name[32];
    char units[32];
};

const size_t STATE_VECTOR_SIZE = 2;
const size_t VARIABLE_VECTOR_SIZE = 2;
const struct VARIABLE_INFO VOI = {"t", "ms"};

const struct VARIABLE_INFO STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"x", "mM"},
    {"y", "mM"},
};

const struct VARIABLE_INFO VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"local_complex_maths", "mM"},
    {"two_x", "milli_mole"},
};

double *createStateVector()
{
    return (double *)malloc(2 * sizeof (double));
}

double *createRateVector()
{
    return (double *)malloc(2 * sizeof (double));
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
    states[0] = 0.0;
    states[1] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = -states[1]*1.0;
    rates[1] = states[0]*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0);
    variables[1] = 2.0*states[0];
}
