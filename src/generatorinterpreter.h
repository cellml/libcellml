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

#include "libcellml/analyserequation.h"

namespace libcellml {

class GeneratorInterpreter; /**< Forward declaration of GeneratorInterpreter class. */
using GeneratorInterpreterPtr = std::shared_ptr<GeneratorInterpreter>; /**< Type definition for shared GeneratorInterpreter pointer. */

/**
 * @brief The GeneratorInterpreter class.
 *
 * The GeneratorInterpreter class is used by the Generator and Interpreter classes to generate the code to compute a
 * model.
 */
class GeneratorInterpreter
{
public:
    ~GeneratorInterpreter(); /**< Destructor, @private. */
    GeneratorInterpreter(const GeneratorInterpreter &rhs) = delete; /**< Copy constructor, @private. */
    GeneratorInterpreter(GeneratorInterpreter &&rhs) noexcept = delete; /**< Move constructor, @private. */
    GeneratorInterpreter &operator=(GeneratorInterpreter rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create an @ref GeneratorInterpreter object.
     *
     * Factory method to create an @ref GeneratorInterpreter. Create a generator-interpreter with::
     *
     * @code
     *   auto interpreterStatement = libcellml::GeneratorInterpreter::create(model, profile, code);
     * @endcode
     *
     * @param model The model for which we want to generate the code to compute.
     * @param profile The profile to be used to generate the code to compute.
     * @param code The code that has already been generated.
     *
     * @return A smart pointer to an @ref GeneratorInterpreter object.
     */
    static GeneratorInterpreterPtr create(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile,
                                          const std::string &code) noexcept;

    /**
     * @brief Create an @ref GeneratorInterpreter object.
     *
     * Factory method to create an @ref GeneratorInterpreter. Create a generator-interpreter with::
     *
     * @code
     *   auto interpreterStatement = libcellml::GeneratorInterpreter::create(profile);
     * @endcode
     *
     * @param ast The AST for which we want to generate some code.
     * @param profile The profile to be used to generate some code.
     *
     * @return A smart pointer to an @ref GeneratorInterpreter object.
     */
    static GeneratorInterpreterPtr create(const AnalyserEquationAstPtr &ast,
                                          const GeneratorProfilePtr &profile) noexcept;

    /**
     * @brief Get the code to compute the model.
     *
     * Get the @c std::string code to compute the model.
     *
     * @return The @c std::string code to compute the model.
     */
    std::string code() const;

private:
    GeneratorInterpreter(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile, const std::string &code); /**< Constructor, @private. */
    GeneratorInterpreter(const AnalyserEquationAstPtr &ast, const GeneratorProfilePtr &profile); /**< Constructor, @private. */

    struct GeneratorInterpreterImpl;
    GeneratorInterpreterImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml