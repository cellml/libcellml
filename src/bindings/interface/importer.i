%module(package="libcellml") importer

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "enumerations.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Importer
"Resolves imported entities.";

%feature("docstring") libcellml::Importer::resolveImports
"Resolves imported entities in a class:`Model` relative to a specified location";

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
