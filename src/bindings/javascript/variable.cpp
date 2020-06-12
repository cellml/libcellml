
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
        .smart_ptr_constructor("Variable", select_overload<libcellml::VariablePtr()>(&libcellml::Variable::create))
        .function("removeAllEquivalences", &libcellml::Variable::removeAllEquivalences)
        .function("equivalentVariable", &libcellml::Variable::equivalentVariable)
        .function("equivalentVariableCount", &libcellml::Variable::equivalentVariableCount)
        .function("hasEquivalentVariable", &libcellml::Variable::hasEquivalentVariable)
        .function("setUnitsByName", select_overload<void(const std::string &)>(&libcellml::Variable::setUnits))
        .function("setUnitsByUnits", select_overload<void(const libcellml::UnitsPtr &)>(&libcellml::Variable::setUnits))
        .function("units", &libcellml::Variable::units)
        .function("setInitialValueByString", select_overload<void(const std::string &)>(&libcellml::Variable::setInitialValue))
        .function("setInitialValueByDouble", select_overload<void(double)>(&libcellml::Variable::setInitialValue))
        .function("initialValue", &libcellml::Variable::initialValue)
        .function("removeInitialValue", &libcellml::Variable::removeInitialValue)
        .function("setInterfaceTypeByString", select_overload<void(const std::string &)>(&libcellml::Variable::setInterfaceType))
        .function("setInterfaceTypeByInterfaceType", select_overload<void(libcellml::Variable::InterfaceType)>(&libcellml::Variable::setInterfaceType))
        .function("interfaceType", &libcellml::Variable::interfaceType)
        .function("removeInterfaceType", &libcellml::Variable::removeInterfaceType)
        .function("clone", &libcellml::Variable::clone)
        .class_function("equivalenceConnectionId", &libcellml::Variable::equivalenceConnectionId)
        .class_function("equivalenceMappingId", &libcellml::Variable::equivalenceMappingId)
        .class_function("addEquivalence", select_overload<bool(const libcellml::VariablePtr &, const libcellml::VariablePtr &)>(&libcellml::Variable::addEquivalence))
        .class_function("addEquivalenceWithIds", select_overload<bool(const libcellml::VariablePtr &, const libcellml::VariablePtr &, const std::string &, const std::string &)>(&libcellml::Variable::addEquivalence))
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
