/* The content of this file was generated using the C profile of libCellML 0.2.0. */

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
    ALGEBRAIC,
    EXTERNAL
} VariableType;

typedef struct {
    char name[8];
    char units[16];
    char component[25];
    VariableType type;
} VariableInfo;

extern const VariableInfo VOI_INFO;
extern const VariableInfo STATE_INFO[];
extern const VariableInfo VARIABLE_INFO[];

double * createStatesArray();
double * createVariablesArray();
void deleteArray(double *array);

typedef double (* ExternalVariable)(double voi, double *states, double *rates, double *variables, size_t index);

void initialiseStatesAndConstants(double *states, double *variables);
void computeComputedConstants(double *variables);
void computeRates(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable);
void computeVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable);
