%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "generatorprofile.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Generator
"Creates a :class:`Generator` object.";

%feature("docstring") libcellml::Generator::profile
"Returns the profile used for code generation.";

%feature("docstring") libcellml::Generator::setProfile
"Sets the profile to use for code generation.";

%feature("docstring") libcellml::Generator::model
"Returns the model used for code generation.";

%feature("docstring") libcellml::Generator::setModel
"Sets the model to use for code generation.";

%feature("docstring") libcellml::Generator::interfaceCode
"Returns the interface code.";

%feature("docstring") libcellml::Generator::implementationCode
"Returns the implementation code.";

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

%create_constructor(Generator)
%create_constructor(GeneratorVariable)

%include "libcellml/generator.h"
