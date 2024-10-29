/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t VARIABLE_COUNT;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[6];
    char units[11];
    char component[14];
    VariableType type;
} VariableInfo;

extern const VariableInfo VARIABLE_INFO[];

double * createVariablesArray();
void deleteArray(double *array);

void initialiseVariables(double *variables);
void computeComputedConstants(double *variables);
void computeVariables(double *variables);
