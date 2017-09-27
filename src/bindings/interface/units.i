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
            return $self->removeUnit(size_t(index));
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
