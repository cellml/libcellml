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
limitations under the License.
*/

#ifndef LIBCELLML_LIBCELLML_IMPORTEDENTITY_H
#define LIBCELLML_LIBCELLML_IMPORTEDENTITY_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/namedentity.h"

namespace libcellml {

/**
 * @brief The ImportedEntity class.
 *
 * Base class for all importable libCellML classes.
 */
class LIBCELLML_EXPORT ImportedEntity: public NamedEntity
{
public:
    ImportedEntity(); /**< Constructor */
    ~ImportedEntity(); /**< Destructor */
    ImportedEntity(const ImportedEntity &rhs); /**< Copy constructor */
    ImportedEntity(ImportedEntity &&rhs); /**< Move constructor */
    ImportedEntity& operator=(ImportedEntity n); /**< Assignment operator */

    /**
     * @brief Test if this entity is an imported entity.
     *
     * Method to test if this entity is an imported entity.  Returns
     * @c true if the import is not the @c nullptr otherwise return @c false.
     *
     * @return @c true if the import is not the @c nullptr, @c false otherwise.
     */
    bool isImport() const;

    /**
     * @brief Get the import set.
     *
     * Get the import set, if no import is set @c nullptr is returned.
     *
     * @sa setImport
     *
     * @return The shared pointer for the import, if no import is set returns @c nullptr.
     */
    ImportPtr getImport() const;

    /**
     * @brief Set the import.
     *
     * Set the import for the imported entity.  Set to @c nullptr to unset the import.
     *
     * @sa getImport
     *
     * @param imp The import to set.
     */
    void setImport(const ImportPtr &imp);

    /**
     * @brief Get the import reference.
     *
     * Get the reference to the entity in the imported model.
     *
     * @sa setImportReference
     *
     * @return The reference to the entity in the imported model, the empty
     * string if it is not set.
     */
    std::string getImportReference() const;

    /**
     * @brief Set the import reference.
     *
     * Set the import reference to an entity in the imported model.  The import
     * reference should be a Component or a Unit in the import model.
     *
     * @sa getImportReference
     *
     * @param reference The name of the reference to refer to in the import model.
     */
    void setImportReference(const std::string &reference);

private:
    void swap(ImportedEntity &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ImportedEntityImpl; /**< Forward declaration for pImpl idiom. */
    ImportedEntityImpl* mPimpl; /**< Private member to implementation pointer. */

};

}

#endif // LIBCELLML_LIBCELLML_IMPORTEDENTITY_H

