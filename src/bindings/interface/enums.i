%module(package="libcellml") enums

#define LIBCELLML_EXPORT

%{
#include "libcellml/enums.h"
%}

%ignore libcellml::cellMLElementAsString;

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%include "libcellml/enums.h"
