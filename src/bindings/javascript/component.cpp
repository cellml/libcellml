
#include <emscripten/bind.h>

#include "libcellml/component.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_component) {

    class_<libcellml::Component, base<libcellml::ComponentEntity>>("Component")
        .smart_ptr_constructor("Component", select_overload<libcellml::ComponentPtr()>(&libcellml::Component::create))
        .function("setSourceComponent", &libcellml::Component::setSourceComponent)
        .function("appendMath", &libcellml::Component::appendMath)
        .function("math", &libcellml::Component::math)
        .function("setMath", &libcellml::Component::setMath)
        .function("removeMath", &libcellml::Component::removeMath)
        .function("addVariable", &libcellml::Component::addVariable)
        .function("removeVariableByIndex", select_overload<bool(size_t)>(&libcellml::Component::removeVariable))
        .function("removeVariableByName", select_overload<bool(const std::string &)>(&libcellml::Component::removeVariable))
        .function("removeVariableByVariable", select_overload<bool(const libcellml::VariablePtr &)>(&libcellml::Component::removeVariable))
        .function("removeAllVariables", &libcellml::Component::removeAllVariables)
        .function("variableByIndex", select_overload<libcellml::VariablePtr(size_t) const>(&libcellml::Component::variable))
        .function("variableByName", select_overload<libcellml::VariablePtr(const std::string &) const>(&libcellml::Component::variable))
        .function("takeVariableByIndex", select_overload<libcellml::VariablePtr(size_t)>(&libcellml::Component::takeVariable))
        .function("takeVariableByName", select_overload<libcellml::VariablePtr(const std::string &)>(&libcellml::Component::takeVariable))
        .function("variableCount", &libcellml::Component::variableCount)
        .function("hasVariableByVariable", select_overload<bool(const libcellml::VariablePtr &) const>(&libcellml::Component::hasVariable))
        .function("hasVariableByName", select_overload<bool(const std::string &) const>(&libcellml::Component::hasVariable))
        .function("addReset", &libcellml::Component::addReset)
        .function("takeReset", &libcellml::Component::takeReset)
        .function("removeResetByIndex", select_overload<bool(size_t)>(&libcellml::Component::removeReset))
        .function("removeResetByReset", select_overload<bool(const libcellml::ResetPtr &)>(&libcellml::Component::removeReset))
        .function("removeAllResets", &libcellml::Component::removeAllResets)
        .function("reset", &libcellml::Component::reset)
        .function("resetCount", &libcellml::Component::resetCount)
        .function("hasReset", &libcellml::Component::hasReset)
        .function("clone", &libcellml::Component::clone)
        .function("requiresImports", &libcellml::Component::requiresImports)
        .function("isImport", &libcellml::ImportedEntity::isImport)
        .function("importSource", &libcellml::ImportedEntity::importSource)
        .function("setImportSource", &libcellml::ImportedEntity::setImportSource)
        .function("importReference", &libcellml::ImportedEntity::importReference)
        .function("setImportReference", &libcellml::ImportedEntity::setImportReference)
        .function("isResolved", &libcellml::ImportedEntity::isResolved)
    ;
}
