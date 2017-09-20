%module(package="libcellml") componententity

#define LIBCELLML_EXPORT

%import "types.i"
%import "importedentity.i"

#if defined(SWIGPYTHON)
    // Allow any type of input to be converted to bool
    %typemap(typecheck,precedence=SWIG_TYPECHECK_BOOL) bool { $1 = 1; }
    %typemap(in) bool { $1 = PyObject_IsTrue($input); }

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

%{
#include "libcellml/componententity.h"
%}

%ignore libcellml::ComponentEntity::ComponentEntity(ComponentEntity &&);
%ignore libcellml::ComponentEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/componententity.h"
