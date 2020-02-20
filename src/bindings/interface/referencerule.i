%module(package="libcellml") referencerule

#define LIBCELLML_EXPORT

%{
#include "libcellml/referencerules.h"
%}

%include "libcellml/referencerules.h"
