%module(package="libcellml") when

#define LIBCELLML_EXPORT

%include "std_string.i"
%include "createconstructor.i"

%import "types.i"
%import "orderedentity.i"

%feature("docstring") libcellml::When
"Class for determining when a reset will occur.";

%feature("docstring") libcellml::When::setCondition
"Set the MathML string as the condition term for this when.";

%feature("docstring") libcellml::When::condition
"Get the MathML string as the condition term for this when.";

%feature("docstring") libcellml::When::setValue
"Set the MathML string as the value term for this when.";

%feature("docstring") libcellml::When::value
"Get the string MathML string that represents the value for this when.";

%{
#include "libcellml/when.h"
%}

%ignore libcellml::When::When(When &&);
%ignore libcellml::When::operator =;

%create_constructor(When)

%include "libcellml/types.h"
%include "libcellml/when.h"

