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

#include <emscripten/bind.h>

#define DAMN_YOU_EMSCRIPTEN
#include "libcellml/component.h"
//#include "libcellml/reset.h"
//#include "libcellml/variable.h"

using namespace emscripten;

//namespace libcellml {

//class ComponentImportedEntity;
//using ComponentImportedEntityPtr = std::shared_ptr<ComponentImportedEntity>;

//// To work around multiple inheritance we have to create a combined Units
//// and ImportedEntity class that we can bind with Emscripten.
//class ComponentImportedEntity: public Component
//{
//public:
//  static ComponentImportedEntityPtr create() noexcept
//  {
//    return std::shared_ptr<ComponentImportedEntity> {new ComponentImportedEntity {}};
//  }

//  static ComponentImportedEntityPtr create(const std::string &name) noexcept
//  {
//    return std::shared_ptr<ComponentImportedEntity> {new ComponentImportedEntity {name}};
//  }

//  // Clone requires special treatment.
//  ComponentImportedEntityPtr clone()
//  {
//    auto c = create();

//    c->setId(id());
//    c->setName(name());
//    c->setMath(math());

//    if (isImport()) {
//      c->setImportSource(importSource());
//    }

//    c->setImportReference(importReference());

//    for (size_t index = 0; index < variableCount(); ++index) {
//      auto v = variable(index);
//      c->addVariable(v->clone());
//    }

//    for (size_t index = 0; index < resetCount(); ++index) {
//      auto r = reset(index);
//      auto rClone = r->clone();
//      c->addReset(rClone);

//      auto resetVariable = r->variable();
//      bool found = false;
//      for (size_t index = 0; (index < variableCount()) && !found; ++index) {
//        auto v = variable(index);
//        if (resetVariable == v) {
//          found = true;
//          rClone->setVariable(c->variable(index));
//        }
//      }
//      auto testVariable = r->testVariable();
//      found = false;
//      for (size_t index = 0; (index < variableCount()) && !found; ++index) {
//        auto v = variable(index);
//        if (testVariable == v) {
//          found = true;
//          rClone->setTestVariable(c->variable(index));
//        }
//      }
//    }

//    for (size_t index = 0; index < componentCount(); ++index) {
//      auto cChild = component(index);
//      c->addComponent(cChild->clone());
//    }

//    return c;
//  }

//  // ImportedEntity methods.
//  bool isImport() const
//  {
//    return Component::isImport();
//  }

//  ImportSourcePtr importSource() const
//  {
//    return Component::importSource();
//  }

//  void setImportSource(const ImportSourcePtr &importSource)
//  {
//    Component::setImportSource(importSource);
//  }

//  std::string importReference() const
//  {
//    return Component::importReference();
//  }

//  void setImportReference(const std::string &reference)
//  {
//    return Component::setImportReference(reference);
//  }

//  bool isResolved() const
//  {
//    return Component::isResolved();
//  }

//private:
//  ComponentImportedEntity()
//    : Component()
//  {
//  }
//  explicit ComponentImportedEntity(const std::string &name)
//    : Component(name)
//  {
//  }

//};

//}

EMSCRIPTEN_BINDINGS(libcellml_component) {

    class_<libcellml::Component, base<libcellml::ComponentEntity>>("Component")
        .smart_ptr<std::shared_ptr<libcellml::Component>>("ComponentPtr")
        .function("setSourceComponent", &libcellml::Component::setSourceComponent)
        .function("appendMath", &libcellml::Component::appendMath)
        .function("math", &libcellml::Component::math)
        .function("setMath", &libcellml::Component::setMath)
        .function("removeMath", &libcellml::Component::removeMath)
        .function("addVariable", &libcellml::Component::addVariable)
        .function("removeVariableByIndex", select_overload<bool(size_t)>(&libcellml::Component::removeVariable))
        .function("removeVariableByName", select_overload<bool(const std::string &)>(&libcellml::Component::removeVariable))
        .function("removeVariableByVariable", select_overload<bool(const libcellml::VariablePtr &)>(&libcellml::Component::removeVariable))
        .function("removeAllVariables", &libcellml::Component::removeAllVariables)
        .function("variableByIndex", select_overload<libcellml::VariablePtr(size_t) const>(&libcellml::Component::variable))
        .function("variableByName", select_overload<libcellml::VariablePtr(const std::string &) const>(&libcellml::Component::variable))
        .function("takeVariableByIndex", select_overload<libcellml::VariablePtr(size_t)>(&libcellml::Component::takeVariable))
        .function("takeVariableByName", select_overload<libcellml::VariablePtr(const std::string &)>(&libcellml::Component::takeVariable))
        .function("variableCount", &libcellml::Component::variableCount)
        .function("hasVariableByVariable", select_overload<bool(const libcellml::VariablePtr &) const>(&libcellml::Component::hasVariable))
        .function("hasVariableByName", select_overload<bool(const std::string &) const>(&libcellml::Component::hasVariable))
        .function("addReset", &libcellml::Component::addReset)
        .function("takeReset", &libcellml::Component::takeReset)
        .function("removeResetByIndex", select_overload<bool(size_t)>(&libcellml::Component::removeReset))
        .function("removeResetByReset", select_overload<bool(const libcellml::ResetPtr &)>(&libcellml::Component::removeReset))
        .function("removeAllResets", &libcellml::Component::removeAllResets)
        .function("requiresImports", &libcellml::Component::requiresImports)
        .function("reset", &libcellml::Component::reset)
        .function("resetCount", &libcellml::Component::resetCount)
        .function("hasReset", &libcellml::Component::hasReset)
        .function("clone", &libcellml::Component::clone)
        .function("isImport", &libcellml::Component::isImport)
        .function("importSource", &libcellml::Component::importSource)
        .function("setImportSource", &libcellml::Component::setImportSource)
        .function("importReference", &libcellml::Component::importReference)
        .function("setImportReference", &libcellml::Component::setImportReference)
        .function("isResolved", &libcellml::Component::isResolved)
    ;

//    class_<libcellml::ComponentImportedEntity, base<libcellml::Component>>("Component")
//        .smart_ptr<std::shared_ptr<libcellml::ComponentImportedEntity>>("ComponentPtr")
//        .constructor(select_overload<libcellml::ComponentImportedEntityPtr()>(&libcellml::ComponentImportedEntity::create))
//        .constructor(select_overload<libcellml::ComponentImportedEntityPtr(const std::string &)>(&libcellml::ComponentImportedEntity::create))
//        .function("clone", &libcellml::ComponentImportedEntity::clone)
//        .function("isImport", &libcellml::ComponentImportedEntity::isImport)
//        .function("importSource", &libcellml::ComponentImportedEntity::importSource)
//        .function("setImportSource", &libcellml::ComponentImportedEntity::setImportSource)
//        .function("importReference", &libcellml::ComponentImportedEntity::importReference)
//        .function("setImportReference", &libcellml::ComponentImportedEntity::setImportReference)
//        .function("isResolved", &libcellml::ComponentImportedEntity::isResolved)
//    ;
}
