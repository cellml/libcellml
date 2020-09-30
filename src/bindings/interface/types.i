/*
Provides support for shared pointers declared in types.h

Only meant to be included, shouldn't be passed to cmake as a module!
*/
%include <std_shared_ptr.i>

%shared_ptr(libcellml::Analyser)
%shared_ptr(libcellml::AnalyserEquation)
%shared_ptr(libcellml::AnalyserEquationAst)
%shared_ptr(libcellml::AnalyserExternalVariable)
%shared_ptr(libcellml::AnalyserModel)
%shared_ptr(libcellml::AnalyserVariable)
%shared_ptr(libcellml::Component)
%shared_ptr(libcellml::ComponentEntity)
%shared_ptr(libcellml::Entity)
%shared_ptr(libcellml::Generator)
%shared_ptr(libcellml::GeneratorProfile)
%shared_ptr(libcellml::Importer)
%shared_ptr(libcellml::ImportSource)
%shared_ptr(libcellml::ImportedEntity)
%shared_ptr(libcellml::Issue)
%shared_ptr(libcellml::Logger)
%shared_ptr(libcellml::Model)
%shared_ptr(libcellml::NamedEntity)
%shared_ptr(libcellml::Parser)
%shared_ptr(libcellml::Printer)
%shared_ptr(libcellml::Reset)
%shared_ptr(libcellml::Units)
%shared_ptr(libcellml::Validator)
%shared_ptr(libcellml::Variable)

// Shared typemaps

%typemap(in) libcellml::AnalyserEquationAst::Type (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::ASSIGNMENT, int) || %static_cast($type::NAN, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::GeneratorProfile::Profile (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::C, int) || %static_cast($type::PYTHON, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::Issue::Cause (int val, int ecode) {
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

%typemap(in) libcellml::Issue::Level (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::ERROR, int) || %static_cast($type::MESSAGE, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::Issue::ReferenceRule (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::UNDEFINED, int) || %static_cast($type::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}

%typemap(in) libcellml::Units::Prefix (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::YOTTA, int) || %static_cast($type::YOCTO, int) < val) {
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
    if (val < %static_cast($type::AMPERE, int) || %static_cast($type::WEBER, int) < val) {
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
    if (val < %static_cast($type::NONE, int) || %static_cast($type::PUBLIC_AND_PRIVATE, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val,$basetype);
  }
}
