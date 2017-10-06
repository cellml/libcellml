%module(package="libcellml") units

#define LIBCELLML_EXPORT

%import "enumerations.i"
%import "importedentity.i"

%ignore libcellml::Units::Units(Units &&);
%ignore libcellml::Units::operator =;

// Add typemaps to fix string ref inputs (fixes memory leak issues)
%include "typemaps.i"
%apply std::string &OUTPUT { std::string& reference };
%apply std::string &OUTPUT { std::string& prefix };
%apply double &OUTPUT { double& exponent };
%apply double &OUTPUT { double& multiplier };
// Add typemaps for reference arguments used to return attributes
%apply std::string &INPUT { const std::string &reference };
%apply std::string &INPUT { const std::string &prefix };

// Remove methods which cause conflicts for languages with bad enum support
// (e.g. Python)
%ignore libcellml::Units::getUnitAttributes(StandardUnit standardRef,
 std::string &prefix, double &exponent, double &multiplier) const;
%ignore libcellml::Units::removeUnit(StandardUnit standardRef);

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Units {
        bool removeUnit(long index) {
            if(index < 0) return false;
            return $self->removeUnit(static_cast<size_t>(index));
        }
    }
#endif

%typemap(in) libcellml::Prefix prefix (int val, int ecode) {
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

%feature("docstring") libcellml::Units
"Represents a CellML Units definition.";

%feature("docstring") libcellml::Units::addUnit
"Lets users add a Unit to this definition.

Possible signatures:

 - addUnit(reference, prefix, exponent=1, multiplier=1)
 - addUnit(reference, exponent)
 - addUnit(reference)

where `reference` can be a string or a StandardUnits. And `prefix` can be a
string or Prefix.

In addition, there's a signature

 - addUnit(reference, prefix, exponent, multiplier=1)

where `prefix` is also allowed to be a float.";

%feature("docstring") libcellml::Units::removeUnit
"Removes the unit specified by index, reference, or StandardUnit.

Only the first matching unit is removed.

`True` is returned on success.";

%feature("docstring") libcellml::Units::removeAllUnits
"Remove all units stored in this Units object. ";

%feature("docstring") libcellml::Units::isBaseUnit
"Tests if this is a base unit.";

%feature("docstring") libcellml::Units::getUnitAttributes
"Returns the attributes of the unit specified by index, reference, or
StandardUnit.";

%feature("docstring") libcellml::Units::unitCount
"Returns the number of units contained by this units object.";

%feature("docstring") libcellml::Units::setSourceUnits
"Makes this Units an imported units by defining an `ImportSource` from which to
extract the units with the given `name`.";

%{
#include "libcellml/units.h"
%}

// The name 'reference' has been typemapped above, which causes an issue for
// the removeUnit(reference) method. This is solved below by creating a new
// method removeUnit(ref) and telling swig not to use removeUnit(reference).
%extend libcellml::Units {
    bool removeUnit(const std::string &ref) {
        return $self->removeUnit(ref);
    }
}
%ignore libcellml::Units::removeUnit(const std::string &reference);

%include "libcellml/types.h"
%include "libcellml/units.h"
