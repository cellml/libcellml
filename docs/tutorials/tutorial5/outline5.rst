.. _tutorial5:

============================================
Tutorial 5: Working with multiple components
============================================

Getting started:  If you're reading this it's presumed that you're already
comfortable with the serlialisation, manipulation, and debugging functionality
available in the libCellML library, as well as using the API to create, debug
and validate your model.  This tutorial will build on work done in
:ref:`Tutorial 4<tutorial4>`: if you are starting from here you can find
the files which were created in that tutorial in the
:code:`resources` folder.

By the end of this tutorial you will be able to:

- create a CellML2.0 model which includes encapsulations and more than one
  :code:`Component`
- connect :code:`Components` to one another by mapping equivalent
  :code:`Variables`

Overview
--------
In :ref:`Tutorial 4<tutorial4>` we created a component representing an ion
channel.  The channel is controlled by a number of gates in series, whose
open or closed state and the transition between them is controlled by voltage:
hence, a "voltage-controlled ion gate".  In this tutorial we will explore how
a channel such as that made in Tutorial 4 can include another level of
control: the rate constants (:math:`\alpha_y` and :math:`\beta_y`) used earlier
are now functions of voltage themselves.  **TODO check this is to be recommended?** We will also show how an
*environment* component can be used to ensure that all components are modelled
synchronously.

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial5_cpp>` page.

Resources:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial5.cpp` Either the skeleton code, or ..
    - :download:`tutorial5_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp`  Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 4 you can download the file created there:
      :download:`../resources/tutorial5_PotassiumChannelModel.cellml`

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial5_py>` page.

Resources:

    - :download:`tutorial5.py` Either the skeleton code, or ..
    - :download:`tutorial5_complete.py` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 4 you can download the file created there:
      :download:`../resources/tutorial5_PotassiumChannelModel.cellml`
