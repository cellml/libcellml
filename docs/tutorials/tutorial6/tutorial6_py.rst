.. _tutorial6_py:

===================================================
Tutorial 6 Python: Working with multiple components
===================================================

The outline for this tutorial is shown on the :ref:`Tutorial 6<tutorial6>` page.
These are the Python instructions.
For the same tutorial in C++ please see the :ref:`Tutorial 6 in C++<tutorial6_cpp>` page instead.

You will need to download these files first:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial;
    - :download:`tutorial6.py` Either the skeleton code or :download:`tutorial6_complete.py` the completed tutorial code;
    - :download:`../utilities/tutorial_utilities.py` Utility functions for use in the tutorials; and
    - :download:`../resources/tutorial6_controller.cellml` A CellML file required for the controller and initialisation components.

.. contents:: Contents
    :local:

Setup
=====
Navigate into the :code:`tutorial6` folder and check that you can run the template against the libCellML library successfully:

Running the template:

.. code-block:: console

    python3 tutorial6.py

... should give the output of the section headings which you'll complete here:

.. code-block:: console

    ----------------------------------------------------------
       STEP 1: Define the potassiumChannel component
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 2: Create the nGate component
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 3: Connect the components together
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 4: Read the controller
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 5: Generate the model and output
    ----------------------------------------------------------

Step 1: Define the potassium channel component
==============================================
In :ref:`Tutorial 5<tutorial5_py>` we created a simple ion channel.
In this tutorial we're going to extend that a little by making its dynamics specific to potassium.
We also introduce voltage dependence into the alpha and beta gate rates, and move them into a separate component to make it cleaner.
This will be done in step 2.

.. container:: dothis

    **1.a** Create a model, name it appropriately.
    Create a new model to represent the potassium channel and add it to your model.

The operation of the potassium channel is similar to the generic ion channel in the previous tutorial, except that the gate rates will be calculated in another component.
The governing mathematical equation becomes:

.. math::

    i_K = n^4 g_K (V - E_K)

... where :math:`i_K` is blah blah.

.. container:: dothis

    **1.b** Add a MathML string representing this equation to your component.
    Remember that you will need to include the MathML opening and closing tags, and namespace.
    If you need to, copy the code underneath the "Show code" link below.

    .. container:: toggle

        .. container:: header

            Show code

        .. code-block:: python

            equation = \
                '  <apply><eq/>\n'\
                '    <ci>i_K</ci>\n'\
                '    <apply><times/>\n'\
                '       <apply><power/>\n'\
                '           <ci>n</ci>\n'\
                '           <cn cellml:units="dimensionless">4</cn>\n'\
                '       </apply>\n'\
                '       <ci>g_K</ci>\n'\
                '       <apply><minus/>\n'\
                '           <ci>V</ci>\n'\
                '           <ci>E_K</ci>\n'\
                '       </apply>\n'\
                '    </apply>\n'\
                '  </apply>\n'

.. container:: dothis

    **1.c** Create and call a Validator instance, and use it to check the model so far.
    At this stage we will expect errors related to missing variables.

.. code-block:: console

    The validator has found 5 errors!
    Validator error[0]:
        Description: MathML ci element has the child text 'i_K' which does not correspond with any variable names present in component 'potassiumChannel'.
    ...

.. container:: dothis

    **1.d** Create the variables, specify their units, and add them to the potassium channel component.
    You may notice that during the process of creating models using the API that you might need to create more than one :code:`Variable` instance with the symbol :code:`V` or :code:`t` (for example).
    The CellML2 specification says that you need to have variable names which are unique within the scope of the *component* in which they're contained, not the entire model.
    In Python you can mimic this using the :code:`if True:` idiom block around your :code:`Variable` definitions: this will make your code easier to follow.

    .. code-block:: python

        # Using the if True: block around the code means that your definition of V here is
        # separate from any others in other components.
        if True:
            V = Variable()
            V.setName("V")
            V.setUnits("millivolt")
            potassiumChannel.addVariable(V)
            # ... etc ...


.. container:: dothis

    **1.e** Use the validator to recheck the model again.
    You can now expect errors related to missing units.

.. code-block:: console

    The validator has found 5 errors!
    Validator error[0]:
        Description: Variable 'E_K' in component 'potassiumChannel' has a units reference
        'millivolt' which is neither standard nor defined in the parent model.
        See section 11.1.1.2 in the CellML specification.

.. container:: dothis

    **1.f** Create and add the missing units.
    This was covered in :code:`Tutorial 5<tutorial5_py>` in case you need a recap.
    Since at the time that the units were specified for the variables, the related :code:`Units` items didn't exist, we also have to link the units in the model properly.
    Use the :code:`Model.linkUnits()` function to do this.

.. container:: dothis

    **1.g** Revalidate the model and check that it is now free of errors.

Step 2: Create the n-gate component
===================================
Here we create the voltage dependency behavior of the potassium component.
This is accomplished by creating a second component, and embedding it within the one we already have.

.. container:: dothis

    **2.a** Create a new component to represent the n-gate, and add it to the potassium channel component.
    Adding it to the component instead of the model creates an encapsulation hierarchy, which affects which components have access to each other.
    It also means that if the potassium channel component is moved or imported somewhere else, then the n-gate child component will be included too.

Now it's time to define the mathematical behaviour of the voltage dependence.
This is give by a differential equation for :math:`n`, the gate status, and by the expressions for voltage control

Next we need to define this new dependency of the :math:`\alpha` and
:math:`\beta` rate constants on the voltage.  The mathematics for this is:

.. math::

    \alpha_n = \frac {0.01(V+10)} {\exp(0.1(V+10))-1}

    \beta_n = 0.125 \exp(0.0125V)

    \frac {dn} {dt} = \alpha_n(1-n) - \beta_n n

.. container:: dothis

    **2.b** Create the appropriate MathML to represent the equations above, and
    add to the n-gate component.
    If needed, you can copy the equation strings from the "Show MathML" block below.
    Validate the model.
    At this stage you can expect errors related to missing variables, and missing errors defined in the constants.

    .. container:: toggle

        .. container:: header

            Show MathML

        .. code-block:: python

            equation1 = \
                '  <apply><eq/>\n'\
                '    <apply><diff/>\n'\
                '      <bvar><ci>t</ci></bvar>\n'\
                '      <ci>n</ci>\n'\
                '    </apply>\n'\
                '    <apply><minus/>\n'\
                '      <apply><times/>\n'\
                '        <ci>alpha_n</ci>\n'\
                '        <apply><minus/>\n'\
                '          <cn cellml:units="dimensionless">1</cn>\n'\
                '          <ci>n</ci>\n'\
                '        </apply>\n'\
                '      </apply>\n'\
                '      <apply><times/>\n'\
                '        <ci>beta_n</ci>\n'\
                '        <ci>n</ci>\n'\
                '      </apply>\n'\
                '    </apply>\n'\
                '  </apply>\n'

            equation2 = \
                '  <apply><eq/>\n'\
                '    <ci>alpha_n</ci>\n'\
                '    <apply><divide/>\n'\
                '      <apply><times/>\n'\
                '        <cn cellml:units="per_millivolt_millisecond">0.01</cn>\n'\
                '        <apply><plus/>\n'\
                '          <ci>V</ci>\n'\
                '          <cn cellml:units="millivolt">10</cn>\n'\
                '        </apply>\n'\
                '      </apply>\n'\
                '      <apply><minus/>\n'\
                '        <apply><exp/>\n'\
                '          <apply><divide/>\n'\
                '            <apply><plus/>\n'\
                '              <ci>V</ci>\n'\
                '              <cn cellml:units="millivolt">10</cn>\n'\
                '            </apply>\n'\
                '            <cn cellml:units="millivolt">10</cn>\n'\
                '          </apply>\n'\
                '        </apply>\n'\
                '        <cn cellml:units="dimensionless">1</cn>\n'\
                '      </apply>\n'\
                '    </apply>\n'\
                '  </apply>\n'

            equation3 = \
                '  <apply><eq/>\n'\
                '    <ci>beta_n</ci>\n'\
                '    <apply><times/>\n'\
                '      <cn cellml:units="per_millisecond">0.125</cn>\n'\
                '      <apply><exp/>\n'\
                '        <apply><divide/>\n'\
                '          <ci>V</ci>\n'\
                '          <cn cellml:units="millivolt">80</cn>\n'\
                '        </apply>\n'\
                '      </apply>\n'\
                '    </apply>\n'\
                '  </apply>\n'

.. code-block:: console

    The validator has found 13 errors!
        Validator error[0]:
            Description: MathML ci element has the child text 't' which does not correspond
            with any variable names present in component 'nGate'.

        ...

        Validator error[7]:
            Description: Math has a cn element with a cellml:units attribute
            'per_millivolt_millisecond' that is not a valid reference to units in the model
            'Tutorial6_PotassiumChannelModel' or a standard unit.

.. container:: dothis

    **2.c** Add the missing variables to the n-gate component, and specify their units.
    Validate your model again, this time expecting only errors relating to units.

.. code-block:: console

    The validator has found 4 errors!
    Validator error[0]:
        Description: Variable 'alpha_n' in component 'nGate' has a units reference
        'per_millisecond' which is neither standard nor defined in the parent model.
        See section 11.1.1.2 in the CellML specification.
    ...

.. container:: dothis

    **2.d** Create the missing units and add them to the model.
    Link the units of the model again, and recheck using the validator.
    Expect the model to be free of errors.

Step 3: Load the controller components
======================================
We introduce the idea of controller and initialisation components here to support the idea that the model (that is, the mathematics) is distinct from its parameters (that is, the numerical values of the variables).
It's a common modelling practice to need to run the same model (mathematics) using different parameters or initial conditions.
If the numerical values of those parameters and initial conditions are buried inside nested components deep in the encapsulation structure, then it becomes difficult to change them easily.
In this tutorial we parse and read an external model which contains a controller (for the time and voltage variables) and initialising components (for constant parameters in the potassium channel and n-gate components).
In :ref:`Tutorial 7<tutorial7_py>` we will use the :code:`import` functionality for the same purpose.

.. container:: dothis

    **3.a** Create a parser and use it to read the contents of the :code:`resources/tutorial6_controller.cellml` file into a temporary model.

.. container:: dothis

    **3.b** From the parsed model, retrieve the component named "controller" and add it to your model (that is, at the top level of the encapuslation hierarchy).
    Remember that you will need to use the :code:`removeParent()` function to detach it from the parsed model before adding.

.. container:: dothis

    **3.c** Repeat the process to retieve the component named "parameters" and add this at the top level of the model.

At this stage, you should have an arrangement like that shown below.

.. code::

    ─ model:
        ├─ component: controller
        ├─ component: parameters
        └─ component: potassium channel
            └─ component: n-gate

.. container:: dothis

    **3.d** Print the model to the screen to check that your component hierarchy matches what is shown above.
    Next, check the contents of the components that you have imported:
    - You should see that the controller component contains some mathematics for the voltage step function that we'll use to trigger the channel response.
    - The other component contains no maths, and is only there to give values to constants or initial values to variables.

.. container:: gotcha

    We demonstrate parsing external components here, and in the next tutorial will show importing them instead.
    The biggest difference between the two methods is that parsing reads *only* the component items and its children, whereas importing will *also* read any units that might be required.
    It is not visible in this example, but the distinction will become clear in the next tutorial.

.. container:: dothis

    **3.e** Link the model's units and revalidate.
    There should be no errors now.

Step 4: Connect the components together
=======================================
In order for components to be able to relate to one another, we have to define two things.
Firstly, the hierarchy in which they exist - this is called the *encapsulation* and determines which components are able to access others.
Each component is only visible to its direct parents, direct children, and siblings (those which share a direct parent).
Secondly, we need to define the way in which the varaibles within the component relate to those outside it.
This is done by creating *equivalent variables*.

We have already defined the encapsulation hierarchy by setting our components to be nested within other components in steps 2.a and 3.b-d.
We now need to define which variables can access each other, and how.
This is done by making variables in different components *equivalent* to one another:

.. code-block:: py

    # Making the firstVariable and secondVariable equivalent to each other
    Variable.addEquivalence(firstVariable, secondVariable)

In our model we have defined a controller component which is used to control all of the independent variables (time, voltage) during the simulation process.

.. container:: dothis

    **4.a** Use the addEquivalence functionality to match the time and voltage variables in the "controller" component with those in the other two.
    Note that if you have used the :code:`if True:` idiom to denote a limited scope for your variable definitions earlier, you will need to retrieve the variables from their components using their names, as they don't exist in the general scope of the code:

.. code-block:: cpp

    # Retrieve the pointers to the variables via their names and add an equivalence:
    Variable.addEquivalence(controller->variable("t"), nGate->variable("t"))

.. container:: dothis

    **4.b** Validate your model and print the errors to the terminal.
    You should see errors related to missing specification of interface types, and - if you followed the example above - also about invalid connections between the n-gate component and the controller and parameters components.

.. code-block:: console

    The validator has found 8 errors!
      ...
      Validator error[5]:
        Description: The equivalence between 't' in component 'nGate' and 't' in component 'controller' is invalid.
        Component 'nGate' and 'controller' are neither siblings nor in a parent/child relationship.

There are some restrictions on which variables can be connected.
Variables can only be made equivalent if they are in neighbouring components; that is, a direct parent, direct child, or sibling component (one with the same parent).
We can add these two variables into the potassium channel component as they are *sibling* components (their parent is the model):

.. code-block:: python

    # Valid: the potassiumChannel and nGate are parent and child:
    Variable.addEquivalence(potassiumChannel.variable("t"), nGate.variable("t"))

    # Valid: the controller and potassiumChannel are siblings:
    Variable.addEquivalence(controller.variable("t"), potassiumChannel.variable("t"))

... but we *cannot* make an equivalence between the :code:`t` variable in the
:code:`controller` component and the :code:`t` variable in the :code:`nGate` component, because that relationship is too distant.
Instead, we need to use the :code:`potassiumChannel` component as a go-between: it is a sibling of the :code:`controller` as well as a direct parent of the :code:`nGate`.

.. container:: dothis

    **4.c** Alter the equivalence arrangement you created in step 4.c so that the neighbouring component rule is followed.
    You will need to do this for the variables representing time :math:`t` and voltage :math:`V` between all components, and for the variable representing :math:`n` between the n-gate and parameters components.
    Validate your model again.
    You should now see validation messages only related to interfaces, as shown below.

.. code-block:: console

    Validator error[0]:
      Description: Variable 'E_K' in component 'potassiumChannel' has no
      interface type set. The interface type required is 'private'.
      ...
    Validator error[2]:
      Description: Variable 'V' in component 'potassiumChannel' has no
      interface type set. The interface type required is 'public'.
      ...
    Validator error[5]:
      Description: Variable 'n' in component 'nGate' has no interface type set.
      The interface type required is 'public_and_private'.

The errors above are caused by the need to specify explicitly the kind of equivalence relationship which is allowed for each variable.
The default is :code:`none`, which prevents any equivalent connections, hence the errors above.

Here's how to think about equivalent variable interface types.
Imagine a family of components such that the mother has two children.
The interface types between the variables in these components needs to be specified as follows:

- Between the siblings, the :code:`public` interface type.
  Siblings know everything about each other.
- Between the children and their mother, the :code:`public` interface for the children, but the :code:`private` interface for the mother.
  Parents can know everything about their children, but children do not know everything about their parents.
- A third option is included to enable more than one kind of relationship to a variable, the :code:`public_and_private` type.
  This is used where successive generations mean that a variable needs to be :code:`private` in one relationship and :code:`public` in another.
  An uncle (the mother's brother) and the mother have a sibling-type (ie: :code:`public`) interface, but the mother must keep a :code:`private` interface for her children too.

.. container:: dothis

    **4.d** Use the :code:`setInterfaceType` function for each of the shared variables to specify their avaiable interfaces using the recommendation from the error messages.

.. container:: dothis

    **4.e** Re-validate your model and confirm that it is now free of errors.

Step 5: Generate and output the model
=====================================

As you have done previously in :ref:`Tutorial 3<tutorial3_py>` and :ref:`Tutorial 5<tutorial5_py>`, it's now time to use the :code:`Generator` functionality to create a runnable version of your model.

.. container:: dothis

    **5.a** Create a :code:`Generator` instance and pass it the model for processing.
    Because we have used an equivalent variable relationship to initialise sets of equivalent variables, we should not see any errors relating to un-initialised or un-computed variables.
    Use the :code:`print_errors_to_terminal()` function with your generator as an argument, and confirm that there are no errors.

.. container:: dothis

    **5.b** Create a :code:`Printer` instance and use it to serialise the model.
    Write you serialised model to a :code:`*.cellml` file.

.. container:: dothis

    **5.c** Now we'll use the generator to create its default C code.
    Retrieve and write the interface code to a :code:`*.h` file.

.. container:: dothis

    **5.d** Retrieve and write the implementation code to a :code:`*.c` file.

.. container:: dothis

    **5.e** Change the generator's profile to Python and reprocess the model.

.. container:: dothis

    **5.f** Retrieve and write the implementation code to a :code:`*.py` file.

In the next section we'll run the simulation and look at the results.

Step 6: Running the simulation
==============================
Following the same approach as you've used in :ref:`Tutorial 4<tutorial4_py>` and :ref:`Tutorial 5<tutorial5_py>` it's now time to use the simple solver to run your simulation.

At this stage you should have some new files created:

- The CellML file of your model (this will be used in later tutorials as you work toward building the whole Hodgkin-Huxley model);
- The generated file for the Python profile; and
- the generated files for the C profile, the header and source files.

These last three files can be used in conjuction with a simple solver to model the behaviour of the potassium channel.
Because this tutorial is in Python we give instructions for the Python solver.
For the C++ solver please see :ref:`the C++ Tutorial 6 instructions<tutorial6_cpp>` or :ref:`the general solver instructions<solver>`.

.. container:: dothis

    **6.a** Navigate to the :code:`tutorials/solver` directory.

.. code-block:: console

  cd ../solver

.. container:: dothis

    **6.b**  Run the :code:`simpleSolver.py` script:.  To do this you'll need to enter:

        - :code:`-m` the path to the generated file to run, relative to the solver directory;
        - :code:`-dt` the step size for the integration variable to take; and
        - :code:`-n` the total number of steps to take.

.. code-block:: console

    python3 simplesolver.py -m path_and_filename_to_run -n number_of_steps -dt step_size

  .. code-block:: console

    python3 simplesolver.py -m ../tutorial6/tutorial6_PotassiumChannelModel.py -n 4000 -dt 0.01

The parameters read from the file, along with your command line arguments are printed to the terminal for checking, and the results of the simulation written to a tab-delimited file with the extension :code:`_solution.txt` after your base file name.
Plotting these results will give you behaviour as shown below.

.. figure:: /tutorials/images/tutorial6_voltage.png
   :name: tutorial6_voltage
   :alt: voltage step input
   :align: center

   Voltage clamp stimulus (:code:`V` versus :code:`t`).


.. figure:: /tutorials/images/tutorial6_ngate.png
   :name: tutorial6_ngate
   :alt: n-gate dynamics
   :align: center

   n-gate dynamics in response to voltage clamp stimulus (:code:`n` versus :code:`t`).


.. figure:: /tutorials/images/tutorial6_K_conductance.png
   :name: tutorial6_K_conductance
   :alt: Potassium channel conductance
   :align: center

   Potassium channel conductance (:code:`g_K` versus :code:`t`).


.. figure:: /tutorials/images/tutorial6_current.png
   :name: tutorial6_current
   :alt: Potassium channel current
   :align: center

   Potassium channel current (:code:`i_K` versus :code:`t`).


.. container:: dothis

    **6.c** Go and have a cuppa, you're done!
