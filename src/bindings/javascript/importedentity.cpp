
#include <emscripten/bind.h>

#include "libcellml/importedentity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_importedentity) {

    class_<libcellml::ImportedEntity>("ImportedEntity")
//        .smart_ptr_constructor("ImportedEntity", &std::make_shared<libcellml::ImportedEntity>)
        .function("isImport", &libcellml::ImportedEntity::isImport)
        .function("importReference", &libcellml::ImportedEntity::importReference)
        .function("importSource", &libcellml::ImportedEntity::importSource)
        .function("setImportSource", &libcellml::ImportedEntity::setImportSource)
        .function("setImportReference", &libcellml::ImportedEntity::setImportReference)
    ;
}
