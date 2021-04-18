
#include <emscripten/bind.h>

#include "libcellml/namedentity.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_namedentity) {

    class_<libcellml::NamedEntity, base<libcellml::ParentedEntity>>("NamedEntity")
        .function("setName", &libcellml::NamedEntity::setName)
        .function("name", &libcellml::NamedEntity::name)
    ;
}
