
===============
Coding Standard
===============


In essence we seek code that looks good, is easy to read and has great documentation.  We don't want to spend time discussing the minutiae of the coding style.

The following is a list of exceptions/deviations from the google style guide that have been agreed upon for libCellML software development purposes.  Think of it like case-law.

 * lower camel case class method names
 * Indent core code 4 spaces at a time (no tabs); for CMake files use 2-space indentation.

Doxygen Comments
================

 * Code-words (e.g., true/false, std::string) should be styled as typewriter text with a preceding "@c".
 * Doxygen comments should be sentence-style: beginning with capitalisation (except code-words) and ending with punctuation. However, they do not need to form grammatically correct sentences.

Test Naming
===========

 * Names should respect the lower camel case convention.
 * Names should be explicit enough to identify the specific code features they cover.

Variable Naming
===============

The following rules for naming of variables should be followed.

 * Class member variables: mMyClassMemberVariable
 * Function parameter variables: myFunctionParameterVariable
 * Local variables: myLocalVariable

