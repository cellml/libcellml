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
 * @brief The AnalyserModel class.
 *
 * The AnalyserModel class is for representing a model in the context of a
 * CellML Analyser.
 */
class LIBCELLML_EXPORT AnalyserModel
{
    friend class Analyser;

public:
    enum class Type
    {
        UNKNOWN,
        ALGEBRAIC,
        ODE,
        INVALID,
        UNDERCONSTRAINED,
        OVERCONSTRAINED,
        UNSUITABLY_CONSTRAINED
    };

    ~AnalyserModel(); /**< Destructor */
    AnalyserModel(const AnalyserModel &rhs) = delete; /**< Copy constructor */
    AnalyserModel(AnalyserModel &&rhs) noexcept = delete; /**< Move constructor */
    AnalyserModel &operator=(AnalyserModel rhs) = delete; /**< Assignment operator */

    /**
     * @brief Test to determine if @c AnalyserModel is a valid model.
     *
     * Test to determine if @c AnalyserModel is a valid model, return @c true if
     * it is a valid model and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel is a valid model, @c false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Get the @c Type of the @c Model.
     *
     * Return the @c Type of the @c Model analysed by an @c Analyser.
     *
     * @return The @c Type.
     */
    Type type() const;

    /**
     * @brief Get the @c Variable of integration of the @c Model.
     *
     * Return the @c Variable of integration of the @c Model analysed by this
     * @c Analyser.
     *
     * @return The @c Variable of integration.
     */
    AnalyserVariablePtr voi() const;

    /**
     * @brief Get the number of states in the @c Model.
     *
     * Return the number of states in the @c Model analysed by this @c Analyser.
     *
     * @return The number of states.
     */
    size_t stateCount() const;

    /**
     * @brief Get the states in the @c Model.
     *
     * Return the states in the @c Model analysed by this @c Analyser.
     *
     * @return The states.
     */
    std::vector<AnalyserVariablePtr> states() const;

    /**
     * @brief Get the state at @p index.
     *
     * Return the state at the index @p index for the @c Model analysed by this
     * @c Analyser.
     *
     * @param index The index of the state to return.
     */
    AnalyserVariablePtr state(size_t index) const;

    /**
     * @brief Get the number of variables in the @c Model.
     *
     * Return the number of variables in the @c Model analysed by this
     * @c Analyser.
     *
     * @return The number of variables.
     */
    size_t variableCount() const;

    /**
     * @brief Get the variables in the @c Model.
     *
     * Return the variables in the @c Model analysed by this @c Analyser.
     *
     * @return The variables.
     */
    std::vector<AnalyserVariablePtr> variables() const;

    /**
     * @brief Get the variable at @p index.
     *
     * Return the variable at the index @p index for the @c Model analysed by
     * this @c Analyser.
     *
     * @param index The index of the variable to return.
     */
    AnalyserVariablePtr variable(size_t index) const;

    /**
     * @brief Get the number of equations in the @c Model.
     *
     * Return the number of equations in the @c Model analysed by this
     * @c Analyser.
     *
     * @return The number of equations.
     */
    size_t equationCount() const;

    /**
     * @brief Get the equations in the @c Model.
     *
     * Return the equations in the @c Model analysed by this @c Analyser.
     *
     * @return The equations.
     */
    std::vector<AnalyserEquationPtr> equations() const;

    /**
     * @brief Get the equation at @p index.
     *
     * Return the equation at the index @p index for the @c Model analysed by
     * this @c Analyser.
     *
     * @param index The index of the equation to return.
     */
    AnalyserEquationPtr equation(size_t index) const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "equal to"
     * function.
     *
     * Test to determine if @c AnalyserModel needs an "equal to" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "equal to" function,
     * @c false otherwise.
     */
    bool needEqFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "not equal to"
     * function.
     *
     * Test to determine if @c AnalyserModel needs a "not equal to" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "not equal to" function,
     * @c false otherwise.
     */
    bool needNeqFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "less than"
     * function.
     *
     * Test to determine if @c AnalyserModel needs a "less than" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "less than" function,
     * @c false otherwise.
     */
    bool needLtFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "less than or equal
     * to" function.
     *
     * Test to determine if @c AnalyserModel needs a "less than or equal to"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "less than or equal to"
     * function, @c false otherwise.
     */
    bool needLeqFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "greater than"
     * function.
     *
     * Test to determine if @c AnalyserModel needs a "greater than" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "greater than" function,
     * @c false otherwise.
     */
    bool needGtFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "greater than or
     * equal to" function.
     *
     * Test to determine if @c AnalyserModel needs a "greater than or equal to"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "greater than or equal to"
     * function, @c false otherwise.
     */
    bool needGeqFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "and" function.
     *
     * Test to determine if @c AnalyserModel needs an "and" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "and" function, @c false
     * otherwise.
     */
    bool needAndFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "or" function.
     *
     * Test to determine if @c AnalyserModel needs an "or" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "or" function, @c false
     * otherwise.
     */
    bool needOrFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "xor" function.
     *
     * Test to determine if @c AnalyserModel needs a "xor" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "xor" function, @c false
     * otherwise.
     */
    bool needXorFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "not" function.
     *
     * Test to determine if @c AnalyserModel needs a "not" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "not" function, @c false
     * otherwise.
     */
    bool needNotFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "minimum" function.
     *
     * Test to determine if @c AnalyserModel needs a "minimum" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "minimum" function, @c false
     * otherwise.
     */
    bool needMinFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "maximum" function.
     *
     * Test to determine if @c AnalyserModel needs a "maximum" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "maximum" function, @c false
     * otherwise.
     */
    bool needMaxFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "secant" function.
     *
     * Test to determine if @c AnalyserModel needs a "secant" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "secant" function, @c false
     * otherwise.
     */
    bool needSecFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "cosecant" function.
     *
     * Test to determine if @c AnalyserModel needs a "cosecant" function, return
     * @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "cosecant" function, @c false
     * otherwise.
     */
    bool needCscFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "cotangent"
     * function.
     *
     * Test to determine if @c AnalyserModel needs a "cotangent" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "cotangent" function,
     * @c false otherwise.
     */
    bool needCotFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "hyperbolic secant"
     * function.
     *
     * Test to determine if @c AnalyserModel needs a "hyperbolic secant"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "hyperbolic secant" function,
     * @c false otherwise.
     */
    bool needSechFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "hyperbolic
     * cosecant" function.
     *
     * Test to determine if @c AnalyserModel needs a "hyperbolic cosecant"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "hyperbolic cosecant"
     * function, @c false otherwise.
     */
    bool needCschFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs a "hyperbolic
     * cotangent" function.
     *
     * Test to determine if @c AnalyserModel needs a "hyperbolic cotangent"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs a "hyperbolic cotangent"
     * function, @c false otherwise.
     */
    bool needCothFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "arc secant"
     * function.
     *
     * Test to determine if @c AnalyserModel needs an "arc secant" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "arc secant" function,
     * @c false otherwise.
     */
    bool needAsecFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "arc cosecant"
     * function.
     *
     * Test to determine if @c AnalyserModel needs an "arc cosecant" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "arc cosecant" function,
     * @c false otherwise.
     */
    bool needAcscFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "arc cotangent"
     * function.
     *
     * Test to determine if @c AnalyserModel needs an "arc cotangent" function,
     * return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "arc cotangent" function,
     * @c false otherwise.
     */
    bool needAcotFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "arc hyperbolic
     * secant" function.
     *
     * Test to determine if @c AnalyserModel needs an "arc hyperbolic secant"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "arc hyperbolic secant"
     * function, @c false otherwise.
     */
    bool needAsechFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "arc hyperbolic
     * cosecant" function.
     *
     * Test to determine if @c AnalyserModel needs an "arc hyperbolic cosecant"
     * function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "arc hyperbolic cosecant"
     * function, @c false otherwise.
     */
    bool needAcschFunction() const;

    /**
     * @brief Test to determine if @c AnalyserModel needs an "arc hyperbolic
     * cotangent" function.
     *
     * Test to determine if @c AnalyserModel needs an "arc hyperbolic
     * cotangent" function, return @c true if it does and @c false otherwise.
     *
     * @return @c true if @c AnalyserModel needs an "arc hyperbolic cotangent"
     * function, @c false otherwise.
     */
    bool needAcothFunction() const;

private:
    AnalyserModel(); /**< Constructor */

    struct AnalyserModelImpl;
    AnalyserModelImpl *mPimpl;
};

} // namespace libcellml
