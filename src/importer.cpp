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

#include "libcellml/importer.h"

#include <algorithm>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/issue.h"
#include "libcellml/model.h"
#include "libcellml/parser.h"

#include "namespaces.h"
#include "utilities.h"
#include "xmldoc.h"
#include "xmlutils.h"

namespace libcellml {

/**
 * @brief The Importer::ImporterImpl struct.
 *
 * The private implementation for the Importer class.
 */
struct Importer::ImporterImpl
{
    Importer *mImporter = nullptr;
};

Importer::Importer()
    : mPimpl(new ImporterImpl())
{
    mPimpl->mImporter = this;
}

Importer::~Importer()
{
    delete mPimpl;
}

ImporterPtr Importer::create() noexcept
{
    return std::shared_ptr<Importer> {new Importer {}};
}

// MOVED FROM MODEL

/**
 * @brief Resolve the path of the given filename using the given base.
 *
 * Resolves the full path to the given @p filename using the @p base.
 *
 * This function is only intended to work with local files.  It may not
 * work with bases that use the 'file://' prefix.
 *
 * @param filename The @c std::string relative path from the base path.
 * @param base The @c std::string location on local disk for determining the full path from.
 *
 * @return The full path from the @p base location to the @p filename
 */
std::string resolvePath(const std::string &filename, const std::string &base)
{
    // We can be naive here as we know what we are dealing with
    std::string path = base.substr(0, base.find_last_of('/') + 1) + filename;
    return path;
}

void resolveImport(const ImportedEntityPtr &importedEntity,
                   const std::string &baseFile)
{
    if (importedEntity->isImport()) {
        ImportSourcePtr importSource = importedEntity->importSource();
        if (!importSource->hasModel()) {
            std::string url = resolvePath(importSource->url(), baseFile);
            std::ifstream file(url);
            if (file.good()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                ParserPtr parser = Parser::create();
                ModelPtr model = parser->parseModel(buffer.str());
                ImporterPtr importer = Importer::create();
                importSource->setModel(model);
                importer->resolveImports(url, model);
            }
        }
    }
}

void resolveComponentImports(const ComponentEntityPtr &parentComponentEntity,
                             const std::string &baseFile)
{
    for (size_t n = 0; n < parentComponentEntity->componentCount(); ++n) {
        libcellml::ComponentPtr component = parentComponentEntity->component(n);
        if (component->isImport()) {
            resolveImport(component, baseFile);
        }
        resolveComponentImports(component, baseFile);
    }
}

void Importer::resolveImports(const std::string &baseFile, const ModelPtr &model)
{
    for (size_t n = 0; n < model->unitsCount(); ++n) {
        libcellml::UnitsPtr units = model->units(n);
        resolveImport(units, baseFile);
    }
    resolveComponentImports(model, baseFile);
}

} // namespace libcellml
