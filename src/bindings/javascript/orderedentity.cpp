
#include <emscripten/bind.h>

#include "libcellml/orderedentity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_orderedentity) {

    class_<libcellml::OrderedEntity>("OrderedEntity")
//        .smart_ptr_constructor("OrderedEntity", &std::make_shared<libcellml::OrderedEntity>)
        .function("order", &libcellml::OrderedEntity::order)
        .function("isOrderSet", &libcellml::OrderedEntity::isOrderSet)
        .function("setOrder", &libcellml::OrderedEntity::setOrder)
        .function("unsetOrder", &libcellml::OrderedEntity::unsetOrder)
    ;
}
