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
#include <string>
#include <vector>

#include "libcellml/exportdefinitions.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

namespace libcellml {

using VariablePair = std::pair<VariablePtr, VariablePtr>;
using UnitItem = std::pair<UnitsPtr, size_t>;
using AnyItem = std::pair<std::uint64_t, std::any>;
using ItemList = std::multimap<std::string, AnyItem>;
/**
 * @brief The Annotator class.
 *
 * The Annotator class is for representing a CellML Annotator.
 */
class LIBCELLML_EXPORT Annotator: public Logger
{
public:
    enum Type
    {
        COMPONENT,
        COMPONENT_REF,
        CONNECTION,
        ENCAPSULATION,
        IMPORT,
        ISSUE,
        MAP_VARIABLES,
        MODEL,
        RESET,
        RESET_VALUE,
        TEST_VALUE,
        UNIT,
        UNITS,
        VARIABLE,
    };

    ~Annotator() override; /**< Destructor */
    Annotator(const Annotator &rhs) = delete; /**< Copy constructor */
    Annotator(Annotator &&rhs) noexcept = delete; /**< Move constructor */
    Annotator &operator=(Annotator rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Annotator object.
     *
     * Factory method to create a @c Annotator.  Create a
     * annotator with::
     *
     *   AnnotatorPtr annotator = libcellml::Annotator::create();
     *
     * @return A smart pointer to an @c Annotator object.
     */
    static AnnotatorPtr create() noexcept;

    /**
     * @brief Builds the internal map of ids to items for the model provided.
     *
     * @param model A @c ModelPtr model to build map for.
     */
    void build(const ModelPtr &model);

    /**
     * @brief Retrieves an item with the given id string, in the model
     * for which the internal map was built using @sa build().
     *
     * The item returned is a @c std::pair containing:
     *  - an @c Annotator::Type enum, and
     *  - an @c std::any item containing the item.
     *
     * Possible string labels and their corresponding items returned are:
     *  - Annotator::Type::COMPONENT
     *          ComponentPtr to item with this id.
     *  - Annotator::Type::COMPONENT_REF
     *          ComponentPtr to component which has component->componentRefId() == id.
     *  - Annotator::Type::CONNECTION
     *          VariablePair including two VariablePtr items which can be used to retrieve the
     *          connection.  Note that multiple pairs of variables could be used to identify
     *          a single connection.
     *   Annotator::Type::ENCAPSULATION
     *          An empty string.
     *   Annotator::Type::IMPORT
     *          An ImportSourcePtr item with this id.
     *   Annotator::Type::ISSUE
     *          An IssuePtr containing an error message.
     *   Annotator::Type::MAP_VARIABLES
     *          A VariablePair including two VariablePtr items which can be used to retrieve the
     *          equivalence.
     *   Annotator::Type::MODEL
     *          A ModelPtr with this id.
     *   Annotator::Type::RESET
     *          A ResetPtr with this id.
     *   Annotator::Type::RESET_VALUE
     *          A ResetPtr which is the parent of the reset_value item found with this id.
     *          Retrieve the reset_value MathML string using reset->resetValue().
     *   Annotator::Type::TEST_VALUE
     *          A ResetPtr which is the parent of the test_value item found with this id.
     *          Retrieve the test_value MathML string using reset->testValue().
     *   Annotator::Type::UNIT
     *          A UnitItem pair containing:
     *              .first: A UnitsPtr to the parent of the unit item with this id, and
     *              .second: A size_t with the index to the Unit item.
     *          Retrieve the unit description using Units::unitAttributes() function with
     *   Annotator::Type::UNITS
     *          A UnitsPtr item with this id.
     *   Annotator::Type::VARIABLE
     *          A VariablePtr item with this id.
          *
     * @param id A @c std::string representing the @p id to retrieve.
     *
     * @return An @c AnyItem item as described above.
     */
    AnyItem item(const std::string &id);

    /**
     * @brief Retrieve a @c ComponentPtr with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ComponentPtr.
     */
    ComponentPtr component(const std::string &id);

    /**
     * @brief Retrieve a @c VariablePtr with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c VariablePtr.
     */
    VariablePtr variable(const std::string &id);

    /**
     * @brief Retrieve a @c ResetPtr with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr reset(const std::string &id);

    /**
     * @brief Retrieve a @c ModelPtr with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ModelPtr.
     */
    ModelPtr model(const std::string &id);

    /**
     * @brief Retrieve a @c ImportSourcePtr with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ImportSourcePtr.
     */
    ImportSourcePtr importSource(const std::string &id);

    /**
     * @brief Retrieve a @c UnitsPtr with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c UnitsPtr.
     */
    UnitsPtr units(const std::string &id);

    /**
     * @brief Retrieve a @c VariablePair item containing the two @c Variables
     *        whose connection has the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c VariablePair.
     */
    VariablePair connection(const std::string &id);

    /**
     * @brief Retrieve a @c VariablePair item containing the two @c Variables
     *        whose mapping has the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c VariablePair.
     */
    VariablePair mapVariables(const std::string &id);

    /**
     * @brief Retrieve a @c UnitItem with the given @p id.
     *
     * The @c UnitItem is a pair containg a @c UnitsPtr to the parent Units item, and
     * the index to the Unit item with this id.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c UnitItem.
     */
    UnitItem unit(const std::string &id);

    /**
     * @brief Retrieve a @c ComponentPtr to the component_ref with the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ComponentPtr.
     */
    ComponentPtr componentRef(const std::string &id);

    /**
     * @brief Retrieve a @c ResetPtr whose test_value has the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr testValue(const std::string &id);

    /**
     * @brief Retrieve a @c ResetPtr whose reset_value has the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr resetValue(const std::string &id);

    // KRM docstrings
    bool assignAutomaticIds();
    bool assignAutomaticIds(Annotator::Type type);
    bool repairNonUniqueIds();
    bool assignId(const AnyItem &item);
    bool assignId(Annotator::Type type, const ModelPtr &item);
    bool assignId(Annotator::Type type, const ComponentPtr &item);
    bool assignId(Annotator::Type type, const ImportSourcePtr &item);
    bool assignId(Annotator::Type type, const ResetPtr &item);
    bool assignId(Annotator::Type type, const UnitsPtr &item);
    bool assignId(Annotator::Type type, const UnitItem &item);
    bool assignId(Annotator::Type type, const VariablePtr &item);
    bool assignId(Annotator::Type type, const VariablePair &item);
    bool assignId(Annotator::Type type, const VariablePtr &item1, const VariablePtr &item2);
    bool assignId(Annotator::Type type, const UnitsPtr &units, size_t index);

    bool assignComponentId(const ComponentPtr &component);
    bool assignComponentRefId(const ComponentPtr &component);
    bool assignConnectionId(const VariablePair &variablePair);
    bool assignEncapsulationId(const ModelPtr &model);
    bool assignImportSourceId(const ImportSourcePtr &importSource);
    bool assignMapVariablesId(const VariablePair &variablePair);
    bool assignModelId(const ModelPtr &model);
    bool assignResetId(const ResetPtr &reset);
    bool assignResetValueId(const ResetPtr &reset);
    bool assignTestValueId(const ResetPtr &reset);
    bool assignUnitId(const UnitItem &unitItem);
    bool assignUnitsId(const UnitsPtr &units);
    bool assignVariableId(const VariablePtr &variable);

private:
    Annotator(); /**< Constructor */

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
