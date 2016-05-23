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

#ifndef LIBCELLML_LIBCELLML_VARIABLE_H
#define LIBCELLML_LIBCELLML_VARIABLE_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/namedentity.h"

namespace libcellml {

/**
 * @brief The Variable class.
 *
 * Class for each variable in libCellML.
 */
class LIBCELLML_EXPORT Variable: public NamedEntity
{
public:
    Variable(); /**< Constructor */
    ~Variable(); /**< Destructor */
    Variable(const Variable &rhs); /**< Copy constructor */
    Variable(Variable &&rhs); /**< Move constructor */
    Variable& operator=(Variable n); /**< Assignment operator */

    /**
     * @brief The InterfaceType enum class.
     *
     * Enum describing the interface types that are available for
     * a given variable.
     */
    enum class InterfaceType
    {
        NONE,
        PRIVATE,
        PUBLIC,
        PUBLIC_AND_PRIVATE
    };

    /**
     * @brief Add each argument variable to the other's equivalent variable set.
     *
     * Add a copy of @p variable1 to the set of equivalent variables for
     * @p variable2 if not already present. Also add a copy of @p variable2 to the
     * set of equivalent variables for @p variable1 if not already present.
     *
     * @sa removeEquivalence, getEquivalentVariable, setEquivalentTo
     *
     * @param variable1 The variable to copy to the equivalent variable set
     * for @p variable2.
     * @param variable2 The variable to copy to the equivalent variable set
     * for @p variable1.
     */
    static void addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2);

    /**
     * @brief Remove each argument variable to the other's equivalent variable set.
     *
     * Removes a copy of @p variable1 from the set of equivalent variables for
     * @p variable2, if present. Also removes a copy of @p variable2 from the
     * set of equivalent variables for @p variable1, if present.
     *
     * @sa addEquivalence, unsetEquivalentTo, getEquivalentVariable
     *
     * @param variable1 The variable to remove from the equivalent variable set
     * for @p variable2.
     * @param variable2 The variable to remove from the equivalent variable set
     * for @p variable1.
     */
    static void removeEquivalence(const VariablePtr &variable1, const VariablePtr &variable2);

    /**
     * @brief Remove all equivalent variables for this variable.
     *
     * Clears all equivalent variables that have been added to the set for this variable.
     */
    void removeAllEquivalences();

    /**
     * @brief Get an equivalent variable at @p index.
     *
     * Returns the equivalent variable at the index @p index for this
     * variable.
     *
     * @param index The index of the variable to return (zero-based).
     *
     * @return The equivalent variable at the given index.
     */
    VariablePtr getEquivalentVariable(size_t index);

    /**
     * @brief Get the number of equivalent variables for this variable.
     *
     * Returns the number of equivalent variables for this variable.
     *
     * @return the number of equivalent variables.
     */
    size_t equivalentVariableCount() const;

    /**
     * @brief Test whether the argument variable is in this variable's equivalent variables.
     *
     * Tests to see if the argument variable exists in the set of this variable's equivalent
     * variables. Returns @c true if the argument variable is in this variable's equivalent
     * variables and @c false otherwise.
     *
     * @param equivalentVariable The variable to check for in this variable's equivalent variables.
     *
     * @return @c true if the @p equivalentVariable is in this variable's equivalent variables
     * and @c false otherwise.
     */
    bool hasEquivalentVariable(const VariablePtr &equivalentVariable);

    /**
     * @brief Set the units for this variable.
     *
     * Set the units for this variable. Set to @c nullptr to unset the units.
     *
     * @sa getUnits
     *
     * @param u The units to set.
     */
    void setUnits(const UnitsPtr &u);

    /**
     * @brief Get the units for this variable.
     *
     * Get the units for this variable.  If no units are set @c nullptr is returned.
     *
     * @sa setUnits
     *
     * @param u The units to get.
     */
    UnitsPtr getUnits() const;

    /**
     * @brief Set the initial value for this variable using a string.
     *
     * Set the initial value for this variable using a string.
     *
     * @sa getInitialValue
     *
     * @param initialValue The initial value to set.
     */
    void setInitialValue(const std::string &initialValue);

    /**
     * @brief Set the initial value for this variable using a real number.
     *
     * Set the initial value for this variable using a real number.
     * The real number value will be converted to and stored as a string.
     *
     * @overload
     *
     * @sa getInitialValue
     *
     * @param initialValue The initial value to set.
     */
    void setInitialValue(double initialValue);

    /**
     * @brief Set the initial value for this variable using a variable reference.
     *
     * Set the initial value for this variable using a variable reference.
     * The initial value will be set to the name of the referenced variable.
     *
     * @overload
     *
     * @sa getInitialValue
     *
     * @param variable The variable reference to use to set the initial value.
     */
    void setInitialValue(const VariablePtr &variable);

    /**
     * @brief Get the initial value for this variable.
     *
     * Get the string corresponding to the initial value for this variable.
     *
     * @sa setInitialValue
     */
    std::string getInitialValue() const;

    /**
     * @brief Set the interface type for this variable.
     *
     * Set the interface type for this variable using a string.
     *
     * @sa getInterfaceType
     *
     * @param interfaceType The string interface type to set for this variable.
     */
    void setInterfaceType(const std::string &interfaceType);

    /**
     * @brief Set the interface type for this variable.
     *
     * Set the interface type for this variable from the available
     * options in the InterfaceType enum class.
     *
     * @overload
     *
     * @sa getInterfaceType
     *
     * @param interfaceType The enum interface type to set for this variable.
     */
    void setInterfaceType(InterfaceType interfaceType);

    /**
     * @brief Get the interface type for this variable.
     *
     * Get the string corresponding to the interface type for this variable.
     *
     * @sa setInterfaceType
     */
    std::string getInterfaceType() const;

private:
    void swap(Variable &rhs); /**< Swap method required for C++ 11 move semantics. */

    /**
     * @brief Private function to add an equivalent variable to the set for this variable.
     *
     * Add the argument equivalent variable to the set of equivalent variables for this
     * variable if it is not already present. If the equivalent variable is present,
     * do nothing.
     *
     * @sa addEquivalence, unsetEquivalentTo
     *
     * @param equivalentVariable The variable to add to this variable's equivalent
     * variable set if not already present.
     */
    void setEquivalentTo(const VariablePtr &equivalentVariable);

    /**
     * @brief Private function to remove an equivalent variable from the set for this variable.
     *
     * Remove the @p equivalentVariable from the set of equivalent variables for this
     * variable if it is present. If the equivalent variable is not in this variable's set,
     * throw @c std::out_of_range.
     *
     * @sa removeEquivalence, setEquivalentTo
     *
     * @param equivalentVariable The variable to remove from this variable's equivalent
     * variable set if it is present.
     */
    void unsetEquivalentTo(const VariablePtr &equivalentVariable);

    std::string doSerialisation(Format format) const;

    struct VariableImpl; /**< Forward declaration for pImpl idiom. */
    VariableImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_VARIABLE_H */
