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
    Logger(); /**< Constructor */
    virtual ~Logger(); /**< Destructor */
    Logger(const Logger &rhs); /**< Copy constructor */
    Logger(Logger &&rhs) noexcept; /**< Move constructor */
    Logger &operator=(Logger rhs); /**< Assignment operator */

    // /**
    //  * @brief Add an error to the logger.
    //  *
    //  * Adds the argument @p error to this logger.
    //  *
    //  * @param error The @c IssuePtr to add.
    //  */
    // void addError(const IssuePtr &error);

    // /**
    //  * @brief Add a warning to the logger.
    //  *
    //  * Adds the argument @p warning to this logger.
    //  *
    //  * @param warning The @c IssuePtr to add.
    //  */
    // void addWarning(const IssuePtr &error);

    // /**
    //  * @brief Add an error to the logger.
    //  *
    //  * Adds the argument @p error to this logger.
    //  *
    //  * @param error The @c IssuePtr to add.
    //  */
    // void addHint(const IssuePtr &error);

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
     * Return the number of issues of any kind currently stored in the logger.
     *
     * @return The number of issues.
     */
    size_t issueCount() const;

    /**
     * @brief Get the number of issues of the specified kind
     *
     * Return the number of issues fo the specified kind currently stored in the logger.
     *
     * @return The number of issues.
     */
    size_t issueCount(Issue::Type type) const;

    /**
     * @brief Get the number of issues of the specified kind(s)
     *
     * Return the number of issues fo the specified kind(s) currently stored in the logger.
     *
     * @return The number of issues.
     */
    size_t issueCount(std::vector<Issue::Type> &types) const;

    // /**
    //  * @brief Clear the errors from the logger.
    //  *
    //  * Clear the errors from the logger.
    //  */
    // void clearErrors();

    // /**
    //  * @brief Clear the errors from the logger.
    //  *
    //  * Clear the errors from the logger.
    //  */
    // void clearWarnings();

    // /**
    //  * @brief Clear the errors from the logger.
    //  *
    //  * Clear the errors from the logger.
    //  */
    // void clearHints();

    /**
     * @brief Clear the issues from the logger.
     *
     * Clear the issues from the logger.
     */
    void clearIssues();

    /**
     * @brief Get error at the specified @p index.
     *
     * Returns an error at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, \#errors).
     *
     * @param index The index of the error to return.
     *
     * @return A reference to the error at the given index on success, @c nullptr otherwise.
     */
    IssuePtr error(size_t index) const;

    /**
     * @brief Get warning at the specified @p index.
     *
     * Returns a warning at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, \#warning).
     *
     * @param index The index of the warning to return.
     *
     * @return A reference to the warning at the given index on success, @c nullptr otherwise.
     */
    IssuePtr warning(size_t index) const;

    /**
     * @brief Get hint at the specified @p index.
     *
     * Returns a hint at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, \#hints).
     *
     * @param index The index of the hint to return.
     *
     * @return A reference to the hint at the given index on success, @c nullptr otherwise.
     */
    IssuePtr hint(size_t index) const;

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

    /**
     * @brief Get issue of the specified @p type at the specified @p index.
     *
     * Returns an issue at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, \#issues_of_type).
     *
     * @param index The index of the issue to return.
     * @type type The type of the issue to return.
     *
     * @return A reference to the issue at the given index on success, @c nullptr otherwise.
     */
    IssuePtr issue(Issue::Type type, size_t index) const;

    /**
     * @brief Get issue of the specified @p type(s) at the specified @p index.
     *
     * Returns an issue at the @p index.  If the @p index
     * is not valid a @c nullptr is returned, the valid range for the @p index
     * is [0, \#issues_of_types).
     *
     * @param index The index of the issue to return.
     * @type type The type of the issue to return.
     *
     * @return A reference to the issue at the given index on success, @c nullptr otherwise.
     */
    IssuePtr issue(std::vector<Issue::Type> &types, size_t index) const;

private:
    void swap(Logger &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct LoggerImpl; /**< Forward declaration for pImpl idiom. */
    LoggerImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
