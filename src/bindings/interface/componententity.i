%module(package="libcellml") componententity

#define LIBCELLML_EXPORT

%import "types.i"
%import "importedentity.i"

#if defined(SWIGPYTHON)
    %typemap(typecheck,precedence=SWIG_TYPECHECK_BOOL) bool { $1 = 1; }
    %typemap(in) bool { $1 = PyObject_IsTrue($input); }
#endif

%{
#include "libcellml/componententity.h"
%}

%ignore libcellml::ComponentEntity::ComponentEntity(ComponentEntity &&);
%ignore libcellml::ComponentEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/componententity.h"
