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
    mPimpl->mImportSource = nullptr;
    mPimpl->mImportReference = "";
}

ImportedEntity::~ImportedEntity()
{
    delete mPimpl;
}

ImportedEntity::ImportedEntity(const ImportedEntity& rhs)
    : NamedEntity(rhs)
    , mPimpl(new ImportedEntityImpl())
{
    mPimpl->mImportSource = rhs.mPimpl->mImportSource;
    mPimpl->mImportReference = rhs.mPimpl->mImportReference;
}

ImportedEntity::ImportedEntity(ImportedEntity &&rhs)
    : NamedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

ImportedEntity& ImportedEntity::operator=(ImportedEntity e)
{
    NamedEntity::operator= (e);
    e.swap(*this);
    return *this;
}

void ImportedEntity::swap(ImportedEntity &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

bool ImportedEntity::isImport() const
{
    return mPimpl->mImportSource != nullptr;
}

ImportSourcePtr ImportedEntity::getImportSource() const
{
    return mPimpl->mImportSource;
}

void ImportedEntity::setImportSource(const ImportSourcePtr &importSource)
{
    mPimpl->mImportSource = importSource;
}

std::string ImportedEntity::getImportReference() const
{
    return mPimpl->mImportReference;
}

void ImportedEntity::setImportReference(const std::string &reference)
{
    mPimpl->mImportReference = reference;
}

}
