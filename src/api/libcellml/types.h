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

#ifndef LIBCELLML_LIBCELLML_TYPES_H_
#define LIBCELLML_LIBCELLML_TYPES_H_

#include <memory>

namespace libcellml {

class Parser; /**< Forward declaration of Parser class. */
class Model; /**< Forward declaration of Model class. */
typedef std::shared_ptr<Model> ModelPtr; /**< Type definition for shared model pointer. */
class Component; /**< Forward declaration of Component class. */
typedef std::shared_ptr<Component> ComponentPtr; /**< Type definition for shared component pointer. */
class Import; /**< Forward declaration of Import class. */
typedef std::shared_ptr<Import> ImportPtr; /**< Type definition for shared import pointer. */
class Units; /**< Forward declaration of Units class. */
typedef std::shared_ptr<Units> UnitsPtr; /**< Type definition for shared units pointer. */
class Variable; /**< Forward declaration of Variable class. */
typedef std::shared_ptr<Variable> VariablePtr; /**< Type definition for shared variable pointer. */

class XmlAttribute; /**< Forward declaration of XmlAttribute class. */
typedef std::shared_ptr<XmlAttribute> XmlAttributePtr; /**< Type definition for shared XML node pointer. */
class XmlNode; /**< Forward declaration of XmlNode class. */
typedef std::shared_ptr<XmlNode> XmlNodePtr; /**< Type definition for shared XML node pointer. */
class XmlDoc; /**< Forward declaration of XmlDoc class. */
typedef std::shared_ptr<XmlDoc> XmlDocPtr; /**< Type definition for shared XML doc pointer. */

}

#endif /* LIBCELLML_LIBCELLML_TYPES_H_ */


