%module(package="libcellml") parser

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "enumerations.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Parser
"Can parse Models encoded as XML strings.";

%feature("docstring") libcellml::Parser::parseModel
"Parses a string and returns a :class:`Model`.";

%{
#include "libcellml/parser.h"
%}

%create_constructor(Parser)

%include "libcellml/types.h"
%include "libcellml/parser.h"
