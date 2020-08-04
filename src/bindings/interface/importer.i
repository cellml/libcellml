%module(package="libcellml") importer

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Importer
"Manages all importing operations between CellML models.";

%feature("docstring") libcellml::Importer::resolveImports
"Resolves all imports in this model.

Resolves all component and units imports by loading the
models from local disk through relative URLs. The ``baseFile`` is used to
determine the full path to the source model relative to this one.";

%feature("docstring") libcellml::Importer::flatten
"Instantiate all imported components and units and return a self-contained model.";

%feature("docstring") libcellml::Importer::libraryCount
"Returns the number of models loaded into the importer's library."

%feature("docstring") libcellml::Importer::library
"Returns the model instance stored at the given URL in the library.
The URL string must be the absolute path to the document, including both the filename
and the baseFile path."

%feature("docstring") libcellml::Importer::addModel
"Manually add a local model instance into the library under the URL key provided.
Returns True if the model was added, and False if the URL key already exists."

%feature("docstring") libcellml::Importer::replaceModel
"Manually replace an existing library model instance with the one provided.
Returns True if the URL key is found in the library and the model is added,
and False if the URL key does not exist."

%feature("docstring") libcellml::Importer::externalDependencyCount
"Returns the number of external dependencies accessed while resolving all
the models passed to this importer."

%feature("docstring") libcellml::Importer::externalDependency
"Returns a pairs of strings at the given index. The first item in the pair is the external URL
at which imports for models which have been resolved by the importer were accessed (and under
which are now stored in the library). The second item is the import reference."

%feature("docstring") libcellml::Importer::clearImports
"Clears the links with other models from all import sources."

%{
#include "libcellml/importer.h"
%}

%create_constructor(Importer)

%include "libcellml/types.h"
%include "libcellml/importer.h"
