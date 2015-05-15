

Options
-------

============== ============ =========================================
Config         Default      Description
============== ============ =========================================
BUILD_TYPE     Release      The type of build Release, Debug etc.
-------------- ------------ -----------------------------------------
BUILD_SHARED   ON           Build shared libraries (so, dylib, DLLs).
-------------- ------------ -----------------------------------------
TWAE :sup:`*`  ON           Treat warnings as errors.
-------------- ------------ -----------------------------------------
INSTALL_PREFIX /usr/lib     Install path prefix (platform specific).
-------------- ------------ -----------------------------------------
UNIT_TESTS     ON           Enable tests.
-------------- ------------ -----------------------------------------
MEMCHECK       ON           Enable memcheck testing (if available).
-------------- ------------ -----------------------------------------
COVERAGE       ON           Enable coverage testing (if available).
============== ============ =========================================

:sup:`*` In CMake GUI Configuration applications this option is given in full ``LIBCELLML_TREAT_WARNINGS_AS_ERRORS``

.. note In CMake GUI Configuration applications the config variable is prefixed with 'LIBCELLML\_'

.. ================================== ============== =========================================
.. GUI Config                         CLI Config     Description
.. ================================== ============== =========================================
.. LIBCELLML_BUILD_TYPE               BUILD_TYPE     The type of build Release, Debug etc.
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_BUILD_SHARED             BUILD_SHARED   Build shared libraries (so, dylib, DLLs).
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_TREAT_WARNINGS_AS_ERRORS TWAE           Treat warnings as errors
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_INSTALL_PREFIX           INSTALL_PREFIX Install path prefix
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_UNIT_TESTS               UNIT_TESTS     Enable tests.
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_MEMCHECK                 MEMCHECK       Enable memcheck testing. (if available)
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELML_COVERAGE                  COVERAGE       Enable coverage testing. (if available)
.. ================================== ============== =========================================

