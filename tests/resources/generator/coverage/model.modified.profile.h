/* The content of this file was generated using a modified C profile of libCellML 0.3.99. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t STATE_COUNT;
extern const size_t VARIABLE_COUNT;

typedef enum {
    VARIABLE_OF_INTEGRATION,
    STATE,
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[38];
    char units[14];
    char component[13];
    VariableType type;
} VariableInfo;

extern const VariableInfo VOI_INFO;
extern const VariableInfo STATE_INFO[];
extern const VariableInfo VARIABLE_INFO[];

double * createStatesVector();
double * createVariablesArray();
void deleteArray(double *array);

void initialiseVariables(double *states, double *variables);
void computeComputedConstants(double *variables);
void computeRates(double voi, double *states, double *rates, double *variables);
void computeVariables(double voi, double *states, double *rates, double *variables);
