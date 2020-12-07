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

#include <set>
#include <string>

#include "libcellml/logger.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Importer class.
 *
 * The Importer class is for representing a CellML Importer.
 */
class LIBCELLML_EXPORT Importer: public Logger
{
public:
    ~Importer() override; /**< Destructor. */
    Importer(const Importer &rhs) = delete; /**< Copy constructor. */
    Importer(Importer &&rhs) noexcept = delete; /**< Move constructor. */
    Importer &operator=(Importer rhs) = delete; /**< Assignment operator. */

    /**
     * @brief Create an @c Importer object.
     *
     * Factory method to create an @c Importer.  Create a
     * blank importer with::
     *
     *   auto importer = libcellml::Importer::create();
     *
     * @return A smart pointer to an @c Importer object.
     */
    static ImporterPtr create() noexcept;

    /**
     * @brief Flatten the @p model.
     *
     * Instantiate all imports and removes them from the @p model.
     * The result is a self-contained model requiring no external
     * resources and having no imports.
     *
     * @sa clone
     *
     * @param model A @c ModelPtr whose imports will be resolved.
     *
     * @return If the operation is successful, a new @c ModelPtr to the flattened model; otherwise, the @c nullptr.
     */
    ModelPtr flattenModel(const ModelPtr &model);

    /**
     * @brief Resolve all imports in the @p model.
     *
     * Resolve all @c Component and @c Units imports by loading the models
     * from local disk through relative URLs.  The @p baseFile is used to determine
     * the full path to the source model relative to this one.
     *
     * @param model The @c Model whose imports need resolution.
     * @param baseFile The @c std::string location on local disk of the source @c Model.
     * 
     * @return @c true if all imports have been resolved successfully, @c false otherwise.
     */
    bool resolveImports(ModelPtr &model, const std::string &baseFile);

    /**
     * @brief Return the number of models present in the importer's library.
     *
     * @return The number of models present in the importer's library.
     */
    size_t libraryCount();

    /**
     * @brief Retrieve the @c ModelPtr instance from the importer library which was loaded
     *        from the given @p key.
     *
     * @return A @c ModelPtr instance.
     */
    ModelPtr library(const std::string &key);

    /**
     * @brief Get a model from the library at the given @p index.
     *
     * Return a reference to the model at the index @p index for this
     * importer's library. If the index is not valid a @c nullptr is returned. The valid
     * range for the index is [0, \#library items).
     *
     * @param index The index of the model to return.
     *
     * @return A reference to the model at the given index on success, @c nullptr otherwise.
     */
    ModelPtr library(const size_t &index);

    /**
     * @brief Get the key string under which a model is stored in the library, at the given @p index.
     * 
     * Get the key string under which a model is stored in the library, at the given @p index.
     * 
     * @param index The index of the key to return.
     * 
     * @return If successful, a string under which the model has been stored, or an empty string otherwise.
     */
    std::string key(const size_t &index);

    /**
     * @brief Manually add a local @c ModelPtr model instance to the importer library,
     *        using the given @p key as a reference.
     *
     * If the given key already exists in the library, the function will return false
     * and the library will not be changed.
     *
     * @sa replaceModel
     *
     * @param model a @c ModelPtr instance to add.
     * @param key a @c std::string representing the key to associate with the model.
     *
     * @return @c true if the model was added, @c false if it was not.
     */
    bool addModel(const ModelPtr &model, const std::string &key);

    /**
     * @brief Replace a @c ModelPtr model instance in the importer library,
     *        using the given @p key as a reference.
     *
     * If the given key already exists in the library, the function will replace its
     * model with the one supplied, and return @c true.
     *
     * If the given key does not exist, the function will return @c false, and
     * the library will be unchanged.
     *
     * @sa addModel.
     *
     * @param model a @c ModelPtr instance to replace the current one.
     * @param key a @c std::string representing the key at which to replace the model.
     *
     * @return @c true if the model was replaced, @c false if it was not.
     */
    bool replaceModel(const ModelPtr &model, const std::string &key);

    /**
     * @brief Clear the links with other models from all import sources.
     *
     * Clear the links with other models from all import sources.
     */
    void clearImports(ModelPtr &model);

    /**
     * @brief Return a vector of @ref ImportRequirement items which are the import requirements of the given @p model.
     * 
     * Return a vector of @ref ImportRequirement items of the given @p model.
     * 
     * @param model A @c Model which imports other models.  
     * 
     * @return A @c std::vector of import requirements.
     */
    std::vector<ImportRequirementPtr> requirements(const ModelPtr &model);

private:
    Importer(); /**< Constructor. */
    explicit Importer(const std::string &name); /**< Constructor with std::string parameter*/

    struct ImporterImpl; /**< Forward declaration for pImpl idiom. */
    ImporterImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
