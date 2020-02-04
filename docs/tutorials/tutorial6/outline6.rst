.. _tutorial6:

============================================
Tutorial 6: Working with multiple components
============================================

Getting started:  If you're reading this it's presumed that you're already
comfortable with the serlialisation, manipulation, and debugging functionality
available in the libCellML library, as well as using the API to create, debug
and validate your model.  This tutorial will build on work done in
:ref:`Tutorial 5<tutorial5>`: if you are starting from here you can find
the files which were created in that tutorial in the
:code:`resources` folder.

By the end of this tutorial you will be able to:

- create a CellML2.0 model which includes encapsulations and more than one
  :code:`Component`
- connect :code:`Components` to one another by mapping equivalent
  :code:`Variables`

Overview
--------
In :ref:`Tutorial 5<tutorial5>` we created a component representing an ion
channel.  The channel is controlled by a number of gates in series, whose
open or closed state and the transition between them is controlled by voltage:
hence, a "voltage-controlled ion gate".  In this tutorial we will explore how
a channel such as that made in Tutorial 5 can include another level of
control: the rate constants (:math:`\alpha_n` and :math:`\beta_n`) used earlier
are now functions of voltage themselves.  This is the situation in a
potassium channel, the theory of which is described in
:ref:`A model of a potassium channel<theory_potassiumchannel>`.

We will also show how an *environment* or *boundary conditions* component
can be used to ensure that the independent variables in the model are shared
consistently between components.  Storing the initial and independent variables
in an external component also makes it easier to change them without needing
to edit the model proper.

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial6_cpp>` page.

Resources:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial6.cpp` Either the skeleton code, or ..
    - :download:`tutorial6_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp`  Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 5 you can download the file created there:
      :download:`../resources/tutorial5_IonChannelModel.cellml`

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial6_py>` page.

Resources:

    - :download:`tutorial6.py` Either the skeleton code, or ..
    - :download:`tutorial6_complete.py` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 5 you can download the file created there:
      :download:`../resources/tutorial5_IonChannelModel.cellml`
