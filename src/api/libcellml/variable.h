/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#ifndef LIBCELLML_LIBCELLML_VARIABLE_H
#define LIBCELLML_LIBCELLML_VARIABLE_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/namedentity.h"

namespace libcellml {

/**
 * @brief The Units class.
 * Class for Units.
 */
class LIBCELLML_EXPORT Variable: public NamedEntity
{
public:
    Variable(); /**< Constructor */
    ~Variable(); /**< Destructor */
    Variable(const Variable &rhs); /**< Copy constructor */
    Variable(Variable &&rhs); /**< Move constructor */
    Variable& operator=(Variable n); /**< Assignment operator */

private:
    void swap(Variable &rhs); /**< Swap method required for C++ 11 move semantics. */

    std::string doSerialisation(libcellml::FORMATS format) const;

    struct VariableImpl; /**< Forward declaration for pImpl idiom. */
    VariableImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_VARIABLE_H */
