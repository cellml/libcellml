
#include <emscripten/bind.h>

#include "libcellml/units.h"

using namespace emscripten;

class EmUnits: public libcellml::Units
{
public:
    bool isBaseUnit() const {return libcellml::Units::isBaseUnit();}
    bool isImport() const {return libcellml::Units::isImport();}

    void addUnit(const std::string &reference, const std::string &prefix, double exponent=1.0,
                 double multiplier=1.0, const std::string &id="") {libcellml::Units::addUnit(reference, prefix, exponent, multiplier, id);}
    void addUnit(const std::string &reference, libcellml::Units::Prefix prefix, double exponent=1.0,
                 double multiplier=1.0, const std::string &id="") {libcellml::Units::addUnit(reference, prefix, exponent, multiplier, id);}
    void addUnit(const std::string &reference, double prefix, double exponent,
                 double multiplier=1.0, const std::string &id="") {libcellml::Units::addUnit(reference, prefix, exponent, multiplier, id);}
    void addUnit(const std::string &reference, double exponent, const std::string &id="") {libcellml::Units::addUnit(reference, exponent, id);}
    void addUnit(const std::string &reference) {libcellml::Units::addUnit(reference);}
    void addUnit(libcellml::Units::StandardUnit standardRef, const std::string &prefix, double exponent=1.0,
                 double multiplier=1.0, const std::string &id="") {libcellml::Units::addUnit(standardRef, prefix, exponent, multiplier, id);}
    void addUnit(libcellml::Units::StandardUnit standardRef, libcellml::Units::Prefix prefix, double exponent=1.0,
                 double multiplier=1.0, const std::string &id="") {libcellml::Units::addUnit(standardRef, prefix, exponent, multiplier, id);}
    void addUnit(libcellml::Units::StandardUnit standardRef, double prefix, double exponent,
                 double multiplier=1.0, const std::string &id="") {libcellml::Units::addUnit(standardRef, prefix, exponent, multiplier, id);}
    void addUnit(libcellml::Units::StandardUnit standardRef, double exponent, const std::string &id="") {libcellml::Units::addUnit(standardRef, exponent, id);}
    void addUnit(libcellml::Units::StandardUnit standardRef) {libcellml::Units::addUnit(standardRef);}
    bool removeUnit(size_t index) {return libcellml::Units::removeUnit(index);}
    bool removeUnit(const std::string &reference) {return libcellml::Units::removeUnit(reference);}
    bool removeUnit(StandardUnit standardRef) {return libcellml::Units::removeUnit(standardRef);}
    void removeAllUnits() {libcellml::Units::removeAllUnits();}
    size_t unitCount() {return libcellml::Units::unitCount();}
    void setSourceUnits(const libcellml::ImportSourcePtr &importSource, const std::string &name) {libcellml::Units::setSourceUnits(importSource, name);}
};

EMSCRIPTEN_BINDINGS(libcellml_units) {
    enum_<libcellml::Units::StandardUnit>("StandardUnit")
        .value("AMPERE", libcellml::Units::StandardUnit::AMPERE)
        .value("BECQUEREL", libcellml::Units::StandardUnit::BECQUEREL)
        .value("CANDELA", libcellml::Units::StandardUnit::CANDELA)
        .value("COULOMB", libcellml::Units::StandardUnit::COULOMB)
        .value("DIMENSIONLESS", libcellml::Units::StandardUnit::DIMENSIONLESS)
        .value("FARAD", libcellml::Units::StandardUnit::FARAD)
        .value("GRAM", libcellml::Units::StandardUnit::GRAM)
        .value("GRAY", libcellml::Units::StandardUnit::GRAY)
        .value("HENRY", libcellml::Units::StandardUnit::HENRY)
        .value("HERTZ", libcellml::Units::StandardUnit::HERTZ)
        .value("JOULE", libcellml::Units::StandardUnit::JOULE)
        .value("KATAL", libcellml::Units::StandardUnit::KATAL)
        .value("KELVIN", libcellml::Units::StandardUnit::KELVIN)
        .value("KILOGRAM", libcellml::Units::StandardUnit::KILOGRAM)
        .value("LITRE", libcellml::Units::StandardUnit::LITRE)
        .value("LUMEN", libcellml::Units::StandardUnit::LUMEN)
        .value("LUX", libcellml::Units::StandardUnit::LUX)
        .value("METRE", libcellml::Units::StandardUnit::METRE)
        .value("MOLE", libcellml::Units::StandardUnit::MOLE)
        .value("NEWTON", libcellml::Units::StandardUnit::NEWTON)
        .value("OHM", libcellml::Units::StandardUnit::OHM)
        .value("PASCAL", libcellml::Units::StandardUnit::PASCAL)
        .value("RADIAN", libcellml::Units::StandardUnit::RADIAN)
        .value("SECOND", libcellml::Units::StandardUnit::SECOND)
        .value("SIEMENS", libcellml::Units::StandardUnit::SIEMENS)
        .value("SIEVERT", libcellml::Units::StandardUnit::SIEVERT)
        .value("STERADIAN", libcellml::Units::StandardUnit::STERADIAN)
        .value("TESLA", libcellml::Units::StandardUnit::TESLA)
        .value("VOLT", libcellml::Units::StandardUnit::VOLT)
        .value("WATT", libcellml::Units::StandardUnit::WATT)
        .value("WEBER", libcellml::Units::StandardUnit::WEBER)
    ;

    //    class_<libcellml::Units, base<libcellml::NamedEntity>>("Units")
    class_<libcellml::Units, base<libcellml::NamedEntity>>("Units")
        .smart_ptr_constructor("Units", select_overload<libcellml::UnitsPtr()>(&libcellml::Units::create))
//        .smart_ptr_constructor("UnitsSetName", select_overload<libcellml::UnitsPtr(const std::string &)>(&libcellml::Units::create))
//        .smart_ptr_constructor("Units", &libcellml::Units::create)
        .function("isBaseUnit", &libcellml::Units::isBaseUnit)
//        .function("isImport", &libcellml::Units::isImport)
        .function("addUnit", select_overload<void(const std::string &, int, double, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByStringPrefix", select_overload<void(const std::string &, const std::string &, double, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByEnumPrefix", select_overload<void(const std::string &, libcellml::Units::Prefix, double, double, const std::string &)>(&libcellml::Units::addUnit))
//        .function("addUnitByDoublePrefix", select_overload<void(const std::string &, double, double, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByExponent", select_overload<void(const std::string &, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByReference", select_overload<void(const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByStandardUnitStringPrefix", select_overload<void(libcellml::Units::StandardUnit, const std::string &, double, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByStandardUnitEnumPrefix", select_overload<void(libcellml::Units::StandardUnit, libcellml::Units::Prefix, double, double, const std::string &)>(&libcellml::Units::addUnit))
//        .function("addUnitByStandardUnitDoublePrefix", select_overload<void(libcellml::Units::StandardUnit, double, double, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByStandardUnitAndExponent", select_overload<void(libcellml::Units::StandardUnit, double, const std::string &)>(&libcellml::Units::addUnit))
        .function("addUnitByStandardUnit", select_overload<void(libcellml::Units::StandardUnit)>(&libcellml::Units::addUnit))
            .function("unitAttributeReferenceByIndex", &libcellml::Units::unitAttributeReferenceByIndex)
            .function("unitAttributePrefixByIndex", &libcellml::Units::unitAttributePrefixByIndex)
            .function("unitAttributeExponentByIndex", &libcellml::Units::unitAttributeExponentByIndex)
            .function("unitAttributeMultiplierByIndex", &libcellml::Units::unitAttributeMultiplierByIndex)
//        .function("unitAttributesByIndex", select_overload<void(size_t, std::string&, std::string&, double &, double &, std::string&) const>(&libcellml::Units::unitAttributes))
//        .function("getUnitAttributesByName", select_overload<void(const std::string &, std::string&, double &, double &, std::string&) const>(&libcellml::Units::getUnitAttributes))
//        .function("getUnitAttributesByStandardUnit", select_overload<void(libcellml::Units::StandardUnit, std::string&, double &, double &, std::string&) const>(&libcellml::Units::getUnitAttributes))
        .function("removeUnitByIndex", select_overload<bool(size_t)>(&libcellml::Units::removeUnit))
        .function("removeUnitByName", select_overload<bool(const std::string &)>(&libcellml::Units::removeUnit))
        .function("removeUnitByStandardUnit", select_overload<bool(libcellml::Units::StandardUnit)>(&libcellml::Units::removeUnit))
        .function("setSourceUnits", &libcellml::Units::setSourceUnits)
        .function("removeAllUnits", &libcellml::Units::removeAllUnits)
        .function("unitCount", &libcellml::Units::unitCount)
            .function("clone", &libcellml::Units::clone)
            .function("isImport", &libcellml::ImportedEntity::isImport)
            .function("importReference", &libcellml::ImportedEntity::importReference)
            .function("importSource", &libcellml::ImportedEntity::importSource)
            .function("setImportSource", &libcellml::ImportedEntity::setImportSource)
            .function("setImportReference", &libcellml::ImportedEntity::setImportReference)
    ;
}
