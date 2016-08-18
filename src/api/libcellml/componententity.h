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

#include "libcellml/importedentity.h"
#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

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
     * @brief Remove the units at the given @p index.
     *
     * Remove the units from this component entity at the given @p index.
     * If the @p index is not in the range [0, #units], a @c std::out_of_range
     * exception will be thrown.
     *
     * @param index The index of the units to remove (zero-based).
     */
    void removeUnits(size_t index);

    /**
     * @brief Remove the units with the given @p name.
     *
     * Remove the first units found with the given @p name.
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
     * Tests to see if the units with the given @c name is contained
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
     * @brief Get a units at the given @p index.
     *
     * Returns a @c const reference to a units at the given @p index.  If the
     * @p index is not valid a @c std::out_of_range exception is thrown.
     *
     * @param index The index of the units to return (zero-based).
     *
     * @return A @c const reference to the units at the given @p index.
     */
    const UnitsPtr& getUnits(size_t index) const;

    /**
     * @brief Get a units at the given @p index.
     *
     * Returns a reference to a units at the given @p index.  If the @p index
     * is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param index The index of the units to return (zero-based).
     *
     * @return A reference to the units at the given @p index.
     */
    UnitsPtr getUnits(size_t index);

    /**
     * @brief Get a units with the given @p name.
     *
     * Returns a @c const reference to a units with the given @p name.  If the
     * @p name is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to return.
     *
     * @return A @c const reference to the units with the given @p name.
     */
    const UnitsPtr& getUnits(const std::string &name) const;

    /**
     * @brief Get a units with the given @p name.
     *
     * Returns a reference to a units with the given @p name.  If the @p name
     * is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to return.
     *
     * @return A reference to the units with the given @p name.
     */
    UnitsPtr getUnits(const std::string &name);

    /**
     * @brief Take the units at the given @p index and return it.
     *
     * Removes the units at the given @p index position and returns it.
     * If an invalid @p index is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @param index The index of the units to take (zero-based).
     *
     * @return The units at the given @p index.
     */
    UnitsPtr takeUnits(size_t index);

    /**
     * @brief Take the units with the given @p name and return it.
     *
     * Takes the units with the given @p name and returns it.
     * If an invalid @p name is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to take.
     *
     * @return The Units identified with the given @p name.
     */
    UnitsPtr takeUnits(const std::string &name);

    /**
     * @brief Replace a units at the given @p index.
     *
     * Replaces the units at the given @p index with @p units.  If an invalid @p index
     * is passed to the method a @c std::out_of_range exception is thrown.
     *
     * @param index Index of the units to replace (zero-based).
     * @param units The units to use for replacement.
     */
    void replaceUnits(size_t index, const UnitsPtr &units);

    /**
     * @brief Replace a units with the given @p name.
     *
     * Replaces the units with the given @p name with @p units. @p name must refer to
     * a valid name of a units in the component entity, otherwise a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the units to replace.
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
     * @brief Remove the component at the given @p index.
     *
     * Remove the component from the model with the given @p index.  If the @p index is
     * not in the range [0, #components) a @c std::out_of_range exception will be thrown.
     *
     * @param index The index of the component to remove (zero-based).
     */
    void removeComponent(size_t index);

    /**
     * @brief Remove the component with the given @p name.
     *
     * Remove the first component found that matches the given @p name.
     * If @p searchEncapsulated is @c true (default) this will also
     * search for the named component through this component's encapsulated components.
     * If the @p name is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param name The name of the component to remove.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the component with the specified @p name. Default value is @c true.
     */
    void removeComponent(const std::string &name, bool searchEncapsulated=true);

    /**
     * @brief Remove the component with the given pointer.
     *
     * Remove the component with the pointer @p component. If @p searchEncapsulated is @c true (default)
     * this will also search for the component pointer through this component's encapsulated components.
     * If the component is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param component The pointer to the component to remove.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the specified @p component pointer. Default value is @c true.
     */
    void removeComponent(const ComponentPtr &component, bool searchEncapsulated=true);

    /**
     * @brief Remove all components stored in this component entity.
     *
     * Clears all components that have been added to this component entity.
     */
    void removeAllComponents();

    /**
     * @brief Tests to see if the named component is contained within this component entity.
     *
     * Tests to see if the component with the given @p name is contained
     * within this component entity. If @p searchEncapsulated is @c true (default) this will also
     * search for the named component in this component's encapsulated components.
     * Returns @c true if the component is in the component entity and @c false otherwise.
     *
     * @param name The component name to test for existence in this component entity.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the component with the specified @p name. Default value is @c true.
     *
     * @return @c true if the named component is in this component entity and @c false otherwise.
     */
    bool containsComponent(const std::string &name, bool searchEncapsulated=true) const;

    /**
     * @brief Tests to see if the component pointer is contained within this component.
     *
     * Tests to see if the argument component pointer @p component is contained
     * within this component entity. If @p searchEncapsulated is @c true (default) this will also
     * search for the component pointer in this component's encapsulated components.
     * Returns @c true if the component is in the component entity and @c false otherwise.
     *
     * @overload
     *
     * @param component The component pointer to test for existence in this component entity.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the specified @p component pointer. Default value is @c true.
     *
     * @return @c true if the component is in the component entity and @c false otherwise.
     */
    bool containsComponent(const ComponentPtr &component, bool searchEncapsulated=true) const;

    /**
     * @brief Get a component at the given @p index.
     *
     * Returns a @c const reference to a component at the given @p index.  If
     * the @p index is not valid a @c std::out_of_range exception is thrown.
     *
     * @param index The index of the Component to return (zero-based).
     *
     * @return A @c const reference to the Component at the given @p index.
     */
    const ComponentPtr& getComponent(size_t index) const;

    /**
     * @brief Get a component at the given @p index.
     *
     * Returns a reference to a component at the given @p index.  If the @p index
     * is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param index The index of the Component to return (zero-based).
     *
     * @return A reference to the Component at the given @p index.
     */
    ComponentPtr getComponent(size_t index);

    /**
     * @brief Get a component with the given @p name.
     *
     * Returns a @c const reference to a component with the given @p name. If @p searchEncapsulated
     * is @c true (default) this will also search for the named component through this component's
     * encapsulated components. If the @p name is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to return.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the component with the specified @p name. Default value is @c true.
     *
     * @return A @c const reference to the Component with the given @p name.
     */
    const ComponentPtr getComponent(const std::string &name, bool searchEncapsulated=true) const;

    /**
     * @brief Get a component with the given @p name.
     *
     * Returns a reference to a component with the given @p name. If @p searchEncapsulated
     * is @c true (default) this will also search for the named component through this component's
     * encapsulated components. If the @p name is not valid a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to return.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the component with the specified @p name. Default value is @c true.
     *
     * @return A reference to the Component with the given @p name.
     */
    ComponentPtr getComponent(const std::string &name, bool searchEncapsulated=true);

    /**
     * @brief Take the component at the given @p index and return it.
     *
     * Removes the component at the given @p index position and returns it.
     * If an invalid @p index is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @param index The index of the Component to take (zero-based).
     *
     * @return The Component at the given @p index.
     */
    ComponentPtr takeComponent(size_t index);

    /**
     * @brief Take the component with the given @p name and return it.
     *
     * Takes the component with the given @p name and returns it. If @p searchEncapsulated
     * is @c true (default) this will also search for the named component through this component's
     * encapsulated components. If an invalid @p name is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to take.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the component with the specified @p name. Default value is @c true.
     *
     * @return The Component identified with the given @p name.
     */
    ComponentPtr takeComponent(const std::string &name, bool searchEncapsulated=true);

    /**
     * @brief Replace a component at the given @p index.
     *
     * Replaces the component at the @p index with component @p c. @p index must be a
     * valid index position.
     *
     * @param index Index of the Component to replace (zero-based).
     * @param c The component to be used as a replacement.
     */
    void replaceComponent(size_t index, const ComponentPtr &c);

    /**
     * @brief Replace a component with the given @p name.
     *
     * Replaces the component with the given @p name with @p c. If @p searchEncapsulated
     * is @c true (default) this will also search for the named component through this component's
     * encapsulated components. @p name must be a valid name of a component in this component,
     * otherwise a @c std::out_of_range exception is thrown.
     *
     * @overload
     *
     * @param name The name of the Component to replace.
     * @param c The Component to use for replacement.
     * @param searchEncapsulated Boolean flag to indicate whether we should also search encapsulated
     * components for the component with the specified @p name. Default value is @c true.
     */
    void replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated=true);

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
    /**
     * @brief Remove the component with the given @p name from this component entity.
     *
     * Remove the first component found that matches the given @p name from this
     * component entity. If the @p name is not found throw @c std::out_of_range.
     *
     * @param name The name of the component to remove.
     */
    void removeComponentInThis(const std::string &name);

    /**
     * @brief Remove the component with the given pointer from this component entity.
     *
     * Remove the component with the pointer @p component from this component entity.
     * If the component is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param component The pointer to the component to remove.
     */
    void removeComponentInThis(const ComponentPtr &component);

    /**
     * @brief Tests to see if the named component is contained within this component entity.
     *
     * Tests to see if the component with the given @p name is contained
     * within this component entity.  Returns @c true if the component is in the component
     * entity and @c false otherwise.
     *
     * @param name The component name to test for existence in this component entity.
     *
     * @return @c true if the named component is in this component entity and @c false otherwise.
     */
    bool containsComponentInThis(const std::string &name) const;

    /**
     * @brief Tests to see if the component pointer is contained within this component entity.
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
    bool containsComponentInThis(const ComponentPtr &component) const;

    /**
     * @brief Get a component with the given @p name in this component entity.
     *
     * Returns a @c const reference to a component with the given @p name in this
     * component entity.  If the @p name is not valid a @c std::out_of_range
     * exception is thrown.
     *
     * @param name The name of the Component to return.
     *
     * @return A @c const reference to the Component with the given @p name.
     */
    const ComponentPtr& getComponentInThis(const std::string &name) const;

    /**
     * @brief Get a component with the given @p name in this component entity.
     *
     * Returns a reference to a component with the given @p name in this
     * component entity.  If the @p name is not valid a @c std::out_of_range
     * exception is thrown.
     *
     * @param name The name of the Component to return.
     *
     * @return A reference to the Component with the given @p name.
     */
    ComponentPtr getComponentInThis(const std::string &name);

    /**
     * @brief Take the component with the given @p name from this component
     * entity and return it.
     *
     * Takes the component with the given @p name from this component entity
     * and returns it. If an invalid @p name is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @param name The name of the Component to take.
     *
     * @return The Component identified with the given @p name.
     */
    ComponentPtr takeComponentInThis(const std::string &name);

    /**
     * @brief Replace a component with the given @p name in this component entity.
     *
     * Replaces the component with the given @p name in this component entity
     * with @p c. @p name must be a valid name of a component in the Component,
     * otherwise a @c std::out_of_range exception is thrown.
     *
     * @param name The name of the Component to replace.
     * @param c The Component to use for replacement.
     */
    void replaceComponentInThis(const std::string &name, const ComponentPtr &c);

    void swap(ComponentEntity &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ComponentEntityImpl; /**< Forward declaration for pImpl idiom. */
    ComponentEntityImpl *mPimpl; /**< Private member to implementation pointer */

};

}
