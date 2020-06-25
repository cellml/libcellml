%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

#ifdef SWIGPYTHON
%import "generatorprofile.i"
#endif

%feature("docstring") libcellml::Generator
"Can generate code from a :class:`Model` according to a code generation profile.";

%feature("docstring") libcellml::Generator::profile
"Returns the :enum:`Profile` type.";

%feature("docstring") libcellml::Generator::setProfile
"Sets this :class:`Generator`'s profile.";

%feature("docstring") libcellml::Generator::interfaceCode
"Return the interface code for the :class:`Model` processed.";

%feature("docstring") libcellml::Generator::implementationCode
"Return the implementation code for the :class:`Model` processed.";

%{
#include "libcellml/generator.h"
%}

%pythonappend libcellml::Generator::Generator %{
from libcellml import GeneratorProfile
profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
self.setProfile(profile)
%}

%create_constructor(Generator)

%include "libcellml/types.h"
%include "libcellml/generator.h"
