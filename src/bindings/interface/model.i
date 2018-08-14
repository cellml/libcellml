%module(package="libcellml") model

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

%feature("docstring") libcellml::Model
"Represents a CellML model.";

%feature("docstring") libcellml::Model::addUnits
"Add a copy of the given Units to this model.";

%feature("docstring") libcellml::Model::getUnits
"Returns a Units object from this Model, specified by index or name.

Only the first matching Units is returned.";

%feature("docstring") libcellml::Model::hasUnits
"Tests to see if this model has the given units, specified by name.";

%feature("docstring") libcellml::Model::removeUnits
"Removes the Units specified by index, name or Units object.

Only the first matching Units is removed.

Returns `True` on success.";

%feature("docstring") libcellml::Model::removeAllUnits
"Removes all units stored in this model.";

%feature("docstring") libcellml::Model::replaceUnits
"Replaces a Units object, specified by index, name or Units object, by another
Units (second argument).

Only the first matching Units is replaced.

Returns `True` on success.";

%feature("docstring") libcellml::Model::takeUnits
"Removes and returns the Units specified by index or name.

Only the first matching Units is removed and returned.";

%feature("docstring") libcellml::Model::unitsCount
"Returns the number of units this model contains.";

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Model {
        bool removeUnits(long index) {
            if(index < 0) return false;
            return $self->removeUnits(size_t(index));
        }
        UnitsPtr getUnits(long index) const {
            if(index < 0) return nullptr;
            return $self->getUnits(size_t(index));
        }
        UnitsPtr takeUnits(long index) {
            if(index < 0) return nullptr;
            return $self->takeUnits(size_t(index));
        }
        bool replaceUnits(long index, UnitsPtr &units) {
            if(index < 0) return false;
            return $self->replaceUnits(size_t(index), units);
        }
    }
#endif

%{
#include "libcellml/model.h"
%}

%ignore libcellml::Model::Model(Model &&);
%ignore libcellml::Model::operator =;

%include "libcellml/types.h"
%include "libcellml/model.h"

