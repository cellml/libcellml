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

#include "utilities.h"

#include <stdexcept>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include <set>

namespace libcellml {

bool convertToDouble(const std::string &candidate, double *value)
{
    bool canConvert = false;
    // Try to convert the candidate string to double.
    try
    {
        double tmp = std::stod(candidate);
        if (value) {
            *value = tmp;
        }
        canConvert = true;
    } catch (...) {
        canConvert = false;
    }

    return canConvert;
}

bool hasNonWhitespaceCharacters(const std::string &input)
{
    return input.find_first_not_of(" \t\n\v\f\r") != input.npos;
}

std::string convertDoubleToString(double value)
{
    std::ostringstream strs;
    strs << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return strs.str();
}

int convertToInt(const std::string &candidate)
{
    return std::stoi(candidate);
}

std::string convertIntToString(int value)
{
    std::ostringstream strs;
    strs << value;
    return strs.str();
}

bool isEuropeanNumericCharacter(char c) {
    const std::set<char> validIntegerCharacters = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    return validIntegerCharacters.find(c) != validIntegerCharacters.end();
}

bool isNonNegativeCellMLInteger(const std::string &candidate)
{
    if (candidate.length() == 0) {
        return false;
    }
    return std::all_of(candidate.begin(), candidate.end(), isEuropeanNumericCharacter);
}

bool isCellMLInteger(const std::string &candidate)
{
    if (candidate.length() > 0 && *candidate.begin() == '-') {
        return isNonNegativeCellMLInteger(candidate.substr(1));
    }
    return isNonNegativeCellMLInteger(candidate);
}

}
