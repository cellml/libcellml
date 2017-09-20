%module(package="libcellml") model

#define LIBCELLML_EXPORT

%import "types.i"
%import "componententity.i"

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

