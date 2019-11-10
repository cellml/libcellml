%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "types.i"

%feature("docstring") libcellml::Entity
"Abstract base class for all libCellML core classes."

%feature("docstring") libcellml::Entity::id
"Returns the `id` document identifier for this entity, or an empty string if
not set.";

%feature("docstring") libcellml::Entity::setId
"Set the `id` document identifier for this entity (use empty string to
unset).";

%feature("docstring") libcellml::Entity::removeParent
"Removes any parent set for this entity.";

%feature("docstring") libcellml::Entity::parent
"Returns the parent of the CellML Entity (or `None` if not set).";

%feature("docstring") libcellml::Entity::hasParent
"Tests if this entity has a parent. Returns true if it has a parent and false otherwise.";

%feature("docstring") libcellml::Entity::hasAncestor
"Tests if any of the ancestors of this entity have the given entity as a parent.";

%feature("docstring") libcellml::Entity::setParent
"Set the parent of the entity to the given entity.  This should ostensibly be a Model or a Component.";

%{
#include "libcellml/entity.h"
%}

%ignore libcellml::Entity::Entity();

%include "libcellml/types.h"
%include "libcellml/entity.h"
