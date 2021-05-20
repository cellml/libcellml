%module(package="libcellml") issue

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "enums.i"
%import "types.i"

%feature("docstring") libcellml::Issue
"Base class for issues used with logger derived classes."

%feature("docstring") libcellml::Issue::description
"Get a string description for why this issue was raised.";

%feature("docstring") libcellml::Issue::setDescription
"Sets a string description for why this issue was raised.";

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

%feature("docstring") libcellml::Issue::unitsItem
"Get the :class:`UnitsItem` relevant to this issue (or ``None``).";

%feature("docstring") libcellml::Issue::setUnitsItem
"Sets the :class`UnitsItem` relevant to this issue (``None`` to unset).";

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

%feature("docstring") libcellml::Issue::cellmlElementType
"Get the type of this issue.";

%feature("docstring") libcellml::Issue::clear
"Clear the issue to its empty state.";

%{
#include "libcellml/issue.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.

from libcellml import CellmlElementType
%}

%create_constructor(Issue)

%ignore libcellml::Issue::item;
%ignore libcellml::Issue::setItem;

%extend libcellml::Issue {
    Issue(const ComponentPtr &component) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(component));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const ImportSourcePtr &importSource) {
        auto ptr = new std::shared_ptr<  libcellml::Issue >(libcellml::Issue::create(importSource));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const ModelPtr &model) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(model));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const ResetPtr &reset) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(reset));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const UnitsPtr &units) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(units));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const UnitsItemPtr &unitsItem) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(unitsItem));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const VariablePtr &variable) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(variable));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    Issue(const VariablePairPtr &pair) {
        auto ptr = new std::shared_ptr<libcellml::Issue>(libcellml::Issue::create(pair));
        return reinterpret_cast<libcellml::Issue *>(ptr);
    }

    %pythoncode %{
        def setItem(self, cellmlElementType, item):
            r"""Set the item by item type related to this issue."""

            if cellmlElementType == CellmlElementType.COMPONENT:
                _issue.Issue_setComponent(self, item)
            elif cellmlElementType == CellmlElementType.COMPONENT_REF:
                _issue.Issue_setComponentRef(self, item)
            elif cellmlElementType == CellmlElementType.CONNECTION:
                _issue.Issue_setConnection(self, item)
            elif cellmlElementType == CellmlElementType.ENCAPSULATION:
                _issue.Issue_setEncapsulation(self, item)
            elif cellmlElementType == CellmlElementType.IMPORT:
                _issue.Issue_setImportSource(self, item)
            elif cellmlElementType == CellmlElementType.MAP_VARIABLES:
                _issue.Issue_setMapVariables(self, item)
            elif cellmlElementType == CellmlElementType.MODEL:
                _issue.Issue_setModel(self, item)
            elif cellmlElementType == CellmlElementType.RESET:
                _issue.Issue_setReset(self, item)
            elif cellmlElementType == CellmlElementType.RESET_VALUE:
                _issue.Issue_setResetValue(self, item)
            elif cellmlElementType == CellmlElementType.TEST_VALUE:
                _issue.Issue_setTestValue(self, item)
            elif cellmlElementType == CellmlElementType.UNIT:
                _issue.Issue_setUnitsItem(self, item)
            elif cellmlElementType == CellmlElementType.UNITS:
                _issue.Issue_setUnits(self, item)
            elif cellmlElementType == CellmlElementType.VARIABLE:
                _issue.Issue_setVariable(self, item)

        def item(self):
            r"""Get the item relevant to this issue by item type (or ``None``)."""

            cellmlElementType = _issue.Issue_cellmlElementType(self)
            if cellmlElementType == CellmlElementType.COMPONENT:
                return (cellmlElementType, _issue.Issue_component(self))
            elif cellmlElementType == CellmlElementType.COMPONENT_REF:
                return (cellmlElementType, _issue.Issue_componentRef(self))
            elif cellmlElementType == CellmlElementType.CONNECTION:
                return (cellmlElementType, _issue.Issue_connection(self))
            elif cellmlElementType == CellmlElementType.ENCAPSULATION:
                return (cellmlElementType, _issue.Issue_encapsulation(self))
            elif cellmlElementType == CellmlElementType.IMPORT:
                return (cellmlElementType, _issue.Issue_importSource(self))
            elif cellmlElementType == CellmlElementType.MAP_VARIABLES:
                return (cellmlElementType, _issue.Issue_mapVariables(self))
            elif cellmlElementType == CellmlElementType.MODEL:
                return (cellmlElementType, _issue.Issue_model(self))
            elif cellmlElementType == CellmlElementType.RESET:
                return (cellmlElementType, _issue.Issue_reset(self))
            elif cellmlElementType == CellmlElementType.RESET_VALUE:
                return (cellmlElementType, _issue.Issue_resetValue(self))
            elif cellmlElementType == CellmlElementType.TEST_VALUE:
                return (cellmlElementType, _issue.Issue_testValue(self))
            elif cellmlElementType == CellmlElementType.UNIT:
                return (cellmlElementType, _issue.Issue_unitsItem(self))
            elif cellmlElementType == CellmlElementType.UNITS:
                return (cellmlElementType, _issue.Issue_units(self))
            elif cellmlElementType == CellmlElementType.VARIABLE:
                return (cellmlElementType, _issue.Issue_variable(self))
            return (CellmlElementType.UNDEFINED, None)
        %}
    }

%include "libcellml/issue.h"
