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
     * @overload
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
     *          A ModelPtr of the model whose encapsulation id is the given id.
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
     * @overload
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns the item in the @p index position.
     * 
     * Note that the @sa Annotator::build function must be called before this can work successfully. 
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
     *          A ModelPtr of the model whose encapsulation id is the given id.
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
     * @param index 
     *
     * @return An @c AnyItem item as described above.
     */
    AnyItem item(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ComponentPtr with the given @p id at @p index.
     *
     *        If an item with the id is not found, has another type, or is not unique, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ComponentPtr.
     */

    ComponentPtr component(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ComponentPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ComponentPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ComponentPtr.
     */
    ComponentPtr component(const std::string &id, size_t index);

    // KRM
    ModelPtr encapsulation(const std::string &id);
    ModelPtr encapsulation(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c VariablePtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c VariablePtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c VariablePtr.
     */
    VariablePtr variable(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ResetPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ResetPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr reset(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ModelPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ModelPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ModelPtr.
     */
    ModelPtr model(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ImportSourcePtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ImportSourcePtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return An @c ImportSourcePtr.
     */
    ImportSourcePtr importSource(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c UnitsPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c UnitsPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c UnitsPtr.
     */
    UnitsPtr units(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c VariablePair in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c VariablePair; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c VariablePair.
     */
    VariablePair connection(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c VariablePair in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c VariablePair; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c VariablePair.
     */
    VariablePair mapVariables(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c UnitItem in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c UnitItem; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c UnitItem.
     */
    UnitItem unit(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ComponentPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ComponentPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ComponentPtr.
     */
    ComponentPtr componentRef(const std::string &id, size_t index);

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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ResetPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ResetPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr testValue(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ResetPtr whose reset_value has the given @p id.
     *
     *  If an item with the id is not found, or has another type, the
     *  @c nullptr is returned.
     * 
     *  The annotator index must be built using Annotator::build(ModelPtr model)
     *  before this function can be called successfully.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr resetValue(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ResetPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#countIds(id));
     *      - the item stored at the @p index is not a @c ResetPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ResetPtr.
     */
    ResetPtr resetValue(const std::string &id, size_t index);

    /**
     * @brief Assign an id string to every item in the model which is already 
     * stored in this annotator, excluding its MathML items.
     * 
     * @return a boolean value indicating whether any ids have been changed.
     */
    bool assignAllIds();

    /**
     * @brief Assign a unique, automatic id string to every item in the given @p model, 
     * excluding its MathML items. 
     * 
     * The given @p model replaces any previously stored in this annotator.
     * 
     * @param model The @c ModelPtr to which id strings will be assigned.
     * 
     * @return a boolean value indicating whether any ids have been changed.
     */
    bool assignAllIds(ModelPtr &model);

    /**
     * @brief Assign an id string to every item of the given @p type in the
     *  model which is already stored in this annotator.
     * 
     *  The annotator index must be built using Annotator::build(ModelPtr model)
     *  before this function can be called successfully.
     * 
     * @param type Items of this @c Annotator::Type will all be assigned a new id.
     * 
     * @return a boolean value indicating whether any ids have been changed.
     */
    bool assignIds(Annotator::Type type);

    /**
     * @brief Clear all id strings from all items in the stored model.
     */
    void clearAllIds();

    /**
     * @brief Clear all id strings from all items in the given @p model.
     * 
     *  The given @p model also replaces the one which was previously stored 
     *  in this annotator.
     * 
     * @param model A @c ModelPtr for which all id strings will be cleared.  It will
     *              replace the stored model in this annotator.
     */
    void clearAllIds(ModelPtr &model);

    /**
     * @brief Test whether the given @p id exists uniquely within the stored model.
     * 
     * @param id A @c std::string to test for uniqueness amongst the set of ids in the stored model.
     * @param raiseError A @c bool determining whether, if duplicates are found, to create an @c Issue item
     *                   in this annotator.
     *
     * @return @c true if the @p id exists exactly once, @c false otherwise.
     */
    bool isUnique(const std::string &id, bool raiseError);

    /**
     * @brief Return a @c std::vector of @c AnyItem items which have the given @p id.
     * 
     *  The annotator index must be built using Annotator::build(ModelPtr model)
     *  before this function can be called successfully.
     * 
     * @param id A @c std::string used to identify the set of items to retrieve.
     * 
     * @return a @c std::vector of @c AnyItem items.
     */
    std::vector<AnyItem> items(const std::string &id);

    /** 
     * @brief Return a @c std::vector of @c std::strings representing any duplicated id
     *  string in the stored model.
     * 
     *  The annotator index must be built using Annotator::build(ModelPtr model)
     *  before this function can be called successfully.
     * 
     * @return a @c std::vector of @c std::strings.
     */
    std::vector<std::string> duplicateIds();

    /**
     * @brief Assign an automatically generated, unique id to the given @p item.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; or
     *   - the given @p item is @c nullptr.
     * 
     * @param item An @c AnyItem to which a new id will be assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(const AnyItem &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if a @c ModelPtr is 
     *     submitted, the @p type must be @c Annotator::Type::MODEL); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c Annotator::Type enumeration.  This must be equal to @c Annotator::Type::MODEL.
     * @param item A @c ModelPtr model to which the new id will be assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const ModelPtr &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if a @c ComponentPtr is 
     *     submitted, the @p type must be @c Annotator::Type::COMPONENT or 
     *     @c Annotator::Type::COMPONENT_REF); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c Annotator::Type enumeration.  This must be equal to:
     *          - @c Annotator::Type::COMPONENT; or
     *          - @c Annotator::Type::COMPONENT_REF.
     * 
     * @param item A @c ComponentPtr item.  The new id will be assigned to either:
     *          - the component (COMPONENT) or
     *          - its encapsulation reference (COMPONENT_REF)
     *        depending on the @p type.
     *    
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const ComponentPtr &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if an @c ImportSourcePtr is 
     *     submitted, the @p type must be @c Annotator::Type::IMPORT); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c Annotator::Type enum.  This must be @c Annotator::Type::IMPORT.
     * @param item An @c ImportSourcePtr to which the new id will be assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const ImportSourcePtr &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if a @c ResetPtr is 
     *     submitted, the @p type must be either @c Annotator::Type::RESET,  
     *     @c Annotator::Type::RESET_VALUE, or  @c Annotator::Type::TEST_VALUE); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c Annotator::Type enumeration.  This must be equal to:
     *          - @c Annotator::Type::RESET; 
     *          - @c Annotator::Type::RESET_VALUE; or
     *          - @c Annotator::TYPE::TEST_VALUE.
     * 
     * @param item A @c ResetPtr item.  The new id will be assigned to either:
     *          - the reset item itself (RESET);
     *          - its reset value (RESET_VALUE); or
     *          - its test value (TEST_VALUE)
     *        depending on the @p type.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const ResetPtr &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if an @c UnitsPtr is 
     *     submitted, the @p type must be @c Annotator::Type::UNITS); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type A @c Annotator::Type enumeration.  This must be equal to @c Annotator::Type::UNITS.
     * @param units A @c UnitsPtr item to which the new id is assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const UnitsPtr &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if an @c UnitItem is 
     *     submitted, the @p type must be @c Annotator::Type::UNIT); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type A @c Annotator::Type enumeration.  This must be equal to @c Annotator::Type::UNIT.
     * @param units A @c UnitItem item to which the new id is assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const UnitItem &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p item 
     * which is of type @p type.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p item is not a member of the stored model; 
     *   - the given @p item is not of the given @p type (ie: if an @c VariablePtr is 
     *     submitted, the @p type must be @c Annotator::Type::VARIABLE); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type A @c Annotator::Type enumeration.  This must be equal to @c Annotator::Type::VARIABLE.
     * @param units A @c VariablePtr item to which the new id is assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const VariablePtr &item);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the given @p pair.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - either @c VariablePtr in the @p pair is not a member of the stored model; 
     *   - either @c VariablePtr in the @p pair is @c nullptr; or
     *   - no item of the given @p type exists in the stored model.
     * 
     * @param type A @c Annotator::Type enumeration.  This must be equal to either:
     *             - @c Annotator::Type::CONNECTION; or
     *             - @c Annotator::Type::MAP_VARIABLES.
     * 
     * @param pair A @c VariablePair item containing two @c VariablePtrs which together define either:
     *             - a connection between parent components (CONNECTION); or
     *             - an equivalence between two variables (MAP_VARIABLES).
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const VariablePair &pair);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the item of type @p type
     *        which exists between @p item1 and @p item2.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - @p item1 and/or @p item2 is not a member of the stored model; 
     *   - @p item1 and/or @p item2 is @c nullptr;
     *   - a connection or equivalence (determined by @p type) does not exist in the stored model;
     *   - the @p type is neither @c Annotator::Type::CONNECTION or @c Annotator::Type::MAP_VARIABLES.
     * 
     * @param type An @c Annotator::Type enumeration.  This must be equal to either:
     *             - @c Annotator::Type::CONNECTION; or
     *             - @c Annotator::Type::MAP_VARIABLE.
     * 
     * @param item1 A @c VariablePtr item related to @p item2 through a connection or equivalence.
     * @param item2 A @c VariablePtr item related to @p item1 through a connection or equivalence.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const VariablePtr &item1, const VariablePtr &item2);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the unit item at index @p index 
     *        within units @p units.  The given @p type must be @c Annotator::Type::UNIT.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p units is not a member of the stored model; 
     *   - the given @p index is beyond the valid index range for the @p units;
     *   - the given @p type is not @c Annotator::Type::UNIT; or
     *   - the given @p units is @c nullptr.
     * 
     * @param type A @c Annotator::Type enumeration.  This must be equal to @c Annotator::Type::UNIT.
     * @param units A @c UnitsPtr containing the child unit item.
     * @param index The index at which the child unit exists within the parent @p units item.
     * 
     * @return the new id string.
     */
    std::string assignId(Annotator::Type type, const UnitsPtr &units, size_t index);

    /**
     * @brief Assign an automatically generated, unique id to the given @p component.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p component is not a member of the stored model; or
     *   - the given @p component is @c nullptr.
     * 
     * @param component The @c ComponentPtr which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignComponentId(const ComponentPtr &component);

    /**
     * @brief Assign an automatically generated, unique id to the encapsulation reference
     *        attached to the given @p component.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p component is not a member of the stored model; or
     *   - the given @p component is @c nullptr.
     * 
     * @param component The @c ComponentPtr whose encapsulation id will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignComponentRefId(const ComponentPtr &component);

    /**
     * @brief Assign an automatically generated, unique id to the connection 
     *        formed between the variables in the given @c variablePair.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the variables in the given @p variablePair are not members of the stored model; or
     *   - either of the variables is @c nullptr; or
     *   - no connection exists between the parent components of the variables.
     * 
     * @param variablePair A @c VariablePair containing two @c VariablePtrs which define the connection 
     *                     which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignConnectionId(const VariablePair &variablePair);

    /**
     * @brief Assign an automatically generated, unique id to the encapsulation 
     *        of the given @c model.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p model is not the stored model; or
     *   - the given @p model of the variables is @c nullptr.
     * 
     * @param model A @c ModelPtr whose encapsulation will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignEncapsulationId(const ModelPtr &model);

    /**
     * @brief Assign an automatically generated, unique id to the given @p importSource.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p importSource is not a member of the stored model; or
     *   - the given @p importSource is @c nullptr.
     * 
     * @param importSource An @c ImportSourcePtr which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignImportSourceId(const ImportSourcePtr &importSource);

    /**
     * @brief Assign an automatically generated, unique id to the variable mapping 
     *        formed between the variables in the given @c variablePair.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the variables in the given @p variablePair are not members of the stored model; or
     *   - either of the variables is @c nullptr; or
     *   - no variable mapping exists between the variables.
     * 
     * @param variablePair A @c VariablePair containing two @c VariablePtrs which define the equivalence 
     *                     which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignMapVariablesId(const VariablePair &variablePair);

    /**
     * @brief Assign an automatically generated, unique id to the given @p model.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p model is not the stored model; or
     *   - the given @p model is @c nullptr.
     * 
     * @param model The @c ModelPtr which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignModelId(const ModelPtr &model);

    /**
     * @brief Assign an automatically generated, unique id to the given @p reset.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p reset is not a member of the stored model; or
     *   - the given @p reset is @c nullptr.
     * 
     * @param reset The @c ResetPtr which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignResetId(const ResetPtr &reset);

    /**
     * @brief Assign an automatically generated, unique id to the reset value inside the given @p reset.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p reset is not a member of the stored model; or
     *   - the given @p reset is @c nullptr.
     * 
     * @param reset The @c ResetPtr whose reset value will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignResetValueId(const ResetPtr &reset);

    /**
     * @brief Assign an automatically generated, unique id to the test value inside the given @p reset.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p reset is not a member of the stored model; or
     *   - the given @p reset is @c nullptr.
     * 
     * @param reset The @c ResetPtr whose test value will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignTestValueId(const ResetPtr &reset);

    /**
     * @brief Assign an automatically generated, unique id to the given @p unitItem.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the units parent of the @p unitItem is not a member of the stored model; or
     *   - the given @p unitItem cannot be constructed (its parent units is @c nullptr, 
     *     or its index is out of the parent's range).
     * 
     * @param unitItem The @c UnitItem which will be assigned the new id. 
     * 
     * @return the new id string.
     */
    std::string assignUnitId(const UnitItem &unitItem);

    /**
     * @brief Assign an automatically generated, unique id to the given @p units.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p units is not a member of the stored model; or
     *   - the given @p units is @c nullptr.
     * 
     * @param units The @c UnitsPtr which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignUnitsId(const UnitsPtr &units);

    /**
     * @brief Assign an automatically generated, unique id to the given @p variable.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p variable is not a member of the stored model; or
     *   - the given @p variable is @c nullptr.
     * 
     * @param variable The @c VariablePtr which will be assigned the new id.
     * 
     * @return the new id string.
     */
    std::string assignVariableId(const VariablePtr &variable);

    /**
     * @overload
     * 
     * @brief Return a string representing the given @p type.
     *  
     *  The string returned is a lower-case equivalent of the @c Annotator::Type
     *  enumeration; for example, @c Annotator::Type::COMPONENT_REF becomes "component_ref".
     *
     * @return a string representing the @p type.
     */

    std::string typeString(const Annotator::Type &type);

    /**
     * @overload
     * 
     * @brief Return a string representing the given @p type.
     *  
     *  The string returned is a lower-case equivalent of the @c Annotator::Type
     *  enumeration; for example, @c Annotator::Type::COMPONENT_REF becomes "component_ref".
     *
     * @return a string representing the @p type.
     */
    std::string typeString(const std::uint64_t &type);

    // KRM
    size_t countIds(const std::string &id);

private:
    Annotator(); /**< Constructor */

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
