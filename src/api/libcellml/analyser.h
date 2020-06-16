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
     * @brief Create a @c Analyser object.
     *
     * Factory method to create a @c Analyser.  Create an analyser with::
     *
     *   AnalyserPtr analyser = libcellml::Analyser::create();
     *
     * @return A smart pointer to a @c Analyser object.
     */
    static AnalyserPtr create() noexcept;

    /**
     * @brief Process the @c Model.
     *
     * Process the @c Model using this @c Analyser.
     *
     * @param model The @c Model to process.
     */
    void processModel(const ModelPtr &model);

private:
    Analyser(); /**< Constructor */

    struct AnalyserImpl;
    AnalyserImpl *mPimpl;
};

} // namespace libcellml
