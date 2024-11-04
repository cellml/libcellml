#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(AnalyserInvestigate, segfault)
{
    auto parser = libcellml::Parser::create(false);
    auto model = parser->parseModel(fileContents("analyser/lung_ROM/lung_ROM.cellml"));

    EXPECT_EQ(size_t(1), parser->issueCount());

    auto v = libcellml::Validator::create();

    v->validateModel(model);

    EXPECT_EQ(size_t(0), v->errorCount());

    auto i = libcellml::Importer::create(false);
    // base_path = os.path.dirname(os.path.abspath(main_model_file))
    i->resolveImports(model, resourcePath("analyser/lung_ROM/"));

    auto flat_model = i->flattenModel(model);

    EXPECT_EQ(size_t(64), flat_model->componentCount());

    auto a = libcellml::Analyser::create();

    a->analyseModel(flat_model);

    EXPECT_EQ(size_t(1), a->errorCount());
}
