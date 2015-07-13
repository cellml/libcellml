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

#ifndef LIBCELLML_LIBCELLML_ENTITY_H_
#define LIBCELLML_LIBCELLML_ENTITY_H_

#include "libcellml/enumerations.h"

namespace libcellml {

/**
 * @brief The Entity class.
 * Base class for all serialisable libCellML classes.
 */
class Entity
{
public:
    /**
     * @brief Serialise entity to std::string.
     * @param format The format to serialise the object to.
     * @return std::string representation of the object.
     */
    std::string serialise(libcellml::CELLML_FORMATS format) const
    {
        return doSerialisation(format);
    }

private:
    /**
     * @brief Pure virtual serialise method to be implemented by derived classes.
     * Pure virtual serialise method for serialising a CellML object to a std::string.
     * @param format The format to serialise the object to.
     * @return std::string representation of the object.
     */
    virtual std::string doSerialisation(libcellml::CELLML_FORMATS format) const = 0;

};

}

#endif /* LIBCELLML_LIBCELLML_ENTITY_H_ */


