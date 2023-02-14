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

#include "libcellml/analyser.h"

namespace libcellml {

/**
 * @brief The AnalyserVariable class.
 *
 * The AnalyserVariable class is for representing a variable in the context of a
 * CellML Analyser.
 */
class LIBCELLML_EXPORT AnalyserVariable
{
    friend class Analyser;

public:
    /**
     * @brief The type of a variable.
     *
     * The type of a variable, i.e. whether it is the variable of integration, a
     * state, a constant, a computed constant, an algebraic variable, or an
     * external variable.
     */
    enum class Type
    {
        VARIABLE_OF_INTEGRATION, /**< The variable is the variable of integration. */
        STATE, /**< The variable is a state. */
        CONSTANT, /**< The variable is a constant (e.g. x = 3). */
        COMPUTED_CONSTANT, /**< The variable is a computed constant (e.g. x = 3+5, x = 3+z, x = y+z where y and z are constants). */
        ALGEBRAIC, /**< The variable is an algebraic variable. */
        EXTERNAL /**< The variable is an external variable, i.e. not computed as part of the model. */
    };

    ~AnalyserVariable(); /**< Destructor, @private. */
    AnalyserVariable(const AnalyserVariable &rhs) = delete; /**< Copy constructor, @private. */
    AnalyserVariable(AnalyserVariable &&rhs) noexcept = delete; /**< Move constructor, @private. */
    AnalyserVariable &operator=(AnalyserVariable rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Get the @c Type of this @c AnalyserVariable.
     *
     * Return the @c Type of this @c AnalyserVariable.
     *
     * @return The @c Type.
     */
    Type type() const;

    /**
     * @brief Get the index of this @c AnalyserVariable.
     *
     * Return the index of this @c AnalyserVariable.
     *
     * @return The index.
     */
    size_t index() const;

    /**
     * @brief Get the initialising @c Variable for this @c AnalyserVariable.
     *
     * Return the initialising @c Variable for this @c AnalyserVariable. It is
     * used to retrieve the initial value of the @c Variable, if there is one.
     * It may or may not be the same @c Variable as the one returned by
     * @sa variable. If it is not the same (e.g., a state variable is
     * initialised in one component and computed in another) then the initial
     * value retrieved from this variable may have to be scaled to account for
     * the variables' units not being equivalent (e.g., a variable is expressed
     * in millivolts and its connected variable is expressed in volts, so the
     * initial value will have to be multiplied or divided by 1000).
     *
     * @sa variable
     * @sa scalingFactor
     *
     * @return The initialising @c Variable, if there is one, or @c nullptr.
     */
    VariablePtr initialisingVariable() const;

    /**
     * @brief Get the (primary) @c Variable for this @c AnalyserVariable.
     *
     * Return the (primary) @c Variable for this @c AnalyserVariable. Its
     * @c Component is the one in which the @c Variable is first defined (in the
     * case of the variable of integration), initialised (in the case of a
     * constant) or computed (in the case of a state, computed constant or
     * algebraic variable). It may or may not be the same @c Variable as the one
     * returned by @sa initialisingVariable (e.g., a state variable is
     * initialised in one component and computed in another).
     *
     * @sa initialisingVariable
     *
     * @return The @c Variable.
     */
    VariablePtr variable() const;

    /**
     * @brief Get the number of equations used to compute this @c AnalyserVariable.
     *
     * Return the number of equations used to compute this @c AnalyserVariable.
     *
     * @return The number of equations used to compute this @c AnalyserVariable.
     */
    size_t equationCount() const;

    /**
     * @brief Get the equations used to compute this @c AnalyserVariable.
     *
     * Return the equations used to compute this @c AnalyserVariable.
     *
     * @return The equations.
     */
    std::vector<AnalyserEquationPtr> equations() const;

    /**
     * @brief Get the equation, at @p index, used to compute this @c AnalyserVariable.
     *
     * Return the equation, at @p index, used to compute this @c AnalyserVariable..
     *
     * @param index The index of the equation to return.
     *
     * @return The equation, at @p index, on success, @c nullptr on failure.
     */
    AnalyserEquationPtr equation(size_t index) const;

private:
    AnalyserVariable(); /**< Constructor, @private. */

    struct AnalyserVariableImpl;
    AnalyserVariableImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
