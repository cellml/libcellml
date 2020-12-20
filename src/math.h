/*
Copyright libCellML Contributors

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

#pragma once

#include <string>

namespace libcellml {

/**
 * @brief Compare math to determine if it is equal.
 *
 * Compare the given math strings to determin if they are equal or not.
 * The current test is a simplistic comparison of string equality.
 *
 * @param math1 The first parameter to compare against parameter two.
 * @param math2 The second parameter to compare against parameter one.
 * @return Return @c true if the @p math1 is equal to @p math2, @c false otherwise.
 */
bool compareMath(const std::string &math1, const std::string &math2);

} // namespace libcellml
