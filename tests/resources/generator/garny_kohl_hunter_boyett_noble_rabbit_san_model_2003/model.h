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
