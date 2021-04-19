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
    friend class Analyser;

public:
    ~Generator(); /**< Destructor. */
    Generator(const Generator &rhs) = delete; /**< Copy constructor. */
    Generator(Generator &&rhs) noexcept = delete; /**< Move constructor. */
    Generator &operator=(Generator rhs) = delete; /**< Assignment operator. */

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

private:
    Generator(); /**< Constructor, @private. */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
