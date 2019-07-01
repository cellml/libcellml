%module(package="libcellml") issue

#define LIBCELLML_EXPORT

%import "std_string.i"

%import "types.i"

%feature("docstring") libcellml::Issue
"Base class for issues used with logger derived classes."

%feature("docstring") libcellml::Issue::description
"Get a string description for why this issue was raised.";

%feature("docstring") libcellml::Issue::setDescription
"Sets a string description for why this issue was raised.";

%feature("docstring") libcellml::Issue::cause
"Get the ``cause`` of this issue. If no cause has been set for this issue, will
return Cause::UNDEFINED.";

%feature("docstring") libcellml::Issue::isCause
"Tests if this issue matches the given ``cause``.";

%feature("docstring") libcellml::Issue::setCause
"Sets the ``cause`` of this issue.";

%feature("docstring") libcellml::Issue::type
"Get the ``type`` of this issue. If no type has been set for this issue, will
return Type::ERROR.";

%feature("docstring") libcellml::Issue::isType
"Tests if this issue matches the given ``type``.";

%feature("docstring") libcellml::Issue::setType
"Sets the ``type`` of this issue.";

%feature("docstring") libcellml::Issue::rule
"Get the :class:`SpecificationRule` of this issue.";

%feature("docstring") libcellml::Issue::setRule
"Sets the :class:`SpecificationRule` for this issue.";

%feature("docstring") libcellml::Issue::specificationHeading
"Returns the CellML 2.0 Specification heading associated with the
:class:`SpecificationRule` for this issue (empty string if not set).";

%feature("docstring") libcellml::Issue::component
"Returns the :class:`Component` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setComponent
"Sets the :class:`Component` that this issue is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Issue::importSource
"Returns the :class:`ImportSource` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setImportSource
"Sets the :class:`ImportSource` that this issue is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Issue::model
"Returns the :class:`Model` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setModel
"Sets the :class:`Model` that this issue is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Issue::units
"Get the :class:`Units` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setUnits
"Sets the :class`Units` that this issue is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Issue::variable
"Get the :class:`Variable` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setVariable
"Sets the :class:`Variable` that this issue is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Issue::reset
"Get the :class:`Reset` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setReset
"Sets the :class:`Reset` that this issue is relevant to (``None`` to unset).";

%feature("docstring") libcellml::Issue::when
"Get the :class:`When` that this issue is relevant to (or ``None``).";

%feature("docstring") libcellml::Issue::setWhen
"Sets the :class:`When` that this issue is relevant to (``None`` to unset).";

%{
#include "libcellml/issue.h"
%}

%ignore libcellml::Issue::Issue(Issue &&);
%ignore libcellml::Issue::operator =;

%include "libcellml/exportdefinitions.h"
%include "libcellml/specificationrules.h"
%include "libcellml/types.h"
%include "libcellml/issue.h"
