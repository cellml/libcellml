libCellML
=========

libCellML aims to become an easy to use library that will be useful to developers of CellML applications.

The prime libCellML repository is located at: https://github.com/cellml/libcellml.

The documentation for the libCellML project is available at: http://libcellml.readthedocs.org/.

Scope
-----

The purpose of libCellML is to create, manipulate, serialise, deserialise, validate and instantiate
CellML models. In the first instance, all serialising and deserialising will be to and from standard
strings and using the CellML XML format.

The library is intended to be lightweight and focused purely in dealing with CellML models. In achieving this,
some of the convenience methods/objects that we might expect will not be part of libCellML.
For example, in our current thoughts, libCellML would not be concerned with the actual mechanics of
resolving and retrieving external resources - calling applications would be required to resolve and
retrieve import URL's and provide the serialised documents to libCellML in the form of strings for
instantiation as part of the CellML 1.1/1.2 hierarchical model description.

Continuous Integration
----------------------

libCellML makes use of Buildbot for continuous integration testing, all code is run through the
test suite when a pull request is created or added to.  More information is available from the
`documentation <http://libcellml.readthedocs.org/>_`.

Contribute
----------

libCellML is an open-source project, thus, welcoming contributions.
If you are interested you may:

  * Fork libCellML on GitHub `here <https://github.com/cellml/libcellml>_` and submit pull-request with your modifications.
    (For more information on contributing code see the `documentation <http://libcellml.readthedocs.org/>_`)
  * Subscribe to the `libCellML mailing list <https://lists.cellml.org/sympa/info/cellml-tools-developers>_`

