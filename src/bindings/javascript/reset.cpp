
#include <emscripten/bind.h>

#include "libcellml/reset.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_reset) {

    class_<libcellml::Reset, base<libcellml::Entity>>("Reset")
        .smart_ptr_constructor("Reset", select_overload<libcellml::ResetPtr()>(&libcellml::Reset::create))
        .function("setOrder", &libcellml::Reset::setOrder)
        .function("order", &libcellml::Reset::order)
        .function("removeOrder", &libcellml::Reset::removeOrder)
        .function("isOrderSet", &libcellml::Reset::isOrderSet)
        .function("setVariable", &libcellml::Reset::setVariable)
        .function("variable", &libcellml::Reset::variable)
        .function("setTestVariable", &libcellml::Reset::setTestVariable)
        .function("testVariable", &libcellml::Reset::testVariable)
        .function("appendTestValue", &libcellml::Reset::appendTestValue)
        .function("testValue", &libcellml::Reset::testValue)
        .function("setTestValue", &libcellml::Reset::setTestValue)
        .function("removeTestValue", &libcellml::Reset::removeTestValue)
        .function("setTestValueId", &libcellml::Reset::setTestValueId)
        .function("removeTestValueId", &libcellml::Reset::removeTestValueId)
        .function("testValueId", &libcellml::Reset::testValueId)
        .function("appendResetValue", &libcellml::Reset::appendResetValue)
        .function("resetValue", &libcellml::Reset::resetValue)
        .function("setResetValue", &libcellml::Reset::setResetValue)
        .function("removeResetValue", &libcellml::Reset::removeResetValue)
        .function("setResetValueId", &libcellml::Reset::setResetValueId)
        .function("removeResetValueId", &libcellml::Reset::removeResetValueId)
        .function("resetValueId", &libcellml::Reset::resetValueId)
        .function("clone", &libcellml::Reset::clone)
    ;

}
