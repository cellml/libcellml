%module(package="libcellml") analyser

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"

%feature("docstring") libcellml::Analyser
"Creates an :class:`Analyser` object.";

%feature("docstring") libcellml::Analyser::analyseModel
"Analyses the model to determine whether it can be used for simulation"
"purposes.";

%feature("docstring") libcellml::Analyser::addExternalVariable
"Adds a variable as an external variable to this analyser.";

%feature("docstring") libcellml::Analyser::removeExternalVariable
"Removes an external variable, specified by an index, name, or with a"
":class:`Variable` object. Returns `True` on success.";

%feature("docstring") libcellml::Analyser::removeAllExternalVariables
"Removes all external variables from this analyser.";

%feature("docstring") libcellml::Analyser::containsExternalVariable
"Tests if an external variable, specified by a name, or with a"
":class:`Variable` object, is contained within this analyser.";

%feature("docstring") libcellml::Analyser::externalVariable
"Returns the external variable, specified by an index or name.";

%feature("docstring") libcellml::Analyser::externalVariableCount
"Returns the number of external variables this analyser contains.";

%feature("docstring") libcellml::Analyser::model
"Returns the :class:`AnalysedModel` object which results from the analysis of a"
"model.";

%{
#include "libcellml/analyser.h"
%}

%create_constructor(Analyser)

%include "libcellml/analyser.h"
