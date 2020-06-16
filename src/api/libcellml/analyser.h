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

#include "libcellml/logger.h"

namespace libcellml {

class Analyser;

/**
 * @brief The AnalyserVariable class.
 *
 * The AnalyserVariable class is for representing a variable in the context
 * of a CellML Analyser, i.e. a constant, a computed constant or an algebraic
 * variable.
 */
class LIBCELLML_EXPORT AnalyserVariable
{
    friend class Analyser;

public:
    enum class Type
    {
        VARIABLE_OF_INTEGRATION,
        STATE,
        CONSTANT,
        COMPUTED_CONSTANT,
        ALGEBRAIC
    };

    ~AnalyserVariable(); /**< Destructor */
    AnalyserVariable(const AnalyserVariable &rhs) = delete; /**< Copy constructor */
    AnalyserVariable(AnalyserVariable &&rhs) noexcept = delete; /**< Move constructor */
    AnalyserVariable &operator=(AnalyserVariable rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create an @c AnalyserVariable object.
     *
     * Factory method to create a @c AnalyserVariable. Create an analyser
     * variable with::
     *
     *   AnalyserVariablePtr AnalyserVariable = libcellml::AnalyserVariable::create();
     *
     * @return A smart pointer to an @c AnalyserVariable object.
     */
    static AnalyserVariablePtr create() noexcept;

    /**
     * @brief Get the initialising @c Variable for this @c AnalyserVariable.
     *
     * Return the initialising @c Variable of this @c AnalyserVariable. It is
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
     * @brief Get the @c Variable for this @c AnalyserVariable.
     *
     * Return the @c Variable of this @c AnalyserVariable. Its @c Component is
     * the one in which the @c Variable is first defined (in the case of the
     * variable of integration), initialised (in the case of a constant) or
     * computed (in the case of a state, computed constant or algebraic
     * variable). It may or may not be the same @c Variable as the one returned
     * by @sa initialisingVariable (e.g., a state variable is initialised in one
     * component and computed in another).
     *
     * @sa initialisingVariable
     *
     * @return The @c Variable.
     */
    VariablePtr variable() const;

    /**
     * @brief Get the @c Type for this @c AnalyserVariable.
     *
     * Return the @c Type of this @c AnalyserVariable.
     *
     * @return The @c Type.
     */
    AnalyserVariable::Type type() const;

private:
    AnalyserVariable(); /**< Constructor */

    struct AnalyserVariableImpl;
    AnalyserVariableImpl *mPimpl;
};

/**
 * @brief The Analyser class.
 *
 * The Analyser class is for representing a CellML Analyser.
 */
class LIBCELLML_EXPORT Analyser: public Logger
{
public:
    enum class ModelType
    {
        UNKNOWN,
        ALGEBRAIC,
        ODE,
        INVALID,
        UNDERCONSTRAINED,
        OVERCONSTRAINED,
        UNSUITABLY_CONSTRAINED
    };

    ~Analyser() override; /**< Destructor */
    Analyser(const Analyser &rhs) = delete; /**< Copy constructor */
    Analyser(Analyser &&rhs) noexcept = delete; /**< Move constructor */
    Analyser &operator=(Analyser rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Analyser object.
     *
     * Factory method to create a @c Analyser.  Create an analyser with::
     *
     *   AnalyserPtr analyser = libcellml::Analyser::create();
     *
     * @return A smart pointer to a @c Analyser object.
     */
    static AnalyserPtr create() noexcept;

    /**
     * @brief Process the @c Model.
     *
     * Process the @c Model using this @c Analyser.
     *
     * @param model The @c Model to process.
     */
    void processModel(const ModelPtr &model);

    /**
     * @brief Get the @c ModelType of the @c Model.
     *
     * Return the @c ModelType of the @c Model processed by this @c Analyser.
     *
     * @return The @c ModelType.
     */
    ModelType modelType() const;

    /**
     * @brief Get the number of states in the @c Model.
     *
     * Return the number of states in the @c Model processed by this
     * @c Analyser.
     *
     * @return The number of states.
     */
    size_t stateCount() const;

    /**
     * @brief Get the number of variables in the @c Model.
     *
     * Return the number of variables in the @c Model processed by this
     * @c Analyser.
     *
     * @return The number of variables.
     */
    size_t variableCount() const;

    /**
     * @brief Get the variable of integration of the @c Model.
     *
     * Return the @c Variable of integration of the @c Model processed by this
     * @c Analyser.
     *
     * @return The @c Type.
     */
    AnalyserVariablePtr voi() const;

    /**
     * @brief Get the state at @p index.
     *
     * Return the state at the index @p index for the @c Model processed by this
     * @c Analyser.
     *
     * @param index The index of the state to return.
     */
    AnalyserVariablePtr state(size_t index) const;

    /**
     * @brief Get the variable at @p index.
     *
     * Return the variable at the index @p index for the @c Model processed by
     * this @c Analyser.
     *
     * @param index The index of the variable to return.
     */
    AnalyserVariablePtr variable(size_t index) const;

private:
    Analyser(); /**< Constructor */

    struct AnalyserImpl;
    AnalyserImpl *mPimpl;
};

} // namespace libcellml
