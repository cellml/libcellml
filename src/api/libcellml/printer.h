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

#include "libcellml/enumerations.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

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
    ~Printer(); /**< Destructor */
    Printer(const Printer &rhs); /**< Copy constructor */
    Printer(Printer &&rhs); /**< Move constructor */
    Printer& operator=(Printer p); /**< Assignment operator */

    /**
     * @brief Serialise the model to @c std::string.
     *
     * Serialise the given @p model to a std::string.
     *
     * @param model The model to serialise.
     *
     * @return The @c std::string representation of the model.
     */
    std::string printModel(ModelPtr model) const;

    /**
     * @brief Serialise the model to @c std::string.
     *
     * Serialise the given @p model to a std::string.
     *
     * @overload
     *
     * @param model The model to serialise.
     *
     * @return The @c std::string representation of the model.
     */
    std::string printModel(Model model) const;

    /**
     * @brief Serialise the model to @c std::string.
     *
     * Serialise the given @p model to a std::string.
     *
     * @overload
     *
     * @param model The model to serialise.
     *
     * @return The @c std::string representation of the model.
     */
    std::string printModel(Model *model) const;

    /**
     * @brief Serialise the units to @c std::string.
     *
     * Serialise the given @p units to a std::string.
     *
     * @param units The units to serialise.
     *
     * @return The @c std::string representation of the units.
     */
    std::string printUnits(UnitsPtr units) const;

    /**
     * @brief Serialise the units to @c std::string.
     *
     * Serialise the given @p units to a std::string.
     *
     * @overload
     *
     * @param units The units to serialise.
     *
     * @return The @c std::string representation of the units.
     */
    std::string printUnits(Units units) const;

    /**
     * @brief Serialise the variable to @c std::string.
     *
     * Serialise the given @p variable to a std::string.
     *
     * @param variable The variable to serialise.
     *
     * @return The @c std::string representation of the variable.
     */
    std::string printVariable(VariablePtr variable) const;

    /**
     * @brief Serialise the variable to @c std::string.
     *
     * Serialise the given @p variable to a std::string.
     *
     * @overload
     *
     * @param variable The variable to serialise.
     *
     * @return The @c std::string representation of the variable.
     */
    std::string printVariable(Variable variable) const;

    /**
     * @brief Serialise the component to @c std::string.
     *
     * Serialise the given @p component to a std::string.
     *
     * @param component The component to serialise.
     *
     * @return The @c std::string representation of the component.
     */
    std::string printComponent(ComponentPtr component) const;

    /**
     * @brief Serialise the component to @c std::string.
     *
     * Serialise the given @p component to a std::string.
     *
     * @overload
     *
     * @param component The component to serialise.
     *
     * @return The @c std::string representation of the component.
     */
    std::string printComponent(Component component) const;

private:
    /**
     * @brief Serialise the component encapsulation to @c std::string.
     *
     * Serialise the given @p component encapsulation to a std::string.
     *
     * @param component The component encapsulation to serialise.
     *
     * @return The @c std::string representation of the component encapsulation.
     */
    std::string printEncapsulation(ComponentPtr component) const;

    void swap(Printer &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct PrinterImpl; /**< Forward declaration for pImpl idiom. */
    PrinterImpl *mPimpl; /**< Private member to implementation pointer. */
};

}
