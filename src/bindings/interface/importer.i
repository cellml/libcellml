%module(package="libcellml") importer

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Importer
"Resolves imported entities.";

%feature("docstring") libcellml::Importer::resolveImports
"Resolves imported entities in a class:`Model` relative to a specified location";

%feature("docstring") libcellml::Importer::flatten
"Instantiate all imported Components and Units to make the given Model self-contained.";

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
