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
limitations under the License.Some license of other
*/

#ifndef LIBCELLML_LIBCELLML_COMPONENT_H
#define LIBCELLML_LIBCELLML_COMPONENT_H

#include "libcellml/libcellml_export.h"
#include "libcellml/componententity.h"

namespace libcellml {

/**
 * @brief The Component class.
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
     * Make this component an imported component by defining an import model
     * from which to extract the named component from.
     * @param imp The import from which the named component originates.
     * @param name The name of the component in the imported model to use.
     */
    void setSourceComponent(const ImportPtr &imp, const std::string &name);

    /**
     * @brief Add a variable by reference as part of this component.
     * Add a variable by reference as part of the given component.
     * @sa removeVariable
     * @param v The variable to add.
     */
    void addVariable(const VariablePtr &v);

    /**
     * @brief Remove the variable with the given name from this component.
     * Remove the variable with the given name from this component. If the
     * name is not found then no variable is removed.
     * @sa addVariable
     * @overload
     * @param name The name of the variable to remove.
     */
    void removeVariable(const std::string &name);

    /**
     * @brief Get a variable at index.
     * Returns a const reference to a variable at the index @p index for this
     * component.  If the index is not valid a std::out_of_range
     * exception is thrown.
     *
     * @param index The index of the variable to return (zero-based).
     * @return A const reference to the variable at the given index.
     */
    const VariablePtr& getVariable(size_t index) const;

    /**
     * @brief Get a variable at index.
     * Returns a reference to a variable at the index @p index for this
     * component. If the index is not valid a std::out_of_range exception
     * is thrown.
     *
     * @overload
     * @param index The index of the variable to return (zero-based).
     * @return A reference to the variable at the given index.
     */
    VariablePtr getVariable(size_t index);

    /**
     * @brief Get a variable with the given name @p name.
     * Returns a const reference to a variable with the name @p name for this
     * component.  If the name is not valid a std::out_of_range exception
     * is thrown.
     *
     * @overload
     * @param name The name of the variable to return.
     * @return A const reference to the variable with the given name.
     */
    const VariablePtr& getVariable(const std::string &name) const;

    /**
     * @brief Get a variable with the given name @p name.
     * Returns a reference to a variable with the name @p name for this
     * component.  If the name is not valid a std::out_of_range exception
     * is thrown.
     *
     * @overload
     * @param name The name of the variable to return.
     * @return A reference to the Variable with the given name.
     */
    VariablePtr getVariable(const std::string &name);

private:
    void doAddComponent(const ComponentPtr &c);

    struct ComponentImpl; /**< Forward declaration for pImpl idiom. */
    ComponentImpl* mPimpl; /**< Private member to implementation pointer */

};

}

#endif // LIBCELLML_LIBCELLML_COMPONENT_H

