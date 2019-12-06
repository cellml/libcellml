..  _tutorial5_cpp:

=============================================
Tutorial 5 C++: Modelling a gated ion channel
=============================================

If you're reading this it's presumed that you're already
comfortable with the serlialisation, mainipulation, and debugging functionality
available in the libCellML library.  If not, please see the earlier tutorials
which introduce these issues:

- :ref:`Tutorial 1: Reading and writing a CellML file <tutorial1_cpp>`
- :ref:`Tutorial 2: Debugging, error checking, and validation<tutorial2_cpp>`
- :ref:`Tutorial 3: Creating a model using the API<tutorial3_cpp>`

From this point onwards the tutorials will build on work done in the previous
ones.  If you need to jump in at some intermediate stage
you will find all the files created by the earlier tutorials in the
:code:`resources` folder.

.. contents:: Contents
    :local:

Overview
=========
The basic steps for model creation and output are the same as those in
:ref:`Tutorial 3<tutorial3_cpp>`, but here you'll begin to create a model based on
the Hodgkin Huxley model. All the biological and mathematical modelling
background needed for this model are explained in a separate document,
:ref:`Understanding the Hodgkin-Huxley model<hh_background>`.

#.  Create a simple model with one component.  This will represent a gated
    ion channel, and we'll write it in such a way that we can reuse it later.
#.  Add mathematics to the component.  This includes writing MathML code as a
    string and adding it to the component.
#.  Because the maths defined above will need variables, we'll need to add
    these to the component as well.
#.  Because the quantities modelled have units, we will define what these are,
    and make sure that they are included in the model too.

As always, the steps discussed here are mirrored by the comments in the code
files attached.  You can choose to either create your own code from the
structure given in the :code:`tutorial5.cpp` file, or to simply read the
finished code given in the :code:`tutorial5_complete.cpp` file.

1: Create the model and component items
=======================================
Following the same procedures as in previous tutorials, our first step is to
create new model and component instances.  We haven't encountered it yet, but
the real power of modelling comes from our ability to use and reuse different
items, combining them into more and more complicated situations.  In this case,
we're going to create a component which represents a generic gated ion channel;
it will be reused later on to represent channels for sodium and potassium in
neuron models, or calcium in a cardiac model.  There's an introduction to the
biological and mathematical theory behind this particular model in
:ref:`Understanding the Hodgkin-Huxley model<hh_background>`.

.. container:: dothis

    **1.a**
    Create a model instance, and name it appropriately.

.. container:: dothis

    **1.b**
    Create a component, name it, and add the component to the model.

.. container:: dothis

    **1.c**
    Create a validator and use it to verify that your model has no errors.

2: Define the mathematical behaviour
====================================
The next step is to define what the component actually *does*.  In this case,
its purpose is to represent a collection of gates in series in order to model
the channel behaviour.  Let's start with the simple ODE below:

.. math::
    \frac{dm}{dt} = \alpha_m (1-m) - \beta_m m

where :math:`m` is the fraction which is open (so :math:`(1-m)` must
be the fraction which is closed), :math:`\alpha_m` is the opening
rate, :math:`\beta_m` is the closing rate, and :math:`t` is time.

Now to add this equation into the component we created in Step 1.
Once the maths is created, the process of adding it is very simple, and follows
the same pattern as adding anything to anything else: there is a `setMath`
command which which does the job nicely.  The more difficult part is creating
the maths itself.  This was covered in :ref:`Tutorial 3<tutorial3_cpp>` and there
are other resources on the :mathml2:`W3 resource pages for MathML2 <>` too.

Consider the equation above, converted here into MathML2 format:

Left hand side: :math:`\frac{dm}{dt}`

.. code-block:: xml

            <apply>
                <diff/>
                <bvar>
                    <ci>time</ci>
                </bvar>
                <ci>m</ci>
            </apply>

Right hand side: :math:`\alpha_m (1-m) ...`

.. code-block:: xml

            <apply>
                <minus/>
                <apply>
                    <times/>
                    <ci>alpha_m</ci>
                    <apply>
                        <minus/>
                        <cn cellml:units="dimensionless">1</cn>
                        <ci>m</ci>
                    </apply>
                </apply>

:math:`... - \beta_m m`  **NB** The negative comes from the first :code:`minus`
operation in the block above, indicating that the block below subtracted
from the one above.

.. code-block:: xml

                <apply>
                    <times/>
                    <ci>beta_m</ci>
                    <ci>m</ci>
                </apply>
            </apply>

All of this needs to be wrapped inside the :code:`<math>` tags, which will
include a namespace definition, as well as the initial :code:`<apply>` and
:code:`<eq/>` tags to assign the left and right-hand sides of the equation:

.. code-block:: xml

    <math xmlns="http://www.w3.org/1998/Math/MathML"
            cellml="http://www.cellml.org/cellml/2.0#">
        <apply>
            <eq/>
                ...
        </apply>
    </math>


.. container:: nb

    **libCellML will only take MathML2 format**, and **not** the more recent
    MathML3 or MathML4 formats, which are targetted at presentation rather
    than content alone.

.. container:: dothis

    **2.a** Create the MathML string(s) representing the following equations:

.. math::
    \frac{dn}{dt} = \alpha_n (1-n) - \beta_n n

    i_K = g_K . n^{\gamma} . (V-E_K)

... where :math:`\alpha_K` and :math:`\beta_K` are the rate constants for the
opening and closing of the gate, :math:`g_K` is the open channel conductance,
:math:`n` is the fraction of open gates, and :math:`\gamma` is the number of
gates which exist in series in the channel, :math:`V` is the transmembrane
voltage, and :math:`i_K` is the current flow through the channel.

Three functions are available for accessing and editing the math block, these
are:

- :code:`setMath(input)` replaces the existing Math string with the `input`
  string
- :code:`appendMath(input)` adds the `input` string to the existing Math string
- :code:`math()` returns the stored Math string

.. container:: nb

    **Note** that there is only one MathML block stored per component. Even if
    there is more than one equation, they're all stored as one single
    concatenated string.

.. container:: dothis

    **2.b** Use the manipulation functions listed above to add your string(s)
    to the component you created in 1.a.

.. container:: dothis

    **2.c** Submit your model to the validator.  Expected errors at this stage
    will be similar to those below, relating to not yet defined variables and
    units:

.. code-block:: terminal

     Description: MathML ci element has the child text 'alpha_n' which does not
        correspond with any variable names present in component
        'HodgkinHuxleySingleIonChannel' and is not a variable defined within a bvar
        element.
     Description: Math has a cn element with a cellml:units attribute
        'per_millivolt_millisecond' that is not a valid reference to units in
        component 'HodgkinHuxleySingleIonChannel' or a standard unit.


3. Define the variables and their units
=======================================
Now that the mathematical behaviour is defined, the variables that have been
used also need to be defined.  Each variable needs a name which is equal to the
term inside the :code:`<ci>` tags in the MathML, as well as units defined in
the model.

.. container:: dothis

    **3.a** Use the validator output or the MathML you've written to determine
    the variables which you'll need to declare.  These must be created, named, and
    added to the component.  Need help? See :ref:`Tutorial 2<tutorial2_cpp>`.

.. container:: nb

    **Note** Remember that the names you give the variables in this step must be
    the same as the names used between the :code:`<ci>` tags inside your MathML
    string.

As well as a name and a parent component, each variable needs :code:`Units`.
These are specified using the :code:`setUnits` function for a variable, just
as you did in :ref:`Tutorial 3<tutorial3_cpp>`.  The units you'll need here are:

- time, :math:`t`, has units of :code:`millisecond`
- voltage, :math:`V`, has units of :code:`millivolt`
- opening rate, :math:`\alpha_m` has units :code:`per_millisecond`
- closing rate, :math:`\beta_m` has units :code:`per_millisecond`

.. container:: dothis

    **3.b** For each of the variables created in 3.a, use the
    :code:`setUnits(name)` function to add the units you'll need.

Even though the final variable in our equations has no units, CellML2 requires
every variable to have some defined.  For the proportion of open gates
:math:`m` use the units name :code:`dimensionless`.

.. container:: dothis

    **3.c** Submit your model to the validator.  Expected errors at this stage
    will be similar to those below.

.. code-block:: terminal

     - Description: Variable 'time' has an invalid units reference 'millisecond'
       that does not correspond with a standard unit or units in the variable's
       parent component or model. See section 11.1.1.2 in the CellML specification.
     - Description: Math has a cn element with a cellml:units attribute 'millivolt'
       that is not a valid reference to units in component
       'HodgkinHuxleySingleIonChannel' or a standard unit.

4. Define the units and add to the model
========================================
The variables created above referenced unit names of :code:`millisecond`,
:code:`millivolt`, :code:`per_millisecond`, and :code:`dimensionless`.  The
:code:`dimensionless` units are already present, so we don't need to take any
other action, but the other three need to be created and added.  This was
covered in :ref:`Tutorial 3<tutorial3_cpp>` in case you need a reminder.

.. container:: dothis

    **4.a** Create the three units you need for this component, name, and define
    them.

.. container:: dothis

    **4.b** Check the units related to constants (that is, the :code:`<cn>`
    blocks) in the maths.  These units also need to be defined in the same way
    and added to the model.

.. container:: dothis

    **4.c** Add all the new units into the model. Adding units to the model
    allows other components (when you have them!) to use them as well.

.. container:: dothis

    **4.d** Validate the final model configuration.  There should be no errors
    at this stage.  If you do encounter any, you can compare the code you've
    created to that provided in the
    :code:`resources/tutorial5/tutorial5_complete.cpp` file.

5: Serialise and write to a file
================================
The final steps are to output our created model to a CellML2.0 file (which
will be used in subsequent tutorials, so be sure to name it something
meaningful!) as well as generating the C or Python files which we can use to
investigate this component's operation in isolation.  We will do the code
generation step first to take advantage of the additional error checks present
inside the :code:`Generator`.

.. container:: dothis

    **5.a** Create a :code:`Generator` item, set the profile (that is, the output
    language) to your choice of C (the default) or Python (see below), and
    then submit the model for processing.

.. code-block:: cpp

    // Change the generated language from the default C to Python if need be
    libcellml::GeneratorProfilePtr profile =
        libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);

.. container:: dothis

    **5.b** Check that the :code:`Generator` has not encountered any errors.

.. container:: dothis

    **5.c** Retrieve the output code from the :code:`Generator`, remembering
    that for output in C you will need both the :code:`interfaceCode` (the
    header file contents) as well as the :code:`implementationCode` (the source
    file contents), whereas for Python you need only output the
    :code:`implementationCode`.  Write the file(s).

The second step is the
same as what was covered at the end of :ref:`Tutorial 2<tutorial2_cpp>` to use
the :code:`Printer`; you can refer back to the code and/or instructions there
if you need to.

.. container:: dothis

    **5.d** Create a :code:`Printer` item and submit your model for serialisation.

.. container:: dothis

    **5.e** Write the serialised string output from the printer to a file.

.. container:: dothis

    **5.f** Check that your files have been written correctly.  You should have
    both the generated files (either *.c/h or *.py) as well as the *.cellml
    file.  If they're present and correct, then go and have a cuppa, you're
    done!
