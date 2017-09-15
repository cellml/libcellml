%module(package="libcellml") units

%include "std_string.i"

libcellml::Units::addUnit(std::string const &);

#define LIBCELLML_EXPORT
%import "enumerations.i"

%import "importedentity.i"

%{
#include "libcellml/units.h"
%}

%ignore libcellml::Units::Units(Units &&);
%ignore libcellml::Units::operator =;

%include "libcellml/types.h"
%include "libcellml/units.h"
