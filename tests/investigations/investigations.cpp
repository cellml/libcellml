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

#include "gtest/gtest.h"
#include <cstdlib>

#include <libcellml>

#include "test_utils.h"

const char *BENCHMARKING_MODEL_ROOT = std::getenv("BENCHMARKING_MODEL_ROOT");

TEST(Investigations, DISABLED_exponentialTimeConsumption11)
{
    const std::string modelPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_11_vessels/image_to_model.cellml";
    const std::string modelImportPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_11_vessels/";
    auto importer = libcellml::Importer::create(false);

    auto parser = libcellml::Parser::create(false);
    auto originalModel = parser->parseModel(fileContents(modelPath, true));
    EXPECT_EQ(size_t(1), parser->issueCount());
    Debug() << modelPath;
    Debug() << parser->issue(0)->description();
    Debug() << originalModel->name();

    importer->resolveImports(originalModel, modelImportPath);

    EXPECT_EQ(size_t(3), importer->issueCount());

    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(0), importer->issueCount());
    EXPECT_NE(nullptr, flatModel);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(flatModel);
    EXPECT_EQ(size_t(0), analyser->issueCount());
    printIssues(analyser);
}

TEST(Investigations, DISABLED_exponentialTimeConsumption246)
{
    const std::string modelPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_246_vessels/image_to_model.cellml";
    const std::string modelImportPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_246_vessels/";
    auto importer = libcellml::Importer::create(false);

    auto parser = libcellml::Parser::create(false);
    auto originalModel = parser->parseModel(fileContents(modelPath, true));
    EXPECT_EQ(size_t(1), parser->issueCount());
    Debug() << parser->issue(0)->description();
    Debug() << originalModel->name();

    importer->resolveImports(originalModel, modelImportPath);

    EXPECT_EQ(size_t(3), importer->issueCount());

    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(0), importer->issueCount());
    EXPECT_NE(nullptr, flatModel);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(flatModel);
    EXPECT_EQ(size_t(0), analyser->issueCount());
    printIssues(analyser);
}

TEST(Investigations, DISABLED_exponentialTimeConsumption380)
{
    const std::string modelPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_380_vessels/image_to_model.cellml";
    const std::string modelImportPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_380_vessels/";
    auto importer = libcellml::Importer::create(false);

    auto parser = libcellml::Parser::create(false);
    auto originalModel = parser->parseModel(fileContents(modelPath, true));
    EXPECT_EQ(size_t(1), parser->issueCount());
    Debug() << modelPath;
    Debug() << parser->issue(0)->description();
    Debug() << originalModel->name();

    importer->resolveImports(originalModel, modelImportPath);

    EXPECT_EQ(size_t(3), importer->issueCount());

    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(0), importer->issueCount());
    EXPECT_NE(nullptr, flatModel);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(flatModel);
    EXPECT_EQ(size_t(0), analyser->issueCount());
    printIssues(analyser);
}

TEST(Investigations, exponentialTimeConsumption524)
{
    const std::string modelPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_524_vessels/image_to_model.cellml";
    const std::string modelImportPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_524_vessels/";
    auto importer = libcellml::Importer::create(false);

    auto parser = libcellml::Parser::create(false);
    auto originalModel = parser->parseModel(fileContents(modelPath, true));
    EXPECT_EQ(size_t(1), parser->issueCount());
    Debug() << modelPath;
    Debug() << parser->issue(0)->description();
    Debug() << originalModel->name();

    importer->resolveImports(originalModel, modelImportPath);

    EXPECT_EQ(size_t(3), importer->issueCount());

    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(0), importer->issueCount());
    EXPECT_NE(nullptr, flatModel);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(flatModel);
    EXPECT_EQ(size_t(0), analyser->issueCount());
    printIssues(analyser);
}

TEST(Investigations, DISABLED_exponentialTimeConsumptionOthers)
{
    const std::vector<int> vesselCounts = {246, 380, 524};

    auto importer = libcellml::Importer::create(false);
    auto parser = libcellml::Parser::create(false);
    auto printer = libcellml::Printer::create();
    auto analyser = libcellml::Analyser::create();
    auto generator = libcellml::Generator::create();

    for (int vesselCount : vesselCounts) {
        SCOPED_TRACE("Vessel count: " + std::to_string(vesselCount));
        std::string modelPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_" + std::to_string(vesselCount) + "_vessels/image_to_model.cellml";
        std::string modelImportPath = std::string(BENCHMARKING_MODEL_ROOT) + "image_to_model_" + std::to_string(vesselCount) + "_vessels/";
        auto originalModel = parser->parseModel(fileContents(modelPath, true));
        EXPECT_EQ(size_t(1), parser->issueCount());

        importer->resolveImports(originalModel, modelImportPath);

        EXPECT_EQ(size_t(0), importer->issueCount());
        for (size_t i = 0; i < importer->issueCount(); ++i) {
            Debug() << "[" << i << "]: " << importer->issue(i)->description();
        }

        auto flatModel = importer->flattenModel(originalModel);
        EXPECT_EQ(size_t(0), importer->issueCount());
        EXPECT_NE(nullptr, flatModel);

        analyser->analyseModel(flatModel);
        EXPECT_EQ(size_t(0), analyser->issueCount());

        const auto implementationCode = generator->implementationCode(analyser->analyserModel());
        EXPECT_NE(size_t(0), implementationCode.length());
    }
}
