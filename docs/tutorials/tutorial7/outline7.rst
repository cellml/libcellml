.. _tutorial7:

=======================================
Tutorial 7: Creating the sodium channel
=======================================

This tutorial is a companion to :ref:`Tutorial 5<tutorial5>` which walked you through the
creation of a gated potassium channel model.  It follows the same basic recipe
steps as previously, but provides only a little guidance in terms of *how*
you will use the API to create the model and its components.  In general:

- create a model, a component, a validator, and the header and footer MathML
- add the governing equations in MathML to the component
- validate the model

    - this returns a list of variables to add
    - add the variables, their units and initial conditions (interfaces come
      later)

- validate the model again

    - this returns a list of units to add to the model
    - add the units

- validate the model yet again - it should be error free.
- repeat for all components
- define the equivalent variable connections
- define the equivalent variable interfaces (this is better done after all of
  the connections are made, so that you can be sure of the kind of interface
  which is needed for each variable)
- define the driving function MathML inside the environment component
- validate and output the model.

Background
----------
**TODO** put link to theory section here

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial7_cpp>` page.

Resources:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial7.cpp` Either the skeleton code, or ..
    - :download:`tutorial7_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp`  Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 5 you can download the file created there:
      :download:`../resources/tutorial7_SodiumChannelModel.cellml`


Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial7_py>` page.

Resources:

    - :download:`tutorial7.py` Either the skeleton code, or ..
    - :download:`tutorial7_complete.py` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 5 you can download the file created there:
      :download:`../resources/tutorial7_SodiumChannelModel.cellml`
