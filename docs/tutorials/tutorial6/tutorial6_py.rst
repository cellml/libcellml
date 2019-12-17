.. _tutorial6_py:

===================================================
Tutorial 6 Python: Working with multiple components
===================================================

**TODO** The code doesn't match the instructions - waiting for the variable parent
issues to be sorted out.

The outline for this tutorial is shown on the :ref:`Tutorial 6<tutorial6>`
page. These are the Python instructions.  For the same tutorial in C++
please see the :ref:`Tutorial 6 in C++<tutorial6_cpp>` page instead.

Resources:

    - :download:`tutorial6.py` Either the skeleton code, or ..
    - :download:`tutorial6_complete.py` the completed tutorial code
    - :download:`../utilities/tutorial_utilities.py` Utility functions for
      use in the tutorials.
    - If you did not complete Tutorial 5 you can download the file created there:
      :download:`../resources/tutorial6_PotassiumChannelModel.cellml`

.. contents:: Contents
    :local:

1: Create the model
===================
By now you should be familiar and comfortable with using the API to create
the model instance, and normally that's how you'd start ... but not this time.
If you completed Tutorial 5 you will have created a model representing a
gated ion channel, serialised the model and written it to a file.  A good
idea for programming, modelling, and work in general is the DRY principle:
**Don't Repeat Yourself**.  With this in mind we want to be able to reuse the
work that's already done, and in particular, that useful ion channel that was
created in Tutorial 5.  There are four possible options:

- Option 0: Write it all again.  We're not going to do that. It's too WET
  (Write Every Time).
- Option 1: Copy the code you wrote in Tutorial 5 to create the component, and
  simply add it here.  This is not a great solution, because it's not as DRY as
  it could be, but it beats writing it all from scratch again.
- Option 2: Use the skills you learned in Tutorial 2 around parsing and
  deserialising a CellML model to read the model from the file which you
  created during Tutorial 5.  This option is DRY-er than Option 1, but will
  involve a tweak or two because the :code:`Parser` will only load the whole
  model, not just the bits we care about.
- Option 3: Instead of parsing and loading the entirety of the model from
  Tutorial 5, just tell libCellML to reference what it needs to.

Option 3 seems to be the DRYest, and indeed this is how we will do it later on
when the :code:`ImportSource` functionality is introduced.  For now though,
we'll just go with Option 2 since there's only one component inside the
Tutorial 5 model anyway.

.. container:: dothis

    **1.a** Create a :code:`Parser` instance and use it to deserialise the
    model from the file created in Tutorial 5 into a new model instance.
    This process was described in :ref:`Tutorial 2<tutorial2_py>`. You
    may like to copy that file into the working directory for this project for
    ease of access.  If you didn't do Tutorial 5 you can copy this file from
    the resource folder instead.

.. container:: dothis

    **1.b** Use the :code:`print_model_to_terminal` function to check that you
    have what you expect.

.. container:: dothis

    **1.c** Create a :code:`Validator` instance and check that your model is
    valid so far.

Now that we've loaded the model and checked that it's working, we want to
rename parts of it so that they make more sense going forward.  Use the
manipulation functionality you learnt in :ref:`Tutorial 3<tutorial3_py>` to
retrieve the following items from the model and rename them.  Recall that you
can access the items contained inside a model by index as well as by name.

.. container:: dothis

    **1.d** Retrieve the component from the model and rename it to
    "potassiumChannel".

2: Include more components in the model
=======================================
This tutorial is intended to illustrate the use of more than one component,
and how they're connected to each other.  Let's get started with creating two
additional components: one to represent the environment variables which will be
shared throughout the whole model, and one to represent details of a
gate.

.. container:: dothis

    **2.a** Create a new component and name it "environment"

.. container:: dothis

    **2.b** Create two new variables with the units below, and add them to the
    component.

    - V (millivolt)
    - t (millisecond)

.. container:: dothis

    **2.c** Add both new components to the model.

.. container:: dothis

    **2.d** Check that the model is valid so far using your validator instance.

3: Create a component for the n-gate
====================================
The last component that we need to create is an update from our Tutorial 5
model such that the rate constants :math:`\alpha` and :math:`\beta` become
functions of voltage.  We have another choice to make.  We could either:

- remove all the mathematics from our existing potassiumChannel component
  and adjust the equations which are already there to suit, or
- create another component to handle the voltage dependence, and pass its
  computed values to our existing component.

In a continuation of the DRY principle, we're going to go with the latter.

.. container:: dothis

    **3.a** Create a new component named "nGate", and to it add five
    new variables, which you'll also need to create:

    - :math:`V` (millivolt)
    - :math:`t` (millisecond)
    - :math:`n` (dimensionless)
    - :math:`\alpha_n` (per millisecond)
    - :math:`\beta_n` (per millisecond)

You may notice that during this process you've created more than one
:code:`Variable` instance with the symbol :code:`V` or :code:`t`.  The
CellML2 specification says that you need to have variable names which are
unique within the scope of the component in which they're contained.  In Python
you can mimic this using an :code:`if True:` block surruonding your variables.

**TODO Check whether this is a good plan or not ...**

Next we need to define this new dependency of the :math:`\alpha` and
:math:`\beta` rate constants on the voltage.  The mathematics for this is:

.. math::

    \alpha_n = \frac{0.01(V+10)}{\exp(0.1(V+10))-1}

    \beta_n = 0.125 \exp (0.0125 V)

    \frac {dn} {dt} = \alpha_n(1-n) - \beta_n n

.. container:: dothis

    **3.b** Create the appropriate MathML to represent the equations above, and
    add to the nGate component.  As in the previous tutorial, you
    can copy this from the file provided in the
    :code:`resources/tutorial6_mathml.py` file if you prefer.

.. container:: dothis

    **3.c** Add the nGate component into the model, and validate it.

During step 3.c your validation should have alerted you to a set of missing
units in the component.  These are not attached to a variable, but to a
constant inside the MathML, but still need to be present in the parent model.

.. container:: dothis

    **3.d** Create the missing units and add to the model.  Confirm that the
    model is now valid.

4: Connect the components to one another
========================================
In order for components to be able to relate to one another, we have to define
two things.  Firstly, the hierarchy in which they exist - this is called the
*encapsulation* and determines which components are able to access others. Each
component is only visible to its direct parents, direct children, and siblings
(those which share a direct parent).  Secondly, we need to define the way in
which the varaibles within the component relate to those outside it.  This is
done by creating *equivalent variables*.

.. container:: dothis

    **4.a** Create an encapsulation hierarchy for our three components.  In
    this tutorial, we need an arrangement such that:

    - the "environment" component stands alone as a child of the model.  We don't
      need to change anything there.
    - the "nGate" should exist entirely inside the
      "potassiumChannel" gate.  This hierarchy is created by adding the
      "nGate" component into the "potassiumChannel" component,
      *instead* of adding it to the model.  Because an item can only have one
      parent, we can remove the gate component from the model (we added it in step
      3.c) simply by adding it to the channel component now.  It will have its
      parent updated, and the model's children will be updated too.

.. code-block:: python

    potassiumChannel->addComponent(nGate);

.. container:: dothis

    **4.b** Print the model to the screen to check your component hierarchy.
    It should contain the section below where a *child component* is listed.

.. code-block:: terminal

     ...
        Component[0] has 1 child components:
            Component[0] has name: 'nGate'
            Component[0] has 5 variables:
            Variable[0] has name: 'V'
            Variable[0] has units: 'millivolt'
            Variable[1] has name: 't'
            Variable[1] has units: 'millisecond'
            Variable[2] has name: 'alpha_n'
            Variable[2] has units: 'per_millisecond'
            Variable[3] has name: 'beta_n'
            Variable[3] has units: 'per_millisecond'
            Variable[4] has name: 'n'
            Variable[4] has units: 'dimensionless'
     ...


After defining how the components are arranged, we need to define which
variables can access each other, and how.  This is done by making variables
in different components *equivalent* to one another:

.. code-block:: python

    # Making the first_variable and second_variable equivalent to each other
    libcellml.Variable.addEquivalence(first_variable, second_variable)

In our model we have defined an "environment" component which we'll use to
control all of the independent variables (time, voltage) during the simulation
process.

.. container:: dothis

    **4.c** Use the addEquivalence functionality to match the time and voltage
    variables in the "environment" component with those in the other two.  You
    will need to retrieve the variables from their components using their
    names, as they don't exist in the general scope of the code:

.. code-block:: python

    # Retrieving the pointers to the variables via their names and adding an equivalence
    libcellml.Variable.addEquivalence(environment.variable("t"), potassiumChannel.variable("t"));
    libcellml.Variable.addEquivalence(environment.variable("t"), nGate.variable("t"));

.. container:: dothis

    **4.d** Validate your model and print the errors to the terminal using the
    :code:`print_errors_to_terminal` function.  You should see an error
    similar to the one below.

.. code-block:: terminal

    **TODO** ?? put error here when the validation is working ??

There are some restrictions on which variables can be matched like this.
Variables can only be made equivalent if they are in *neighbouring* components;
that is, a direct parent, direct child, or sibling component (one with the same
parent).   We can add these two variables into the "potassiumChannel" component
as they are *sibling* components (their parent is the model):

.. code-block:: python

    libcellml.Variable.addEquivalence(time_in_environment, time_in_channel)

... but we *cannot* make an equivalence between the :code:`t` variable in the
:code:`environment` component and the :code:`t` variable in the :code:`nGate`
component, because that relationship is too distant.  Instead, we need to use
the :code:`potassiumChannel` component as a go-between: it is a sibling of the
:code:`environment` as well as a direct parent of the :code:`nGate`.

.. container:: dothis

    **4.e** Alter the equivalence arrangement you created in step 4.d so that
    the neighbouring component rule is followed.  You will need to do this for
    the variables representing time :math:`t` and voltage :math:`V` between all
    three components, and the gating variable :math:`n` between the :code:`nGate`
    and :code:`potassiumChannel` components.  Validate your model again.  You
    should see a validation message similar to that shown below.

.. code-block:: terminal

    **TODO Put error messages here when they're working**

The errors above are caused by the need to specify explicitly the kind of
equivalence relationship which is allowed for each variable.  The default
is :code:`none`, which prevents any equivalent connections, hence the error
above.

Here's how to think about equivalent variable interface types.  Imagine a
family of components such that the mother has two children.  The interface
types between the variables in these components needs to be specified as
follows:

- Between the siblings, the :code:`public` interface type.  Siblings know
  everything about each other.
- Between the children and their mother, the :code:`public` interface for
  the children, but the :code:`private` interface for the mother.  Parents
  can know everything about their children, but children do not know everything
  about their parents.
- A third option is included to enable more than one kind of relationship
  to a variable, the :code:`public_and_private` type.  This is used where
  successive generations mean that a variable needs to be :code:`private` in
  one relationship and :code:`public` in another.  An uncle (the mother's
  brother) and the mother have a sibling-type (ie: :code:`public`) interface,
  but the mother must keep a :code:`private` interface for her children too.

.. container:: dothis

    **4.f**  Use the :code:`setInterfaceType` function for each of the shared
    variables to specify their avaiable interfaces.  Re-validate your model and
    confirm that it is now free of errors.

5: Define the driving function
==============================
In order to give the simulation something to actually simulate, we need to add
a driving function as an input.  This simulation replicates a voltage clamp
experiment wherein the input voltage is given a square wave and the current
response measured, so we need to define the voltage in the
:code:`environment` component as a function of time.  (At this stage we'll use
the MathML markup as in previous tutorials, but in a future tutorial we'll
introduce the idea of Resets items as an alternative approach.)  The MathML
below shows how piecewise functions can be used to return the absolute value of
a given :math:`x` variable. The :code:`<otherwise>` statement is there as a
default, and can apply to more than one section of the axis.

.. code-block:: xml

    <piecewise>
        <piece>
            <apply><minus/><ci>x</ci></apply>
            <apply><lt/><ci>x</ci><cn>0</cn></apply>
        </piece>
        <piece>
            <cn>0</cn>
            <apply><eq/><ci>x</ci><cn>0</cn></apply>
        </piece>
        <otherwise>
            <ci>x</ci>
        </otherwise>
    </piecewise>

.. container:: dothis

    **5.a** Create a MathML string representing a step change such that the
    voltage variable is set to -85 millivolts between times of 5 and 15
    milliseconds, and 0 otherwise.  Remember that you will need to specify both
    the units as well as their namespace in each constant
    :code:`<cn cellml:units="yourUnitsHere">`, and to specify the CellML
    namespace itself in the maths header:

.. code-block:: xml

    <math xmlns="http://www.w3.org/1998/Math/MathML"
          xmlns:cellml="http://www.cellml.org/cellml/2.0#">

.. container:: dothis

    **5.b** Use the :code:`setMath` function to add your MathML string from
    5.a to the :code:`environment` component.

.. container:: dothis

    **5.c** Call the validator to check that your model is free of errors.

6: Serialise and print the model
================================

.. container:: dothis

    **6.a** As in :ref:`Tutorial 1<tutorial1_py>`, use the :code:`Printer` module
    to serialise the model, and then write it to a file.

.. container:: dothis

    **6.b** Go and have a cuppa, you're done!
