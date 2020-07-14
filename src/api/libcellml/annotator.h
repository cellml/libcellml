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

#include <any>
#include <map>
#include <string>
#include <vector>

#include "libcellml/exportdefinitions.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

namespace libcellml {

using VariablePair = std::pair<VariablePtr, VariablePtr>;
using UnitItem = std::pair<UnitsPtr, size_t>;
using AnyItem = std::pair<std::uint64_t, std::any>;
using ItemList = std::map<std::string, AnyItem>;
/**
 * @brief The Annotator class.
 *
 * The Annotator class is for representing a CellML Annotator.
 */
class LIBCELLML_EXPORT Annotator: public Logger
{
public:
    enum Type
    {
        COMPONENT,
        COMPONENT_REF,
        CONNECTION,
        ENCAPSULATION,
        IMPORT,
        ISSUE,
        MAP_VARIABLES,
        MODEL,
        RESET,
        RESET_VALUE,
        TEST_VALUE,
        UNIT,
        UNITS,
        VARIABLE,
    };

    ~Annotator() override; /**< Destructor */
    Annotator(const Annotator &rhs) = delete; /**< Copy constructor */
    Annotator(Annotator &&rhs) noexcept = delete; /**< Move constructor */
    Annotator &operator=(Annotator rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Annotator object.
     *
     * Factory method to create a @c Annotator.  Create a
     * annotator with::
     *
     *   AnnotatorPtr annotator = libcellml::Annotator::create();
     *
     * @return A smart pointer to an @c Annotator object.
     */
    static AnnotatorPtr create() noexcept;

    /**
     * @brief Builds the internal map of ids to items for the model provided.
     *
     * @param model A @c ModelPtr model to build map for.
     */
    void build(const ModelPtr &model);

    /**
     * @brief Retrieves an item with the given id string, in the model
     * for which the internal map was built using @sa build().
     *
     * The item returned is a @c std::pair containing:
     *  - an @c Annotator::Type enum, and
     *  - an @c std::any item containing the item.
     *
     * Possible string labels and their corresponding items returned are:
     *  - Annotator::Type::COMPONENT
     *          ComponentPtr to item with this id.
     *  - Annotator::Type::COMPONENT_REF
     *          ComponentPtr to component which has component->componentRefId() == id.
     *  - Annotator::Type::CONNECTION
     *          VariablePair including two VariablePtr items which can be used to retrieve the
     *          connection.  Note that multiple pairs of variables could be used to identify
     *          a single connection.
     *   Annotator::Type::ENCAPSULATION
     *          An empty string.
     *   Annotator::Type::IMPORT
     *          An ImportSourcePtr item with this id.
     *   Annotator::Type::ISSUE
     *          An IssuePtr containing an error message.
     *   Annotator::Type::MAP_VARIABLES
     *          A VariablePair including two VariablePtr items which can be used to retrieve the
     *          equivalence.
     *   Annotator::Type::MODEL
     *          A ModelPtr with this id.
     *   Annotator::Type::RESET
     *          A ResetPtr with this id.
     *   Annotator::Type::RESET_VALUE
     *          A ResetPtr which is the parent of the reset_value item found with this id.
     *          Retrieve the reset_value MathML string using reset->resetValue().
     *   Annotator::Type::TEST_VALUE
     *          A ResetPtr which is the parent of the test_value item found with this id.
     *          Retrieve the test_value MathML string using reset->testValue().
     *   Annotator::Type::UNIT
     *          A UnitItem pair containing:
     *              .first: A UnitsPtr to the parent of the unit item with this id, and
     *              .second: A size_t with the index to the Unit item.
     *          Retrieve the unit description using Units::unitAttributes() function with
     *   Annotator::Type::UNITS
     *          A UnitsPtr item with this id.
     *   Annotator::Type::VARIABLE
     *          A VariablePtr item with this id.
          *
     * @param id A @c std::string representing the @p id to retrieve.
     *
     * @return An @c AnyItem item as described above.
     */
    AnyItem item(const std::string &id);

    // KRM reinstating specific return types
    ComponentPtr component(const std::string &id);
    VariablePtr variable(const std::string &id);
    ResetPtr reset(const std::string &id);
    ModelPtr model(const std::string &id);
    ImportSourcePtr importSource(const std::string &id);
    UnitsPtr units(const std::string &id);
    VariablePair connection(const std::string &id);
    VariablePair mapVariables(const std::string &id);
    UnitItem unit(const std::string &id);
    ComponentPtr componentRef(const std::string &id);
    // std::string math(const std::string &id); // This could return a ComponentPtr the same way reset_value returns a ResetPtr?
    ResetPtr testValue(const std::string &id);
    ResetPtr resetValue(const std::string &id);

    std::pair<Annotator::Type, std::vector<std::size_t>> indicesToItem(const std::string &id);
    std::string instructions(const std::string &id);

private:
    Annotator(); /**< Constructor */

    struct AnnotatorImpl; /**< Forward declaration for pImpl idiom. */
    AnnotatorImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
