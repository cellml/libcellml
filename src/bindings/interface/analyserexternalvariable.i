%module(package="libcellml") analyserexternalvariable

#define LIBCELLML_EXPORT

%feature("docstring") libcellml::AnalyserExternalVariable
"Creates an :class:`AnalyserExternalVariable` object.";

%{
#include "libcellml/analyserexternalvariable.h"
%}

%include "libcellml/analyserexternalvariable.h"
