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

#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Printer class.
 *
 * The Printer class is for representing a CellML Printer.
 */
class LIBCELLML_EXPORT Printer
{
public:
    ~Printer(); /**< Destructor */
    Printer(const Printer &rhs) = delete; /**< Copy constructor */
    Printer(Printer &&rhs) noexcept = delete; /**< Move constructor */
    Printer &operator=(Printer rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Printer object.
     *
     * Factory method to create a @c Printer.  Create a
     * printer with::
     *
     *   PrinterPtr printer = libcellml::Printer::create();
     *
     * @return A smart pointer to a @c Printer object.
     */
    static PrinterPtr create() noexcept;

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

private:
    Printer(); /**< Constructor */

    struct PrinterImpl; /**< Forward declaration for pImpl idiom. */
    PrinterImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
