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

#ifndef LIBCELLML_LIBCELLML_PARSER_H_
#define LIBCELLML_LIBCELLML_PARSER_H_

#include <string>

#include "libcellml/model.h"
#include "libcellml/types.h"
#include "libcellml/units.h"
#include "../xmldoc.h"
#include "../xmlnode.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Parser class.
 *
 * The Parser class is for representing a CellML Parser.
 */
class LIBCELLML_EXPORT Parser
{ 
public:
    Parser(Format format); /**< Constructor */
    ~Parser(); /**< Destructor */
    Parser(const Parser &rhs); /**< Copy constructor */
    Parser(Parser &&rhs); /**< Move constructor */
    Parser& operator=(Parser p); /**< Assignment operator */

    /**
     * @brief Create and populate a new model from a @c std::string.
     *
     * Creates and populates a new model pointer by parsing CellML
     * entities and attributes from the @p input @c std::string.
     *
     * @param input The string to parse into a model.
     *
     * @return The new @c ModelPtr deserialised from the input string.
     */
    ModelPtr parseModel(const std::string &input);

    /**
     * @brief Updates an existing model with the attributes from a @c std::string.
     *
     * Updates the argument @p model with CellML entities and attributes
     * from the argument @p input @c std::string. Any entities, objects,
     * or attributes of with matching names in the model will be
     * overwritten by those loaded from the @p input @c std::string.
     *
     * @param model The @c ModelPtr to update.
     * @param input The string to parse into the @p model.
     */
    void updateModel(const ModelPtr &model, const std::string &input);

private:
    /**
     * @brief Load the @p model with attributes parsed from the XML @p node.
     *
     * Loads the argument @p model with attributes and objects parsed from
     * the argument XML @p node. Existing objects/attributes with matching
     * names in the @p model will be overwritten by those from the XML @p node.
     *
     * @param model The @c ModelPtr to update.
     * @param node The @c XmlNodePtr to load the @p model from.
     */
    void loadModel(const ModelPtr &model, const XmlNodePtr &node);

    /**
     * @brief Load the @p component with attributes parsed from the XML @p node.
     *
     * Loads the argument @p component with attributes and objects parsed from
     * the argument XML @p node. Existing objects/attributes with matching
     * names in the @p component will be overwritten by those from the XML @p node.
     *
     * @param component The @c ComponentPtr to update.
     * @param node The @c XmlNodePtr to load the @p component from.
     */
    void loadComponent(const ComponentPtr &component, const XmlNodePtr &node);

    /**
     * @brief Load the @p model with attributes parsed from the connection XML @p node.
     *
     * Loads the argument @p model with CellML connection information parsed from
     * the argument XML @p node. If any variable equivalence relationships already
     * exist in the @p model, the connection information parsed from the XML @p node
     * will be added to this network.
     *
     * @param model The @c ModelPtr to update.
     * @param node The @c XmlNodePtr to load the connection from.
     */
    void loadConnection(const ModelPtr &model, const XmlNodePtr &node);

    /**
     * @brief Load the @p model with attributes parsed from the encapsulated XML node.
     *
     * Loads the argument @p model with CellML encapsulation information parsed from
     * the argument XML @p parentComponentNode. If any encapsulation relationships already
     * exist in the @p model, the encapsulation information parsed from the XML @p node
     * will be added to this network.
     *
     * @param model The @c ModelPtr to update.
     * @param parentComponentNode The parent @c XmlNodePtr to load the encapsulated node into.
     */
    void loadEncapsulation(const ModelPtr &model, XmlNodePtr &parentComponentnode);

    /**
     * @brief Load the @p import with attributes parsed from the XML @p node.
     *
     * Loads the argument @p import with CellML attributes parsed from
     * the argument XML @p node. Existing objects/attributes with matching
     * names in the @p import will be overwritten by those from the XML @p node.
     * Any imported components or units will also be added to the @p model.
     *
     * @param import The @c ImportPtr to update.
     * @param model The @c ModelPtr to add imported components/units to.
     * @param node The @c XmlNodePtr to load the @p import from.
     */
    void loadImport(const ImportPtr &import, const ModelPtr &model, const XmlNodePtr &node);

    /**
     * @brief Load the @p units with attributes parsed from the XML @p node.
     *
     * Loads the argument @p units with CellML attributes parsed from
     * the argument XML @p node. Existing objects/attributes with matching
     * names in the @p units will be overwritten by those from the XML @p node.
     *
     * @param units The @c UnitsPtr to update.
     * @param node The @c XmlNodePtr to load the @p units from.
     */
    void loadUnits(const UnitsPtr &units, const XmlNodePtr &node);

    /**
     * @brief Load the @p variable with attributes parsed from the XML @p node.
     *
     * Loads the argument @p variable with CellML attributes parsed from
     * the argument XML @p node. Existing objects/attributes with matching
     * names in the @p variable will be overwritten by those from the XML @p node.
     *
     * @param variable The @c VariablePtr to update.
     * @param node The @c XmlNodePtr to load the @p units from.
     */
    void loadVariable(const VariablePtr &variable, const XmlNodePtr &node);

    void swap(Parser &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ParserImpl; /**< Forward declaration for pImpl idiom. */
    ParserImpl* mPimpl; /**< Private member to implementation pointer. */

};

}

#endif /* LIBCELLML_LIBCELLML_PARSER_H_ */

