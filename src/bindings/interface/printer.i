%module(package="libcellml") printer

#define LIBCELLML_EXPORT

%include "std_string.i"

%import "types.i"
%import "logger.i"
%import "enumerations.i"

%feature("docstring") libcellml::Printer
"Prints CellML models to an XML string.";

%feature("docstring") libcellml::Printer::printComponent
"Serialises the given :class:`Component` to an XML string.";

%feature("docstring") libcellml::Printer::printModel
"Serialises the given :class:`Model` to an XML string.";

%feature("docstring") libcellml::Printer::printUnits
"Serialises the given :class:`Units` to an XML string.";

%feature("docstring") libcellml::Printer::printVariable
"Serialises the given :class:`Variable` to an XML string.";

%{
#include "libcellml/printer.h"
%}

%ignore libcellml::Printer::Printer(Printer &&);
%ignore libcellml::Printer::operator =;

// Hide methods that cause conflicts
%ignore libcellml::Printer::printModel(Model model) const;
%ignore libcellml::Printer::printModel(Model* model) const;
%ignore libcellml::Printer::printUnits(Units units) const;
%ignore libcellml::Printer::printVariable(Variable variable) const;
%ignore libcellml::Printer::printComponent(Component component) const;
%ignore libcellml::Printer::printReset(Reset reset) const;

%include "libcellml/types.h"
%include "libcellml/printer.h"
