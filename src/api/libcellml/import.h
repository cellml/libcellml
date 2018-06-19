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
 * @brief The Import class.
 *
 * The import class is for encapsulating an external CellML Model.
 */
class LIBCELLML_EXPORT Import: public Entity
{
public:
    Import(); /**< Constructor */
    ~Import(); /**< Destructor */
    Import(const Import &rhs); /**< Copy constructor */
    Import(Import &&rhs); /**< Move constructor */
    Import& operator=(Import m); /**< Assignment operator */

    /**
     * @brief Set the source Model's URL.
     *
     * Set the source Model's URL that this import refers to.
     *
     * @param reference The referenced model's URL.
     */
    void setSource(const std::string &reference);

    /**
     * @brief Get the source model's URL.
     *
     * Get the source model's URL set in this instance. If no source model
     * URL is set then return an empty string.
     *
     * @return The reference to the source model if set otherwise the emtpy string.
     */
    std::string getSource() const;

    /**
     * @brief Provide the model used to resolve this import.
     *
     * Uses the provided model to resolve this import, which should correspond
     * to the @c source identified by this import.
     *
     * @param model The model to use in resolving this import.
     */
    void resolveImport(libcellml::ModelPtr model);

    /**
     * @brief Get the resolving model.
     *
     * Get the model which has been assigned to resolve this import. If no model
     * has been assigned then return the @c nullptr.
     *
     * @return The model used to resolve this import.
     */
    libcellml::ModelPtr getResolvingModel() const;

    /**
     * @brief Test is this import is resolved.
     *
     * Method to test if this import has been resolved, i.e., the source model has
     * been assigned. Returns @c true if the import is resolved otherwise returns
     * @c false.
     *
     * @return @c true if the import has been resolved, @c false otherwise.
     */
    bool isResolved() const;

private:
    void swap(Import &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ImportImpl; /**< Forward declaration for pImpl idiom. */
    ImportImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
