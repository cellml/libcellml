/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[31];
    char units[27];
    char component[53];
} VariableInfo;

typedef struct {
    char name[31];
    char units[27];
    char component[53];
    VariableType type;
} VariableInfoWithType;
