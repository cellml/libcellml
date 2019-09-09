/*
Copyright 2016 University of Auckland

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

#include "libcellml/component.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

#include <algorithm>
#include <iostream>
#include <vector>

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
    std::vector<IssuePtr> mIssues;
    std::vector<std::vector<size_t>> mTypeIndex {{}, {}, {}}; // TODO Don't like this ... want cleaner way to get length of Type enum
    // std::vector<int> mIndex;
};

Logger::Logger()
    : mPimpl(new LoggerImpl())
{
}

Logger::~Logger()
{
    delete mPimpl;
}

Logger::Logger(const Logger &rhs)
    : mPimpl(new LoggerImpl())
{
    mPimpl->mIssues = rhs.mPimpl->mIssues;
    mPimpl->mTypeIndex = rhs.mPimpl->mTypeIndex;
}

Logger::Logger(Logger &&rhs) noexcept
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Logger &Logger::operator=(Logger rhs)
{
    rhs.swap(*this);
    return *this;
}

void Logger::swap(Logger &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

void Logger::clearIssues()
{
    // TODO What's the rationale of using .clear() instead of swapping with empty vector here?
    mPimpl->mIssues.clear();
    // mPimpl->mIndex.clear();
    mPimpl->mTypeIndex.at(static_cast<size_t>(libcellml::Issue::Type::ERROR)).clear();
    mPimpl->mTypeIndex.at(static_cast<size_t>(libcellml::Issue::Type::WARNING)).clear();
    mPimpl->mTypeIndex.at(static_cast<size_t>(libcellml::Issue::Type::HINT)).clear();
}

void Logger::addIssue(const IssuePtr &issue)
{
    mPimpl->mIssues.push_back(issue);
    auto typeIndex = static_cast<size_t>(issue->type());

    // mPimpl->mIndex.push_back(mPimpl->mTypeIndex.at(typeIndex).size());

    mPimpl->mTypeIndex.at(typeIndex).push_back(mPimpl->mIssues.size() - size_t(1));
}

size_t Logger::issueCount() const
{
    return mPimpl->mIssues.size();
}

size_t Logger::issueCount(Issue::Type type) const
{
    return mPimpl->mTypeIndex.at(static_cast<size_t>(type)).size();
}

size_t Logger::issueCount(std::vector<Issue::Type> &types) const
{
    size_t num = 0;
    for (auto t : types) {
        num += mPimpl->mTypeIndex.at(static_cast<size_t>(t)).size();
    }
    return num;
}

IssuePtr Logger::issue(size_t index) const
{
    IssuePtr err = nullptr;
    if (index < mPimpl->mIssues.size()) {
        err = mPimpl->mIssues.at(index);
    }
    return err;
}

IssuePtr Logger::issue(Issue::Type type, size_t index) const
{
    IssuePtr err = nullptr;
    if (index < mPimpl->mTypeIndex.at(static_cast<size_t>(type)).size()) {
        size_t i = mPimpl->mTypeIndex.at(static_cast<size_t>(type)).at(index);
        err = mPimpl->mIssues.at(i);
    }
    return err;
}

IssuePtr Logger::issue(std::vector<Issue::Type> &types, size_t index) const
{
    // TODO This seems like a super inefficient way to do it ... a lot of manipulation to retrieve one item :(
    IssuePtr err = nullptr;
    if (index < issueCount(types)) {
        std::vector<int> get_issues(mPimpl->mIssues.size(), -1);
        for (auto type : types) {
            auto t = static_cast<size_t>(type);
            for (auto const &i : mPimpl->mTypeIndex.at(t)) {
                get_issues.at(i) = static_cast<int>(i);
            }
        }

        get_issues.erase(std::remove(get_issues.begin(), get_issues.end(), -1), get_issues.end());
        err = mPimpl->mIssues.at(static_cast<size_t>(get_issues.at(index)));
    }
    return err;
}

} // namespace libcellml
