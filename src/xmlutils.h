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

#include <vector>

#include "xmldoc.h"

namespace libcellml {

/**
 * @brief Determine the missing namespaces of @p namespaceMap1 in @p namespaceMap2.
 *
 * Iterate through the namespaces in @p namespaceMap1 and search for each namespace
 * in @p namespaceMap2.  If a namespace in @p namespaceMap1 is not found in namespaceMap2
 * record it in the missing namespace map and return that.  Returns an empty @c XmlNamespaceMap if
 * all namespaces are found or if there are no namespaces in @p namespaceMap1.
 *
 * @param namespaceMap1 The @c XmlNamespaceMap namespaces to search for.
 * @param namespaceMap2 The @c XmlNamespaceMap namespaces to find in.
 * @return The @c XmlNamespaceMap of missing namespaces.
 */
XmlNamespaceMap determineMissingNamespaces(const XmlNamespaceMap &namespaceMap1, const XmlNamespaceMap &namespaceMap2);

/**
 * @brief Traverse the tree and return an @c XmlNamespaceMap of any undefined namespaces.
 *
 * From the root node of the tree given by the @p node, traverse the tree
 * searching for any undefined namespaces.  Return the @c XmlNamespaceMap
 * of all namespaces that are undefined.  This is done by comparing the defined
 * namespaces with the used namespaces.  Any used namespaces that are not found
 * in the defined namespace map are recorded as missing namespaces.
 *
 * @param node The root node of the tree to traverse.
 * @return @c XmlNamespaceMap of undefined namespaces.
 */
XmlNamespaceMap traverseTreeForUndefinedNamespaces(const XmlNodePtr &node);

/**
 * @brief Turn XML content with potentially multiple root elements in a vector of documents.
 *
 * Parse the @p content and try to find XML documents returning a vector of any XML documents
 * found.
 *
 * @param content The string to parse for XML roots.
 * @return A vector of @c XmlDoc pointers.
 */
std::vector<XmlDocPtr> multiRootXml(const std::string &content);

} // namespace libcellml
