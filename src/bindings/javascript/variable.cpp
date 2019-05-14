
#include <emscripten/bind.h>

#include "libcellml/variable.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_variable) {

    enum_<libcellml::Variable::InterfaceType>("Variable_InterfaceType")
            .value("NONE", libcellml::Variable::InterfaceType::NONE)
            .value("PRIVATE", libcellml::Variable::InterfaceType::PRIVATE)
            .value("PUBLIC", libcellml::Variable::InterfaceType::PUBLIC)
            .value("PUBLIC_AND_PRIVATE", libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE)
    ;

    class_<libcellml::Variable, base<libcellml::NamedEntity>>("Variable")
        .smart_ptr_constructor("Variable", &std::make_shared<libcellml::Variable>)
            .function("removeAllEquivalences", &libcellml::Variable::removeAllEquivalences)
            .function("getEquivalentVariable", &libcellml::Variable::getEquivalentVariable)
            .function("equivalentVariableCount", &libcellml::Variable::equivalentVariableCount)
            .function("hasEquivalentVariable", &libcellml::Variable::hasEquivalentVariable)
            .function("setUnitsByName", select_overload<void(const std::string &)>(&libcellml::Variable::setUnits))
            .function("setUnitsByUnits", select_overload<void(const libcellml::UnitsPtr &)>(&libcellml::Variable::setUnits))
            .function("getUnits", &libcellml::Variable::getUnits)
            .function("setInitialValueByString", select_overload<void(const std::string &)>(&libcellml::Variable::setInitialValue))
            .function("setInitialValueByDouble", select_overload<void(double)>(&libcellml::Variable::setInitialValue))
            .function("setInterfaceTypeByString", select_overload<void(const std::string &)>(&libcellml::Variable::setInterfaceType))
            .function("setInterfaceTypeByInterfaceType", select_overload<void(libcellml::Variable::InterfaceType)>(&libcellml::Variable::setInterfaceType))
            .function("getInterfaceType", &libcellml::Variable::getInterfaceType)
            .class_function("getEquivalenceConnectionId", &libcellml::Variable::getEquivalenceConnectionId)
            .class_function("getEquivalenceMappingId", &libcellml::Variable::getEquivalenceMappingId)
            .class_function("addEquivalence", select_overload<void(const libcellml::VariablePtr &, const libcellml::VariablePtr &)>(&libcellml::Variable::addEquivalence))
            .class_function("addEquivalenceWithIds", select_overload<void(const libcellml::VariablePtr &, const libcellml::VariablePtr &, const std::string &, const std::string &)>(&libcellml::Variable::addEquivalence))
            .class_function("removeEquivalence", &libcellml::Variable::removeEquivalence)
            .class_function("setEquivalenceConnectionId", &libcellml::Variable::setEquivalenceConnectionId)
            .class_function("setEquivalenceMappingId", &libcellml::Variable::setEquivalenceMappingId)
    ;

//    Maybe smoething like this gets my enum inside the variable class in javascript somehow?
//    EM_ASM(
//        libCellML['Variable']['InterfaceType'] = libCellML['Variable.InterfaceType'];
//        delete libCellML['Variable.InterfaceType'];
//    );
}
