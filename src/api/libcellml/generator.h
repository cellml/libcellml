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
     * @brief Get the interface code for the @ref AnalyserModel.
     *
     * Return the interface code for the @ref AnalyserModel, using the @ref GeneratorProfile.
     *
     * @param model The @ref AnalyserModel for which we want to generate some interface code.
     *
     * @return The interface code as a @c std::string.
     */
    std::string interfaceCode(const AnalyserModelPtr &model) const;

    /**
     * @brief Get the implementation code for the @ref AnalyserModel.
     *
     * Return the implementation code for the @ref AnalyserModel, using the @ref GeneratorProfile.
     *
     * @param model The @ref AnalyserModel for which we want to generate some implementation code.
     *
     * @return The implementation code as a @c std::string.
     */
    std::string implementationCode(const AnalyserModelPtr &model) const;

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
    GeneratorImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
