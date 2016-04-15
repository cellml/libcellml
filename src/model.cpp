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

#include "libcellml/model.h"

#include <map>
#include <vector>
#include <utility>
#include <stack>

#include <libcellml/import.h>

namespace libcellml {

Model::Model()
{
}

Model::~Model()
{
}

Model::Model(const Model& rhs)
    : ComponentEntity(rhs)
{
}

Model::Model(Model &&rhs)
    : ComponentEntity(std::move(rhs))
{
}

Model& Model::operator=(Model m)
{
    ComponentEntity::operator= (m);
    return *this;
}

std::string Model::doSerialisation(FORMATS format) const
{
    typedef std::pair <std::string, std::string> ImportNamePair;
    typedef std::vector<ImportNamePair>::const_iterator VectorPairIterator;
    typedef std::map <ImportPtr, std::vector<ImportNamePair> > ImportMap;
    typedef ImportMap::const_iterator ImportMapIterator;

    // Gather all imports
    ImportMap importMap;
    std::stack<size_t> indeciesStack;
    std::stack<ComponentPtr> componentStack;
    bool incrementComponent = false;
    for (size_t i = 0; i < componentCount(); ++i) {
        ComponentPtr comp = getComponent(i);
        ComponentPtr modelComponent = comp;
        size_t index = 0;
        while (comp != nullptr) {
            incrementComponent = false;
            if (comp->isImport()) {
                ImportNamePair pair = std::make_pair(comp->getImportReference(), comp->getName());
                ImportPtr imp = comp->getImport();
                if (!importMap.count(imp)) {
                    importMap[imp] = std::vector<ImportNamePair>();
                }
                importMap[imp].push_back(pair);
                incrementComponent = true;
            } else if (comp->componentCount()) {
                // If the current component is a model component
                // let the 'for' loop take care of the stack.
                if (modelComponent != comp) {
                    componentStack.push(comp);
                    indeciesStack.push(index);
                }
                index = 0;
                comp = comp->getComponent(index);
            } else {
                incrementComponent = true;
            }

            if (incrementComponent) {
                if (!componentStack.empty()) {
                    index = indeciesStack.top();
                    comp = componentStack.top();
                    indeciesStack.pop();
                    componentStack.pop();
                    index += 1;
                    if (index < comp->componentCount()) {
                        comp = comp->getComponent(index);
                    } else {
                        comp = nullptr;
                    }
                } else {
                    index = 0;
                    comp = nullptr;
                }
            }
        }
    }

    std::string repr = "";
    if (format == FORMAT_XML) {
        repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"";
        if (getName().length()) {
            repr += " name=\"" + getName() + "\"";
        }
        repr += ">";

        for (ImportMapIterator iter = importMap.begin(); iter != importMap.end(); ++iter)
        {
            repr += "<import xlink:href=\"" + iter->first->getSource() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
            for (VectorPairIterator vectorIter = iter->second.begin(); vectorIter != iter->second.end(); ++vectorIter) {
                repr += "<component component_ref=\"" + std::get<0>(*vectorIter) + "\" name=\"" + std::get<1>(*vectorIter) + "\"/>";
            }
            repr += "</import>";
        }

        repr += serialiseUnits(format);

        // Serialize components of the model, imported components have already been dealt with at this point.
        for (size_t i = 0; i < componentCount(); ++i) {
            repr += getComponent(i)->serialise(format);
        }
        repr += "</model>";
    }

    return repr;
}

void Model::doAddComponent(const ComponentPtr &c)
{
    // Check for cycles
    if (!hasParent(c.get())) {
        c->setParent(this);
        ComponentEntity::doAddComponent(c);
    }
}

}
