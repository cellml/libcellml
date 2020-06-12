
#include <emscripten/bind.h>

#include "libcellml/component.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_component) {

    class_<libcellml::Component, base<libcellml::ComponentEntity>>("Component")
        .smart_ptr_constructor("Component", select_overload<libcellml::ComponentPtr()>(&libcellml::Component::create))
        .function("addReset", &libcellml::Component::addReset)
        .function("addVariable", &libcellml::Component::addVariable)
        .function("appendMath", &libcellml::Component::appendMath)
        .function("math", &libcellml::Component::math)
        .function("resetByIndex", &libcellml::Component::reset)
        .function("variableByIndex", select_overload<libcellml::VariablePtr(size_t) const>(&libcellml::Component::variable))
        .function("variableByName", select_overload<libcellml::VariablePtr(const std::string &) const>(&libcellml::Component::variable))
        .function("hasReset", &libcellml::Component::hasReset)
        .function("hasVariableByName", select_overload<bool(const std::string &) const>(&libcellml::Component::hasVariable))
        .function("hasVariableByVariable", select_overload<bool(const libcellml::VariablePtr &) const>(&libcellml::Component::hasVariable))
        .function("removeAllResets", &libcellml::Component::removeAllResets)
        .function("removeAllVariables", &libcellml::Component::removeAllVariables)
        .function("removeResetByIndex", select_overload<bool(size_t)>(&libcellml::Component::removeReset))
        .function("removeResetByReset", select_overload<bool(const libcellml::ResetPtr &)>(&libcellml::Component::removeReset))
        .function("removeVariableByIndex", select_overload<bool(size_t)>(&libcellml::Component::removeVariable))
        .function("removeVariableByName", select_overload<bool(const std::string &)>(&libcellml::Component::removeVariable))
        .function("removeVariableByVariable", select_overload<bool(const libcellml::VariablePtr &)>(&libcellml::Component::removeVariable))
        .function("resetCount", &libcellml::Component::resetCount)
        .function("setMath", &libcellml::Component::setMath)
        .function("setSourceComponent", &libcellml::Component::setSourceComponent)
        .function("takeVariableByIndex", select_overload<libcellml::VariablePtr(size_t)>(&libcellml::Component::takeVariable))
        .function("takeVariableByName", select_overload<libcellml::VariablePtr(const std::string &)>(&libcellml::Component::takeVariable))
        .function("takeResetByIndex", &libcellml::Component::takeReset)
        .function("variableCount", &libcellml::Component::variableCount)
        .function("clone", &libcellml::Component::clone)
        .function("isImport", &libcellml::ImportedEntity::isImport)
        .function("importReference", &libcellml::ImportedEntity::importReference)
        .function("importSource", &libcellml::ImportedEntity::importSource)
        .function("setImportSource", &libcellml::ImportedEntity::setImportSource)
        .function("setImportReference", &libcellml::ImportedEntity::setImportReference)
    ;
}
