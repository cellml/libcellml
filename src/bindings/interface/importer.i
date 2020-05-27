%module(package="libcellml") importer

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Importer
"Imports CellML objects.";

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
