%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Annotator
"Validates CellML objects.";

%feature("docstring") libcellml::Annotator::test
"test";

%{
#include "libcellml/annotator.h"
%}

%create_constructor(Annotator)

%include "libcellml/types.h"
%include "libcellml/annotator.h"
