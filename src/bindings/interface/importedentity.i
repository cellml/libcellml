%module(package="libcellml") importedentity

#define LIBCELLML_EXPORT

%import "types.i"
%import "namedentity.i"

%feature("docstring") libcellml::ImportedEntity
"Abstract base class for entities that can be imported.";

%feature("docstring") libcellml::ImportedEntity::getImportSource
"Returns an ImportSource if this entity is imported, else `None`.";

%feature("docstring") libcellml::ImportedEntity::setImportSource
"Set the ImportSource for this entity (use `None` to unset).";

%feature("docstring") libcellml::ImportedEntity::getImportReference
"Returns the reference to the entity in the imported model, or an empty string
if not set.";

%feature("docstring") libcellml::ImportedEntity::setImportReference
"Set the import reference to an entity in the imported model (use an empty
string to unset).";

%feature("docstring") libcellml::ImportedEntity::isImport
"Test if this entity is imported.";

%{
#include "libcellml/importedentity.h"
%}

%ignore libcellml::ImportedEntity::ImportedEntity(ImportedEntity &&);
%ignore libcellml::ImportedEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/importedentity.h"
