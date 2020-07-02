%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"

#ifdef SWIGPYTHON
%import "analysermodel.i"
%import "generatorprofile.i"
#endif

%feature("docstring") libcellml::Generator
"Creates a :class:`Generator` object.";

%feature("docstring") libcellml::Generator::profile
"Returns the :enum:`Profile` type.";

%feature("docstring") libcellml::Generator::setProfile
"Sets this :class:`Generator`'s profile.";

%feature("docstring") libcellml::Generator::interfaceCode
"Returns the interface code for an :class:`AnalyserModel`.";

%feature("docstring") libcellml::Generator::implementationCode
"Returns the implementation code for an :class:`AnalyserModel`.";

%{
#include "libcellml/generator.h"
%}

%pythonappend libcellml::Generator::Generator %{
from libcellml import GeneratorProfile
profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
self.setProfile(profile)
%}

%create_constructor(Generator)

%include "libcellml/generator.h"
