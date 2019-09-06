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

#include "libcellml/entity.h"
#include "libcellml/exportdefinitions.h"
#include "libcellml/orderedentity.h"
#include "libcellml/types.h"

#include <string>

namespace libcellml {

/**
 * @brief The Reset class.
 * The Reset class is for describing a CellML reset.
 */
class LIBCELLML_EXPORT Reset: public OrderedEntity
{
public:
    Reset(); /**< Constructor */
    ~Reset() override; /**< Destructor */
    Reset(const Reset &rhs); /**< Copy constructor */
    Reset(Reset &&rhs) noexcept; /**< Move constructor */
    Reset &operator=(Reset rhs); /**< Assignment operator */

    /**
     * @brief Set the @c Variable for this @c Reset.
     *
     * Set the @c Variable for this @c Reset.
     *
     * @param variable The @c Variable to set.
     */
    void setVariable(const VariablePtr &variable);

    /**
     * @brief Get the @c Variable for this @c Reset.
     *
     * Return the @c Variable of this @c Reset.
     *
     * @return The @c Variable.
     */
    VariablePtr variable() const;

    /**
     * @brief Set the test @c Variable for this @c Reset.
     *
     * Set the test @c Variable for this @c Reset.
     *
     * @param variable The test @c Variable to set.
     */
    void setTestVariable(const VariablePtr &variable);

    /**
     * @brief Get the test variable for this @c Reset.
     *
     * Return the @c Variable used in the test condition of this @c Reset.
     *
     * @return The @c Variable used in the test condition.
     */
    VariablePtr testVariable() const;

    /**
     * @brief Append the argument to the test value string for this reset.
     *
     * Append @p math to the existing test value string for this reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void appendTestValue(const std::string &math);

    /**
     * @brief Get the test value string for this reset.
     *
     * Return a test value string if one has been appended for this reset. Returns
     * an empty string if a test value has not been appended (or has been removed).
     *
     * @return @c std::string test value for this reset.
     */
    std::string testValue() const;

    /**
     * @brief Set the test value string for this reset.
     *
     * Set the test value string for this reset. If @p math is an empty
     * string, the test value will effectively be removed from the reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void setTestValue(const std::string &math);

    /**
     * @brief Set an identifier to the test value for this reset.
     *
     * Set the identifier to the test value string for this reset.  Setting
     * the @p id to the empty string will effectively remove the identifier.
     *
     * @param id The @c std::string to set for this reset's test value.
     */
    void setTestValueId(const std::string &id);

    /**
     * @brief Return the identifier of the test value for this reset.
     *
     * Get the identifier of the test value for this reset.
     *
     * @return @c std::string The identifier of the test value for this reset.
     */
    std::string testValueId() const;

    /**
     * @brief Append the argument to the reset value for this reset.
     *
     * Append @p math to the existing reset value for this reset.
     *
     * @param math The @c std::string to append to the reset value for this reset.
     */
    void appendResetValue(const std::string &math);

    /**
     * @brief Get the reset value string for this reset.
     *
     * Return a math string if one has been appended for this reset. Returns
     * an empty string if math has not been appended (or has been removed).
     *
     * @return @c std::string reset value for this reset.
     */
    std::string resetValue() const;

    /**
     * @brief Set the reset value math for this reset.
     *
     * Set the math to the reset value for this reset. If @p math is an empty
     * string, reset value will effectively be removed from the reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void setResetValue(const std::string &math);

    /**
     * @brief Set an identifier to the reset value for this reset.
     *
     * Set an identifier to the reset value for this reset.
     *
     * @param id The @c std::string to set for this reset's reset value identifier.
     */
    void setResetValueId(const std::string &id);

    /**
     * @brief Return the identifier of the reset value for this reset.
     *
     * Get the identifier of the reset value for this reset.
     *
     * @return @c std::string The identifier of the reset value for this reset.
     */
    std::string resetValueId() const;

private:
    void swap(Reset &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ResetImpl; /**< Forward declaration for pImpl idiom. */
    ResetImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
