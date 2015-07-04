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
#include <memory>

#include "libcellml/libcellml_export.h"
#include "libcellml/nameable.h"
#include "libcellml/component.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Model class.
 * The Model class is for representing a CellML Model.
 */
class LIBCELLML_EXPORT Model: public Nameable
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

    Model(Model&& rhs); /**< move constructor */
    Model& operator=(Model&& rhs); /**< move assignment */
    Model(const Model&);/**< copy constructor */
    Model& operator=(const Model&);/**< assignment */

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
     * @brief add a component to the model.
     * Adds a copy of the given component to the model.
     * @param c the component to add.
     */
    void addComponent(const Component &c);

    /**
     * @brief get the number of components in the model.
     * Returns the number of components the model directly contains.
     * @return the number of components.
     */
    int componentCount() const;

private:

    struct ModelImpl; /**< Forward declaration for pImpl idiom. */
    ModelImpl *mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_MODEL_H_ */

