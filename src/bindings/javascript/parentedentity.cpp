
# include <emscripten/bind.h>

# include "libcellml/parentedentity.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_parentedentity)
{
    class_<libcellml::ParentedEntity, base<libcellml::Entity>>("ParentedEntity")
        .function("parent", &libcellml::ParentedEntity::parent)
        .function("setParent", &libcellml::ParentedEntity::setParent)
        .function("removeParent", &libcellml::ParentedEntity::removeParent)
        .function("hasParent", &libcellml::ParentedEntity::hasParent)
        .function("hasAncestor", &libcellml::ParentedEntity::hasAncestor)
    ;
}
