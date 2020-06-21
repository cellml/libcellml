%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Annotator
"Holds functionality for annotation.";

%feature("docstring") libcellml::Annotator::build
"Build map for given model.";

// %feature("docstring") libcellml::Annotator::itemFromId
// "Retrieves an ``Entity`` for a given id.";

%{
#include "libcellml/annotator.h"
%}

%create_constructor(Annotator)

%include "libcellml/types.h"
%include "libcellml/annotator.h"
