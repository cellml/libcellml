%module(package="libcellml") namedentity

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%{
#include "libcellml/namedentity.h"
%}

%ignore libcellml::NamedEntity::NamedEntity(NamedEntity &&);
%ignore libcellml::NamedEntity::operator =;

%include "libcellml/namedentity.h"
