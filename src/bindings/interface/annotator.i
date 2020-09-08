%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "enums.i"
%import "logger.i"
%import "types.i"

%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>
%include <stdint.i>

%feature("docstring") libcellml::Annotator
"Interacts with CellML objects using their id attribute.";

%feature("docstring") libcellml::Annotator::setModel
"Construct a searchable map of items in the model.";

%feature("docstring") libcellml::Annotator::item
"Return the item with the given id.";

%feature("docstring") libcellml::Annotator::component
"Return the component with the given id.";

%feature("docstring") libcellml::Annotator::encapsulation
"Return the model with the given encapsulation id.";

%feature("docstring") libcellml::Annotator::model
"Return the model with the given id.";

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

%feature("docstring") libcellml::Annotator::assignAllIds
"Traverse the stored model and set any blank id fields to an automatically generated id.";

%feature("docstring") libcellml::Annotator::assignIds
"Set all items of the given type in the stored model to automatically generated, unique strings.";

%feature("docstring") libcellml::Annotator::clearAllIds
"Clear all the id strings in the given or stored model.";

%feature("docstring") libcellml::Annotator::isUnique
"Return `true` if the given string is not duplicated in the stored model, or `false` otherwise.";

%feature("docstring") libcellml::Annotator::ids
"Return a list of all id strings within the stored model.";

%feature("docstring") libcellml::Annotator::duplicateIds
"Return a list of id strings which are duplicated within the stored model.";

%feature("docstring") libcellml::Annotator::assignComponentId
"Assign an automatically generated, unique id to the given component.";

%feature("docstring") libcellml::Annotator::assignComponentRefId
"Assign an automatically generated, unique id to the given component's encapsulation.";

%feature("docstring") libcellml::Annotator::assignConnectionId
"Assign an automatically generated, unique id to the connection between the given variables.";

%feature("docstring") libcellml::Annotator::assignEncapsulationId
"Assign an automatically generated, unique id to the encapsulation of the given model.";

%feature("docstring") libcellml::Annotator::assignImportSourceId
"Assign an automatically generated, unique id to the given import source.";

%feature("docstring") libcellml::Annotator::assignMapVariablesId
"Assign an automatically generated, unique id to the equivalence between the given variables.";

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
"Report whether the annotator index is up-to-date with its stored model state.";

// PRIVATE: Functions only written to support bindings. They are not 
// intended to be called from anywhere other than this file.

%feature("docstring") libcellml::Annotator::itemTypeForSWIG
"Private: Utility function to retrieve item type integer based on id.";

%feature("docstring") libcellml::Annotator::unitIndexForSWIG
"Private: Utility function to retrieve index of Unit item within parent Units item based on given id.";

%feature("docstring") libcellml::Annotator::unitParentForSWIG
"Private: Utility function to retrieve UnitsPtr parent for Unit item with given id.";

%feature("docstring") libcellml::Annotator::connectionForSWIG
"Private: Utility function to retrieve one of VariablePtrs connection with given id.";

%feature("docstring") libcellml::Annotator::mapVariablesForSWIG
"Private: Utility function to retrieve one of VariablePtrs map_variables with given id.";

%feature("docstring") libcellml::Annotator::assignConnectionIdForSWIG
"Private: Utility function to set a unique id for the connection between a given variable pair..";

%feature("docstring") libcellml::Annotator::assignMapVariablesIdForSWIG
"Private: Utility function to set a unique id for the equivalence between a given variable pair.";

%feature("docstring") libcellml::Annotator::assignUnitIdForSWIG
"Private: Utility function to set a unique id for the unit located by the given index and units.";


%{
#include "libcellml/annotator.h"
%}

%create_constructor(Annotator)

%template(StringVector) std::vector<std::string>;

%ignore libcellml::Annotator::item;
%ignore libcellml::Annotator::items;
%ignore libcellml::Annotator::unit;
%ignore libcellml::Annotator::connection;
%ignore libcellml::Annotator::mapVariables;
%ignore libcellml::Annotator::assignId;

%pythoncode %{
from libcellml import CellMLElement
%}

%extend libcellml::Annotator {

    int itemTypeForSWIG(const std::string &id, size_t index)
    {
        auto itemInfo = $self->item(id, index);
        return static_cast<int>(itemInfo.first);
    }

    int unitIndexForSWIG(const std::string &id, size_t index)
    {
        auto u = $self->unit(id, index);
        if(u.first == nullptr){
            return -1;
        }
        return u.second;
    }

    UnitsPtr unitParentForSWIG(const std::string &id, size_t index)
    {
        auto u = $self->unit(id, index);
        return u.first;
    }

    VariablePtr connectionForSWIG(const std::string &id, bool useFirst, const size_t &index)
    {
        auto vPair = $self->connection(id, index);
        if (useFirst) {
            return vPair.first;
        }
        return vPair.second;
    }

    VariablePtr mapVariablesForSWIG(const std::string &id, bool useFirst, const size_t &index)
    {
        auto vPair = $self->mapVariables(id, index);
        if (useFirst) {
            return vPair.first;
        }
        return vPair.second;
    }

    std::string assignConnectionIdForSWIG(VariablePtr &item, VariablePtr &item2) {
        libcellml::VariablePair variablePair = std::make_pair(item, item2);
        return $self->assignConnectionId(variablePair);
    }

    std::string assignMapVariablesIdForSWIG(VariablePtr &item, VariablePtr &item2) {
        libcellml::VariablePair variablePair = std::make_pair(item, item2);
        return $self->assignMapVariablesId(variablePair);
    }

    std::string assignUnitIdForSWIG(UnitsPtr &item, size_t index) {
        libcellml::UnitItem unitItem = std::make_pair(item, index);
        return $self->assignUnitId(unitItem);
    }

    %pythoncode %{
        def assignId(self, type, item, item2=None):
            r"""Sets the given item's id to an automatically generated, unique string."""
            if type == CellMLElement.COMPONENT:
                return _annotator.Annotator_assignComponentId(self, item)
            elif type == CellMLElement.COMPONENT_REF:
                return _annotator.Annotator_assignComponentRefId(self, item)
            elif type == CellMLElement.ENCAPSULATION:
                return _annotator.Annotator_assignEncapsulationId(self, item)
            elif type == CellMLElement.IMPORT:
                return _annotator.Annotator_assignImportSourceId(self, item)
            elif type == CellMLElement.MODEL:
                return _annotator.Annotator_assignModelId(self, item)
            elif type == CellMLElement.RESET:
                return _annotator.Annotator_assignResetId(self, item)
            elif type == CellMLElement.RESET_VALUE:
                return _annotator.Annotator_assignResetValueId(self, item)
            elif type == CellMLElement.TEST_VALUE:
                return _annotator.Annotator_assignTestValueId(self, item)
            elif type == CellMLElement.UNITS:
                return _annotator.Annotator_assignUnitsId(self, item)
            elif type == CellMLElement.VARIABLE:
                return _annotator.Annotator_assignVariableId(self, item)

            if type == CellMLElement.CONNECTION:
                return _annotator.Annotator_assignConnectionIdForSWIG(self, item, item2)
            elif type == CellMLElement.MAP_VARIABLES:
                return _annotator.Annotator_assignMapVariablesIdForSWIG(self, item, item2)
            elif type == CellMLElement.UNIT:
                return _annotator.Annotator_assignUnitIdForSWIG(self, item, item2)
            return ""
       
        def unit(self, id, index=0):
            r"""Return the UnitItem with the given id.  The first item is the parent UnitsPtr item, the second is the index of this unit."""
            return (_annotator.Annotator_unitParentForSWIG(self, id, index), _annotator.Annotator_unitIndexForSWIG(self, id, index))

        def connection(self, id, index=0):
            r"""Retrieve a tuple of VariablePtr items from a connection with the given id."""
            return (_annotator.Annotator_connectionForSWIG(self, id, True, index), _annotator.Annotator_connectionForSWIG(self, id, False, index))

        def mapVariables(self, id, index=0):
            r"""Retrieve a tuple of VariablePtr items from a map_variables with the given id."""
            return (_annotator.Annotator_mapVariablesForSWIG(self, id, True, index), _annotator.Annotator_mapVariablesForSWIG(self, id, False, index))

        def item(self, id, index=-1):
            r"""Retrieve a unique item with the given id."""
            if index == -1 and not _annotator.Annotator_isUnique(id, true):
                return (-1, None)
            
            if index == -1:
                index = 0

            type = _annotator.Annotator_itemTypeForSWIG(self, id, index)
            if type == CellMLElement.COMPONENT:
                return (type, _annotator.Annotator_component(self, id, index))
            elif type == CellMLElement.COMPONENT_REF:
                return (type, _annotator.Annotator_componentRef(self, id, index))
            elif type == CellMLElement.CONNECTION:
                first = _annotator.Annotator_connectionForSWIG(self, id, True, index)
                second = _annotator.Annotator_connectionForSWIG(self, id, False, index)
                return (type, (first, second))
            elif type == CellMLElement.ENCAPSULATION:
                return (type, _annotator.Annotator_encapsulation(self, id, index))
            elif type == CellMLElement.IMPORT:
                return (type, _annotator.Annotator_importSource(self, id, index))
            elif type == CellMLElement.MAP_VARIABLES:
                first = _annotator.Annotator_mapVariablesForSWIG(self, id, True, index)
                second = _annotator.Annotator_mapVariablesForSWIG(self, id, False, index)
                return (type, (first, second))
            elif type == CellMLElement.MODEL:
                return (type, _annotator.Annotator_model(self, id, index))
            elif type == CellMLElement.RESET:
                return (type, _annotator.Annotator_reset(self, id, index))
            elif type == CellMLElement.RESET_VALUE:
                return (type, _annotator.Annotator_resetValue(self, id, index))
            elif type == CellMLElement.TEST_VALUE:
                return (type, _annotator.Annotator_testValue(self, id, index)) 
            elif type == CellMLElement.UNIT:
                first = _annotator.Annotator_unitParentForSWIG(self, id, index)
                second = _annotator.Annotator_unitIndexForSWIG(self, id, index)
                return (type, (first, second))
            elif type == CellMLElement.UNITS:
                return (type, _annotator.Annotator_units(self, id, index))
            elif type == CellMLElement.VARIABLE:
                return (type, _annotator.Annotator_variable(self, id, index))
            return (-1, None)

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

%include "libcellml/annotator.h"
