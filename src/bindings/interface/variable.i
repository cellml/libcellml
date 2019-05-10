%module(package="libcellml") variable

#define LIBCELLML_EXPORT

%import "types.i"
%import "namedentity.i"

%feature("docstring") libcellml::Variable
"Represents a CellML Variable entity";

%feature("docstring") libcellml::Variable::addEquivalence
"Adds an equivalence relation between this variable and the given one (both
objects are updated)";

%feature("docstring") libcellml::Variable::getEquivalentVariable
"Returns the equivalent variable at the given index.";

%feature("docstring") libcellml::Variable::hasEquivalentVariable
"Tests if the given variable is in this variable's set of equivalent
variables.";

%feature("docstring") libcellml::Variable::isEquivalentVariable
"Tests whether the argument variable is equivalent to this variable.";

%feature("docstring") libcellml::Variable::removeEquivalence
"Removes an equivalence between this variable and the given one (both objects
are updated).

Returns `True` on success.";

%feature("docstring") libcellml::Variable::removeAllEquivalences
"Removes all equivalent variables for this variable (all relevant objects are
updated).";

%feature("docstring") libcellml::Variable::equivalentVariableCount
"Returns the number of equivalent variables for this variable.";

%feature("docstring") libcellml::Variable::getUnits
"Returns the name of the units set for this variable (empty string if none)";

%feature("docstring") libcellml::Variable::setUnits
"Sets the units for this variable to the given string (name) or Units object.";

%feature("docstring") libcellml::Variable::getInitialValue
"Returns the string corresponding to the initial value for this variable.";

%feature("docstring") libcellml::Variable::setInitialValue
"Sets this variable's initial value, given as a string, number, or variable
reference.";

%feature("docstring") libcellml::Variable::getInterfaceType
"Returns this variable's interface type as string.";

%feature("docstring") libcellml::Variable::setInterfaceType
"Sets this variable's interfacetype to the given type specified as string or
InterfaceType.";

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Variable {
        VariablePtr getEquivalentVariable(long index) {
            if(index < 0) return nullptr;
            return $self->getEquivalentVariable(size_t(index));
        }
    }
#endif

%{
#include "libcellml/variable.h"
%}

%ignore libcellml::Variable::Variable(Variable &&);
%ignore libcellml::Variable::operator =;

%include "libcellml/types.h"
%include "libcellml/variable.h"
