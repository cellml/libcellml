
#include <emscripten/bind.h>

#include "libcellml/parser.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_parser) {

    class_<libcellml::Parser, base<libcellml::Logger>>("Parser")
        .smart_ptr_constructor("Parser", &libcellml::Parser::create)
        .function("parseModel", &libcellml::Parser::parseModel)
    ;
}
