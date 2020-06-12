
#include <emscripten/bind.h>

#include "libcellml/entity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_entity) {

    class_<libcellml::Entity>("Entity")
        .smart_ptr<std::shared_ptr<libcellml::Entity>>("shared_ptr<libcellml::Entity>")
        .function("id", &libcellml::Entity::id)
        .function("setId", &libcellml::Entity::setId)
        .function("parent", &libcellml::Entity::parent)
        .function("setParent", &libcellml::Entity::setParent)
        .function("removeParent", &libcellml::Entity::removeParent)
        .function("hasParent", &libcellml::Entity::hasParent)
        .function("hasAncestor", &libcellml::Entity::hasAncestor)
    ;
}
