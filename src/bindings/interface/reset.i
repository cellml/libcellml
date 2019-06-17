%module(package="libcellml") reset

#define LIBCELLML_EXPORT

%import "types.i"
%import "orderedentity.i"

%feature("docstring") libcellml::Reset
"The Reset class is for describing a CellML reset.";

%feature("docstring") libcellml::Reset::setVariable
"Sets the :class: Variable for this reset.";

%feature("docstring") libcellml::Reset::variable
"Returns the :class: Variable of this reset.";

#if defined(SWIGPYTHON)
    // Allow any type of input to be converted to bool
    %typemap(typecheck,precedence=SWIG_TYPECHECK_BOOL) bool { $1 = 1; }
    %typemap(in) bool { $1 = PyObject_IsTrue($input) == 1; }
#endif

%{
#include "libcellml/reset.h"
%}

%ignore libcellml::Reset::Reset(Reset &&);
%ignore libcellml::Reset::operator =;

%include "libcellml/types.h"
%include "libcellml/reset.h"

