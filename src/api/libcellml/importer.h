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
    ~Importer() override; /**< Destructor */
    Importer(const Importer &rhs) = delete; /**< Copy constructor */
    Importer(Importer &&rhs) noexcept = delete; /**< Move constructor */
    Importer &operator=(Importer rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Importer object.
     *
     * Factory method to create a @c Importer.  Create a
     * blank model with::
     *
     *   ImporterPtr importer = libcellml::Importer::create();
     *
     * @return A smart pointer to a @c Importer object.
     */
    static ImporterPtr create() noexcept;

    /**
     * @brief Flatten the @p model.
     *
     * Instantiates all imports and removes them from the @p model.
     * The result is a self-contained model requiring no external
     * resources and having no imports.
     *
     * @sa clone
     */
    ModelPtr flatten(const ModelPtr &inModel);

    /**
     * @brief Resolve all imports in the @p model.
     *
     * Resolve all @c Component and @c Units imports by loading the models
     * from local disk through relative URLs.  The @p baseFile is used to determine
     * the full path to the source model relative to this one.
     * @param model The @c Model whose imports need resolution.
     * @param baseFile The @c std::string location on local disk of the source @c Model.
     */
    void resolveImports(ModelPtr &model, const std::string &baseFile);

    /**
     * @brief Return the number of models present in the importer's library.
     *
     * @return The number of models present in the importer's library.
     */
    size_t libraryCount();

    /**
     * @brief Retrieve the @c ModelPtr instance from the importer library which was loaded
     *        from the given @p url.
     *
     *  The @p url must be the absolute path, including the filename and the baseFile path.
     *
     * @return A @c ModelPtr instance.
     */
    ModelPtr library(const std::string &url);

    /**
     * @brief Manually add a local @c ModelPtr model instance to the importer library,
     *        using the given @p url as a reference.
     *
     * If the given url already exists in the library, the function will return false
     * and the library will not be changed.
     * @sa replaceModel.
     *
     * @param model a @c ModelPtr instance to add.
     * @param url a @c std::string representing the url to associate with the model.
     *
     * @return boolean value, @c true if the model was added, @c false if it was not.
     */
    bool addModel(const ModelPtr &model, const std::string &url);

    /**
     * @brief Replace a @c ModelPtr model instance in the importer library,
     *        using the given @p url as a reference.
     *
     * If the given url already exists in the library, the function will replace its
     * model with the one supplied, and return @c true.
     *
     * If the given url does not exist, the function will return @c false, and
     * the library will be unchanged.
     *
     * @sa addModel.
     *
     * @param model a @c ModelPtr instance to replace the current one.
     * @param url a @c std::string representing the url at which to replace the model.
     *
     * @return boolean value, @c true if the model was replaced, @c false if it was not.
     */
    bool replaceModel(const ModelPtr &model, const std::string &url);

    /**
     * @brief Retrieve the pair of url key and import reference at the given index.
     *
     * This is taken from the list of dependencies for the models which have been resolved,
     * and is what will break if those external files are ever moved or renamed.
     *
     * The "first" attribute of the returned pair is the url at which the imported model was
     * accessed and under which it is now stored in the library, and the "second" attribute
     * is the import reference.
     *
     * @return a @c std::pair of @c std::strings.
     */
    std::pair<std::string, std::string> externalDependency(size_t index) const;

    /**
     * @brief Get the number of external dependencies in the library.
     *
     * Returns the number of dependencies for the models which have been resolved by this
     * importer.
     *
     * @return the number of variables.
     */
    size_t externalDependencyCount() const;

private:
    Importer(); /**< Constructor */
    explicit Importer(const std::string &name); /**< Constructor with std::string parameter*/

    struct ImporterImpl; /**< Forward declaration for pImpl idiom. */
    ImporterImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
