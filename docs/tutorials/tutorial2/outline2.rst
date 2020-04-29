.. _tutorial2:

====================================================
Tutorial 2: Debugging, error checking and validating
====================================================
In this tutorial you'll explore how the :code:`Validator` object can be put to use as you create and interact with your models to help you debug and find issues ahead of submitting it for simulation.
You'll be taking a CellML2.0 file which has some mistakes in it, using the validation functionality to identify them, and then using the access and editing functions to fix them.
By the time you have worked through Tutorial 2 you will be able to:

- Use the :code:`Parser` to report errors enountered when reading a file or deserialising a string; and
- Use the :code:`Validator` to check for errors related to a model's description as compared to the CellML2.0 specifications.

This tutorial assumes that you can already:

  - Read and deserialise a CellML model from a file (as in :ref:`Tutorial 1<tutorial1>`);
  - Retrieve the name and id of models, components, and variables;
  - Navigate through the hierarchy of the :code:`Model` and its subsidiary elements (:code:`Components`, :code:`Variables`, :code:`Units`, and MathML blocks); and
  - Serialise and print a :code:`Model` structure to a CellML file.

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial2_cpp>` page.  You will need to download:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial;
    - :download:`tutorial2.cpp` Either the skeleton code or :download:`tutorial2_complete.cpp` the completed tutorial code; and
    - :download:`../resources/tutorial2.cellml` The input CellML file to read.

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial2_py>` page.  You will need to download:

    - :download:`tutorial2.py` Either the skeleton code or :download:`tutorial2_complete.py` the completed tutorial code; and
    - :download:`../resources/tutorial2.cellml` The input CellML file to read,
