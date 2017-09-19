%module(package="libcellml") variable

#define LIBCELLML_EXPORT

%import "types.i"
%import "namedentity.i"

%{
#include "libcellml/variable.h"
%}

%ignore libcellml::Variable::Variable(Variable &&);
%ignore libcellml::Variable::operator =;

%include "libcellml/types.h"
%include "libcellml/variable.h"
