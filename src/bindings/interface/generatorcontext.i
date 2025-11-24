%module(package="libcellml") generatorcontext

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"

%feature("docstring") libcellml::GeneratorContext
"Creates a :class:`GeneratorContext` object.";

%feature("docstring") libcellml::GeneratorContext::isTrackedVariable
"Tests if the given variable is tracked.";

%feature("docstring") libcellml::GeneratorContext::isUntrackedVariable
"Tests if the given variable is untracked.";

%feature("docstring") libcellml::GeneratorContext::trackVariable
"Tracks the given variable.";

%feature("docstring") libcellml::GeneratorContext::untrackVariable
"Untracks the given variable.";

%feature("docstring") libcellml::GeneratorContext::trackAllConstants
"Tracks all the constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackAllConstants
"Untracks all the constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackAllComputedConstants
"Tracks all the computed constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackAllComputedConstants
"Untracks all the computed constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackAllAlgebraicVariables
"Tracks all the algebraic variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackAllAlgebraicVariables
"Untracks all the algebraic variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackAllVariables
"Tracks all the variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackAllVariables
"Untracks all the variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackedConstantCount
"Returns the number of tracked constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackedConstantCount
"Returns the number of untracked constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackedComputedConstantCount
"Returns the number of tracked computed constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackedComputedConstantCount
"Returns the number of untracked computed constants in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackedAlgebraicVariableCount
"Returns the number of tracked algebraic variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackedAlgebraicVariableCount
"Returns the number of untracked algebraic variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::trackedVariableCount
"Returns the number of tracked variables in the given model.";

%feature("docstring") libcellml::GeneratorContext::untrackedVariableCount
"Returns the number of untracked variables in the given model.";

%{
#include "libcellml/generatorcontext.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(GeneratorContext)

%include "libcellml/generatorcontext.h"
