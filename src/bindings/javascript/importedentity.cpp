
#include <emscripten/bind.h>

#include "libcellml/importedentity.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_importedentity) {

    class_<libcellml::ImportedEntity>("ImportedEntity")
        .function("isImport", &libcellml::ImportedEntity::isImport)
        .function("importSource", &libcellml::ImportedEntity::importSource)
        .function("setImportSource", &libcellml::ImportedEntity::setImportSource)
        .function("importReference", &libcellml::ImportedEntity::importReference)
        .function("setImportReference", &libcellml::ImportedEntity::setImportReference)
        .function("isResolved", &libcellml::ImportedEntity::isResolved)
    ;
}
