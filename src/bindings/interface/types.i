/*
Provides support for shared pointers declared in types.h.
*/
%module(package="libcellml") types

#define LIBCELLML_EXPORT

%include <std_multimap.i>
%include <std_pair.i>
%include <std_shared_ptr.i>
%include <std_string.i>
%include <stdint.i>

%shared_ptr(libcellml::Analyser)
%shared_ptr(libcellml::AnalyserEquation)
%shared_ptr(libcellml::AnalyserEquationAst)
%shared_ptr(libcellml::AnalyserModel)
%shared_ptr(libcellml::AnalyserVariable)
%shared_ptr(libcellml::Annotator)
%shared_ptr(libcellml::Component)
%shared_ptr(libcellml::ComponentEntity)
%shared_ptr(libcellml::Entity)
%shared_ptr(libcellml::Generator)
%shared_ptr(libcellml::GeneratorProfile)
%shared_ptr(libcellml::Importer)
%shared_ptr(libcellml::ImportRequirement)
%shared_ptr(libcellml::ImportSource)
%shared_ptr(libcellml::ImportedEntity)
%shared_ptr(libcellml::Issue)
%shared_ptr(libcellml::Logger)
%shared_ptr(libcellml::Model)
%shared_ptr(libcellml::NamedEntity)
%shared_ptr(libcellml::Parser)
%shared_ptr(libcellml::Printer)
%shared_ptr(libcellml::Reset)
%shared_ptr(libcellml::Unit)
%shared_ptr(libcellml::Units)
%shared_ptr(libcellml::Validator)
%shared_ptr(libcellml::Variable)
%shared_ptr(libcellml::VariablePair)

%feature("docstring") libcellml::VariablePair
"A class for describing a variable pair.";

%feature("docstring") libcellml::VariablePair::create
"Create a variable pair object.";

%feature("docstring") libcellml::VariablePair::variable1
"Return the first variable in the pair of variables.";

%feature("docstring") libcellml::VariablePair::variable2
"Return the second variable in the pair of variables.";

%feature("docstring") libcellml::VariablePair::isValid
"Test if the pair is valid.";

%feature("docstring") libcellml::Unit
"A class for describing a unit.";

%feature("docstring") libcellml::Unit::create
"Create a Unit object.";

%feature("docstring") libcellml::Unit::units
"Return the units for the unit reference.";

%feature("docstring") libcellml::Unit::index
"Return the index for the unit reference.";

%feature("docstring") libcellml::Unit::isValid
"Test if the unit reference is valid.";

%feature("docstring") libcellml::ImportRequirement
"A class containing a URL and referenced Model.";

%feature("docstring") libcellml::ImportRequirement::create
"Create an ImportRequirement item.";

%feature("docstring") libcellml::ImportRequirement::url
"Return the URL of this requirement, relative to the importing model.";

%feature("docstring") libcellml::ImportRequirement::model
"Return the Model used by this requirement.";

%{
#include "libcellml/types.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%template() std::multimap< std::string, libcellml::CellmlElementType>;

// Shared typemaps

%typemap(in) libcellml::AnalyserEquationAst::Type (int val, int ecode) {
  ecode = SWIG_AsVal(int)($input, &val);
  if (!SWIG_IsOK(ecode)) {
    %argument_fail(ecode, "$type", $symname, $argnum);
  } else {
    if (val < %static_cast($type::ASSIGNMENT, int) || %static_cast($type::NAN, int) < val) {
      %argument_fail(ecode, "$type is not a valid value for the enumeration.", $symname, $argnum);
    }
    $1 = %static_cast(val, $basetype);
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
    $1 = %static_cast(val, $basetype);
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
    $1 = %static_cast(val, $basetype);
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
    $1 = %static_cast(val, $basetype);
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
    $1 = %static_cast(val, $basetype);
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
    $1 = %static_cast(val, $basetype);
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
    $1 = %static_cast(val, $basetype);
  }
}

%typemap(out) libcellml::Unit *Unit() {
  /*
  Here we take the returned value from the Constructor for this object and cast it
  to the pointer that it actually is.  Once that is done we can set the required resultobj.
  */
  std::shared_ptr<  libcellml::Unit > *smartresult = reinterpret_cast<std::shared_ptr<  libcellml::Unit > *>(result);
  resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_libcellml__Unit_t, SWIG_POINTER_NEW | SWIG_POINTER_OWN);
}

%typemap(out) libcellml::VariablePair *VariablePair() {
  /*
  Here we take the returned value from the Constructor for this object and cast it
  to the pointer that it actually is.  Once that is done we can set the required resultobj.
  */
  std::shared_ptr<  libcellml::VariablePair > *smartresult = reinterpret_cast<std::shared_ptr<  libcellml::VariablePair > *>(result);
  resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_libcellml__VariablePair_t, SWIG_POINTER_NEW | SWIG_POINTER_OWN);
}

%extend libcellml::Unit {
    Unit(const UnitsPtr &units, size_t index) {
        auto ptr = new std::shared_ptr<libcellml::Unit>(libcellml::Unit::create(units, index));
        return reinterpret_cast<libcellml::Unit *>(ptr);
    }
}

%extend libcellml::VariablePair {
    VariablePair(const VariablePtr &variable1, const VariablePtr &variable2) {
        auto ptr = new std::shared_ptr<libcellml::VariablePair>(libcellml::VariablePair::create(variable1, variable2));
        return reinterpret_cast<libcellml::VariablePair *>(ptr);
    }
}

%ignore libcellml::Unit::create;
%ignore libcellml::VariablePair::create;

%include "libcellml/types.h"
