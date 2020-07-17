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

    /**
     * @brief Add a dependency to this external @c Variable.
     *
     * Add the given @c Variable as a dependency of this external @c Variable,
     * but only if the given @c Variable or its primary equivalent has not
     * already been added.
     *
     * @param variable The @c Variable to add as a dependency.
     *
     * @return True if the variable was added, false otherwise.
     */
    bool addDependency(const VariablePtr &variable);

    /**
     * @brief Remove the dependency at the given @p index.
     *
     * Remove the dependency with the given @p index. @p index must be in the
     * range [0, \#dependencies).
     *
     * @param index The index of the dependency to remove.
     *
     * @return True if the dependency was removed, false otherwise.
     */
    bool removeDependency(size_t index);

    /**
     * @overload
     *
     * @brief Remove the dependency with the given @p variableName in the
     * @c Component with the given @p componentName in the given @p model.
     *
     * Remove the dependency found that matches the given @p variableName in the
     * @c Component with the given @p componentName in the given @p model.
     *
     * @param model The pointer to the @c Model which contains the dependency to
     * remove.
     * @param componentName The name of the @c Component which contains the
     * dependency to remove.
     * @param variableName The name of the dependency to remove.
     *
     * @return True if the dependency was removed, false otherwise.
     */
    bool removeDependency(const ModelPtr &model,
                          const std::string &componentName,
                          const std::string &variableName);

    /**
     * @overload
     *
     * @brief Remove the dependency with the given pointer.
     *
     * Remove the dependency with the pointer @p variable.
     *
     * @param variable The pointer to the dependency to remove.
     *
     * @return True if the dependency was removed, false otherwise.
     */
    bool removeDependency(const VariablePtr &variable);

    /**
     * @brief Remove all dependencies from this external @c Variable.
     *
     * Clears all dependencies that have been added to this external
     * @c Variable.
     */
    void removeAllDependencies();

    /**
     * @brief Tests to see if the dependency with the given @p variableName in
     * the @c Component with the given @p componentName in the given @p model is
     * contained within this external @c Variable.
     *
     * Tests to see if the dependency with the the given @p variableName in the
     * @c Component with the given @p componentName in the given @p model is
     * contained within this external @c Variable. Returns @c true if the dummy
     * is in the external @c Variable and @c false otherwise.
     *
     * @param model The pointer to the @c Model which contains the dependency to
     * test.
     * @param componentName The name of the @c Component which contains the
     * dependency to test.
     * @param variableName The name of the dependency to test.
     *
     * @return @c true if the dependency is in this external @c Variable and
     * @c false otherwise.
     */
    bool containsDependency(const ModelPtr &model,
                            const std::string &componentName,
                            const std::string &variableName) const;

    /**
     * @overload
     *
     * @brief Tests to see if the dependency with the given pointer is contained
     * within this external @c Variable.
     *
     * Tests to see if the dependency with the given pointer is contained within
     * this external @c Variable. Returns @c true if the dependency is in the
     * external @c Variable and @c false otherwise.
     *
     * @param variable The pointer to the dependency to remove.
     *
     * @return @c true if the dependency is in this external @c Variable and
     * @c false otherwise.
     */
    bool containsDependency(const VariablePtr &variable) const;

    /**
     * @brief Get the dependency at the given @p index.
     *
     * Returns a reference to the dependency at the given @p index. @p index
     * must be in the range [0, \#dependencies).
     *
     * @param index The index of the dependency to return.
     *
     * @return The dependency at the given @p index on success, @c nullptr on
     * failure.
     */
    VariablePtr dependency(size_t index) const;

    /**
     * @overload
     *
     * @brief Get the dependency with the given @p name.
     *
     * Returns the dependency with the given @p variableName in the @c Component
     * with the given @p componentName in the given @p model. If no such
     * dependency is contained withing the external @c Variable, a @c nullptr is
     * returned.
     *
     * @param model The pointer to the @c Model which contains the dependency to
     * retrieve.
     * @param componentName The name of the @c Component which contains the
     * dependency to retrieve.
     * @param variableName The name of the dependency to retrieve.
     *
     * @return The dependency with the given @p variableName in the @c Component
     * with the given @p componentName in the given @p model on success,
     * @c nullptr on failure.
     */
    VariablePtr dependency(const ModelPtr &model,
                           const std::string &componentName,
                           const std::string &variableName) const;

    /**
     * @brief Get the number of dependencies in this external @c Variable.
     *
     * Returns the number of dependencies the external @c Variable contains.
     *
     * @return The number of dependencies.
     */
    size_t dependencyCount() const;

private:
    explicit AnalyserExternalVariable(const VariablePtr &variable); /**< Constructor */

    struct AnalyserExternalVariableImpl;
    AnalyserExternalVariableImpl *mPimpl;
};

} // namespace libcellml
