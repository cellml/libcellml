/* The content of this file was generated using a modified C profile of libCellML 0.6.3. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t STATE_COUNT;
extern const size_t CONSTANT_COUNT;
extern const size_t COMPUTED_CONSTANT_COUNT;
extern const size_t ALGEBRAIC_COUNT;
extern const size_t EXTERNAL_COUNT;

typedef struct {
    char name[38];
    char units[14];
    char component[13];
} VariableInfo;

extern const VariableInfo VOI_INFO;
extern const VariableInfo STATE_INFO[];
extern const VariableInfo CONSTANT_INFO[];
extern const VariableInfo COMPUTED_CONSTANT_INFO[];
extern const VariableInfo ALGEBRAIC_INFO[];
extern const VariableInfo EXTERNAL_INFO[];

double * createStatesVector();
double * createConstantsArray();
double * createComputedConstantsArray();
double * createAlgebraicArray();
double * createExternalsArray();

void deleteArray(double *array);

typedef double (* ExternalVariable)(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, size_t index);

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic);
void computeComputedConstants(double *constants, double *computedConstants);
void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable);
void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable);
