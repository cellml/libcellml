%module(package="libcellml") importsource

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%{
#include "libcellml/importsource.h"
%}

%ignore libcellml::ImportSource::ImportSource(ImportSource &&);
%ignore libcellml::ImportSource::operator =;

%include "libcellml/types.h"
%include "libcellml/importsource.h"
