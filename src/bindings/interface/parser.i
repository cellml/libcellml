%module(package="libcellml") parser

#define LIBCELLML_EXPORT

%import "types.i"
%import "logger.i"
%import "enumerations.i"

%{
#include "libcellml/parser.h"
%}

%ignore libcellml::Parser::Parser(Parser &&);
%ignore libcellml::Parser::operator =;

%include "libcellml/types.h"
%include "libcellml/parser.h"
