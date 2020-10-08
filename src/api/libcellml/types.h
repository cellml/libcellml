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
#include <memory>
#include <utility>

#include "libcellml/enums.h"
#include "libcellml/exportdefinitions.h"

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
class Annotator; /**< Forward declaration of Annotator class. */
using AnnotatorPtr = std::shared_ptr<Annotator>; /**< Type definition for @c std::shared Annotator pointer. */
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
class Unit; /**< Forward declaration of Unit class. */
using UnitPtr = std::shared_ptr<Unit>; /**< Type definition for shared unit pointer. */
class Units; /**< Forward declaration of Units class. */
using UnitsPtr = std::shared_ptr<Units>; /**< Type definition for shared units pointer. */
class Variable; /**< Forward declaration of Variable class. */
using VariablePtr = std::shared_ptr<Variable>; /**< Type definition for shared variable pointer. */

using AnyItem = std::pair<CellmlElementType, std::any>;

/**
 * @brief The Unit class
 *
 * The Unit class can be used to refer to a unit in a @ref Units.
 */
class LIBCELLML_EXPORT Unit
{
public:
    ~Unit(); /**< Destructor. */
    Unit() = delete; /**< Constructor. */
    Unit(const Unit &rhs) = delete; /**< Copy constructor. */
    Unit(Unit &&rhs) noexcept = delete; /**< Move constructor. */
    Unit &operator=(Unit rhs) = delete; /**< Assignment operator. */

    /**
     * @brief Create a unit reference object.
     *
     * Factory method to create a @ref UnitPtr.  Create a unit with @ref Units
     * and index with::
     *
     *   auto unit = libcellml::UnitPtr::create(units, index);
     *
     * @return A smart pointer to a @ref UnitPtr object.
     */
    static UnitPtr create(const UnitsPtr &units, size_t index) noexcept;

    /**
     * @brief Get the unit.
     *
     * Get the unit in the @ref Units.
     *
     * @return The unit.
     */
    UnitsPtr units() const;

    /**
     * @brief Get the index.
     *
     * Get the index for the unit in the @ref Units.
     *
     * @return The index.
     */
    size_t index() const;

    /**
     * @brief Test to see if this unit reference is valid.
     *
     * Test to see if the @ref Units used in this unit reference exists and
     * has a unit at the given index.
     *
     * @return @c true if this unit reference is valid, @c false otherwise.
     */
    bool isValid() const;

private:
    explicit Unit(const UnitsPtr &units, size_t index); /**< Constructor with two variables as parameters. */

    struct UnitImpl; /**< Forward declaration for pImpl idiom. */
    UnitImpl *mPimpl; /**< Private member to implementation pointer. */
};

class VariablePair;
using VariablePairPtr = std::shared_ptr<VariablePair>;

/**
 * @brief The VariablePair class
 *
 * The VariablePair class can be used to describe connections
 * or map variables in CellML.
 */
class LIBCELLML_EXPORT VariablePair
{
public:
    ~VariablePair(); /**< Destructor. */
    VariablePair() = delete; /**< Constructor. */
    VariablePair(const VariablePair &rhs) = delete; /**< Copy constructor. */
    VariablePair(VariablePair &&rhs) noexcept = delete; /**< Move constructor. */
    VariablePair &operator=(VariablePair rhs) = delete; /**< Assignment operator. */

    /**
     * @brief Create a variable pair object.
     *
     * Factory method to create a @ref VariablePairPtr.  Create a
     * variable pair with variable 1 and variable 2 with::
     *
     *   VariablePairPtr variablePair = libcellml::VariablePairPtr::create(variable1, variable2);
     *
     * @return A smart pointer to a @ref VariablePairPtr object.
     */
    static VariablePairPtr create(const VariablePtr &variable1, const VariablePtr &variable2) noexcept;

    /**
     * @brief Get the first variable in the pair.
     *
     * Get the first variable in the pair.
     *
     * @return The first variable in the pair.
     */
    VariablePtr variable1() const;

    /**
     * @brief Get the second variable in the pair.
     *
     * Get the second variable in the pair.
     *
     * @return The second variable in the pair.
     */
    VariablePtr variable2() const;

    /**
     * @brief Test to see if this variable pair is valid.
     *
     * Test to see if both the variables in this variable pair are
     * not @c nullptr.
     *
     * @return @c true if this variable pair is valid, @c false otherwise.
     */
    bool isValid() const;

private:
    explicit VariablePair(const VariablePtr &variable1, const VariablePtr &variable2); /**< Constructor with two variables as parameters. */

    struct VariablePairImpl; /**< Forward declaration for pImpl idiom. */
    VariablePairImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
