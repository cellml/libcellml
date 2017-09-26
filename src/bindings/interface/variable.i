%module(package="libcellml") variable

#define LIBCELLML_EXPORT

%import "types.i"
%import "namedentity.i"

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Variable {
        VariablePtr getEquivalentVariable(long index) {
            if(index < 0) return nullptr;
            return $self->getEquivalentVariable(size_t(index));
        }
    }
#endif

%{
#include "libcellml/variable.h"
%}

%ignore libcellml::Variable::Variable(Variable &&);
%ignore libcellml::Variable::operator =;

%include "libcellml/types.h"
%include "libcellml/variable.h"
