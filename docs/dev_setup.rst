.. Developer Setup for libCellML

=================
Development Setup
=================

This section describes how someone wanting to contribute to the libCellML project should set up their *working copy* for developing libCellML.

.. contents::

Overview
========

The libCellML codebase is hosted on `GitHub <https://github.com/>`_ and therefore `Git <https://git-scm.com/>`_ is used to track changes. Before you begin, you will need to have a few pre-requisites satisfied:

1. `GitHub <https://github.com/>`_ user account (for the rest of this document we will call our user *andre*).
#. `Git <https://git-scm.com/>`_.
#. `CMake <https://cmake.org/>`_.
#. Toolchain for building software (dependent on the operating system).
#. `LibXml2 <http://xmlsoft.org/>`_.

Pre-requisite acquisition
=========================

In this section, we cover the retrieval and installation of pre-requisites.

Git
---

Creating a `GitHub <https://github.com/>`_ user account is straightforward and can be done `here <https://github.com/join>`_.
Installing a `Git <https://git-scm.com/>`_ client is particular to each operating system and some pointers are offered below:

* `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`_ `Git <https://git-scm.com/>`_ is available from a variety of vendors.
We commonly use `Git for windows <http://gitforwindows.org/>`_, but other popular `Git <https://git-scm.com/>`_ implementations are:

  - `GitHub Desktop <https://desktop.github.com/>`_
  - `GitKracken <https://www.gitkraken.com/>`_
  - `Git SCM <https://git-scm.com/>`_

* `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`_ (and other `Linux <https://en.wikipedia.org/wiki/Linux>`_ distributions) `Git <https://git-scm.com/>`_ can be installed using the package manager with the command ``sudo apt install git``.
* `macOS <https://en.wikipedia.org/wiki/MacOS>`_ `Git <https://git-scm.com/>`_ is pre-installed and available from the command line.

CMake
-----

`CMake <https://cmake.org/>`_ is the cross-platform family of tools designed to build, test and package software.
`CMake <https://cmake.org/>`_ is used to control the software compilation process using simple platform and compiler independent configuration files, and to generate native makefiles and workspaces that can be used in the compiler environment of your choice.

Again, installation of `CMake <https://cmake.org/>`_ is particular to each operating system.
For `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`_ (and other `Linux <https://en.wikipedia.org/wiki/Linux>`_ distributions), `CMake <https://cmake.org/>`_ can be installed using the package manager with the command ``sudo apt install cmake``.
For `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`_ and `macOS <https://en.wikipedia.org/wiki/MacOS>`_, `CMake <https://cmake.org/>`_ provides `installation binaries <https://cmake.org/download/>`_.
Choose the binary appropriate for your operating system and follow the installation instructions.

Toolchain
---------

The toolchain specifies the compiler that we will use to build libCellML.
Toolchains are highly dependent on the operating system.
When we test libCellML, we currently use `Visual Studio <https://visualstudio.microsoft.com/downloads/>`_ on `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`_, `GCC <https://gcc.gnu.org/>`_ on `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`_, and `Clang <https://clang.llvm.org/>`_ on `macOS <https://en.wikipedia.org/wiki/MacOS>`_.
We recommend using these compilers on these systems, but feel free to use a different toolchain.
We sometimes use the `Intel C++ compiler <https://software.intel.com/en-us/c-compilers>`_ to build libCellML, but we do not (at the time of writing) test with it.

The following sub-sections provide guidance on how to install the recommended toolchain on the major operating systems that libCellML supports.

Windows
+++++++

Visual Studio is available to download from `here <https://visualstudio.microsoft.com/downloads/>`_.
We currently test with Visual Studio 2015 (version 14), but later versions are known to work.
The *Community* edition is more than sufficient for the needs of libCellML.
To minimize the size of the installation, you may install only the C++ compiler.
This component (and its requirements) is sufficient for building libCellML.

LibXml2
-------

`LibXml2 <http://xmlsoft.org/>`_ is already installed on `macOS <https://en.wikipedia.org/wiki/MacOS>`_, so no further action is required on that platform.
On `Windows <https://en.wikipedia.org/wiki/Microsoft_Windows>`_, we must install `LibXml2 <http://xmlsoft.org/>`_ using the recommended implementation available from `here <https://github.com/OpenCMISS-Dependencies/libxml2/releases>`_ while on `Ubuntu <https://en.wikipedia.org/wiki/Ubuntu>`_ `LibXml2 <http://xmlsoft.org/>`_ can be installed using ``sudo apt install libxml2-dev``.

Python bindings
---------------

Optional Python bindings are provided using `SWIG <http://www.swig.org/>`_.
To compile the bindings, a `SWIG <http://www.swig.org/>`_ installation is required, as well as a Python 2 or Python 3 installation (including the development packages on `Linux <https://en.wikipedia.org/wiki/Linux>`_ systems, e.g. ``python-dev``).
Creation of Python bindings can be enabled/disabled at configuration time.

Setting up the codebase
=======================

The remainder of this document assumes that the above pre-requisites have been met.
It covers setup from the command line.
If you are using a `GUI <https://en.wikipedia.org/wiki/Graphical_user_interface>`_ like `GitHub Desktop <https://desktop.github.com/>`_ then you will need to adjust the commands for the `GUI <https://en.wikipedia.org/wiki/Graphical_user_interface>`_ you are using.

The goal here is to get a working copy of source code, tests, and documentation onto your computer so that you can begin development.
To make this happen, you will need to fork the :term:`prime libCellML repository`, make a clone onto your computer, and set up the `Git <https://git-scm.com/>`_ remotes.
In :numref:`fig_devSetup_githubRepos`, you can see a pictorial representation of what we are aiming to achieve.

.. _fig_devSetup_githubRepos:

.. figure:: images/libCellMLProcesses-GitHubRepos.png
   :align: center
   :alt: Setup of Git repositories.

   Setup of repositories for development.

The four steps to getting set up are detailed below.

Forking your own copy
---------------------

Login to `GitHub <https://github.com/>`_ using your credentials and go to https://github.com/cellml/libcellml.

Use the fork button to create a libcellml repository under your own account, see :numref:`fig_devSetup_githubFork` for locating this button.

.. _fig_devSetup_githubFork:

.. figure:: images/libCellMLProcesses-GitHubForkButton.png
   :align: center
   :alt: Fork button of libCellML repository.

   Fork button for libCellML repository.

Clone
-----

You now need to clone the libCellML repository to your computer.
You do this by going to your fork (in this example user *andre*'s fork) at https://github.com/andre/libcellml.

.. warning::

   Do not try and clone this location substitute your `GitHub <https://github.com/>`_ username for *andre*.
   In all likelihood, it does not exist.

On the right hand side of the webpage, on your fork of the repository, you can get the link for cloning the repository to your computer, in our example::

  https://github.com/andre/libcellml.git

Now clone the repository::

  cd <somewhere/you/keep/development/code>
  git clone https://github.com/andre/libcellml.git

Note: again, do not clone this location substitute your `GitHub <https://github.com/>`_ username for *andre*.

Set Git remotes
---------------

You now need to setup a read-only remote connection to the :term:`prime libCellML repository`.
Given that you are still in the directory where you cloned the libCellML repository from, do the following::

  cd libcellml
  git remote add prime https://github.com/cellml/libcellml.git
  git config remote.prime.pushurl "You really did not want to do that!"

You have now added a new remote named ``prime`` and set origin as the default fetch and push location to point at repositories under your control on `GitHub <https://github.com/>`_.
Here, ``prime`` is a reference to the main definitive repository where releases are made from for the libCellML project.
You have also set the ``prime`` repository as read-only by setting an invalid push URL.

Finally
=======

You are all done and ready to start development, read :doc:`Building <dev_building>` on how to build libCellML.
Then, read :doc:`Contribution <dev_contribution>` to get your changes into libCellML's prime repository.
