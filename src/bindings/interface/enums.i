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

%pythoncode %{
from enum import IntEnum
def redo(prefix):
    tmpD = {k:v for k,v in globals().items() if k.startswith(prefix + '_')}
    for k,v in tmpD.items():
        del globals()[k]
    tmpD = {k[len(prefix)+1:]:v for k,v in tmpD.items()}
    # globals()[prefix] = type(prefix,(),tmpD) # pre-Enum support
    globals()[prefix] = IntEnum(prefix,tmpD)
redo('CellMLElement')
del redo  # cleaning up the namespace
del IntEnum
%}
