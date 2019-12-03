.. _tutorial4_cpp:

------------------------------------------
Tutorial 4: Generating code and simulation
------------------------------------------

Getting started:  If you're reading this it's presumed that you're already
comfortable with the deserlialisation and debugging functionality
available in the libCellML library.

By the end of this tutorial you will be able to:

- use the Generator to create models in Python or C format
- use the simple solver provided to run your created model(s).

1: Read the predator prey model
----------------------------------------

In :ref:`Tutorial 3<tutorial3>` you created a CellML model representing the
population dynamics in a predator-prey situation.  In this tutorial we will
use the CellML file you made to demonstrate how the :code:`Generator` can be used to create the same model in either
Python or C formats, and explain the contents and usages of the generated files.

container:: dothis

    **1.a** Parse the Tutorial3_PredatorPrey.cellml file and create a
    model from it, named "Tutorial4_PredatorPreyModel".  If you didn't
    complete Tutorial 3 you can copy the file from the
    :code:`resources` folder instead.

container:: dothis

    **1.b** Create a :code:`Validator` instance and confirm that the model you've
    created is valid.

2: Create a Generator instance and initialise it
-----------------------------------------------------

The :code:`Generator` is accessed similarly to the :code:`Validator` and
:code:`Parser`, and a simple call to the :code:`processModel` function
will do most of the work.

.. code-block:: cpp

    libcellml::GeneratorPtr generator=libcellml::Generator::create();
    generator->processModel(model);

container:: dothis

    **2.a** Construct a generator as above, and check that no errors were
    encountered.
