
#include <emscripten/bind.h>

#include "libcellml/validator.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_validator) {

    class_<libcellml::Validator, base<libcellml::Logger>>("Validator")
        .smart_ptr_constructor("Validator", &libcellml::Validator::create)
        .function("validateModel", &libcellml::Validator::validateModel)
    ;
}
