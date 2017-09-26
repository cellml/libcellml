%module(package="libcellml") printer

#define LIBCELLML_EXPORT

%import "types.i"
%import "logger.i"
%import "enumerations.i"

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

%include "libcellml/types.h"
%include "libcellml/printer.h"
