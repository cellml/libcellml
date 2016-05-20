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
limitations under the License.
*/

#ifndef LIBCELLML_LIBCELLML_MODEL_H_
#define LIBCELLML_LIBCELLML_MODEL_H_

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/component.h"
#include "libcellml/componententity.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Model class.
 * The Model class is for representing a CellML Model.
 */
class LIBCELLML_EXPORT Model: public ComponentEntity
{
public:
    Model(); /**< Constructor */
    ~Model(); /**< Destructor */
    Model(const Model &rhs); /**< Copy constructor */
    Model(Model &&rhs); /**< Move constructor */
    Model& operator=(Model m); /**< Assignment operator */

private:
    void doAddComponent(const ComponentPtr &c);
    std::string doSerialisation(Format format) const;
};

}

#endif /* LIBCELLML_LIBCELLML_MODEL_H_ */

