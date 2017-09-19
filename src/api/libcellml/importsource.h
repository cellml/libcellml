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
 * The import source class is for defining a location at which a CellML model
 * is expected to be obtainable (the `source`). The import source also acts as
 * a handle to indicate that imported entities originate from the same instance of
 * that imported source.
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
     * @brief Set the imported model source.
     *
     * Set the imported model source that this import source refers to.
     *
     * @param source The source of the model as a @c std::string.
     */
    void setSource(const std::string &source);

    /**
     * @brief Get the imported model source.
     *
     * Get the imported model source set in this instance.  If no imported source
     * is set then return an empty string.
     *
     * @return The imported model source as a @c std::string, if set, otherwise the empty string.
     */
    std::string getSource() const;

private:
    void swap(ImportSource &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ImportSourceImpl; /**< Forward declaration for pImpl idiom. */
    ImportSourceImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
