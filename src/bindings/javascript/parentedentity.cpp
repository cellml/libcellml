
#include <emscripten/bind.h>

#include "libcellml/parentedentity.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_parentedentity)
{
    class_<libcellml::ParentedEntity, base<libcellml::Entity>>("ParentedEntity")
        .smart_ptr<std::shared_ptr<libcellml::ParentedEntity>>("ParentedEntity")
        .function("parent", &libcellml::ParentedEntity::parent)
        .function("hasParent", &libcellml::ParentedEntity::hasParent)
        .function("hasAncestor", &libcellml::ParentedEntity::hasAncestor)
    ;
}
