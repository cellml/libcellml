/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t STATE_COUNT;
extern const size_t CONSTANT_COUNT;
extern const size_t COMPUTED_CONSTANT_COUNT;
extern const size_t ALGEBRAIC_COUNT;

typedef enum {
    VARIABLE_OF_INTEGRATION,
    STATE,
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[15];
    char units[26];
    char component[28];
    VariableType type;
} VariableInfo;

extern const VariableInfo VOI_INFO;
extern const VariableInfo STATE_INFO[];
extern const VariableInfo VARIABLE_INFO[];

double * createStatesArray();
double * createVariablesArray();
void deleteArray(double *array);

void initialiseVariables(double *states, double *rates, double *constants);
void computeComputedConstants(double *constants, double *computedConstants);
void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic);
void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic);
