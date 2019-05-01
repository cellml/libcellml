%module(package="libcellml") units

#define LIBCELLML_EXPORT

%import "types.i"
%import "enumerations.i"
%import "importedentity.i"

%ignore libcellml::Units::Units(Units &&);
%ignore libcellml::Units::operator =;

// Add typemaps to fix string ref inputs (fixes memory leak issues)
%include "typemaps.i"
%apply std::string &OUTPUT { std::string &reference };
%apply std::string &OUTPUT { std::string &prefix };
%apply double &OUTPUT { double &exponent };
%apply double &OUTPUT { double &multiplier };
%apply std::string &OUTPUT { std::string &id };
// Add typemaps for reference arguments used to return attributes
%apply std::string &INPUT { const std::string &reference };
%apply std::string &INPUT { const std::string &prefix };
%apply std::string &INPUT { const std::string &id };

// Remove methods which cause conflicts for languages with bad enum support
// (e.g. Python)
%ignore libcellml::Units::getUnitAttributes(StandardUnit standardRef,
 std::string &prefix, double &exponent, double &multiplier, std::string &id) const;
%ignore libcellml::Units::removeUnit(StandardUnit standardRef);
// This one causes confusion: addUnit(1, 1.0) --> (StandardUnit, double exp)
// but: addUnit(1, 1) --> (StandardUnit, Prefix, default=1, default=1)
%ignore libcellml::Units::addUnit(StandardUnit standardRef, double exponent);

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

where `prefix` is also allowed to be an integer.";

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

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Units {
        bool removeUnit(long index) {
            if(index < 0) return false;
            return $self->removeUnit((size_t)index);
        }
    }
#endif

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
