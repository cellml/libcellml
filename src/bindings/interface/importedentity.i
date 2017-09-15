%module(package="libcellml") importedentity

#define LIBCELLML_EXPORT

%import "types.i"
%import "namedentity.i"

%{
#include "libcellml/importedentity.h"
%}

%ignore libcellml::ImportedEntity::ImportedEntity(ImportedEntity &&);
%ignore libcellml::ImportedEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/importedentity.h"
