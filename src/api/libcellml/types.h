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
#include <memory>

#include "libcellml/enums.h"

namespace libcellml {

// General classes.
class Analyser; /**< Forward declaration of Analyser class. */
using AnalyserPtr = std::shared_ptr<Analyser>; /**< Type definition for shared analyser pointer. */
class AnalyserEquation; /**< Forward declaration of AnalyserEquation class. */
using AnalyserEquationPtr = std::shared_ptr<AnalyserEquation>; /**< Type definition for shared analyser equation pointer. */
class AnalyserEquationAst; /**< Forward declaration of AnalyserEquationAst class. */
using AnalyserEquationAstPtr = std::shared_ptr<AnalyserEquationAst>; /**< Type definition for shared analyser equation AST pointer. */
class AnalyserModel; /**< Forward declaration of AnalyserModel class. */
using AnalyserModelPtr = std::shared_ptr<AnalyserModel>; /**< Type definition for shared analyser model pointer. */
class AnalyserVariable; /**< Forward declaration of AnalyserVariable class. */
using AnalyserVariablePtr = std::shared_ptr<AnalyserVariable>; /**< Type definition for shared analyser variable pointer. */
class Generator; /**< Forward declaration of Generator class. */
using GeneratorPtr = std::shared_ptr<Generator>; /**< Type definition for shared generator pointer. */
class GeneratorProfile; /**< Forward declaration of GeneratorProfile class. */
using GeneratorProfilePtr = std::shared_ptr<GeneratorProfile>; /**< Type definition for shared generator variable pointer. */
class Importer; /**< Forward declaration of Importer class. */
using ImporterPtr = std::shared_ptr<Importer>; /**< Type definition for shared importer pointer. */
class Issue; /**< Forward declaration of Issue class. */
using IssuePtr = std::shared_ptr<Issue>; /**< Type definition for shared issue pointer. */
class Logger; /**< Forward declaration of Parser class. */
using LoggerPtr = std::shared_ptr<Logger>; /**< Type definition for shared parser pointer. */
class Parser; /**< Forward declaration of Parser class. */
using ParserPtr = std::shared_ptr<Parser>; /**< Type definition for shared parser pointer. */
class Printer; /**< Forward declaration of Printer class. */
using PrinterPtr = std::shared_ptr<Printer>; /**< Type definition for shared printer pointer. */
class Validator; /**< Forward declaration of Validator class. */
using ValidatorPtr = std::shared_ptr<Validator>; /**< Type definition for shared validator pointer. */

// CellML entities.
class Component; /**< Forward declaration of Component class. */
using ComponentPtr = std::shared_ptr<Component>; /**< Type definition for shared component pointer. */
class ComponentEntity; /**< Forward declaration of ComponentEntity class. */
using ComponentEntityConstPtr = std::shared_ptr<const ComponentEntity>; /**< Type definition for shared component entity const pointer. */
using ComponentEntityPtr = std::shared_ptr<ComponentEntity>; /**< Type definition for shared component entity pointer. */
class Entity; /**< Forward declaration of Entity class. */
using EntityPtr = std::shared_ptr<Entity>; /**< Type definition for shared entity pointer. */
using EntityConstPtr = std::shared_ptr<const Entity>; /**< Type definition for shared entity const pointer. */
class ImportedEntity; /**< Forward declaration of ImportedEntity class. */
using ImportedEntityPtr = std::shared_ptr<ImportedEntity>; /**< Type definition for shared imported entity pointer. */
class ImportSource; /**< Forward declaration of ImportSource class. */
using ImportSourcePtr = std::shared_ptr<ImportSource>; /**< Type definition for shared import source pointer. */
class Model; /**< Forward declaration of Model class. */
using ModelPtr = std::shared_ptr<Model>; /**< Type definition for shared model pointer. */
class Reset; /**< Forward declaration of Reset class. */
using ResetPtr = std::shared_ptr<Reset>; /**< Type definition for shared reset pointer. */
class Units; /**< Forward declaration of Units class. */
using UnitsPtr = std::shared_ptr<Units>; /**< Type definition for shared units pointer. */
class Variable; /**< Forward declaration of Variable class. */
using VariablePtr = std::shared_ptr<Variable>; /**< Type definition for shared variable pointer. */

using AnyItem = std::pair<ItemType, std::any>; /**< Type definition for the AnyItem pair. */
using UnitItem = std::pair<UnitsPtr, size_t>; /**< Type definition for the UnitItem pair. */
using VariablePair = std::pair<VariablePtr, VariablePtr>; /**< Type definition for VariablePtr pair.*/

} // namespace libcellml
