%module(package="libcellml") importer

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Importer
"Imports CellML objects.";

%feature("docstring") libcellml::Model::flatten
"Instantiate all imported Components and Units and return a self-contained model.";

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
