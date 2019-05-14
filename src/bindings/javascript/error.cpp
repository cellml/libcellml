
#include <emscripten/bind.h>

#include "libcellml/error.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_error) {

    class_<libcellml::Error>("Error")
        .smart_ptr_constructor("Error", &std::make_shared<libcellml::Error>)
        .function("getDescription", &libcellml::Error::getDescription)
        .function("setDescription", &libcellml::Error::getKind)
        .function("setDescription", &libcellml::Error::setDescription)
        .function("getDescription", &libcellml::Error::setKind)
    ;
}
