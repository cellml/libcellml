/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 4;

const VariableInfo VOI_INFO = {"time", "day", "predator_prey_component"};

const VariableInfo STATE_INFO[] = {
    {"y_s", "number_of_sharks", "predator_prey_component"},
    {"y_f", "thousands_of_fish", "predator_prey_component"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"a", "per_day", "predator_prey_component", CONSTANT},
    {"b", "per_shark_day", "predator_prey_component", CONSTANT},
    {"d", "per_1000fish_day", "predator_prey_component", CONSTANT},
    {"c", "per_day", "predator_prey_component", COMPUTED_CONSTANT}
};

double * createStatesArray()
{
    return (double *) malloc(2*sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(4*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeStatesAndConstants(double *states, double *variables)
{
    states[0] = 2.0;
    states[1] = 1.0;
    variables[0] = 1.2;
    variables[1] = -0.6;
    variables[2] = 0.3;
}

void computeComputedConstants(double *variables)
{
    variables[3] = variables[0]-2.0;
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0]*states[0]+variables[1]*states[0]*states[1];
    rates[1] = variables[3]*states[1]+variables[2]*states[0]*states[1];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}
