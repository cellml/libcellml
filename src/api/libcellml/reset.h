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
class LIBCELLML_EXPORT Reset: public OrderedEntity
{
public:
    Reset(); /**< Constructor */
    ~Reset(); /**< Destructor */
    Reset(const Reset &rhs); /**< Copy constructor */
    Reset(Reset &&rhs); /**< Move constructor */
    Reset& operator=(Reset n); /**< Assignment operator */

    /**
     * @brief Set the @c Variable for this @c Reset.
     *
     * Sets the @c Variable for this @c Reset.
     *
     * @param variable The @c Variable to set.
     */
    void setVariable(VariablePtr variable);

    /**
     * @brief Get the @c Variable for this @c Reset.
     *
     * Returns the @c Variable of this @c Reset.
     *
     * @return The @c Variable.
     */
    VariablePtr getVariable() const;

    /**
     * @brief Add a child when to this @c Reset.
     *
     * Add a copy of the given @p when as a child @c When of this @c Reset.
     *
     * @param when The @c When to add.
     */
    void addWhen(const WhenPtr &when);

    /**
     * @brief Remove the @c When at the given @p index.
     *
     * Remove the @c When with the given @p index. @p index must
     * be in the range [0, \#Whens).
     *
     * @param index The index of the @c When to remove.
     *
     * @return True if the @c When was removed, false otherwise.
     */
    bool removeWhen(size_t index);

    /**
     * @brief Remove the @c When with the given pointer.
     *
     * Remove the @c When with the pointer @p when.
     *
     * @overload
     *
     * @param when The pointer to the @c When to remove.
     * @return True if the @c When was removed, false otherwise.
     */
    bool removeWhen(const WhenPtr &when);

    /**
     * @brief Remove all @c Whens stored in this @c Reset.
     *
     * Clears all @c Whens that have been added to this @c Reset.
     */
    void removeAllWhens();

    /**
     * @brief Tests to see if the @c When pointer is contained within this @c Reset.
     *
     * Tests to see if the argument @c When pointer @p when is contained
     * within this @c When entity. Returns @c true if the @c When is within this @c Reset
     * entity and @c false otherwise.
     *
     * @overload
     *
     * @param when The @c When pointer to test for existence in this @c Reset.
     *
     * @return @c true if the @c When is in the @c Reset and @c false otherwise.
     */
    bool containsWhen(const WhenPtr &when) const;

    /**
     * @brief Get a @c When at the given @p index.
     *
     * Returns a reference to a @c When at the given @p index.  @p index must
     * be in the range [0, \#Whens).
     *
     * @overload
     *
     * @param index The index of the @c When to return.
     *
     * @return The @c When at the given @p index on success, @c nullptr on failure.
     */
    WhenPtr getWhen(size_t index) const;

    /**
     * @brief Take the @c When at the given @p index and return it.
     *
     * Removes the @c When at the given @p index position and returns it.
     * @p index must be in the range [0, \#Whens).
     *
     * @param index The index of the @c When to take.
     *
     * @return The @c When at the given @p index, @c nullptr on failure.
     */
    WhenPtr takeWhen(size_t index);

    /**
     * @brief Replace a @c When at the given @p index.
     *
     * Replaces the @c When at the @p index with @p when. @p index must be in
     * the range [0, \#Whens).
     *
     * @param index Index of the @c When to replace.
     * @param when The @c When to be used as a replacement.
     *
     * @return True if the @c When was replaced, false otherwise.
     */
    bool replaceWhen(size_t index, const WhenPtr &when);

    /**
     * @brief Get the number of @c Whens in the @c Reset.
     *
     * Returns the number of @c Whens the @c Reset contains.
     *
     * @return The number of @c Whens.
     */
    size_t whenCount() const;

private:
    void swap(Reset &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ResetImpl; /**< Forward declaration for pImpl idiom. */
    ResetImpl *mPimpl; /**< Private member to implementation pointer */
};

}
