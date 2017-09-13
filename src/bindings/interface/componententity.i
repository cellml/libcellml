%module(package="libcellml") componententity

#define LIBCELLML_EXPORT

%import "types.i"
%import "importedentity.i"

%{
#include "libcellml/componententity.h"
%}

%include "libcellml/types.h"
%include "libcellml/componententity.h"
