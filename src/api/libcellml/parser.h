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

#include <string>

#include "libcellml/logger.h"
#include "libcellml/model.h"
#include "libcellml/types.h"
#include "libcellml/units.h"

namespace libcellml {

/**
 * @brief The Parser class.
 *
 * The Parser class is for representing a CellML Parser.
 */
class LIBCELLML_EXPORT Parser: public Logger
{
public:
    ~Parser() override; /**< Destructor, @private. */
    Parser(const Parser &rhs) = delete; /**< Copy constructor, @private. */
    Parser(Parser &&rhs) noexcept = delete; /**< Move constructor, @private. */
    Parser &operator=(Parser rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create a @c Parser object.
     *
     * Factory method to create a @c Parser.  Create a
     * parser with::
     *
     *   ParserPtr parser = libcellml::Parser::create();
     *
     * @return A smart pointer to a @c Parser object.
     */
    static ParserPtr create() noexcept;

    /**
     * @brief Create and populate a new model from a @c std::string.
     *
     * Creates and populates a new model pointer by parsing CellML
     * entities and attributes from the @p input @c std::string.
     *
     * All existing issues will be removed before the input is parsed.
     *
     * If @p parseVersion1XModels is @c true then CellML 1.0, CellML 1.1, and
     * CellML 2.0 models will be parsed. If @p parseVersion1XModels is @c false then
     * only CellML 2.0 models will be parsed.  The default value of parseVersion1XModels
     * is @c false.
     *
     * @param input The string to parse into a model.
     * @param parseVersion1XModels Boolean to signal whether CellML 1.X
     * models should be parsed, @c false by default.
     *
     * @return The new @c ModelPtr deserialised from the input string.
     */
    ModelPtr parseModel(const std::string &input, bool parseVersion1XModels=false);

private:
    Parser(); /**< Constructor, @private. */

    class ParserImpl; /**< Forward declaration for pImpl idiom, @private. */

    ParserImpl *pFunc(); /**< Getter for private implementation pointer, @private. */
};

} // namespace libcellml
