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

#include <memory>

namespace libcellml {

// Input, output, and error handlers.
class Parser; /**< Forward declaration of Parser class. */
class Validator; /**< Forward declaration of Validator class. */

// CellML entities.
class Model; /**< Forward declaration of Model class. */
typedef std::shared_ptr<Model> ModelPtr; /**< Type definition for shared model pointer. */
class Component; /**< Forward declaration of Component class. */
typedef std::shared_ptr<Component> ComponentPtr; /**< Type definition for shared component pointer. */
class Error; /**< Forward declaration of Error class. */
typedef std::shared_ptr<Error> ErrorPtr; /**< Type definition for shared error pointer. */
class ImportSource; /**< Forward declaration of ImportSource class. */
typedef std::shared_ptr<ImportSource> ImportSourcePtr; /**< Type definition for shared import source pointer. */
class Units; /**< Forward declaration of Units class. */
typedef std::shared_ptr<Units> UnitsPtr; /**< Type definition for shared units pointer. */
class Variable; /**< Forward declaration of Variable class. */
typedef std::shared_ptr<Variable> VariablePtr; /**< Type definition for shared variable pointer. */

}
