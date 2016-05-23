/*
Copyright 2015 libCellML Contributors

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

#ifndef LIBCELLML_LIBCELLML_VERSION_H_
#define LIBCELLML_LIBCELLML_VERSION_H_

#include <string>

#include "libcellml/libcellml_export.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief Get the version string.
 *
 * The version string is in the format x.y.z, where the "."s are literal, and x,y and z represent counting numbers,
 * in which case x is the major version, y the minor version, and z the patch level.
 *
 *  @return A string to represent the version.
 */
LIBCELLML_EXPORT const std::string versionString();

/**
 * @brief Get the version number.
 *
 * Returns the version of the library as a number.
 *
 * @return An unsigned int to represent the version.
 */
LIBCELLML_EXPORT unsigned int version();

}  // namespace libcellml

#endif  // LIBCELLML_LIBCELLML_VERSION_H_
