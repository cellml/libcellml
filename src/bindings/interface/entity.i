%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%import "types.i"
%import "std_string.i"

%{
#include "libcellml/entity.h"
%}

%ignore libcellml::Entity::Entity(Entity &&);
%ignore libcellml::Entity::operator =;

%include "libcellml/types.h"
%include "libcellml/entity.h"
