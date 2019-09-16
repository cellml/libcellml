/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

extern const char LIBCELLML_VERSION[];

extern const size_t STATE_COUNT;
extern const size_t VARIABLE_COUNT;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[38];
    char units[14];
    char component[13];
} VariableInfo;

typedef struct {
    char name[38];
    char units[14];
    char component[13];
    VariableType type;
} VariableInfoWithType;

extern const VariableInfo VOI_INFO;
extern const VariableInfo STATE_INFO[];
extern const VariableInfoWithType VARIABLE_INFO[];

extern double xor(double x, double y);
extern double min(double x, double y);
extern double max(double x, double y);

extern double sec(double x);
extern double csc(double x);
extern double cot(double x);
extern double sech(double x);
extern double csch(double x);
extern double coth(double x);
extern double asec(double x);
extern double acsc(double x);
extern double acot(double x);
extern double asech(double x);
extern double acsch(double x);
extern double acoth(double x);

extern double * createStatesArray();
extern double * createVariablesArray();
extern void deleteArray(double *array);
