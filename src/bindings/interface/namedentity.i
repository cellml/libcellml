%module(package="libcellml") namedentity

#define LIBCELLML_EXPORT

%import "entity.i"

%{
#include "libcellml/namedentity.h"
%}

%include "libcellml/namedentity.h"
