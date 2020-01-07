.. _tutorial8_py:

====================================================================
Tutorial 8 Python: Encapsulating components and working with parents
====================================================================

The outline for this tutorial is shown on the :ref:`Tutorial 8<tutorial8>`
page. These are the Python instructions.  For the same tutorial in C++
please see the :ref:`Tutorial 8 in C++<tutorial8_cpp>` page instead.

Resources:

    - :download:`tutorial8.py` Either the skeleton code, or ..
    - :download:`tutorial8_complete.cpp` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py`  Utility functions for
      use in the tutorials.
    - :download:`../resources/tutorial8_LeakageCurrentModel.cellml` The leakage current model
    - If you did not complete Tutorial 7 you can download the file created there:
      :download:`../resources/tutorial8_MembraneModel.cellml`

.. contents:: Contents
    :local:


0: Setup
====================================================================
We'll start by creating the utilities that we'll use later on.

.. container:: dothis

    **0.a** As previously, create:

    - a :code:`Parser` instance to deserialise the models
    - a :code:`Validator` instance for debugging purposes
    - a :code:`Model` model to attach everything into

1: Read the membrane component
====================================================================

.. container:: dothis

    **1.a** Just as you did in :ref:`Tutorial 6<tutorial6_py>` TODO CHECK for the potassium
    channel, parse the :code:`tutorial8_MembraneModel.cellml` file and save the
    deserialised model to a new model instance (*not* the one you've already
    created above - a new one). If you'd like, use the
    :code:`print_model_to_terminal` utility function to check it has been read
    correctly, and the validator to make sure that it is valid on its own.

At this stage you will have two :code:`Model` items - an empty one you
created in earlier which will become the combined model,
and the one you've just read from the file.

.. container:: dothis

    **1.b** Since you'll want to reuse the membrane component from the imported
    potassium channel model within your combined model, you need to retrieve it
    from the imported model and add it to the combined one.  Note that you will
    need to retrieve the membrane component from the model and use the
    :code:`clearParent()` function to detach it from
    the membrane model *before* you add it to your combined model.

.. container:: nb

    **Note** that the :code:`addComponent` and :code:`addVariable` functions
    have a built-in check which will prevent them from having one parent:

        - if a :code:`Variable` or :code:`Component` has a :code:`nullptr`
          parent, then calling an :code:`addComponent` or :code:`addVariable`
          function will insert that item into the parent component.
        - if a :code:`Variable` or :code:`Component` already has a
          :code:`parent()` component, then nothing will be changed.
        - if you need to move parent ownership of a variable or a component
          you need to first call the :code:`clearParent()` function **before**
          adding it to the new parent.

Before going much further it's probably a good idea to understand what it is
that you've just imported.  For a full description of the biological theory,
please see the :ref:`Hodgkin-Huxley background<hh_background>` document. You
should be able to see the variables and maths inside the imported component
by simply printing the combined model to the screen.

.. container:: dothis

    **1.c** Print the MathML2 string from the :code:`membrane`
    component in your combined model and check it represents the equations
    below.  You can check back to the earlier
    :ref:`Tutorial 5, step 2<tutorial5_py>` if need be.

.. math::

    i_{tot} = i_{stim} + i_{Na} + i_{K} + i_{L}

    \frac {dV} {dt} = \frac {-i_{tot}} {Cm}

.. container:: dothis

    **1.d** Call the validator to check the combined model.  At this stage we
    expect to see errors related to missing units: we have imported a component
    containing maths and variables, both of which reference units that we haven't
    yet included in the combined model:

.. code-block:: console

     The validator has found 13 errors!
     Validator error[0]:
       Description: Variable 'V' has an invalid units reference 'mV' that does not correspond
       with a standard unit or units in the variable's parent component or model.
       See section 11.1.1.2 in the CellML specification.

      ...

     Validator error[8]:
       Description: Math has a cn element with a cellml:units attribute 'microA_per_cm2' that
       is not a valid reference to units in the model 'Tutorial8_HHModel' or a standard unit.

.. container:: dothis

    **1.e** Use a loop to import all of the units from the the potassium
    channel model into the combined model.

.. container:: dothis

    **1.f** Validate the combined model once more and check that it is now free
    of errors.

2: Read the sodium channel component
====================================================================
In :ref:`Tutorial 7<tutorial7_py>` you created a component to represent the
behaviour of a gated sodium gate and stored it inside a model.

.. container:: dothis

    **2.a** As in step 1.a, retrieve the sodium channel *model* from the
    file you created in Tutorial 7, or use the
    :code:`resources/tutorial7_SodiumChannelModel.cellml` file.

.. container:: dothis

    **2.b** As in step 1.b, retrieve the sodium channel *component* and add it to
    the membrane component created in step 1.  Remember to clear its parent first!
    Print the combined model to the terminal using the condensed function
    :code:`print_encapsulation_structure_to_terminal` and notice that the "child"
    components encapsulated by the sodium channel component - the :code:`mGate`
    and :code:`hGate` components - are imported as well.

.. code-block:: console

     Model 'Tutorial8_HHModel' has 1 components
      - Component 'membrane' has 1 child components
         - Component 'sodiumChannel' has 2 child components
            - Component 'mGate' has 0 child components
            - Component 'hGate' has 0 child components


.. container:: dothis

    **2.c** Call the validator to check the combined model so far.  At this
    stage we expect to see two kinds of errors:

    - errors related to units missing from the combined model, as before.
    - **TODO** errors related to the equivalent variables connections between the
      sodium channel component (which is now in the combined model) and the
      environment component (which is still in the sodium channel *model*).  Since
      the components are no longer adjacent in the encapsulation hierarchy, they
      cannot be connected.

.. container:: dothis

    **2.d** Import the missing units into the combined model from the sodium
    channel model.  Revalidate the combined model and pay attention to errors
    related to the units.

.. container:: nb

    **Note** that you cannot have units with duplicate names in a model: if
    you have simply imported *all* of the units from the
    sodium channel model, then there will be double-ups.  You can use
    the :code:`model.hasUnits` function to check whether a :code:`Units` item
    with the same name already exists in a model before importing it.

After validation you should see that there are no more errors
related to units, but you will still need to address the illegal connections
between variables in the newly-moved sodium channel *component* and the old
environment component in the sodium channel *model*.

.. code-block:: console

    **PUT ERRORS HERE WHEN VALIDATOR IS WORKING**

Recall the idiom you used in :ref:`Tutorial 5<tutorial6_py>` to create the
connections between equivalent variables; the same can be done in reverse
here to *remove* the equivalence between two variables:

.. code-block:: python

    # Retrieving the pointers to the variables via their names and removing an equivalence
    libcellml.Variable.removeEquivalence(
        sodium_channel_model.component("environment").variable("t"),
        sodium_channel.variable("t")
    )

.. container:: dothis

    **2.e** Disconnect any equivalences between variables in the
    environment component of the
    sodium channel *model*, from those inside the newly-moved
    sodium channel *component* in the combined model.

.. container:: dothis

    **2.f** Validate the combined model to see that it is now free of errors.

3: Import the potassium channel component
====================================================================
Now we simply need to repeat the same process for our potassium channel
component and add it to the combined model.

.. container:: dothis

    **3.a-b** Repeat the process above to import the potassium channel
    component that was created in :ref:`Tutorial 5<tutorial6_py>` into the
    membrane component.  Note that if you did not complete that tutorial
    you can simply copy the
    :code:`resources/tutorial6_PotassiumComponentModel.cellml` file.

.. container:: dothis

    **3.c** Use the validator to alert you to the errors at this stage.

If you have used the files provided in the :code:`resources` folder, you
can expect to see errors at this point relating to missing units.
This is because even though both the sodium and potassium channel components
require the same set of units, each of them has used different names for them;
for example, "millivolt" and "mV".  At this stage you have a choice:

- either import all the units under their original names from the
  potassium channel as well,
- or rename the units throughout the potassium channel component's
  variables and maths.

Here we'll go with the latter to illustrate the process, and to create a more
compact model description.

.. container:: dothis

    **3.d**  Use the examples below to rename the units referenced by variables
    inside this component.  This is straightforward:

.. code-block:: python

    # Setting the names of units to be consistent with those in the combined model
    potassium_channel.variable("t").setUnits("ms")
    potassium_channel.component("nGate").variable("t").setUnits("ms")
    ... etc ...

You'll also need to replace the units of any constants in the
MathML blocks of the components as well.  This is not quite as
straightforward, but we've provided a utility function
:code:`switch_units_in_maths` which does a string replacement for
the unit names.  The function can be used like this:

.. code-block:: python

    # The switch_units_in_maths function's definition in tutorial_utilities.py:
    new_maths = switch_units_in_maths(old_maths, old_units, new_units)

    # Switch the name of the units referred to in a MathML string
    # Retrieve the MathML string from the component
    n_gate_maths = potassium_channel.component("nGate").math()

    # Switch the unit names in the string
    n_gate_maths = switch_units_in_maths(n_gate_maths, "millivolt", "mV")

    # Repeat for all units ...
    # Remember to add the corrected string back into the component when you're done

.. container:: nb

    **Note** that a simple string replacement for any and all occurrences of the :code:`in`
    string within the :code:`maths` string with the :code:`out` string could cause problems
    when the :code:`in` string is a substring of another unit name.  In order to be
    sure that **only** full name matches for units are replaced, we exploit
    the fact that the units names in the MathML string will be in quotation marks, and include
    :code:`"` blocks on either side of the :code:`in` and :code:`out`
    strings for safety.  **You will therefore need to substitute whole names only for this
    function to work.**

.. container:: dothis

    **3.e** Rename the units in the MathML strings as needed.  Remember
    that you'll need to re-add the corrected MathML string to the
    component when you're done:

.. code-block:: python

    potassium_channel.component("nGate").setMath(n_gate_maths)

.. code-block:: console

     Switched units 'millivolt' for units 'mV'
     Switched units 'millisecond' for units 'ms'
     Switched units 'per_millisecond' for units 'per_ms'
     Switched units 'per_millivolt_millisecond' for units 'per_mV_ms'
     Switched units 'milliS_per_cm2' for units 'mS_per_cm2'

.. container:: dothis

    **3.f** As you did in step 2.e, disconnect the variable equivalences which
    link the imported component to the old environment in the
    potassium channel model, and validate that the combined model
    is now free of errors.

4: Read the current leakage component
====================================================================

.. container:: dothis

    **4.a** If you know the tune, sing along!  Import the leakage component
    from the model in :code:`resources/tutorial8_LeakageModel.cellml`
    and add it to the :code:`membrane` component.  Use the validator to debug
    and make any adjustments you need to until your combined model is free of
    errors.

5: Create the environment component
====================================================================
Now your model should have the encapsulation structure shown below.  You can
check this in the same way as you did in step 2.b.

.. code-block:: console

     Model 'Tutorial8_HHModel' has 1 components
     - Component 'membrane' has 3 child components
      - Component 'sodiumChannel' has 2 child components
          - Component 'mGate' has 0 child components
          - Component 'hGate' has 0 child components
      - Component 'potassiumChannel' has 1 child components
          - Component 'nGate' has 0 child components
      - Component 'leakageCurrent' has 0 child components


The final component you need to add is an :code:`environment` component for
this combined model.  This contains the time :math:`t` of
the simulation as well as the membrane voltage :math:`V`.

.. container:: dothis

    **5.a** Create a new :code:`Component` to represent the environment,
    and add it to your combined model as a top-level component.

    **5.b** Include the local environment variables that you'll need, including
    their units, and validate that your model is free of errors.

6: Connect the equivalent variables
====================================================================
The encapsulation structure for this model has several tiers, as shown in the
diagram below:

.. code-block:: text

    ____ HodgkinHuxleyModel
            |
            |____ environment (V, t)
            |
            |____ membrane (V, t)
                    |
                    |____ sodiumChannel (V, t, h, m)
                    |       |
                    |       |____ hGate (h, V, t)
                    |       |
                    |       |____ mGate (m, V, t)
                    |
                    |____ potassiumChannel (n, V, t)
                    |       |
                    |       |____ nGate (n, V, t)
                    |
                    |____ leakageCurrent (V)


The encapsulation structure above includes the variables in each component
which are shared with an adjacent component.

.. container:: dothis

    **6.a** Set the equivalent variables according to the diagram above.  Note
    that the gates remain connected to the sodium and potassium channels and don't
    need to be added again.

.. container:: dothis

    **6.b** Using the same interface type rules as in :ref:`Tutorial 7<tutorial7_py>`,
    set the interface type for the missing interfaces.

.. container:: dothis

    **6.c** Validate that the final model is free of errors.

7: Define the driving function
====================================================================
In contrast to earlier tutorials, this simulation will not be a voltage clamp
experiment, but will model instead the response to a stimulus current in the
membrane. You've already got some maths inside the :code:`membrane`
component which you imported in step 1.b which defined the influence of the
total membrane current :math:`i_{tot}` on the voltage, :math:`V`.  It also
defined the total current as the sum of currents in the potassium channel
:math:`i_K`, the sodium channel :math:`i_{Na}`, the leakage current
:math:`i_L`, as well as an as-yet unused variable, the stimulus current
:math:`i_{stim}`.  To constrain the mathematics completely, you'll need to
add a definition for this stimulus current.

.. container:: dothis

    **7.a** Create a :mathml2:`MathML2 <>` equation to represent the stimulus
    current having a value of 100 mA/cm^2 between 1ms < t < 1.2ms and zero
    otherwise.

    **7.b** Because there is already a maths block (with
    :code:`<math>...</math>` tags at both ends) you can't just add new equation
    on the end of what's there - it needs to be added before the final
    :code:`</math>` tag.  There's a utility function to help with this which
    can be called using
    :code:`new_maths = insert_into_mathml_string(old_maths, maths_to_include)`

.. code-block:: python

    # Insert the new MathML string before the closing </math> tag
    membrane_math = membrane.math()
    membrane_math = insert_into_mathml_string(membrane_math, stimulus_math)
    # Remember to add the new maths back into your component as well ...

8: Output the model
====================================================================
Finally you're ready to write the model ready for simulation.  You know the
drill!
