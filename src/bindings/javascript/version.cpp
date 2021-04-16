
#include <emscripten/bind.h>

#include "libcellml/version.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_version) {
    function("versionString", &libcellml::versionString);
    function("version", &libcellml::version);
}
