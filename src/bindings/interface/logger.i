%module(package="libcellml") logger

#define LIBCELLML_EXPORT

%import "types.i"

%feature("docstring") libcellml::Logger
"Base class for all serialisable libCellML classes.";

%feature("docstring") libcellml::Logger::removeAllIssues
"Clears all issues from this logger.";

%feature("docstring") libcellml::Logger::addIssue
"Adds an issue to this logger.";

%feature("docstring") libcellml::Logger::issue
"Returns the issue of any level at the specified 'index'.";

%feature("docstring") libcellml::Logger::issueCount
"Returns the number of issues currently stored in the logger.";

%feature("docstring") libcellml::Logger::addError
"Adds an issue with level of 'error' to this logger.";

%feature("docstring") libcellml::Logger::error
"Returns the issue of level 'error' at the specified 'index'.";

%feature("docstring") libcellml::Logger::errorCount
"Returns the number of issues of level 'error' currently stored in the logger.";

%feature("docstring") libcellml::Logger::addWarning
"Adds an issue with level of 'warning' to this logger.";

%feature("docstring") libcellml::Logger::warning
"Returns the issue of level 'warning' at the specified 'index'.";

%feature("docstring") libcellml::Logger::warningCount
"Returns the number of issues of level 'warning' currently stored in the logger.";

%feature("docstring") libcellml::Logger::addHint
"Adds an issue with level of 'hint' to this logger.";

%feature("docstring") libcellml::Logger::hint
"Returns the issue of level 'hint' at the specified 'index'.";

%feature("docstring") libcellml::Logger::hintCount
"Returns the number of issues of level 'hint' currently stored in the logger.";

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Logger {
        IssuePtr error(long index) {
            if (index < 0) return nullptr;
            return $self->error(size_t(index));
        }
    }
#endif

%{
#include "libcellml/logger.h"
%}

%ignore libcellml::Logger::Logger();

%include "libcellml/types.h"
%include "libcellml/logger.h"
