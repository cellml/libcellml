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
"Returns the issue of any level at the specified ``index``.";

%feature("docstring") libcellml::Logger::issueCount
"Returns the number of issues currently stored in the logger.";

%feature("docstring") libcellml::Logger::error
"Returns the issue of level ERROR at the specified ``index``.";

%feature("docstring") libcellml::Logger::errorCount
"Returns the number of issues of level ERROR currently stored in the logger.";

%feature("docstring") libcellml::Logger::warning
"Returns the issue of level WARNING at the specified ``index``.";

%feature("docstring") libcellml::Logger::warningCount
"Returns the number of issues of level WARNING currently stored in the logger.";

%feature("docstring") libcellml::Logger::hint
"Returns the issue of level HINT at the specified ``index``.";

%feature("docstring") libcellml::Logger::hintCount
"Returns the number of issues of level HINT currently stored in the logger.";

%feature("docstring") libcellml::Logger::message
"Returns the issue of level MESSAGE at the specified ``index``.";

%feature("docstring") libcellml::Logger::messageCount
"Returns the number of issues of level MESSAGE currently stored in the logger.";

#if defined(SWIGPYTHON)
    // Treat negative size_t as invalid index (instead of unknown method)
    %extend libcellml::Logger {
        IssuePtr issue(long index) {
            if (index < 0) return nullptr;
            return $self->issue(size_t(index));
        }
    }
#endif

%{
#include "libcellml/logger.h"
%}

%ignore libcellml::Logger::Logger();

%include "libcellml/types.h"
%include "libcellml/logger.h"
