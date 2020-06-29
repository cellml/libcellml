%module(package="libcellml") analyservariable

#define LIBCELLML_EXPORT

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

%{
#include "libcellml/analyservariable.h"
%}

%include "libcellml/types.h"
%include "libcellml/analyservariable.h"
