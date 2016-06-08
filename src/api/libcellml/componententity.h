/*
Copyright 2015 University of Auckland

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

#ifndef LIBCELLML_LIBCELLML_COMPONENTENTITY_H
#define LIBCELLML_LIBCELLML_COMPONENTENTITY_H

#include <libcellml/libcellml_export.h>
#include <libcellml/importedentity.h>
#include <libcellml/types.h>

namespace libcellml {

class Component;
/**
 * @brief The ComponentEntity class.
 *
 * The interface class for managing Components.
 */
class LIBCELLML_EXPORT ComponentEntity: public ImportedEntity
{
public:
    /**
     * @brief ComponentEntity Constructor.
     *
     * Default ComponentEntity constructor.
     */
    ComponentEntity();
    /**
     * @brief ComponentEntity Destructor.
     *
     * Default ComponentEntity destructor.
     */
    ~ComponentEntity();

    ComponentEntity(ComponentEntity &&rhs); /**< Move constructor */
    ComponentEntity(const ComponentEntity &rhs); /**< Copy constructor */
    ComponentEntity& operator=(ComponentEntity rhs); /**< Assignment operator */

    /**
     * @brief Add a child units to this component entity.
     *
     * Add a copy of the given units as a child units of this component entity.
     *
     * @param units The units to add.
     */
    void addUnits(const UnitsPtr &units);

    /**
     * @brief Remove the units at the given index.
     *
     * Remove the units from this component entity at the index @p index.
     * If the index is not in the range [0, #units], a @c std::out_of_range
     * exception will be thrown.
     *
     * @param index The index of the units to remove (zero-based).
     */
    void removeUnits(size_t index);

    /**
     * @brief Remove the units with the given @p name.
     *
     * Remove the first units found with the name @p name.
     * If the name is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param name The name of the units to remove.
     */
    void removeUnits(const std::string &name);

    /**
     * @brief Remove the units with the given pointer.
     *
     * Remove the units with the pointer @p units. If the
     * units are not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param units The pointer to the units to remove.
     */
    void removeUnits(const UnitsPtr &units);

    /**
     * @brief Remove all units stored in this component entity.
     *
     * Clears all units that have been added to this component entity.
     */
    void removeAllUnits();

    /**
     * @brief Tests to see if the units is within this component entity.
     *
     * Tests to see if the units with the given name 'name' is contained
     * within this component entity.  Returns @c true if the units is in
     * the component entity and @c false otherwise.
     *
     * @param name The name of the units to test for existence in
     * this component entity.
     *
     * @return @c true if the named units is in the component entity
     * and @c false otherwise.
     */
    bool hasUnits(const std::string &name) const;

    /**
     * @brief Get a units at index.
     *
     * Returns a const reference to a units at the index @p index.  If the
     * index is not valid a @c std::out_of_range exception is thrown.
     *
     * @param index The index of the Units to return (zero-based).
     *
     * @return A const reference to the units at the given index.
     */
    const UnitsPtr& getUnits(size_t index) const;

    /**
     * @brief Get a units at index.
     *
     * Returns a reference to a units at the index @p index.  If the index
     * is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param index The index of the units to return (zero-based).
     *
     * @return A reference to the units at the given index.
     */
    UnitsPtr getUnits(size_t index);

    /**
     * @brief Get a units with the given name @p name.
     *
     * Returns a const reference to a units with the name @p name.  If the
     * name is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to return.
     *
     * @return A const reference to the units with the given name.
     */
    const UnitsPtr& getUnits(const std::string &name) const;

    /**
     * @brief Get a units with the given name @p name.
     *
     * Returns a reference to a units with the name @p name.  If the name
     * is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to return.
     *
     * @return A reference to the units with the given name.
     */
    UnitsPtr getUnits(const std::string &name);

    /**
     * @brief Take the units at the given index and return it.
     *
     * Removes the units at the given index position and returns it.
     * If an invalid index is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @param index The index of the units to take (zero-based).
     *
     * @return The units at the given index.
     */
    UnitsPtr takeUnits(size_t index);

    /**
     * @brief Take the units with the given name @p name and return it.
     *
     * Takes the units with the given name @p name and returns it.
     * If an invalid name is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to take.
     *
     * @return The Units identified with the given name.
     */
    UnitsPtr takeUnits(const std::string &name);

    /**
     * @brief Replace a units at index.
     *
     * Replaces the units at index @p index with @p units.  Index must be a valid index
     * position.
     *
     * @param index Index of the units to replace (zero-based).
     * @param units The units to use for replacement.
     */
    void replaceUnits(size_t index, const UnitsPtr &units);

    /**
     * @brief Replace a units with the given name.
     *
     * Replaces the units with the given name @p name with @p units.  Name must be a valid name
     * of a units in the component entity, if it isn't a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Units to replace.
     * @param units The units to use for replacement.
     */
    void replaceUnits(const std::string &name, const UnitsPtr &units);

    /**
     * @brief Get the number of units in the component entity.
     *
     * Returns the number of units (non-imported) the component entity contains.
     *
     * @return The number of units.
     */
    size_t unitsCount() const;

    /**
     * @brief Add a child component to this component entity.
     *
     * Add a copy of the given component as a child component of this component entity.
     *
     * @param c The component to add.
     */
    void addComponent(const ComponentPtr &c);

    /**
     * @brief Remove the component at the given index.
     *
     * Remove the component from the model with the index @p index.  If the index is
     * not in the range [0, #components) a std::out_of_range exception
     * will be thrown.
     *
     * @param index The index of the component to remove (zero-based).
     */
    void removeComponent(size_t index);

    /**
     * @brief Remove the component with the given name.
     *
     * Remove the first component found that matches the name @p name.
     * If the name is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param name The name of the component to remove.
     */
    void removeComponent(const std::string &name);

    /**
     * @brief Remove the component with the given pointer.
     *
     * Remove the component with the pointer @p component. If the
     * component is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param component The pointer to the component to remove.
     */
    void removeComponent(const ComponentPtr &component);

    /**
     * @brief Remove all components stored in this component entity.
     *
     * Clears all components that have been added to this component entity.
     */
    void removeAllComponents();

    /**
     * @brief Tests to see if the named component is contained within this component entity.
     *
     * Tests to see if the component with the given name @p name is contained
     * within this component entity.  Returns @c true if the component is in the component
     * entity and @c false otherwise.
     *
     * @param name The component name to test for existence in this component entity.
     *
     * @return @c true if the named component is in this component entity and @c false otherwise.
     */
    bool containsComponent(const std::string &name) const;

    /**
     * @brief Tests to see if the component pointer is contained within this component.
     *
     * Tests to see if the argument component pointer @p component is contained
     * within this component entity.  Returns @c true if the component is in the component
     * entity and @c false otherwise.
     *
     * @overload
     *
     * @param component The component pointer to test for existence in this component entity.
     *
     * @return @c true if the component is in the component entity and @c false otherwise.
     */
    bool containsComponent(const ComponentPtr &component) const;

    /**
     * @brief Get a component at index.
     *
     * Returns a const reference to a component at the index @p index.  If the
     * index is not valid a std::out_of_range exception is thrown.
     *
     * @param index The index of the Component to return (zero-based).
     *
     * @return A const reference to the Component at the given index.
     */
    const ComponentPtr& getComponent(size_t index) const;

    /**
     * @brief Get a component at index.
     *
     * Returns a reference to a component at the index @p index.  If the index
     * is not valid a std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param index The index of the Component to return (zero-based).
     *
     * @return A reference to the Component at the given index.
     */
    ComponentPtr getComponent(size_t index);

    /**
     * @brief Get a component with the given name @p name.
     *
     * Returns a const reference to a component with the name @p name.  If the
     * name is not valid a std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to return.
     *
     * @return A const reference to the Component with the given name.
     */
    const ComponentPtr& getComponent(const std::string &name) const;

    /**
     * @brief Get a component with the given name @p name.
     *
     * Returns a reference to a component with the name @p name.  If the name
     * is not valid a std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to return.
     *
     * @return A reference to the Component with the given name.
     */
    ComponentPtr getComponent(const std::string &name);

    /**
     * @brief Take the component at the given index and return it.
     *
     * Removes the component at the given index position and returns it.
     * If an invalid index is passed to the method a std::out_of_range
     * exception is thrown.
     *
     * @param index The index of the Component to take (zero-based).
     *
     * @return The Component at the given index.
     */
    ComponentPtr takeComponent(size_t index);

    /**
     * @brief Take the component with the given name @p name and return it.
     *
     * Takes the component with the given name @p name and returns it.
     * If an invalid name is passed to the method a std::out_of_range
     * exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to take.
     *
     * @return The Component identified with the given name.
     */
    ComponentPtr takeComponent(const std::string &name);

    /**
     * @brief Replace a component at index.
     *
     * Replaces the component at index @p index with @p c.  Index must be a valid index
     * position.
     *
     * @param index Index of the Component to replace (zero-based).
     * @param c The Component to use for replacement.
     */
    void replaceComponent(size_t index, const ComponentPtr &c);

    /**
     * @brief Replace a component with the given name.
     *
     * Replaces the component with the given name @p name with @p c.  Name must be a valid name
     * of a component in the Component, if it isn't a std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to replace.
     * @param c The Component to use for replacement.
     */
    void replaceComponent(const std::string &name, const ComponentPtr &c);

    /**
     * @brief Get the number of components in the component.
     *
     * Returns the number of components (non-imported) the component contains.
     *
     * @return The number of components.
     */
    size_t componentCount() const;

protected:

    /**
     * @brief Virtual add component method to be implemented by derived classes.
     *
     * Virtual addComponent method to allow the model and component classes to
     * implement their own versions.
     *
     * @param c The ComponentPtr to add to the list of components.
     */
    virtual void doAddComponent(const ComponentPtr &c);

    /**
     * @brief Protected units serialisation.
     *
     * @param format The format to serialise to.
     *
     * @return The string representation of the serialised units.
     */
    std::string serialiseUnits(Format format) const;

    /**
     * @brief Protected serialisation of encapsulated components.
     *
     * @param format The format to serialise to.
     *
     * @return the string representation of the serialised encapsulated components.
     */
    std::string serialiseEncapsulation(Format format) const;

private:
    void swap(ComponentEntity &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ComponentEntityImpl; /**< Forward declaration for pImpl idiom. */
    ComponentEntityImpl* mPimpl; /**< Private member to implementation pointer */

};

}

#endif // LIBCELLML_LIBCELLML_COMPONENTENTITY_H
