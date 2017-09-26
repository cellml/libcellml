%module(package="libcellml") validator

#define LIBCELLML_EXPORT

%import "types.i"
%import "logger.i"

%{
#include "libcellml/validator.h"
%}

%ignore libcellml::Validator::Validator(Validator &&);
%ignore libcellml::Validator::operator =;

%include "libcellml/types.h"
%include "libcellml/validator.h"
