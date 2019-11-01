%module(package="libcellml") reset

#define LIBCELLML_EXPORT

%include "createconstructor.i"

%import "types.i"
%import "orderedentity.i"

%feature("docstring") libcellml::Reset
"The Reset class is for describing a CellML reset.";

%feature("docstring") libcellml::Reset::setVariable
"Sets the :class: Variable for this reset.";

%feature("docstring") libcellml::Reset::variable
"Returns the :class: Variable of this reset.";

%feature("docstring") libcellml::Reset::addWhen
"Add a copy of the given :class: When as a child When of this :class: Reset.";

%feature("docstring") libcellml::Reset::removeWhen
"Remove the when with the given :param: index. :param: index must be in the range [0, #whens).";

%feature("docstring") libcellml::Reset::removeAllWhens
"Clears all whens that have been added to this reset.";

%feature("docstring") libcellml::Reset::containsWhen
"Tests to see if the argument when pointer :param: when is contained
within this When entity. Returns True if the when is in the reset
entity and False otherwise.";

%feature("docstring") libcellml::Reset::when
"Returns a reference to a when at the given :param: index.  :param: index must be in the range [0, #whens).";

%feature("docstring") libcellml::Reset::takeWhen
"Removes the when at the given :param: index position and returns it. :param: index must be in the range [0, #Whens).";

%feature("docstring") libcellml::Reset::replaceWhen
"Replaces the when at the :param: index with when :param: when. :param: index must be in the range [0, #whens).";

%feature("docstring") libcellml::Reset::whenCount
"Returns the number of whens the reset contains.";

#if defined(SWIGPYTHON)
    // Allow any type of input to be converted to bool
    %typemap(typecheck,precedence=SWIG_TYPECHECK_BOOL) bool { $1 = 1; }
    %typemap(in) bool { $1 = PyObject_IsTrue($input) == 1; }

    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Reset {
        WhenPtr when(long index) const {
            if (index < 0) return nullptr;
            return $self->when(size_t(index));
        }
        bool removeWhen(long index) {
            if (index < 0) return false;
            return $self->removeWhen(size_t(index));
        }
        WhenPtr takeWhen(long index) {
            if (index < 0) return nullptr;
            return $self->takeWhen(size_t(index));
        }
        bool replaceWhen(long index, const WhenPtr &c) {
            if (index < 0) return false;
            return $self->replaceWhen(size_t(index), c);
        }
    }
#endif

%{
#include "libcellml/reset.h"
%}

%create_constructor(Reset)

%include "libcellml/types.h"
%include "libcellml/reset.h"

