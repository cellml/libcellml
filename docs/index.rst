.. _main_index:

=======================
libCellML Documentation
=======================

Welcome to the documentation for libCellML, including user tutorials,
developer guidelines, installation information and the formal language
specification.

The purpose of libCellML is to create, manipulate, serialise, deserialise,
validate and instantiate :cellml2:`CellML2 <>` models.
In the first instance, all serialising and deserialising will be to and from
standard strings and using the CellML2.0 specification.

The library is intended to be lightweight and focused purely in dealing with
:cellml2:`CellML <>` models.  In achieving this, some of the
convenience methods/objects that we might expect will not be part of libCellML.
For example, in our current thoughts, libCellML would not be concerned with the
actual mechanics of resolving and retrieving external resources - calling
applications would be required to resolve and retrieve import URLs and provide
the serialised documents to libCellML in the form of strings for instantiation
as part of the CellML hierarchical model description.

Installation and system requirements
------------------------------------
How and where you install libCellML will depend a little on who you are and
how you want to use it.

* For a quickstart setup of libCellML for users already familiar with the
  CellML format, please follow the Quickstart guide.

* For users who are new to CellML, please see the step-by-step instructions
  which begin with :ref:`Tutorial 0: Installation and testing<tutorial0>`.

* For developers who want to contribute or build libCellML from source,
  please start with the :ref:`Setup for Developers<dev_setup>` page in the
  :ref:`Documentation for developers<index_development>` section.


Tutorials for users
-------------------

.. toctree::
   :maxdepth: 2
   :titlesonly:

   tutorials/tutorials_index
   theory/theory_index

CellML2 format specification
----------------------------

.. toctree::
    :maxdepth: 2
    :titlesonly:

    specification/specification_index

Documentation for developers
----------------------------

.. toctree::
   :maxdepth: 2
   :titlesonly:

   developer_docs/index_development

External references
----------------------------
.. toctree::
   :maxdepth: 1
   :titlesonly:

   references

Indices and tables
----------------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

Supported by:
==============

.. figure:: developer_docs/images/vpr.png
   :target: http://www.virtualrat.org
   :width: 50%
.. figure:: developer_docs/images/abi.png
   :target: http://www.abi.auckland.ac.nz
   :width: 50%


.. toctree::
   :hidden:

   developer_docs/dev_configuration_options
   tutorials/tutorial0/tutorial0_cpp
   tutorials/tutorial0/tutorial0_py
   tutorials/tutorial1/tutorial1_cpp
   tutorials/tutorial1/tutorial1_py
   tutorials/tutorial2/tutorial2_cpp
   tutorials/tutorial2/tutorial2_py
   tutorials/tutorial3/tutorial3_cpp
   tutorials/tutorial3/tutorial3_py
   tutorials/tutorial4/tutorial4_cpp
   tutorials/tutorial4/tutorial4_py
   tutorials/tutorial5/tutorial5_cpp
   tutorials/tutorial5/tutorial5_py
   tutorials/tutorial6/tutorial6_cpp
   tutorials/tutorial6/tutorial6_py
   tutorials/tutorial7/tutorial7_cpp
   tutorials/tutorial7/tutorial7_py
   tutorials/tutorial8/tutorial8_cpp
   tutorials/tutorial8/tutorial8_py
