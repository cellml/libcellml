%module(package="libcellml") importsource

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%feature("docstring") libcellml::ImportSource
"The `ImportSource` class is for defining a location at which a CellML model is
expected to be obtainable (the 'source'). The `ImportSource` also acts as a
handle to indicate that imported entities originate from the same instance of
that imported source.";

%feature("docstring") libcellml::ImportSource::getSource
"Returns the imported model source set in this instance (empty string if not
set).";

%feature("docstring") libcellml::ImportSource::setSource
"Sets the imported model source that this import source refers to (string to
unset).";

%{
#include "libcellml/importsource.h"
%}

%ignore libcellml::ImportSource::ImportSource(ImportSource &&);
%ignore libcellml::ImportSource::operator =;

%include "libcellml/types.h"
%include "libcellml/importsource.h"
