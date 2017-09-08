%module(package="libcellml") entity
%include "std_string.i"

#define LIBCELLML_EXPORT

%{
#include "libcellml/entity.h"
%}

%include "libcellml/types.h"
%include "libcellml/entity.h"
