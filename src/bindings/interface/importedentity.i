%module(package="libcellml") importedentity

#define LIBCELLML_EXPORT

%import "types.i"
%import "namedentity.i"

%{
#include "libcellml/importedentity.h"
%}

%include "libcellml/types.h"
%include "libcellml/importedentity.h"
