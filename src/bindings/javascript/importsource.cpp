
#include <emscripten/bind.h>

#include "libcellml/importsource.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_importsource) {

    class_<libcellml::ImportSource, base<libcellml::Entity>>("ImportSource")
        .smart_ptr_constructor("ImportSource", &libcellml::ImportSource::create)
        .function("url", &libcellml::ImportSource::url)
        .function("setUrl", &libcellml::ImportSource::setUrl)
        .function("model", &libcellml::ImportSource::model)
        .function("setModel", &libcellml::ImportSource::setModel)
        .function("removeModel", &libcellml::ImportSource::removeModel)
        .function("hasModel", &libcellml::ImportSource::hasModel)
        .function("clone", &libcellml::ImportSource::clone)
    ;
}
