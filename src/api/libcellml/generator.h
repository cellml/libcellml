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

#include <list>
#include <string>

#include "libcellml/logger.h"

namespace libcellml {

class Generator;

/**
 * @brief The Generator class.
 *
 * The Generator class is for representing a CellML Generator.
 */
class LIBCELLML_EXPORT Generator: public Logger
{
public:
    ~Generator() override; /**< Destructor */
    Generator(const Generator &rhs) = delete; /**< Copy constructor */
    Generator(Generator &&rhs) noexcept = delete; /**< Move constructor */
    Generator &operator=(Generator rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Generator object.
     *
     * Factory method to create a @c Generator. Create a generator with::
     *
     *   GeneratorPtr generator = libcellml::Generator::create();
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
     * @brief Get the interface code for the @c Model.
     *
     * Return the interface code for the @c Model processed by this
     * @c Generator, using its @c GeneratorProfile.
     *
     * @param model The @AnalyserModel for which interface code is to be
     * generated.
     *
     * @return The code.
     */
    std::string interfaceCode(const AnalyserModelPtr &model) const;

    /**
     * @brief Get the implementation code for the @c Model.
     *
     * Return the implementation code for the @c Model processed by this
     * @c Generator, using its @c GeneratorProfile.
     *
     * @param model The @AnalyserModel for which implementation code is to be
     * generated.
     *
     * @return The code.
     */
    std::string implementationCode(const AnalyserModelPtr &model) const;

private:
    Generator(); /**< Constructor */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl;
};

} // namespace libcellml
