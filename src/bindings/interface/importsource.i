%module(package="libcellml") importsource

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%feature("docstring") libcellml::ImportSource
"The `ImportSource` class is for defining a location at which a CellML model is
expected to be obtainable (the 'source'). The `ImportSource` also acts as a
handle to indicate that imported entities originate from the same instance of
that imported source.";

%feature("docstring") libcellml::ImportSource::url
"Returns the URL of the source model (empty string if not set).";

%feature("docstring") libcellml::ImportSource::setUrl
"Sets the source model URL that this import source refers to (empty string to
unset).";

%feature("docstring") libcellml::ImportSource::model
"Returns the Model that has been assigned to resolve this ImportSource.";

%feature("docstring") libcellml::ImportSource::setModel
"Sets the Model to resolve this ImportSource.";

%feature("docstring") libcellml::ImportSource::hasModel
"Returns True if this ImportSource has been resolved, False otherwise.";

%{
#include "libcellml/importsource.h"
%}

%ignore libcellml::ImportSource::ImportSource(ImportSource &&);
%ignore libcellml::ImportSource::operator =;

%include "libcellml/types.h"
%include "libcellml/importsource.h"
