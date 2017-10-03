%module(package="libcellml") error

#define LIBCELLML_EXPORT

%import "std_string.i"

%import "types.i"

%feature("docstring") libcellml::Error
"Base class for errors used with logger derived classes."

%feature("docstring") libcellml::Error::getDescription
"Get a string description for why this error was raised.";

%feature("docstring") libcellml::Error::setDescription
"Sets a string description for why this error was raised.";

%feature("docstring") libcellml::Error::getKind
"Get the `kind` of this error. If no kind has been set for this error, will
return Kind::UNDEFINED.";

%feature("docstring") libcellml::Error::isKind
"Tests if this error matches the given `kind`.";

%feature("docstring") libcellml::Error::setKind
"Sets the `kind` of this error.";

%feature("docstring") libcellml::Error::getRule
"Get the `SpecificationRule` of this error.";

%feature("docstring") libcellml::Error::setRule
"Sets the `SpecificationRule` for this error.";

%feature("docstring") libcellml::Error::getSpecificationHeading
"Returns the CellML 2.0 Specification heading associated with the
SpecificationRule for this error (empty string if not set).";

%feature("docstring") libcellml::Error::getComponent
"Returns the Component that this error is relevant to (or `None`).";

%feature("docstring") libcellml::Error::setComponent
"Sets the Component that this error is relevant to (`None` to unset).";

%feature("docstring") libcellml::Error::getImportSource
"Returns the ImportSource that this error is relevant to (or `None`).";

%feature("docstring") libcellml::Error::setImportSource
"Sets the ImportSource that this error is relevant to (`None` to unset).";

%feature("docstring") libcellml::Error::getModel
"Returns the Model that this error is relevant to (or `None`).";

%feature("docstring") libcellml::Error::setModel
"Sets the Model that this error is relevant to (`None` to unset).";

%feature("docstring") libcellml::Error::getUnits
"Get the Units that this error is relevant to (or `None`).";

%feature("docstring") libcellml::Error::setUnits
"Sets the Units that this error is relevant to (`None` to unset).";

%feature("docstring") libcellml::Error::getVariable
"Get the variable that this error is relevant to (or `None`).";

%feature("docstring") libcellml::Error::setVariable
"Sets the Variable that this error is relevant to (`None` to unset).";

%{
#include "libcellml/error.h"
%}

%ignore libcellml::Error::Error(Error &&);
%ignore libcellml::Error::operator =;

%include "libcellml/exportdefinitions.h"
%include "libcellml/specificationrules.h"
%include "libcellml/types.h"
%include "libcellml/error.h"
