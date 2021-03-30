# include <emscripten/bind.h>

# include "libcellml/analyser.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_analyser)
{
    class_<libcellml::Analyser, base<libcellml::Logger>>("Analyser")
        .smart_ptr_constructor("Analyser", &libcellml::Analyser::create)
        .function("analyseModel", &libcellml::Analyser::analyseModel)
        .function("addExternalVariable", &libcellml::Analyser::addExternalVariable)
        .function("removeExternalVariableByIndex", select_overload<bool(size_t)>(&libcellml::Analyser::removeExternalVariable))
        .function("removeExternalVariableByModel", select_overload<bool(const libcellml::ModelPtr &, const std::string &, const std::string &)>(&libcellml::Analyser::removeExternalVariable))
        .function("removeExternalVariableByExternalVariable", select_overload<bool(const libcellml::AnalyserExternalVariablePtr &)>(&libcellml::Analyser::removeExternalVariable))
        .function("removeAllExternalVariables", &libcellml::Analyser::removeAllExternalVariables)
        .function("containsExternalVariableByModel", select_overload<bool(const libcellml::ModelPtr &, const std::string &, const std::string &) const>(&libcellml::Analyser::containsExternalVariable))
        .function("containsExternalVariableByExternalVariable", select_overload<bool(const libcellml::AnalyserExternalVariablePtr &) const>(&libcellml::Analyser::containsExternalVariable))
        .function("externalVariableByIndex", select_overload<libcellml::AnalyserExternalVariablePtr(size_t) const>(&libcellml::Analyser::externalVariable))
        .function("externalVariableByModel", select_overload<libcellml::AnalyserExternalVariablePtr(const libcellml::ModelPtr &, const std::string &, const std::string &) const>(&libcellml::Analyser::externalVariable))
        .function("externalVariableCount", &libcellml::Analyser::externalVariableCount)
        .function("model", &libcellml::Analyser::model)
    ;
}

