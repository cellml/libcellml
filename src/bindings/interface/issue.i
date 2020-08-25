%module(package="libcellml") issue

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
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

%feature("docstring") libcellml::Issue::setCause
"Sets the ``cause`` of this issue.";

%feature("docstring") libcellml::Issue::level
"Get the ``level`` of this issue. If no level has been set for this issue,
Level::ERROR will be returned.";

%feature("docstring") libcellml::Issue::setLevel
"Sets the ``level`` of this issue.";

%feature("docstring") libcellml::Issue::referenceRule
"Get the :class:`ReferenceRule` of this issue.";

%feature("docstring") libcellml::Issue::setReferenceRule
"Sets the :class:`ReferenceRule` for this issue.";

%feature("docstring") libcellml::Issue::url
"Get the URL for more information about this issue.";

%feature("docstring") libcellml::Issue::referenceHeading
"Returns the CellML 2.0 Specification heading associated with the
:class:`ReferenceRule` for this issue (empty string if not set).";

%feature("docstring") libcellml::Issue::component
"Returns the :class:`Component` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setComponent
"Sets the :class:`Component` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::componentRef
"Returns the :class:`Component` whose encapsulation is relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setComponentRef
"Sets the :class:`Component` whose encapsulation is relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::importSource
"Returns the :class:`ImportSource` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setImportSource
"Sets the :class:`ImportSource` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::model
"Returns the :class:`Model` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setModel
"Sets the :class:`Model` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::encapsulation
"Returns the :class:`Model` whose encapsulation is relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setEncapsulation
"Sets the :class:`Model` whose encapsulation is relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::units
"Get the :class:`Units` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setUnits
"Sets the :class`Units` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::unit
"Get the :class:`UnitItem` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setUnit
"Sets the :class`UnitItem` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::variable
"Get the :class:`Variable` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setVariable
"Sets the :class:`Variable` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::reset
"Get the :class:`Reset` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setReset
"Sets the :class:`Reset` relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::math
"Get the :class:`Component` containing the MathML relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setMath
"Sets the :class:`Component` containing the MathML relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::connection
"Get the :class:`VariablePair` representing the connection relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setConnection
"Sets the :class:`VariablePair` representing the connection relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::mapVariables
"Get the :class:`VariablePair` representing the equivalence relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setMapVariables
"Sets the :class:`VariablePair` representing the equivalence relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::resetValue
"Get the :class:`Reset` containing the reset value relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setResetValue
"Sets the :class:`Reset` containing the reset value relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::testValue
"Get the :class:`Reset` containing the test value relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setTestValue
"Sets the :class:`Reset` containing the test value relevant to this issue (``None`` to unset).";

%feature("docstring") libcellml::Issue::item
"Get the :class:`AnyItem` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setItem
"Sets the :class:`AnyItem` relevant to this issue (``None`` to unset).";

%{
#include "libcellml/issue.h"
%}

%create_constructor(Issue)
%extend libcellml::Issue {
    Issue(const ComponentPtr &component) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(component));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }
    Issue(const ImportSourcePtr &importSource) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(importSource));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }
    Issue(const ModelPtr &model) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(model));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }
    Issue(const ResetPtr &reset) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(reset));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }
    Issue(const UnitsPtr &units) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(units));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }
    Issue(const VariablePtr &variable) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(variable));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }
}

%include "libcellml/enums.h"
%include "libcellml/exportdefinitions.h"
%include "libcellml/types.h"
%include "libcellml/issue.h"
