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
"Get the ``kind`` of this error. If no kind has been set for this error, will
return Kind::UNDEFINED.";

%feature("docstring") libcellml::Error::isKind
"Tests if this error matches the given ``kind``.";

%feature("docstring") libcellml::Error::setKind
"Sets the ``kind`` of this error.";

%feature("docstring") libcellml::Error::getRule
"Get the :class:`SpecificationRule` of this error.";

%feature("docstring") libcellml::Error::setRule
"Sets the :class:`SpecificationRule` for this error.";

%feature("docstring") libcellml::Error::getSpecificationHeading
"Returns the CellML 2.0 Specification heading associated with the
:class:`SpecificationRule` for this error (empty string if not set).";

%feature("docstring") libcellml::Error::getComponent
"Returns the :class:`Component` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setComponent
"Sets the :class:`Component` that this error is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Error::getImportSource
"Returns the :class:`ImportSource` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setImportSource
"Sets the :class:`ImportSource` that this error is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Error::getModel
"Returns the :class:`Model` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setModel
"Sets the :class:`Model` that this error is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Error::getUnits
"Get the :class:`Units` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setUnits
"Sets the :class`Units` that this error is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Error::getVariable
"Get the :class:`Variable` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setVariable
"Sets the :class:`Variable` that this error is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Error::getReset
"Get the :class:`Reset` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setReset
"Sets the :class:`Reset` that this error is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Error::getWhen
"Get the :class:`When` that this error is relevant to (or ``None``).";

%feature("docstring") libcellml::Error::setWhen
"Sets the :class:`When` that this error is relevant to (``None`` to unset).";

%{
#include "libcellml/error.h"
%}

%ignore libcellml::Error::Error(Error &&);
%ignore libcellml::Error::operator =;

%include "libcellml/exportdefinitions.h"
%include "libcellml/specificationrules.h"
%include "libcellml/types.h"
%include "libcellml/error.h"
