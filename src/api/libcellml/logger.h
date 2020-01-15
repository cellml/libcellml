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
#include "libcellml/issue.h"
#include "libcellml/types.h"

#include <string>

namespace libcellml {

/**
 * @brief The Logger class.
 *
 * Base class for all serialisable libCellML classes.
 */
class LIBCELLML_EXPORT Logger
{
public:
    virtual ~Logger(); /**< Destructor */
    Logger(const Logger &rhs) = delete; /**< Copy constructor */
    Logger(Logger &&rhs) noexcept = delete; /**< Move constructor */
    Logger &operator=(Logger rhs) = delete; /**< Assignment operator */

    /**
     * @brief Clear the issues from the logger.
     *
     * Clear the issues from the logger.
     */
    void removeAllErrors();

    /**
     * @brief Add an issue to the logger.
     *
     * Adds the argument @p issue to this logger.
     *
     * @param issue The @c IssuePtr to add.
     */
    void addIssue(const IssuePtr &issue);

    /**
     * @brief Get the number of issues.
     *
     * Return the number of issues currently stored in the logger.
     *
     * @return The number of issues.
     */
    size_t issueCount() const;

    /**
     * @brief Get issue at the specified @p index.
     *
     * Returns an issue at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, \#issues).
     *
     * @param index The index of the issue to return.
     *
     * @return A reference to the issue at the given index on success, @c nullptr otherwise.
     */
    IssuePtr issue(size_t index) const;

protected:
    Logger(); /**< Constructor */

private:
    struct LoggerImpl; /**< Forward declaration for pImpl idiom. */
    LoggerImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
