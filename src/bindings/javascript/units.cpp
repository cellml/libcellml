
#include <emscripten/bind.h>

#include "libcellml/exportdefinitions.h"
#include "libcellml/units.h"

using namespace emscripten;

namespace libcellml {

class UnitsImportedEntity; /**< Forward declaration of Units class. */
using UnitsImportedEntityPtr = std::shared_ptr<UnitsImportedEntity>; /**< Type definition for shared units pointer. */

class LIBCELLML_EXPORT UnitsImportedEntity: public Units
{
public:
  static UnitsImportedEntityPtr create() noexcept
  {
    return std::shared_ptr<UnitsImportedEntity> {new UnitsImportedEntity {}};
  }

  static UnitsImportedEntityPtr create(const std::string &name) noexcept
  {
    return std::shared_ptr<UnitsImportedEntity> {new UnitsImportedEntity {name}};
  }

  // ImportedEntity methods.
  bool isImport() const
  {
    return Units::isImport();
  }

  ImportSourcePtr importSource() const
  {
    return Units::importSource();
  }

  void setImportSource(const ImportSourcePtr &importSource)
  {
    Units::setImportSource(importSource);
  }

  std::string importReference() const
  {
    return Units::importReference();
  }

  void setImportReference(const std::string &reference)
  {
    return Units::setImportReference(reference);
  }

  bool isResolved() const
  {
    return Units::isResolved();
  }

  // Units methods.
  bool isBaseUnit() const
  {
    return Units::isBaseUnit();
  }

  void addUnit(const std::string &reference, const std::string &prefix, double exponent, double multiplier)
  {
    return Units::addUnit(reference, prefix, exponent, multiplier);
  }

  void addUnit(const std::string &reference, Prefix prefix, double exponent, double multiplier)
  {
    return Units::addUnit(reference, prefix, exponent, multiplier);
  }

  void addUnit(const std::string &reference, int prefix, double exponent, double multiplier)
  {
    return Units::addUnit(reference, prefix, exponent, multiplier);
  }

  void addUnit(const std::string &reference, double exponent)
  {
    Units::addUnit(reference, exponent);
  }

  void addUnit(const std::string &reference)
  {
    Units::addUnit(reference);
  }

  void addUnit(StandardUnit standardUnit, const std::string &prefix, double exponent, double multiplier)
  {
    Units::addUnit(standardUnit, prefix, exponent, multiplier);
  }

  void addUnit(StandardUnit standardUnit, Prefix prefix, double exponent, double multiplier)
  {
    Units::addUnit(standardUnit, prefix, exponent, multiplier);
  }

  void addUnit(StandardUnit standardUnit, int prefix, double exponent, double multiplier)
  {
    Units::addUnit(standardUnit, prefix, exponent, multiplier);
  }

  void addUnit(StandardUnit standardUnit, double exponent)
  {
    Units::addUnit(standardUnit, exponent);
  }

  void addUnit(StandardUnit standardUnit)
  {
    Units::addUnit(standardUnit);
  }

  std::string unitAttributeReference(size_t index) const
  {
    return Units::unitAttributeReference(index);
  }

  std::string unitAttributePrefix(size_t index) const
  {
    return Units::unitAttributePrefix(index);
  }

  double unitAttributeExponent(size_t index) const
  {
    return Units::unitAttributeExponent(index);
  }

  double unitAttributeMultiplier(size_t index) const
  {
    return Units::unitAttributeMultiplier(index);
  }

  bool removeUnit(size_t index)
  {
    return Units::removeUnit(index);
  }

  bool removeUnit(const std::string &reference)
  {
    return Units::removeUnit(reference);
  }

  bool removeUnit(StandardUnit standardUnit)
  {
    return Units::removeUnit(standardUnit);
  }

  void removeAllUnits()
  {
    Units::removeAllUnits();
  }

  void setSourceUnits(ImportSourcePtr &importSource, const std::string &name)
  {
    Units::setSourceUnits(importSource, name);
  }

  size_t unitCount() const
  {
    return Units::unitCount();
  }

  bool requiresImports() const
  {
    return Units::requiresImports();
  }

  UnitsImportedEntityPtr clone() const
  {
    auto units = create();

    units->setId(id());
    units->setName(name());

    if (isImport()) {
        units->setImportSource(importSource());
    }

    units->setImportReference(importReference());

    std::string reference;
    std::string prefix;
    std::string id;
    double exponent;
    double multiplier;
    for (size_t index = 0; index < unitCount(); ++index) {
        unitAttributes(index, reference, prefix, exponent, multiplier, id);
        units->addUnit(reference, prefix, exponent, multiplier);
        units->setUnitId(index, id);
    }

    return units;
  }

  bool setUnitId(size_t index, const std::string &id)
  {
    return Units::setUnitId(index, id);
  }

  std::string unitId(size_t index) const
  {
    return Units::unitId(index);
  }

  static double scalingFactor(const UnitsImportedEntityPtr &units1, const UnitsImportedEntityPtr &units2, bool checkCompatibility = true)
  {
    return Units::scalingFactor(units1, units2, checkCompatibility);
  }

  static bool compatible(const UnitsImportedEntityPtr &units1, const UnitsImportedEntityPtr &units2)
  {
    return Units::compatible(units1, units2);
  }

  static bool equivalent(const UnitsImportedEntityPtr &units1, const UnitsImportedEntityPtr &units2)
  {
    return Units::equivalent(units1, units2);
  }

private:
    UnitsImportedEntity()
      : Units()
    {

    }
    explicit UnitsImportedEntity(const std::string &name)
      : Units(name)
    {

    }

};

}

EMSCRIPTEN_BINDINGS(libcellml_units) {

    enum_<libcellml::Units::Prefix>("Prefix")
        .value("YOTTA", libcellml::Units::Prefix::YOTTA)
        .value("ZETTA", libcellml::Units::Prefix::ZETTA)
        .value("EXA", libcellml::Units::Prefix::EXA)
        .value("PETA", libcellml::Units::Prefix::PETA)
        .value("TERA", libcellml::Units::Prefix::TERA)
        .value("GIGA", libcellml::Units::Prefix::GIGA)
        .value("MEGA", libcellml::Units::Prefix::MEGA)
        .value("KILO", libcellml::Units::Prefix::KILO)
        .value("HECTO", libcellml::Units::Prefix::HECTO)
        .value("DECA", libcellml::Units::Prefix::DECA)
        .value("DECI", libcellml::Units::Prefix::DECI)
        .value("CENTI", libcellml::Units::Prefix::CENTI)
        .value("MILLI", libcellml::Units::Prefix::MILLI)
        .value("MICRO", libcellml::Units::Prefix::MICRO)
        .value("NANO", libcellml::Units::Prefix::NANO)
        .value("PICO", libcellml::Units::Prefix::PICO)
        .value("FEMTO", libcellml::Units::Prefix::FEMTO)
        .value("ATTO", libcellml::Units::Prefix::ATTO)
        .value("ZEPTO", libcellml::Units::Prefix::ZEPTO)
        .value("YOCTO", libcellml::Units::Prefix::YOCTO)
    ;

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

    class_<libcellml::UnitsImportedEntity, base<libcellml::NamedEntity>>("Units")
        .smart_ptr<std::shared_ptr<libcellml::UnitsImportedEntity>>("UnitsPtr")
        .constructor(select_overload<libcellml::UnitsImportedEntityPtr()>(&libcellml::UnitsImportedEntity::create))
        .constructor(select_overload<libcellml::UnitsImportedEntityPtr(const std::string &)>(&libcellml::UnitsImportedEntity::create))
        .function("isBaseUnit", &libcellml::UnitsImportedEntity::isBaseUnit)
        .function("addUnitByReferenceStringPrefix", select_overload<void(const std::string &, const std::string &, double, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByReferenceEnumPrefix", select_overload<void(const std::string &, libcellml::Units::Prefix, double, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByReferenceIntPrefix", select_overload<void(const std::string &, int, double, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByReferenceExponent", select_overload<void(const std::string &, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByReference", select_overload<void(const std::string &)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByStandardUnitStringPrefix", select_overload<void(libcellml::Units::StandardUnit, const std::string &, double, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByStandardUnitEnumPrefix", select_overload<void(libcellml::Units::StandardUnit, libcellml::Units::Prefix, double, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByStandardUnitIntPrefix", select_overload<void(libcellml::Units::StandardUnit, int, double, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByStandardUnitExponent", select_overload<void(libcellml::Units::StandardUnit, double)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("addUnitByStandardUnit", select_overload<void(libcellml::Units::StandardUnit)>(&libcellml::UnitsImportedEntity::addUnit))
        .function("unitAttributeReference", &libcellml::UnitsImportedEntity::unitAttributeReference)
        .function("unitAttributePrefix", &libcellml::UnitsImportedEntity::unitAttributePrefix)
        .function("unitAttributeExponent", &libcellml::UnitsImportedEntity::unitAttributeExponent)
        .function("unitAttributeMultiplier", &libcellml::UnitsImportedEntity::unitAttributeMultiplier)
        .function("removeUnitByIndex", select_overload<bool(size_t)>(&libcellml::UnitsImportedEntity::removeUnit))
        .function("removeUnitByReference", select_overload<bool(const std::string &)>(&libcellml::UnitsImportedEntity::removeUnit))
        .function("removeUnitByStandardUnit", select_overload<bool(libcellml::Units::StandardUnit)>(&libcellml::UnitsImportedEntity::removeUnit))
        .function("removeAllUnits", &libcellml::UnitsImportedEntity::removeAllUnits)
        .function("setSourceUnits", &libcellml::UnitsImportedEntity::setSourceUnits)
        .function("unitCount", &libcellml::UnitsImportedEntity::unitCount)
        .function("requiresImports", &libcellml::UnitsImportedEntity::requiresImports)
        .function("clone", &libcellml::UnitsImportedEntity::clone)
        .function("setUnitId", &libcellml::UnitsImportedEntity::setUnitId)
        .function("unitId", &libcellml::UnitsImportedEntity::unitId)
        .function("isImport", &libcellml::UnitsImportedEntity::isImport)
        .function("importSource", &libcellml::UnitsImportedEntity::importSource)
        .function("setImportSource", &libcellml::UnitsImportedEntity::setImportSource)
        .function("importReference", &libcellml::UnitsImportedEntity::importReference)
        .function("setImportReference", &libcellml::UnitsImportedEntity::setImportReference)
        .function("isResolved", &libcellml::UnitsImportedEntity::isResolved)
        .class_function("scalingFactor", &libcellml::UnitsImportedEntity::scalingFactor)
        .class_function("compatible", &libcellml::UnitsImportedEntity::compatible)
        .class_function("equivalent", &libcellml::UnitsImportedEntity::equivalent)
    ;

}
