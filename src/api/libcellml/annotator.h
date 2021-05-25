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
     * @brief Create a @ref Annotator object.
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
     * @param model A @ref Model model to use in this annotator.
     */
    void setModel(const ModelPtr &model);

    /**
     * @brief Get the model associated with this annotator.
     *
     * Get the model associated with this annotator.  A @c nullptr
     * is returned if there is no model associated with this annotator.
     *
     * @return A @ref Model to a model, or a @c nullptr.
     */
    ModelPtr model() const;

    /**
     * @brief Return the item at @p index with the @p id.
     *
     * From a list of items extracted from the stored model find and return the item with
     * the given @p id string and @p index.  The default @p index is zero if none is given.
     *
     * Errors are logged if:
     *  - there is no stored model,
     *  - there is no item with the given @p id; or
     *  - there are multiple items with the given @p id.
     *
     * The item returned is an @ref AnyCellmlElement object containing both:
     *  - a type (as a @ref CellmlElementType enum); and
     *  - an item, which can be a
     *    - @ref Component,
     *    - @ref ImportSource,
     *    - @ref Model,
     *    - @ref Reset,
     *    - @ref Units,
     *    - @ref UnitsItem,
     *    - @ref Variable; or a
     *    - @ref VariablePair.
     *
     * @param id A @c std::string representing the @p id to retrieve.
     * @param index The index of the item to return from the list of items with @p id.
     *              The defualt index is zero if none is given.
     *
     * @return An @ref AnyCellmlElement item as described in item(const std::string &).
     */
    AnyCellmlElementPtr item(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Component in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Component at that location.
     *
     * A @c nullptr will be returned if:
     *  - no item with the given @p id exists in the stored model;
     *  - the given @p index is beyond the range [0, \#itemCount(id));
     *  - the item stored at the @p index is not a @ref ComponentPtr; or
     *  - the annotator does not have a model attached.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Component on success otherwise @c nullptr.
     */
    ComponentPtr component(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Component in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Component at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Component on success otherwise @c nullptr.
     */
    ComponentPtr componentEncapsulation(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Model in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Model at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Model on success otherwise @c nullptr.
     */
    ModelPtr encapsulation(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Variable in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Variable at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Variable on success otherwise @c nullptr.
     */
    VariablePtr variable(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Reset in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Reset at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Reset on success otherwise @c nullptr.
     */
    ResetPtr reset(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Model in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Model at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Model on success otherwise @c nullptr.
     */
    ModelPtr model(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref ImportSource in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref ImportSource at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return An @ref ImportSource on success otherwise @c nullptr.
     */
    ImportSourcePtr importSource(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Units in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Units at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Units on success otherwise @c nullptr.
     */
    UnitsPtr units(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref VariablePair in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref VariablePair at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref VariablePair on success otherwise @c nullptr.
     */
    VariablePairPtr mapVariables(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref VariablePair in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref VariablePair at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref VariablePair on success otherwise @c nullptr.
     */
    VariablePairPtr connection(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref UnitsItem in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref UnitsItem at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref UnitsItem on success otherwise @c nullptr.
     */
    UnitsItemPtr unitsItem(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Reset in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Reset at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Reset on success otherwise @c nullptr.
     */
    ResetPtr testValue(const std::string &id, size_t index = 0);

    /**
     * @brief From a list of items in the stored model with the given @p id string,
     *        this method returns a @ref Reset in the @p index position, if it exists.
     *
     * From a list of all items with the given @p id return the @ref Reset at that location.
     *
     * @see component(const std::string &, size_t) for times when a @c nullptr is returned.
     *
     * @param id A @c std::string representing the identifier of the item to retrieve.
     * @param index The position of an item within the list of items with the given @p id to retrieve.
     *
     * @return A @ref Reset on success otherwise @c nullptr.
     */
    ResetPtr resetValue(const std::string &id, size_t index = 0);

    /**
     * @brief Assign an identifier to every item without one in the model.
     *
     * Assign an identifier to every item in the model which do not already have an
     * identifier assigned.  Newly assigned identifiers will be unique within the model.
     * No identifiers will be added to MathML items.
     *
     * Existing identifiers will not be changed.
     *
     * Returns @c true if at least one identifier was assigned, @c false otherwise.
     *
     * @return @c true if any identifiers have been changed, @c false otherwise.
     */
    bool assignAllIds();

    /**
     * @brief Assign an identifier to every item without one in the given @p model.
     *
     * Assign a unique, automatic identifier to every item in the given @p model,
     * excluding its MathML items.
     *
     * Existing identifiers will not be changed.
     *
     * The given @p model replaces any previously stored in this annotator.
     *
     * @overload
     *
     * @param model The @ref Model to which identifiers will be assigned.
     *
     * @return @c true if any identifiers have been changed, @c false otherwise.
     */
    bool assignAllIds(ModelPtr &model);

    /**
     * @brief Assign an identifier string to every item of the given @p type in the model.
     *
     * Assign an identifier string to every item of the given @p type in the
     * model. Returns @c true if at least one identifier was assigned, @c false otherwise.
     *
     * Existing identifiers will not be changed.
     *
     * @param type Items of this @ref CellmlElementType will all be assigned a new identifier.
     *
     * @return @c true if any identifiers have been changed, @c false otherwise.
     */
    bool assignIds(CellmlElementType type);

    /**
     * @brief Clear all identifiers from the model.
     *
     * Clear all identifiers from all items in the stored model.
     * Does nothing if there is no model.
     */
    void clearAllIds();

    /**
     * @brief Clear all identifiers from all items in the given @p model.
     *
     * Clear all identifiers from the @p model. The given @p model will replace any model currently stored
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
     * @param id A @c std::string to test for uniqueness amongst the set of identifiers in the stored model.
     *
     * @return @c true if the @p id exists exactly once, @c false otherwise.
     */
    bool isUnique(const std::string &id);

    /**
     * @brief Return a @c std::vector of @ref AnyCellmlElement items which have the given @p id.
     *
     * Return all items with the given @p id.
     *
     * The annotator requires a model to be set with setModel(const ModelPtr &)
     * before this method can be called successfully.
     *
     * @param id A @c std::string used to identify the items to retrieve.
     *
     * @return a @c std::vector of @ref AnyCellmlElement items.
     */
    std::vector<AnyCellmlElementPtr> items(const std::string &id);

    /**
     * @brief Return a @c std::vector of @c std::strings representing all identifier
     * strings in the stored model.
     *
     * Return all identifiers in the stored model.
     *
     * The annotator requires a model to be set with setModel(const ModelPtr &)
     * before this method can be called successfully.
     *
     * @return a @c std::vector of @c std::strings.
     */
    std::vector<std::string> ids();

    /**
     * @brief Return a @c std::vector of @c std::strings representing any duplicated identifier
     * string in the stored model.
     *
     * Return all duplicated identifiers in the stored model.
     *
     * The annotator requires a model to be set with setModel(const ModelPtr &)
     * before this method can be called successfully.
     *
     * @return a @c std::vector of @c std::strings.
     */
    std::vector<std::string> duplicateIds();

    /**
     * @brief Assign an automatically generated, unique identifier to the given @p model.
     *
     * Assign an automatically generated, unique identifier to the given @p model.
     * The default is to assign an identifier to a MODEL item.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellmlElementType::MODEL and CellmlElementType::ENCAPSULATION are relevant any other
     * CellmlElementType type will not assign an identifier.  @see errorCount() if and/or error(size_t) for any
     * issues that may have been raised.
     *
     * An identifier will not be assigned if:
     *  - no model has been stored in this annotator;
     *  - the given @p item is not a member of the stored model;
     *  - the given @p item is not relevant to the given @p type; or
     *  - the given @p item is @c nullptr.
     *
     * @overload
     *
     * @param model A @ref Model model to which the new identifier will be assigned.
     * @param type An @ref CellmlElementType enumeration.
     *
     * @return the new identifier string.
     */
    std::string assignId(const ModelPtr &model, CellmlElementType type = CellmlElementType::MODEL);

    /**
     * @brief Assign an automatically generated, unique identifier to the given @p component.
     *
     * Assign an automatically generated, unique identifier to the given @p component.
     * The default is to assign an identifier to a COMPONENT item.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellmlElementType::COMPONENT and CellmlElementType::COMPONENT_REF are relevant any other
     * CellmlElementType type will not assign an identifier.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param component A @ref Component item.
     * @param type An @ref CellmlElementType enumeration.
     *
     * @return the new identifier string.
     */
    std::string assignId(const ComponentPtr &component, CellmlElementType type = CellmlElementType::COMPONENT);

    /**
     * @brief Assign an automatically generated, unique identifier to the given @p importSource.
     *
     * Assign an automatically generated, unique identifier to the given @p importSource.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param importSource An @ref ImportSourcePtr to which the new identifier will be assigned.
     *
     * @return the new identifier string.
     */
    std::string assignId(const ImportSourcePtr &importSource);

    /**
     * @overload
     *
     * @brief Assign an automatically generated, unique identifier of the associated @p type to the given @p reset.
     *
     * Assign an automatically generated, unique identifier of the associated @p type to the given @p reset.
     * The default is to assign an identifier to a RESET item.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellmlElementType::RESET, CellmlElementType::RESET_VALUE, and CellmlElementType::TEST_VALUE are relevant any other
     * CellmlElementType type will not assign an identifier.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param reset A @ref ResetPtr.
     * @param type An @ref CellmlElementType enumeration.
     *
     * @return the new identifier string.
     */
    std::string assignId(const ResetPtr &reset, CellmlElementType type = CellmlElementType::RESET);

    /**
     * @brief Assign an automatically generated, unique identifier to the given @p units.
     *
     * Assign an automatically generated, unique identifier to the given @p units.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param units A @ref UnitsPtr item to which the new identifier is assigned.
     *
     * @return the new identifier string.
     */
    std::string assignId(const UnitsPtr &units);

    /**
     * @brief Assign an automatically generated, unique identifier to the given @p unitsItem.
     *
     * Assign an automatically generated, unique identifier to the given @p unitsItem.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param unitsItem A @ref UnitsItem to which the new identifier is assigned.
     *
     * @return the new identifier string.
     */
    std::string assignId(const UnitsItemPtr &unitsItem);

    /**
     * @brief Assign an automatically generated, unique identifier to the given @p variable.
     *
     * Assign an automatically generated, unique identifier to the given @p variable.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param variable A @ref Variable item to which the new identifier is assigned.
     *
     * @return the new identifier string.
     */
    std::string assignId(const VariablePtr &variable);

    /**
     * @brief Assign an automatically generated, unique identifier to the associated @p type for the given @p pair.
     *
     * Assign an automatically generated, unique identifier to the associated @p type for the given @p pair.
     * The default is to assign an identifier to a MAP_VARIABLES item.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * Only CellmlElementType::MAP_VARIABLES, and CellmlElementType::CONNECTION are relevant any other
     * CellmlElementType type will not assign an identifier.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param pair A @ref VariablePair item.
     * @param type A @ref CellmlElementType enumeration.
     *
     * @return the new identifier string.
     */
    std::string assignId(const VariablePairPtr &pair, CellmlElementType type = CellmlElementType::MAP_VARIABLES);

    /**
     * @overload
     *
     * @brief Assign an automatically generated, unique identifier to the item of type @p type
     *        which exists between @p item1 and @p item2.
     *
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     * The default is to assign an identifier to a MAP_VARIABLES item.
     *
     * Only CellmlElementType::MAP_VARIABLES, and CellmlElementType::CONNECTION are relevant any other
     * CellmlElementType type will not assign an identifier.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param variable1 A @ref VariablePtr item defining to the first item in a connection or equivalence.
     * @param variable2 A @ref VariablePtr item defining to the second item in a connection or equivalence.
     * @param type A @ref CellmlElementType enumeration.
     *
     * @return the new identifier string.
     */
    std::string assignId(const VariablePtr &variable1, const VariablePtr &variable2, CellmlElementType type = CellmlElementType::MAP_VARIABLES);

    /**
     * @brief Assign an automatically generated, unique identifier to the unit item at index @p index
     *        within units @p units.
     *
     * Assign an automatically generated, unique identifier to the unit item at index @p index
     * within units @p units.
     * This method will return the new identifier that has been assigned, or an empty string
     * if the operation failed.
     *
     * @see assignId(const ModelPtr &, CellmlElementType) for a list of reasons that an identifier may not be assigned.
     * @see errorCount() if and/or error(size_t) for any issues that may have been raised.
     *
     * @overload
     *
     * @param units A @ref Units containing the child unit item.
     * @param index The index at which the child unit exists within the parent @p units item.
     *
     * @return the new identifier string.
     */
    std::string assignId(const UnitsPtr &units, size_t index);

    /**
     * @brief Get the number of items with the given @p id.
     *
     * Return the number of items with the given @p id.
     *
     * @param id A @c std::string for the identifier to find.
     *
     * @return the number of items with the given @p id.
     */
    size_t itemCount(const std::string &id);

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

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom, @private. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
