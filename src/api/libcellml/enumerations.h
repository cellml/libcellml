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
limitations under the License.
*/

#ifndef LIBCELLML_LIBCELLML_ENUMERATIONS_H_
#define LIBCELLML_LIBCELLML_ENUMERATIONS_H_

/** @file */

namespace libcellml {

/**
 * @brief The Format enum class.
 *
 * Enum describing the formats that are available for
 * serialisation.
 */
enum class Format
{
     XML = 0 /**< XML format for CellML files. */
};

/**
 * @brief The Prefix enum class.
 *
 * Enum describing the prefixes that are available for
 * units.
 */
enum class Prefix
{
    YOTTA =  24,
    ZETTA =  21,
    EXA   =  18,
    PETA  =  15,
    TERA  =  12,
    GIGA  =   9,
    MEGA  =   6,
    KILO  =   3,
    HECTO =   2,
    DECA  =   1,
    DECI  =  -1,
    CENTI =  -2,
    MILLI =  -3,
    MICRO =  -6,
    NANO  =  -9,
    PICO  = -12,
    FEMTO = -15,
    ATTO  = -18,
    ZEPTO = -21,
    YOCTO = -24
};

}

#endif /* LIBCELLML_LIBCELLML_ENUMERATIONS_H_ */

