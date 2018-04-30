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

#include "libcellml/exportdefinitions.h"
#include "libcellml/entity.h"
#include "libcellml/orderedentity.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Reset class.
 * The Reset class is for describing a CellML reset.
 */
class LIBCELLML_EXPORT Reset: public Entity, public OrderedEntity
{
public:
    Reset(); /**< Constructor */
    ~Reset(); /**< Destructor */
    Reset(const Reset &rhs); /**< Copy constructor */
    Reset(Reset &&rhs); /**< Move constructor */
    Reset& operator=(Reset n); /**< Assignment operator */

    /**
     * @brief Set the variable for this reset.
     *
     * Sets the variable for this reset.
     *
     * @param variable The variable to set.
     */
    void setVariable(VariablePtr variable);

    /**
     * @brief Get the variable for this reset.
     *
     * Returns the variable of this reset.
     *
     * @return The variable.
     */
    VariablePtr getVariable() const;

    /**
     * @brief Add a child when to this Reset.
     *
     * Add a copy of the given @c When as a child When of this @c Reset.
     *
     * @param w The When to add.
     */
    void addWhen(const WhenPtr &when);

    /**
     * @brief Remove the when at the given @p index.
     *
     * Remove the when with the given @p index. @p index must
     * be in the range [0, #whens).
     *
     * @param index The index of the when to remove.
     *
     * @return True if the when was replaced, false otherwise.
     */
    bool removeWhen(size_t index);

    /**
     * @brief Remove the when with the given pointer.
     *
     * Remove the when with the pointer @p when.
     *
     * @overload
     *
     * @param when The pointer to the when to remove.
     * Whens for the specified @p When pointer. Default value is @c true.
     *
     * @return True if the when was replaced, false otherwise.
     */
    bool removeWhen(const WhenPtr &when);

    /**
     * @brief Remove all whens stored in this when entity.
     *
     * Clears all whens that have been added to this reset.
     */
    void removeAllWhens();

    /**
     * @brief Tests to see if the when pointer is contained within this reset.
     *
     * Tests to see if the argument when pointer @p when is contained
     * within this When entity. Returns @c true if the when is in the reset
     * entity and @c false otherwise.
     *
     * @overload
     *
     * @param when The when pointer to test for existence in this reset entity.
     *
     * @return @c true if the when is in the reset entity and @c false otherwise.
     */
    bool containsWhen(const WhenPtr &when) const;

    /**
     * @brief Get a when at the given @p index.
     *
     * Returns a reference to a when at the given @p index.  @p index must
     * be in the range [0, #whens).
     *
     * @overload
     *
     * @param index The index of the when to return.
     *
     * @return The when at the given @p index on success, @c nullptr on failure.
     */
    WhenPtr getWhen(size_t index) const;

    /**
     * @brief Take the when at the given @p index and return it.
     *
     * Removes the when at the given @p index position and returns it.
     * @p index must be in the range [0, #Whens).
     *
     * @param index The index of the when to take.
     *
     * @return The when at the given @p index, @c nullptr on failure.
     */
    WhenPtr takeWhen(size_t index);

    /**
     * @brief Replace a when at the given @p index.
     *
     * Replaces the when at the @p index with when @p when. @p index must be in
     * the range [0, #whens).
     *
     * @param index Index of the when to replace.
     * @param when The when to be used as a replacement.
     *
     * @return True if the when was replaced, false otherwise.
     */
    bool replaceWhen(size_t index, const WhenPtr &when);

    /**
     * @brief Get the number of whens in the reset.
     *
     * Returns the number of whens the reset contains.
     *
     * @return The number of whens.
     */
    size_t whenCount() const;

private:
    void swap(Reset &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ResetImpl; /**< Forward declaration for pImpl idiom. */
    ResetImpl *mPimpl; /**< Private member to implementation pointer */
};

}
