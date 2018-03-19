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

#include "libcellml/componententity.h"
#include "libcellml/exportdefinitions.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Model class.
 *
 * The Model class is for representing a CellML Model.
 */
class LIBCELLML_EXPORT Model: public ComponentEntity
{
public:
    Model(); /**< Constructor */
    ~Model(); /**< Destructor */
    Model(const Model &rhs); /**< Copy constructor */
    Model(Model &&rhs); /**< Move constructor */
    Model& operator=(Model m); /**< Assignment operator */

    /**
     * @brief Add a child units to this model.
     *
     * Add a copy of the given units as a child units of this model.
     *
     * @param units The units to add.
     */
    void addUnits(const UnitsPtr &units);

    /**
     * @brief Remove the units at the given @p index.
     *
     * Remove the units from this model at the given @p index.
     * @p index must be in the range [0, #units).
     *
     * @param index The index of the units to remove.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool removeUnits(size_t index);

    /**
     * @brief Remove the units with the given @p name.
     *
     * Remove the first units found with the given @p name.
     *
     * @overload
     *
     * @param name The name of the units to remove.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool removeUnits(const std::string &name);

    /**
     * @brief Remove the units with the given pointer.
     *
     * Remove the units with the pointer @p units.
     *
     * @overload
     *
     * @param units The pointer to the units to remove.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool removeUnits(const UnitsPtr &units);

    /**
     * @brief Remove all units stored in this model.
     *
     * Clears all units that have been added to this model.
     */
    void removeAllUnits();

    /**
     * @brief Tests to see if the units is within this model.
     *
     * Tests to see if the units with the given @c name is contained
     * within this component entity.  Returns @c true if the units is in
     * the model and @c false otherwise.
     *
     * @param name The name of the units to test for existence in
     * this model.
     *
     * @return @c true if the named units is in the model
     * and @c false otherwise.
     */
    bool hasUnits(const std::string &name) const;

    /**
     * @brief Get a units at the given @p index.
     *
     * Returns a reference to a units at the given @p index.  If the @p index
     * is not valid a @c nullptr is returned, the range of valid values for the
     * index is [0, #units).
     *
     * @overload
     *
     * @param index The index of the units to return.
     *
     * @return A reference to the units at the given @p index on success, @c nullptr otherwise.
     */
    UnitsPtr getUnits(size_t index) const;

    /**
     * @brief Get a units with the given @p name.
     *
     * Returns a reference to a units with the given @p name.  If the @p name
     * is not valid a @c nullptr is returned.
     *
     * @overload
     *
     * @param name The name of the units to return.
     *
     * @return A reference to the units with the given @p name on success, @c nullptr otherwise.
     */
    UnitsPtr getUnits(const std::string &name) const;

    /**
     * @brief Take the units at the given @p index and return it.
     *
     * Removes the units at the given @p index position and returns it.
     * @p index must be in the range [0, #units).
     *
     * @param index The index of the units to take.
     *
     * @return A reference to the units at the given @p index if the index is valid, @c nullptr otherwise.
     */
    UnitsPtr takeUnits(size_t index);

    /**
     * @brief Take the units with the given @p name and return it.
     *
     * Takes the first occurence of the units with the given name @p name and returns it.
     * If no units with name @p name is found then a @c nullptr is returned.
     *
     * @overload
     *
     * @param name The name of the units to take.
     *
     * @return A reference to the units identified with the given @p name if found, @c nullptr otherwise.
     */
    UnitsPtr takeUnits(const std::string &name);

    /**
     * @brief Replace a units at the given @p index.
     *
     * Replaces the units at the given @p index with @p units.
     * @p index must be in the range [0, #units).
     *
     * @param index Index of the units to replace.
     * @param units The units to use for replacement.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool replaceUnits(size_t index, const UnitsPtr &units);

    /**
     * @brief Replace a units with the given @p name.
     *
     * Replaces the units with the given @p name with @p units.
     *
     * @overload
     *
     * @param name The name of the units to replace.
     * @param units The units to use for replacement.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool replaceUnits(const std::string &name, const UnitsPtr &units);

    /**
     * @brief Replace a units with another units.
     *
     * Replaces one units with another.
     *
     * @overload
     *
     * @param oldUnits The units to be replaced.
     * @param newUnits The units to use for replacement.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool replaceUnits(const UnitsPtr &oldUnits, const UnitsPtr &newUnits);

    /**
     * @brief Get the number of units in the model.
     *
     * Returns the number of units the model contains.
     *
     * @return The number of units.
     */
    size_t unitsCount() const;

private:
    void doAddComponent(const ComponentPtr &c);
    void swap(Model &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ModelImpl; /**< Forward declaration for pImpl idiom. */
    ModelImpl *mPimpl; /**< Private member to implementation pointer */
};

}
