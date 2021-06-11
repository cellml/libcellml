# include <emscripten/bind.h>

# include "libcellml/importer.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_importer)
{
    class_<libcellml::Importer>("Importer")
        .smart_ptr_constructor("Importer", &libcellml::Importer::create)
        .function("flattenModel", &libcellml::Importer::flattenModel)
        .function("resolveImports", &libcellml::Importer::resolveImports)
        .function("libraryCount", &libcellml::Importer::libraryCount)
        .function("libraryByKey", select_overload<libcellml::ModelPtr(const std::string &)>(&libcellml::Importer::library))
        .function("libraryByIndex", select_overload<libcellml::ModelPtr(const size_t &)>(&libcellml::Importer::library))
        .function("key", &libcellml::Importer::key)
        .function("addModel", &libcellml::Importer::addModel)
        .function("replaceModel", &libcellml::Importer::replaceModel)
        .function("clearImports", &libcellml::Importer::clearImports)
        .function("removeAllModels", &libcellml::Importer::removeAllModels)
        .function("addImportSource", &libcellml::Importer::addImportSource)
        .function("importSourceCount", &libcellml::Importer::importSourceCount)
        .function("importSource", &libcellml::Importer::importSource)
        .function("removeImportSourceByIndex", select_overload<bool(size_t)>(&libcellml::Importer::removeImportSource))
        .function("removeImportSourceByImportSource", select_overload<bool(const libcellml::ImportSourcePtr &)>(&libcellml::Importer::removeImportSource))
        .function("removeAllImportSources", &libcellml::Importer::removeAllImportSources)
        .function("hasImportSource", &libcellml::Importer::hasImportSource)
    ;
}

