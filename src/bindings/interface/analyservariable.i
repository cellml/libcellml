%module(package="libcellml") analyservariable

#define LIBCELLML_EXPORT

%include <std_shared_ptr.i>

%import "types.i"

%feature("docstring") libcellml::AnalyserVariable
"Creates an :class:`AnalyserVariable` object.";

%feature("docstring") libcellml::AnalyserVariable::type
"Returns the :enum:`AnalyserVariable::Type`.";

%feature("docstring") libcellml::AnalyserVariable::typeAsString
"Returns the :enum:`AnalyserVariable::Type` as a string.";

%feature("docstring") libcellml::AnalyserVariable::index
"Returns the index.";

%feature("docstring") libcellml::AnalyserVariable::initialisingVariable
"Returns the initialising :class:`Variable`.";

%feature("docstring") libcellml::AnalyserVariable::variable
"Returns the :class:`Variable`.";

%feature("docstring") libcellml::AnalyserVariable::model
"Returns the :class:`AnalyserModel`.";

%feature("docstring") libcellml::AnalyserVariable::equationCount
"Returns the number of equations used to compute this :class:`AnalyserVariable` object.";

%feature("docstring") libcellml::AnalyserVariable::equations
"Returns the equations used to compute this :class:`AnalyserVariable` object.";

%feature("docstring") libcellml::AnalyserVariable::equation
"Returns the equation, at the given index, used to compute this :class:`AnalyserVariable` object.";

%{
#include "libcellml/analyservariable.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%shared_ptr(libcellml::AnalyserVariable);

%include "libcellml/types.h"
%include "libcellml/analyservariable.h"
