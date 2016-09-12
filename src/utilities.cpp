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

namespace libcellml {

bool convertToDouble(const std::string &candidate, double *value)
{
    bool canConvert = false;
    // Try to convert the input string to double.
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
    return input.find_first_not_of(" \t\n\v\f\r") != input.npos;;
}

std::string convertDoubleToString(double value)
{
    std::ostringstream strs;
    strs << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return strs.str();
}

}
