/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[20];
    char units[11];
    char component[24];
} VariableInfo;

typedef struct {
    char name[20];
    char units[11];
    char component[24];
    VariableType type;
} VariableInfoWithType;
