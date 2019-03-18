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
#include "libcellml/entity.h"
#include "libcellml/orderedentity.h"
#include "libcellml/types.h"

#include <string>

namespace libcellml {

/**
 * @brief The When class.
 * Class for determining when a reset will occur.
 */
class LIBCELLML_EXPORT When: public OrderedEntity
{
public:
    When(); /**< Constructor */
    ~When() override; /**< Destructor */
    When(const When &rhs); /**< Copy constructor */
    When(When &&rhs); /**< Move constructor */
    When& operator=(When rhs); /**< Assignment operator */

    /**
     * @brief Set the condition term for this when.
     *
     * Set the @c std::string MathML string as the condition term for this when.
     *
     * @param condition The @c std::string MathML string of the condition to set.
     */
    void setCondition(const std::string &condition);

    /**
     * @brief Get the condition term for this when.
     *
     * Get the @c std::string MathML string as the condition term for this when.
     *
     * @return The @c std::string MathML string of the condition.
     */
    std::string getCondition() const;

    /**
     * @brief Set the value term for this when.
     *
     * Set the @c std::string MathML string as the value term for this when.
     *
     * @param value The @c std::string MathML string of the value to set.
     */
    void setValue(const std::string &value);

    /**
     * @brief Get the MathML value term for this when.
     *
     * Get the @c std::string MathML string that represents the value for
     * this when.
     *
     * @return The @c std::string MathML string of the value.
     */
    std::string getValue() const;

private:
    void swap(When &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct WhenImpl; /**< Forward declaration for pImpl idiom. */
    WhenImpl *mPimpl; /**< Private member to implementation pointer */
};

}
