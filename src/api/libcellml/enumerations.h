/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#ifndef LIBCELLML_LIBCELLML_ENUMERATIONS_H_
#define LIBCELLML_LIBCELLML_ENUMERATIONS_H_

/** @file */

namespace libcellml {

/**
 * @brief The CELLML_FORMATS enum.
 * Enum describing the formats that are available for
 * serialisation.
 */
enum CELLML_FORMATS
{
     CELLML_FORMAT_XML = 0 /**< XML format for CellML files. */
};

/**
 * @brief The CELLML_PREFIXES enum.
 * Enum describing the prefixes that are available for
 * units.
 */
enum CELLML_PREFIXES
{
    CELLML_PREFIX_YOTTA =  24,
    CELLML_PREFIX_ZETTA =  21,
    CELLML_PREFIX_EXA   =  18,
    CELLML_PREFIX_PETA  =  15,
    CELLML_PREFIX_TERA  =  12,
    CELLML_PREFIX_GIGA  =   9,
    CELLML_PREFIX_MEGA  =   6,
    CELLML_PREFIX_KILO  =   3,
    CELLML_PREFIX_HECTO =   2,
    CELLML_PREFIX_DECA  =   1,
    CELLML_PREFIX_UNIT  =   0,
    CELLML_PREFIX_DECI  =  -1,
    CELLML_PREFIX_CENTI =  -2,
    CELLML_PREFIX_MILLI =  -3,
    CELLML_PREFIX_MICRO =  -6,
    CELLML_PREFIX_NANO  =  -9,
    CELLML_PREFIX_PICO  = -12,
    CELLML_PREFIX_FEMTO = -15,
    CELLML_PREFIX_ATTO  = -18,
    CELLML_PREFIX_ZEPTO = -21,
    CELLML_PREFIX_YOCTO = -24
};

/**
 * @brief The CELLML_STANDARD_UNITS enum.
 * Enum describing the standard units that are suitable for variable declarations
 * or attached to bare numbers in mathematics.  The enum comprises of
 * the SI base units, the SI derived units with special names and symbols, and
 * some additional units commonly used in the types of biological models likely
 * to be defined using CellML.
 */
enum CELLML_STANDARD_UNITS
{
    CELLML_STANDARD_UNIT_AMPERE, /**< Base SI unit ampere. */
    CELLML_STANDARD_UNIT_BECQUEREL, /**< Derived SI unit becquerel. */
    CELLML_STANDARD_UNIT_CANDELA, /**< Base SI unit candela. */
    CELLML_STANDARD_UNIT_CELSIUS, /**< Derived SI unit celsius. */
    CELLML_STANDARD_UNIT_COULOMB, /**< Derived SI unit coulomb. */
    CELLML_STANDARD_UNIT_DIMENSIONLESS, /**< Convenience unit dimensionless. */
    CELLML_STANDARD_UNIT_FARAD, /**< Derived SI unit farad. */
    CELLML_STANDARD_UNIT_GRAM, /**< Convenience unit gram. */
    CELLML_STANDARD_UNIT_GRAY, /**< Derived SI unit gray. */
    CELLML_STANDARD_UNIT_HENRY, /**< Derived SI unit henry. */
    CELLML_STANDARD_UNIT_HERTZ, /**< Derived SI unit hertz. */
    CELLML_STANDARD_UNIT_JOULE, /**< Derived SI unit joule. */
    CELLML_STANDARD_UNIT_KATAL, /**< Derived SI unit katal. */
    CELLML_STANDARD_UNIT_KELVIN, /**< Base SI unit kelvin. */
    CELLML_STANDARD_UNIT_KILOGRAM, /**< Base SI unit kilogram. */
    CELLML_STANDARD_UNIT_LITER, /**< Convenience unit liter (alternative spelling). */
    CELLML_STANDARD_UNIT_LITRE, /**< Convenience unit litre. */
    CELLML_STANDARD_UNIT_LUMEN, /**< Derived SI unit lumen. */
    CELLML_STANDARD_UNIT_LUX, /**< Derived SI unit lux. */
    CELLML_STANDARD_UNIT_METER, /**< Base SI unit meter. */
    CELLML_STANDARD_UNIT_METRE, /**< Base SI unit metre (alternative spelling). */
    CELLML_STANDARD_UNIT_MOLE, /**< Base SI unit mole. */
    CELLML_STANDARD_UNIT_NEWTON, /**< Derived SI unit newton. */
    CELLML_STANDARD_UNIT_OHM, /**< Derived SI unit ohm. */
    CELLML_STANDARD_UNIT_PASCAL, /**< Derived SI unit pascal. */
    CELLML_STANDARD_UNIT_RADIAN, /**< Derived SI unit radian. */
    CELLML_STANDARD_UNIT_SECOND, /**< Base SI unit second. */
    CELLML_STANDARD_UNIT_SIEMENS, /**< Derived SI unit siemens. */
    CELLML_STANDARD_UNIT_SIEVERT, /**< Derived SI unit sievert. */
    CELLML_STANDARD_UNIT_STERADIAN, /**< Derived SI unit steradian. */
    CELLML_STANDARD_UNIT_TESLA, /**< Derived SI unit tesla. */
    CELLML_STANDARD_UNIT_VOLT, /**< Derived SI unit volt. */
    CELLML_STANDARD_UNIT_WATT, /**< Derived SI unit watt. */
    CELLML_STANDARD_UNIT_WEBER, /**< Derived SI unit weber. */
};


}

#endif /* LIBCELLML_LIBCELLML_ENUMERATIONS_H_ */

