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

#include <list>
#include <string>

#include "libcellml/logger.h"

namespace libcellml {

class Generator;

/**
 * @brief The GeneratorVariable class.
 *
 * The GeneratorVariable class is for representing a variable in the context
 * of a CellML Generator, i.e. a constant, a computed constant or an algebraic
 * variable.
 */
class LIBCELLML_EXPORT GeneratorVariable
{
    friend class Generator;

public:
    enum class Type
    {
        VARIABLE_OF_INTEGRATION,
        STATE,
        CONSTANT,
        COMPUTED_CONSTANT,
        ALGEBRAIC
    };

    ~GeneratorVariable(); /**< Destructor */
    GeneratorVariable(const GeneratorVariable &rhs) = delete; /**< Copy constructor */
    GeneratorVariable(GeneratorVariable &&rhs) noexcept = delete; /**< Move constructor */
    GeneratorVariable &operator=(GeneratorVariable rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c GeneratorVariable object.
     *
     * Factory method to create a @c GeneratorVariable. Create a generator
     * variable with::
     *
     *   GeneratorVariablePtr generatorVariable = libcellml::GeneratorVariable::create();
     *
     * @return A smart pointer to a @c GeneratorVariable object.
     */
    static GeneratorVariablePtr create() noexcept;

    /**
     * @brief Get the initialising @c Variable for this @c GeneratorVariable.
     *
     * Return the initialising @c Variable of this @c GeneratorVariable. It is
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
     * @brief Get the @c Variable for this @c GeneratorVariable.
     *
     * Return the @c Variable of this @c GeneratorVariable. Its @c Component is
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
     * @brief Get the index of this @c GeneratorVariable.
     *
     * Return the index of this @c GeneratorVariable.
     *
     * @return The index.
     */
    size_t index() const;

    /**
     * @brief Get the @c Type for this @c GeneratorVariable.
     *
     * Return the @c Type of this @c GeneratorVariable.
     *
     * @return The @c Type.
     */
    GeneratorVariable::Type type() const;

private:
    GeneratorVariable(); /**< Constructor */

    struct GeneratorVariableImpl;
    GeneratorVariableImpl *mPimpl;
};

class LIBCELLML_EXPORT GeneratorEquation
{
    friend class Generator;

public:
    enum struct Type
    {
        TRUE_CONSTANT,
        VARIABLE_BASED_CONSTANT,
        RATE,
        ALGEBRAIC
    };

    ~GeneratorEquation(); /**< Destructor */
    GeneratorEquation(const GeneratorEquation &rhs) = delete; /**< Copy constructor */
    GeneratorEquation(GeneratorEquation &&rhs) noexcept = delete; /**< Move constructor */
    GeneratorEquation &operator=(GeneratorEquation rhs) = delete; /**< Assignment operator */

    static GeneratorEquationPtr create() noexcept;

    GeneratorEquation::Type type() const;
    GeneratorEquationAstPtr ast() const;
    std::list<GeneratorEquationPtr> dependencies() const;
    bool isStateRateBased() const;

private:
    GeneratorEquation(); /**< Constructor */

    struct GeneratorEquationImpl;
    GeneratorEquationImpl *mPimpl;
};

/**
 * @brief The Generator class.
 *
 * The Generator class is for representing a CellML Generator.
 */
class LIBCELLML_EXPORT Generator: public Logger
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

    ~Generator() override; /**< Destructor */
    Generator(const Generator &rhs) = delete; /**< Copy constructor */
    Generator(Generator &&rhs) noexcept = delete; /**< Move constructor */
    Generator &operator=(Generator rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Generator object.
     *
     * Factory method to create a @c Generator. Create a generator with::
     *
     *   GeneratorPtr generator = libcellml::Generator::create();
     *
     * @return A smart pointer to a @c Generator object.
     */
    static GeneratorPtr create() noexcept;

    /**
     * @brief Get the @c GeneratorProfile.
     *
     * Get the @c GeneratorProfile used by this @c Generator.
     *
     * @return The @c GeneratorProfile used.
     */
    GeneratorProfilePtr profile();

    /**
     * @brief Set the @c GeneratorProfile.
     *
     * Set the @c GeneratorProfile to be used by this @c Generator.
     *
     * @param profile The @c GeneratorProfile to set.
     */
    void setProfile(const GeneratorProfilePtr &profile);

    /**
     * @brief Process the @c Model.
     *
     * Process the @c Model using this @c Generator.
     *
     * @param model The @c Model to process.
     */
    void processModel(const ModelPtr &model);

    /**
     * @brief Get the @c ModelType of the @c Model.
     *
     * Return the @c ModelType of the @c Model processed by this @c Generator.
     *
     * @return The @c ModelType.
     */
    ModelType modelType() const;

    /**
     * @brief Get the number of states in the @c Model.
     *
     * Return the number of states in the @c Model processed by this
     * @c Generator.
     *
     * @return The number of states.
     */
    size_t stateCount() const;

    /**
     * @brief Get the number of variables in the @c Model.
     *
     * Return the number of variables in the @c Model processed by this
     * @c Generator.
     *
     * @return The number of variables.
     */
    size_t variableCount() const;

    /**
     * @brief Get the variable of integration of the @c Model.
     *
     * Return the @c Variable of integration of the @c Model processed by this
     * @c Generator.
     *
     * @return The @c Type.
     */
    GeneratorVariablePtr voi() const;

    /**
     * @brief Get the state at @p index.
     *
     * Return the state at the index @p index for the @c Model processed by this
     * @c Generator.
     *
     * @param index The index of the state to return.
     */
    GeneratorVariablePtr state(size_t index) const;

    /**
     * @brief Get the variable at @p index.
     *
     * Return the variable at the index @p index for the @c Model processed by
     * this @c Generator.
     *
     * @param index The index of the variable to return.
     */
    GeneratorVariablePtr variable(size_t index) const;

    /**
     * @brief Get the interface code for the @c Model.
     *
     * Return the interface code for the @c Model processed by this
     * @c Generator, using its @c GeneratorProfile.
     *
     * @return The code.
     */
    std::string interfaceCode() const;

    /**
     * @brief Get the implementation code for the @c Model.
     *
     * Return the implementation code for the @c Model processed by this
     * @c Generator, using its @c GeneratorProfile.
     *
     * @return The code.
     */
    std::string implementationCode() const;

private:
    Generator(); /**< Constructor */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl;
};

} // namespace libcellml
