%module(package="libcellml") component

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

%{
#include "libcellml/component.h"
%}

%include "libcellml/types.h"
%include "libcellml/component.h"
