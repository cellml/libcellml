/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t CONSTANT_COUNT;
extern const size_t COMPUTED_CONSTANT_COUNT;
extern const size_t ALGEBRAIC_COUNT;
extern const size_t EXTERNAL_COUNT;

typedef struct {
    char name[6];
    char units[11];
    char component[14];
} VariableInfo;

extern const VariableInfo CONSTANT_INFO[];
extern const VariableInfo COMPUTED_CONSTANT_INFO[];
extern const VariableInfo ALGEBRAIC_INFO[];
extern const VariableInfo EXTERNAL_INFO[];

double * createConstantsArray();
double * createComputedConstantsArray();
double * createAlgebraicArray();
double * createExternalsArray();

void deleteArray(double *array);

typedef double (* ExternalVariable)(double *constants, double *computedConstants, double *algebraic, double *externals, size_t index);

void initialiseVariables(double *constants, double *computedConstants, double *algebraic);
void computeComputedConstants(double *constants, double *computedConstants);
void computeVariables(double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable);
