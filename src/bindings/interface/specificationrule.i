%module(package="libcellml") specificationrule

#define LIBCELLML_EXPORT

%{
#include "libcellml/specificationrules.h"
%}

%include "libcellml/specificationrules.h"
