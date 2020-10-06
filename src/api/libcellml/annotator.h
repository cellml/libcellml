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
     * Factory method to create a @ref Annotator.  Create an
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
     * this method returns the item in the @p index position.
     *
     * See item(const std::string &) for a full breakdown of the @ref AnyItem return value.
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
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c ComponentPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Component at that location.
     *
     * A @c nullptr will be returned if:
     *  - no item with the given @p id exists in the stored model;
     *  - the given @p index is beyond the range [0, \#duplicateCount(id));
     *  - the item stored at the @p index is not a @c ComponentPtr; or
     *  - the annotator does not have a model attached.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ComponentPtr on success otherwise @c nullptr.
     */
    ComponentPtr component(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @ref ComponentPtr with the given @p id.
     *
     * Retrieve a @ref Component that has the @p id.
     *
     * A @c nullptr will be returned if:
     *  - the annotator does not have a model attached;
     *  - the @p id is not found;
     *  - the item with @p id is not a component; or
     *  - the @p id is not unique.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @ref ComponentPtr on success otherwise @c nullptr.
     */
    ComponentPtr component(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref ComponentPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Component at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ComponentPtr on success otherwise @c nullptr.
     */
    ComponentPtr componentRef(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @ref ComponentPtr to the component_ref with the given @p id.
     *
     * Returns a @ref Component that has component_ref id @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c ComponentPtr on success otherwise @c nullptr.
     */
    ComponentPtr componentRef(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref ModelPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Model at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ModelPtr on success otherwise @c nullptr.
     */
    ModelPtr encapsulation(const std::string &id, size_t index);

    /**
     * @brief Retrieve the @ref ModelPtr if its encapsulation has the given @p id.
     *
     * Returns a @ref ModelPtr for the attached model if its encapsulation id is @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @ref ModelPtr on success otherwise @c nullptr.
     */
    ModelPtr encapsulation(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c VariablePtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Variable at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c VariablePtr on success otherwise @c nullptr.
     */
    VariablePtr variable(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c VariablePtr with the given @p id.
     *
     * Returns a @ref Variable with the given @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @ref VariablePtr on success otherwise @c nullptr.
     */
    VariablePtr variable(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref ResetPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Reset at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ResetPtr on success otherwise @c nullptr.
     */
    ResetPtr reset(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ResetPtr with the given @p id.
     *
     * Returns a @ref Reset with the given @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr on success otherwise @c nullptr.
     */
    ResetPtr reset(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c ModelPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Model at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ModelPtr on success otherwise @c nullptr.
     */
    ModelPtr model(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ModelPtr with the given @p id.
     *
     * Returns a @ref Model with the given @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c ModelPtr on success otherwise @c nullptr.
     */
    ModelPtr model(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c ImportSourcePtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref ImportSource at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return An @c ImportSourcePtr on success otherwise @c nullptr.
     */
    ImportSourcePtr importSource(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ImportSourcePtr with the given @p id.
     *
     * Returns a @ref ImportSource with the given @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c ImportSourcePtr on success otherwise @c nullptr.
     */
    ImportSourcePtr importSource(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c UnitsPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Units at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c UnitsPtr on success otherwise @c nullptr.
     */
    UnitsPtr units(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c UnitsPtr with the given @p id.
     *
     * Returns a @ref Units with the given @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c UnitsPtr on success otherwise @c nullptr.
     */
    UnitsPtr units(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c VariablePair in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref VariablePair at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c std::pair<nullptr, nullptr> is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c VariablePair on success otherwise @c std::pair<nullptr, nullptr>.
     */
    VariablePair connection(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c VariablePair item containing the two @c Variables
     *        whose connection has the given @p id.
     *
     * Returns a @ref VariablePair with the given @p id.
     *
     * @see component(const std::string &) for times when a @c std::pair<nullptr, nullptr> is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c VariablePair on success otherwise @c std::pair<nullptr, nullptr>.
     */
    VariablePair connection(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c VariablePair in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref VariablePair at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c std::pair<nullptr, nullptr> is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c VariablePair on success otherwise @c std::pair<nullptr, nullptr>.
     */
    VariablePair mapVariables(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @ref VariablePair item containing the two @ref Variables
     *        whose mapping has the given @p id.
     *
     * Returns a @ref VariablePair with the given @p id.
     *
     * @see component(const std::string &) for times when a @c std::pair<nullptr, nullptr> is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c VariablePair on success otherwise @c std::pair<nullptr, nullptr>.
     */
    VariablePair mapVariables(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c UnitItem in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref UnitItem at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c std::pair<nullptr, 0> is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c UnitItem on success otherwise @c std::pair<nullptr, 0>.
     */
    UnitItem unit(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c UnitItem with the given @p id.
     *
     * Returns a @ref UnitItem with the given @p id.
     *
     * @see component(const std::string &) for times when a @c nullptr is returned.
     *
     * @overload
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c UnitItem on success otherwise @c nullptr.
     */
    UnitItem unit(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c ResetPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Reset at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ResetPtr on success otherwise @c nullptr.
     */
    ResetPtr testValue(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ResetPtr whose test_value has the given @p id.
     *
     *        If an item with the id is not found, or has another type, the
     *        @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr on success otherwise @c nullptr.
     */
    ResetPtr testValue(const std::string &id);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @c ResetPtr in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Reset at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @c ResetPtr on success otherwise @c nullptr.
     */
    ResetPtr resetValue(const std::string &id, size_t index);

    /**
     * @brief Retrieve a @c ResetPtr whose reset_value has the given @p id.
     *
     *  If an item with the id is not found, or has another type, the
     *  @c nullptr is returned.
     *
     *  The annotator index must be built using Annotator::buildModelIndex(ModelPtr model)
     *  before this method can be called successfully.
     *
     * @param id A @c std::string representing the id of the item to retrieve.
     *
     * @return A @c ResetPtr on success otherwise @c nullptr.
     */
    ResetPtr resetValue(const std::string &id);

    /**
     * @brief Assign an id to every non-idied item in the model.
     *
     * Assing an id to every item in the model which do not already have an
     * id assigned.  Newly assigned ids will be unique within the model.
     * No ids will be added to MathML items.
     *
     * Existing ids will not be changed.
     *
     * Returns @c true if at least one id was assigned, @c false otherwise.
     *
     * @return @c true if any ids have been changed, @c false otherwise.
     */
    bool assignAllIds();

    /**
     * @brief Assign an id to every non-idied item in the given @p model.
     *
     * Assign a unique, automatic id to every item in the given @p model,
     * excluding its MathML items.
     *
     * Existing ids will not be changed.
     *
     * The given @p model replaces any previously stored in this annotator.
     *
     * @overload
     *
     * @param model The @c ModelPtr to which ids will be assigned.
     *
     * @return @c true if any ids have been changed, @c false otherwise.
     */
    bool assignAllIds(ModelPtr &model);

    /**
     * @brief Assign an id string to every item of the given @p type in the model.
     *
     * Assign an id string to every item of the given @p type in the
     * model. Returns @c true if at least one id was assigned, @c false otherwise.
     *
     * Existing ids will not be changed.
     *
     * @param type Items of this @c CellMLElement will all be assigned a new id.
     *
     * @return @c true if any ids have been changed, @c false otherwise.
     */
    bool assignIds(CellMLElement type);

    /**
     * @brief Clear all ids from the model.
     *
     * Clear all ids from all items in the stored model.
     * Does nothing if there is no model.
     */
    void clearAllIds();

    /**
     * @brief Clear all ids from all items in the given @p model.
     *
     * Clear all ids from the @p model. The given @p model will replace any model currently stored
     * in this annotator.
     *
     * @param model A @ref ModelPtr.
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
     * Return all items with the given @p id.
     *
     * The annotator requires a model to be set with setModel(const ModelPtr &)
     * before this method can be called successfully.
     *
     * @param id A @c std::string used to identify the items to retrieve.
     *
     * @return a @c std::vector of @ref AnyItem items.
     */
    std::vector<AnyItem> items(const std::string &id);

    /**
     * @brief Return a @c std::vector of @c std::strings representing all id
     * strings in the stored model.
     *
     * Return all ids in the stored model.
     *
     * The annotator requires a model to be set with setModel(const ModelPtr &)
     * before this method can be called successfully.
     *
     * @return a @c std::vector of @c std::strings.
     */
    std::vector<std::string> ids();

    /**
     * @brief Return a @c std::vector of @c std::strings representing any duplicated id
     * string in the stored model.
     *
     * Return all duplicated ids in the stored model.
     *
     * The annotator requires a model to be set with setModel(const ModelPtr &)
     * before this method can be called successfully.
     *
     * @return a @c std::vector of @c std::strings.
     */
    std::vector<std::string> duplicateIds();

    /**
     * @brief Assign an automatically generated, unique id to the given @p item.
     *
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * The id will not be assigned if:
     *   - no model has been stored in this annotator;
     *   - the given @p item is not a member of the stored model; or
     *   - the given @p item is @c nullptr.
     *
     * @param item An @c AnyItem to which a new id will be assigned.
     *
     * @return the new id.
     */
    std::string assignId(const AnyItem &item);

    /**
     * @brief Assign an automatically generated, unique id to the given @p model.
     *
     * Assign an automatically generated, unique id to the given @p model.
     * The default is to assign an id to a MODEL item.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellMLElement::MODEL and CellMLElement::ENCAPSULATION are relevant any other
     * CellMLElement type will not assign an id.  @see errorCount() if and/or error(size_t) for any
     * issues that may have been raised.
     *
     * An id will not be assigned if:
     *  - no model has been stored in this annotator;
     *  - the given @p item is not a member of the stored model;
     *  - the given @p item is not relevant to the given @p type; or
     *  - the given @p item is @c nullptr.
     *
     * @overload
     *
     * @param model A @c ModelPtr model to which the new id will be assigned.
     * @param type An @c CellMLElement enumeration.
     *
     * @return the new id string.
     */
    std::string assignId(const ModelPtr &model, CellMLElement type = CellMLElement::MODEL);

    /**
     * @brief Assign an automatically generated, unique id to the given @p component.
     *
     * Assign an automatically generated, unique id to the given @p component.
     * The default is to assign an id to a COMPONENT item.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellMLElement::COMPONENT and CellMLElement::COMPONENT_REF are relevant any other
     * CellMLElement type will not assign an id.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param component A @c ComponentPtr item.
     * @param type An @c CellMLElement enumeration.
     *
     * @return the new id string.
     */
    std::string assignId(const ComponentPtr &component, CellMLElement type = CellMLElement::COMPONENT);

    /**
     * @brief Assign an automatically generated, unique id to the given @p importSource.
     *
     * Assign an automatically generated, unique id to the given @p importSource.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param importSource An @c ImportSourcePtr to which the new id will be assigned.
     * @param type An @c CellMLElement enum.
     *
     * @return the new id string.
     */
    std::string assignId(const ImportSourcePtr &importSource);

    /**
     * @overload
     *
     * @brief Assign an automatically generated, unique id of the associated @p type to the given @p reset.
     *
     * Assign an automatically generated, unique id of the associated @p type to the given @p reset.
     * The default is to assign an id to a RESET item.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellMLElement::RESET, CellMLElement::RESET_VALUE, and CellMLElement::TEST_VALUE are relevant any other
     * CellMLElement type will not assign an id.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param reset A @ref ResetPtr.
     * @param type An @c CellMLElement enumeration.
     *
     * @return the new id string.
     */
    std::string assignId(const ResetPtr &reset, CellMLElement type = CellMLElement::RESET);

    /**
     * @brief Assign an automatically generated, unique id to the given @p units.
     *
     * Assign an automatically generated, unique id to the given @p units.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param units A @c UnitsPtr item to which the new id is assigned.
     *
     * @return the new id string.
     */
    std::string assignId(const UnitsPtr &units);

    /**
     * @brief Assign an automatically generated, unique id to the given @p unitItem.
     *
     * Assign an automatically generated, unique id to the given @p unitItem.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param unitItem A @c UnitItem item to which the new id is assigned.
     *
     * @return the new id string.
     */
    std::string assignId(const UnitItem &unitItem);

    /**
     * @brief Assign an automatically generated, unique id to the given @p variable.
     *
     * Assign an automatically generated, unique id to the given @p variable.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param variable A @c VariablePtr item to which the new id is assigned.
     *
     * @return the new id string.
     */
    std::string assignId(const VariablePtr &variable);

    /**
     * @brief Assign an automatically generated, unique id to the associated @p type for the given @p pair.
     *
     * Assign an automatically generated, unique id to the associated @p type for the given @p pair.
     * The default is to assign an id to a MAP_VARIABLES item.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellMLElement::MAP_VARIABLES, and CellMLElement::CONNECTION are relevant any other
     * CellMLElement type will not assign an id.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param pair A @c VariablePair item.
     * @param type A @c CellMLElement enumeration.
     *
     * @return the new id string.
     */
    std::string assignId(const VariablePair &pair, CellMLElement type = CellMLElement::MAP_VARIABLES);

    /**
     * @overload
     *
     * @brief Assign an automatically generated, unique id to the item of type @p type
     *        which exists between @p item1 and @p item2.
     *
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     * The default is to assign an id to a MAP_VARIABLES item.
     *
     * Only CellMLElement::MAP_VARIABLES, and CellMLElement::CONNECTION are relevant any other
     * CellMLElement type will not assign an id.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param variable1 A @c VariablePtr item defining to the first item in a connection or equivalence.
     * @param variable2 A @c VariablePtr item defining to the second item in a connection or equivalence.
     * @param type A @c CellMLElement enumeration.
     *
     * @return the new id string.
     */
    std::string assignId(const VariablePtr &variable1, const VariablePtr &variable2, CellMLElement type = CellMLElement::MAP_VARIABLES);

    /**
     * @brief Assign an automatically generated, unique id to the unit item at index @p index
     *        within units @p units.
     *
     * Assign an automatically generated, unique id to the unit item at index @p index
     * within units @p units.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param units A @c UnitsPtr containing the child unit item.
     * @param index The index at which the child unit exists within the parent @p units item.
     *
     * @return the new id string.
     */
    std::string assignId(const UnitsPtr &units, size_t index);

    /**
     * @brief Assign an automatically generated, unique id to the given @p component.
     *
     * Assign an automatically generated, unique id to the given @p component.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
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
     * Assign an automatically generated, unique id to the encapsulation reference
     * attached to the given @p component.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
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
     * Assign an automatically generated, unique id to the connection
     * formed between the variables in the given @c variablePair.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
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
     * Assign an automatically generated, unique id to the encapsulation
     * of the given @c model.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param model A @c ModelPtr whose encapsulation will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignEncapsulationId(const ModelPtr &model);

    /**
     * @brief Assign an automatically generated, unique id to the given @p importSource.
     *
     * Assign an automatically generated, unique id to the given @p importSource.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
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
     * Assign an automatically generated, unique id to the variable mapping
     * formed between the variables in the given @c variablePair.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
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
     * Assign an automatically generated, unique id to the given @p model.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param model The @c ModelPtr which will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignModelId(const ModelPtr &model);

    /**
     * @brief Assign an automatically generated, unique id to the given @p reset.
     *
     * Assign an automatically generated, unique id to the given @p reset.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param reset The @c ResetPtr which will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignResetId(const ResetPtr &reset);

    /**
     * @brief Assign an automatically generated, unique id to the reset value inside the given @p reset.
     *
     * Assign an automatically generated, unique id to the reset value inside the given @p reset.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param reset The @c ResetPtr whose reset value will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignResetValueId(const ResetPtr &reset);

    /**
     * @brief Assign an automatically generated, unique id to the test value inside the given @p reset.
     *
     * Assign an automatically generated, unique id to the test value inside the given @p reset.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param reset The @c ResetPtr whose test value will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignTestValueId(const ResetPtr &reset);

    /**
     * @brief Assign an automatically generated, unique id to the given @p unitItem.
     *
     * Assign an automatically generated, unique id to the given @p unitItem.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param unitItem The @c UnitItem which will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignUnitId(const UnitItem &unitItem);

    /**
     * @brief Assign an automatically generated, unique id to the given @p units.
     *
     * Assign an automatically generated, unique id to the given @p units.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param units The @c UnitsPtr which will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignUnitsId(const UnitsPtr &units);

    /**
     * @brief Assign an automatically generated, unique id to the given @p variable.
     *
     * Assign an automatically generated, unique id to the given @p variable.
     * This method will return the new id that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellMLElement) for a list of reasons that an id may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @param variable The @c VariablePtr which will be assigned the new id.
     *
     * @return the new id string.
     */
    std::string assignVariableId(const VariablePtr &variable);

    /**
     * @brief Get the number of items with the given @p id.
     *
     * Return the number of items with the given @p id.
     *
     * @param id A @c std::string for the id to find.
     *
     * @return the number of items with the given @p id.
     */
    size_t duplicateCount(const std::string &id);

    /**
     * @brief Test whether the annotator has a stored model.
     *
     * Test whether the annotator has a stored model.
     *
     * @return @c true if the annotator has a model, @c false otherwise.
     */
    bool hasModel() const;

private:
    Annotator(); /**< Constructor */

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
