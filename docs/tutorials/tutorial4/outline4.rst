.. _tutorial4:

========================================
Tutorial 4: Understanding generated code
========================================

By the time you have worked through Tutorial 4 you will be able to:

- investigate and understand the contents of files created by the
  :code:`Generator`
- integrate generated code into a simple solver to run a simulation

This tutorial assumes that you are comfortable with:

- interacting with a model and its entities using the API
  (see :ref:`Tutorial 3<tutorial3>`)
- using the :code:`Generator` functionality to output files in C
  or Python (see :ref:`Tutorial 3<tutorial3>`)

Overview
--------

During this tutorial you will take the code you generated during
:ref:`Tutorial 3<tutorial3>` which represented the population dynamics of two
species - a predator, the sharks, and their prey, the fish - and investigate
the files' contents.
Once we understand what the :ref:`Generator` can output, you will use a simple
numerical integrator to solve the system of equations which governs the model's
behaviour.

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial4_cpp>` page.

Requirements:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial4.cpp` Either the skeleton code, or ..
    - :download:`tutorial4_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp`  Utility functions for
      use in the tutorials.

If you did not complete :ref:`Tutorial 3<tutorial 3>` you can download the
files created by the :code:`Generator` from the :code:`resources` folder. These
are:
 - :download:`../resources/tutorial3_PredatorPrey_generated.c` The C implementation/source file
 - :download:`../resources/tutorial3_PredatorPrey_generated.h` The C interface/header file

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial4_py>` page.

Requirements:

    - :download:`tutorial4.py` Either the skeleton code, or ..
    - :download:`tutorial4_complete.py` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.

If you did not complete :ref:`Tutorial 3<tutorial 3>` you can download the
files created by the :code:`Generator` from the :code:`resources` folder. This is:
 - :download:`../resources/tutorial3_PredatorPrey_generated.py` The Python implementation/source file
