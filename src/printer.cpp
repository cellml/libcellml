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

#include "libcellml/printer.h"

#include "libcellml/enumerations.h"

namespace libcellml {

/**
 * @brief The Printer::PrinterImpl struct.
 *
 * The private implementation for the Printer class.
 */
struct Printer::PrinterImpl
{
    Format mFormat;
};

Printer::Printer(Format format)
    : mPimpl(new PrinterImpl())
{
    mPimpl->mFormat = format;
}

Printer::~Printer()
{
    delete mPimpl;
}

Printer::Printer(const Printer& rhs)
    : Logger(rhs)
    , mPimpl(new PrinterImpl())
{
    mPimpl->mFormat = rhs.mPimpl->mFormat;
}

Printer::Printer(Printer &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Printer& Printer::operator=(Printer p)
{
    Logger::operator =(p);
    p.swap(*this);
    return *this;
}

void Printer::swap(Printer &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string Printer::printModel(ModelPtr /* model */)
{
    std::string output = "";
    return output;
}

}
