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

#include "libcellml/exportdefinitions.h"
#include "libcellml/namedentity.h"
#include "libcellml/types.h"

#include <string>

#ifndef SWIG
template class LIBCELLML_EXPORT std::weak_ptr<libcellml::Variable>;
#endif

namespace libcellml {

/**
 * @brief The Variable class.
 *
 * Class for each variable in libCellML.
 */
class LIBCELLML_EXPORT Variable: public NamedEntity
#ifndef SWIG
    ,
                                 public std::enable_shared_from_this<Variable>
#endif
{
public:
    ~Variable() override; /**< Destructor */
    Variable(const Variable &rhs) = delete; /**< Copy constructor */
    Variable(Variable &&rhs) noexcept = delete; /**< Move constructor */
    Variable &operator=(Variable rhs) = delete; /**< Assignment operator */

    template<typename... Args>
    static std::shared_ptr<Variable> create(Args &&... args) noexcept
    {
        return std::shared_ptr<Variable> {new Variable {std::forward<Args>(args)...}};
    }

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
     * @sa removeEquivalence, equivalentVariable
     *
     * @param variable1 The variable to copy to the equivalent variable set
     * for @p variable2.
     * @param variable2 The variable to copy to the equivalent variable set
     * for @p variable1.
     */
    static void addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2);

    /**
     * @brief Add each argument variable to the other's equivalent variable set.
     *
     * Add a copy of @p variable1 to the set of equivalent variables for
     * @p variable2 if not already present. Also add a copy of @p variable2 to the
     * set of equivalent variables for @p variable1 if not already present.  Also set the
     * mapping id of the equivalence and also optionally the connection id fo the
     * equivalence.
     *
     * @overload
     *
     * @param variable1 The variable to copy to the equivalent variable set
     * for @p variable2.
     * @param variable2 The variable to copy to the equivalent variable set
     * for @p variable1.
     * @param mappingId The @c std::string mapping id.
     * @param connectionId The @c std::string connection id (optional).
     */
    static void addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &mappingId, const std::string &connectionId = "");

    /**
     * @brief Set the equivalent mapping id for this equivalence.
     *
     * Record the given id as the mapping id for the equivalence defined with the given
     * variables.  The variables are commutative. This id appears in the 'map_variables'
     * element of the model when serialised.
     *
     * To clear an equivalence mapping id set it to the empty string. If the two variables are
     * not equivalent the mapping id is not set.
     *
     * @param variable1 Variable one of the equivalence.
     * @param variable2 Variable two of the equivalence.
     * @param mappingId The @c std::string mapping id.
     */
    static void setEquivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &mappingId);

    /**
     * @brief Set the equivalent connection id for this equivalence.
     *
     * Record the given id as the connection id for the equivalence defined with the given
     * variables.  The variables are commutative. This id appears in the 'connection'
     * element of the model when serialised.
     *
     * To clear an equivalence connection id set it to the empty string. If the two variables are
     * not equivalent the connection id is not set.
     *
     * @param variable1 Variable one of the equivalence.
     * @param variable2 Variable two of the equivalence.
     * @param connectionId The @c std::string connection id.
     */
    static void setEquivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &connectionId);

    /**
     * @brief Get the equivalent mapping id for this equivalence.
     *
     * Get the mapping id set for the equivalence defined with the given variables.
     * The variables are commutative.  If no mapping id is set the empty string is returned.
     *
     * If the two variables are not equivalent the empty string is returned.
     *
     * @param variable1Variable one of the equivalence.
     * @param variable2 Variable one of the equivalence.
     * @return the @c std::string mapping id.
     */
    static std::string equivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2);

    /**
     * @brief Get the equivalent connection id for this equivalence.
     *
     * Get the connection id set for the equivalence defined with the given variables.
     * The variables are commutative.  If no connection id is set the empty string is returned.
     *
     * If the two variables are not equivalent the empty string is returned.
     *
     * @param variable1 Variable one of the equivalence.
     * @param variable2 Variable one of the equivalence.
     * @return the @c std::string connection id.
     */
    static std::string equivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2);

    /**
     * @brief Remove each argument variable to the other's equivalent variable set.
     *
     * Removes a copy of @p variable1 from the set of equivalent variables for
     * @p variable2, if present. Also removes a copy of @p variable2 from the
     * set of equivalent variables for @p variable1, if present.
     *
     * @sa addEquivalence, equivalentVariable
     *
     * @param variable1 The variable to remove from the equivalent variable set
     * for @p variable2.
     * @param variable2 The variable to remove from the equivalent variable set
     * for @p variable1.
     *
     * @return True if the equivalence was removed, false otherwise.
     */
    static bool removeEquivalence(const VariablePtr &variable1, const VariablePtr &variable2);

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
     * variable. The index must be in the range [0, \#equivalentVariables).
     *
     * @param index The index of the variable to return.
     *
     * @return The equivalent variable at the given index.
     */
    VariablePtr equivalentVariable(size_t index) const;

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
     *
     * @deprecated This method is currently needed by our Printer and Validator classes, but this is
     * not a method that a libCellML user should ever need. It will therefore be removed at some point.
     */
    bool hasDirectEquivalentVariable(const VariablePtr &equivalentVariable) const;

    /**
     * @brief Test whether the argument variable is equivalent to this variable.
     *
     * Tests to see if the argument variable is equivalent to this variable. Returns @c true if
     * the argument variable is equivalent to this variable and @c false otherwise.
     *
     * @param equivalentVariable The variable to check for equivalence.
     *
     * @return @c true if the @p equivalentVariable is equivalent to this variable and
     * @c false otherwise.
     */
    bool hasEquivalentVariable(const VariablePtr &equivalentVariable) const;

    /**
     * @brief Set the units by @p name for this variable.
     *
     * Set the units for this variable by name. Set to an empty string
     * to unset the units.
     *
     * @sa units
     *
     * @param name The name of the units to set.
     */
    void setUnits(const std::string &name);

    /**
     * @brief Set the units for this variable using a @c UnitsPtr.
     *
     * Set the units for this variable as the name associated with the
     * argument @p units.
     *
     * @overload
     *
     * @sa units
     *
     * @param units The @c UnitsPtr to set.
     */
    void setUnits(const UnitsPtr &units);

    /**
     * @brief Get the name of the units for this variable.
     *
     * Get the name of the units for this variable. If no units are set
     * an empty @c std::string is returned.
     *
     * @sa setUnits
     *
     * @return The @c UnitsPtr of the units for this variable.
     */
    UnitsPtr units() const;

    /**
     * @brief Set the initial value for this variable using a string.
     *
     * Set the initial value for this variable using a string.
     *
     * @sa initialValue
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
     * @sa initialValue
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
     * @sa initialValue
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
    std::string initialValue() const;

    /**
     * @brief Set the interface type for this variable.
     *
     * Set the interface type for this variable using a string.
     *
     * @sa interfaceType
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
     * @sa interfaceType
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
    std::string interfaceType() const;

private:
    Variable(); /**< Constructor */
    explicit Variable(const std::string &name);

    struct VariableImpl; /**< Forward declaration for pImpl idiom. */
    VariableImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
