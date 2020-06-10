/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t STATE_COUNT;
extern const size_t VARIABLE_COUNT;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[2];
    char units[3];
    char component[12];
} VariableInfo;

typedef struct {
    char name[2];
    char units[3];
    char component[12];
    VariableType type;
} VariableInfoWithType;

extern const VariableInfo VOI_INFO;
extern const VariableInfo STATE_INFO[];
extern const VariableInfoWithType VARIABLE_INFO[];

double * createStatesArray();
double * createVariablesArray();
void deleteArray(double *array);

void initializeStatesAndConstants(double *states, double *variables);
void computeComputedConstants(double *variables);
void computeRates(double voi, double *states, double *rates, double *variables);
void computeVariables(double voi, double *states, double *rates, double *variables);
