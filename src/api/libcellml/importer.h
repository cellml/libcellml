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

#include "libcellml/logger.h"
#include "libcellml/model.h"
#include "libcellml/types.h"

#include <string>

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
     * @brief Create an @c Importer object.
     *
     * Factory method to create an @c Importer.  Create an
     * importer with::
     *
     *   ImporterPtr importer = libcellml::Importer::create();
     *
     * @return A smart pointer to an @c Importer object.
     */
    static ImporterPtr create() noexcept;

    /**
     * @brief Resolve all imports in this model.
     *
     * Resolve all @c Component and @c Units imports by loading the models
     * from local disk through relative URLs.  The @p baseFile is used to determine
     * the full path to the source model relative to this one.
     *
     * @param baseFile The @c std::string location on local disk of the source @c Model.
     * @param model The @c Model to resolve.
     */
    static void resolveImports(const std::string &baseFile, const ModelPtr &model);

private:
    Importer(); /**< Constructor */

    struct ImporterImpl; /**< Forward declaration for pImpl idiom. */
    ImporterImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
