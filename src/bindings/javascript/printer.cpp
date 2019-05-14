
#include <emscripten/bind.h>

#include "libcellml/printer.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_printer) {

    class_<libcellml::Printer, base<libcellml::Logger>>("Printer")
        .smart_ptr_constructor("Printer", &std::make_shared<libcellml::Printer>)
        .function("printModel", select_overload<std::string(libcellml::ModelPtr) const>(&libcellml::Printer::printModel))
    ;
}
