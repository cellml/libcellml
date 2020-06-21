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

#pragma once

#include <string>
#include <vector>

#include "libcellml/logger.h"
#include "libcellml/types.h"

namespace libcellml {

// class AnnotatorItem
// {
// private:
//     enum class Tag
//     {
//         MODEL,
//         COMPONENT,
//         VARIABLE,
//         UNITS,
//         RESET,
//         IMPORTSOURCE
//     } type;
//     struct
//     {
//         ModelPtr model;
//         ComponentPtr component;
//         VariablePtr variable;
//         UnitsPtr units;
//         ResetPtr reset;
//         ImportSourcePtr importSource;
//     };
//     AnnotatorItem &operator=(const AnnotatorItem &in)
//     {
//         if (type == Tag::MODEL && in.type == Tag::MODEL) {
//             model = in.model;
//             return *this;
//         }

//         switch (type) {
//         case Tag::MODEL:
//             model.~ModelPtr();
//             break;
//         case Tag::COMPONENT:
//             component.~ComponentPtr();
//             break;
//         case Tag::VARIABLE:
//             variable.~VariablePtr();
//             break;
//         case Tag::UNITS:
//             units.~UnitsPtr();
//             break;
//         case Tag::RESET:
//             reset.~ResetPtr();
//             break;
//         case Tag::IMPORTSOURCE:
//             importSource.~ImportSourcePtr();
//             break;
//         }

//         switch (in.type) {
//         case Tag::MODEL:
//             model = in.model;
//             break;
//         case Tag::COMPONENT:
//             component = in.component;
//             break;
//         case Tag::VARIABLE:
//             variable = in.variable;
//             break;
//         case Tag::UNITS:
//             units = in.units;
//             break;
//         case Tag::RESET:
//             reset = in.reset;
//             break;
//         case Tag::IMPORTSOURCE:
//             importSource = in.importSource;
//             break;
//         }
//         type = in.type;
//         return *this;
//     } // namespace libcellml
// };

/**
 * @brief The Annotator class.
 *
 * The Annotator class is for representing a CellML Annotator.
 */
class LIBCELLML_EXPORT Annotator: public Logger
{
public:
    ~Annotator() override; /**< Destructor */
    Annotator(const Annotator &rhs) = delete; /**< Copy constructor */
    Annotator(Annotator &&rhs) noexcept = delete; /**< Move constructor */
    Annotator &operator=(Annotator rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Annotator object.
     *
     * Factory method to create a @c Annotator.  Create a
     * annotator with::
     *
     *   AnnotatorPtr annotator = libcellml::Annotator::create();
     *
     * @return A smart pointer to a @c Annotator object.
     */
    static AnnotatorPtr create() noexcept;

    // void createAllIds(ModelPtr &model, bool includeMathMLElements);
    void build();

private:
    Annotator(); /**< Constructor */

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
