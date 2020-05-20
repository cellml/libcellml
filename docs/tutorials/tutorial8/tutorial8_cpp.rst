.. _tutorial8_cpp:

===============================================
Tutorial 8 C++: Importing and flattening models
===============================================

The outline for this tutorial is shown on the :ref:`Tutorial 8<tutorial8>`
page. These are the C++ instructions.  For the same tutorial in Python
please see the :ref:`Tutorial 8 in Python<tutorial8_py>` page instead.

**Resources:**

    - :download:`CMakeLists.txt` The CMake file for building this tutorial;
    - :download:`tutorial8.cpp` Either the skeleton code, or :download:`tutorial8_complete.cpp` the completed tutorial code;
    - :download:`../utilities/tutorial_utilities.h` and :download:`../utilities/tutorial_utilities.cpp` Utility functions for use in the tutorials.

   - The following files are needed as inputs for this tutorial.
     If you did not complete the relevant tutorials you can copy these files from the resources folder:

        - :download:`../resources/tutorial8_LeakageCurrentModel.cellml` The leakage current model;
        - :download:`../resources/tutorial8_LeakageCurrentModel_parameters.cellml` Leakage parameters;
        - :download:`../resources/tutorial8_MembraneModel.cellml` The membrane model;
        - :download:`../resources/tutorial6_PotassiumChannelModel.cellml` The potassium channel (or use your own) and its controller :download:`../resources/tutorial6_controller.cellml`; and
        - :download:`../resources/tutorial7_SodiumChannelModel.cellml` The sodium channel (or use your own) and its controller model :download:`/resources/tutorial7_controller.cellml`.

.. contents:: Contents
    :local:

Step 0: Set the stage
=====================
Before going much further it's probably a good idea to understand what it is that you're doing here.
For a full description of the biological theory, please see the :ref:`Hodgkin-Huxley background<hh_background>` document.
You should be able to see the variables and maths inside the components as you go by simply printing them to the screen.

.. container:: dothis

    **0.a** As previously, create:
        - a :code:`Validator` instance for debugging purposes;
        - a :code:`Model` model, and name it appropriately.

As we go through this tutorial you'll be importing the models and components that you've created in previous tutorials, and pulling them all together to create the final Hodgkin-Huxley model.
If you didn't complete the tutorials, you can use the files provided in the :code:`resources` folder.

.. container:: nb

    Because you will be importing several different files into this one, please note that these will need to be in the same folder location.
    This is necessary because the :code:`Model::resolveImports()` function will only store one folder path per model.
    Before you proceed, please copy the files listed above into your working directory, whether they are ones you have created in previous tutorials or those provided in the resources directory.

Step 1: Import the membrane component
=====================================

.. container:: dothis

    **1.a** First create a component which will represent the membrane of the Hodgkin-Huxley model, and name it appropriately.
    Add it to your model.

.. container:: dothis

    **1.b** Just as you did in :ref:`Tutorial 7<tutorial7_cpp>`, next you need to create an :code:`ImportSource` item, and set its url to be the :code:`tutorial8_MembraneModel.cellml` file supplied in the resources folder.

.. container:: dothis

    **1.c** Thirdly we need to link our import source to the import destination using the :code:`Component::setImportSource()` function on the membrane component, and to use the :code:`Component::setImportReference()` function to specify the name of the component inside the import model to retrieve.
    In this case, the component is named "membrane_for_importing".

.. container:: dothis

    **1.d** At this stage, our model has only one component in it, and even though we've specified the imports completely, we still need to resolve the imports and flatten the model before the imported items will be instantiated here.
    Use the :code:`Model::hasUnresolvedImports()` function to show that the imports have not been resolved yet.

.. container:: dothis

    **1.e** Print the model to the terminal to show that it contains only one empty component at the moment.

.. code-block:: console

    The model name is: 'Tutorial8_HHModel'
    The model defines 0 custom units:
    The model has 1 components:
      Component[0] has name: 'membrane'
      Component[0] has 0 variables


.. container:: dothis

    **1.f** Use the :code:`Model::resolveImports()` function of the model to (erm) resolve the imports.
    This takes an argument of a string representing the full absolute path to the directory in which the import file specified in 1.b is stored, and must end with a slash.
    If the files you're importing are in the working directory as your code, you can use and empty string :code:`""` as the path.

.. container:: dothis

    **1.g** Call the :code:`hasUnreolvedImports()` function again and verify that they are now resolved.

.. container:: dothis

    **1.h** Flatten the model.
    This process will recursively search through all of the imported items in the model and create local instances of them.

.. container:: nb

    Note that:

    - If you call the flatten() function without first resolving the imports, nothing will change.
    - Flattening a model fundamentally changes it ... and cannot be undone.

.. container:: dothis

    **1.i** Print the flattened model to the terminal and verify that it now contains:

       - 4 units
       - 1 component with

           - 8 variables
           - a MathML block.

Step 2: Import the sodium channel component
===========================================

.. container:: dothis

    **2.a** Create a component representing the sodium channel.
    This will be encapsulated inside the membrane component, so add it there instead of adding it to the model.

.. container:: dothis

    **2.b** Create an importer for the sodium channel, and point it to the file you created in :ref:`Tutorial 7<tutorial7_cpp>`.
    Note that you will need to make sure it exists in the same path as the earlier files.
    If you did not complete Tutorial 7 you can use the :download:`../resources/tutorial7_SodiumChannelModel.cellml` file in the resources folder.

.. container:: dothis

    **2.c** Link the sodium channel component to the importer and set the reference (the name of the source component) to import.
    In the file provided this is named "sodiumChannel".
    You will need to change this to whatever you named the component in Tutorial 7.

Until a model containing imports has been flattened, those imported components exist only as an instruction: they are not instantiated, and their variables do not yet exist.
This means that equivalences between variables in imported cannot be specified.
For this reason, we need to create dummy variables in the imported components; these will be overwritten when the imports are flattened, but they allow us to create connections to variables before then.

.. container:: dothis

    **2.d** Create dummy variables for voltage, time, and the sodium current, and add them to your sodium channel component.
    These need to have the same name as those in the imported component.

.. container:: dothis

    **2.e** Resolve the model's imports and check that none are unresolved.

Step 3: Import the potassium channel component
==============================================

.. container:: dothis

    **3.a** Repeat all the tasks in Step 2, this time for the potassium channel model you created in :ref:`Tutorial 6<tutorial6_cpp>`.
    If you did not complete Tutorial 6 you can use the :download:`../resources/tutorial6_PotassiumChannelModel.cellml`, and import the component called "potassiumChannel".

.. container:: dothis

    **3.b** Create dummy variables for voltage, time, and the potassium channel current, and add them to your component.


Step 4: Import the leakage component
====================================

.. container:: dothis

    **4.a** Repeat all the tasks in Step 2, this time for the "leakageCurrent" component in the model supplied inside :download:`../resources/tutorial8_LeakageModel.cellml`.

.. container:: dothis

    **4.b** Create dummy variables for voltage, time, and the leakage current (named :code:`i_L`), and add them to you leakage component.

Step 5: Import parameters
=========================

.. container:: dothis

    **5.a** Repeat all the tasks in Step 2, this time for the "parameters" component in the model supplied inside :download:`../resources/tutorial8_controller.cellml`.

.. container:: dothis

    **5.b** Set up a dummy variable for voltage so that the parameters component can initialise the ODE in the membrane component, and for a variable called :code:`Cm`.

Step 6: Connect variables between components
============================================

.. container:: dothis

    **6.a** Now that we've got all the imports done, we need to connect the imported components and their dummy variables together.
    The variables to connect are:

      - voltage:  parameters -> membrane -> sodium channel, potassium channel, leakage
      - time: membrane -> sodium channel, potassium channel
      - current variables (i_Na, i_K, i_L): membrane -> their respective channels
      - Cm: parameters -> membrane

.. container:: dothis

    **6.b** Serialise the model and it to a CellML file.
    In the steps below the model will be flattened for code generation, but it's good to keep an unflattened copy too in case you want to make changes later on.

Step 7: Resolve imports and flatten the model
=============================================

.. container:: dothis

    **7.a** Resolve the model's imports to the folder where all of the files are located, and check that there are no unresolved imports outstanding.

.. container:: dothis

    **7.b** Flatten the model, and print the flattened model structure to the terminal for checking.

.. container:: dothis

    **7.c** Validate the flattened model, expecting that there are no errors.

Step 8: Generate the model and output
=====================================

.. container:: dothis

    **8.a** Create a :code:`Generator` instance and submit the model for processing.
    Expect that there are no errors logged in the generator afterwards, but if there are, your experience with the possible issues in previous tutorials should be enough to resolve them.

.. container:: dothis

    **8.b** Retrieve and write the interface code (*.h) and implementation code (*.c) to files.

.. container:: dothis

    **8.c** Change the generator profile to Python and reprocess the model.

.. container:: dothis

    **8.d** Retrieve and write the implementation code (*.py) to a file.

Now that the model has been created an output, it's time to submit it to the solver for simulation.

Step 9: Running the simulation
==============================

Running the simulation using the :ref:`simple solver<solver>` with a timestep of 0.001 for 2000 iterations will give you the results shown below.
