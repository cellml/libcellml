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
     * @brief Add an @c AnalyserExternalVariable to this @c Analyser.
     *
     * Add the given @c AnalyserExternalVariable to this @c Analyser, but only
     * if the given @c AnalyserExternalVariable or its primary equivalent has
     * not already been added.
     *
     * @param variable The @c AnalyserExternalVariable to add.
     *
     * @return True if the variable was added, false otherwise.
     */
    bool addExternalVariable(const AnalyserExternalVariablePtr &externalVariable);

    /**
     * @brief Remove the @c AnalyserExternalVariable at the given @p index.
     *
     * Remove the @c AnalyserExternalVariable with the given @p index. @p index
     * must be in the range [0, \#externalVariables).
     *
     * @param index The index of the @c AnalyserExternalVariable to remove.
     *
     * @return True if the @c AnalyserExternalVariable was removed, false
     * otherwise.
     */
    bool removeExternalVariable(size_t index);

    /**
     * @overload
     *
     * @brief Remove the @c AnalyserExternalVariable with the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model.
     *
     * Remove the @c AnalyserExternalVariable found that matches the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model.
     *
     * @param model The pointer to the @c Model which contains the
     * @c AnalyserExternalVariable to remove.
     * @param componentName The name of the @c Component which contains the
     * @c AnalyserExternalVariable to remove.
     * @param variableName The name of the @c AnalyserExternalVariable to
     * remove.
     *
     * @return True if the @c AnalyserExternalVariable was removed, false
     * otherwise.
     */
    bool removeExternalVariable(const ModelPtr &model,
                                const std::string &componentName,
                                const std::string &variableName);

    /**
     * @overload
     *
     * @brief Remove the @c AnalyserExternalVariable with the given pointer.
     *
     * Remove the @c AnalyserExternalVariable with the pointer
     * @p externalVariable.
     *
     * @param variable The pointer to the @c AnalyserExternalVariable to remove.
     *
     * @return True if the @c AnalyserExternalVariable was removed, false
     * otherwise.
     */
    bool removeExternalVariable(const AnalyserExternalVariablePtr &externalVariable);

    /**
     * @brief Remove all @c AnalyserExternalVariable items from this
     * @c Analyser.
     *
     * Clears all @c AnalyserExternalVariable items that have been added to this
     * @c Analyser.
     */
    void removeAllExternalVariables();

    /**
     * @brief Tests to see if the @c AnalyserExternalVariable with the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model is contained within this @c Analyser.
     *
     * Tests to see if the @c AnalyserExternalVariable with the the given
     * @p variableName in the @c Component with the given @p componentName in
     * the given @p model is contained within this @c Analyser. Returns @c true
     * if the @c AnalyserExternalVariable is in the @c Analyser and @c false
     * otherwise.
     *
     * @param model The pointer to the @c Model which contains the
     * @c AnalyserExternalVariable to test.
     * @param componentName The name of the @c Component which contains the
     * @c AnalyserExternalVariable to test.
     * @param variableName The name of the @c AnalyserExternalVariable to test.
     *
     * @return @c true if the @c AnalyserExternalVariable is in this @c Analyser
     * and @c false otherwise.
     */
    bool containsExternalVariable(const ModelPtr &model,
                                  const std::string &componentName,
                                  const std::string &variableName) const;

    /**
     * @overload
     *
     * @brief Tests to see if the @c AnalyserExternalVariable with the given
     * pointer is contained within this @c Analyser.
     *
     * Tests to see if the @c AnalyserExternalVariable with the given pointer is
     * contained within this @c Analyser. Returns @c true if the
     * @c AnalyserExternalVariable is in the @c Analyser and @c false otherwise.
     *
     * @param variable The pointer to the @c AnalyserExternalVariable to remove.
     *
     * @return @c true if the @c AnalyserExternalVariable is in this @c Analyser
     * and @c false otherwise.
     */
    bool containsExternalVariable(const AnalyserExternalVariablePtr &externalVariable) const;

    /**
     * @brief Get the @c AnalyserExternalVariable at the given @p index.
     *
     * Returns a reference to the @c AnalyserExternalVariable at the given
     * @p index. @p index must be in the range [0, \#externalVariables).
     *
     * @param index The index of the @c AnalyserExternalVariable to return.
     *
     * @return The @c AnalyserExternalVariable at the given @p index on success,
     * @c nullptr on failure.
     */
    AnalyserExternalVariablePtr externalVariable(size_t index) const;

    /**
     * @overload
     *
     * @brief Get the @c AnalyserExternalVariable with the given @p name.
     *
     * Returns the @c AnalyserExternalVariable with the given @p variableName in
     * the @c Component with the given @p componentName in the given @p model.
     * If no such @c AnalyserExternalVariable is contained withing the
     * @c Analyser, a @c nullptr is returned.
     *
     * @param model The pointer to the @c Model which contains the
     * @c AnalyserExternalVariable to retrieve.
     * @param componentName The name of the @c Component which contains the
     * @c AnalyserExternalVariable to retrieve.
     * @param variableName The name of the @c AnalyserExternalVariable to
     * retrieve.
     *
     * @return The @c AnalyserExternalVariable with the given @p variableName in
     * the @c Component with the given @p componentName in the given @p model on
     * success, @c nullptr on failure.
     */
    AnalyserExternalVariablePtr externalVariable(const ModelPtr &model,
                                                 const std::string &componentName,
                                                 const std::string &variableName) const;

    /**
     * @brief Get the number of @c AnalyserExternalVariable items in this
     * @c Analyser.
     *
     * Returns the number of @c AnalyserExternalVariable items the @c Analyser
     * contains.
     *
     * @return The number of @c AnalyserExternalVariable items.
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