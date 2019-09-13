/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[5];
    char units[14];
    char component[13];
} VariableInfo;

typedef struct {
    char name[5];
    char units[14];
    char component[13];
    VariableType type;
} VariableInfoWithType;
