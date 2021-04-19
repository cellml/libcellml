
# include <emscripten/bind.h>

# include "libcellml/analyserexternalvariable.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_analyserexternalvariable)
{
    class_<libcellml::AnalyserExternalVariable>("AnalyserExternalVariable")
        .smart_ptr_constructor("AnalyserExternalVariable", &libcellml::AnalyserExternalVariable::create)
        .function("variable", &libcellml::AnalyserExternalVariable::variable)
        .function("addDependency", &libcellml::AnalyserExternalVariable::addDependency)
        .function("removeDependencyByIndex", select_overload<bool(size_t)>(&libcellml::AnalyserExternalVariable::removeDependency))
        .function("removeDependencyByModel", select_overload<bool(const libcellml::ModelPtr &, const std::string &, const std::string &)>(&libcellml::AnalyserExternalVariable::removeDependency))
        .function("removeDependencyByVariable", select_overload<bool(const libcellml::VariablePtr &)>(&libcellml::AnalyserExternalVariable::removeDependency))
        .function("removeAllDependencies", &libcellml::AnalyserExternalVariable::removeAllDependencies)
        .function("containsDependencyByModel", select_overload<bool(const libcellml::ModelPtr &, const std::string &, const std::string &) const>(&libcellml::AnalyserExternalVariable::containsDependency))
        .function("containsDependencyByVariable", select_overload<bool(const libcellml::VariablePtr &) const>(&libcellml::AnalyserExternalVariable::containsDependency))
        .function("dependencyByIndex", select_overload<libcellml::VariablePtr(size_t) const>(&libcellml::AnalyserExternalVariable::dependency))
        .function("dependencyByModel", select_overload<libcellml::VariablePtr(const libcellml::ModelPtr &, const std::string &, const std::string &) const>(&libcellml::AnalyserExternalVariable::dependency))
        .function("dependencies", &libcellml::AnalyserExternalVariable::dependencies)
        .function("dependencyCount", &libcellml::AnalyserExternalVariable::dependencyCount)
    ;
}
