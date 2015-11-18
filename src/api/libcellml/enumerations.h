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
 * @brief The FORMATS enum.
 * Enum describing the formats that are available for
 * serialisation.
 */
enum FORMATS
{
     FORMAT_XML = 0 /**< XML format for CellML files. */
};

/**
 * @brief The PREFIXES enum.
 * Enum describing the prefixes that are available for
 * units.
 */
enum PREFIXES
{
    PREFIX_YOTTA =  24,
    PREFIX_ZETTA =  21,
    PREFIX_EXA   =  18,
    PREFIX_PETA  =  15,
    PREFIX_TERA  =  12,
    PREFIX_GIGA  =   9,
    PREFIX_MEGA  =   6,
    PREFIX_KILO  =   3,
    PREFIX_HECTO =   2,
    PREFIX_DECA  =   1,
    PREFIX_UNIT  =   0,
    PREFIX_DECI  =  -1,
    PREFIX_CENTI =  -2,
    PREFIX_MILLI =  -3,
    PREFIX_MICRO =  -6,
    PREFIX_NANO  =  -9,
    PREFIX_PICO  = -12,
    PREFIX_FEMTO = -15,
    PREFIX_ATTO  = -18,
    PREFIX_ZEPTO = -21,
    PREFIX_YOCTO = -24
};

/**
 * @brief The STANDARD_UNITS enum.
 * Enum describing the standard units that are suitable for variable declarations
 * or attached to bare numbers in mathematics.  The enum comprises of
 * the SI base units, the SI derived units with special names and symbols, and
 * some additional units commonly used in the types of biological models likely
 * to be defined using CellML.
 */
enum STANDARD_UNITS
{
    STANDARD_UNIT_AMPERE, /**< Base SI unit ampere. */
    STANDARD_UNIT_BECQUEREL, /**< Derived SI unit becquerel. */
    STANDARD_UNIT_CANDELA, /**< Base SI unit candela. */
    STANDARD_UNIT_CELSIUS, /**< Derived SI unit celsius. */
    STANDARD_UNIT_COULOMB, /**< Derived SI unit coulomb. */
    STANDARD_UNIT_DIMENSIONLESS, /**< Convenience unit dimensionless. */
    STANDARD_UNIT_FARAD, /**< Derived SI unit farad. */
    STANDARD_UNIT_GRAM, /**< Convenience unit gram. */
    STANDARD_UNIT_GRAY, /**< Derived SI unit gray. */
    STANDARD_UNIT_HENRY, /**< Derived SI unit henry. */
    STANDARD_UNIT_HERTZ, /**< Derived SI unit hertz. */
    STANDARD_UNIT_JOULE, /**< Derived SI unit joule. */
    STANDARD_UNIT_KATAL, /**< Derived SI unit katal. */
    STANDARD_UNIT_KELVIN, /**< Base SI unit kelvin. */
    STANDARD_UNIT_KILOGRAM, /**< Base SI unit kilogram. */
    STANDARD_UNIT_LITER, /**< Convenience unit liter (alternative spelling). */
    STANDARD_UNIT_LITRE, /**< Convenience unit litre. */
    STANDARD_UNIT_LUMEN, /**< Derived SI unit lumen. */
    STANDARD_UNIT_LUX, /**< Derived SI unit lux. */
    STANDARD_UNIT_METER, /**< Base SI unit meter. */
    STANDARD_UNIT_METRE, /**< Base SI unit metre (alternative spelling). */
    STANDARD_UNIT_MOLE, /**< Base SI unit mole. */
    STANDARD_UNIT_NEWTON, /**< Derived SI unit newton. */
    STANDARD_UNIT_OHM, /**< Derived SI unit ohm. */
    STANDARD_UNIT_PASCAL, /**< Derived SI unit pascal. */
    STANDARD_UNIT_RADIAN, /**< Derived SI unit radian. */
    STANDARD_UNIT_SECOND, /**< Base SI unit second. */
    STANDARD_UNIT_SIEMENS, /**< Derived SI unit siemens. */
    STANDARD_UNIT_SIEVERT, /**< Derived SI unit sievert. */
    STANDARD_UNIT_STERADIAN, /**< Derived SI unit steradian. */
    STANDARD_UNIT_TESLA, /**< Derived SI unit tesla. */
    STANDARD_UNIT_VOLT, /**< Derived SI unit volt. */
    STANDARD_UNIT_WATT, /**< Derived SI unit watt. */
    STANDARD_UNIT_WEBER, /**< Derived SI unit weber. */
};


}

#endif /* LIBCELLML_LIBCELLML_ENUMERATIONS_H_ */

