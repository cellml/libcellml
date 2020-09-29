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
#include <vector>

#include "libcellml/exportdefinitions.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Annotator class.
 *
 * The Annotator class is for representing a CellML Annotator.
 */
class LIBCELLML_EXPORT Annotator: public Logger
{
public:
    ~Annotator() override; /**< Destructor */
    Annotator(const Annotator &rhs) = delete; /**< Copy constructor */
    Annotator(Annotator &&rhs) noexcept = delete; /**< Move constructor */
    Annotator &operator=(Annotator rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Annotator object.
     *
     * Factory method to create a @ref Annotator.  Create a
     * annotator with:
     *
     * @code
     *   AnnotatorPtr annotator = libcellml::Annotator::create();
     * @endcode
     *
     * @return A smart pointer to an @ref Annotator object.
     */
    static AnnotatorPtr create() noexcept;

    /**
     * @brief Set the model that this annotator will use.
     *
     * Set the model that this annotator will use.
     *
     * @param model A @ref ModelPtr model to use in this annotator.
     */
    void setModel(const ModelPtr &model);

    /**
     * @brief Get the model associated with this annotator.
     *
     * Get the model associated with this annotator.  A @c nullptr
     * is returned if there is no model associated with this annotator.
     *
     * @return A @ref ModelPtr to a model, or a @c nullptr.
     */
    ModelPtr model() const;

    /**
     * @brief Retrieves an item with the given id string.
     *
     * The item returned is a @c std::pair containing:
     *  - a @ref CellMLElement enum, and
     *  - a @c std::any item containing the item.
     *
     * Possible pairs returned returned are:
     *  - <CellMLElement::COMPONENT, @ref ComponentPtr> - Retrieve id with Component::id().
     *  - <CellMLElement::COMPONENT_REF, @ref ComponentPtr> - Retrieve id with Component::encapsulationId().
     *  - <CellMLElement::CONNECTION, @ref VariablePair> - Retrieve id with Variable::equivalenceConnectionId(const VariablePtr &,const VariablePtr &).
     *  - <CellMLElement::ENCAPSULATION, @ref ModelPtr> - Retrieve id with Model::encapsulationId().
     *  - <CellMLElement::IMPORT, @ref ImportSourcePtr> - Retrieve id with ImportSource::id().
     *  - <CellMLElement::MAP_VARIABLES, @ref VariablePair> - Retrieve id with Variable::equivalenceMappingId(const VariablePtr &, const VariablePtr &).
     *  - <CellMLElement::MODEL, @ref ModelPtr> - Retrieve id with Model::id().
     *  - <CellMLElement::RESET, @ref ResetPtr> - Retrieve id with Reset::id().
     *  - <CellMLElement::RESET_VALUE, @ref ResetPtr> - Retrieve id with Reset::resetValueId (const std::string &).
     *  - <CellMLElement::TEST_VALUE, @ref ResetPtr> - Retrieve id with Reset::testValueId (const std::string &).
     *  - <CellMLElement::UNDEFINED, @c nullptr>.
     *  - <CellMLElement::UNIT, @ref UnitItem> - Retrieve id with Units::unitId(size_t) const.
     *  - <CellMLElement::UNITS, @ref UnitsPtr> - Retrieve id with Units::id().
     *  - <CellMLElement::VARIABLE, @ref VariablePtr> - Retrieve id with Variable::id().
     *
     * @param id A @c std::string representing the @p id to retrieve.
     *
     * @return An @c AnyItem item (as described above).
     */
    AnyItem item(const std::string &id);

    /**
     * @brief Return the item at @p index with the @p id.
     *
     * From a list of items in the stored model with the given @p id string,
     * this function returns the item in the @p index position.
     * 
     * See item(const std::string &) for a full breakdown of the return value.
     *
     * @overload
     *
     * @sa item(const std::string &)
     *
     * @param id A @c std::string representing the @p id to retrieve.
     * @param index The index of the item to return from the list of items with @p id.
     *
     * @return An @c AnyItem item as described in item(const std::string &).
     */
    AnyItem item(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @ref ComponentPtr with the given @p id.
     *
     * If an item with the id is not found, has another type, or is not unique, the
     * @c nullptr is returned.
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
     *      - the item stored at the @p index is not a @c ComponentPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ComponentPtr.
     */
    ComponentPtr component(const std::string &id, size_t index);

    /**
     * @brief Retrieve the @c ModelPtr if its encapsulation has the given @p id.
     *
     *        If an item with the id is not found, has another type, or is not unique, the
     *        @c nullptr is returned.
     *
     * @param id String representing the id of the item to retrieve.
     *
     * @return A @c ComponentPtr.
     */
    ModelPtr encapsulation(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this function returns a @c ModelPtr in the @p index position, if it exists.
     *
     *  A @c nullptr will be returned if:
     *      - no item with the given @p id exists in the stored model;
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
     *      - the item stored at the @p index is not a @c ModelPtr; or
     *      - the annotator is not built; 
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ModelPtr.
     */
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     *  The annotator index must be built using Annotator::buildModelIndex(ModelPtr model)
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
     *      - the given @p index is beyond the range [0, \#duplicateCount(id));
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
     * stored in this annotator, excluding its MathML items. Existing ids will 
     * not be changed.
     * 
     * @return a boolean value indicating whether any ids have been changed.
     */
    bool assignAllIds();

    /**
     * @brief Assign a unique, automatic id string to every item in the given @p model, 
     * excluding its MathML items. Existing ids will not be changed.
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
     *  model which is already stored in this annotator. Existing ids will not be changed.
     * 
     *  The annotator index must be built using Annotator::buildModelIndex(ModelPtr model)
     *  before this function can be called successfully.
     * 
     * @param type Items of this @c CellMLElement will all be assigned a new id.
     * 
     * @return a boolean value indicating whether any ids have been changed.
     */
    bool assignIds(CellMLElement type);

    /**
     * Clear all id strings from all items in the stored model.
     */
    void clearAllIds();

    /**
     * @brief Clear all id strings from all items in the given @p model.
     * 
     *  The given @p model will replace the one which was previously stored 
     *  in this annotator.
     * 
     * @param model A @c ModelPtr for which all id strings will be cleared.  It will
     *              replace the stored model in this annotator.
     */
    void clearAllIds(ModelPtr &model);

    /**
     * @brief Test whether the given @p id exists uniquely within the stored model.
     *
     * Test whether the given @p id exists uniquely within the stored model.
     * 
     * @param id A @c std::string to test for uniqueness amongst the set of ids in the stored model.
     *
     * @return @c true if the @p id exists exactly once, @c false otherwise.
     */
    bool isUnique(const std::string &id);

    /**
     * @brief Return a @c std::vector of @c AnyItem items which have the given @p id.
     * 
     * The annotator requires a model to be set with setModel(ModelPtr)
     * before this function can be called successfully.
     * 
     * @param id A @c std::string used to identify the set of items to retrieve.
     * 
     * @return a @c std::vector of @ref AnyItem items.
     */
    std::vector<AnyItem> items(const std::string &id);

    /** 
     * @brief Return a @c std::vector of @c std::strings representing all id
     * strings in the stored model.
     * 
     * The annotator requires a model to be set with setModel(ModelPtr)
     * before this function can be called successfully.
     * 
     * @return a @c std::vector of @c std::strings.
     */
    std::vector<std::string> ids();

    /** 
     * @brief Return a @c std::multimap of @c std::strings representing all id
     * strings in the stored model, paired with their @c CellMLElement type.
     * 
     * The annotator requires a model to be set with setModel(ModelPtr)
     * before this function can be called successfully.
     * 
     * @return a @c std::multimap of @c std::strings, @c CellMLElement enums.
     */
    IdCellMLElementMap dictionary();

    /** 
     * @brief Return a @c std::vector of @c std::strings representing any duplicated id
     * string in the stored model.
     * 
     * The annotator requires a model to be set with setModel(ModelPtr)
     * before this function can be called successfully.
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
     *     submitted, the @p type must be @c CellMLElement::MODEL); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c CellMLElement enumeration.  This must be equal to @c CellMLElement::MODEL.
     * @param item A @c ModelPtr model to which the new id will be assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(const ModelPtr &model, CellMLElement type = CellMLElement::MODEL);

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
     *     submitted, the @p type must be @c CellMLElement::COMPONENT or
     *     @c CellMLElement::COMPONENT_REF); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c CellMLElement enumeration.  This must be equal to:
     *          - @c CellMLElement::COMPONENT; or
     *          - @c CellMLElement::COMPONENT_REF.
     * 
     * @param item A @c ComponentPtr item.  The new id will be assigned to either:
     *          - the component (COMPONENT) or
     *          - its encapsulation reference (COMPONENT_REF)
     *        depending on the @p type.
     *    
     * @return the new id string.
     */
    std::string assignId(const ComponentPtr &component, CellMLElement type = CellMLElement::COMPONENT);

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
     *     submitted, the @p type must be @c CellMLElement::IMPORT); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type An @c CellMLElement enum.  This must be @c CellMLElement::IMPORT.
     * @param item An @c ImportSourcePtr to which the new id will be assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(const ImportSourcePtr &importSource);

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
     *     submitted, the @p type must be either @c CellMLElement::RESET,
     *     @c CellMLElement::RESET_VALUE, or  @c CellMLElement::TEST_VALUE); or
     *   - the given @p item is @c nullptr.
     * 
     * @param reset A @ref ResetPtr.  The new id will be assigned to either:
     *          - the reset item itself (RESET);
     *          - its reset value (RESET_VALUE); or
     *          - its test value (TEST_VALUE)
     *        depending on the @p type.
     * @param type An @c CellMLElement enumeration.  This must be equal to:
     *          - @c CellMLElement::RESET;
     *          - @c CellMLElement::RESET_VALUE; or
     *          - @c CellMLElement::TEST_VALUE.
     *
     * @return the new id string.
     */
    std::string assignId(const ResetPtr &reset, CellMLElement type = CellMLElement::RESET);

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
     *     submitted, the @p type must be @c CellMLElement::UNITS); or
     *   - the given @p item is @c nullptr.
     * 
     * @param units A @c UnitsPtr item to which the new id is assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(const UnitsPtr &units);

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
     *     submitted, the @p type must be @c CellMLElement::UNIT); or
     *   - the given @p item is @c nullptr.
     * 
     * @param units A @c UnitItem item to which the new id is assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(const UnitItem &item);

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
     *     submitted, the @p type must be @c CellMLElement::VARIABLE); or
     *   - the given @p item is @c nullptr.
     * 
     * @param type A @c CellMLElement enumeration.  This must be equal to @c CellMLElement::VARIABLE.
     * @param units A @c VariablePtr item to which the new id is assigned.
     * 
     * @return the new id string.
     */
    std::string assignId(const VariablePtr &variable);

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
     * @param type A @c CellMLElement enumeration.  This must be equal to either:
     *             - @c CellMLElement::CONNECTION; or
     *             - @c CellMLElement::MAP_VARIABLES.
     * 
     * @param pair A @c VariablePair item containing two @c VariablePtrs which together define either:
     *             - a connection between parent components (CONNECTION); or
     *             - an equivalence between two variables (MAP_VARIABLES).
     * 
     * @return the new id string.
     */
    std::string assignId(const VariablePair &pair, CellMLElement type = CellMLElement::CONNECTION);

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
     *   - the @p type is neither @c CellMLElement::CONNECTION or @c CellMLElement::MAP_VARIABLES.
     * 
     * @param type An @c CellMLElement enumeration.  This must be equal to either:
     *             - @c CellMLElement::CONNECTION; or
     *             - @c CellMLElement::MAP_VARIABLE.
     * 
     * @param item1 A @c VariablePtr item related to @p item2 through a connection or equivalence.
     * @param item2 A @c VariablePtr item related to @p item1 through a connection or equivalence.
     * 
     * @return the new id string.
     */
    std::string assignId(const VariablePtr &variable1, const VariablePtr &variable2, CellMLElement type = CellMLElement::CONNECTION);

    /**
     * @overload
     * 
     * @brief Assign an automatically generated, unique id to the unit item at index @p index 
     *        within units @p units.  The given @p type must be @c CellMLElement::UNIT.
     * 
     *  This function will return the new id that has been assigned, or an empty string
     *  if the operation failed.  The id will not be assigned if:
     *   - no model has been stored and/or built in this annotator;
     *   - the given @p units is not a member of the stored model; 
     *   - the given @p index is beyond the valid index range for the @p units;
     *   - the given @p type is not @c CellMLElement::UNIT; or
     *   - the given @p units is @c nullptr.
     * 
     * @param type A @c CellMLElement enumeration.  This must be equal to @c CellMLElement::UNIT.
     * @param units A @c UnitsPtr containing the child unit item.
     * @param index The index at which the child unit exists within the parent @p units item.
     * 
     * @return the new id string.
     */
    std::string assignId(const UnitsPtr &units, size_t index);

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
     * @brief Get the number of items with the given @p id.
     *
     * @param id A @c std::string for the id to find.
     * 
     * @return the number of items with the given @p id.
     */
    size_t duplicateCount(const std::string &id);

    /**
     * @brief Test whether the annotator is up-to-date with the state of the stored model.
     *
     * @return @c true if the annotator has been built with respect to the current model state, or @c false otherwise.
     */
    bool hasModel() const;

private:
    Annotator(); /**< Constructor */

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
