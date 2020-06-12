
#include <emscripten/bind.h>

#include "libcellml/model.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_model) {

    class_<libcellml::Model, base<libcellml::ComponentEntity>>("Model")
        .smart_ptr_constructor("Model", select_overload<libcellml::ModelPtr()>(&libcellml::Model::create))
        .function("addUnits", &libcellml::Model::addUnits)
        .function("removeUnitsByIndex", select_overload<bool(size_t)>(&libcellml::Model::removeUnits))
        .function("removeUnitsByName", select_overload<bool(const std::string &)>(&libcellml::Model::removeUnits))
        .function("removeUnitsByUnits", select_overload<bool(const libcellml::UnitsPtr &)>(&libcellml::Model::removeUnits))
        .function("removeAllUnits", &libcellml::Model::removeAllUnits)
        .function("hasUnitsByName", select_overload<bool(const std::string &) const>(&libcellml::Model::hasUnits))
        .function("hasUnitsByUnits", select_overload<bool(const libcellml::UnitsPtr &) const>(&libcellml::Model::hasUnits))
        .function("unitsByIndex", select_overload<libcellml::UnitsPtr(size_t) const>(&libcellml::Model::units))
        .function("unitsByName", select_overload<libcellml::UnitsPtr(const std::string &) const>(&libcellml::Model::units))
        .function("takeUnitsByIndex", select_overload<libcellml::UnitsPtr(size_t)>(&libcellml::Model::takeUnits))
        .function("takeUnitsByName", select_overload<libcellml::UnitsPtr(const std::string &)>(&libcellml::Model::takeUnits))
        .function("replaceUnitsByIndex", select_overload<bool(size_t, const libcellml::UnitsPtr &)>(&libcellml::Model::replaceUnits))
        .function("replaceUnitsByName", select_overload<bool(const std::string &, const libcellml::UnitsPtr &)>(&libcellml::Model::replaceUnits))
        .function("replaceUnitsByUnits", select_overload<bool(const libcellml::UnitsPtr &, const libcellml::UnitsPtr &)>(&libcellml::Model::replaceUnits))
        .function("unitsCount", &libcellml::Model::unitsCount)
        .function("resolveImports", &libcellml::Model::resolveImports)
        .function("hasUnresolvedImports", &libcellml::Model::hasUnresolvedImports)
        .function("clone", &libcellml::Model::clone)
    ;
}
