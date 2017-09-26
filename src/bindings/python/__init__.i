%module(package="libcellml") __init__

//TODO: http://www.swig.org/Doc1.3/Python.html#Python_nn65

%pythoncode %{
from libcellml.component import Component
from libcellml.componententity import ComponentEntity
from libcellml.entity import Entity
from libcellml.error import Error
from libcellml.importedentity import ImportedEntity
from libcellml.importsource import Import as ImportSource #TODO
from libcellml.logger import Logger
from libcellml.model import Model
from libcellml.namedentity import NamedEntity
from libcellml.printer import Printer
from libcellml.units import Units
from libcellml.variable import Variable

class InterfaceType:
    NONE = Variable.InterfaceType_NONE
    PRIVATE = Variable.InterfaceType_PRIVATE
    PUBLIC = Variable.InterfaceType_PUBLIC
    PUBLIC_AND_PRIVATE = Variable.InterfaceType_PUBLIC_AND_PRIVATE
Variable.InterfaceType = InterfaceType()
del(
    Variable.InterfaceType_NONE,
    Variable.InterfaceType_PRIVATE,
    Variable.InterfaceType_PUBLIC,
    Variable.InterfaceType_PUBLIC_AND_PRIVATE,
    InterfaceType
)

class StandardUnit:
    AMPERE = Units.StandardUnit_AMPERE
    BECQUEREL = Units.StandardUnit_BECQUEREL
    CANDELA = Units.StandardUnit_CANDELA
    COULOMB = Units.StandardUnit_COULOMB
    DIMENSIONLESS = Units.StandardUnit_DIMENSIONLESS
    FARAD = Units.StandardUnit_FARAD
    GRAM = Units.StandardUnit_GRAM
    GRAY = Units.StandardUnit_GRAY
    HENRY = Units.StandardUnit_HENRY
    HERTZ = Units.StandardUnit_HERTZ
    JOULE = Units.StandardUnit_JOULE
    KATAL = Units.StandardUnit_KATAL
    KELVIN = Units.StandardUnit_KELVIN
    KILOGRAM = Units.StandardUnit_KILOGRAM
    LITER = Units.StandardUnit_LITER
    LITRE = Units.StandardUnit_LITRE
    LUMEN = Units.StandardUnit_LUMEN
    LUX = Units.StandardUnit_LUX
    METER = Units.StandardUnit_METER
    METRE = Units.StandardUnit_METRE
    MOLE = Units.StandardUnit_MOLE
    NEWTON = Units.StandardUnit_NEWTON
    OHM = Units.StandardUnit_OHM
    PASCAL = Units.StandardUnit_PASCAL
    RADIAN = Units.StandardUnit_RADIAN
    SECOND = Units.StandardUnit_SECOND
    SIEMENS = Units.StandardUnit_SIEMENS
    SIEVERT = Units.StandardUnit_SIEVERT
    STERADIAN = Units.StandardUnit_STERADIAN
    TESLA = Units.StandardUnit_TESLA
    VOLT = Units.StandardUnit_VOLT
    WATT = Units.StandardUnit_WATT
    WEBER = Units.StandardUnit_WEBER
Units.StandardUnit = StandardUnit()
del(
    StandardUnit,
    Units.StandardUnit_AMPERE,
    Units.StandardUnit_BECQUEREL,
    Units.StandardUnit_CANDELA,
    Units.StandardUnit_COULOMB,
    Units.StandardUnit_DIMENSIONLESS,
    Units.StandardUnit_FARAD,
    Units.StandardUnit_GRAM,
    Units.StandardUnit_GRAY,
    Units.StandardUnit_HENRY,
    Units.StandardUnit_HERTZ,
    Units.StandardUnit_JOULE,
    Units.StandardUnit_KATAL,
    Units.StandardUnit_KELVIN,
    Units.StandardUnit_KILOGRAM,
    Units.StandardUnit_LITER,
    Units.StandardUnit_LITRE,
    Units.StandardUnit_LUMEN,
    Units.StandardUnit_LUX,
    Units.StandardUnit_METER,
    Units.StandardUnit_METRE,
    Units.StandardUnit_MOLE,
    Units.StandardUnit_NEWTON,
    Units.StandardUnit_OHM,
    Units.StandardUnit_PASCAL,
    Units.StandardUnit_RADIAN,
    Units.StandardUnit_SECOND,
    Units.StandardUnit_SIEMENS,
    Units.StandardUnit_SIEVERT,
    Units.StandardUnit_STERADIAN,
    Units.StandardUnit_TESLA,
    Units.StandardUnit_VOLT,
    Units.StandardUnit_WATT,
    Units.StandardUnit_WEBER,
)

import libcellml.enumerations
class Prefix:
    YOTTA = libcellml.enumerations.Prefix_YOTTA
    ZETTA = libcellml.enumerations.Prefix_ZETTA
    EXA = libcellml.enumerations.Prefix_EXA
    PETA = libcellml.enumerations.Prefix_PETA
    TERA = libcellml.enumerations.Prefix_TERA
    GIGA = libcellml.enumerations.Prefix_GIGA
    MEGA = libcellml.enumerations.Prefix_MEGA
    KILO = libcellml.enumerations.Prefix_KILO
    HECTO = libcellml.enumerations.Prefix_HECTO
    DECA = libcellml.enumerations.Prefix_DECA
    DECI = libcellml.enumerations.Prefix_DECI
    CENTI = libcellml.enumerations.Prefix_CENTI
    MILLI = libcellml.enumerations.Prefix_MILLI
    MICRO = libcellml.enumerations.Prefix_MICRO
    NANO = libcellml.enumerations.Prefix_NANO
    PICO = libcellml.enumerations.Prefix_PICO
    FEMTO = libcellml.enumerations.Prefix_FEMTO
    ATTO = libcellml.enumerations.Prefix_ATTO
    ZEPTO = libcellml.enumerations.Prefix_ZEPTO
    YOCTO = libcellml.enumerations.Prefix_YOCTO
Units.Prefix = Prefix()
del(Prefix, libcellml.enumerations)
%}
