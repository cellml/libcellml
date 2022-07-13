
# include <emscripten/bind.h>

# include "libcellml/types.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_types)
{
    register_vector<libcellml::VariablePtr>("VectorVariablePtr");
}
