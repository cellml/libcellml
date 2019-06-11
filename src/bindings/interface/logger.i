%module(package="libcellml") logger

#define LIBCELLML_EXPORT

%import "types.i"

%feature("docstring") libcellml::Logger
"Base class for all serialisable libCellML classes.";

%feature("docstring") libcellml::Logger::addError
"Adds an error to this logger.";

%feature("docstring") libcellml::Logger::clearErrors
"Clears all errors from this logger.";

%feature("docstring") libcellml::Logger::getError
"Returns the error at the specified `index`.";

%feature("docstring") libcellml::Logger::errorCount
"Returns the number of errors currently stored in the logger.";

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Logger {
        ErrorPtr getError(long index) {
            if (index < 0) return nullptr;
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
