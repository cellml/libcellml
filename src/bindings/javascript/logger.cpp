
#include <emscripten/bind.h>

#include "libcellml/logger.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_logger)
{
    class_<libcellml::Logger>("Logger")
        .function("issueCount", &libcellml::Logger::issueCount)
        .function("issue", &libcellml::Logger::issue)
        .function("errorCount", &libcellml::Logger::errorCount)
        .function("error", &libcellml::Logger::error)
        .function("warningCount", &libcellml::Logger::warningCount)
        .function("warning", &libcellml::Logger::warning)
        .function("messageCount", &libcellml::Logger::messageCount)
        .function("message", &libcellml::Logger::message)
    ;
}
