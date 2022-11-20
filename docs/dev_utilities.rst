=========
Utilities
=========

This document covers the utilities that are availble to developers of libCellML.
The utilities are not built or made available by default.
The utilities can be enabled through the configuration of the library.
In order to enable the utilities set the configuration variable LIBCELLML_ENABLE_UTILITES to true.

The available utilities are:

#. Create MathML DTD files
#. Update generator profile SHA-1 values

Create MathML DTD Files
=======================

The create MathML DTD files utility generates a compressed MathML DTD of determining the validity of MathML strings.
It can be run using the *create_mathml_dtd_files* target.
For a make based envirionment the utility may be run with the following command::

  make create_mathml_dtd_files

Update generator profile SHA-1 values
=====================================

The update generator profile SHA-1 values utility calculates the SHA-1 values for the current C and Python profiles.
The utility updates the header file *generatorprofilesha1values.h* in the source tree of the current build.
For a make based envirionment the utility may be run with the following command::

  make update_generator_profile_sha1_values
