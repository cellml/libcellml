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

#include "libcellml/generator.h"

#include "libcellml/generatorprofile.h"

#include "utilities.h"

namespace libcellml {

/**
 * @brief The Generator::GeneratorImpl struct.
 *
 * The private implementation for the Generator class.
 */
struct Generator::GeneratorImpl
{
    AnalyserModelPtr mModel;
    bool mModelHasOdes = false;
    bool mModelHasNlas = false;

    GeneratorProfilePtr mProfile = GeneratorProfile::create();
    std::string mCode;

    void reset();

    void updateVariableInfoSizes(size_t &componentSize, size_t &nameSize,
                                 size_t &unitsSize,
                                 const AnalyserVariablePtr &variable) const;

    bool modifiedProfile() const;

    void addOriginCommentCode();

    void addInterfaceHeaderCode();
    void addImplementationHeaderCode();

    void addVersionAndLibcellmlVersionCode(bool interface = false);

    void addStateAndVariableCountCode(bool interface = false);

    void addVariableTypeObjectCode();

    std::string generateVariableInfoObjectCode(const std::string &objectString) const;

    void addVariableInfoObjectCode();

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component,
                                              const std::string &type) const;

    void addInterfaceVoiStateAndVariableInfoCode();
    void addImplementationVoiInfoCode();
    void addImplementationStateInfoCode();
    void addImplementationVariableInfoCode();

    void addArithmeticFunctionsCode();
    void addTrigonometricFunctionsCode();

    void addInterfaceCreateDeleteArrayMethodsCode();
    void addExternalVariableMethodTypeDefinitionCode();
    void addImplementationCreateStatesArrayMethodCode();
    void addImplementationCreateVariablesArrayMethodCode();
    void addImplementationDeleteArrayMethodCode();

    void addRootFindingInfoObjectCode();
    void addExternNlaSolveMethodCode();

    void addInterfaceComputeModelMethodsCode();
    void addImplementationComputeModelMethodsCode();
};

} // namespace libcellml
