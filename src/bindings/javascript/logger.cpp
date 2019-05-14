
#include <emscripten/bind.h>

#include "libcellml/logger.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_logger) {

    class_<libcellml::Logger>("Logger")
        .smart_ptr_constructor("Logger", &std::make_shared<libcellml::Logger>)
        .function("addError", &libcellml::Logger::addError)
        .function("clearErrors", &libcellml::Logger::clearErrors)
        .function("errorCount", &libcellml::Logger::errorCount)
        .function("getError", &libcellml::Logger::getError)
    ;
}
