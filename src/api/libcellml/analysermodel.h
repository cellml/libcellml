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
     * Return the @c Type of the @c Model processed by an @c Analyser.
     *
     * @return The @c Type.
     */
    Type type() const;

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
    AnalyserModel(); /**< Constructor */

    struct AnalyserModelImpl;
    AnalyserModelImpl *mPimpl;
};

} // namespace libcellml
