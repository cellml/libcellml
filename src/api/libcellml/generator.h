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

#include <string>

namespace libcellml {

class Generator;

class LIBCELLML_EXPORT GeneratorVariable
{
    friend class Generator;

public:
    enum class Type
    {
        CONSTANT,
        COMPUTED_CONSTANT,
        ALGEBRAIC
    };

    GeneratorVariable(); /**< Constructor */
    ~GeneratorVariable(); /**< Destructor */
    GeneratorVariable(const GeneratorVariable &rhs); /**< Copy constructor */
    GeneratorVariable(GeneratorVariable &&rhs) noexcept; /**< Move constructor */
    GeneratorVariable &operator=(GeneratorVariable rhs); /**< Assignment operator */

    /**
     * @brief Get the @c Variable for this @c GeneratorVariable.
     *
     * Return the @c Variable of this @c GeneratorVariable.
     *
     * @return The @c Variable.
     */
    VariablePtr variable() const;

    /**
     * @brief Get the @c Type for this @c GeneratorVariable.
     *
     * Return the @c Type of this @c GeneratorVariable.
     *
     * @return The @c Type.
     */
    GeneratorVariable::Type type() const;

private:
    void swap(GeneratorVariable &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorVariableImpl;
    GeneratorVariableImpl *mPimpl;
};

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

    Generator(); /**< Constructor */
    ~Generator() override; /**< Destructor */
    Generator(const Generator &rhs); /**< Copy constructor */
    Generator(Generator &&rhs) noexcept; /**< Move constructor */
    Generator &operator=(Generator rhs); /**< Assignment operator */

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
    VariablePtr variableOfIntegration() const;

    /**
     * @brief Get the state at @p index.
     *
     * Return the state at the index @p index for the @c Model processed by this
     * @c Generator.
     *
     * @param index The index of the state to return.
     */
    VariablePtr state(size_t index) const;

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
     * @brief Get the code for the @c Model.
     *
     * Return the code for the @c Model processed by this @c Generator, using
     * its @c GeneratorProfile.
     *
     * @return The code.
     */
    std::string code() const;

private:
    void swap(Generator &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl;
};

} // namespace libcellml
