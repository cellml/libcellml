%module(package="libcellml") interpreter

#define LIBCELLML_EXPORT

%{
#define SWIG_FILE_WITH_INIT
%}
%include "numpy.i"
%init %{
import_array();
%}

%apply (double* INPLACE_ARRAY1, int DIM1) {(double* constants, int)};
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* computedConstants, int)};
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* algebraic, int)};
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* states, int)};
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* rates, int)};
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* externals, int)};

%import "analysermodel.i"
%import "createconstructor.i"

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

%{
#include "libcellml/interpreter.h"
%}

%extend libcellml::Interpreter {
    void initialiseVariables(double* constants, int constants_size,
                           double* computedConstants, int computedConstants_size,
                           double* algebraic, int algebraic_size) const {
        $self->initialiseVariables(constants, computedConstants, algebraic);
    }

    void initialiseVariables(double* states, int states_size,
                             double* rates, int rates_size,
                             double* constants, int constants_size,
                             double* computedConstants, int computedConstants_size,
                             double* algebraic, int algebraic_size) const {
        $self->initialiseVariables(states, rates, constants, computedConstants, algebraic);
    }

    void computeComputedConstants(double* constants, int constants_size,
                                  double* computedConstants, int computedConstants_size) const {
        $self->computeComputedConstants(constants, computedConstants);
    }

    void computeRates(double voi,
                      double* states, int states_size,
                      double* rates, int rates_size,
                      double* constants, int constants_size,
                      double* computedConstants, int computedConstants_size,
                      double* algebraic, int algebraic_size) const {
        $self->computeRates(voi, states, rates, constants, computedConstants, algebraic);
    }

    void computeVariables(double* constants, int constants_size,
                          double* computedConstants, int computedConstants_size,
                          double* algebraic, int algebraic_size) const {
        $self->computeVariables(constants, computedConstants, algebraic);
    }

    void computeVariables(double voi,
                          double* states, int states_size,
                          double* rates, int rates_size,
                          double* constants, int constants_size,
                          double* computedConstants, int computedConstants_size,
                          double* algebraic, int algebraic_size) const {
        $self->computeVariables(voi, states, rates, constants, computedConstants, algebraic);
    }
}

%pythoncode %{
# libCellML generated wrapper code starts here.
%}

%create_constructor(Interpreter)

%include "libcellml/interpreter.h"
