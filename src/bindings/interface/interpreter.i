%module(package="libcellml") interpreter

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "analysermodel.i"
%import "createconstructor.i"

%feature("docstring") libcellml::Interpreter
"Creates a :class:`Interpreter` object.";

%feature("docstring") libcellml::Interpreter::model
"Returns the model to interpret.";

%feature("docstring") libcellml::Interpreter::setModel
"Sets the model to interpret.";

%feature("docstring") libcellml::Interpreter::voi
"Returns the value of the model's variable of integration.";

%feature("docstring") libcellml::Interpreter::stateCount
"Returns the number of states in the model.";

%feature("docstring") libcellml::Interpreter::states
"Returns the model's states.";

%feature("docstring") libcellml::Interpreter::rateCount
"Returns the number of rates in the model.";

%feature("docstring") libcellml::Interpreter::rates
"Returns the model's rates.";

%feature("docstring") libcellml::Interpreter::variableCount
"Returns the number of variables in the model.";

%feature("docstring") libcellml::Interpreter::variables
"Returns the model's variables.";

%feature("docstring") libcellml::Interpreter::initialiseVariables
"Initialises the model's variables.";

%feature("docstring") libcellml::Interpreter::computeComputedConstants
"Computes the model's computed constants.";

%feature("docstring") libcellml::Interpreter::computeRates
"Computes the model's rates.";

%feature("docstring") libcellml::Interpreter::computeVariables
"Computes the model's variables.";

%{
#include "libcellml/interpreter.h"
%}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(Interpreter)

%include "libcellml/interpreter.h"
