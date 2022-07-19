%module(package="libcellml") parser

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Parser
"Can parse Models encoded as XML strings.";

%feature("docstring") libcellml::Parser::parseModel
"Parses a string and returns a :class:`Model`.";

%feature("docstring") libcellml::Parser::parse1XModel
"Parses a string describing a CellML 1.0 or CellML 1.1 model and returns a :class:`Model`.";

%{
#include "libcellml/parser.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(Parser)

%include "libcellml/types.h"
%include "libcellml/parser.h"
