/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#ifndef LIBCELLML_LIBCELLML_IMPORTEDENTITY_H
#define LIBCELLML_LIBCELLML_IMPORTEDENTITY_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/namedentity.h"

namespace libcellml {

/**
 * @brief The Nameable class.
 * Base class for all nameable libCellML classes.
 */
class LIBCELLML_EXPORT ImportedEntity: public NamedEntity
{
public:
    ImportedEntity(); /**< Constructor */
    ~ImportedEntity(); /**< Destructor */
    ImportedEntity(const ImportedEntity &rhs); /**< Copy constructor */
    ImportedEntity(ImportedEntity &&rhs); /**< Move constructor */
    ImportedEntity& operator=(ImportedEntity n); /**< Assignment operator */

    bool isImport() const;

    ImportPtr getImport() const;

    void setImport(const ImportPtr &imp);

    std::string getImportReference() const;

    void setImportReference(const std::string &reference);

    /**
     * @brief Set the source component for this component.
     * Make this component an imported component by defining an import model
     * from which to extract the named component from.
     * @param imp The import from which the named component originates.
     * @param name The name of the component in the imported model to use.
     */
    void setSourceComponent(const ImportPtr &imp, const std::string &name);

private:
    void swap(ImportedEntity &rhs);

    struct ImportedEntityImpl; /**< Forward declaration for pImpl idiom. */
    ImportedEntityImpl* mPimpl; /**< Private member to implementation pointer */

};

}

#endif // LIBCELLML_LIBCELLML_IMPORTEDENTITY_H

