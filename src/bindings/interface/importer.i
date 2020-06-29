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

%feature("docstring") libcellml::Importer::libraryCount
"Returns the number of models loaded into the importer's library."

%feature("docstring") libcellml::Importer::library
"Returns the model instance stored at the given url in the library.
The url string must be the absolute path to the document, including both the filename
and the baseFile path."

%feature("docstring") libcellml::Importer::addModel
"Manually add a local model instance into the library under the url key provided.
Returns true if the model was added, and false if the url key already exists."

%feature("docstring") libcellml::Importer::replaceModel
"Manually replace an existing library model instance with the one provided.
Returns true if the url key is found in the library and the model is added,
and false if the url key does not exist."

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
