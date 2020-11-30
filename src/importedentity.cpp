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

#include "libcellml/importedentity.h"

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/units.h"

#include "utilities.h"

namespace libcellml {

/**
 * @brief The ImportedEntity::ImportedEntityImpl struct.
 *
 * The private implementation for the ImportedEntity class.
 */
struct ImportedEntity::ImportedEntityImpl
{
    ImportSourcePtr mImportSource;
    std::string mImportReference;
};

ImportedEntity::ImportedEntity()
    : mPimpl(new ImportedEntityImpl())
{
}

ImportedEntity::~ImportedEntity()
{
    delete mPimpl;
}

bool ImportedEntity::isImport() const
{
    return mPimpl->mImportSource != nullptr;
}

ImportSourcePtr ImportedEntity::importSource() const
{
    return mPimpl->mImportSource;
}

void ImportedEntity::setImportSource(const ImportSourcePtr &importSource)
{
    doSetImportSource(importSource);
}

void ImportedEntity::doSetImportSource(const ImportSourcePtr &importSource)
{
    mPimpl->mImportSource = importSource;
}

std::string ImportedEntity::importReference() const
{
    return mPimpl->mImportReference;
}

void ImportedEntity::setImportReference(const std::string &reference)
{
    mPimpl->mImportReference = reference;
}

bool ImportedEntity::isResolved() const
{
    bool resolved = true;
    if (mPimpl->mImportSource) {
        auto model = mPimpl->mImportSource->model();
        if (model) {
            if (typeid(*this) == typeid(Units)) {
                auto importedUnits = model->units(mPimpl->mImportReference);
                if (importedUnits) {
                    if (importedUnits->isImport()) {
                        resolved = importedUnits->isResolved();
                    } else {
                        for (size_t u = 0; u < importedUnits->unitCount() && resolved; ++u) {
                            std::string reference;
                            std::string prefix;
                            std::string id;
                            double exponent;
                            double multiplier;
                            importedUnits->unitAttributes(u, reference, prefix, exponent, multiplier, id);
                            if (isStandardUnitName(reference)) {
                                continue;
                            }
                            auto childUnits = model->units(reference);
                            if (childUnits) {
                                resolved = childUnits->isResolved();
                            } else {
                                resolved = false;
                            }
                        }
                    }
                } else {
                    resolved = false;
                }
            } else if (typeid(*this) == typeid(Component)) {
                auto importedComponent = model->component(mPimpl->mImportReference);
                if (importedComponent) {
                    resolved = importedComponent->isResolved();
                } else {
                    resolved = false;
                }
            }
        } else {
            resolved = false;
        }
    }

    return resolved;
}

} // namespace libcellml
