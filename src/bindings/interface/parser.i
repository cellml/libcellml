%module(package="libcellml") parser

#define LIBCELLML_EXPORT

%include "std_string.i"

%import "types.i"
%import "logger.i"
%import "enumerations.i"

%feature("docstring") libcellml::Parser
"Can parse Models encoded as XML strings.";

%feature("docstring") libcellml::Parser::parseModel
"Parses a string and returns a :class:`Model`.";

%{
#include "libcellml/parser.h"
%}

%ignore libcellml::Parser::Parser(Parser &&);
%ignore libcellml::Parser::operator =;

%include "libcellml/types.h"
%include "libcellml/parser.h"
