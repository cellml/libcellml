==================
Building libCellML
==================

This document covers building libCellML from source.
It is assumed that you already have the codebase downloaded and ready for building.
The variable ``LIBCELLML_SRC`` shall be used to refer to the directory containing the ``LICENSE`` file for libCellML.

Build Directory
===============

It is best to build libCellML outside of the source tree.
To this end, create a build directory that is not the ``LIBCELLML_SRC`` directory.
A sibling directory of ``LIBCELLML_SRC`` is a good choice, named something like ``build`` or ``libcellml-build``.
The variable ``LIBCELLML_BUILD`` shall be used to refer to the build directory.

Configuration 
=============

Linux and MacOS
---------------

The libCellML library uses the `CMake <https://cmake.org/>`_ build configuration tool to configure the library.
Version 3.2 or greater of `CMake <https://cmake.org/>`_ is required to configure libCellML.

The configuration options for the library are detailed in the following table.
The command line options can be set with the ``-D`` flag, like so ``-DBUILD_TYPE=Release``.
Please note that in `CMake <https://cmake.org/>`_ GUI Configuration applications, the config variable is prefixed with ``LIBCELLML_``

.. include:: dev_configuration_options.rst

.. Select a generator that is appropriate for your system, or let the CMake configuration application

From the command line (bash shell), libCellML can be configured to create an optimised shared object library like so::

  cd $LIBCELLML_BUILD
  cmake -DBUILD_TYPE=Release $LIBCELLML_SRC

Windows
-------

When configuring libCellML on `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`_, we may need to set the location of the `LibXml2 <http://xmlsoft.org/>`_ library, which is dependent on the computer's environment settings.
We can set the location of the `LibXml2 <http://xmlsoft.org/>`_ library when we configure libCellML.
When we configure libCellML, the location of `LibXml2 <http://xmlsoft.org/>`_ can be specified through the command line by adding the parameter::

  -DLibXml2_DIR="C:\Program Files\libxml2 2.9.6\lib\cmake"

to the configuration command.
This assumes that the recommended LibXml2 binaries have been installed to the default location ``C:\Program Files\libxml2 2.9.6``.  

Please note that libCellML will _only_ work with a 64-bit installation of libxml2.  A pre-built 64-bit installer is available from the `OpenCMISS repository <https://github.com/OpenCMISS-Dependencies/libxml2/releases>`_; 32-bit binaries or 32-bit builds will not work. 


You may need to also download and install `Graphvis <https://graphviz.gitlab.io/_pages/Download/Download_windows.html>`_ and add it to your PATH.  This is used by Doxygen to generate graphs of the dependencies between classes. You may also need to restart your computer so that it recognises your Doxygen installation.


Windows CMake-GUI
+++++++++++++++++

When we use the CMake-GUI application on `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`_, we first set the location of the source files and the location for the generated build files.
:numref:`fig_devBuilding_windowsCMakeGUISourceBuildDirs` shows the source files directory and the build directory set for user *andre*.

Note that the COVERAGE and MEMCHECK options should be set to OFF for a Windows build; these options will only run on Linux.

.. _fig_devBuilding_windowsCMakeGUISourceBuildDirs:

.. figure:: images/libCellMLBuilding-CMakeGUISourceBuildDirs.png
   :align: center
   :alt: CMake-GUI with initial values for source and build directories set.

   CMake-GUI with source and build directores set for user *andre*.

When we press the *Configure* button, `CMake <https://cmake.org/>`_ performs an initial configuration.
This initial configuration is likely to encounter an error because `CMake <https://cmake.org/>`_ is not able to find `LibXml2 <http://xmlsoft.org/>`_.
We can see in :numref:`fig_devBuilding_windowsCMakeConfigurationError` that this has happened for user *andre*.

.. _fig_devBuilding_windowsCMakeConfigurationError:

.. figure:: images/libCellMLBuilding-CMakeWindowsConfigurationError.png
   :align: center
   :alt: CMake-GUI on Windows showing configuration error after initial configuration attempt.

   CMake-GUI showing configuration error after initial configuration attempt.

We can resolve this error easily if we set the value of the ``LibXml2_DIR`` variable to the location of the `LibXml2 <http://xmlsoft.org/>`_ ``cmake`` directory.
:numref:`fig_devBuilding_windowsCMakeLibXml2DIRNotFound` shows the ``LibXml2_DIR`` variable with the value of ``LibXml2_DIR-NOTFOUND``.

.. _fig_devBuilding_windowsCMakeLibXml2DIRNotFound:

.. figure:: images/libCellMLBuilding-CMakeWindowsLibXml2DIRNotFound.png
   :align: center
   :alt: LibXml2_DIR variable with a value of LibXml2_DIR-NOTFOUND.

   ``LibXml2_DIR`` variable with a value of ``LibXml2_DIR-NOTFOUND``.

Setting the value of ``LibXml2_DIR`` to ``C:\Program Files\libxml2 2.9.6\lib\cmake`` and configuring again will result in a successful configuration (:numref:`fig_devBuilding_windowsCMakeLibXml2DirSet` shows a successfully configured ``LibXml2_DIR`` variable) from which build files may be generated using the *Generate* button.

.. _fig_devBuilding_windowsCMakeLibXml2DirSet:

.. figure:: images/libCellMLBuilding-CMakeWindowsLibXml2DirSet.png
   :align: center
   :alt: LibXml2_DIR variable with a value of C:\Program Files\libxml2 2.9.6\lib\cmake.

   ``LibXml2_DIR`` variable with a value of ``C:\Program Files\libxml2 2.9.6\lib\cmake``.

If `LibXml2 <http://xmlsoft.org/>`_ was not installed to ``C:\Program Files\libxml2 2.9.6``, you will need to adjust the path to match your situation.

Note: If after pushing the *Configure* button your path to the LibXml2 directory is lost, and CMake continues to return an error about it, make sure that your LibXml2 is the required 64-bit version.  If not, simply download and run the *.exe 64-bit installer from the `OpenCMISS repository <https://github.com/OpenCMISS-Dependencies/libxml2/releases/>`_, and check that your paths and settings above match the location of this installation.   

Build
=====

Once the build scripts have been generated by `CMake <https://cmake.org/>`_, invoke the build with the appropriate command.
For ``Makefile``-based configurations, the command is simply::

  make

If testing is enabled, run the tests using the test target::

  make test

or using the `ctest <https://cmake.org/cmake/help/latest/manual/ctest.1.html>`_ application::

  ctest

For a more verbose output, run::

  ctest -V

Build in Windows and Visual Studio
----------------------------------

Once you have used CMake to configure and generate your project files, just push the Open project button to launch the project in your Visual Studio IDE.  This is the equivalent of opening the solution *.sln file inside your build folder.  The libCellML solution is a library of different projects and each of uses slightly different configurations. 

Possible issues

"The code execution cannot proceed because libcellmld.dll was not found.  Reinstalling the program may fix this problem."

.. _fig_devBuilding_libcellml_dll_not_found:

.. figure:: images/libcellml_dll_not_found.png
   :align: center
   :alt: System error when dll is not found.

Solution:  You need to add location of the file(s) to the environment path of the project.  To do this, right-click the project and open the Properties editor.  Under the menu Configuration Properties > Debugging > Environment click the Edit button, and add the path to your libcellmldl.dll file.  You should find this file in your build directory in the  `\\src\\Debug` folder.  

- The statement should begin with "PATH=" and then contain a list of semicolon-separated directories.
- The statement should end with "%PATH%" in order to include elements included from elsewhere.
- Note that if your path contains spaces you must surround it with double quotation marks.
- Note that the end of each path item must be a folder name (not a slash) and terminated with a semi-colon.

You may need to repeat this process for the gtest.dll and gtest_main.dll files as well.  These are found in your build directory, under "tests\\gtest\\Debug" or similar.

      





