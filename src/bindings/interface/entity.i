%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%import "types.i"
%import "std_string.i"

%feature("docstring") libcellml::Entity
"Abstract base class for all libCellML core classes."

%feature("docstring") libcellml::Entity::id
"Returns the `id` document identifier for this entity, or an empty string if
not set.";

%feature("docstring") libcellml::Entity::setId
"Set the `id` document identifier for this entity (use empty string to
unset).";

%feature("docstring") libcellml::Entity::clearParent
"Removes any parent set for this entity.";

%feature("docstring") libcellml::Entity::parent
"Returns the parent of the CellML Entity (or `None` if not set).";

%feature("docstring") libcellml::Entity::hasParent
"Tests if this entity have the given entity as a parent.";

%feature("docstring") libcellml::Entity::hasAncestor
"Tests if this entity or any of its ancestors have the given entity as a parent.";

%feature("docstring") libcellml::Entity::setParent
"Set the parent of the entity to the given Model or Component.";

%{
#include "libcellml/entity.h"
#include "libcellml/model.h"
#include "libcellml/component.h"
%}

%ignore libcellml::Entity::Entity(Entity &&);
%ignore libcellml::Entity::operator =;

%typemap(out) libcellml::EntityPtr parent {
    auto isAModel = std::dynamic_pointer_cast<libcellml::Model>($1);
    auto isAComponent = std::dynamic_pointer_cast<libcellml::Component>($1);
    if (isAModel != nullptr) {
        std::shared_ptr<  libcellml::Model > *smartresult = result ? new std::shared_ptr<  libcellml::Model >(isAModel) : nullptr;
        resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_libcellml__Model_t, SWIG_POINTER_OWN);
    } else if (isAComponent != nullptr) {
        std::shared_ptr<  libcellml::Component > *smartresult = result ? new std::shared_ptr<  libcellml::Component >(isAComponent) : nullptr;
        resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_libcellml__Component_t, SWIG_POINTER_OWN);
    }
}

%include "libcellml/types.h"
%include "libcellml/entity.h"
