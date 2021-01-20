.. Developer Setup for libCellML

.. _devsetup:

=================
Development Setup
=================

This section describes how someone wanting to contribute to the libCellML project should set up their *working copy* for developing libCellML.

.. contents::

Overview
========

The libCellML codebase is hosted on `GitHub <https://github.com/>`__ and therefore `Git <https://git-scm.com/>`__ is used to track changes. Before you begin, you will need to have a few pre-requisites satisfied:

1. `GitHub <https://github.com/>`__ user account (for the rest of this document we will call our user *andre*).
#. `Git <https://git-scm.com/>`__ for tracking changes in code
#. `CMake <https://cmake.org/>`__ to configure the build files
#. Toolchain for building the library (dependent on the operating system).
#. `LibXml2 <http://xmlsoft.org/>`__, an external library used to parse XML
#. `Doxygen <https://doxygen.nl/>`__ to generate documentation

If Python bindings are required, the following packages are also needed:

a. `Python <https://www.python.org/>`__ Version 3.5.2 or later is needed for Sphinx (see below)
#. `SWIG <http://swig.org>`__ to generate the bindings for Python
#. `Sphinx <http://www.sphinx-doc.org/en/master/>`__ to generate documentation for Python bindings


Pre-requisite acquisition
=========================

In this section, we cover the retrieval and installation of pre-requisites.


.. _devsetup_git:

Git
---

Creating a `GitHub <https://github.com/>`__ user account is straightforward and can be done `here <https://github.com/join>`__.
Installing a `Git <https://git-scm.com/>`__ client is particular to each operating system and some pointers are offered below:

* `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`__ `Git <https://git-scm.com/>`__ is available from a variety of vendors.
We commonly use `Git for windows <http://gitforwindows.org/>`__, but other popular `Git <https://git-scm.com/>`__ implementations are:
  - `GitHub Desktop <https://desktop.github.com/>`__
  - `GitKracken <https://www.gitkraken.com/>`__
  - `Git SCM <https://git-scm.com/>`__

* `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`__ (and other `Linux <https://en.wikipedia.org/wiki/Linux>`__ distributions) `Git <https://git-scm.com/>`__ can be installed using the package manager with the command ``sudo apt-get install git``.
* `macOS <https://en.wikipedia.org/wiki/MacOS>`__ `Git <https://git-scm.com/>`__ is pre-installed and available from the command line.


.. _devsetup_cmake:

CMake
-----

`CMake <https://cmake.org/>`__ is the cross-platform family of tools designed to build, test and package software.
CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and to generate native makefiles and workspaces that can be used in the compiler environment of your choice.
Note that CMake version 3.2 or later is required to configure libCellML.

Again, installation of CMake is particular to each operating system.
For `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`__ (and other `Linux <https://en.wikipedia.org/wiki/Linux>`__ distributions), `CMake <https://cmake.org/>`__ can be installed using the package manager with the command ``sudo apt-get install cmake``.
For `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`__ and `macOS <https://en.wikipedia.org/wiki/MacOS>`__, `CMake <https://cmake.org/>`__ provides `installation binaries <https://cmake.org/download/>`__.
Choose the binary appropriate for your operating system and follow the installation instructions.


.. _devsetup_toolchain:

Toolchain
---------

The toolchain specifies the compiler that we will use to build libCellML.
Toolchains are highly dependent on the operating system.
When we test libCellML, we currently use `Visual Studio <https://visualstudio.microsoft.com/downloads/>`__ on `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`__, `GCC <https://gcc.gnu.org/>`__ on `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`__, and `Clang <https://clang.llvm.org/>`__ on `macOS <https://en.wikipedia.org/wiki/MacOS>`__.
We recommend using these compilers on these systems, but feel free to use a different toolchain.
We sometimes use the `Intel C++ compiler <https://software.intel.com/en-us/c-compilers>`__ to build libCellML, but we do not (at the time of writing) test with it.

The following sub-sections provide guidance on how to install the recommended toolchain on the major operating systems that libCellML supports.

Windows
+++++++

Visual Studio is available to download from `here <https://visualstudio.microsoft.com/downloads/>`__.
We currently test with Visual Studio 2015 (version 14), but later versions are known to work.
The *Community* edition is more than sufficient for the needs of libCellML.
To minimize the size of the installation, you may install only the C++ compiler.
This component (and its requirements) is sufficient for building libCellML.

Linux
+++++
(todo)

MacOS
+++++
(todo)


.. _devsetup_libxml2:

LibXml2
-------

`LibXml2 <http://xmlsoft.org/>`__ is a parser and toolkit for manipulating XML files and text.  
It's important to use a 64-bit version of the library as the 32-bit is not compatible with libCellML.  

LibXML2 is already installed on `macOS <https://en.wikipedia.org/wiki/MacOS>`__, so no further action is required on that platform.  

On `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`__, it's easiest to install using the packaged version available from `the OpenCMISS site <https://github.com/OpenCMISS-Dependencies/libxml2/releases>`__.
You're welcome to build your own version if you'd rather, but please make sure it's a 64-bit implementation.  
Source code for building it yourself can be downloaded from the `LibXml2 <http://xmlsoft.org/>`__ site.

On `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`__ LibXml2 can be installed using ``sudo apt install libxml2-dev``.


.. _devsetup_doxygen:

Doxygen
-------

`Doxygen <http://www.doxygen.nl/>`__ is software which assembles documentation files directly from annotated source code, including the generation of inheritance and dependency tree diagrams for classes.  
In order for libCellML to build its documentation you will need to have Doxygen and its dependencies installed.  
Note that this does not affect your use of the libCellML library itself. 

Binary distributions for Linux, Windows, and MacOS are available from the `download page of the Doxygen website <http://www.doxygen.nl/download.html#srcbin>`__, and source code is available there too.

On Windows you may also need to download and install the Graphviz package in order to generate the class heirarchy diagrams.  You can `download Graphviz <http://graphviz.org/download/>`__ from their website.


.. _devsetup_python:

Python (optional)
-----------------
`Python <https://www.python.org/>`__ is an open-source language which is syntactically easier to read than other higher-level languages.  
It is commonly used as a scripting language for experimentation, and is included here to allow libCellML to be accessed from Python-based programs.  
Note that creation of Python bindings is optional, and can be enabled/disabled at configuration time - there will be instructions for this on the :doc:`Building LibCellML <dev_building>` page.

On MacOS, Python `is already installed <https://legacy.python.org/getit/mac/>`__, though depending on the age of your machine you may like to upgrade it to a `later version from the Python site <https://www.python.org/downloads/mac-osx/>`__.

Linux also natively includes Python, but again depending on the age of your machine and system installation, you may like to upgrade to a more recent version from the `Python download page <https://www.python.org/downloads/source/>`__.    

Python binaries for Windows can be found on `the Python download page <https://www.python.org/downloads/windows/>`__, or you can build your own from source files if you prefer. 


.. _devsetup_swig:

SWIG for Python bindings (optional)
-----------------------------------

`SWIG <http://www.swig.org/>`__ is a tool which acts as a translator between code written in C++ and other languages, including `Python <https://www.python.org/>`__.  
Here SWIG is used to generate the optional Python bindings for libCellML.  
The current version (0.9) of libCellML uses SWIG 4.0.0. 

SWIG for MacOS can be accessed using the `downloads for Unix/Linux sources <http://www.swig.org/download.html>`__ and building it locally according to the instructions provided on that page.
  
SWIG for Windows is available from the `Swigwin download link <https://sourceforge.net/projects/swig/files/swigwin/>`__.
  
On Linux systems both Python and SWIG are already included, so no further action is needed.  


.. _devsetup_sphinx:

Sphinx for Python documentation (optional)
------------------------------------------

`Sphinx <http://www.sphinx-doc.org/en/master/>`__ is an additional documentation tool used here to assemble documentation of the Python bindings.  
Instructions for all operating systems can be found on their `Installation page <http://www.sphinx-doc.org/en/master/usage/installation.html>`__.
The current version (2.0.1) needs Python version 3.5.2 or later (note that Python subversions 3.5.0 and 3.5.1 will still raise an `import error <https://github.com/rtfd/readthedocs.org/issues/3812>`__ despite being reported fixed since version Sphinx 1.7.2).  


.. _devsetup_codebase:

Setting up the codebase
=======================

The remainder of this document assumes that the above pre-requisites have been met.
It covers setup from the command line.
If you are using a `GUI <https://en.wikipedia.org/wiki/Graphical_user_interface>`__ like `GitHub Desktop <https://desktop.github.com/>`__ then you will need to adjust the commands for the `GUI <https://en.wikipedia.org/wiki/Graphical_user_interface>`__ you are using.

The goal here is to get a working copy of source code, tests, and documentation onto your computer so that you can begin development.
To make this happen, you will need to fork the :term:`prime libCellML repository`, make a clone onto your computer, and set up the `Git <https://git-scm.com/>`__ remotes.
In :numref:`fig_devSetup_githubRepos`, you can see a pictorial representation of what we are aiming to achieve.

.. _fig_devSetup_githubRepos:

.. figure:: ../images/libCellMLProcesses-GitHubRepos.png
   :align: center
   :alt: Setup of Git repositories.

   Setup of repositories for development.

The four steps to getting set up are detailed below.

Forking your own copy
---------------------

Login to `GitHub <https://github.com/>`__ using your credentials and go to https://github.com/cellml/libCellML.

Use the fork button to create a libCellML repository under your own account, see :numref:`fig_devSetup_githubFork` for locating this button.

.. _fig_devSetup_githubFork:

.. figure:: ../images/libCellMLProcesses-GitHubForkButton.png
   :align: center
   :alt: Fork button of libCellML repository.

   Fork button for libCellML repository.

Clone
-----

You now need to clone the libCellML repository to your computer.
You do this by going to your fork (in this example user *andre*'s fork) at https://github.com/andre/libCellML.

.. warning::

   Do not try and clone this location substitute your `GitHub <https://github.com/>`__ username for *andre*.
   In all likelihood, it does not exist.

On the right hand side of the webpage, on your fork of the repository, you can get the link for cloning the repository to your computer, in our example::

  https://github.com/andre/libCellML.git

Now clone the repository::

  cd <somewhere/you/keep/development/code>
  git clone https://github.com/andre/libCellML.git

Note: again, do not clone this location; substitute your `GitHub <https://github.com/>`__ username for *andre*.

Set Git remotes
---------------

You now need to setup a read-only remote connection to the :term:`prime libCellML repository`.
Given that you are still in the directory where you cloned the libCellML repository from, do the following::

  cd libCellML
  git remote add prime https://github.com/cellml/libCellML.git
  git config remote.prime.pushurl "You really did not want to do that!"

You have now added a new remote named ``prime`` and set origin as the default fetch and push location to point at repositories under your control on `GitHub <https://github.com/>`__.
Here, ``prime`` is a reference to the main definitive repository where releases are made from for the libCellML project.
You have also set the ``prime`` repository as read-only by setting an invalid push URL.

Finally
=======

You are all done and ready to start development, read :doc:`Building <dev_building>` on how to build libCellML.
Then, read :doc:`Contribution <dev_contribution>` to get your changes into libCellML's prime repository.
