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

}

#endif /* LIBCELLML_LIBCELLML_ENUMERATIONS_H_ */

