%module(package="libcellml") generatorcontext

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"

%feature("docstring") libcellml::GeneratorContext
"Creates a :class:`GeneratorContext` object.";

%{
#include "libcellml/generatorcontext.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(GeneratorContext)

%include "libcellml/generatorcontext.h"
