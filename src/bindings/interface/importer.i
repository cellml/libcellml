%module(package="libcellml") importer

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Importer
"Imports CellML objects.";

%feature("docstring") libcellml::Importer::resolveImports
"Resolves all imports in this model.

Resolves all :class:`Component` and :class:`Units` imports by loading the
models from local disk through relative urls. The ``baseFile`` is used to
determine the full path to the source model relative to this one.";

%feature("docstring") libcellml::Importer::flatten
"Instantiate all imported Components and Units and return a self-contained model.";

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
