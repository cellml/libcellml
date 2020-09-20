%module(package="libcellml") generator

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"

%import "analysermodel.i"
%import "generatorprofile.i"

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

%create_constructor(Generator)

%include "libcellml/generator.h"
