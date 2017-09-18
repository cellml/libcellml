%module(package="libcellml") model

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

%{
#include "libcellml/model.h"
%}

%ignore libcellml::Model::Model(Model &&);
%ignore libcellml::Model::operator =;

%include "libcellml/types.h"
%include "libcellml/model.h"

