.. _tutorial1:

========================================
Tutorial 1: Reading, writing, 'rithmetic
========================================

Welcome to the introductory tutorial for the use of the libCellML library.
Using these tutorials in sequence will walk you through the functionality and
build your knowledge step by step. If, however, you just need to jump in and
figure out one specific idea, you can find a tutorial related to that subject
using the index. **TODO**

After completing this tutorial you will be able to:

- read the contents of a CellML file
- deserialse its contents using the :code:`Parser` to create a :code:`Model` structure
- investigate the hierarchical contents of the :code:`Model`, including the
  :code:`Components`, :code:`Variables`, and MathML blocks
- serialise the model and write to another file

Where you see the green indentation >> in this document it means that there's
something you need to do, and if you're stuck at any stage you can refer to
the completed :code:`tutorial1_completed` file for help.

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial1_cpp>` page.

Requirements:

    - The CMake file for building :download:`CMakeLists.txt`
    - Either the skeleton code from :download:`tutorial1.cpp` or the completed
      code from :download:`tutorial1_complete.cpp`
    - The input CellML file :download:`../resources/tutorial1.cellml`

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial1_py>` page.

Requirements:

    - Either the skeleton code from :download:`tutorial1.py` or the completed
      code from :download:`tutorial1_complete.py`
    - The input CellML file :download:`../resources/tutorial1.cellml`
