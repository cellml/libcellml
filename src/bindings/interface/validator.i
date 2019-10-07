%module(package="libcellml") validator

#define LIBCELLML_EXPORT

%import "types.i"
%import "logger.i"

%feature("docstring") libcellml::Validator
"Validates CellML objects.";

%feature("docstring") libcellml::Validator::validateModel
"Validate the given `model` and its encapsulated entities using the CellML 2.0
Specification. Any errors will be logged in the `Validator`.";

%{
#include "libcellml/validator.h"
%}

%ignore libcellml::Validator::Validator(Validator &&);
%ignore libcellml::Validator::operator =;

%include "libcellml/types.h"
%include "libcellml/validator.h"
