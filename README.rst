libCellML
=========

libCellML aims to become an easy to use library that will be useful to developers of `CellML <https://www.cellml.org/>`_ applications.

The prime libCellML repository is located at https://github.com/cellml/libcellml.

The documentation for the libCellML project is available at https://libcellml.readthedocs.io/.

**NOTE**: ALTHOUGH libCellML IS ALREADY BEING USED SUCCESSFULLY, IT SHOULD BE CONSIDERED ALPHA UNTIL VERSION 1.0 IS RELEASED.

Scope
-----

The purpose of libCellML is to create, manipulate, serialise, deserialise, validate and instantiate `CellML <https://www.cellml.org/>`_ models.
In the first instance, all serialising and deserialising will be to and from standard strings and using the `CellML <https://www.cellml.org/>`_ `XML <https://www.w3.org/XML/>`_ format.

The library is intended to be lightweight and focused purely in dealing with `CellML <https://www.cellml.org/>`_ models.
In achieving this, some of the convenience methods/objects that we might expect will not be part of libCellML.
For example, in our current thoughts, libCellML would not be concerned with the actual mechanics of resolving and retrieving external resources - calling applications would be required to resolve and retrieve import URLs and provide the serialised documents to libCellML in the form of strings for instantiation as part of the `CellML <https://www.cellml.org/>`_ hierarchical model description.

Example code will be provided that demonstrates how such tasks can be achieved using standard tools, i.e. `libcurl <https://curl.haxx.se/libcurl/>`_ for C/C++ and requests for Python to resolve and retrieve imported models.

Continuous Integration
----------------------

libCellML makes use of :buildbot:`Buildbot<>` for continuous integration testing, all code is run through the test suite when a pull request is created or added to.
More information on how :buildbot:`Buildbot<>` is integrated in to the development process is available from the documentation at http://libcellml.readthedocs.io/.

Contribute
----------

libCellML is an open-source project, thus, welcoming contributions.
If you are interested you may (in short):

* Fork `libCellML on GitHub <https://github.com/cellml/libcellml>`_ and submit a pull request with your modifications.
  For more information on contributing code see the documentation at http://libcellml.readthedocs.io/.
* Subscribe to the libCellML mailing list at https://lists.cellml.org/sympa/info/cellml-tools-developers.
