%module(package="libcellml") analyser

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"

%feature("docstring") libcellml::Analyser
"Creates an :class:`Analyser` object.";

%feature("docstring") libcellml::Analyser::analyseModel
"Analyses the model to determine whether it can be used for simulation purposes.";

%feature("docstring") libcellml::Analyser::model
"Returns the :class:`AnalysedModel` object which results from the analysis of a model.";

%{
#include "libcellml/analyser.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(Analyser)

%include "libcellml/analyser.h"
