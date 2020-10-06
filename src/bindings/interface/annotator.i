%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "enums.i"
%import "logger.i"
%import "types.i"

%include <std_pair.i>
%include <std_vector.i>

%feature("docstring") libcellml::Annotator
"Interacts with CellML objects using their id attribute.";

%feature("docstring") libcellml::Annotator::setModel
"Set the model for this Annotator to work with.";

%feature("docstring") libcellml::Annotator::item
"Return the item with the given id.";

%feature("docstring") libcellml::Annotator::component
"Return the component with the given id.";

%feature("docstring") libcellml::Annotator::encapsulation
"Return the model with the given encapsulation id.";

%feature("docstring") libcellml::Annotator::model
"Return the model assigned to this Annotator or the model with the given id.";

%feature("docstring") libcellml::Annotator::variable
"Return the variable with the given id.";

%feature("docstring") libcellml::Annotator::importSource
"Return the import source with the given id.";

%feature("docstring") libcellml::Annotator::units
"Return the units with the given id.";

%feature("docstring") libcellml::Annotator::reset
"Return the reset with the given id.";

%feature("docstring") libcellml::Annotator::testValue
"Return the ResetPtr whose test_value has the given id.";

%feature("docstring") libcellml::Annotator::resetValue
"Return the ResetPtr whose reset_value has the given id.";

%feature("docstring") libcellml::Annotator::componentRef
"Return the ComponentPtr with the given component_ref id.";

%feature("docstring") libcellml::Annotator::unit
"Returns a UnitItem, a pair consisting of UnitsPtr and index which defines the Unit with the given id.";

%feature("docstring") libcellml::Annotator::connection
"Return a VariablePair that defines a connection with given id.";

%feature("docstring") libcellml::Annotator::mapVariables
"Return a VariablePair that defines a map_variables with given id.";

%feature("docstring") libcellml::Annotator::assignAllIds
"Traverse the stored model and set any blank id fields to an automatically generated id.";

%feature("docstring") libcellml::Annotator::assignIds
"Set all items of the given type in the stored model to automatically generated, unique strings.";

%feature("docstring") libcellml::Annotator::clearAllIds
"Clear all the id strings in the given or stored model.";

%feature("docstring") libcellml::Annotator::isUnique
"Return `true` if the given string occurs exactly once as an id in the stored model, `false` otherwise.";

%feature("docstring") libcellml::Annotator::ids
"Return a list of all id strings within the stored model.";

%feature("docstring") libcellml::Annotator::duplicateIds
"Return a list of id strings which are duplicated within the stored model.";

%feature("docstring") libcellml::Annotator::assignComponentId
"Assign an automatically generated, unique id to the given component.";

%feature("docstring") libcellml::Annotator::assignComponentRefId
"Assign an automatically generated, unique id to the given component's encapsulation.";

%feature("docstring") libcellml::Annotator::assignConnectionId
"Assign an automatically generated, unique id to the connection defined by the VariablePair.";

%feature("docstring") libcellml::Annotator::assignEncapsulationId
"Assign an automatically generated, unique id to the encapsulation of the given model.";

%feature("docstring") libcellml::Annotator::assignImportSourceId
"Assign an automatically generated, unique id to the given import source.";

%feature("docstring") libcellml::Annotator::assignMapVariablesId
"Assign an automatically generated, unique id to the equivalence defined by the VariablePair.";

%feature("docstring") libcellml::Annotator::assignModelId
"Assign an automatically generated, unique id to the given model.";

%feature("docstring") libcellml::Annotator::assignResetId
"Assign an automatically generated, unique id to the given reset.";

%feature("docstring") libcellml::Annotator::assignResetValueId
"Assign an automatically generated, unique id to the reset value of the given reset.";

%feature("docstring") libcellml::Annotator::assignTestValueId
"Assign an automatically generated, unique id to the test value of the given reset.";

%feature("docstring") libcellml::Annotator::assignUnitId
"Assign an automatically generated, unique id to the unit given by the units and index supplied.";

%feature("docstring") libcellml::Annotator::assignUnitsId
"Assign an automatically generated, unique id to the given units.";

%feature("docstring") libcellml::Annotator::assignVariableId
"Assign an automatically generated, unique id to the given variable.";

%feature("docstring") libcellml::Annotator::duplicateCount
"Return the number of items in the stored model with the given id.";

%feature("docstring") libcellml::Annotator::hasModel
"Report whether the annotator has a model assigned or not.";

// PRIVATE: Functions only written to support bindings. They are not
// intended to be called from anywhere other than this file.

%feature("docstring") libcellml::Annotator::_itemCellmlElement
"Private: Utility function to retrieve item type integer based on id.";

%{
#include "libcellml/annotator.h"
%}

%create_constructor(Annotator)

%ignore libcellml::Annotator::item;
%ignore libcellml::Annotator::items;
%ignore libcellml::Annotator::assignId(const AnyItem &item);

%ignore libcellml::Annotator::assignId(libcellml::ModelPtr const &,libcellml::CellMLElement);
%ignore libcellml::Annotator::assignId(libcellml::ModelPtr const &);
%ignore libcellml::Annotator::assignId(libcellml::ComponentPtr const &,libcellml::CellMLElement);
%ignore libcellml::Annotator::assignId(libcellml::ComponentPtr const &);
%ignore libcellml::Annotator::assignId(libcellml::ImportSourcePtr const &);
%ignore libcellml::Annotator::assignId(libcellml::ResetPtr const &,libcellml::CellMLElement);
%ignore libcellml::Annotator::assignId(libcellml::ResetPtr const &);
%ignore libcellml::Annotator::assignId(libcellml::UnitsPtr const &);
%ignore libcellml::Annotator::assignId(libcellml::UnitItem const &);
%ignore libcellml::Annotator::assignId(libcellml::VariablePtr const &);
%ignore libcellml::Annotator::assignId(libcellml::VariablePair const &,libcellml::CellMLElement);
%ignore libcellml::Annotator::assignId(libcellml::VariablePair const &);
%ignore libcellml::Annotator::assignId(libcellml::VariablePtr const &,libcellml::VariablePtr const &,libcellml::CellMLElement);
%ignore libcellml::Annotator::assignId(libcellml::VariablePtr const &,libcellml::VariablePtr const &);
%ignore libcellml::Annotator::assignId(libcellml::UnitsPtr const &, size_t);

%pythoncode %{
# libCellML generated wrapper code starts here.

from libcellml import CellMLElement
%}

%template() std::vector<std::string>;

%include "libcellml/annotator.h"

%template(UnitItem) std::pair< libcellml::UnitsPtr, size_t >;
%template(VariablePair) std::pair< libcellml::VariablePtr, libcellml::VariablePtr >;

%extend libcellml::Annotator {

    CellMLElement _itemCellmlElement(const std::string &id, size_t index)
    {
        auto itemInfo = $self->item(id, index);
        return itemInfo.first;
    }

%pythoncode %{

    def assignId(self, arg1, arg2=None):
        r"""Set the id of the given item to an automatically generated, unique string, and return new id."""
        if arg2:
            return _annotator.Annotator_assignId(self, arg1, arg2)
        if type(arg1).__name__ in ['list', 'tuple']:
            return _annotator.Annotator_assignId(self, arg1[1], arg1[0])
        return _annotator.Annotator_assignId(self, arg1)

    def item(self, id, index=-1):
        r"""Retrieve a unique item with the given id."""
        if index == -1 and not _annotator.Annotator_isUnique(self, id):
            return (CellMLElement.UNDEFINED, None)

        if index == -1:
            index = 0

        type = _annotator.Annotator__itemCellmlElement(self, id, index)
        if type == CellMLElement.COMPONENT:
            return (type, _annotator.Annotator_component(self, id, index))
        elif type == CellMLElement.COMPONENT_REF:
            return (type, _annotator.Annotator_componentRef(self, id, index))
        elif type == CellMLElement.CONNECTION:
            return (type, _annotator.Annotator_connection(self, id, index))
        elif type == CellMLElement.ENCAPSULATION:
            return (type, _annotator.Annotator_encapsulation(self, id, index))
        elif type == CellMLElement.IMPORT:
            return (type, _annotator.Annotator_importSource(self, id, index))
        elif type == CellMLElement.MAP_VARIABLES:
            return (type, _annotator.Annotator_mapVariables(self, id, index))
        elif type == CellMLElement.MODEL:
            return (type, _annotator.Annotator_model(self, id, index))
        elif type == CellMLElement.RESET:
            return (type, _annotator.Annotator_reset(self, id, index))
        elif type == CellMLElement.RESET_VALUE:
            return (type, _annotator.Annotator_resetValue(self, id, index))
        elif type == CellMLElement.TEST_VALUE:
            return (type, _annotator.Annotator_testValue(self, id, index))
        elif type == CellMLElement.UNIT:
            return (type, _annotator.Annotator_unit(self, id, index))
        elif type == CellMLElement.UNITS:
            return (type, _annotator.Annotator_units(self, id, index))
        elif type == CellMLElement.VARIABLE:
            return (type, _annotator.Annotator_variable(self, id, index))
        return (CellMLElement.UNDEFINED, None)

    def items(self, id):
        r"""Returns everything with the given id as as list of (type, item) tuples."""
        count = _annotator.Annotator_duplicateCount(self, id)
        itemsList = []
        for c in range(0, count):
            items_with_id = self.item(id, c)
            itemsList.append(items_with_id)
        return itemsList

%}

}
