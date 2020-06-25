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

#include <list>

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
    enum struct Type
    {
        TRUE_CONSTANT,
        VARIABLE_BASED_CONSTANT,
        RATE,
        ALGEBRAIC
    };

    ~AnalyserEquation(); /**< Destructor */
    AnalyserEquation(const AnalyserEquation &rhs) = delete; /**< Copy constructor */
    AnalyserEquation(AnalyserEquation &&rhs) noexcept = delete; /**< Move constructor */
    AnalyserEquation &operator=(AnalyserEquation rhs) = delete; /**< Assignment operator */

    Type type() const;
    AnalyserEquationAstPtr ast() const;
    std::list<AnalyserEquationPtr> dependencies() const;
    bool isStateRateBased() const;

private:
    AnalyserEquation(); /**< Constructor */

    struct AnalyserEquationImpl;
    AnalyserEquationImpl *mPimpl;
};

} // namespace libcellml
