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
 * @brief The Generator class.
 *
 * The Generator class is for representing a CellML Generator.
 */
class LIBCELLML_EXPORT Generator: public Logger
{
public:
    ~Generator(); /**< Destructor, @private. */
    Generator(const Generator &rhs) = delete; /**< Copy constructor, @private. */
    Generator(Generator &&rhs) noexcept = delete; /**< Move constructor, @private. */
    Generator &operator=(Generator rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create a @ref Generator object.
     *
     * Factory method to create a @ref Generator. Create a generator with::
     *
     * @code
     *   auto generator = libcellml::Generator::create();
     * @endcode
     *
     * @return A smart pointer to a @ref Generator object.
     */
    static GeneratorPtr create() noexcept;

    /**
     * @brief Get the @ref GeneratorProfile.
     *
     * Get the @ref GeneratorProfile used by this @ref Generator.
     *
     * @return The @ref GeneratorProfile used.
     */
    GeneratorProfilePtr profile();

    /**
     * @brief Set the @ref GeneratorProfile.
     *
     * Set the @ref GeneratorProfile to be used by this @ref Generator.
     *
     * @param profile The @ref GeneratorProfile to set.
     */
    void setProfile(const GeneratorProfilePtr &profile);

    /**
     * @brief Test if the given @p variable is tracked.
     *
     * Test if the given @p variable is tracked.
     *
     * @param variable The pointer to the @ref AnalyserVariable to test.
     *
     * @return @c true if the variable is tracked, @c false otherwise.
     */
    bool isTrackedVariable(const AnalyserVariablePtr &variable);

    /**
     * @brief Test if the given @p variable is untracked.
     *
     * Test if the given @p variable is untracked.
     *
     * @param variable The pointer to the @ref AnalyserVariable to test.
     *
     * @return @c true if the variable is untracked, @c false otherwise.
     */
    bool isUntrackedVariable(const AnalyserVariablePtr &variable);

    /**
     * @brief Track the given @p variable.
     *
     * Track the given @p variable. This will add the variable to the list of tracked variables.
     *
     * @param variable The pointer to the @ref AnalyserVariable to track.
     */
    void trackVariable(const AnalyserVariablePtr &variable);

    /**
     * @brief Untrack the given @p variable.
     *
     * Untrack the given @p variable. This will remove the variable from the list of tracked variables.
     *
     * @param variable The pointer to the @ref AnalyserVariable to untrack.
     */
    void untrackVariable(const AnalyserVariablePtr &variable);

    /**
     * @brief Track all the constants in the given @p model.
     *
     * Track all the constants in the given @p model. This will add all the constants in the model to the list of
     * tracked variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the constants are to be tracked.
     */
    void trackAllConstants(const AnalyserModelPtr &model);

    /**
     * @brief Untrack all the constants in the given @p model.
     *
     * Untrack all the constants in the given @p model. This will remove all the constants in the model from the list of
     * tracked variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the constants are to be untracked.
     */
    void untrackAllConstants(const AnalyserModelPtr &model);

    /**
     * @brief Track all the computed constants in the given @p model.
     *
     * Track all the computed constants in the given @p model. This will add all the computed constants in the model to
     * the list of tracked variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the computed constants are to be tracked.
     */
    void trackAllComputedConstants(const AnalyserModelPtr &model);

    /**
     * @brief Untrack all the computed constants in the given @p model.
     *
     * Untrack all the computed constants in the given @p model. This will remove all the computed constants in the model
     * from the list of tracked variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the computed constants are to be untracked.
     */
    void untrackAllComputedConstants(const AnalyserModelPtr &model);

    /**
     * @brief Track all the algebraic variables in the given @p model.
     *
     * Track all the algebraic variables in the given @p model. This will add all the algebraic variables in the model to
     * the list of tracked variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the algebraic variables are to be tracked.
     */
    void trackAllAlgebraic(const AnalyserModelPtr &model);

    /**
     * @brief Untrack all the algebraic variables in the given @p model.
     *
     * Untrack all the algebraic variables in the given @p model. This will remove all the algebraic variables in the
     * model from the list of tracked variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the algebraic variables are to be untracked.
     */
    void untrackAllAlgebraic(const AnalyserModelPtr &model);

    /**
     * @brief Track all the variables in the given @p model.
     *
     * Track all the variables in the given @p model. This will add all the variables in the model to the list of
     * tracked variables. This includes all the constants, computed constants, and algebraic variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the variables are to be tracked.
     */
    void trackAllVariables(const AnalyserModelPtr &model);

    /**
     * @brief Untrack all the variables in the given @p model.
     *
     * Untrack all the variables in the given @p model. This will remove all the variables in the model from the list of
     * tracked variables. This includes all the constants, computed constants, and algebraic variables.
     *
     * @param model The pointer to the @ref AnalyserModel which all the variables are to be untracked.
     */
    void untrackAllVariables(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of tracked constants in the given @p model.
     *
     * Get the number of tracked constants in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of tracked constants.
     *
     * @return The number of tracked constants in the model.
     */
    size_t trackedConstantCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of untracked constants in the given @p model.
     *
     * Get the number of untracked constants in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of untracked constants.
     *
     * @return The number of untracked constants in the model.
     */
    size_t untrackedConstantCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of tracked computed constants in the given @p model.
     *
     * Get the number of tracked computed constants in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of tracked computed constants.
     *
     * @return The number of tracked computed constants in the model.
     */
    size_t trackedComputedConstantCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of untracked computed constants in the given @p model.
     *
     * Get the number of untracked computed constants in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of untracked computed constants.
     *
     * @return The number of untracked computed constants in the model.
     */
    size_t untrackedComputedConstantCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of tracked algebraic variables in the given @p model.
     *
     * Get the number of tracked algebraic variables in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of tracked algebraic variables.
     *
     * @return The number of tracked algebraic variables in the model.
     */
    size_t trackedAlgebraicCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of untracked algebraic variables in the given @p model.
     *
     * Get the number of untracked algebraic variables in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of untracked algebraic variables.
     *
     * @return The number of untracked algebraic variables in the model.
     */
    size_t untrackedAlgebraicCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of tracked variables in the given @p model.
     *
     * Get the number of tracked variables in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of tracked variables.
     *
     * @return The number of tracked variables in the model.
     */
    size_t trackedVariableCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the number of untracked variables in the given @p model.
     *
     * Get the number of untracked variables in the given @p model.
     *
     * @param model The pointer to the @ref AnalyserModel for which to get the number of untracked variables.
     *
     * @return The number of untracked variables in the model.
     */
    size_t untrackedVariableCount(const AnalyserModelPtr &model);

    /**
     * @brief Get the interface code for the @ref AnalyserModel.
     *
     * Return the interface code for the @ref AnalyserModel, using the @ref GeneratorProfile.
     *
     * @param model The @ref AnalyserModel for which we want to generate some interface code.
     *
     * @return The interface code as a @c std::string.
     */
    std::string interfaceCode(const AnalyserModelPtr &model);

    /**
     * @brief Get the implementation code for the @ref AnalyserModel.
     *
     * Return the implementation code for the @ref AnalyserModel, using the @ref GeneratorProfile.
     *
     * @param model The @ref AnalyserModel for which we want to generate some implementation code.
     *
     * @return The implementation code as a @c std::string.
     */
    std::string implementationCode(const AnalyserModelPtr &model);

    /**
     * @brief Get the equation code for the given @ref AnalyserEquationAst.
     *
     * Return the equation code for the given @ref AnalyserEquationAst using @ref GeneratorProfile.
     *
     * @param ast The @ref AnalyserEquationAst for which we want to generate the equation code.
     * @param generatorProfile The @ref GeneratorProfile, if any, to use to generate the equation code. If no
     * @ref GeneratorProfile is provided then the default @ref GeneratorProfile is used.
     *
     * @return The equation code as a @c std::string.
     */
    static std::string equationCode(const AnalyserEquationAstPtr &ast,
                                    const GeneratorProfilePtr &generatorProfile);

    /**
     * @brief Get the equation code for the given @ref AnalyserEquationAst using a default @ref GeneratorProfile.
     *
     * Return the equation code for the given @ref AnalyserEquationAst using a default @ref GeneratorProfile.
     *
     * @param ast The @ref AnalyserEquationAst for which we want to generate the equation code.
     *
     * @return The equation code as a @c std::string.
     */
    static std::string equationCode(const AnalyserEquationAstPtr &ast);

private:
    Generator(); /**< Constructor, @private. */

    struct GeneratorImpl;

    GeneratorImpl *pFunc(); /**< Getter for private implementation pointer, @private. */
    const GeneratorImpl *pFunc() const; /**< Const getter for private implementation pointer, @private. */
};

} // namespace libcellml
