%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "analysermodel.i"
%import "createconstructor.i"
%import "generatorprofile.i"

%feature("docstring") libcellml::Generator
"Creates a :class:`Generator` object.";

%feature("docstring") libcellml::Generator::profile
"Returns the profile used for code generation.";

%feature("docstring") libcellml::Generator::setProfile
"Sets the profile to use for code generation.";

%feature("docstring") libcellml::Generator::isTrackedVariable
"Tests if the given variable is tracked.";

%feature("docstring") libcellml::Generator::isUntrackedVariable
"Tests if the given variable is untracked.";

%feature("docstring") libcellml::Generator::trackVariable
"Tracks the given variable.";

%feature("docstring") libcellml::Generator::untrackVariable
"Untracks the given variable.";

%feature("docstring") libcellml::Generator::trackAllConstants
"Tracks all the constants in the given model.";

%feature("docstring") libcellml::Generator::untrackAllConstants
"Untracks all the constants in the given model.";

%feature("docstring") libcellml::Generator::trackAllComputedConstants
"Tracks all the computed constants in the given model.";

%feature("docstring") libcellml::Generator::untrackAllComputedConstants
"Untracks all the computed constants in the given model.";

%feature("docstring") libcellml::Generator::trackAllAlgebraic
"Tracks all the algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::untrackAllAlgebraic
"Untracks all the algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::trackAllExternals
"Tracks all the external variables in the given model.";

%feature("docstring") libcellml::Generator::untrackAllExternals
"Untracks all the external variables in the given model.";

%feature("docstring") libcellml::Generator::trackAllVariables
"Tracks all the variables in the given model.";

%feature("docstring") libcellml::Generator::untrackAllVariables
"Untracks all the variables in the given model.";

%feature("docstring") libcellml::Generator::trackedConstantCount
"Returns the number of tracked constants in the given model.";

%feature("docstring") libcellml::Generator::untrackedConstantCount
"Returns the number of untracked constants in the given model.";

%feature("docstring") libcellml::Generator::trackedComputedConstantCount
"Returns the number of tracked computed constants in the given model.";

%feature("docstring") libcellml::Generator::untrackedComputedConstantCount
"Returns the number of untracked computed constants in the given model.";

%feature("docstring") libcellml::Generator::trackedAlgebraicCount
"Returns the number of tracked algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::untrackedAlgebraicCount
"Returns the number of untracked algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::trackedExternalCount
"Returns the number of tracked external variables in the given model.";

%feature("docstring") libcellml::Generator::untrackedExternalCount
"Returns the number of untracked external variables in the given model.";

%feature("docstring") libcellml::Generator::trackedVariableCount
"Returns the number of tracked variables in the given model.";

%feature("docstring") libcellml::Generator::untrackedVariableCount
"Returns the number of untracked variables in the given model.";

%feature("docstring") libcellml::Generator::interfaceCode
"Returns the interface code.";

%feature("docstring") libcellml::Generator::implementationCode
"Returns the implementation code.";

%feature("docstring") libcellml::Generator::equationCode
"Returns the equation code for a given equation AST.";

%{
#include "libcellml/generator.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(Generator)

%include "libcellml/generator.h"
