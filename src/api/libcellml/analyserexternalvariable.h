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

namespace libcellml {

/**
 * @brief The AnalyserExternalVariable class.
 *
 * The AnalyserExternalVariable class is for representing an external variable
 * in the context of a CellML Analyser, i.e. a variable which is not set or
 * computed by a model, but set externally.
 */
class LIBCELLML_EXPORT AnalyserExternalVariable
{
public:
    ~AnalyserExternalVariable(); /**< Destructor */
    AnalyserExternalVariable(const AnalyserExternalVariable &rhs) = delete; /**< Copy constructor */
    AnalyserExternalVariable(AnalyserExternalVariable &&rhs) noexcept = delete; /**< Move constructor */
    AnalyserExternalVariable &operator=(AnalyserExternalVariable rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create an @c AnalyserExternalVariable object.
     *
     * Factory method to create an @c AnalyserExternalVariable. Create an
     * analyser external variable with::
     *
     *   VariablePtr variable = libcellml::Variable::create();
     *   AnalyserExternalVariablePtr analyserExternalVariable = libcellml::AnalyserExternalVariable::create(variable);
     *
     * @return A smart pointer to a @c AnalyserExternalVariable object.
     */
    static AnalyserExternalVariablePtr create(const VariablePtr &variable) noexcept;

private:
    explicit AnalyserExternalVariable(const VariablePtr &variable); /**< Constructor */

    struct AnalyserExternalVariableImpl;
    AnalyserExternalVariableImpl *mPimpl;
};

} // namespace libcellml
