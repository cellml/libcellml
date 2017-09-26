%module(package="libcellml") units

#define LIBCELLML_EXPORT

%import "enumerations.i"
%import "importedentity.i"

%ignore libcellml::Units::Units(Units &&);
%ignore libcellml::Units::operator =;

// Fix return reference arguments for getUnitAttributes:
//%ignore libcellml::Units::getUnitAttributes(size_t index, std::string& reference, std::string &prefix, double &exponent, double &multiplier) const;
%ignore libcellml::Units::getUnitAttributes(const std::string &reference, std::string &prefix, double &exponent, double &multiplier) const;
%ignore libcellml::Units::getUnitAttributes(StandardUnit standardRef, std::string &prefix, double &exponent, double &multiplier) const;
%include "typemaps.i"
%include "std_string.i"
%apply std::string &OUTPUT { std::string& reference };
%apply std::string &OUTPUT { std::string& prefix };
%apply double &OUTPUT { double& exponent };
%apply double &OUTPUT { double& multiplier };

// Fix memory leaks
%apply std::string &INPUT { const std::string &reference };
%apply std::string &INPUT { const std::string &prefix };


%{
#include "libcellml/units.h"
%}

%include "libcellml/types.h"
%include "libcellml/units.h"
