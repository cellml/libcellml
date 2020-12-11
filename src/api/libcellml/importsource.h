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

#ifndef SWIG
template class LIBCELLML_EXPORT std::weak_ptr<libcellml::ImportSource>;
#endif

namespace libcellml {

class ImportSourcePrivate;

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

    /**
     * @brief Add a component to this import source item.
     *
     * The added @p component will be treated as an import, and
     * will be sourced from the combination of URL of this import source
     * item, and the component's own import reference.
     *
     * @param component The @c ComponentPtr to add.
     *
     * @return @c true if the component was added successfully, @c false
     * if it already exists in this import.
     */
    bool addComponent(const ComponentPtr &component);

    /**
     * @brief Remove the component at the given @p index.
     *
     * Remove the component from this import source at the given @p index.
     * @p index must be in the range [0, \#components).
     *
     * @param index The index of the component to remove.
     * @param setEmpty Whether or not to set the removed Component's
     *        importSource to nullptr.  True by default.
     *
     * @return True if the component was removed, false otherwise.
     */
    bool removeComponent(size_t index, bool setEmpty = true);

    /**
     * @overload
     *
     * @brief Remove the component with the given pointer.
     *
     * Remove the component with the pointer @p component.
     *
     * @param component The pointer to the component to remove.
     * @param setEmpty Whether or not to set the removed Component's
     *        importSource to nullptr.  True by default.
     *
     * @return True if the component was removed, false otherwise.
     */
    bool removeComponent(ComponentPtr &component, bool setEmpty = true);

    /**
     * @brief Remove all components from the import source.
     *
     * Note that components which are removed from the import will have their
     * import source cleared.  They thus become locally
     * concrete instances in the model, and will return @c false to the
     * function isImport().
     *
     * @return True if the components are removed, false otherwise.
     */
    bool removeAllComponents();

    /**
     * @brief Get the number of components accessed by this import source.
     *
     * @return The number of components.
     */
    size_t componentCount() const;

    /**
     * @brief Get the component item at the given @p index.
     *
     * Returns a reference to the component at the given @p index imported
     * by this import source.  If the @p index is not valid a @c nullptr is
     * returned, the range of valid values for the index is [0, \#components).
     *
     * @param index The index of the component to return.
     *
     * @return A reference to the component at the given @p index on success, @c nullptr otherwise.
     */
    ComponentPtr component(size_t index) const;

    /**
     * @brief Add a units item to this import source item.
     *
     * The added @p units will be treated as an import, and
     * will be sourced from the combination of URL of this import source
     * item, and the units' own import reference.
     *
     * The function will return @c false and no action is taken if:
     *  - The @p units pointer already exists in this import; or
     *  - The @p units is @c nullptr.
     *
     * @param units The @c UnitsPtr to add.
     *
     * @return True if the units item was added successfully, false otherwise.
     */
    bool addUnits(const UnitsPtr &units);

    /**
     * @brief Remove the units at the given @p index.
     *
     * Remove the units from this import source at the given @p index.
     * @p index must be in the range [0, \#units).
     *
     * @param index The index of the units to remove.
     * @param setEmpty Whether or not to set the removed Units'
     *        importSource to nullptr.  True by default.
     *
     * @return True if the units were removed, false otherwise.
     */
    bool removeUnits(size_t index, bool setEmpty = true);

    /**
     * @overload
     *
     * @brief Remove the units with the given pointer.
     *
     * Remove the units with the pointer @p units.
     *
     * @param units The pointer to the units to remove.
     * @param setEmpty Whether or not to set the removed Units'
     *        importSource to nullptr.  True by default.
     *
     * @return True if the units were removed, false otherwise.
     */
    bool removeUnits(UnitsPtr &units, bool setEmpty = true);

    /**
     * @brief Remove all units from the import source.
     *
     * Note that units which are removed from the import have their import
     * source cleared.  They therefore become locally
     * concrete instances in the model, and will return @c false to the
     * function isImport().
     *
     * @return True if the units are removed, false otherwise.
     */
    bool removeAllUnits();

    /**
     * @brief Get the number of units accessed by this import source.
     *
     * Returns the number of units imported by this import source.
     *
     * @return The number of units.
     */
    size_t unitsCount() const;

    /**
     * @brief Get the units item at the given @p index.
     *
     * Returns a reference to a units at the given @p index imported by this import source.
     * If the @p index is not valid a @c nullptr is returned, the range of valid values for the
     * index is [0, \#units).
     *
     * @param index The index of the units to return.
     *
     * @return A reference to the units at the given @p index on success, @c nullptr otherwise.
     */
    UnitsPtr units(size_t index) const;

protected:
    bool doEqual(const EntityPtr &other) const override;

private:
    ImportSource(); /**< Constructor. */

    ImportSourcePrivate *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
