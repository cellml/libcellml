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

#include "libcellml/exportdefinitions.h"
#include "libcellml/namedentity.h"

namespace libcellml {

/**
 * @brief The ImportSource class.
 *
 * The import source class is for encapsulating an external CellML Model.
 */
class LIBCELLML_EXPORT ImportSource: public Entity
{
public:
    ImportSource(); /**< Constructor */
    ~ImportSource(); /**< Destructor */
    ImportSource(const ImportSource &rhs); /**< Copy constructor */
    ImportSource(ImportSource &&rhs); /**< Move constructor */
    ImportSource& operator=(ImportSource m); /**< Assignment operator */

    /**
     * @brief Set the source Model.
     *
     * Set the source Model that this import source refers to.
     *
     * @param reference The reference model.
     */
    void setSource(const std::string &reference);

    /**
     * @brief Get the source model.
     *
     * Get the source model set in this instance.  If no source model
     * is set then return an empty string.
     *
     * @return The reference to the source model if set otherwise the emtpy string.
     */
    std::string getSource() const;

private:
    void swap(ImportSource &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ImportSourceImpl; /**< Forward declaration for pImpl idiom. */
    ImportSourceImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
