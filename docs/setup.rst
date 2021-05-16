.. _setup:

=================
Development setup
=================

This section describes how someone wanting to contribute to the libCellML project should set up their *working copy* for developing libCellML.

Overview
========

The libCellML codebase is hosted on :github:`Github<>` and therefore :git:`Git<>` is used to track changes. Before you begin, you will need to have a few pre-requisites satisfied:

.. container:: shortlist

  1. :github:`Github<>` user account (for the rest of this document we will call our user *andre*);
  #. :git:`Git<>` for tracking changes in code;
  #. :cmake:`CMake<>` to configure the build files;
  #. Toolchain for building the library (dependent on the operating system);
  #. :libxml2:`LibXml2<>`, an external library used to parse XML; and
  #. :doxygen:`Doxygen<>` to generate documentation.

If Python bindings are required, the following packages are also needed:

.. container:: shortlist

  a. :python:`Python<>` Version 3.5.2 or later is needed for Sphinx (see below)
  #. :swig:`SWIG<>` to generate the bindings for Python
  #. :sphinx:`Sphinx<>` to generate documentation for Python bindings


Pre-requisite acquisition
=========================

In this section, we cover the retrieval and installation of pre-requisites.

.. _setup_git:

Git
---

Creating a :github:`Github<>` user account is straightforward and can be done on the :github:`Github sign-up page</join>`.
Installing a Git client is particular to each operating system and some pointers are offered below:

- **Windows** Git is available from a variety of vendors.
  We commonly use `Git for windows <http://gitforwindows.org/>`__, but other popular implementations are:
  - `GitHub Desktop <https://desktop.github.com/>`__
  - `GitKracken <https://www.gitkraken.com/>`__
  - `Git SCM <https://git-scm.com/>`__

- **Linux** Git can be installed using the package manager with the command :code:`sudo apt-get install git`.
- **macOS** Git is pre-installed and available from the command line.


.. _setup_cmake:

CMake
-----

:cmake:`CMake<>` is the cross-platform family of tools designed to build, test and package software.
CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and to generate native makefiles and workspaces that can be used in the compiler environment of your choice.
Note that CMake version 3.2 or later is required to configure libCellML.

Again, installation of CMake is particular to each operating system.

- **Windows** CMake provides :cmake:`installation binaries</download/>` .
  Choose the binary appropriate for your operating system and follow the installation instructions.
- **Linux** CMake can be installed using the package manager with the command :code:`sudo apt-get install cmake`.
- **macOS** CMake provides :cmake:`installation binaries</download/>` .
  Choose the binary appropriate for your operating system and follow the installation instructions.


.. _setup_toolchain:

Toolchain
---------

The toolchain specifies the compiler that we will use to build libCellML.
Toolchains are highly dependent on the operating system.
When we test libCellML, we currently use:

- **Windows** :msvs:`Microsoft Visual Studio<>` ;
- **Linux** :gcc:`GCC<>` ; and
- **macOS** :clang:`Clang<>` .

We recommend using these compilers on these systems, but feel free to use a different toolchain.
The following sub-sections provide guidance on how to install the recommended toolchain on the major operating systems that libCellML supports.

- **Windows** Visual Studio is available to download from :msvs:`the MSVS download page</downloads/>`.
  We currently test with Visual Studio 2015 (version 14), but later versions are known to work.
  The *Community* edition is more than sufficient for the needs of libCellML.
  To minimise the size of the installation, you may install only the C++ compiler.
  This component (and its requirements) is sufficient for building libCellML.
- **Linux** TODO
- **macOS** TODO

.. _setup_libxml2:

LibXml2
-------
:libxml2:`LibXml2<>` is a parser and toolkit for manipulating XML files and text.
It's important to use a 64-bit version of the library as the 32-bit is not compatible with libCellML.

- **Windows** On Windows, it's easiest to install using the packaged version available from :opencmiss_repo:`the OpenCMISS site<>` .
  You're welcome to build your own version if you'd rather, but please make sure it's a 64-bit implementation.
  Source code for building it yourself can be downloaded from the :libxml2:`LibXml2<>` site.
- **Linux** LibXml2 can be installed using :code:`sudo apt install libxml2-dev`.
- **macOS** LibXML2 is already installed on macOS, so no further action is required on that platform.

.. _setup_doxygen:

Doxygen
-------
:doxygen:`Doxygen<>` is software which assembles documentation files directly from annotated source code, including the generation of inheritance and dependency tree diagrams for classes.
In order for libCellML to build its documentation you will need to have Doxygen and its dependencies installed.
Note that this does not affect your use of the libCellML library itself.

- **Windows** Binary distributions are available from the :doxygen:`download page of the Doxygen website </download.html#srcbin>`.
  You may also need to download and install the Graphviz package in order to generate the class hierarchy diagrams.
  You can :graphviz:`download Graphviz</download/>` from their website.
- **Linux** Binary distributions are available from the :doxygen:`download page of the Doxygen website </download.html#srcbin>`.
- **macOS** Binary distributions are available from the :doxygen:`download page of the Doxygen website </download.html#srcbin>`.


.. _setup_python:

Python (optional)
-----------------
:python:`Python<>` is an open-source language which is syntactically easier to read than other higher-level languages.
It is commonly used as a scripting language for experimentation, and is included here to allow libCellML to be accessed from Python-based programs.
Note that creation of Python bindings is optional, and can be enabled/disabled at configuration time - there will be instructions for this on the :ref:`Building LibCellML <configure_and_build>` page.

- **Windows** Python binaries for Windows can be found on :python:`the Python download page</downloads/windows/>`, or you can build your own from source files if you prefer.

- **Linux** Linux natively includes Python, but depending on the age of your machine and system installation, you may like to upgrade to a more recent version from the :python:`Python download page</downloads/source/>` .

- **macOS** Python is already installed, though depending on the age of your machine you may like to upgrade it to a :python:`later version from the Python site<downloads/mac-osx/>` .

.. _setup_swig:

SWIG for Python bindings (optional)
-----------------------------------
:swig:`SWIG<>` is a tool which acts as a translator between code written in C++ and other languages, including :python:`Python<>`.
Here SWIG is used to generate the optional Python bindings for libCellML.
The current version (0.9) of libCellML uses SWIG 4.0.0.

- **Windows** SWIG for Windows is available from the :swigwin_download:`Swigwin download page<>`.

- **Linux** Both Python and SWIG are already included, so no further action is needed.

- **macOS** SWIG for macOS can be accessed using the :swig:`downloads for Unix/Linux sources</download.html>` and building them locally according to the instructions provided on that page.

.. _setup_sphinx:

Sphinx for Python documentation (optional)
------------------------------------------
:sphinx:`Sphinx<>` is an additional documentation tool used here to assemble documentation of the Python bindings.
Instructions for all operating systems can be found on their :sphinx:`Installation page</usage/installation.html>`.
The current version (2.0.1) needs Python version 3.5.2 or later (note that Python subversions 3.5.0 and 3.5.1 will still raise an :github_rtd:`import error</3812>` despite being reported fixed since version Sphinx 1.7.2).


.. _setup_codebase:

Setting up the codebase
=======================
The remainder of this document assumes that the above pre-requisites have been met, and covers setup from the command line.
If you are using a GUI like :github_desktop:`GitHub Desktop<>` then you will need to adjust the commands accordingly.

The goal here is to get a working copy of source code, tests, and documentation onto your computer so that you can begin development.
To make this happen, you will need to fork the :term:`prime libCellML repository`, make a clone onto your computer, and set up the Git remotes.
In :numref:`repository_setup`, you can see a pictorial representation of what we are aiming to achieve.

.. figure:: ./images/libCellMLProcesses-GitHubRepos.png
   :align: center
   :alt: Setup of Git repositories.
   :name: repository_setup

   How the repositories for development are arranged.

The four steps to getting set up are detailed below.

Forking your own copy
---------------------
Login to Github using your credentials and go to https://github.com/cellml/libCellML.

Use the fork button to create a libCellML repository under your own account, see :numref:`forking_a_repo` for locating this button.

.. figure:: ./images/libCellMLProcesses-GitHubForkButton.png
   :align: center
   :alt: Fork button of libCellML repository.
   :name: forking_a_repo

   Fork button for libCellML repository.

Clone
-----
You now need to clone the libCellML repository to your computer.
You do this by going to your fork (in this example user *andre*'s fork) at https://github.com/andre/libCellML.

.. container:: nb

   Do not try and clone this location!
   Substitute your Github username for *andre*.

On the right hand side of the webpage, on your fork of the repository, you can get the link for cloning the repository to your computer, in our example::

  https://github.com/andre/libCellML.git

Now clone the repository::

  cd <somewhere/you/keep/development/code>
  git clone https://github.com/andre/libCellML.git

Note: again, do not clone this location; substitute your Github username for *andre*.

Set Git remotes
---------------
You now need to setup a read-only remote connection to the :term:`prime libCellML repository`.
Given that you are still in the directory where you cloned the libCellML repository from, do the following::

  cd libCellML
  git remote add prime https://github.com/cellml/libCellML.git
  git config remote.prime.pushurl "You really did not want to do that!"

You have now added a new remote named :code:`prime` and set origin as the default fetch and push location to point at repositories under your control on Github.
Here, :code:`prime` is a reference to the main definitive repository where releases are made from for the libCellML project.
You have also set the :code:`prime` repository as read-only by setting an invalid push URL.

Finally
=======
You are all done and ready to start development, read :ref:`Building <configure_and_build>` on how to build libCellML.
Then, read :ref:`Contribution <contributing>` to get your changes into libCellML's prime repository.
