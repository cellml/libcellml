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

#ifdef ENABLE_HANDY_DEBUGGING_FUNCTIONS

#include "debug.h"

namespace libcellml {

void printStack(const IndexStack &stack)
{
    Debug(false) << "[";
    for (auto iter = stack.begin(); iter < stack.end(); ++iter) {
        Debug(false) << *iter;
        if (iter + 1 < stack.end()) {
            Debug(false) << ", ";
        }
    }
    Debug() << "]";
}

void printEquivalenceMap(const EquivalenceMap &map)
{
    Debug() << "Print out of equivalence map";
    for (EquivalenceMap::const_iterator iter = map.begin(); iter != map.end(); ++iter) {
        auto key = iter->first;
        Debug(false) << "key: ";
        printStack(key);
        auto vector = iter->second;
        for (auto vectorIt = vector.begin(); vectorIt < vector.end(); ++vectorIt) {
            Debug(false) << "value: ";
            printStack(*vectorIt);
        }
    }
}

} // namespace libcellml

#endif /* ENABLE_HANDY_DEBUGGING_FUNCTIONS */
