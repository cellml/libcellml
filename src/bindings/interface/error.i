%module(package="libcellml") error

#define LIBCELLML_EXPORT

%import "types.i"

%{
#include "libcellml/error.h"
%}

%ignore libcellml::Error::Error(Error &&);
%ignore libcellml::Error::operator =;

%include "libcellml/exportdefinitions.h"
%include "libcellml/specificationrules.h"
%include "libcellml/types.h"
%include "libcellml/error.h"
