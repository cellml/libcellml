
#include <emscripten/bind.h>

#include "libcellml/importsource.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_importsource) {

    class_<libcellml::ImportSource, base<libcellml::Entity>>("ImportSource")
        .smart_ptr_constructor("ImportSource", &std::make_shared<libcellml::ImportSource>)
        .function("getModel", &libcellml::ImportSource::getModel)
        .function("getUrl", &libcellml::ImportSource::getUrl)
        .function("hasModel", &libcellml::ImportSource::hasModel)
        .function("setModel", &libcellml::ImportSource::setModel)
        .function("setUrl", &libcellml::ImportSource::setUrl)
    ;
}
