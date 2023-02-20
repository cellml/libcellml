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

#include "libcellml/enums.h"

#include <map>

#include "libcellml/analysermodel.h"
#include "libcellml/generatorprofile.h"

namespace libcellml {

static const std::map<CellmlElementType, std::string> cellmlElementTypeToString = {
    {CellmlElementType::COMPONENT, "component"},
    {CellmlElementType::COMPONENT_REF, "component_ref"},
    {CellmlElementType::CONNECTION, "connection"},
    {CellmlElementType::ENCAPSULATION, "encapsulation"},
    {CellmlElementType::IMPORT, "import"},
    {CellmlElementType::MATH, "math"},
    {CellmlElementType::MAP_VARIABLES, "map_variables"},
    {CellmlElementType::MODEL, "model"},
    {CellmlElementType::RESET, "reset"},
    {CellmlElementType::RESET_VALUE, "reset_value"},
    {CellmlElementType::TEST_VALUE, "test_value"},
    {CellmlElementType::UNDEFINED, "undefined"},
    {CellmlElementType::UNIT, "unit"},
    {CellmlElementType::UNITS, "units"},
    {CellmlElementType::VARIABLE, "variable"}};

static const std::map<AnalyserModel::Type, std::string> analyserModelTypeStringMap = {
    {AnalyserModel::Type::ALGEBRAIC, "Algebriac"},
    {AnalyserModel::Type::INVALID, "Invalid"},
    {AnalyserModel::Type::ODE, "ODE"},
    {AnalyserModel::Type::OVERCONSTRAINED, "Overconstrained"},
    {AnalyserModel::Type::UNDERCONSTRAINED, "Underconstrained"},
    {AnalyserModel::Type::UNKNOWN, "Unknown"},
    {AnalyserModel::Type::UNSUITABLY_CONSTRAINED, "Unsuitable constrained"},
};

static const std::map<GeneratorProfile::Profile, std::string> generatorProfileProfileStringMap = {
    {GeneratorProfile::Profile::C, "C"},
    {GeneratorProfile::Profile::PYTHON, "Python"},
};

std::string enumerationAsString(CellmlElementType value)
{
    return cellmlElementTypeToString.at(value);
}

std::string enumerationAsString(AnalyserModel::Type value)
{
    return analyserModelTypeStringMap.at(value);
}

std::string enumerationAsString(GeneratorProfile::Profile value)
{
    return generatorProfileProfileStringMap.at(value);
}

} // namespace libcellml
