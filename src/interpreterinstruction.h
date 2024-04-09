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

#include <memory>

namespace libcellml {

class InterpreterInstruction; /**< Forward declaration of InterpreterInstruction class. */
using InterpreterInstructionPtr = std::shared_ptr<InterpreterInstruction>; /**< Type definition for shared InterpreterInstruction pointer. */

/**
 * @brief The InterpreterInstruction class.
 *
 * The InterpreterInstruction class is for representing a CellML Interpreter Instruction.
 */
class InterpreterInstruction
{
public:
    ~InterpreterInstruction(); /**< Destructor, @private. */
    InterpreterInstruction(const InterpreterInstruction &rhs) = delete; /**< Copy constructor, @private. */
    InterpreterInstruction(InterpreterInstruction &&rhs) noexcept = delete; /**< Move constructor, @private. */
    InterpreterInstruction &operator=(InterpreterInstruction rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create an @ref InterpreterInstruction object.
     *
     * Factory method to create an @ref InterpreterInstruction. Create an interpreter with::
     *
     * @code
     *   auto interpreterInstruction = libcellml::InterpreterInstruction::create();
     * @endcode
     *
     * @return A smart pointer to an @ref InterpreterInstruction object.
     */
    static InterpreterInstructionPtr create() noexcept;

private:
    InterpreterInstruction(); /**< Constructor, @private. */

    struct InterpreterInstructionImpl;
    InterpreterInstructionImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
