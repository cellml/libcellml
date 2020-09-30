%module(package="libcellml") analyservariable

#define LIBCELLML_EXPORT

%include <std_shared_ptr.i>

%feature("docstring") libcellml::AnalyserVariable
"Creates an :class:`AnalyserVariable` object.";

%feature("docstring") libcellml::AnalyserVariable::type
"Returns the :enum:`AnalyserVariable::Type`.";

%feature("docstring") libcellml::AnalyserVariable::index
"Returns the index.";

%feature("docstring") libcellml::AnalyserVariable::initialisingVariable
"Returns the initialising :class:`Variable`.";

%feature("docstring") libcellml::AnalyserVariable::variable
"Returns the :class:`Variable`.";

%feature("docstring") libcellml::AnalyserVariable::equation
"Returns the :class:`AnalyserEquation`.";

%{
#include "libcellml/analyservariable.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%shared_ptr(libcellml::AnalyserVariable);

%include "libcellml/types.h"
%include "libcellml/analyservariable.h"
