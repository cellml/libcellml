%module(package="libcellml") component

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

%{
#include "libcellml/component.h"
%}

%ignore libcellml::Component::Component(Component &&);
%ignore libcellml::Component::operator =;

%include "libcellml/types.h"
%include "libcellml/component.h"
