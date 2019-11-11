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
    Printer(Printer &&rhs) noexcept; /**< Move constructor */
    Printer &operator=(Printer rhs); /**< Assignment operator */

    template<typename... Args>
    static std::shared_ptr<Printer> create(Args &&... args) noexcept
    {
        return std::shared_ptr<Printer> {new Printer {std::forward<Args>(args)...}};
    }

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
    void swap(Printer &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct PrinterImpl; /**< Forward declaration for pImpl idiom. */
    PrinterImpl *mPimpl; /**< Private member to implementation pointer. */
};

} // namespace libcellml
