
#include <emscripten/bind.h>

#include "libcellml/printer.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_printer) {

    class_<libcellml::Printer>("Printer")
        .smart_ptr_constructor("Printer", &libcellml::Printer::create)
        .function("printModel", &libcellml::Printer::printModel)
    ;
}
