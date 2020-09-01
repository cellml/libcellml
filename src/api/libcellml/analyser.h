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
 * The Analyser class is for representing a CellML Analyser, which aim is to
 * check whether a model makes mathematical sense. If a model makes mathematical
 * sense then an @c AnalyserModel object can be retrieved, which can be used to
 * generate code, for instance.
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
     * @code
     *   auto analyser = libcellml::Analyser::create();
     * @endcode
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
     * @brief Get the analysed model.
     *
     * Get the analysed model that is the result of the model analysis.
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
