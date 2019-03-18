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
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <vector>

namespace libcellml {

double convertToDouble(const std::string &candidate)
{
    double value = 0.0;
    try {
        value = std::stod(candidate);
    } catch (...) {
        value = std::numeric_limits<double>::infinity();
    }
    return value;
}

bool hasNonWhitespaceCharacters(const std::string &input)
{
    return input.find_first_not_of(" \t\n\v\f\r") != std::string::npos;
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

bool isCellMLExponent(const std::string &candidate)
{
    if (candidate.length() > 0 && *candidate.begin() == '+') {
        return isCellMLInteger(candidate.substr(1));
    }
    return isCellMLInteger(candidate);
}

std::vector<size_t> findOccurences(const std::string &candidate, const std::string &sub)
{
    std::vector<size_t> occurences;
    size_t pos = candidate.find(sub, 0);
    while(pos != std::string::npos) {
        occurences.push_back(pos);
        pos = candidate.find(sub, pos+1);
    }
    return occurences;
}

bool isCellMLBasicReal(const std::string &candidate)
{
    if (candidate.length() > 0) {
        std::vector<size_t> decimalOccurences = findOccurences(candidate, ".");
        if (decimalOccurences.size() < 2) {
            bool beginsMinus = *candidate.begin() == '-';
            std::string numbersOnlyCandidate = candidate;
            if (decimalOccurences.size() == 1) {
                numbersOnlyCandidate.erase(decimalOccurences.at(0), 1);
            }
            if (beginsMinus) {
                numbersOnlyCandidate.erase(0, 1);
            }
            return std::all_of(numbersOnlyCandidate.begin(), numbersOnlyCandidate.end(), isEuropeanNumericCharacter);
        }
    }
    return false;
}

bool isCellMLReal(const std::string &candidate)
{
    bool isReal = false;
    if (candidate.length() > 0) {
        std::string normalisedCandidate = candidate;
        std::vector<size_t> eOccurences = findOccurences(candidate, "E");
        for (auto ePos : eOccurences) {
             normalisedCandidate.replace(ePos, 1, "e");
        }
        std::vector<size_t> lowerEOccurences = findOccurences(normalisedCandidate, "e");
        size_t eIndicatorCount = lowerEOccurences.size();
        if (eIndicatorCount < 2) {
            if (eIndicatorCount == 1) {
                size_t ePos = lowerEOccurences.at(0);
                std::string significand = normalisedCandidate.substr(0, ePos);
                std::string exponent = normalisedCandidate.substr(ePos+1, std::string::npos);
                if (isCellMLBasicReal(significand) && isCellMLExponent(exponent)) {
                    isReal = true;
                }
            } else {
                isReal = isCellMLBasicReal(normalisedCandidate);
            }
        }
    }
    return isReal;
}

}
