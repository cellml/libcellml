%module(package="libcellml") importsource

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%{
#include "libcellml/import.h"
%}

%ignore libcellml::Import::Import(Import &&);
%ignore libcellml::Import::operator =;

%include "libcellml/types.h"
%include "libcellml/import.h"
