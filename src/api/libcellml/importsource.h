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
#include "libcellml/entity.h"

#ifndef SWIG
template class LIBCELLML_EXPORT std::weak_ptr<libcellml::ImportSource>;
#endif

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
#ifndef SWIG
    ,
                                     public std::enable_shared_from_this<ImportSource>
#endif
{
public:
    ~ImportSource() override; /**< Destructor. */
    ImportSource(const ImportSource &rhs) = delete; /**< Copy constructor. */
    ImportSource(ImportSource &&rhs) noexcept = delete; /**< Move constructor. */
    ImportSource &operator=(ImportSource rhs) = delete; /**< Assignment operator. */

    /**
     * @brief Create a @c ImportSource object.
     *
     * Factory method to create an @c ImportSource.  Create an
     * import source with::
     *
     *   ImportSourcePtr importSource = libcellml::ImportSource::create();
     *
     * @return A smart pointer to an @c ImportSource object.
     */
    static ImportSourcePtr create() noexcept;

    /**
     * @brief Get the source @c Model's URL.
     *
     * Get the source @c Model's URL set in this instance. If no source @c Model
     * URL is set then return an empty string.
     *
     * @return The URL of the source @c Model if set otherwise the emtpy string.
     */
    std::string url() const;

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
    ModelPtr model() const;

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
     * @brief Remove the model from this import source.
     *
     * Remove the reference to a model from this import source.
     */
    void removeModel();

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

    /**
     * @brief Create a clone of this import source.
     *
     * Creates a full separate copy of this import source without copying
     * the parent.
     *
     * @return a new @c ImportSourcePtr to the cloned import source.
     */
    ImportSourcePtr clone() const;

protected:
    bool doEquals(const EntityPtr &other) const override; /**< Virtual implementation method for equals, @private. */

private:
    ImportSource(); /**< Constructor, @private. */

    struct ImportSourceImpl; /**< Forward declaration for pImpl idiom, @private. */
    ImportSourceImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
