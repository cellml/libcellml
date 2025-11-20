%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "analysermodel.i"
%import "createconstructor.i"
%import "generatorcontext.i"
%import "generatorprofile.i"
%import "logger.i"

%feature("docstring") libcellml::Generator
"Creates a :class:`Generator` object.";

%feature("docstring") libcellml::Generator::context
"Returns the context used for code generation.";

%feature("docstring") libcellml::Generator::setContext
"Sets the context to use for code generation.";

%feature("docstring") libcellml::Generator::profile
"Returns the profile used for code generation.";

%feature("docstring") libcellml::Generator::setProfile
"Sets the profile to use for code generation.";

%feature("docstring") libcellml::Generator::isTrackedVariable //---GRY--- TO BE DELETED.
"Tests if the given variable is tracked.";

%feature("docstring") libcellml::Generator::isUntrackedVariable //---GRY--- TO BE DELETED.
"Tests if the given variable is untracked.";

%feature("docstring") libcellml::Generator::trackVariable //---GRY--- TO BE DELETED.
"Tracks the given variable.";

%feature("docstring") libcellml::Generator::untrackVariable //---GRY--- TO BE DELETED.
"Untracks the given variable.";

%feature("docstring") libcellml::Generator::trackAllConstants //---GRY--- TO BE DELETED.
"Tracks all the constants in the given model.";

%feature("docstring") libcellml::Generator::untrackAllConstants //---GRY--- TO BE DELETED.
"Untracks all the constants in the given model.";

%feature("docstring") libcellml::Generator::trackAllComputedConstants //---GRY--- TO BE DELETED.
"Tracks all the computed constants in the given model.";

%feature("docstring") libcellml::Generator::untrackAllComputedConstants //---GRY--- TO BE DELETED.
"Untracks all the computed constants in the given model.";

%feature("docstring") libcellml::Generator::trackAllAlgebraicVariables //---GRY--- TO BE DELETED.
"Tracks all the algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::untrackAllAlgebraicVariables //---GRY--- TO BE DELETED.
"Untracks all the algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::trackAllVariables //---GRY--- TO BE DELETED.
"Tracks all the variables in the given model.";

%feature("docstring") libcellml::Generator::untrackAllVariables //---GRY--- TO BE DELETED.
"Untracks all the variables in the given model.";

%feature("docstring") libcellml::Generator::trackedConstantCount //---GRY--- TO BE DELETED.
"Returns the number of tracked constants in the given model.";

%feature("docstring") libcellml::Generator::untrackedConstantCount //---GRY--- TO BE DELETED.
"Returns the number of untracked constants in the given model.";

%feature("docstring") libcellml::Generator::trackedComputedConstantCount //---GRY--- TO BE DELETED.
"Returns the number of tracked computed constants in the given model.";

%feature("docstring") libcellml::Generator::untrackedComputedConstantCount //---GRY--- TO BE DELETED.
"Returns the number of untracked computed constants in the given model.";

%feature("docstring") libcellml::Generator::trackedAlgebraicCount //---GRY--- TO BE DELETED.
"Returns the number of tracked algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::untrackedAlgebraicCount //---GRY--- TO BE DELETED.
"Returns the number of untracked algebraic variables in the given model.";

%feature("docstring") libcellml::Generator::trackedVariableCount //---GRY--- TO BE DELETED.
"Returns the number of tracked variables in the given model.";

%feature("docstring") libcellml::Generator::untrackedVariableCount //---GRY--- TO BE DELETED.
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
