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

#ifndef LIBCELLML_LIBCELLML_COMPONENT_H
#define LIBCELLML_LIBCELLML_COMPONENT_H

#include "libcellml/libcellml_export.h"
#include "libcellml/componententity.h"

namespace libcellml {

/**
 * @brief The Component class.
 *
 * The Component class is for representing a CellML Component.
 */
class LIBCELLML_EXPORT Component: public ComponentEntity
{
public:
    Component(); /**< Constructor */
    ~Component(); /**< Destructor */
    Component(const Component &rhs); /**< Copy constructor */
    Component(Component &&rhs); /**< Move constructor */
    Component& operator=(Component m); /**< Assignment operator */

    /**
     * @brief Set the source component for this component.
     *
     * Make this component an imported component by defining an import model
     * from which to extract the named component from.
     *
     * @param imp The import from which the named component originates.
     * @param name The name of the component in the imported model to use.
     */
    void setSourceComponent(const ImportPtr &imp, const std::string &name);

    /**
     * @brief Appends the argument to the math string for this component.
     *
     * Appends @p math to the existing math string for this component.
     *
     * @param math The @c std::string to append for this component.
     */
    void appendMath(const std::string &math);

    /**
     * @brief Get the math string for this component.
     *
     * Returns a math string if one has been appended for this component. Returns
     * an empty string if math has not been appended (or has been removed).
     *
     * @return @c std::string math for this component.
     */
    std::string getMath() const;

    /**
     * @brief Set the math string for this component.
     *
     * Sets the math string for this component. If @p math is an empty
     * string, math will be removed from the component.
     *
     * @param math The @c std::string to append for this component.
     */
    void setMath(const std::string &math);

    /**
     * @brief Add a variable by reference as part of this component.
     *
     * Add a variable by reference as part of the given component.
     *
     * @sa removeVariable
     *
     * @param v The variable to add.
     */
    void addVariable(const VariablePtr &v);

    /**
     * @brief Remove the variable with the given @p name from this component.
     *
     * Remove the variable with the given name from this component. If the
     * name is not found then throw @c std::out_of_range. If the named variable to
     * be removed is in a connection (is equivalent to another variable), this
     * component will not be serialised in the connection @c map_components.
     *
     * @sa addVariable
     *
     * @param name The name of the variable to remove.
     */
    void removeVariable(const std::string &name);

    /**
     * @brief Remove the variable by the given @p variable pointer from this component.
     *
     * Remove the variable with the given pointer from this component. If the
     * variable is not found then throw @c std::out_of_range. If the @p variable to
     * be removed is in a connection (is equivalent to another variable), this
     * component will not be serialised in the connection @c map_components.
     * @sa addVariable
     *
     * @overload
     *
     * @param variable The pointer to the variable to remove.
     */
    void removeVariable(const VariablePtr &variable);

    /**
     * @brief Remove all variables stored in this component.
     *
     * Clears all variables that have been added to this component. If any of the
     * variables to be removed are in connections (are equivalent to other variables),
     * this component will not be serialised in the connection @c map_components.
     */
    void removeAllVariables();

    /**
     * @brief Get a variable at index.
     *
     * Returns a const reference to a variable at the index @p index for this
     * component.  If the index is not valid a std::out_of_range
     * exception is thrown.
     *
     * @param index The index of the variable to return (zero-based).
     *
     * @return A const reference to the variable at the given index.
     */
    const VariablePtr& getVariable(size_t index) const;

    /**
     * @brief Get a variable at index.
     *
     * Returns a reference to a variable at the index @p index for this
     * component. If the index is not valid a std::out_of_range exception
     * is thrown.
     *
     * @overload
     *
     * @param index The index of the variable to return (zero-based).
     *
     * @return A reference to the variable at the given index.
     */
    VariablePtr getVariable(size_t index);

    /**
     * @brief Get a variable with the given name @p name.
     *
     * Returns a const reference to a variable with the name @p name for this
     * component.  If the name is not valid a std::out_of_range exception
     * is thrown.
     *
     * @overload
     *
     * @param name The name of the variable to return.
     *
     * @return A const reference to the variable with the given name.
     */
    const VariablePtr& getVariable(const std::string &name) const;

    /**
     * @brief Get a variable with the given name @p name.
     *
     * Returns a reference to a variable with the name @p name for this
     * component.  If the name is not valid a std::out_of_range exception
     * is thrown.
     *
     * @overload
     *
     * @param name The name of the variable to return.
     *
     * @return A reference to the Variable with the given name.
     */
    VariablePtr getVariable(const std::string &name);

    /**
     * @brief Get the number of variables in the component.
     *
     * Returns the number of variables the component directly contains.
     *
     * @return the number of variables.
     */
    size_t variableCount() const;

    /**
     * @brief Test whether the argument @p variable is in this component.
     *
     * Tests whether the argument @p variable exists in the set of this component's
     * variables. Returns @c true if the @p variable is in this component's
     * variables and @c false otherwise.
     *
     * @param variable The variable to check for in this component.
     *
     * @return @c true if the @p variable is in this component and @c false otherwise.
     */
    bool hasVariable(const VariablePtr &variable);

private:
    void swap(Component &rhs); /**< Swap method required for C++ 11 move semantics. */

    void doAddComponent(const ComponentPtr &c);
    std::string doSerialisation(Format format) const;

    struct ComponentImpl; /**< Forward declaration for pImpl idiom. */
    ComponentImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif // LIBCELLML_LIBCELLML_COMPONENT_H

