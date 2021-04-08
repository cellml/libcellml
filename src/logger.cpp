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

#include "libcellml/logger.h"

#include <algorithm>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Logger::LoggerImpl struct.
 *
 * This struct is the private implementation struct for the LoggerImpl class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Logger::LoggerImpl
{
    std::vector<size_t> mErrors;
    std::vector<size_t> mWarnings;
    std::vector<size_t> mMessages;
    std::vector<IssuePtr> mIssues;
};

Logger::Logger()
    : mPimpl(new LoggerImpl())
{
}

Logger::~Logger()
{
    delete mPimpl;
}

size_t Logger::errorCount() const
{
    return mPimpl->mErrors.size();
}

IssuePtr Logger::error(size_t index) const
{
    IssuePtr issue = nullptr;
    if (index < mPimpl->mErrors.size()) {
        issue = mPimpl->mIssues.at(mPimpl->mErrors.at(index));
    }
    return issue;
}

size_t Logger::warningCount() const
{
    return mPimpl->mWarnings.size();
}

IssuePtr Logger::warning(size_t index) const
{
    IssuePtr issue = nullptr;
    if (index < mPimpl->mWarnings.size()) {
        issue = mPimpl->mIssues.at(mPimpl->mWarnings.at(index));
    }
    return issue;
}

size_t Logger::messageCount() const
{
    return mPimpl->mMessages.size();
}

IssuePtr Logger::message(size_t index) const
{
    IssuePtr issue = nullptr;
    if (index < mPimpl->mMessages.size()) {
        issue = mPimpl->mIssues.at(mPimpl->mMessages.at(index));
    }
    return issue;
}

void Logger::removeAllIssues()
{
    mPimpl->mIssues.clear();
    mPimpl->mErrors.clear();
    mPimpl->mWarnings.clear();
    mPimpl->mMessages.clear();
}

void Logger::addIssue(const IssuePtr &issue)
{
    // When an issue is added, update the appropriate array based on its level.
    size_t index = mPimpl->mIssues.size();
    mPimpl->mIssues.push_back(issue);
    libcellml::Issue::Level level = issue->level();
    switch (level) {
    case libcellml::Issue::Level::ERROR:
        mPimpl->mErrors.push_back(index);
        break;
    case libcellml::Issue::Level::WARNING:
        mPimpl->mWarnings.push_back(index);
        break;
    case libcellml::Issue::Level::MESSAGE:
        mPimpl->mMessages.push_back(index);
        break;
    }
}

void Logger::addIssues(const std::vector<IssuePtr> &issues)
{
    for (auto &issue : issues) {
        addIssue(issue);
    }
}

size_t Logger::issueCount() const
{
    return mPimpl->mIssues.size();
}

IssuePtr Logger::issue(size_t index) const
{
    IssuePtr issue = nullptr;
    if (index < mPimpl->mIssues.size()) {
        issue = mPimpl->mIssues.at(index);
    }
    return issue;
}

} // namespace libcellml
