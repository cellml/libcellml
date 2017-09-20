%module(package="libcellml") component

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Component {
        VariablePtr getVariable(long index) {
            if(index < 0) return nullptr;
            return $self->getVariable(size_t(index));
        }
    }
#endif

%{
#include "libcellml/component.h"
%}

%ignore libcellml::Component::Component(Component &&);
%ignore libcellml::Component::operator =;

%include "libcellml/types.h"
%include "libcellml/component.h"
