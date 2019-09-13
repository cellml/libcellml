/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 2;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[5];
    char units[14];
    char component[13];
} VariableInfo;

typedef struct {
    char name[5];
    char units[14];
    char component[13];
    VariableType type;
} VariableInfoWithType;

const VariableInfo VOI_INFO = {"time", "second", "my_component"};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_component"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"b", "second", "my_component", ALGEBRAIC},
    {"a", "second", "my_component", ALGEBRAIC}
};

double * createStatesArray()
{
    return (double *) malloc(1*sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(2*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeStatesAndConstants(double *states, double *variables)
{
    states[0] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = 2.0*voi;
    variables[1] = 3.0*variables[0];
}
