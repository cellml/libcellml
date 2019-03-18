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
    ~ImportSource() override; /**< Destructor */
    ImportSource(const ImportSource &rhs); /**< Copy constructor */
    ImportSource(ImportSource &&rhs) noexcept; /**< Move constructor */
    ImportSource& operator=(ImportSource rhs); /**< Assignment operator */

    /**
     * @brief Get the source @c Model's URL.
     *
     * Get the source @c Model's URL set in this instance. If no source @c Model
     * URL is set then return an empty string.
     *
     * @return The URL of the source @c Model if set otherwise the emtpy string.
     */
    std::string getUrl() const;

    /**
     * @brief Set the source @c Model's URL.
     *
     * Set the source @c Model's URL that this @c ImportSource refers to.
     *
     * @param source The source @c Model's URL.
     */
    void setUrl(const std::string &url);

    /**
     * @brief Get the @c Model that resolves the import.
     *
     * Get the @c Model which has been assigned to resolve this @c ImportSource. If no @c Model
     * has been assigned then return the @c nullptr.
     *
     * @return The @c Model used to resolve this @c ImportSource.
     */
    ModelPtr getModel() const;

    /**
     * @brief Provide the @c Model used to resolve this import.
     *
     * Uses the provided @c Model to resolve this @c ImportSource, which should correspond
     * to the @c ImportSource identified by this import.
     *
     * @param model The @c Model to use in resolving this @c ImportSource.
     */
    void setModel(const ModelPtr &model);

    /**
     * @brief Test if this @c ImportSource is resolved.
     *
     * Method to test if this @c ImportSource has been resolved, i.e. the source @c Model has
     * been assigned. Returns @c true if the @c ImportSource is resolved otherwise returns
     * @c false.
     *
     * @return @c true if the @c ImportSource has been resolved, @c false otherwise.
     */
    bool hasModel() const;

private:
    void swap(ImportSource &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ImportSourceImpl; /**< Forward declaration for pImpl idiom. */
    ImportSourceImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
