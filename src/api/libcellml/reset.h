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
     * Sets the @c Variable for this @c Reset.
     *
     * @param variable The @c Variable to set.
     */
    void setVariable(const VariablePtr &variable);

    /**
     * @brief Get the @c Variable for this @c Reset.
     *
     * Returns the @c Variable of this @c Reset.
     *
     * @return The @c Variable.
     */
    VariablePtr variable() const;

    /**
     * @brief Set the @c TestVariable for this @c Reset.
     *
     * Sets the @c TestVariable for this @c Reset.
     *
     * @param variable The @c TestVariable to set.
     */
    void setTestVariable(const VariablePtr &variable);

    /**
     * @brief Get the @c TestVariable for this @c Reset.
     *
     * Returns the @c TestVariable of this @c Reset.
     *
     * @return The @c TestVariable.
     */
    VariablePtr testVariable() const;

    /**
     * @brief Appends the argument to the testValue string for this reset.
     *
     * Appends @p math to the existing testValue string for this reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void appendTestValue(const std::string &math);

    /**
     * @brief Get the testValue string for this reset.
     *
     * Returns a testValue string if one has been appended for this reset. Returns
     * an empty string if testValue has not been appended (or has been removed).
     *
     * @return @c std::string testValue for this reset.
     */
    std::string testValue() const;

    /**
     * @brief Set the TestValue string for this reset.
     *
     * Sets the TestValue string for this reset. If @p math is an empty
     * string, TestValue will be removed from the reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void setTestValue(const std::string &math);

    /**
     * @brief Appends the argument to the resetValue string for this reset.
     *
     * Appends @p math to the existing resetValue string for this reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void appendResetValue(const std::string &math);

    /**
     * @brief Get the resetValue string for this reset.
     *
     * Returns a math string if one has been appended for this reset. Returns
     * an empty string if math has not been appended (or has been removed).
     *
     * @return @c std::string resetValue for this reset.
     */
    std::string resetValue() const;

    /**
     * @brief Set the resetValue math string for this reset.
     *
     * Sets the math string for this reset. If @p math is an empty
     * string, resetValue will be removed from the reset.
     *
     * @param math The @c std::string to append for this reset.
     */
    void setResetValue(const std::string &math);

private:
    void swap(Reset &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ResetImpl; /**< Forward declaration for pImpl idiom. */
    ResetImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
