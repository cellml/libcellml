
#include <emscripten/bind.h>

#include "libcellml/entity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_entity) {
    class_<libcellml::Entity>("Entity")
//        .smart_ptr_constructor("Entity", &std::make_shared<libcellml::Entity>)
        .function("id", &libcellml::Entity::id)
        .function("setId", &libcellml::Entity::setId)
    ;
}
