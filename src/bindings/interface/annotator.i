%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "enums.i"
%import "logger.i"
%import "types.i"

%include <std_pair.i>
%include <std_vector.i>

%feature("docstring") libcellml::Annotator
"Interacts with CellML objects using their identifier attribute.";

%feature("docstring") libcellml::Annotator::setModel
"Set the model for this Annotator to work with.";

%feature("docstring") libcellml::Annotator::item
"Return the item with the given identifier.";

%feature("docstring") libcellml::Annotator::component
"Return the component with the given identifier.";

%feature("docstring") libcellml::Annotator::model
"Return the model assigned to this Annotator or the model with the given identifier.";

%feature("docstring") libcellml::Annotator::variable
"Return the variable with the given identifier.";

%feature("docstring") libcellml::Annotator::importSource
"Return the import source with the given identifier.";

%feature("docstring") libcellml::Annotator::units
"Return the units with the given identifier.";

%feature("docstring") libcellml::Annotator::reset
"Return the reset with the given identifier.";

%feature("docstring") libcellml::Annotator::testValue
"Return the ResetPtr whose test_value has the given identifier.";

%feature("docstring") libcellml::Annotator::resetValue
"Return the ResetPtr whose reset_value has the given identifier.";

%feature("docstring") libcellml::Annotator::unit
"Returns a Unit, a pair consisting of UnitsPtr and index which defines the Unit with the given identifier.";

%feature("docstring") libcellml::Annotator::connection
"Return a VariablePair that defines a connection with given identifier.";

%feature("docstring") libcellml::Annotator::mapVariables
"Return a VariablePair that defines a map_variables with given identifier.";

%feature("docstring") libcellml::Annotator::assignAllIds
"Traverse the stored model and set any blank identifier fields to an automatically generated identifier.";

%feature("docstring") libcellml::Annotator::assignIds
"Set all items of the given type in the stored model to automatically generated, unique strings.";

%feature("docstring") libcellml::Annotator::clearAllIds
"Clear all the identifier strings in the given or stored model.";

%feature("docstring") libcellml::Annotator::isUnique
"Return `true` if the given string occurs exactly once as an identifier in the stored model, `false` otherwise.";

%feature("docstring") libcellml::Annotator::ids
"Return a list of all identifier strings within the stored model.";

%feature("docstring") libcellml::Annotator::duplicateIds
"Return a list of identifier strings which are duplicated within the stored model.";

%feature("docstring") libcellml::Annotator::assignComponentId
"Assign an automatically generated, unique identifier to the given component.";

%feature("docstring") libcellml::Annotator::encapsulation
"Return the model with the given encapsulation identifier.";

%feature("docstring") libcellml::Annotator::componentEncapsulation
"Return the ComponentPtr with the given component_ref identifier.";

%feature("docstring") libcellml::Annotator::assignComponentRefId
"Assign an automatically generated, unique identifier to the given component's encapsulation.";

%feature("docstring") libcellml::Annotator::assignConnectionId
"Assign an automatically generated, unique identifier to the connection defined by the VariablePair.";

%feature("docstring") libcellml::Annotator::assignEncapsulationId
"Assign an automatically generated, unique identifier to the encapsulation of the given model.";

%feature("docstring") libcellml::Annotator::assignImportSourceId
"Assign an automatically generated, unique identifier to the given import source.";

%feature("docstring") libcellml::Annotator::assignMapVariablesId
"Assign an automatically generated, unique identifier to the equivalence defined by the VariablePair.";

%feature("docstring") libcellml::Annotator::assignModelId
"Assign an automatically generated, unique identifier to the given model.";

%feature("docstring") libcellml::Annotator::assignResetId
"Assign an automatically generated, unique identifier to the given reset.";

%feature("docstring") libcellml::Annotator::assignResetValueId
"Assign an automatically generated, unique identifier to the reset value of the given reset.";

%feature("docstring") libcellml::Annotator::assignTestValueId
"Assign an automatically generated, unique identifier to the test value of the given reset.";

%feature("docstring") libcellml::Annotator::assignUnitId
"Assign an automatically generated, unique identifier to the unit given by the units and index supplied.";

%feature("docstring") libcellml::Annotator::assignUnitsId
"Assign an automatically generated, unique identifier to the given units.";

%feature("docstring") libcellml::Annotator::assignVariableId
"Assign an automatically generated, unique identifier to the given variable.";

%feature("docstring") libcellml::Annotator::itemCount
"Return the number of items in the stored model with the given identifier.";

%feature("docstring") libcellml::Annotator::hasModel
"Report whether the annotator has a model assigned or not.";

%feature("docstring") libcellml::Annotator::assignId
"Function to assign an automatic identifier.";

%{
#include "libcellml/annotator.h"
%}

%create_constructor(Annotator)

%ignore libcellml::Annotator::items;

%pythoncode %{
# libCellML generated wrapper code starts here.

from libcellml.enums import CellmlElementType
from libcellml.types import AnyCellmlElement
%}

%template() std::vector<std::string>;

%include "libcellml/annotator.h"
%include "libcellml/types.h"

%extend libcellml::Annotator {
%pythoncode %{
    def items(self, id):
        r"""Returns everything with the given identifier as a list of (type, item) tuples."""
        count = _annotator.Annotator_itemCount(self, id)
        itemsList = []
        for c in range(0, count):
            items_with_id = self.item(id, c)
            itemsList.append(items_with_id)
        return itemsList
%}
}
