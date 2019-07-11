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
        STATE,
        CONSTANT,
        COMPUTED_CONSTANT,
        ALGEBRAIC
    };

    GeneratorVariable(); /**< Constructor */
    ~GeneratorVariable(); /**< Destructor */
    GeneratorVariable(const GeneratorVariable &rhs); /**< Copy constructor */
    GeneratorVariable(GeneratorVariable &&rhs) noexcept; /**< Move constructor */
    GeneratorVariable &operator=(GeneratorVariable rhs); /**< Assignment operator */

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

    void setProfile(const GeneratorProfilePtr &profile);

    void processModel(const ModelPtr &model);

    ModelType modelType() const;

    size_t stateCount() const;
    size_t variableCount() const;

    VariablePtr variableOfIntegration() const;
    GeneratorVariablePtr state(size_t index) const;
    GeneratorVariablePtr variable(size_t index) const;

    std::string code() const;

private:
    void swap(Generator &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl;
};

} // namespace libcellml
