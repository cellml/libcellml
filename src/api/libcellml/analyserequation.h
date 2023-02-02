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
 * @brief The AnalyserEquation class.
 *
 * The AnalyserEquation class is for representing an equation in the context of
 * a CellML Analyser.
 */
class LIBCELLML_EXPORT AnalyserEquation
{
    friend class Analyser;

public:
    /**
     * @brief The type of an equation.
     *
     * The type of an equation, i.e. whether it is used to compute a true
     * constant, a variable-based constant, a rate, an algebraic variable,
     * or whether it is an equation that is computed externally.
     */
    enum class Type
    {
        TRUE_CONSTANT, /**< An equation that computes a true constant, e.g. x = 3. */
        VARIABLE_BASED_CONSTANT, /**< An equation that computes a variable-based constant, e.g. x = y+z where y and z are true constants. */
        ODE, /**< An equation that computes an ODE, e.g. d(y)/dt = f(t, x). */
        NLA, /**< An equation that computes one or several algebraic variables, e.g. x+y = f(z) where x and y are known, but not z.. */
        ALGEBRAIC, /**< An equation that computes an algebraic variable, e.g. y = f(x). */
        EXTERNAL /**< An equation that is computed externally. */
    };

    ~AnalyserEquation(); /**< Destructor, @private. */
    AnalyserEquation(const AnalyserEquation &rhs) = delete; /**< Copy constructor, @private. */
    AnalyserEquation(AnalyserEquation &&rhs) noexcept = delete; /**< Move constructor, @private. */
    AnalyserEquation &operator=(AnalyserEquation rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Get the @c Type of this @c AnalyserEquation.
     *
     * Return the @c Type of this @c AnalyserEquation.
     *
     * @return The @c Type.
     */
    Type type() const;

    /**
     * @brief Get the @c AnalyserEquationAst for this @c AnalyserEquation.
     *
     * Return the @c AnalyserEquationAst for this @c AnalyserEquation.
     *
     * @return The @c AnalyserEquationAst.
     */
    AnalyserEquationAstPtr ast() const;

    /**
     * @brief Get the list of @c AnalyserEquation dependencies.
     *
     * Return the list of @c AnalyserEquation items which correspond to the
     * equations on which this @c AnalyserEquation depends.
     *
     * @return The list of @c AnalyserEquation dependencies.
     */
    std::vector<AnalyserEquationPtr> dependencies() const;

    /**
     * @brief Test to determine if this @c AnalyserEquation relies on states
     * and/or rates.
     *
     * Test to determine if this @c AnalyserEquation relies on states and/or
     * rates, return @c true if it does and @c false otherwise.
     *
     * @return @c true if this @c AnalyserEquation relies on states and/or
     * rates, @c false otherwise.
     */
    bool isStateRateBased() const;

    /**
     * @brief Get the @c AnalyserVariable for this @c AnalyserEquation.
     *
     * Return the @c AnalyserVariable for this @c AnalyserEquation.
     *
     * @return The @c AnalyserVariable.
     */
    AnalyserVariablePtr variable() const;

private:
    AnalyserEquation(); /**< Constructor, @private. */

    struct AnalyserEquationImpl;
    AnalyserEquationImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
