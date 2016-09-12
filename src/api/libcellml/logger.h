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

#include "libcellml/error.h"
#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Logger class.
 *
 * Base class for all serialisable libCellML classes.
 */
class LIBCELLML_EXPORT Logger
{
public:
    Logger(); /**< Constructor */
    ~Logger(); /**< Destructor */
    Logger(const Logger &rhs); /**< Copy constructor */
    Logger(Logger &&rhs); /**< Move constructor */
    Logger& operator=(Logger rhs); /**< Assignment operator */

    /**
     * @brief Clear the errors from the logger.
     *
     * Clear the errors from the logger.
     */
    void clearErrors();

    /**
     * @brief Add an error to the logger.
     *
     * Adds the argument @p error to this logger.
     *
     * @param error The @c ErrorPtr to add.
     */
    void addError(const ErrorPtr error);

    /**
     * @brief Get the number of errors.
     *
     * Return the number of errors currently stored in the logger.
     *
     * @return The number of errors.
     */
    size_t errorCount() const;

    /**
     * @brief Get error at the specified @p index.
     *
     * Returns an error at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, #errors).
     *
     * @param index The index of the error to return.
     *
     * @return A reference to the error at the given index on success, @c nullptr otherwise.
     */
    ErrorPtr getError(size_t index) const;

private:
    void swap(Logger &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct LoggerImpl; /**< Forward declaration for pImpl idiom. */
    LoggerImpl *mPimpl; /**< Private member to implementation pointer */
};

}
