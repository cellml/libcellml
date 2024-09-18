%module(package="libcellml") interpreter

#define LIBCELLML_EXPORT

%{
#define SWIG_FILE_WITH_INIT
#include "libcellml/interpreter.h"
%}

%import "analysermodel.i"
%import "createconstructor.i"
%import "numpy.i"

%feature("docstring") libcellml::Interpreter
"Creates a :class:`Interpreter` object.";

%feature("docstring") libcellml::Interpreter::model
"Returns the model to interpret.";

%feature("docstring") libcellml::Interpreter::setModel
"Sets the model to interpret.";

%feature("docstring") libcellml::Interpreter::initialiseVariables
"Initialises the model's variables.";

%feature("docstring") libcellml::Interpreter::computeComputedConstants
"Computes the model's computed constants.";

%feature("docstring") libcellml::Interpreter::computeRates
"Computes the model's rates.";

%feature("docstring") libcellml::Interpreter::computeVariables
"Computes the model's variables.";

%init %{
import_array();
%}

%apply (double* INPLACE_ARRAY1) {(double *array)}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(Interpreter)

%include "libcellml/interpreter.h"
