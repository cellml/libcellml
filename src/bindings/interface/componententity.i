%module(package="libcellml") componententity

#define LIBCELLML_EXPORT

%import "types.i"
%import "importedentity.i"

%{
#include "libcellml/componententity.h"
%}

%ignore libcellml::ComponentEntity::ComponentEntity(ComponentEntity &&);
%ignore libcellml::ComponentEntity::operator =;

%include "libcellml/types.h"
%include "libcellml/componententity.h"
