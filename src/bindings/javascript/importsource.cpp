
#include <emscripten/bind.h>

#include "libcellml/importsource.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_importsource) {

    class_<libcellml::ImportSource, base<libcellml::Entity>>("ImportSource")
        .smart_ptr_constructor("ImportSource", &libcellml::ImportSource::create)
        .function("model", &libcellml::ImportSource::model)
        .function("url", &libcellml::ImportSource::url)
        .function("hasModel", &libcellml::ImportSource::hasModel)
        .function("setModel", &libcellml::ImportSource::setModel)
        .function("setUrl", &libcellml::ImportSource::setUrl)
    ;
}
