%module(package="libcellml") annotator

#define LIBCELLML_EXPORT

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>
%include <stdint.i>

%feature("docstring") libcellml::Annotator
"Interacts with CellML objects using their id attribute.";

%feature("docstring") libcellml::Annotator::build
"Construct a searchable map of items in the model.";

%feature("docstring") libcellml::Annotator::item
"Return the item with the given id.";

%feature("docstring") libcellml::Annotator::component
"Return the component with the given id.";

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
"Traverses the stored model and sets any blank id fields to an automatically generated id.";

%feature("docstring") libcellml::Annotator::assignIds
"Sets all items of the given type in the stored model to automatically generated, unique strings.";

%feature("docstring") libcellml::Annotator::clearAllIds
"Clears all the id strings in the given or stored model.";

%feature("docstring") libcellml::Annotator::isUnique
"Returns `true` if the given string is not duplicated in the stored model, or `false` otherwise.";

%feature("docstring") libcellml::Annotator::duplicateIds
"Returns a list of id strings which are duplicated within the stored model.";

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

%feature("docstring") libcellml::Annotator::typeString
"Translates the given Annotator::Type enumeration into a string.";

// PRIVATE: Functions only written to support bindings. They are not 
// intended to be called from anywhere.
%feature("docstring") libcellml::Annotator::itemForPython
"Private: Utility function to retrieve item based on id.";

%feature("docstring") libcellml::Annotator::itemTypeForPython
"Private: Utility function to retrieve item type integer based on id.";

%feature("docstring") libcellml::Annotator::unitIndexForPython
"Private: Utility function to retrieve index of Unit item within parent Units item based on given id.";

%feature("docstring") libcellml::Annotator::unitParentForPython
"Private: Utility function to retrieve UnitsPtr parent for Unit item with given id.";

%feature("docstring") libcellml::Annotator::connectionForPython
"Private: Utility function to retrieve one of VariablePtrs connection with given id.";

%feature("docstring") libcellml::Annotator::mapVariablesForPython
"Private: Utility function to retrieve one of VariablePtrs map_variables with given id.";

%feature("docstring") libcellml::Annotator::assignConnectionIdForPython
"Private: Utility function to set a unique id for the connection between a given variable pair..";

%feature("docstring") libcellml::Annotator::assignMapVariablesIdForPython
"Private: Utility function to set a unique id for the equivalence between a given variable pair.";

%feature("docstring") libcellml::Annotator::assignUnitIdForPython
"Private: Utility function to set a unique id for the unit located by the given index and units.";

// %feature("docstring") libcellml::Annotator::itemsForPython
// "Private: Utility function to return a collection of items with the given id.";

%{
#include "libcellml/annotator.h"
%}

%ignore libcellml::Annotator::item;
%ignore libcellml::Annotator::unit;
%ignore libcellml::Annotator::connection;
%ignore libcellml::Annotator::mapVariables;
%ignore libcellml::Annotator::assignId;
%ignore libcellml::Annotator::items; // KRM Only ignoring until I can write the manual binding for it.

%create_constructor(Annotator)

%extend libcellml::Annotator {

    void itemForPython(const std::string &id, int &type, std::any &itemPtr)
    {
        auto itemInfo = $self->item(id);
        type = static_cast<int>(itemInfo.first);
        itemPtr = itemInfo.second;
    }

    int itemTypeForPython(const std::string &id)
    {
        auto itemInfo = $self->item(id);
        return static_cast<int>(itemInfo.first);
    }

    int unitIndexForPython(const std::string &id)
    {
        auto u = $self->unit(id);
        if(u.first == nullptr){
            return -1;
        }
        return u.second;
    }

    UnitsPtr unitParentForPython(const std::string &id)
    {
        auto u = $self->unit(id);
        return u.first;
    }

    VariablePtr connectionForPython(const std::string &id, const size_t &index)
    {
        auto vPair = $self->connection(id);
        if (index == 0) {
            return vPair.first;
        }
        return vPair.second;
    }

    VariablePtr mapVariablesForPython(const std::string &id, const size_t &index)
    {
        auto vPair = $self->mapVariables(id);
        if (index == 0) {
            return vPair.first;
        }
        return vPair.second;
    }

    std::string assignConnectionIdForPython(VariablePtr &item, VariablePtr &item2) {
        libcellml::VariablePair variablePair = std::make_pair(item, item2);
        return $self->assignConnectionId(variablePair);
    }

    std::string assignMapVariablesIdForPython(VariablePtr &item, VariablePtr &item2) {
        libcellml::VariablePair variablePair = std::make_pair(item, item2);
        return $self->assignMapVariablesId(variablePair);
    }

    std::string assignUnitIdForPython(UnitsPtr &item, size_t index) {
        libcellml::UnitItem unitItem = std::make_pair(item, index);
        return $self->assignUnitId(unitItem);
    }

    %pythoncode %{
        def assignId(self, type, item, item2=None):
            r"""Sets the given item's id to an automatically generated, unique string."""
            if type == Annotator.Type.COMPONENT:
                return _annotator.Annotator_assignComponentId(self, item)
            elif type == Annotator.Type.COMPONENT_REF:
                return _annotator.Annotator_assignComponentRefId(self, item)
            elif type == Annotator.Type.ENCAPSULATION:
                return _annotator.Annotator_assignEncapsulationId(self, item)
            elif type == Annotator.Type.IMPORT:
                return _annotator.Annotator_assignImportSourceId(self, item)
            elif type == Annotator.Type.MODEL:
                return _annotator.Annotator_assignModelId(self, item)
            elif type == Annotator.Type.RESET:
                return _annotator.Annotator_assignResetId(self, item)
            elif type == Annotator.Type.RESET_VALUE:
                return _annotator.Annotator_assignResetValueId(self, item)
            elif type == Annotator.Type.TEST_VALUE:
                return _annotator.Annotator_assignTestValueId(self, item)
            elif type == Annotator.Type.UNITS:
                return _annotator.Annotator_assignUnitsId(self, item)
            elif type == Annotator.Type.VARIABLE:
                return _annotator.Annotator_assignVariableId(self, item)

            if type == Annotator.Type.CONNECTION:
                return _annotator.Annotator_assignConnectionIdForPython(self, item, item2)
            elif type == Annotator.Type.MAP_VARIABLES:
                return _annotator.Annotator_assignMapVariablesIdForPython(self, item, item2)
            elif type == Annotator.Type.UNIT:
                return _annotator.Annotator_assignUnitIdForPython(self, item, item2)
            return ""
       
        def unit(self, id):
            r"""Return the UnitItem with the given id.  The first item is the parent UnitsPtr item, the second is the index of this unit."""
            return (_annotator.Annotator_unitParentForPython(self, id), _annotator.Annotator_unitIndexForPython(self, id))

        def connection(self, id):
            r"""Retrieve a tuple of VariablePtr items from a connection with the given id."""
            return (_annotator.Annotator_connectionForPython(self, id, 0), _annotator.Annotator_connectionForPython(self, id, 1))

        def mapVariables(self, id):
            r"""Retrieve a tuple of VariablePtr items from a map_variables with the given id."""
            return (_annotator.Annotator_mapVariablesForPython(self, id, 0), _annotator.Annotator_mapVariablesForPython(self, id, 1))

        def item(self, id):
            r"""Retrieve the item with the given id."""
            type = _annotator.Annotator_itemTypeForPython(self, id)
            if type == Annotator.Type.COMPONENT:
                return (type, _annotator.Annotator_component(self, id))
            elif type == Annotator.Type.COMPONENT_REF:
                return (type, _annotator.Annotator_componentRef(self, id))
            elif type == Annotator.Type.CONNECTION:
                return (type, _annotator.Annotator_connection(self, id))
            elif type == Annotator.Type.ENCAPSULATION:
                return (type, _annotator.Annotator_encapsulation(self, id))
            elif type == Annotator.Type.IMPORT:
                return (type, _annotator.Annotator_import(self, id))
            elif type == Annotator.Type.ISSUE:
                return (type, _annotator.Annotator_issue(self, id))
            elif type == Annotator.Type.MAP_VARIABLES:
                return (type, _annotator.Annotator_mapVariables(self, id))
            elif type == Annotator.Type.MODEL:
                return (type, _annotator.Annotator_model(self, id))
            elif type == Annotator.Type.RESET:
                return (type, _annotator.Annotator_reset(self, id))
            elif type == Annotator.Type.RESET_VALUE:
                return (type, _annotator.Annotator_resetValue(self, id))
            elif type == Annotator.Type.TEST_VALUE:
                return (type, _annotator.Annotator_testValue(self, id)) 
            elif type == Annotator.Type.UNIT:
                return (type, _annotator.Annotator_unit(self, id))
            elif type == Annotator.Type.UNITS:
                return (type, _annotator.Annotator_units(self, id))
            elif type == Annotator.Type.VARIABLE:
                return (type, _annotator.Annotator_variable(self, id))
            return (-1, None)
        %}
    }

%include "libcellml/types.h"
%include "libcellml/annotator.h"
