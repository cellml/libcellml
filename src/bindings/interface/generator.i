%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "generatorprofile.i"
%import "logger.i"
%import "types.i"


%feature("docstring") libcellml::GeneratorVariable
"Defines a variable created by processing a :class:`Model` with the :class:`Generator`.";

%feature("docstring") libcellml::GeneratorVariable::initialisingVariable
"Return the initialising :class:`Variable`.";

%feature("docstring") libcellml::GeneratorVariable::variable
"Return the :class:`Variable`.";

%feature("docstring") libcellml::GeneratorVariable::type
"Return the :enum:`GeneratorVariable::Type`.";

%feature("docstring") libcellml::Generator
"Can generate code from a :class:`Model` according to a code generation profile.";

%feature("docstring") libcellml::Generator::profile
"Returns the :enum:`Profile` type.";

%feature("docstring") libcellml::Generator::setProfile
"Sets this :class:`Generator`'s profile.";

%feature("docstring") libcellml::Generator::processModel
"Process the :class:`Model` given, analysing, and
preparing for code generation.";

%feature("docstring") libcellml::Generator::modelType
"Return the :enum:`ModelType` of the :class:`Model` that has been processed.";

%feature("docstring") libcellml::Generator::stateCount
"Return the number of states found in the processed :class:`Model`.";

%feature("docstring") libcellml::Generator::variableCount
"Return the number of variables found in the processed :class:`Model`.";

%feature("docstring") libcellml::Generator::voi
"Return the variable of integration found in the processed :class:`Model`.";

%feature("docstring") libcellml::Generator::state
"Return the state at the given index from the state array.";

%feature("docstring") libcellml::Generator::variable
"Return the variable at the given index from the variable array.";

%feature("docstring") libcellml::Generator::interfaceCode
"Return the interface code for the :class:`Model` processed.";

%feature("docstring") libcellml::Generator::implementationCode
"Return the implementation code for the :class:`Model` processed.";

%{
#include "libcellml/generator.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%pythonappend libcellml::Generator::Generator %{
from libcellml import GeneratorProfile
profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
self.setProfile(profile)
%}

%create_constructor(GeneratorVariable)
%create_constructor(Generator)

%include "libcellml/types.h"
%include "libcellml/generator.h"
