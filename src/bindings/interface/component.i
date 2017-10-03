%module(package="libcellml") component

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Component {
        VariablePtr getVariable(long index) const {
            if(index < 0) return nullptr;
            return $self->getVariable(size_t(index));
        }
        bool removeVariable(long index) {
            if(index < 0) return false;
            return $self->removeVariable(size_t(index));
        }
    }
#endif

%feature("docstring") libcellml::Component
"Represents a CellML component.";

%feature("docstring") libcellml::Component::setSourceComponent
"Marks this component as an imported component by defining an
`importSource` specifying the source of the import and the `name` of the
component in the `importSource`.";

%feature("docstring") libcellml::Component::appendMath
"Appends `math` to the existing math string for this component.";

%feature("docstring") libcellml::Component::getMath
"Returns a math string if one has been appended for this component. Returns an
empty string if math has not been appended (or has been removed).";

%feature("docstring") libcellml::Component::setMath
"Sets the math string for this component.
If `math` is an empty string, math will be removed from the component.";

%feature("docstring") libcellml::Component::addVariable
"Adds variable `v` to this component.";

%feature("docstring") libcellml::Component::getVariable
"Returns the variable at the given index `index`, or with the given`name`.";

%feature("docstring") libcellml::Component::hasVariable
"Tests if `variable` is in this component.";

%feature("docstring") libcellml::Component::removeVariable
"Removes a variable from this component, specified either by name, by index,
or by passing in the variable object.

If the variable to be removed is in a connection (is equivalent to another
variable), this component will not be serialised in the connection.";

%feature("docstring") libcellml::Component::removeAllVariables
"Clears all variables that have been added to this component.

If any of the variables to be removed are in connections (are equivalent to
other variables), this component will not be serialised in the connection.";

%feature("docstring") libcellml::Component::variableCount
"Returns the number of variables the component directly contains.";

%{
#include "libcellml/component.h"
%}

%ignore libcellml::Component::Component(Component &&);
%ignore libcellml::Component::operator =;

%include "libcellml/types.h"
%include "libcellml/component.h"
