/*
Provides support for shared pointers declared in types.h

Only meant to be included, shouldn't be passed to cmake as a module!
*/
%include <std_shared_ptr.i>

%shared_ptr(libcellml::Component)
%shared_ptr(libcellml::ComponentEntity)
%shared_ptr(libcellml::Entity)
%shared_ptr(libcellml::Error)
%shared_ptr(libcellml::ImportSource)
%shared_ptr(libcellml::ImportedEntity)
%shared_ptr(libcellml::Model)
%shared_ptr(libcellml::NamedEntity)
%shared_ptr(libcellml::OrderedEntity)
%shared_ptr(libcellml::Reset)
%shared_ptr(libcellml::Units)
%shared_ptr(libcellml::Variable)
%shared_ptr(libcellml::When)

// Shared typemaps

%typemap(in) libcellml::Prefix (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast(libcellml::Prefix::YOTTA, int) || %static_cast(libcellml::Prefix::YOCTO, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::Units::StandardUnit (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast(libcellml::Units::StandardUnit::AMPERE, int) || %static_cast(libcellml::Units::StandardUnit::WEBER, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::Error::Kind (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast(libcellml::Error::Kind::COMPONENT, int) || %static_cast(libcellml::Error::Kind::XML, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::SpecificationRule (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast(libcellml::SpecificationRule::UNDEFINED, int) || %static_cast(libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE2, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::Variable::InterfaceType (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast(libcellml::Variable::InterfaceType::NONE, int) || %static_cast(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}


