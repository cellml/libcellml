/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t CONSTANT_COUNT;
extern const size_t COMPUTED_CONSTANT_COUNT;
extern const size_t ALGEBRAIC_COUNT;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC,
    EXTERNAL
} VariableType;

typedef struct {
    char name[2];
    char units[14];
    char component[17];
    VariableType type;
} VariableInfo;

extern const VariableInfo VARIABLE_INFO[];

double * createVariablesArray();
void deleteArray(double *array);

typedef double (* ExternalVariable)(double *variables, size_t index);

void initialiseVariables(double *constants, ExternalVariable externalVariable);
void computeComputedConstants(double *constants, double *computedConstants);
void computeVariables(double *constants, double *computedConstants, double *algebraic, ExternalVariable externalVariable);
