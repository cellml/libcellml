%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%import "types.i"
%import "std_string.i"

%feature("docstring") libcellml::Entity
"Abstract base class for all libCellML core classes."

%feature("docstring") libcellml::Entity::id
"Returns the `id` document identifier for this entity, or an empty string if
not set.";

%feature("docstring") libcellml::Entity::setId
"Set the `id` document identifier for this entity (use empty string to
unset).";

%feature("docstring") libcellml::Entity::clearParent
"Removes any parent set for this entity.";

%feature("docstring") libcellml::Entity::parent
"Returns the parent of the CellML Entity (or `None` if not set).";

%feature("docstring") libcellml::Entity::getParentComponent
"Returns the parent component of the CellML Entity (or `None` if not set).";

%feature("docstring") libcellml::Entity::getParentModel
"Returns the parent model of the CellML Entity (or `None` if not set).";

%feature("docstring") libcellml::Entity::hasParent
"Tests if this entity, or any of its parent entities, have the given entity as
parent.";

%feature("docstring") libcellml::Entity::setParent
"Set the parent of the entity to the given Model or Component.";

%{
#include "libcellml/entity.h"
%}

%ignore libcellml::Entity::Entity(Entity &&);
%ignore libcellml::Entity::operator =;

%include "libcellml/types.h"
%include "libcellml/entity.h"
