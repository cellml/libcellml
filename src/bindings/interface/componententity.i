%module(package="libcellml") componententity

#define LIBCELLML_EXPORT

%import "types.i"
%import "importedentity.i"

#if defined(SWIGPYTHON)
    // Allow any type of input to be converted to bool
    %typemap(typecheck,precedence=SWIG_TYPECHECK_BOOL) bool { $1 = 1; }
    %typemap(in) bool { $1 = PyObject_IsTrue($input) == 1; }

    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::ComponentEntity {
        ComponentPtr getComponent(long index) const {
            if(index < 0) return nullptr;
            return $self->getComponent(size_t(index));
        }
        bool removeComponent(long index) {
            if(index < 0) return false;
            return $self->removeComponent(size_t(index));
        }
        ComponentPtr takeComponent(long index) {
            if(index < 0) return nullptr;
            return $self->takeComponent(size_t(index));
        }
        bool replaceComponent(long index, const ComponentPtr &c) {
            if(index < 0) return false;
            return $self->replaceComponent(size_t(index), c);
        }
    }
#endif

%feature("docstring") libcellml::ComponentEntity
"Abstract class that provides component managing functionality.";

%feature("docstring") libcellml::ComponentEntity::addComponent
"Add a copy of the given component as a child component of this component
entity.";

%feature("docstring") libcellml::ComponentEntity::containsComponent
"Tests if a component, specified by an index, name, or with a Component object,
 is contained within this entity.

A second argument can be given to specify whether or not child components
should be searched for the component to remove.";

%feature("docstring") libcellml::ComponentEntity::getComponent
"Returns a component, specified by an index or name.

A second argument can be given to specify whether or not child components
should be searched for the component to remove.

Only the first matching component is returned.";

%feature("docstring") libcellml::ComponentEntity::removeComponent
"Removes a component, specified by an index, name, or with a Component object.

A second argument can be given to specify whether or not child components
should be searched for the component to remove.

Only the first matching component is removed.

Returns `True` on success.";

%feature("docstring") libcellml::ComponentEntity::removeAllComponents
"Removes all components that have been added to this entity.";

%feature("docstring") libcellml::ComponentEntity::takeComponent
"Removes and returns a component, specified by an index or name.

Only the first matching component is removed and  returned.";

%feature("docstring") libcellml::ComponentEntity::replaceComponent
"Removes a component, specified by an index, name, or with a Component object,
and replaces it with the given component object (second argument).

A third argument can be given to specify whether or not child components
should be searched for the component to remove.

Only the first matching component is replaced.

Returns `True` on success.";

%feature("docstring") libcellml::ComponentEntity::componentCount
"Returns the number of components the component contains.  ";

%{
#include "libcellml/componententity.h"
%}

%ignore libcellml::ComponentEntity::ComponentEntity(ComponentEntity &&);
%ignore libcellml::ComponentEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/componententity.h"
