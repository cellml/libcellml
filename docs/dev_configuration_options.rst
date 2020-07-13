Options
-------

============== ============ =========================================
Config         Default      Description
============== ============ =========================================
BUILD_SHARED   ON           Build shared libraries (so, dylib, DLLs).
-------------- ------------ -----------------------------------------
BUILD_TYPE     Release      The type of build Release, Debug, etc.
-------------- ------------ -----------------------------------------
CCACHE         ON           Enable ccache (if available).
-------------- ------------ -----------------------------------------
CLCACHE        ON           Enable clcache (if available).
-------------- ------------ -----------------------------------------
COVERAGE       ON           Enable coverage testing (if available).
-------------- ------------ -----------------------------------------
INSTALL_PREFIX /usr/lib     Install path prefix (platform specific).
-------------- ------------ -----------------------------------------
MEMCHECK       ON           Enable memcheck testing (if available).
-------------- ------------ -----------------------------------------
TWAE :sup:`*`  ON           Treat warnings as errors.
-------------- ------------ -----------------------------------------
UNIT_TESTS     ON           Enable tests.
============== ============ =========================================

:sup:`*` In CMake GUI Configuration applications this option is given in full ``LIBCELLML_TREAT_WARNINGS_AS_ERRORS``

.. note In CMake GUI Configuration applications the config variable is prefixed with 'LIBCELLML\_'

.. ================================== ============== =========================================
.. GUI Config                         CLI Config     Description
.. ================================== ============== =========================================
.. LIBCELLML_BUILD_SHARED             BUILD_SHARED   Build shared libraries (so, dylib, DLLs).
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_BUILD_TYPE               BUILD_TYPE     The type of build Release, Debug, etc.
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELML_CLCACHE                   CLCACHE        Enable clcache (if available).
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELML_CCACHE                    CCACHE         Enable ccache (if available).
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELML_COVERAGE                  COVERAGE       Enable coverage testing (if available).
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_INSTALL_PREFIX           INSTALL_PREFIX Install path prefix.
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_MEMCHECK                 MEMCHECK       Enable memcheck testing (if available).
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_TREAT_WARNINGS_AS_ERRORS TWAE           Treat warnings as errors.
.. ---------------------------------- -------------- -----------------------------------------
.. LIBCELLML_UNIT_TESTS               UNIT_TESTS     Enable tests.
.. ================================== ============== =========================================
