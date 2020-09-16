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

%{
#include "libcellml/issue.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
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

%include "libcellml/exportdefinitions.h"
%include "libcellml/types.h"
%include "libcellml/issue.h"
