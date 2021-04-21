
#include <emscripten/bind.h>

#include "libcellml/entity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_entity) {

    class_<libcellml::Entity>("Entity")
        .smart_ptr<std::shared_ptr<libcellml::Entity>>("shared_ptr<libcellml::Entity>")
        .function("setId", &libcellml::Entity::setId)
        .function("id", &libcellml::Entity::id)
        .function("removeId", &libcellml::Entity::removeId)
        .function("equals", &libcellml::Entity::equals)
    ;
}
