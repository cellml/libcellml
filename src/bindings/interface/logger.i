%module(package="libcellml") logger

#define LIBCELLML_EXPORT

%import "types.i"

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Logger {
        ErrorPtr getError(long index) {
            if(index < 0) return nullptr;
            return $self->getError(size_t(index));
        }
    }
#endif

%{
#include "libcellml/logger.h"
%}

%ignore libcellml::Logger::Logger(Logger &&);
%ignore libcellml::Logger::operator =;

%include "libcellml/types.h"
%include "libcellml/logger.h"
