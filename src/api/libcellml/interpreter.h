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

#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

#include <vector>

namespace libcellml {

/**
 * @brief The Interpreter class.
 *
 * The Interpreter class is for representing a CellML Interpreter.
 */
class LIBCELLML_EXPORT Interpreter
{
public:
    ~Interpreter(); /**< Destructor, @private. */
    Interpreter(const Interpreter &rhs) = delete; /**< Copy constructor, @private. */
    Interpreter(Interpreter &&rhs) noexcept = delete; /**< Move constructor, @private. */
    Interpreter &operator=(Interpreter rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create an @ref Interpreter object.
     *
     * Factory method to create an @ref Interpreter. Create an interpreter with::
     *
     * @code
     *   auto interpreter = libcellml::Interpreter::create();
     * @endcode
     *
     * @return A smart pointer to an @ref Interpreter object.
     */
    static InterpreterPtr create() noexcept;

    /**
     * @brief Get the @ref AnalyserModel.
     *
     * Get the @ref AnalyserModel used by this @ref Interpreter.
     *
     * @return The @ref AnalyserModel used.
     */
    AnalyserModelPtr model();

    /**
     * @brief Set the @ref AnalyserModel.
     *
     * Set the @ref AnalyserModel to be used by this @ref Interpreter.
     *
     * @param model The @ref AnalyserModel to set.
     */
    void setModel(const AnalyserModelPtr &model);

    /**
     * @brief Get the value of the model's variable of integration.
     *
     * Return the value of the model's variable of integration. If no variable of integration is needed to compute the
     * model then 0.0 is returned.
     *
     * @return The value of the variable of integration as a @c double.
     */
    double voi();

    /**
     * @brief Get the model's states.
     *
     * Return the model's states. If the model doesn't have any states then @c nullptr is returned.
     *
     * @return The model's states as a @c std::vector of @c double.
     */
    std::vector<double> states();

    /**
     * @brief Get the model's rates.
     *
     * Return the model's rates. If the model doesn't have any rates then @c nullptr is returned.
     *
     * @return The model's rates as a @c std::vector of @c double.
     */
    std::vector<double> rates();

    /**
     * @brief Get the model's variables.
     *
     * Return the model's variables.
     *
     * @return The model's variables as a @c std::vector of @c double.
     */
    std::vector<double> variables();

    /**
     * @brief Initialise the model's variables.
     *
     * Initialise the model's variables.
     *
     * @sa computeComputedConstants, computeRates, computeVariables
     */
    void initialiseVariables();

    /**
     * @brief Compute the model's computed constants.
     *
     * Compute the model's computed constants.
     *
     * @sa initialiseVariables, computeRates, computeVariables
     */
    void computeComputedConstants();

    /**
     * @brief Compute the model's rates.
     *
     * Compute the model's rates.
     *
     * @sa initialiseVariables, computeComputedConstants, computeVariables
     */
    void computeRates();

    /**
     * @brief Compute the model's variables.
     *
     * Compute the model's variables.
     *
     * @sa initialiseVariables, computeComputedConstants, computeRates
     */
    void computeVariables();

private:
    Interpreter(); /**< Constructor, @private. */

    struct InterpreterImpl;
    InterpreterImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
