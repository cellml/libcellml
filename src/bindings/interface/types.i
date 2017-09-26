/*
Provides support for shared pointers declared in types.h

Only meant to be included, shouldn't be passed to cmake as a module!
*/
%include <std_shared_ptr.i>

%shared_ptr(libcellml::Component)
%shared_ptr(libcellml::ComponentEntity)
%shared_ptr(libcellml::Entity)
%shared_ptr(libcellml::Error)
%shared_ptr(libcellml::ImportSource)
%shared_ptr(libcellml::ImportedEntity)
%shared_ptr(libcellml::Model)
%shared_ptr(libcellml::NamedEntity)
%shared_ptr(libcellml::Units)
%shared_ptr(libcellml::Variable)
