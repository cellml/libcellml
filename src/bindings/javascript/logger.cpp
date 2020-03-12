
#include <emscripten/bind.h>

#include "libcellml/logger.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_logger) {

    class_<libcellml::Logger>("Logger")
//        .smart_ptr_constructor("Logger", &libcellml::Logger::create)
        .function("addError", &libcellml::Logger::addError)
        .function("removeAllErrors", &libcellml::Logger::removeAllErrors)
        .function("errorCount", &libcellml::Logger::errorCount)
        .function("error", &libcellml::Logger::error)
    ;
}
