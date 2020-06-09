..  _tutorial5_py:

================================================
Tutorial 5 Python: Modelling a gated ion channel
================================================

If you're reading this it's presumed that you're already comfortable with the serlialisation, mainipulation, and debugging functionality available in the libCellML library.
If not, please see the earlier tutorials which introduce these issues:

- :ref:`Tutorial 1: Reading, writing, and 'rithmetic in a CellML file
  <tutorial1_py>`
- :ref:`Tutorial 2: Debugging, error checking, and validation<tutorial2_py>`
- :ref:`Tutorial 3: Creating a model using the API<tutorial3_py>`

From this point onwards the tutorials will build on work done in the previous ones.
If you need to jump in at some intermediate stage you will find all the files created by the earlier tutorials in the :code:`resources` folder.

.. contents:: Contents
    :local:

Overview
========
The basic steps for model creation and output are the same as those in :ref:`Tutorial 3<tutorial3_py>`, but here you'll begin to create a model based on the Hodgkin Huxley model.
All the biological and mathematical modelling background needed for this model are explained in a separate document, :ref:`Understanding the Hodgkin-Huxley model<hh_background>`.

#.  Create a simple model with one component.
    This will represent a gated ion channel, and we'll write it in such a way that we can reuse it later.
#.  Add mathematics to the component.
    This includes writing MathML code as a string and adding it to the component.
#.  Because the maths defined above will need variables, we'll need to add these to the component as well.
#.  Because the quantities modelled have units, we will define what these are, and make sure that they are included in the model too.

As always, the steps discussed here are mirrored by the comments in the code files attached.
You can choose to either create your own code from the structure given in the :code:`tutorial5.py` file, or to simply read the finished code given in the :code:`tutorial5_complete.py` file.

Step 1: Create the model and component items
============================================
Following the same procedures as in previous tutorials, our first step is to create new model and component instances.
We haven't encountered it yet, but the real power of modelling comes from our ability to use and reuse different items, combining them into more and more complicated situations.
In this case, we're going to create a component which represents a generic gated ion channel; it will be reused later on to represent channels for sodium and potassium in neuron models, or calcium in a cardiac model.
There's an introduction to the biological and mathematical theory behind this particular model in :ref:`Understanding the Hodgkin-Huxley model<hh_background>`.

.. container:: dothis

    **1.a** Create a model instance, and name it appropriately.

.. container:: dothis

    **1.b** Create a component, name it, and add the component to the model.

.. container:: dothis

    **1.c** Create a validator and use it to verify that your model has no errors.

Step 2: Define the mathematical behaviour
=========================================
The next step is to define what the component actually *does*.
In this case, its purpose is to represent a collection of gates in series in order to model the channel behaviour.
Let's start with the simple ODE below:

.. math::
    \frac{dn}{dt} = \alpha_y (1-y) - \beta_y y

where :math:`y` is the fraction which is open (so :math:`(1-y)` must be the fraction which is closed), :math:`\alpha_y` is the opening rate, :math:`\beta_y` is the closing rate, and :math:`t` is time.

Now to add this equation into the component we created in Step 1.
Once the maths is created, the process of adding it is very simple, and follows the same pattern as adding anything to anything else: there is a :code:`setMath` command which which does the job nicely.
The more difficult part is creating the maths itself.
This was covered in :ref:`Tutorial 3<tutorial3_py>` and there are other resources on the :mathml2help:`W3 resource pages for MathML2 <>` too.

Consider the equation above, converted here into MathML2 format:

Left hand side: :math:`\frac{dn}{dt}`

.. code-block:: xml

            <apply>
                <diff/>
                <bvar>
                    <ci>time</ci>
                </bvar>
                <ci>y</ci>
            </apply>

Right hand side: :math:`\alpha_y (1-y) ...`

.. code-block:: xml

            <apply>
                <minus/>
                <apply>
                    <times/>
                    <ci>alpha_y</ci>
                    <apply>
                        <minus/>
                        <cn cellml:units="dimensionless">1</cn>
                        <ci>y</ci>
                    </apply>
                </apply>

:math:`... - \beta_y y`

**NB** The negative comes from the first :code:`minus` operation in the block above, indicating that the block below subtracted from the one above.

.. code-block:: xml

                <apply>
                    <times/>
                    <ci>beta_y</ci>
                    <ci>y</ci>
                </apply>
            </apply>

All of this needs to be wrapped inside the :code:`<math>` tags, which will include a namespace definition, as well as the initial :code:`<apply>` and :code:`<eq/>` tags to assign the left and right-hand sides of the equation:

.. code-block:: xml

    <math xmlns="http://www.w3.org/1998/Math/MathML"
            cellml="http://www.cellml.org/cellml/2.0#">
        <apply>
            <eq/>
                ...
        </apply>
    </math>


.. container:: gotcha

    **Note**:
    **libCellML will only take MathML2 format**, and **not** the more recent MathML3 or MathML4 formats, which are targetted at presentation rather than content alone.

To proceed with this tutorial you can either write your own MathML strings, or copy them from the code provided under the "See MathML" links below.

.. container:: dothis

    **2.a** Create the MathML string(s) representing the following equations:

.. math::
    \frac{dn}{dt} = \alpha_y (1-y) - \beta_y y

    i_K = g_K . y^{\gamma} . (V-E_K)

... where :math:`\alpha_K` and :math:`\beta_K` are the rate constants for the opening and closing of the gate, :math:`g_K` is the open channel conductance, :math:`y` is the fraction of open gates, and :math:`\gamma` is the number of gates which exist in series in the channel, :math:`V` is the transmembrane voltage, and :math:`i_K` is the current flow through the channel.

.. container:: toggle

    .. container:: header

        See MathML string

    .. code-block:: python

            equation1 = \
                '  <apply><eq/>\n'\
                '    <apply><diff/>\n'\
                '      <bvar>\n'\
                '        <ci>t</ci>\n'\
                '      </bvar>\n'\
                '      <ci>y</ci>\n'\
                '    </apply>\n'\
                '    <apply><minus/>\n'\
                '      <apply><times/>\n'\
                '        <ci>alpha_y</ci>\n'\
                '        <apply><minus/>\n'\
                '          <cn cellml:units="dimensionless">1</cn>\n'\
                '          <ci>y</ci>\n'\
                '        </apply>\n'\
                '      </apply>\n'\
                '      <apply><times/>\n'\
                '        <ci>beta_y</ci>\n'\
                '        <ci>y</ci>\n'\
                '      </apply>\n'\
                '    </apply>\n'\
                '  </apply>\n'

            equation2 = \
                '  <apply><eq/>\n'\
                '    <ci>i_y</ci>\n'\
                '    <apply><times/>\n'\
                '      <ci>g_y</ci>\n'\
                '      <apply><minus/>\n'\
                '        <ci>V</ci>\n'\
                '        <ci>E_y</ci>\n'\
                '      </apply>\n'\
                '      <apply><power/>\n'\
                '        <ci>y</ci>\n'\
                '        <ci>gamma</ci>\n'\
                '      </apply>\n'\
                '    </apply>\n'\
                '  </apply>\n'

Three functions are available for accessing and editing the math block, these are:

- :code:`setMath(input)` replaces the existing MathML string with the :code:`input` string;
- :code:`appendMath(input)` adds the :code:`input` string to the existing MathML string; and
- :code:`math()` returns the stored MathML string.

.. container:: gotcha

    **Note** that there is only one MathML block stored per component.
    Even if there is more than one equation, they're all stored as one single concatenated string.

.. container:: dothis

    **2.b** Use the manipulation functions listed above to add your string(s) to the component you created in 1.a.

.. container:: dothis

    **2.c** Submit your model to the validator.
    Expected errors at this stage will be similar to those below, relating to not yet defined variables and units:

.. code-block:: console

     Description: MathML ci element has the child text 'alpha_y' which does not
        correspond with any variable names present in component
        'HodgkinHuxleySingleIonChannel' and is not a variable defined within a bvar
        element.
     Description: Math has a cn element with a cellml:units attribute
        'per_millivolt_millisecond' that is not a valid reference to units in
        component 'HodgkinHuxleySingleIonChannel' or a standard unit.

Step 3: Define the variables and their units
============================================
Now that the mathematical behaviour is defined, the variables that have been used also need to be defined.
Each variable needs a name which is equal to the term inside the :code:`<ci>` tags in the MathML, as well as units defined in the model.

.. container:: dothis

    **3.a** Use the validator output or the MathML you've written to determine the variables which you'll need to declare.
    For each you will need to create, name, and add it to the component.
    Need help? See :ref:`Tutorial 2<tutorial2_py>`.

.. container:: gotcha

    **Note** Remember that the names you give the variables in this step must be the same as the names used between the :code:`<ci>` tags inside your MathML string.

As well as a name and a parent component, each variable needs :code:`Units`.
These are specified using the :code:`setUnits` function for a variable, just as you did in :ref:`Tutorial 3<tutorial3_py>`.
The units you'll need here are:

- time, :math:`t`, has units of :code:`millisecond`;
- voltage, :math:`V`, has units of :code:`millivolt`;
- opening rate, :math:`\alpha_y` has units :code:`per_millisecond`; and
- closing rate, :math:`\beta_y` has units :code:`per_millisecond`.

.. container:: dothis

    **3.b** For each of the variables created in 3.a, use the :code:`setUnits(name)` function to add the units you'll need.

Even though the final variable in our equations has no units, CellML2 requires every variable to have some defined.
For the proportion of open gates :math:`y` use the units name :code:`dimensionless`.

.. container:: dothis

    **3.c** Submit your model to the validator.
    Expected errors at this stage will be similar to those below.

.. code-block:: console

     - Description: Variable 'time' has an invalid units reference 'millisecond'
       that does not correspond with a standard unit or units in the variable's
       parent component or model. See section 11.1.1.2 in the CellML specification.

     - Description: Math has a cn element with a cellml:units attribute 'millivolt'
       that is not a valid reference to units in component
       'HodgkinHuxleySingleIonChannel' or a standard unit.

Step 4: Define the units and add to the model
=============================================
The variables created above referenced unit names of :code:`millisecond`, :code:`millivolt`, :code:`per_millisecond`, and :code:`dimensionless`.
The :code:`dimensionless` units are already present, so we don't need to take any other action, but the other three need to be created and added.
This was covered in :ref:`Tutorial 3<tutorial3_py>` in case you need a reminder.

.. container:: dothis

    **4.a** Create the three units you need for this component, name, and define them.

.. container:: dothis

    **4.b** Check the units related to constants (that is, the :code:`<cn>` blocks) in the maths.
    These units also need to be defined in the same way and added to the model.

.. container:: dothis

    **4.c** Add all the new units into the model.
    Adding units to the model allows other components (when you have them!) to use them as well.

.. container:: dothis

    **4.d** Validate the final model configuration.
    There should be no errors at this stage.
    If you do encounter any, you can compare the code you've created to that provided in the :code:`resources/tutorials_complete/tutorial5_complete.py` file.

Step 5: Serialise and generate code
===================================
The final steps are to output our created model to a CellML2.0 file (which will be used in subsequent tutorials, so be sure to name it something meaningful!) as well as generating the C or Python files which we can use to investigate this component's operation in isolation.
We will do the code generation step first to take advantage of the additional error checks present inside the :code:`Generator`.

.. container:: dothis

    **5.a** Create a :code:`Generator` item, set the profile (that is, the output language) to your choice of C (the default) or Python (see below), and then submit the model for processing.

.. code-block:: python

    # Change the generated language from the default C to Python if need be.
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

.. container:: dothis

    **5.b** Check the :code:`Generator` for errors.
    At this stage you can expect errors related to non-initialised variables.
    Go back and set the following initial conditions:

    - :math:`V(t=0)=0`
    - :math:`y(t=0)=0`
    - :math:`E_K(t=0)=-85`
    - :math:`g_K(t=0)=36`
    - :math:`\gamma(t=0)=4`
    - :math:`\alpha_y(t=0)=1`
    - :math:`\beta_y(t=0)=2`

.. container:: dothis

    **5.c** Retrieve the output code from the :code:`Generator`, remembering that for output in C you will need both the code:`interfaceCode` (the header file contents) as well as the :code:`implementationCode` (the source file contents), whereas for Python you need only output the :code:`implementationCode`.
    Write the file(s).

The second step is the same as what was covered at the end of :ref:`Tutorial 2<tutorial2_py>` to use the :code:`Printer`; you can refer back to the code and/or instructions there if you need to.

.. container:: dothis

    **5.d** Create a :code:`Printer` item and submit your model for serialisation.

.. container:: dothis

    **5.e** Write the serialised string output from the printer to a CellML file.

.. container:: dothis

    **5.f** Check that your files have been written correctly.
    You should have both the generated files (either *.c/h or *.py) as well as the *.cellml file.

Step 6: Simulate the behavior of the gate
=========================================
At this stage you should have four new files created:

- The CellML file of your model: this will be used in later tutorials as you work toward building the whole Hodgkin-Huxley model;
- The generated file for the Python profile (an example for changing profiles only); and
- The generated files for the C profile, the header and source files.

These last three files can be used in conjuction with a simple solver to model the behaviour of this ion channel.
Because this tutorial is in Python we give instructions for the Python solver.
For the C++ solver please see :ref:`the C++ Tutorial 5 instructions<tutorial5_cpp>` or :ref:`the general solver instructions<solver>`.

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

Running your generated model for 50 steps with a step size of 0.1ms should give the output shown below.

.. code-block:: console

    python3 simplesolver.py -m ../tutorial5/tutorial5_IonChannelModel.py -n 50 -dt 0.1

    ====================================================================
    SIMPLE SOLVER: ../tutorial5/tutorial5_IonChannelModel
    --------------------------------------------------------------------

    VARIABLE OF INTEGRATION (units, stepsize)
    --------------------------------------------------------------------
        t (millisecond, 0.1)
        50 steps


    STATE VARIABLES (units, initial value)
    --------------------------------------------------------------------
        y (dimensionless, 0.0)


    VARIABLES (units, initial value)
    --------------------------------------------------------------------
        E_y (millivolt, -85.0)
        V (millivolt, 0.0)
        alpha_y (per_millisecond, 1.0)
        beta_y (per_millisecond, 2.0)
        g_y (milliS_per_cm2, 36.0)
        gamma (dimensionless, 4.0)
        i_K (microA_per_cm2, 0.0)


    SOLUTION written to ../tutorial5/tutorial5_IonChannelModel_solution.txt
    ====================================================================

Note that the solution is written to the same directory as the generated file, not the :code:`solver` directory (as for the C++ solver).  Plotting the solution gives :numref:`tutorial5_image`.

.. figure:: /tutorials/images/tutorial5_image.png
   :name: tutorial5_image
   :alt: Parameter behaviour for ion channel gate
   :align: center

   Behaviour of the current and ion channel status with time.
