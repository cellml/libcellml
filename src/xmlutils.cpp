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

#include "xmlutils.h"

#include "utilities.h"
#include "xmldoc.h"

namespace libcellml {

/**
 * @brief Return a map of namespaces on attributes for this node.
 *
 * Scans all attributes of the node and records any associated namespace
 * attached to the attribute in an @c XmlNamespaceMap.
 *
 * @param node The @c XmlNode to scan attributes of.
 * @return @c XmlNamespaceMap of namespaces on attributes for the given @p node.
 */
XmlNamespaceMap attributeNamespaces(const XmlNodePtr &node)
{
    XmlNamespaceMap namespaceMap;
    auto tempAttribute = node->firstAttribute();
    while (tempAttribute != nullptr) {
        namespaceMap.emplace(tempAttribute->namespacePrefix(), tempAttribute->namespaceUri());
        tempAttribute = tempAttribute->next();
    }
    return namespaceMap;
}

XmlNamespaceMap determineMissingNamespaces(const XmlNamespaceMap &namespaceMap1, const XmlNamespaceMap &namespaceMap2)
{
    XmlNamespaceMap undefinedNamespaces;
    XmlNamespaceMap::const_iterator it;
    for (it = namespaceMap1.begin(); it != namespaceMap1.end(); ++it) {
        auto result = namespaceMap2.find(it->first);
        if (result == namespaceMap2.end()) {
            undefinedNamespaces.emplace(it->first, it->second);
        }
    }
    return undefinedNamespaces;
}

XmlNamespaceMap traverseTreeForUndefinedNamespaces(const XmlNodePtr &node)
{
    XmlNamespaceMap undefinedNamespaces;
    auto tempNode = node;
    while (tempNode != nullptr) {
        auto definedNamespaces = tempNode->definedNamespaces();
        auto usedNamespaces = attributeNamespaces(tempNode);
        auto missingNamespaces = determineMissingNamespaces(usedNamespaces, definedNamespaces);

        // Update undefined namespaces with missing namespaces.
        missingNamespaces.insert(undefinedNamespaces.begin(), undefinedNamespaces.end());
        std::swap(undefinedNamespaces, missingNamespaces);

        auto subUndefineNamespaces = traverseTreeForUndefinedNamespaces(tempNode->firstChild());

        // Update undefined namespaces with undefined namespaces in children.
        subUndefineNamespaces.insert(undefinedNamespaces.begin(), undefinedNamespaces.end());
        std::swap(undefinedNamespaces, subUndefineNamespaces);

        tempNode = tempNode->next();
    }

    return undefinedNamespaces;
}

std::vector<XmlDocPtr> multiRootXml(const std::string &content)
{
    std::vector<XmlDocPtr> childDocs;

    // Wrap potentially multiple nodes in our own root node.
    auto wrappedContent = "<root>" + trimCopy(content) + "</root>";

    // Parse this new string as a document and turn the child nodes
    // into their own document.
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    doc->parse(wrappedContent);
    XmlNodePtr rootNode = doc->rootNode();
    if (rootNode != nullptr) {
        XmlNodePtr child = rootNode->firstChild();
        while (child != nullptr) {
            if (child->isElement()) {
                auto childContent = child->convertToString();
                XmlDocPtr childDoc = std::make_shared<XmlDoc>();
                childDoc->parse(childContent);
                childDocs.push_back(childDoc);
            }
            child = child->next();
        }
    } else {
        XmlDocPtr originalContentDoc = std::make_shared<XmlDoc>();
        originalContentDoc->parse(content);
        childDocs.push_back(originalContentDoc);
    }

    return childDocs;
}

} // namespace libcellml
