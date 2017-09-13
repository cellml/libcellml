%module(package="libcellml") imports    // 'import' is a Python keyword!

#define LIBCELLML_EXPORT

%import "types.i"
%import "entity.i"

%{
#include "libcellml/import.h"
%}

%include "libcellml/types.h"
%include "libcellml/import.h"
