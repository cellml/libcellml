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

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/logger.h"
#include "libcellml/model.h"
#include "libcellml/operatorlibrary.h"
#include "libcellml/variable.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4275)
#endif
struct LIBCELLML_EXPORT CodeNotGenerated : public std::exception
{
	const char * what () const throw ();
};
#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4275)
#endif
struct LIBCELLML_EXPORT UnknownNode : public std::exception
{
    const char * what () const throw ();
};
#ifdef _MSC_VER
    #pragma warning(pop)
#endif

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class LIBCELLML_EXPORT Generator : public Logger
{
public:
    Generator();
    virtual ~Generator();

    std::string generateCode(ModelPtr m);
    void writeCodeToFile(std::string filename);

private:
    struct GeneratorImpl;
    GeneratorImpl* mPimpl;
};

}
