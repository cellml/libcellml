%module(package="libcellml") version

#define LIBCELLML_EXPORT

%include "std_string.i"

%{
#include "libcellml/version.h"
%}

%include "libcellml/version.h"
