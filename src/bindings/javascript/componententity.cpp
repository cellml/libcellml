
#include <emscripten/bind.h>

#include "libcellml/model.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_componententity) {

    class_<libcellml::ComponentEntity, base<libcellml::NamedEntity>>("ComponentEntity")
        .function("addComponent", &libcellml::ComponentEntity::addComponent)
        .function("componentCount", &libcellml::ComponentEntity::componentCount)
        .function("containsComponentByName", select_overload<bool(const std::string &, bool) const>(&libcellml::ComponentEntity::containsComponent))
        .function("containsComponentByComponent", select_overload<bool(const libcellml::ComponentPtr &, bool) const>(&libcellml::ComponentEntity::containsComponent))
        .function("componentByIndex", select_overload<libcellml::ComponentPtr(size_t) const>(&libcellml::ComponentEntity::component))
        .function("componentByName", select_overload<libcellml::ComponentPtr(const std::string &, bool) const>(&libcellml::ComponentEntity::component))
        .function("encapsulationId", &libcellml::ComponentEntity::encapsulationId)
        .function("removeAllComponents", &libcellml::ComponentEntity::removeAllComponents)
        .function("removeComponentByIndex", select_overload<bool(size_t)>(&libcellml::ComponentEntity::removeComponent))
        .function("removeComponentByName", select_overload<bool(const std::string &, bool)>(&libcellml::ComponentEntity::removeComponent))
        .function("removeComponentByComponent", select_overload<bool(const libcellml::ComponentPtr &, bool)>(&libcellml::ComponentEntity::removeComponent))
        .function("replaceComponentByIndex", select_overload<bool(size_t, const libcellml::ComponentPtr &)>(&libcellml::ComponentEntity::replaceComponent))
        .function("replaceComponentByName", select_overload<bool(const std::string &, const libcellml::ComponentPtr &, bool)>(&libcellml::ComponentEntity::replaceComponent))
        .function("replaceComponentByComponent", select_overload<bool(const libcellml::ComponentPtr &, const libcellml::ComponentPtr &, bool)>(&libcellml::ComponentEntity::replaceComponent))
        .function("setEncapsulationId", &libcellml::ComponentEntity::setEncapsulationId)
        .function("takeComponentByIndex", select_overload<libcellml::ComponentPtr(size_t)>(&libcellml::ComponentEntity::takeComponent))
        .function("takeComponentByName", select_overload<libcellml::ComponentPtr(const std::string &, bool)>(&libcellml::ComponentEntity::takeComponent))
    ;
}
