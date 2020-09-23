%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "enums.i"
%import "logger.i"
%import "types.i"

%include <std_multimap.i>
%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>
%include <stdint.i>

%feature("docstring") libcellml::Annotator
"Interacts with CellML objects using their id attribute.";

%feature("docstring") libcellml::Annotator::setModel
"Set the model for this Annototor to work with.";

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

%feature("docstring") libcellml::Annotator::assignAllIds
"Traverse the stored model and set any blank id fields to an automatically generated id.";

%feature("docstring") libcellml::Annotator::assignIds
"Set all items of the given type in the stored model to automatically generated, unique strings.";

%feature("docstring") libcellml::Annotator::assignId
"Set the id of the given item to an automatically generated, unique string.";

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
"Report whether the annotator has a model assigned or not.";

// PRIVATE: Functions only written to support bindings. They are not 
// intended to be called from anywhere other than this file.

%feature("docstring") libcellml::Annotator::_itemTypeForSWIG
"Private: Utility function to retrieve item type integer based on id.";

%feature("docstring") libcellml::Annotator::_unitIndexForSWIG
"Private: Utility function to retrieve index of Unit item within parent Units item based on given id.";

%feature("docstring") libcellml::Annotator::_unitParentForSWIG
"Private: Utility function to retrieve UnitsPtr parent for Unit item with given id.";

%feature("docstring") libcellml::Annotator::_connectionForSWIG
"Private: Utility function to retrieve one of VariablePtrs connection with given id.";

%feature("docstring") libcellml::Annotator::_mapVariablesForSWIG
"Private: Utility function to retrieve one of VariablePtrs map_variables with given id.";

%feature("docstring") libcellml::Annotator::_assignConnectionIdForSWIG
"Private: Utility function to set a unique id for the connection between a given variable pair..";

%feature("docstring") libcellml::Annotator::_assignMapVariablesIdForSWIG
"Private: Utility function to set a unique id for the equivalence between a given variable pair.";

%feature("docstring") libcellml::Annotator::_assignUnitIdForSWIG
"Private: Utility function to set a unique id for the unit located by the given index and units.";

%feature("docstring") libcellml::Annotator::_dictionaryForSWIG
"Private: Utility function to return the id dictionary for this model.";


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
%ignore libcellml::Annotator::dictionary;

%pythoncode %{
from libcellml import CellMLElement
%}

%extend libcellml::Annotator {

    int _itemTypeForSWIG(const std::string &id, size_t index)
    {
        auto itemInfo = $self->item(id, index);
        return static_cast<int>(itemInfo.first);
    }

    int _unitIndexForSWIG(const std::string &id, size_t index)
    {
        auto u = $self->unit(id, index);
        if(u.first == nullptr){
            return -1;
        }
        return u.second;
    }

    UnitsPtr _unitParentForSWIG(const std::string &id, size_t index)
    {
        auto u = $self->unit(id, index);
        return u.first;
    }

    VariablePtr _connectionForSWIG(const std::string &id, bool useFirst, const size_t &index)
    {
        auto vPair = $self->connection(id, index);
        if (useFirst) {
            return vPair.first;
        }
        return vPair.second;
    }

    VariablePtr _mapVariablesForSWIG(const std::string &id, bool useFirst, const size_t &index)
    {
        auto vPair = $self->mapVariables(id, index);
        if (useFirst) {
            return vPair.first;
        }
        return vPair.second;
    }

    std::string _assignConnectionIdForSWIG(VariablePtr &item, VariablePtr &item2) {
        libcellml::VariablePair variablePair = std::make_pair(item, item2);
        return $self->assignConnectionId(variablePair);
    }

    std::string _assignMapVariablesIdForSWIG(VariablePtr &item, VariablePtr &item2) {
        libcellml::VariablePair variablePair = std::make_pair(item, item2);
        return $self->assignMapVariablesId(variablePair);
    }

    std::string _assignUnitIdForSWIG(UnitsPtr &item, size_t index) {
        libcellml::UnitItem unitItem = std::make_pair(item, index);
        return $self->assignUnitId(unitItem);
    }

    std::vector<std::string> _dictionaryForSWIG(bool first) {
        std::vector<std::string> rtn;
        if(first){
            for( auto &i : $self->dictionary()) {
                rtn.push_back(i.first);
            }
        }
        else {
            for( auto &i : $self->dictionary()) {
                rtn.push_back(cellMLElementAsString(i.second));
            }
        }
        return rtn;
    }
            
    %pythoncode %{

        def assignId(self, a, b=None, c=None):
            r"""Sets the given item's id to an automatically generated, unique string."""
            if b == None: 
                type = a[0]
                if type == CellMLElement.CONNECTION or type == CellMLElement.MAP_VARIABLES or type == CellMLElement.UNIT:
                    item2 = a[1][1]
                    item = a[1][0]
                else:
                    item = a[1]
            elif c == None:
                item = a
                type = b
            else:
                item = a
                item2 = b
                type = c

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
                return _annotator.Annotator__assignConnectionIdForSWIG(self, item, item2)
            elif type == CellMLElement.MAP_VARIABLES:
                return _annotator.Annotator__assignMapVariablesIdForSWIG(self, item, item2)
            elif type == CellMLElement.UNIT:
                return _annotator.Annotator__assignUnitIdForSWIG(self, item, item2)
            return ""
       
        def unit(self, id, index=0):
            r"""Return the UnitItem with the given id.  The first item is the parent UnitsPtr item, the second is the index of this unit."""
            return (_annotator.Annotator__unitParentForSWIG(self, id, index), _annotator.Annotator__unitIndexForSWIG(self, id, index))

        def connection(self, id, index=0):
            r"""Retrieve a tuple of VariablePtr items from a connection with the given id."""
            return (_annotator.Annotator__connectionForSWIG(self, id, True, index), _annotator.Annotator__connectionForSWIG(self, id, False, index))

        def mapVariables(self, id, index=0):
            r"""Retrieve a tuple of VariablePtr items from a map_variables with the given id."""
            return (_annotator.Annotator__mapVariablesForSWIG(self, id, True, index), _annotator.Annotator__mapVariablesForSWIG(self, id, False, index))

        def item(self, id, index=-1):
            r"""Retrieve a unique item with the given id."""
            if index == -1 and not _annotator.Annotator_isUnique(self, id):
                return (-1, None)
            
            if index == -1:
                index = 0

            type = _annotator.Annotator__itemTypeForSWIG(self, id, index)
            if type == CellMLElement.COMPONENT:
                return (type, _annotator.Annotator_component(self, id, index))
            elif type == CellMLElement.COMPONENT_REF:
                return (type, _annotator.Annotator_componentRef(self, id, index))
            elif type == CellMLElement.CONNECTION:
                first = _annotator.Annotator__connectionForSWIG(self, id, True, index)
                second = _annotator.Annotator__connectionForSWIG(self, id, False, index)
                return (type, (first, second))
            elif type == CellMLElement.ENCAPSULATION:
                return (type, _annotator.Annotator_encapsulation(self, id, index))
            elif type == CellMLElement.IMPORT:
                return (type, _annotator.Annotator_importSource(self, id, index))
            elif type == CellMLElement.MAP_VARIABLES:
                first = _annotator.Annotator__mapVariablesForSWIG(self, id, True, index)
                second = _annotator.Annotator__mapVariablesForSWIG(self, id, False, index)
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
                first = _annotator.Annotator__unitParentForSWIG(self, id, index)
                second = _annotator.Annotator__unitIndexForSWIG(self, id, index)
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
        
        def dictionary(self):
            r"""Return a dictionary of all id strings and their type within the stored model."""
            rtn = []
            for k, v in zip(_annotator.Annotator__dictionaryForSWIG(self, True), _annotator.Annotator__dictionaryForSWIG(self, False)):
                rtn.append((k,v))
            return rtn
    %}
}

%include "libcellml/annotator.h"
