.. _libcellmlRoadmap:

=======
Roadmap
=======

David Nickerson, 9 June 2014.

Contributions from Alan Garny, Jonathan Cooper, Mike Cooling, Tommy Yu, Hugh Sorby, Randall Britten and the CellML Community but no time yet for full consensus.

These requirements and milestones are derived from the `CellML API May 2014 Requirements <https://docs.google.com/document/d/1qMpltGGk19RgFAgkgnG8xZVKyI0Q-ZatcxV7VB_ccKc/edit>`_
collected from the CellML community, with input from the primary target users (application
developers) and the CellML Editorial Board. Previous editorial board discussions have also been
incorporated into this roadmap.

Clearly the milestones defined below are to be worked on in numerical order and previous milestones will be completed before work on subsequent milestones begins. Each milestone may consist of several 'releases' and future requirements may impact the design and implementation of earlier releases of libCellML. Major changes in the API will be accepted up to the release of libCellML version 1.0.0.

.. contents::

High level objectives
=====================

* Focus on CellML 1.2 and beyond.

  * The implementation of libCellML should be driven by the requirements for supporting CellML 1.2 and beyond.
  * Implementing support for core+secondary specifications is likely to be a big challenge for libCellML.

    * libCellML should be designed to support the core specification with the flexibility for extra restrictions/constraints coming from the secondary specifications.
    * Multiple secondary specifications could be used in one model.
    * Secondary specifications may exist for a period of time before they are integrated or consolidated into a new version of CellML (if at all, there is still a lot to learn about how secondary specifications will evolve).

  * libCellML should always be able to import earlier CellML version models.
  * To begin with, libCellML must be able to export CellML 1.2 models to CellML 1.1 (probably using API marked as deprecated from the beginning and removed once Milestone 3 is achieved).

* Develop the libCellML API as work progresses through the milestones outlined below.

Environment
===========

This section will specify the environment for the development of libCellML.

* `GitHub <https://github.com/>`_ to host the primary libCellML source repository and issue tracker under the `CellML organisation <https://github.com/cellml>`_ (current and former editorial board members).
* Development language: C++ with `SWIG <http://www.swig.org/>`_ bindings.
* Build: `CMake <http://www.cmake.org/>`_ for generating cross-platform build rules.
* Test: using `Buildbot <http://buildbot.net/>`_ on the BaTS to run continuous integration testing.
* Test: unit testing to use `gtest <https://code.google.com/p/googletest/>`_.
* Documentation: written in `reStructuredText <http://docutils.sourceforge.net/docs/ref/rst/restructuredtext.html>`_.
* Documentation: API and source code examples will be documented using c++-style `doxygen <http://www.doxygen.org/>`_ comments.

Requirements
------------

* Documentation: made available on `readthedocs.io <https://readthedocs.io/>`_. Read the Docs uses `Sphinx <http://sphinx-doc.org/>`_ for generating documentation.
* Documentation: Is amenable for inclusion in external documentation efforts
* Development: Agile, test driven development where:

  * Functionality is more important than API stability in early releases.
  * Release early and often.

* Development: code review prior to acceptance into the primary repository using the `pull request <https://help.github.com/articles/using-pull-requests>`_ feature on `GitHub <https://github.com/>`_.
* Development: objectives are added and broken down into incremental tasks.
* Development: a single task should be no more than two weeks.
* Development: the next objective to be worked on is discussed and agreed with the community before work is started on an objective.

We should avoid using non-standard system libraries unless there is a compelling reason. Once features are available, the API can be fine tuned in consultation with the CellML community.

Milestone 0: setting up development environment
===============================================

#. Share an `UML <http://www.uml.org/>`_-esque document with the community via `GitHub <https://github.com/>`_ describing a CellML specific object model.

   #. The form of the API to libCellML should not be dictated by the XML serialisation but by the objects tool developers desire to work with
   #. Respond to feedback

#. Setup the cross platform build and test environment using the ABI's build and test server (BaTS).

   #. Builds required: Windows 64 bit, OS X 10.9, Ubuntu 14.04 64 bit
   #. Using Buildbot for CI framework
   #. Interact with GitHub to process changes
   #. Make Buildbot status available from autotest.bioeng.auckland.ac.nz/libcellml-buildbot/

#. Document the development process/workflow.

   #. Code contribution document
   #. Developer setup document
   #. Code review document

Milestone 1: starting to get useful code (timeframe: ? months)
==============================================================

#. Create a CellML 1.2 model from scratch and save it to XML

   #. Create a new model, add imports, components, variables, units and mathematics.
   #. The first test case?

#. Load a CellML 1.2 model, make changes to it and save it.

   #. Ability to preserve the underlying XML structure/ordering for documents read in and written out.

#. Load a CellML 1.2 model and validate it.

   #. This is important to get out early as it will help make sure the normative specification is “complete” and sensible.
   #. It will ensure that we can test models as we work on getting the specification completed (c.f. the error ridden examples from the CellML 1.0 and 1.1 specifications).
   #. It must include proper units validation of the mathematics.
   #. libCellML should have a validation framework based on the core specification and then secondary specifications can add their specific rules.
   #. For CellML 1.2, this is mainly the mathematics, so the core validation can probably validate a model, but it needs the actual restricted subset of MathML from the secondary specifications to fully validate units consistency.

#. Import CellML 1.0/1.1 models.
#. Export to CellML 1.1 (and, by extension, CellML 1.0), so that we can still use existing tools (e.g., simulation, annotation, NeSI), preserving model and XML structure/ordering/modularity where possible.
#. Platform support: Windows, Linux and OS X.

   #. Native installers (using CPack, pip).
   #. Easy to setup build environment (good documentation).

#. Language support: C++, Python, Java, MATLAB.
#. Documentation available.

   #. API.
   #. Tutorials/documented code examples.
   #. Integrating libCellML into various common IDEs (Visual Studio, Eclipse, Qt Creator, NetBeans...).

Milestone 2: toward simulation support (timeframe: ? months)
============================================================

#. Conversion to intermediate representation.

   #. Conversion to CellML structureless mathematics (i.e. just the mathematics, but with units information) into an intermediate representation that can be transformed / analysed by other tools.
   #. Ability to maintain the CellML structure (as much as possible), perhaps via object annotation (e.g., COR).
   #. Will form the basis for tools using libCellML to perform numerical simulation.

#. Improved support for model authoring/editing/manipulation.

   #. Provide an events system to monitor changes in the model.
   #. Provide access to data contained in CellML models in external namespaces (RDF, extensions, etc.).

#. Documentation, documentation and more documentation!

Milestone 3: functional library for tool developers (timeframe: ? months)
=========================================================================

#. Establish the process/API required to generate procedural code from the intermediate representation.

   #. Generic code vs solver specific code.
   #. Could be a role for being informed from `SED-ML <http://sed-ml.org/>`_ what solver is to be used and customising the generated code appropriately.
   #. It would be a tool sitting on top of libCellML, not directly part of it.

#. Being able to run simulations with CellML 1.2.

   #. While not directly part of libCellML, helping tool developers get to the point where they can execute simulations is critically important.
   #. CellML 1.2 will not be released until we can do this (in addition to the other requirements above).

Milestone 4: advanced capabilities (timeframe: ? months)
========================================================

#. High-order model manipulation (recall the discussion with Andrew McCulloch at the 8th CellML workshop).

   #. Again, it is outside the scope of libCellML, but helping tool developers provide these kinds of services is very important.

Milestone 5: broadening accessibility (timeframe: ? months)
===========================================================

#. Support for more platforms.

   #. Android, iOS.

#. And languages.

   #. JS, C#/.NET, C, Fortran[77|90|20XX].

