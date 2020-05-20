.. _tutorial8:

=================================================================
Tutorial 8: Encapsulating components and working with parents
=================================================================

If you're reading this it's presumed that you're already
comfortable with the deserlialisation and debugging functionality
available in the libCellML library.

By the end of this tutorial you will be able to:

- Create complicated encapsulation structures to allow interdependency between
  modelling components,
- design and create files which allow easy reuse of components,
- appreciate the consistency needed throughout the imports to avoid renaming
  units.

Background
----------
**TODO** Add the references to the cable equation and leakage stuff here ...

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial8_cpp>` page.

Resources:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial8.cpp` Either the skeleton code, or ..
    - :download:`tutorial8_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp`  Utility functions for
      use in the tutorials.
    - :download:`../resources/tutorial8_LeakageCurrentModel.cellml` The leakage current model
    - If you did not complete Tutorial 7 you can download the file created there:
      :download:`../resources/tutorial8_MembraneModel.cellml`

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial8_py>` page.

Resources:

    - :download:`tutorial8.py` Either the skeleton code, or ..
    - :download:`tutorial8_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.
    - :download:`../resources/tutorial8_LeakageCurrentModel.cellml` The leakage current model
    - If you did not complete Tutorial 7 you can download the file created there:
      :download:`../resources/tutorial8_MembraneModel.cellml`
