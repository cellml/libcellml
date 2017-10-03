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
"Returns a math string if one has been created for this component (empty string
if not).";

%feature("docstring") libcellml::Component::setMath
"Sets the math string for this component.
If `math` is an empty string, math will be removed from the component.";

%feature("docstring") libcellml::Component::addVariable
"Adds variable `v` to this component.";

%feature("docstring") libcellml::Component::getVariable
"Returns a Variable from this component, specified by name or index.";

%feature("docstring") libcellml::Component::hasVariable
"Tests if this component contains a given variable, specified by name or as
`Variable` object.";

%feature("docstring") libcellml::Component::removeVariable
"Removes a variable from this component, specified by name, index, or
`Variable` object.

If the variable to be removed is in a connection (is equivalent to another
variable), this component will not be serialised in the connection.

Returns `True` on success.";

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
