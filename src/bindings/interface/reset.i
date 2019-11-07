%module(package="libcellml") reset

#define LIBCELLML_EXPORT

%include "createconstructor.i"

%import "types.i"
%import "orderedentity.i"

%feature("docstring") libcellml::Reset
"The Reset class is for describing a CellML reset.";

%feature("docstring") libcellml::Reset::setVariable
"Sets the :class: variable for this reset.";

%feature("docstring") libcellml::Reset::variable
"Returns the :class: variable of this reset.";

%feature("docstring") libcellml::Reset::setTestVariable
"Sets the :class: test_variable for this reset.";

%feature("docstring") libcellml::Reset::testVariable
"Returns the :class: test_variable of this reset.";

%feature("docstring") libcellml::Reset::testValue
"Returns the :class: test_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::resetValue
"Returns the :class: reset_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::setTestValue
"Sets the :class: test_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::clearTestValue
"Clears the :class: test_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::setResetValue
"Sets the :class: reset_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::clearResetValue
"Clears the :class: reset_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::appendTestValue
"Appends to the :class: test_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::appendResetValue
"Appends to the :class: reset_value MathML string of this reset.";

%feature("docstring") libcellml::Reset::setTestValueId
"Sets the :class: test_value id string of this reset.";

%feature("docstring") libcellml::Reset::clearTestValueId
"Clears the :class: test_value id string of this reset.";

%feature("docstring") libcellml::Reset::setResetValueId
"Sets the :class: reset_value id string of this reset.";

%feature("docstring") libcellml::Reset::clearResetValueId
"Clears the :class: reset_value id string of this reset.";

%feature("docstring") libcellml::Reset::testValueId
"Returns the :class: test_value id string of this reset.";

%feature("docstring") libcellml::Reset::resetValueId
"Returns the :class: reset_value id string of this reset.";

#if defined(SWIGPYTHON)
    // Allow any type of input to be converted to bool
    %typemap(typecheck,precedence=SWIG_TYPECHECK_BOOL) bool { $1 = 1; }
    %typemap(in) bool { $1 = PyObject_IsTrue($input) == 1; }
#endif

%{
#include "libcellml/reset.h"
%}

%create_constructor(Reset)

%include "libcellml/types.h"
%include "libcellml/reset.h"

