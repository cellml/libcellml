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
"Interacs with CellML objects using their id attribute.";

%feature("docstring") libcellml::Annotator::build
"Construct a searchable map of items in the model."

%feature("docstring") libcellml::Annotator::item
"Retrieve the item with the given id."

%feature("docstring") libcellml::Annotator::component
"Return the component with the given id."

%feature("docstring") libcellml::Annotator::model
"Return the model with the given id."

%feature("docstring") libcellml::Annotator::variable
"Return the variable with the given id."

%feature("docstring") libcellml::Annotator::importSource
"Return the import source with the given id."

%feature("docstring") libcellml::Annotator::units
"Return the units with the given id."

%feature("docstring") libcellml::Annotator::reset
"Return the reset with the given id."

%feature("docstring") libcellml::Annotator::testValue
"Return the ResetPtr whose test_value has the given id."

%feature("docstring") libcellml::Annotator::resetValue
"Return the ResetPtr whose reset_value has the given id."

%feature("docstring") libcellml::Annotator::componentRef
"Return the ComponentPtr with the given component_ref id."

%feature("docstring") libcellml::Annotator::itemForPython
"Private: Utility function to retrieve item based on id."

%feature("docstring") libcellml::Annotator::itemTypeForPython
"Private: Utility function to retrieve item type integer based on id."

%feature("docstring") libcellml::Annotator::unitIndexForPython
"Private: Utility function to retrieve index of Unit item within parent Units item based on given id."

%feature("docstring") libcellml::Annotator::unitParentForPython
"Private: Utility function to retrieve UnitsPtr parent for Unit item with given id."

%feature("docstring") libcellml::Annotator::connectionForPython
"Private: Utility function to retrieve one of VariablePtrs connection with given id."

%feature("docstring") libcellml::Annotator::mapVariablesForPython
"Private: Utility function to retrieve one of VariablePtrs map_variables with given id."

%{
#include "libcellml/annotator.h"
%}

%ignore libcellml::Annotator::item;
%ignore libcellml::Annotator::unit;
%ignore libcellml::Annotator::connection;
%ignore libcellml::Annotator::mapVariables;

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

    %pythoncode %{
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
            if type == 0:
                return (type, _annotator.Annotator_component(self, id))
            elif type == 1:
                return (type, _annotator.Annotator_componentRef(self, id))
            elif type == 2:
                return (type, _annotator.Annotator_connection(self, id))
            elif type == 3:
                return (type, _annotator.Annotator_encapsulation(self, id))
            elif type == 4:
                return (type, _annotator.Annotator_import(self, id))
            elif type == 5:
                return (type, _annotator.Annotator_issue(self, id))
            elif type == 6:
                return (type, _annotator.Annotator_mapVariables(self, id))
            elif type == 7:
                return (type, _annotator.Annotator_model(self, id))
            elif type == 8:
                return (type, _annotator.Annotator_reset(self, id))
            elif type == 9:
                return (type, _annotator.Annotator_resetValue(self, id))
            elif type == 10:
                return (type, _annotator.Annotator_testValue(self, id)) 
            elif type == 11:
                return (type, _annotator.Annotator_unit(self, id))
            elif type == 12:
                return (type, _annotator.Annotator_units(self, id))
            elif type == 13:
                return (type, _annotator.Annotator_variable(self, id))
            return (-1, None)
        %}
    }

%include "libcellml/types.h"
%include "libcellml/annotator.h"
