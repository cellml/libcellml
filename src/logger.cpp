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

#include "libcellml/logger.h"

#include <vector>

#include "libcellml/types.h"
#include <libcellml/component.h>

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
    std::vector<EntityErrorPtr> mErrors;
};

Logger::Logger()
    : mPimpl(new LoggerImpl())
{
}

Logger::~Logger()
{
    delete mPimpl;
}

Logger::Logger(const Logger& rhs)
    : mPimpl(new LoggerImpl())
{
    mPimpl->mErrors = rhs.mPimpl->mErrors;
}

Logger::Logger(Logger &&rhs)
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Logger& Logger::operator=(Logger rhs)
{
    rhs.swap(*this);
    return *this;
}

void Logger::swap(Logger &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Logger::clearErrors()
{
    mPimpl->mErrors.clear();
}

void Logger::addError(EntityErrorPtr err)
{
    mPimpl->mErrors.push_back(err);
}

size_t Logger::errorCount() const
{
    return mPimpl->mErrors.size();
}

EntityErrorPtr Logger::getError(size_t index)
{
    return mPimpl->mErrors.at(index);
}

std::string EntityError::doSerialisation() const
{
    std::string s = "";
    return s;
}

std::string VariableError::doSerialisation() const
{
    std::string s = "Variable " + getName() + " not found in component " + mComponent->getName();
    return s;
}

}
