/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <stddef.h>

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC
} VariableType;

typedef struct {
    char name[15];
    char units[26];
    char component[28];
} VariableInfo;

typedef struct {
    char name[15];
    char units[26];
    char component[28];
    VariableType type;
} VariableInfoWithType;
