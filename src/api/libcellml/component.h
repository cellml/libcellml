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

#ifndef LIBCELLML_LIBCELLML_COMPONENT_H
#define LIBCELLML_LIBCELLML_COMPONENT_H

#include "libcellml/libcellml_export.h"
#include "libcellml/componententity.h"

namespace libcellml {

/**
 * @brief The Component class.
 * The Component class is for representing a CellML Component.
 */
class LIBCELLML_EXPORT Component: public ComponentEntity
{
public:
    Component(); /**< Constructor */
    ~Component(); /**< Destructor */
    Component(const Component &rhs); /**< Copy constructor */
    Component(Component &&rhs); /**< Move constructor */
    Component& operator=(Component m); /**< Assignment operator */

//    void addComponent(const ComponentPtr &c);

    /**
     * @brief Set the source component for this component.
     * Make this component an imported component by defining an import model
     * from which to extract the named component from.
     * @param imp The import from which the named component originates.
     * @param name The name of the component in the imported model to use.
     */
    void setSourceComponent(const ImportPtr &imp, const std::string &name);
private:
    void doAddComponent(const ComponentPtr &c);

};

}

#endif // LIBCELLML_LIBCELLML_COMPONENT_H

