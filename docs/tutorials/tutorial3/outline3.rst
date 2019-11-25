.. _tutorial3:

==========================================
Tutorial 3: Create a model using the API
==========================================

By the time you have worked through Tutorial 3 you will be able to:

- create a new model and its child entities from scratch using the API
- write your own MathML syntax to construct governing equations
- define custom combinations of built-in units
- define your own custom units independent from the built-in units
- use the :code:`Generator` functionality to transform the model into other
  languages.

This tutorial assumes that you are comfortable with:

- accessing and adjusting names of items inside a model hierarchy
  (see :ref:`Tutorial 2<tutorial2>`)
- creating a validator and using it to check a model for errors
  (see :ref:`Tutorial 2<tutorial2>`)
- accessing the errors produced by a validator and using them to correct
  the model (see :ref:`Tutorial 2<tutorial2>`)
- serialising and printing a model to a CellML2 file (see
  :ref:`Tutorial 1<tutorial1>`)

Overview
--------

During this tutorial you will create a simple model representing the
exponential decay of speed for a sled sliding on ice.  You will use
both built-in and create your own user-defined units.

**TODO** Finish this explanation


C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial3_cpp>` page.

Requirements:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial3.cpp` Either the skeleton code, or ..
    - :download:`tutorial3_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp`  Utility functions for
      use in the tutorials.


Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial3_py>` page.

Requirements:

    - :download:`tutorial3.py` Either the skeleton code, or ..
    - :download:`tutorial3_complete.py` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.
