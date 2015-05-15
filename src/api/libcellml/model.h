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

#ifndef LIBCELLML_LIBCELLML_MODEL_H_
#define LIBCELLML_LIBCELLML_MODEL_H_

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/entity.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Model class.
 * The Model class is for representing a CellML Model.
 */
class LIBCELLML_EXPORT Model: public Entity
{
public:
    /**
     * @brief Model Constructor.
     * Default Model constructor.
     */
    Model();
    /**
     * @brief Model Destructor.
     * Default Model destructor.
     */
    ~Model();

    /**
     * @brief serialise the Model.
     * This method serialises the Model to a std:string representation in the
     * desired format.
     * @sa deserialise
     * @param format The format to serialise the Model to.
     * @return std::string representation of the Model in the given format.
     */
    std::string serialise(libcellml::CELLML_FORMATS format) const;

    /**
     * @brief deserialise the Model.
     * Method to deserialise the Model from a std::string representation of the format
     * given by the format parameter.
     * @sa serialise
     * @param string The std::string representation of the model to deserialise.
     * @param format The format of the given string.
     */
    void deserialise(std::string string, libcellml::CELLML_FORMATS format);

private:
    struct ModelImpl; /**< Forward declaration for pImpl idiom. */
    std::shared_ptr<ModelImpl> _pimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_MODEL_H_ */

