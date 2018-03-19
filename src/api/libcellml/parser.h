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

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Parser class.
 *
 * The Parser class is for representing a CellML Parser.
 */
class LIBCELLML_EXPORT Parser: public Logger
{ 
public:
    Parser(); /**< Constructor */
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

private:
    void swap(Parser &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ParserImpl; /**< Forward declaration for pImpl idiom. */
    ParserImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
