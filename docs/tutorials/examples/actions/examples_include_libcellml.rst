.. _examples_include_libcellml:

Include the libCellML library in your project
+++++++++++++++++++++++++++++++++++++++++++++
If you've followed :ref:`the instructions for installing libCellML<tutorial0>` then the library is available for use as shown below.
Note that this doesn't invoke the libCellML namespace, so classes are accessed using the :code:`libcellml::` prefix.

.. code-block:: cpp

  // main.cpp
  #include <libcellml>

  auto model = libcellml::Model::create();

In Python classes can be imported individually as required, or the whole library imported at once.

.. code-block:: python

  # main.py
  import libcellml                       # import the entire library, or
  from libcellml import Model, Variable  # import specific classes as needed
