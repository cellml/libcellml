%module(package="libcellml") strict

#define LIBCELLML_EXPORT

%import "types.i"

%feature("docstring") libcellml::Strict
"Abstract base class for entities that can be imported.";

%feature("docstring") libcellml::Strict::isStrict
"Returns an ImportSource if this entity is imported, else `None`.";

%feature("docstring") libcellml::Strict::setStrict
"Set the ImportSource for this entity (use `None` to unset).";

%{
#include "libcellml/types.h"
#include "libcellml/strict.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%ignore libcellml::Strict::Strict();

%include "libcellml/strict.h"
