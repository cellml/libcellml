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
 *
 * @warning The Interpreter class currently supports pure algebraic models and ODE models. NLA and DAE models are not
 * currently supported and neither are models with external variables.
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
     * @brief Initialise the model's variables.
     *
     * Initialise the model's variables. This method is only relevant for algebraic models.
     *
     * @param constants The array of constants to initialise.
     * @param computedConstants The array of computed constants to initialise.
     * @param algebraic The array of algebraic variables to initialise.
     */
    void initialiseVariablesForAlgebraicModel(double *constants, double *computedConstants, double *algebraic) const;

    /**
     * @brief Initialise the model's variables.
     *
     * Initialise the model's variables. This method is only relevant for differential models.
     *
     * @param states The array of states to initialise.
     * @param rates The array of rates to initialise.
     * @param constants The array of constants to initialise.
     * @param computedConstants The array of computed constants to initialise.
     * @param algebraic The array of algebraic variables to initialise.
     */
    void initialiseVariablesForDifferentialModel(double *states, double *rates, double *constants, double *computedConstants, double *algebraic) const;

    /**
     * @brief Compute the model's computed constants.
     *
     * Compute the model's computed constants.
     *
     * @param constants The array of constants to initialise.
     * @param computedConstants The array of computed constants to initialise.
     */
    void computeComputedConstants(double *constants, double *computedConstants) const;

    /**
     * @brief Compute the model's rates.
     *
     * Compute the model's rates. This method is only relevant for differential models.
     *
     * @param voi The value of the variable of integration.
     * @param states The array of states.
     * @param rates The array of rates to compute.
     * @param constants The array of constants to initialise.
     * @param computedConstants The array of computed constants to initialise.
     * @param algebraic The array of algebraic variables to initialise.
     */
    void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic) const;

    /**
     * @brief Compute the model's variables.
     *
     * Compute the model's variables. This method is only relevant for algebraic models.
     *
     * @param constants The array of constants to initialise.
     * @param computedConstants The array of computed constants to initialise.
     * @param algebraic The array of algebraic variables to initialise.
     */
    void computeVariablesForAlgebraicModel(double *constants, double *computedConstants, double *algebraic) const;

    /**
     * @brief Compute the model's variables.
     *
     * Compute the model's variables. This method is only relevant for differential models.
     *
     * @param voi The value of the variable of integration.
     * @param states The array of states.
     * @param rates The array of rates.
     * @param constants The array of constants to initialise.
     * @param computedConstants The array of computed constants to initialise.
     * @param algebraic The array of algebraic variables to initialise.
     */
    void computeVariablesForDifferentialModel(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic) const;

private:
    Interpreter(); /**< Constructor, @private. */

    struct InterpreterImpl;
    InterpreterImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
