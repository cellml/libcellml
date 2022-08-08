/* The content of this file was generated using the C profile of libCellML 0.2.0. */

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
    char name[2];
    char units[3];
    char component[10];
    VariableType type;
} VariableInfo;

extern const VariableInfo VARIABLE_INFO[];

double * createVariablesArray();
void deleteArray(double *array);

void initialiseVariables(double *variables);
void computeComputedConstants(double *variables);
void computeVariables(double *variables);
