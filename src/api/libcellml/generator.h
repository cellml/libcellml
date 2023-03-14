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

#include <string>

#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Generator class.
 *
 * The Generator class is for representing a CellML Generator.
 */
class LIBCELLML_EXPORT Generator
{
public:
    ~Generator(); /**< Destructor, @private. */
    Generator(const Generator &rhs) = delete; /**< Copy constructor, @private. */
    Generator(Generator &&rhs) noexcept = delete; /**< Move constructor, @private. */
    Generator &operator=(Generator rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create a @c Generator object.
     *
     * Factory method to create a @c Generator. Create a generator with::
     *
     * @code
     *   auto generator = libcellml::Generator::create();
     * @endcode
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
     * @brief Get the @c AnalyserModel.
     *
     * Get the @c AnalyserModel used by this @c Generator.
     *
     * @return The @c AnalyserModel used.
     */
    AnalyserModelPtr model();

    /**
     * @brief Set the @c AnalyserModel.
     *
     * Set the @c AnalyserModel to be used by this @c Generator.
     *
     * @param model The @c AnalyserModel to set.
     */
    void setModel(const AnalyserModelPtr &model);

    /**
     * @brief Get the interface code for the @c AnalyserModel.
     *
     * Return the interface code for the @c AnalyserModel, using the
     * @c GeneratorProfile.
     *
     * @return The interface code as a @c std::string.
     */
    std::string interfaceCode() const;

    /**
     * @brief Get the implementation code for the @c AnalyserModel.
     *
     * Return the implementation code for the @c AnalyserModel, using the
     * @c GeneratorProfile.
     *
     * @return The implementation code as a @c std::string.
     */
    std::string implementationCode() const;

    /**
     * @brief Get the equation code for the given @c AnalyserEquationAst.
     *
     * Return the equation code for the given @c AnalyserEquationAst using @c GeneratorProfile, if present, or the
     * default @c GeneratorProfile.
     *
     * @param ast The @c AnalyserEquationAst for which we want to generate some code.
     * @param generatorProfile The @c GeneratorProfile, if any, to use to generate the equation code. If no
     * @c GeneratorProfile is provided then the default @c GeneratorProfile is used.
     */
    static std::string equationCode(const AnalyserEquationAstPtr &ast,
                                    const GeneratorProfilePtr &generatorProfile);

    /**
     * @brief Get the equation code for the given @c AnalyserEquationAst using a default @c GeneratorProfile.
     *
     * Return the equation code for the given @c AnalyserEquationAst using a default @c GeneratorProfile.
     *
     * @param ast The @c AnalyserEquationAst for which we want to generate some code.
     */
    static std::string equationCode(const AnalyserEquationAstPtr &ast);

private:
    Generator(); /**< Constructor, @private. */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
