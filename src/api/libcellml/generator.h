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
#include "libcellml/model.h"
#include "libcellml/variable.h"
#include "../xmldoc.h"
#include "../xmlnode.h"

class Representable;
class BinaryOperator;
class ArithmeticOperator;
class Addition;
class Subtraction;
class Multiplication;
class Division;
class Power;
class UnaryOperator;
class STDOperator;
class AbsoluteValue;
class Sine;
class Cosine;
class Variable;
class Constant;

//! Everything in libCellML is in this namespace.
namespace libcellml {

class LIBCELLML_EXPORT Generator
{
public:
    std::string generateCode(ModelPtr m);
    void writeCodeToFile(std::string filename);

private:
    void findVOI(std::string math);
    void findVOIHelper(XmlNodePtr node);
    void findInitialValues(ComponentPtr c);
    std::shared_ptr<Representable> parseMathML(std::string math);
    std::shared_ptr<Representable> parseNode(XmlNodePtr node);
    std::string generateInitConsts();
    std::string generateComputeRates(std::shared_ptr<Representable> r);
    std::string generateComputeVariables();
    std::string generateStateAliases();
    std::string generateVoiAlias();

    std::string voi;
    std::vector<std::string> states;
    std::unordered_map<std::string,double> initialValues;
    std::string code = "";
};

}
