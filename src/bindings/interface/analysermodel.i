%module(package="libcellml") analysermodel

#define LIBCELLML_EXPORT

%include <std_shared_ptr.i>

%feature("docstring") libcellml::AnalyserModel
"Creates an :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::isValid
"Tests if this :class:`AnalyserModel` object is valid.";

%feature("docstring") libcellml::AnalyserModel::type
"Returns the :enum:`AnalyserModel::Type`.";

%feature("docstring") libcellml::AnalyserModel::voi
"Returns the :class:`AnalyserVariable` for the variable of integration.";

%feature("docstring") libcellml::AnalyserModel::voi
"Returns the :class:`AnalyserVariable` for the variable of integration.";

%feature("docstring") libcellml::AnalyserModel::stateCount
"Returns the number of states contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::states
"Returns the states contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::state
"Removes the state, specified by index, contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::variableCount
"Returns the number of variables contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::variables
"Returns the variables contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::variable
"Removes the variable, specified by index, contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::equationCount
"Returns the number of equations contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::equations
"Returns the equations contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::equation
"Removes the equation, specified by index, contained by this :class:`AnalyserModel` object.";

%feature("docstring") libcellml::AnalyserModel::needEqFunction
"Tests if this :class:`AnalyserModel` object needs the equality function.";

%feature("docstring") libcellml::AnalyserModel::needNeqFunction
"Tests if this :class:`AnalyserModel` object needs the inequality function.";

%feature("docstring") libcellml::AnalyserModel::needLtFunction
"Tests if this :class:`AnalyserModel` object needs the less than function.";

%feature("docstring") libcellml::AnalyserModel::needLeqFunction
"Tests if this :class:`AnalyserModel` object needs the less or equal than function.";

%feature("docstring") libcellml::AnalyserModel::needGtFunction
"Tests if this :class:`AnalyserModel` object needs the greater than function.";

%feature("docstring") libcellml::AnalyserModel::needGeqFunction
"Tests if this :class:`AnalyserModel` object needs the greater or equal than function.";

%feature("docstring") libcellml::AnalyserModel::needAndFunction
"Tests if this :class:`AnalyserModel` object needs the and function.";

%feature("docstring") libcellml::AnalyserModel::needOrFunction
"Tests if this :class:`AnalyserModel` object needs the or function.";

%feature("docstring") libcellml::AnalyserModel::needXorFunction
"Tests if this :class:`AnalyserModel` object needs the xor function.";

%feature("docstring") libcellml::AnalyserModel::needNotFunction
"Tests if this :class:`AnalyserModel` object needs the not function.";

%feature("docstring") libcellml::AnalyserModel::needMinFunction
"Tests if this :class:`AnalyserModel` object needs the minimum function.";

%feature("docstring") libcellml::AnalyserModel::needMaxFunction
"Tests if this :class:`AnalyserModel` object needs the maximum function.";

%feature("docstring") libcellml::AnalyserModel::needSecFunction
"Tests if this :class:`AnalyserModel` object needs the secant function.";

%feature("docstring") libcellml::AnalyserModel::needCscFunction
"Tests if this :class:`AnalyserModel` object needs the cosecant function.";

%feature("docstring") libcellml::AnalyserModel::needCotFunction
"Tests if this :class:`AnalyserModel` object needs the cotangent function.";

%feature("docstring") libcellml::AnalyserModel::needSechFunction
"Tests if this :class:`AnalyserModel` object needs the hyperbolic secant function.";

%feature("docstring") libcellml::AnalyserModel::needCschFunction
"Tests if this :class:`AnalyserModel` object needs the hyperbolic cosecant function.";

%feature("docstring") libcellml::AnalyserModel::needCothFunction
"Tests if this :class:`AnalyserModel` object needs the hyperbolic cotangent function.";

%feature("docstring") libcellml::AnalyserModel::needAsecFunction
"Tests if this :class:`AnalyserModel` object needs the arc secant function.";

%feature("docstring") libcellml::AnalyserModel::needAcscFunction
"Tests if this :class:`AnalyserModel` object needs the arc cosecant function.";

%feature("docstring") libcellml::AnalyserModel::needAcotFunction
"Tests if this :class:`AnalyserModel` object needs the arc cotangent function.";

%feature("docstring") libcellml::AnalyserModel::needAsechFunction
"Tests if this :class:`AnalyserModel` object needs the arc hyperbolic secant function.";

%feature("docstring") libcellml::AnalyserModel::needAcschFunction
"Tests if this :class:`AnalyserModel` object needs the arc hyperbolic cosecant function.";

%feature("docstring") libcellml::AnalyserModel::needAcothFunction
"Tests if this :class:`AnalyserModel` object needs the arc hyperbolic cotangent function.";

%{
#include "libcellml/analysermodel.h"
%}

%shared_ptr(libcellml::AnalyserModel);

%include "libcellml/types.h"
%include "libcellml/analysermodel.h"
