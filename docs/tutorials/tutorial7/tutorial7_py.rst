.. _tutorial7_py:

==============================================
Tutorial 7 Python: Creating the sodium channel
==============================================

The outline for this tutorial is shown on the :ref:`Tutorial 7<tutorial7>` page.
These are the Python instructions.
For the same tutorial in C++ please see the :ref:`Tutorial 7 in C++<tutorial7_cpp>` page instead.

**TODO** THESE ARE OUT OF DATE!

**Resources:**

    - :download:`tutorial7.py` Either the skeleton code, or :download:`tutorial7_complete.py` the completed tutorial code;
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for use in the tutorials; and
    - :download:`../resources/tutorial7_controller.cellml` An external controller model.

.. contents:: Contents:
    :local:

Step 1: Create the sodium channel component
===========================================

.. container:: dothis

    **1.a** Create a model and name it appropriately.

.. container:: dothis

    **1.b** Create a component instance for the sodium channel and name it appropriately.
    Add the component to the model.

.. container:: dothis

    **1.c** Add the mathematics to this component according to the equations shown below (if you need to, you can copy the code from the "Show code" link below).
    Call the validator, expecting errors related to missing variables.

.. math::

    Na_{conductance} = g_{Na} h m^{3} \\

    i_{Na} = Na_{conductance} (V-E_{Na})

.. container:: toggle

    .. container:: header

        Show code

    .. code-block:: python

        equation1 = \
            '  <apply><eq/>\n'\
            '    <ci>Na_conductance</ci>\n'\
            '    <apply><times/>\n'\
            '      <ci>g_Na</ci>\n'\
            '      <ci>h</ci>\n'\
            '      <apply><power/>\n'\
            '        <ci>m</ci>\n'\
            '        <cn cellml:units="dimensionless">3</cn>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        equation2 = \
            '  <apply><eq/>\n'\
            '    <ci>i_Na</ci>\n'\
            '    <apply><times/>\n'\
            '      <ci>Na_conductance</ci>\n'\
            '      <apply><minus/>\n'\
            '        <ci>V</ci>\n'\
            '        <ci>E_Na</ci>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'


.. container:: dothis

    **1.d** Add the missing variables as listed by the validator.
    Validate the model again, expecting errors related to missing units.

.. container:: dothis

    **1.e** Add the units are required by the validator.

.. container:: dothis

    **1.f** Link the model's units, and validate that the model is now free of errors.

Step 2: Create the m-gate imported component
============================================
All the other components required by this model can be imported.
Importing is different from our previous method of reusing code, in that it does not create a copy, or simply parse the code, but simply saves instructions for how items (components or units) in another model can be used in the current one.
This means that many models can make use of a single component, without needing to have different copies. 
Imports are the best way to reuse items where you don't need to make any changes to the items.  
If you do need to make changes, it's better to use the :code:`Parser` to instantiate the items instead of importing.

To create the recipe by which items will be imported, we need to specify three pieces of information:

- a destination in the current model for the imported item (this is the placeholder item, created in 2.a below);
- a source file containing the item to be imported (this is set by the :code:`ImportSource.setUrl` function); and
- the name of the item within the source model that will be imported (this is set by the :code:`ImportSource.setImportReference` function).

The structure in which this information is stored is:

.. code:: text

    model:
      ├─ importSource: <╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶┐
      │   └─ url: "../pathToSourceModel/sourceModel.cellml" ╵
      │                                                     ╵
      ├─ units: name = "destinationUnits"                   ╵
      │   ├─ importSource <╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶┤
      │   └─ importReference = "sourceUnits"                ╵
      │                                                     ╵
      └─ component: name = "destinationComponent"           ╵
          ├─ importSource <╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶┘
          └─ importReference = "sourceComponent"

    model: sourceModel.cellml
      ├─ units: name = "sourceUnits"
      └─ component: name = "sourceComponent"

The :code:`ImportSource` items are added to parent model by the action of adding them to a component or units item (as shown below).
An :code:`ImportSource` can be used more than once (ie: added to more than one component or units), provided they share the same source model.
The :code:`importReference` attribute belongs to the item imported, not to the :code:`ImportSource`.
More than one item with the same import source and reference is permitted, as long as the destination items are named uniquely.
An :code:`ImportSource` item can be retrieved either from the item which uses it, or from the model itself.
The example below is based on the diagram above, and all import sources returned are identical.

.. code:: python

    # From the destination units:
    import_source1 = units.importSource()

    # From the destination component:
    import_source2 = component.importSource()

    # From the model:
    num_import_sources = model.importSourceCount() # returns 1.
    import_source3 = model.importSource(0)

.. container:: dothis

    **2.a** Create a new component for the m-gate and name it appropriately.
    Add the m-gate component as a child of the sodium channel component.
    The component will be a placeholder for the component in a separate model which we'll import.

.. container:: dothis

    **2.b** Create an :code:`ImportSource` item and attach it to the component using the :code:`Component.setImportSource` function.
    This indicates that the component's contents will be imported from another model, and means that the :code:`Model.hasUnresolvedImports` function will now return true.

.. container:: dothis

    **2.c** Set the URL of the :code:`ImportSource` to the location at which the source model can be found.
    This can be absolute, or relative to the current model's location.
    For this example, use the file in the resources folder named "tutorial7_mGate.cellml", and set the path from where this model will be stored to that folder.
  
.. container:: dothis

    **2.d** Set the component's import reference using the :code:`Component.setImportReference` function to be the name of the component in the source model whose contents will be imported into this one.  
    For this example, use "mGate".
    
Specifying imports in this way does not create anything in the model itself, it just saves a set of instructions for how to create those components (or units) later on.
The process of verifying that the instructions work is called "resolving" the imports, and the process of actually creating the imported items in this model is called "flattening" the model.
Because it's easier to work with unflattened models later on (if you want to vary their ingredients etc), you will probably find that you need to connect imported components to local ones, or to other imported ones before the model is flattened.
This creates a problem as the variables in those imported components can't yet be referenced: they don't exist yet in this model.
The way around this is to create "dummy" variables in the imported component placeholders you created.
Note that these need to have the same names as the variables in the import, and will be over-written by the "real" ones when the model is flattened.
Because they will be over-written, you only need to specify their names and nothing else.

.. container:: dothis

    **2.e** Create dummy variables representing time "t", voltage "V", and gate status "m" and add to this component.
    You do not need to specify units or interface types, so can take advantage of the compact form of creation, naming, and addition:

    .. code:: python

        m_gate.addVariable(Variable.create("t"))

.. container:: dothis

    **2.f** Add variable equivalences between the dummy variables you just created and their counterparts in the sodium channel component.
    These will be the variables named :code:`"t"`, :code:`"V"`, and :code:`"m"`.

.. container:: dothis

    **2.g** Submit to the validator for checking.  
    Expect errors related to the interface types on the variables you have just created equivalences for.

.. container:: dothis

    **2.h** Fix the interface types for the sodium channel variables by setting them to "public_and_private".
    Revalidate and expect there to be no more errors.


Steps 3-5: Import further components
====================================

The next few steps replicate step 2, but for other components.

.. container:: dothis

    **3** Repeat the steps within Step 2 for the "hGate" component, and include it as a child of the sodium channel component.
    As always, you can use the :code:`Validator` to check each step, and to give you messages about where you may have gone wrong.

    - The source component is defined inside the file called "tutorial7_hGate.cellml" in the resources folder.
    - It is named "hGate" in that file.
    - You will need to create and link dummy variables named "h", "V", and "t".
    - You will need to set the sodium channel variable "h" to have an interface type "public_and_private".

.. container:: dothis

    **4** Repeat the steps within Step 2 for the "controller" component, and include it as a child of the model. 

    - The controller is defined inside the file called "tutorial7_controller.cellml" in the resources folder.
    - It is named "controller" in that file.
    - You will need to create and link dummy variables named "V" and "t".
    - You will need to set the sodium channel variables to have an interface type "public_and_private".

.. container:: dothis

    **5** Repeat the steps within Step 2 for the parameters component, and include it as a child of the model. 
    Note that since this step will access the same file as was used in Step 4 ("tutorial7_controller.cellml" in the resources folder), you can simply reuse the same :code:`ImportSource` item you created there for this component.  
    - Import the component reference "parameters" from that file.
    - You will need to create and link dummy variables named "m", "h", "g_Na", and "E_Na".
    - You will need to set the corresponding sodium channel variables to have an interface type "public".

Step 6: Clean-up and serialise
==============================

Once you have all the components imported, it's time to tidy it up and serialise to a CellML file.
Even though it won't be used in this tutorial, we need to set the interface types on any variable in the sodium channel component that will need to be accessible to other components later.
It's worth thinking about these at the time of writing the component, as it increases its re-usability and usefulness later on.
In this case, we'll only need to set the "i_Na" sodium current variable to have a public interface.

.. container:: dothis

    **6.a** Set the sodium current variable in the sodium channel to have a public interface.

 At this stage our model can be written to a CellML file.
 As the model contains import statements, the serialised and printed model would also maintain those same dependencies, and would need to exist in the same relative position to the source model files which it uses.
 In later steps we'll disconnect this dependency to allow for the code generation step.

.. container:: dothis

    **6.b** Check that the model is valid, then create a :code:`Printer`, and use it to serialise the model.
    Write the serialised model to a file.

.. container:: dothis

    **6.c** Go and have a cuppa, you're halfway there!

The remainder of this tutorial looks at the processes needed in order to generate a runnable set of C++ or Python files from your model.
If you don't need your model in those formats, you can stop now.
If you do, read on ... 

Step 7: Resolving and flattening the model
==========================================

As alluded to in Step 2, creating "imported" items really just creates a recipe for retrieving those items, but it doesn't actually do the retrieval step.
That process of opening the source model files and instantiating their contents into the destination items is known as "flattening" the model.
This is done with the help of an :code:`Importer` class, and has two key steps:

- "resolving" the imports in the current model (this is the process of opening and checking the source files for the required references, including following generations of imports back to their original concrete source item); and
- "flattening" the model (this is the process of instantiating the imported items in their destination items; they are no longer imports after this).

.. container:: dothis

    **7.a** Create an :code:`Importer` instance.

.. container:: dothis

    **7.b** Call the :code:`hasUnresolvedImports()` function on your model to check that its imports have not yet been resolved.
    This should return :code:`True`, indicating that the model has unresolved imports.

.. container:: dothis

    **7.c** The importer needs to know the path to where the import dependencies are located.
    This should be relative to the current working directory, and should end with a slash.
    Call the :code:`Importer.resolveImports` function with the model and the pathway to the resources folder from your working directory.

    .. code:: python

        importer.resolveImports(yourModelHere, '/path/to/the/source/models/')
    
.. container:: dothis

    **7.d** Check that the imports have been resolved by repeating 7.b and expecting it to return :code:`False`.

.. container:: dothis

    **7.e** Check that there have been no issues reported by the :code:`Importer`.  
    Note that these are not necessarily errors, and you should check all of the issue levels.
    The :code:`Importer` class will report different types of issues, including cyclical imports and missing files: these are returned as warnings, so it's important to check all issue types in order to get the full picture.
    
.. container:: dothis

    **7.f** Now it's time to flatten the model.
    This process will leave the original model untouched and return a flattened copy.
    Create a flattened model by calling the :code:`Importer.flattenModel` function with your model as input.

.. container:: gotcha

    Note that if you call the :code:`flattenModel` function on a model which still has unresolved imports, it will return :code:`None`. 

.. container:: dothis

    **7.g** Check that the flattened model is not :code:`None`, and then pass it to the validator and check that there are no errors.

Step 7: Generate and output the model
=====================================
As we've done several times before, it's time to generate the runnable model code.

.. container:: dothis

    **7.a** Create a :code:`Generator` instance and submit the model for processing with a :code:`C` profile.
    Check that there are no errors found during this processing.

.. container:: dothis

    **7.b** Retrieve and write the interface :code:`*.h` code and implementation :code:`*.c` code to files.

.. container:: dothis

    **7.c**  Change the generator profile to Python and reprocess the model

.. container:: dothis

    **7.d** Retrieve and write the implementation code :code:`*.py` to a file.

Step 8: Run the simulation
==========================
You can solve the model to simulate the dynamics of the sodium gate using the supplied solver.
Instructions for running this are given on the :ref:`Simple solver for generated models<solver>` page, as well as in previous tutorials.
You should see the behaviour shown in the figures below by the red line representing a voltage step to -20mV.
The theory of this channel's operation is given in :ref:`Theory of the sodium channel<theory_sodiumchannel>`.

.. figure:: ../../theory/images/tut7_Vgraph.png
   :name: tut7_Vgraph
   :alt: Driving function for the voltage clamp
   :align: center

   Driving function for the voltage clamp


.. figure:: ../../theory/images/tut7_mgraph.png
   :name: tut7_mgraph
   :alt: m-gate dynamics
   :align: center

   m-gate dynamics


.. figure:: ../../theory/images/tut7_hgraph.png
   :name: tut7_hgraph
   :alt: h-gate dynamics
   :align: center

   h-gate dynamics


.. figure:: ../../theory/images/tut7_Nacond_graph.png
   :name: tut7_Nacond_graph
   :alt: Sodium conductance
   :align: center

   Sodium conductance


.. figure:: ../../theory/images/tut7_iNagraph.png
   :name: tut7_Naigraph
   :alt: Sodium current
   :align: center

   Sodium current
