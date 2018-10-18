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
#include <unordered_map>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/logger.h"
#include "libcellml/model.h"
#include "libcellml/operatorLibrary.h"
#include "libcellml/variable.h"
#include "../xmldoc.h"
#include "../xmlnode.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

struct LIBCELLML_EXPORT CodeNotGenerated : public std::exception
{
	const char * what () const throw ();
};

struct LIBCELLML_EXPORT UnknownNode : public std::exception
{
    const char * what () const throw ();
};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class CXX
{
public:
    enum class types {void_t, double_t, double_ct, double_pt, double_rt};
    static const std::unordered_map<types, std::string, EnumClassHash> returnTypes;
    static const std::unordered_map<types, std::string, EnumClassHash> argTypes;

    static std::string returnType(types t) {return returnTypes.at(t);}
    static std::string argType(types t) {return argTypes.at(t);}
    static std::string argListOp() {return "(";}
    static std::string argListCl() {return ")";}
    static std::string funBodyOp() {return "{";}
    static std::string funBodyCl() {return "}";}
    static std::string instructionDelimiter() {return ";";}
    static std::string dereferenceOp() {return "*";}
};

class LIBCELLML_EXPORT Generator : public Logger
{
public:
    template <typename L = CXX>
        std::string generateCode(ModelPtr m);
    void writeCodeToFile(std::string filename);

private:
    void findVOI(std::string math);
    void findVOIHelper(XmlNodePtr node);
    void findInitialValues(ComponentPtr c);
    std::shared_ptr<libcellml::operators::Representable> parseMathML(std::string math);
    std::shared_ptr<libcellml::operators::Representable> parseNode(XmlNodePtr node);
    template <typename L = CXX>
        std::string generateInitConsts();
    template <typename L = CXX>
        std::string generateComputeRates(
                std::shared_ptr<libcellml::operators::Representable> r);
    template <typename L = CXX>
        std::string generateComputeVariables();
    template <typename L = CXX>
        std::string generateStateAliases();
    template <typename L = CXX>
        std::string generateVoiAlias();

    std::string voi;
    std::vector<std::string> states;
    std::unordered_map<std::string,double> initialValues;
    std::string code = "";
};

}
