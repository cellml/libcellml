
# include <emscripten/bind.h>

# include "libcellml/generator.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_generator)
{
    class_<libcellml::Generator>("Generator")
        .smart_ptr_constructor("Generator", &libcellml::Generator::create)
        .function("profile", &libcellml::Generator::profile)
        .function("setProfile", &libcellml::Generator::setProfile)
        .function("model", &libcellml::Generator::model)
        .function("setModel", &libcellml::Generator::setModel)
        .function("interfaceCode", &libcellml::Generator::interfaceCode)
        .function("implementationCode", &libcellml::Generator::implementationCode)
    ;
}
