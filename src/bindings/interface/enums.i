%module(package="libcellml") enums

#define LIBCELLML_EXPORT

%typemap(in) libcellml::ItemType (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::COMPONENT, int) || %static_cast($type::XML, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%{
#include "libcellml/enums.h"
%}

%include "libcellml/enums.h"


