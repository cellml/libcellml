
#include <emscripten/bind.h>

#include "libcellml/logger.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_logger) {

    class_<libcellml::Logger>("Logger")
        .function("removeAllIssues", &libcellml::Logger::removeAllIssues)
        .function("addIssue", &libcellml::Logger::addIssue)
        .function("addIssues", &libcellml::Logger::addIssues)
        .function("issueCount", &libcellml::Logger::issueCount)
        .function("issue", &libcellml::Logger::issue)
        .function("errorCount", &libcellml::Logger::errorCount)
        .function("error", &libcellml::Logger::error)
        .function("warningCount", &libcellml::Logger::warningCount)
        .function("warning", &libcellml::Logger::warning)
        .function("hintCount", &libcellml::Logger::hintCount)
        .function("hint", &libcellml::Logger::hint)
        .function("messageCount", &libcellml::Logger::messageCount)
        .function("message", &libcellml::Logger::message)
    ;
}
