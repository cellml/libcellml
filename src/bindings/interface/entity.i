%module(package="libcellml") entity

#define LIBCELLML_EXPORT

%{
#include "libcellml/entity.h"
%}

//%include "libcellml/enumerations.h"
//%include "libcellml/exportdefinitions.h"
%include "libcellml/types.h"
%include "libcellml/entity.h"
