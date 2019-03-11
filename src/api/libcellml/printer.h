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

#include "libcellml/enumerations.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

#include <string>

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Printer class.
 *
 * The Printer class is for representing a CellML Printer.
 */
class LIBCELLML_EXPORT Printer: public Logger
{
public:
    Printer(); /**< Constructor */
    ~Printer() override; /**< Destructor */
    Printer(const Printer &rhs); /**< Copy constructor */
    Printer(Printer &&rhs); /**< Move constructor */
    Printer& operator=(Printer rhs); /**< Assignment operator */

    /**
     * @brief Serialise the @c Model to @c std::string.
     *
     * Serialise the given @p model to a std::string.
     *
     * @param model The @c Model to serialise.
     *
     * @return The @c std::string representation of the @c Model.
     */
    std::string printModel(const ModelPtr &model) const;

    /**
     * @brief Serialise the @c Model to @c std::string.
     *
     * Serialise the given @p model to a std::string.
     *
     * @overload
     *
     * @param model The @c Model to serialise.
     *
     * @return The @c std::string representation of the @c Model.
     */
    std::string printModel(Model model) const;

    /**
     * @brief Serialise the @c Model to @c std::string.
     *
     * Serialise the given @p model to a std::string.
     *
     * @overload
     *
     * @param model The @c Model to serialise.
     *
     * @return The @c std::string representation of the @c Model.
     */
    std::string printModel(Model *model) const;

    /**
     * @brief Serialise the @c Units to @c std::string.
     *
     * Serialise the given @p units to a std::string.
     *
     * @param units The @c Units to serialise.
     *
     * @return The @c std::string representation of the @c Units.
     */
    std::string printUnits(const UnitsPtr &units) const;

    /**
     * @brief Serialise the @c Units to @c std::string.
     *
     * Serialise the given @p units to a std::string.
     *
     * @overload
     *
     * @param units The @c Units to serialise.
     *
     * @return The @c std::string representation of the @c Units.
     */
    std::string printUnits(Units units) const;

    /**
     * @brief Serialise the variable to @c std::string.
     *
     * Serialise the given @p variable to a std::string.
     *
     * @param variable The @c Variable to serialise.
     *
     * @return The @c std::string representation of the @c Variable.
     */
    std::string printVariable(const VariablePtr &variable) const;

    /**
     * @brief Serialise the @c Variable to @c std::string.
     *
     * Serialise the given @p variable to a std::string.
     *
     * @overload
     *
     * @param variable The @c Variable to serialise.
     *
     * @return The @c std::string representation of the @c Variable.
     */
    std::string printVariable(Variable variable) const;

    /**
     * @brief Serialise the @c Component to @c std::string.
     *
     * Serialise the given @p component to a std::string.
     *
     * @param component The @c Component to serialise.
     *
     * @return The @c std::string representation of the @c Component.
     */
    std::string printComponent(const ComponentPtr &component) const;

    /**
     * @brief Serialise the @c Component to @c std::string.
     *
     * Serialise the given @p component to a std::string.
     *
     * @overload
     *
     * @param component The @c Component to serialise.
     *
     * @return The @c std::string representation of the @c Component.
     */
    std::string printComponent(Component component) const;

    /**
     * @brief Serialise the @c Reset to @c std::string.
     *
     * Serialise the given @p reset to a std::string.
     *
     * @param reset The @c Reset to serialise.
     *
     * @return  The @c std::string representation of the @c Reset.
     */
    std::string printReset(const ResetPtr &reset) const;

    /**
     * @brief Serialise the @c Reset to @c std::string.
     *
     * Serialise the given @p reset to a std::string.
     *
     * @overload
     *
     * @param reset The @c Reset to serialise.
     *
     * @return The @c std::string representation of the @c Reset.
     */
    std::string printReset(Reset reset) const;

private:
    void swap(Printer &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct PrinterImpl; /**< Forward declaration for pImpl idiom. */
    PrinterImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
