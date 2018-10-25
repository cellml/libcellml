.. Developer Setup for libCellML

=================
Development Setup
=================

This section describes how someone wanting to contribute to the libCellML project should set up their *working copy* for developing libCellML.

.. contents::

Overview
========

The libCellML codebase is hosted on GitHub and therefore Git is used to track changes. Before you begin, you will need to have a few pre-requisites satisfied:

#. GitHub user account (for the rest of this document we will call our user *andre*).
#. Git.
#. CMake.
#. Toolchain for building software (dependent on the operating system).
#. libXml2.

Pre-requisite acquisition
=========================

In this section, we cover the retrieval and installation of pre-requisites.

Git
---

Creating a GitHub user account is straightforward and can be done `here <https://github.com/join>`__.  Installing a *Git* client is particular to each operating system and some pointers are offered below:

* macOS *Git* is pre-installed and available from the command line.
* Ubuntu (and other linux distributions) *Git* can be installed using the package manager with the command :code:`sudo apt-get install git`.
* Windows *Git* is available from a variety of vendors.  We commonly use `Git for windows <http://gitforwindows.org/>`_, but other popular *Git* implementations are:

  - `GitHub Desktop <https://desktop.github.com/>`_
  - `GitKracken <https://www.gitkraken.com/>`_
  - `Git SCM <https://git-scm.com/>`_

CMake
-----

*CMake* is the cross-platform family of tools designed to build, test and package software.  *CMake* is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.

Again, installation of *CMake* is particular to each operating system.  For Ubuntu (and other linux distributions), *CMake* can be installed using the package manager with the command :code:`sudo apt-get install cmake`.  For macOS and Windows, *CMake* provides installation binaries from `here <https://cmake.org/download/>`__.  Choose the binary appropriate for your operating system and follow the installation instructions.

Toolchain
---------

The toolchain specifies the compiler that we will use to build *libCellML*, toolchains are highly dependent on the operating system.  When we test *libCellML*, we currently use *Microsoft Visual Studio Compilers* on Windows, the *GNU* family of compilers on Ubuntu, and the *clang* family of compilers on macOS.  We recommend using these compilers on these systems, but feel free to use a different toolchain.  We often use *intel* compilers to build *libCellML* but we don't (at the time of writing) test with them.

The following sub-sections provide guidance on how to install the recommended toolchain on the major operating systems that *libCellML* supports.

Windows
+++++++

*Microsoft Visual Studio* is available to download from `here <https://www.visualstudio.com/downloads/>`__.  We currently test with version 14 of this software but later versions are known to work.  The *community edition* is more than sufficient for the needs of *libCellML*.  To minimize the size of the installation you may install only the C++ compiler, this component (and its requirements) is sufficient for building the *libCellML* library.

LibXml2
-------

LibXml2 is already available on Ubuntu and macOS so no further action is required.  However, on Windows we must install LibXml2 ourselves.  The recommended implementation of LibXml2 for use with libCellML is available from `here <https://github.com/OpenCMISS-Dependencies/libxml2/releases>`__.

Python bindings
---------------
Optional Python bindings are provided using SWIG. To compile the bindings, a SWIG installation is required, as well as a Python 2 or Python 3 installation (including the development packages on linux systems, e.g. ``python-dev``). Creation of Python bindings can be enabled/disabled using ``ccmake``.

Setting up the codebase
=======================

The remainder of this document assumes that the above pre-requisites have been met.  It covers setup from the command line.  If you are using a GUI like 'GitHub for Windows' then you will need to adjust the commands for the GUI you are using.

The goal here is to get a working copy of source code, tests, and documentation onto your computer so that you can begin development.  To make this happen you will need to fork the :term:`prime libCellML repository`, make a clone onto your computer, and set up the Git remotes.  In :numref:`fig_devSetup_githubRepos` you can see a pictorial representation of what we are aiming to achieve.

.. _fig_devSetup_githubRepos:

.. figure:: images/libCellMLProcesses-GitHubRepos.png
   :align: center
   :alt: Setup of Git repositories

   Setup of repositories for development

The four steps to getting set up are detailed below.

Forking your own copy
---------------------

Login to GitHub using your credentials and go to::

   https://github.com/cellml/libcellml

Use the fork button to create a libcellml repository under your own account, see :numref:`fig_devSetup_githubFork` for locating this button.

.. _fig_devSetup_githubFork:

.. figure:: images/libCellMLProcesses-GitHubForkButton.png
   :align: center
   :alt: Fork button of libCellML repository

   Fork button for libCellML repository

Clone
-----

You now need to clone the libCellML repository to your computer.  You do this by going to your fork (in this example user *andre*'s fork) at::

   https://github.com/andre/libcellml

.. warning::

   Don't try and clone this location substitute your GitHub username for *andre*.  In all likelihood it doesn't exist.

On the right hand side of the webpage on your fork of the repository you can get the link for cloning the repository to your PC, in our example::

        git@github.com:andre/libcellml.git

Now clone the repository::

        cd <somewhere/you/keep/development/code>
        git clone git@github.com:andre/libcellml.git

Note: again, don't clone this location substitute your username for *andre*.

Set Git remotes
---------------

You now need to setup a read-only remote connection to the prime repository.  Given that you are still in the directory where you cloned the libCellML repository from do the following::

   cd libcellml
   git remote add prime git@github.com:cellml/libcellml.git
   git config remote.prime.pushurl "you really didn't want to do that"

You have now added a new remote named **prime** and set origin as the default fetch and push location to point at repositories under your control on GitHub.  Here **prime** is a reference to the main definitive repository where releases are made from for the libCellML project.  You have also set the **prime** repository as read-only by setting an invalid push url.

Finally
=======

You are all done and ready to start development, read :doc:`Building <dev_building>` on how to build libCellML then read :doc:`Contribution <dev_contribution>` to get your changes into libCellML's prime repository.


