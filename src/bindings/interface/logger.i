%module(package="libcellml") logger

#define LIBCELLML_EXPORT

%import "types.i"

%{
#include "libcellml/logger.h"
%}

%ignore libcellml::Logger::Logger(Logger &&);
%ignore libcellml::Logger::operator =;

%include "libcellml/types.h"
%include "libcellml/logger.h"
