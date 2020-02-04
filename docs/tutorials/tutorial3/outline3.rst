.. _tutorial3:

==========================================================
Tutorial 3: Create a model and generate code using the API
==========================================================

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
population dynamics of two species - one a predator (sharks), and the other
their prey (fish).
The population of fish can only grow when they
are not being constantly eaten by sharks, and the rate at which is grows will
depend on how many fish are available for breeding.  At the same time, the
population of sharks will depend on how much food is available in the fish
population.  In maths this relationship can be written:

.. math::

    \frac{dy_s}{dt} =f(sharks, fishes, time) = a y_s + b y_s y_f

    \frac{dy_f}{dt} =f(sharks, fishes, time) = c y_f + d y_s y_f

where the constants :math:`(a, b, c, d)=(-0.8, 0.3, 1.2, -0.6)` and we'll use
the initial condtions of :math:`y_s(t=0)=1.0` and
:math:`y_f(t=0)=2.0`.

In order to model these unusual populations you'll need to create your own
custom units, to enter and check these governing equations in MathML syntax,
and to use the :code:`Generator` functionality to create files able to be
solved using a numerical integrator in C or Python.

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
