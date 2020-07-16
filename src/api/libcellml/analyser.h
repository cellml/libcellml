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

/**
 * @brief The Analyser class.
 *
 * The Analyser class is for representing a CellML Analyser.
 */
class LIBCELLML_EXPORT Analyser: public Logger
{
public:
    ~Analyser() override; /**< Destructor */
    Analyser(const Analyser &rhs) = delete; /**< Copy constructor */
    Analyser(Analyser &&rhs) noexcept = delete; /**< Move constructor */
    Analyser &operator=(Analyser rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create an @c Analyser object.
     *
     * Factory method to create an @c Analyser.  Create an analyser with::
     *
     *   AnalyserPtr analyser = libcellml::Analyser::create();
     *
     * @return A smart pointer to an @c Analyser object.
     */
    static AnalyserPtr create() noexcept;

    /**
     * @brief Analyse the @c Model.
     *
     * Analyse the @c Model using this @c Analyser.
     *
     * @param model The @c Model to analyse.
     */
    void analyseModel(const ModelPtr &model);

    /**
     * @brief Add an external @c Variable to this @c Analyser.
     *
     * Add the given @c Variable as an external @c Variable of this @c Analyser,
     * but only if the given @c Variable or its primary equivalent has not
     * already been added.
     *
     * @param variable The @c Variable to add as an external @c Variable.
     *
     * @return True if the variable was added, false otherwise.
     */
    bool addExternalVariable(const VariablePtr &variable);

    /**
     * @brief Remove the external @c Variable at the given @p index.
     *
     * Remove the external @c Variable with the given @p index. @p index must
     * be in the range [0, \#externalVariables).
     *
     * @param index The index of the external @c Variable to remove.
     *
     * @return True if the external @c Variable was removed, false otherwise.
     */
    bool removeExternalVariable(size_t index);

    /**
     * @overload
     *
     * @brief Remove the external @c Variable with the given @p variableName in
     * the @c Component with the given @p componentName in the given @p model.
     *
     * Remove the external @c Variable found that matches the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model.
     *
     * @param model The pointer to the @c Model which contains the external
     * @c Variable to remove.
     * @param componentName The name of the @c Component which contains the
     * external @c Variable to remove.
     * @param variableName The name of the external @c Variable to remove.
     *
     * @return True if the external @c Variable was removed, false otherwise.
     */
    bool removeExternalVariable(const ModelPtr &model,
                                const std::string &componentName,
                                const std::string &variableName);

    /**
     * @overload
     *
     * @brief Remove the external @c Variable with the given pointer.
     *
     * Remove the external @c Variable with the pointer @p variable.
     *
     * @param variable The pointer to the external @c Variable to remove.
     *
     * @return True if the external @c Variable was removed, false otherwise.
     */
    bool removeExternalVariable(const VariablePtr &variable);

    /**
     * @brief Remove all external @c Variable items from this @c Analyser.
     *
     * Clears all external @c Variable items that have been added to this
     * @c Analyser.
     */
    void removeAllExternalVariables();

    /**
     * @brief Tests to see if the external @c Variable with the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model is contained within this @c Analyser.
     *
     * Tests to see if the external @c Variable with the the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model is contained within this @c Analyser. Returns @c true
     * if the external @c Variable is in the @c Analyser and @c false otherwise.
     *
     * @param model The pointer to the @c Model which contains the external
     * @c Variable to remove.
     * @param componentName The name of the @c Component which contains the
     * external @c Variable to remove.
     * @param variableName The name of the external @c Variable to remove.
     *
     * @return @c true if the external @c Variable is in this @c Analyser and
     * @c false otherwise.
     */
    bool containsExternalVariable(const ModelPtr &model,
                                  const std::string &componentName,
                                  const std::string &variableName) const;

    /**
     * @overload
     *
     * @brief Tests to see if the external @c Variable Variable with the given
     * pointer is contained within this @c Analyser.
     *
     * Tests to see if the external @c Variable with the given pointer is
     * contained within this @c Analyser. Returns @c true if the external
     * @c Variable is in the @c Analyser and @c false otherwise.
     *
     * @param variable The pointer to the external @c Variable to remove.
     *
     * @return @c true if the external @c Variable is in this @c Analyser and
     * @c false otherwise.
     */
    bool containsExternalVariable(const VariablePtr &variable) const;

    /**
     * @brief Get the number of external @c Variable items in this @c Analyser.
     *
     * Returns the number of external @c Variable items the @c Analyser
     * contains.
     *
     * @return The number of external @c Variable items.
     */
    size_t externalVariableCount() const;

    /**
     * @brief Get the analysed model.
     *
     * @return The analysed model for the @c Model analysed by this @c Analyser.
     */
    AnalyserModelPtr model() const;

private:
    Analyser(); /**< Constructor */

    struct AnalyserImpl;
    AnalyserImpl *mPimpl;
};

} // namespace libcellml
