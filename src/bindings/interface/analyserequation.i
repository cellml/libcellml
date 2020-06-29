%module(package="libcellml") analyserequation

#define LIBCELLML_EXPORT

%feature("docstring") libcellml::AnalyserEquation
"Creates an :class:`AnalyserEquation` object.";

%feature("docstring") libcellml::AnalyserEquation::type
"Returns the :enum:`AnalyserEquation::Type` for this :class:`AnalyserEquation` object.";

%feature("docstring") libcellml::AnalyserEquation::ast
"Returns the :class:`AnalyserEquationAst` object for this :class:`AnalyserEquation` object.";

%feature("docstring") libcellml::AnalyserEquation::dependencies
"Returns the list of :class:`AnalyserEquation` objects which corresponds to the equations on which this :class:`AnalyserEquation` object depends.";

%feature("docstring") libcellml::AnalyserEquation::isStateRateBased
"Tests if this :class:`AnalyserEquation` object relies on states and/or rates.";

%feature("docstring") libcellml::AnalyserEquation::variable
"Returns the :class:`AnalyserVariable` object for this :class:`AnalyserEquation` object.";

%{
#include "libcellml/analyserequation.h"
%}

%include "libcellml/types.h"
%include "libcellml/analyserequation.h"
