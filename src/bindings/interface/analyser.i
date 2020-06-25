%module(package="libcellml") analyser

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "logger.i"
%import "types.i"

#ifdef SWIGPYTHON
// %import "analyserequation.i"
// %import "analyserequationast.i"
// %import "analysermodel.i"
// %import "analyservariable.i"
#endif

%feature("docstring") libcellml::Analyser
"Creates an :class:`Analyser` object.";

%feature("docstring") libcellml::Analyser::processModel
"Processes a :class:`Model` to determine whether it can be used for simulation purposes.";

%feature("docstring") libcellml::Analyser::model
"Returns an :class:`AnalysedModel`.";

%{
#include "libcellml/analyser.h"
%}

%pythonappend libcellml::Analyser::Analyser %{
from libcellml import AnalyserProfile
profile = AnalyserProfile(AnalyserProfile.Profile.PYTHON)
self.setProfile(profile)
%}

%create_constructor(Analyser)

%include "libcellml/types.h"
%include "libcellml/analyser.h"
