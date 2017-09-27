%define DOCSTRING
"Python bindings for libCellML

The purpose of libCellML is to create, manipulate, serialise, deserialise,
 validate and instantiate CellML models. In the first instance, all serialising
 and deserialising will be to and from standard strings and using the CellML
 XML format."
%enddef

%module(package="libcellml", docstring=DOCSTRING) __init__

//TODO: http://www.swig.org/Doc1.3/Python.html#Python_nn65

%pythoncode %{
from libcellml.component import Component
from libcellml.componententity import ComponentEntity
from libcellml.entity import Entity
from libcellml.error import Error
from libcellml.importedentity import ImportedEntity
from libcellml.importsource import ImportSource
from libcellml.logger import Logger
from libcellml.model import Model
from libcellml.namedentity import NamedEntity
from libcellml.parser import Parser
from libcellml.printer import Printer
from libcellml.units import Units
from libcellml.validator import Validator
from libcellml.variable import Variable
from libcellml.version import version, versionString

# Convert Error.Kind_X to Error.Kind.X
if 'Kind_COMPONENT' in dir(Error):
    class Kind:
        COMPONENT = Error.Kind_COMPONENT
        CONNECTION = Error.Kind_CONNECTION
        ENCAPSULATION = Error.Kind_ENCAPSULATION
        IMPORT = Error.Kind_IMPORT
        MATHML = Error.Kind_MATHML
        MODEL = Error.Kind_MODEL
        UNDEFINED = Error.Kind_UNDEFINED
        UNITS = Error.Kind_UNITS
        VARIABLE = Error.Kind_VARIABLE
        XML = Error.Kind_XML
    Error.Kind = Kind()
    del(
        Error.Kind_COMPONENT,
        Error.Kind_CONNECTION,
        Error.Kind_ENCAPSULATION,
        Error.Kind_IMPORT,
        Error.Kind_MATHML,
        Error.Kind_MODEL,
        Error.Kind_UNDEFINED,
        Error.Kind_UNITS,
        Error.Kind_VARIABLE,
        Error.Kind_XML,
        Kind
    )

# Convert Variable.InterfaceType_X to Variable.InterfaceType.X
if 'InterfaceType_NONE' in dir(Variable):
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

# Convert Units.StandardUnit_X to Units.StandardUnit.X
if 'StandardUnit_AMPERE' in dir(Units):
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

# Import Format and Prefix from enumerations
from libcellml import enumerations as er
class Format:
    XML = er.Format_XML
Format = Format()
class Prefix:
    YOTTA = er.Prefix_YOTTA
    ZETTA = er.Prefix_ZETTA
    EXA = er.Prefix_EXA
    PETA = er.Prefix_PETA
    TERA = er.Prefix_TERA
    GIGA = er.Prefix_GIGA
    MEGA = er.Prefix_MEGA
    KILO = er.Prefix_KILO
    HECTO = er.Prefix_HECTO
    DECA = er.Prefix_DECA
    DECI = er.Prefix_DECI
    CENTI = er.Prefix_CENTI
    MILLI = er.Prefix_MILLI
    MICRO = er.Prefix_MICRO
    NANO = er.Prefix_NANO
    PICO = er.Prefix_PICO
    FEMTO = er.Prefix_FEMTO
    ATTO = er.Prefix_ATTO
    ZEPTO = er.Prefix_ZEPTO
    YOCTO = er.Prefix_YOCTO
Units.Prefix = Prefix()
del(Prefix, er)

# Import SpecificationRules from specificationrule
import libcellml.specificationrule as sr
class SpecificationRule:
    UNDEFINED = sr.SpecificationRule_UNDEFINED
    MODEL_ELEMENT = sr.SpecificationRule_MODEL_ELEMENT
    MODEL_NAME = sr.SpecificationRule_MODEL_NAME
    MODEL_CHILD = sr.SpecificationRule_MODEL_CHILD
    IMPORT_HREF = sr.SpecificationRule_IMPORT_HREF
    IMPORT_CHILD = sr.SpecificationRule_IMPORT_CHILD
    IMPORT_CIRCULAR = sr.SpecificationRule_IMPORT_CIRCULAR
    IMPORT_UNITS_NAME = sr.SpecificationRule_IMPORT_UNITS_NAME
    IMPORT_UNITS_REF = sr.SpecificationRule_IMPORT_UNITS_REF
    IMPORT_COMPONENT_NAME = sr.SpecificationRule_IMPORT_COMPONENT_NAME
    IMPORT_COMPONENT_REF = sr.SpecificationRule_IMPORT_COMPONENT_REF
    UNITS_NAME = sr.SpecificationRule_UNITS_NAME
    UNITS_MODEL_UNIQUE = sr.SpecificationRule_UNITS_MODEL_UNIQUE
    UNITS_COMPONENT_UNIQUE = sr.SpecificationRule_UNITS_COMPONENT_UNIQUE
    UNITS_STANDARD = sr.SpecificationRule_UNITS_STANDARD
    UNITS_BASE = sr.SpecificationRule_UNITS_BASE
    UNITS_CHILD = sr.SpecificationRule_UNITS_CHILD
    UNIT_UNITS_REF = sr.SpecificationRule_UNIT_UNITS_REF
    UNIT_DIGRAPH = sr.SpecificationRule_UNIT_DIGRAPH
    UNIT_CIRCULAR_REF = sr.SpecificationRule_UNIT_CIRCULAR_REF
    UNIT_ATTRIBUTE = sr.SpecificationRule_UNIT_ATTRIBUTE
    UNIT_PREFIX = sr.SpecificationRule_UNIT_PREFIX
    UNIT_MULTIPLIER = sr.SpecificationRule_UNIT_MULTIPLIER
    UNIT_EXPONENT = sr.SpecificationRule_UNIT_EXPONENT
    COMPONENT_NAME = sr.SpecificationRule_COMPONENT_NAME
    COMPONENT_CHILD = sr.SpecificationRule_COMPONENT_CHILD
    VARIABLE_ATTRIBUTE = sr.SpecificationRule_VARIABLE_ATTRIBUTE
    VARIABLE_NAME = sr.SpecificationRule_VARIABLE_NAME
    VARIABLE_UNITS = sr.SpecificationRule_VARIABLE_UNITS
    VARIABLE_INTERFACE = sr.SpecificationRule_VARIABLE_INTERFACE
    VARIABLE_INITIAL_VALUE = sr.SpecificationRule_VARIABLE_INITIAL_VALUE
    ENCAPSULATION_COMPONENT_REF = \
        sr.SpecificationRule_ENCAPSULATION_COMPONENT_REF
    COMPONENT_REF_COMPONENT = sr.SpecificationRule_COMPONENT_REF_COMPONENT
    COMPONENT_REF_CHILD = sr.SpecificationRule_COMPONENT_REF_CHILD
    ENCAPSULATION_COMPONENT_REF_CHILD = \
        sr.SpecificationRule_ENCAPSULATION_COMPONENT_REF_CHILD
    CONNECTION_CHILD = sr.SpecificationRule_CONNECTION_CHILD
    CONNECTION_MAP_COMPONENTS = sr.SpecificationRule_CONNECTION_MAP_COMPONENTS
    CONNECTION_MAP_VARIABLES = sr.SpecificationRule_CONNECTION_MAP_VARIABLES
    MAP_COMPONENTS_COMPONENT1 = sr.SpecificationRule_MAP_COMPONENTS_COMPONENT1
    MAP_COMPONENTS_COMPONENT2 = sr.SpecificationRule_MAP_COMPONENTS_COMPONENT2
    MAP_VARIABLES_VARIABLE1 = sr.SpecificationRule_MAP_VARIABLES_VARIABLE1
    MAP_VARIABLES_VARIABLE2 = sr.SpecificationRule_MAP_VARIABLES_VARIABLE2
SpecificationRule = SpecificationRule()
del(sr)

%}
