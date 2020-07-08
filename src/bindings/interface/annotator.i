%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%feature("docstring") libcellml::Annotator
"Validates CellML objects.";

%feature("docstring") libcellml::Annotator::build
"Construct a searchable map of items in the model."

%feature("docstring") libcellml::Annotator::item
"Return the item with the given id."

%feature("docstring") libcellml::Annotator::indicesToItem
"Return the a pair. The first item is the enumeration value,
 and the second is a vector of indices to the item with the given id."

%feature("docstring") libcellml::Annotator::instructions
"Return a string containing instructions to retrieve the item with the given id."

// %feature("docstring") libcellml::Annotator::component
// "Return the component with the given id."

// %feature("docstring") libcellml::Annotator::model
// "Return the model with the given id."

// %feature("docstring") libcellml::Annotator::variable
// "Return the variable with the given id."

// %feature("docstring") libcellml::Annotator::import
// "Return the import source with the given id."

// %feature("docstring") libcellml::Annotator::units
// "Return the units with the given id."

// %feature("docstring") libcellml::Annotator::reset
// "Return the reset with the given id."

// %feature("docstring") libcellml::Annotator::connection
// "Return a VariablePair representing the connection with the given id."

// %feature("docstring") libcellml::Annotator::map_variables
// "Return a VariablePair representing the map_variables with the given id."

// %feature("docstring") libcellml::Annotator::unit
// "Return the UnitItem with the given id.  The first item is the parent "
// "units item, the second is the index of this unit."

// %feature("docstring") libcellml::Annotator::math
// "Return the math string with the given id."

// %feature("docstring") libcellml::Annotator::test_value
// "Return the test_value math string with the given id."

// %feature("docstring") libcellml::Annotator::reset_value
// "Return the reset_value math string with the given id."

// %feature("docstring") libcellml::Annotator::component_ref
// "Return the ComponentPtr with the given component_ref id."

%{
#include "libcellml/annotator.h"
%}

%create_constructor(Annotator)

%include "libcellml/types.h"
%include "libcellml/annotator.h"
