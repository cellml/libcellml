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

#include <algorithm>
#include <iomanip>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>

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

bool isCellMLIntegerCharacter(char c) {
    const std::set<char> validIntegerCharacters = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    return validIntegerCharacters.find(c) != validIntegerCharacters.end();
}

bool convertToInt(const std::string &candidate, int *value)
{
    bool conversionSuccessful = false;
    // Try to convert the candidate string to int.
    try
    {
        int startIndex = 0;
        if (candidate.length() > 0 &&
                *candidate.begin() == '-') {
            startIndex = 1;
        }
        if (std::all_of(candidate.begin() + startIndex, candidate.end(), isCellMLIntegerCharacter)) {
            int tmp = std::stoi(candidate);
            if (value) {
                *value = tmp;
                conversionSuccessful = true;
            }
        }
    } catch (...) {
        conversionSuccessful = false;
    }

    return conversionSuccessful;
}

std::string convertIntToString(int value)
{
    std::ostringstream strs;
    strs << value;
    return strs.str();
}

}
