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

namespace libcellml {

static const std::map<CellMLElement, std::string> cellMLElementToString = {
    {CellMLElement::COMPONENT, "component"},
    {CellMLElement::COMPONENT_REF, "component_ref"},
    {CellMLElement::CONNECTION, "connection"},
    {CellMLElement::ENCAPSULATION, "encapsulation"},
    {CellMLElement::IMPORT, "import"},
    {CellMLElement::MAP_VARIABLES, "map_variables"},
    {CellMLElement::MODEL, "model"},
    {CellMLElement::RESET, "reset"},
    {CellMLElement::RESET_VALUE, "reset_value"},
    {CellMLElement::TEST_VALUE, "test_value"},
    {CellMLElement::UNDEFINED, "undefined"},
    {CellMLElement::UNIT, "unit"},
    {CellMLElement::UNITS, "units"},
    {CellMLElement::VARIABLE, "variable"}};

std::string cellMLElementAsString(CellMLElement value)
{
    return cellMLElementToString.at(value);
}

} // namespace libcellml
