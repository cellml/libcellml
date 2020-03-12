
#include <emscripten/bind.h>

#include "libcellml/error.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_error) {

    class_<libcellml::Error>("Error")
        .smart_ptr_constructor("Error", select_overload<libcellml::ErrorPtr()>(&libcellml::Error::create))
        .function("description", &libcellml::Error::description)
        .function("kind", &libcellml::Error::kind)
        .function("setDescription", &libcellml::Error::setDescription)
        .function("setKind", &libcellml::Error::setKind)
    ;
}
