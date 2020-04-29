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
#include "debug.h"

namespace libcellml {

void printStack(const IndexStack &stack)
{
    bool first = true;
    Debug(false) << "[";
    for (const auto &iter : stack) {
        if (!first) {
            Debug(false) << ", ";
        }
        Debug(false) << iter;
        first = false;
    }
    Debug() << "]";
}

void printEquivalenceMap(const EquivalenceMap &map)
{
    Debug() << "Print out of equivalence map";
    for (const auto &iter : map) {
        auto key = iter.first;
        Debug(false) << "key: ";
        printStack(key);
        auto vector = iter.second;
        for (const auto &vectorIt : vector) {
            Debug(false) << "value: ";
            printStack(vectorIt);
        }
    }
}

void printStringStringMap(const StringStringMap &map)
{
    Debug() << "Print out of string -> string map";
    for (const auto &iter : map) {
        Debug() << iter.first << ": " << iter.second;
    }
}

} // namespace libcellml
