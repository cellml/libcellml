/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[9];
    char units[16];
    char component[25];
} VariableInfo;

typedef struct {
    char name[9];
    char units[16];
    char component[25];
    VariableType type;
} VariableInfoWithType;
