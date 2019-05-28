%module(package="libcellml") orderedentity

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%feature("docstring") libcellml::OrderedEntity
"Abstract base class for entities that can be ordered relative to others.";

%feature("docstring") libcellml::OrderedEntity::getOrder
"Returns the order for this entity as an integer value.";

%feature("docstring") libcellml::OrderedEntity::setOrder
"Set the order for this entity.  The order value must be an integer.";

%feature("docstring") libcellml::OrderedEntity::unsetOrder
"Sets the state of the order to unset.";

%feature("docstring") libcellml::OrderedEntity::isOrderSet
"Returns True if the order is set, False otherwise.";

%{
#include <memory>
#include "libcellml/orderedentity.h"
%}

%ignore libcellml::OrderedEntity::OrderedEntity(OrderedEntity &&);
%ignore libcellml::OrderedEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/orderedentity.h"
