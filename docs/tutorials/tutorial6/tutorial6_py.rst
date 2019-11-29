.. _tutorial6_py:

--------------------------------------
Tutorial 6: Generating code **TODO**
--------------------------------------

Getting started:  If you're reading this it's presumed that you're already
comfortable with the deserlialisation and debugging functionality
available in the libCellML library.

By the end of this tutorial you will be able to:

- use the Generator to create models in Python or C format
- use the simple solver provided to run your created model(s).

Step 1: Read the potassium channel model
----------------------------------------

In Tutorial 5 you created a CellML model representing the behaviour of a gated
potassium channel, and included a driving function to replicate a voltage clamp
experiment.  In this tutorial we will use the CellML file you made to
demonstrate how the Generator can be used to create the same model in either
Python or C formats.

container:: dothis

    **1.a** Parse the Tutorial5_PotassiumChannelModel.cellml file and create a
    model from it, named "Tutorial6_PotassiumChannelModel".  If you didn't
    complete Tutorial 5 you can copy the file from the
    :code:`resources/tutorial5` folder instead.

container:: dothis

    **1.b** Create a Validator instance and confirm that the model you've
    created is valid.

Step 2: Create a Generator instance and initialise it
-----------------------------------------------------

The Generator is accessed similarly to the Validator and Parser, and a simple
call to the :code:`processModel` function will do most of the work.
::

    libcellml::GeneratorPtr generator=libcellml::Generator::create();
    generator->processModel(model);

container:: dothis

    **2.a** Construct a generator as above, and use the utility function to
    check that no errors were encountered.

TODO Currently segfaults - waiting for fix.
