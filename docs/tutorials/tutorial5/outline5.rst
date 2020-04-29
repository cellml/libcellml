.. _tutorial5:

=========================================
Tutorial 5: Modelling a gated ion channel
=========================================

If you're reading this it's presumed that you're already comfortable with the serlialisation, mainipulation, and debugging functionality available in the libCellML library.
If not, please see the earlier tutorials which introduce these issues:

- :ref:`Tutorial 1: Reading, writing, and 'rithmetic in a CellML file<tutorial1>`
- :ref:`Tutorial 2: Debugging, error checking, and validation<tutorial2>`
- :ref:`Tutorial 3: Creating a model using the API<tutorial3>`

From this point onwards the tutorials will build on work done in the previous ones.
If you need to jump in at some intermediate stage you will find all the files created by the earlier tutorials in the
:code:`resources` folder.

Overview
--------
The basic steps for model creation and output are the same as those in :ref:`Tutorial 3<tutorial3>`, but here you'll begin to create a model which will later become the Hodgkin Huxley model.
All the biological and mathematical modelling background needed for this model are explained separately, :ref:`Understanding the Hodgkin-Huxley model<hh_theory>`.
In general we will:

#.  Create a simple model with one component.
    This will represent a gated ion channel, and we'll write it in such a way that we can reuse it later.
#.  Add mathematics to the component.
    This includes writing MathML code as a string and adding it to the component.
#.  Because the maths defined above will need variables, we'll need to add these to the component as well.
#.  Because the quantities modelled have units, we will define what these are, and make sure that they are included in the model too.

As always, the steps discussed here are mirrored by the comments in the code files attached.
You can choose to either create your own code from the structure given in the :code:`tutorial5` file(s), or to simply read the
finished code given in the :code:`tutorial5_complete` file(s).

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial5_cpp>` page.
You will need to download the following files:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial;
    - :download:`tutorial5.cpp` Either the skeleton code, or :download:`tutorial5_complete.cpp` the completed tutorial code; and
    - :download:`../utilities/tutorial_utilities.h` and :download:`../utilities/tutorial_utilities.cpp`  Utility functions for use in the tutorials.


Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial5_py>` page.
You will need to download the following files:

    - :download:`tutorial5.py` Either the skeleton code, or :download:`tutorial5_complete.py` the completed tutorial code; and
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for use in the tutorials.
