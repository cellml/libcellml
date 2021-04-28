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

#include <any>
#include <map>
#include <unordered_set>
#include <vector>

#include "libcellml/types.h"

namespace libcellml {

using ComponentNameMap = std::map<std::string, ComponentPtr>; /**< Type definition for map of component name to component pointer. */

using IndexStack = std::vector<size_t>; /**< Type definition for tracking indicies. */
using EquivalenceMap = std::map<IndexStack, std::vector<IndexStack>>; /**< Type definition for map of variable equivalences defined over model. */

using NameList = std::vector<std::string>; /**< Type definition for list of names. */
using StringStringMap = std::map<std::string, std::string>; /**< Type definition for map of string to string. */

// VariableMap
using VariableMap = std::vector<VariablePairPtr>; /**< Type definition for vector of VariablePair.*/
using VariableMapIterator = VariableMap::const_iterator; /**< Type definition of const iterator for vector of VariablePair.*/

// ComponentMap
using ComponentPair = std::pair<ComponentPtr, ComponentPtr>; /**< Type definition for Component pointer pair.*/
using ComponentMap = std::vector<ComponentPair>; /**< Type definition for vector of ComponentPair.*/
using ComponentMapIterator = ComponentMap::const_iterator; /**< Type definition of const iterator for vector of ComponentPair.*/

using VariablePtrs = std::vector<VariablePtr>; /**< Type definition for list of variables. */

using IdMap = std::map<std::string, std::pair<int, std::vector<std::string>>>; /**< Type definition for map of IDs in Validator. **/
using ImportLibrary = std::map<std::string, ModelPtr>; /** Type definition for library map of imported models. */
using IdList = std::unordered_set<std::string>; /**< Type definition for list of identifiers. */

using ComponentWeakPtr = std::weak_ptr<Component>; /**< Type definition for weak component pointer. */
using ImportSourceWeakPtr = std::weak_ptr<ImportSource>; /**< Type definition for weak import source pointer. */
using ModelWeakPtr = std::weak_ptr<Model>; /**< Type definition for weak model pointer. */
using ResetWeakPtr = std::weak_ptr<Reset>; /**< Type definition for weak reset pointer. */
using UnitsWeakPtr = std::weak_ptr<Units>; /**< Type definition for weak units pointer. */
using VariableWeakPtr = std::weak_ptr<Variable>; /**< Type definition for weak variable pointer. */

using ComponentConstPtr = std::shared_ptr<const Component>; /**< Type definition for shared component const pointer. */
using ComponentEntityConstPtr = std::shared_ptr<const ComponentEntity>; /**< Type definition for shared component entity const pointer. */
using ModelConstPtr = std::shared_ptr<const Model>; /**< Type definition for shared model const pointer. */
using ParentedEntityConstPtr = std::shared_ptr<const ParentedEntity>; /**< Type definition for shared parented entity const pointer. */

using ConnectionMap = std::map<VariablePtr, VariablePtr>; /**< Type definition for a connection map.*/

using HistoryEntry = std::tuple<std::string, std::string, std::string>; /**< Type definition for a history entry.*/
using History = std::vector<HistoryEntry>; /**< Type definition for history.*/

using ImportHistoryEntry = std::pair<ModelPtr, std::string>; /**< Type definition for an import history entry.*/
using ImportHistory = std::vector<ImportHistoryEntry>; /**< Type definition for import history.*/

using Strings = std::vector<std::string>; /**< Type definition for strings.*/

} // namespace libcellml
