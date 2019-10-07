%module(package="libcellml") namedentity

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%feature("docstring") libcellml::NamedEntity
"Abstract base class for all nameable libCellML classes.";

%feature("docstring") libcellml::NamedEntity::name
"Returns this entity's name (empty string if not set).";

%feature("docstring") libcellml::NamedEntity::setName
"Sets this entity's name (empty string to unset).";

%{
#include "libcellml/namedentity.h"
%}

%ignore libcellml::NamedEntity::NamedEntity(NamedEntity &&);
%ignore libcellml::NamedEntity::operator =;

%include "libcellml/namedentity.h"
