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





Tutorials for users
-------------------

.. toctree::
   :maxdepth: 3
   :titlesonly:

   tutorials/tutorial0/outline0
   tutorials/tutorial1/outline1
   tutorials/tutorial2/outline2
   tutorials/tutorial3/outline3
   tutorials/tutorial4/outline4
   tutorials/tutorial5/outline5
   tutorials/tutorial6/outline6
   tutorials/tutorial7/outline7
   tutorials/tutorial8/outline8
   theory/theory_index


CellML2 format specification
----------------------------

.. toctree::
    :maxdepth: 2
    :titlesonly:

    specifications/interpretation/4_model
    specifications/interpretation/5_import
    specifications/interpretation/6_import_units
    specifications/interpretation/7_import_component
    specifications/interpretation/8_units
    specifications/interpretation/9_unit
    specifications/interpretation/10_component
    specifications/interpretation/11_variable
    specifications/interpretation/12_reset
    specifications/interpretation/14_math
    specifications/interpretation/15_encapsulation
    specifications/interpretation/16_component_ref
    specifications/interpretation/17_connection
    specifications/interpretation/18_map_variables
    specifications/formal_specification


Documentation for developers
----------------------------

.. toctree::
   :maxdepth: 2
   :titlesonly:

   developer_docs/roadmap
   developer_docs/current_thinking
   developer_docs/usecases
   developer_docs/object_model
   developer_docs/api_documentation
   developer_docs/coverage_statistics
   developer_docs/dev_setup
   developer_docs/dev_building
   developer_docs/dev_testing_code
   developer_docs/dev_contribution
   developer_docs/dev_review
   developer_docs/dev_coding_standard
   contributors
   glossary

External references
----------------------------
.. toctree::
   :maxdepth: 2
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
