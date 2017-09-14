%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%import "std_string.i"

%{
#include "libcellml/entity.h"
%}

%include "libcellml/types.h"
%include "libcellml/entity.h"
