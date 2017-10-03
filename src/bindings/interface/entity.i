%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%import "types.i"
%import "std_string.i"

%feature("docstring") libcellml::Entity
"Abstract base class for all libCellML core classes."

%feature("docstring") libcellml::Entity::getId
"Returns the `id` document identifier for this entity.";

%feature("docstring") libcellml::Entity::setId
"Set the `id` document identifier for this entity.";

%feature("docstring") libcellml::Entity::clearParent
"";

%feature("docstring") libcellml::Entity::getParent
"Returns the parent of the CellML Entity (or `None` if not set).";

%feature("docstring") libcellml::Entity::hasParent
"";

%feature("docstring") libcellml::Entity::setParent
"";

%{
#include "libcellml/entity.h"
%}

%ignore libcellml::Entity::Entity(Entity &&);
%ignore libcellml::Entity::operator =;

%include "libcellml/types.h"
%include "libcellml/entity.h"
