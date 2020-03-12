
#include <emscripten/bind.h>

#include "libcellml/namedentity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_namedentity) {
    class_<libcellml::NamedEntity, base<libcellml::Entity>>("NamedEntity")
//        .smart_ptr_constructor("NamedEntity", &std::make_shared<libcellml::NamedEntity>)
        .function("name", &libcellml::NamedEntity::name)
        .function("setName", &libcellml::NamedEntity::setName)
    ;
}
