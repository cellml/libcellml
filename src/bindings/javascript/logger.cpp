
#include <emscripten/bind.h>

#include "libcellml/logger.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_logger) {

    class_<libcellml::Logger>("Logger")
        .function("addIssue", &libcellml::Logger::addIssue)
        .function("removeAllIssues", &libcellml::Logger::removeAllIssues)
        .function("error", &libcellml::Logger::error)
        .function("warning", &libcellml::Logger::warning)
        .function("hint", &libcellml::Logger::hint)
    ;
}
