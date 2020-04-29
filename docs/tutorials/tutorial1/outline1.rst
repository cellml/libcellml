.. _tutorial1:

============================================
Tutorial 1: Reading and writing CellML files
============================================

Welcome to the introductory tutorial for the use of the libCellML library.
Using these tutorials in sequence will walk you through the functionality and build your knowledge step by step.
If, however, you just need to jump in and figure out one specific idea, you can find a tutorial related to that subject using the index. **TODO**

After completing this tutorial you will be able to:

- Read the contents of a CellML file;
- Deserialse its contents using the :code:`Parser` to create a :code:`Model` structure;
- Investigate the hierarchical contents of the :code:`Model`, including the :code:`Components`, :code:`Variables`, and MathML blocks; and
- Serialise the model and write to another file using the :code:`Printer`.

C++ instructions
----------------
Please see the :ref:`C++ instructions<tutorial1_cpp>` page.
The files you will need are:

    - The CMake file for building :download:`CMakeLists.txt`;
    - Either the skeleton code from :download:`tutorial1.cpp` or the completed code from :download:`tutorial1_complete.cpp`; or
    - The input CellML file :download:`../resources/tutorial1.cellml`.

Python instructions
-------------------
Please see the :ref:`Python instructions<tutorial1_py>` page.
The files you will need are:

    - Either the skeleton code from :download:`tutorial1.py` or the completed code from :download:`tutorial1_complete.py`; and
    - The input CellML file :download:`../resources/tutorial1.cellml`.
