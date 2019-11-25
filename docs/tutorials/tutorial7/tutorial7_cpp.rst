.. _tutorial7:

------------------------------------------
Tutorial 7: Creating the sodium channel
------------------------------------------

This tutorial is a companion to Tutorial 5 which walked you through the
creation of a gated potassium channel model.  It follows the same basic recipe
steps as previously, but provides only a little guidance in terms of *how*
you will use the API to create the model and its components.  In general:

- create a model, a component, a validator, and the header and footer MathML
- add the governing equations in MathML to the component
- validate the model

    - this returns a list of variables to add
    - add the variables, their units and initial conditions (interfaces come
      later)

- validate the model again

    - this returns a list of units to add to the model
    - add the units

- validate the model yet again - it should be error free.
- repeat for all components
- define the equivalent variable connections
- define the equivalent variable interfaces (this is better done after all of
  the connections are made, so that you can be sure of the kind of interface
  which is needed for each variable)
- define the driving function MathML inside the environment component
- validate and output the model.

0: Setup
--------

.. container:: dothis

    **0.a** Create a model instance and name it appropriately.

.. container:: dothis

    **0.b** Create a validator for later use.

1: Create the sodium channel component
--------------------------------------

.. container:: dothis

    **1.a** Create a component instance for the sodium channel and name it
    appropriately.  Add the component to the model.

.. container:: dothis

    **1.b** Add the mathematics to this component according to:

.. math::

    E_{Na} = RTF \: \log(\frac{Nao}{Nai})

    Na_{conductance} = g_{Na} \: m^{3h}

    i_{Na} = Na_{conductance} (V-E_{Na})

.. container:: dothis

    **1.c** Call the validator and print its debugging information.  This will
    help to summarise the variables which you need to add:

- :math:`V` voltage, mV
- :math:`t` time, ms
- :math:`h` h-gate status, dimensionless
- :math:`m` m-gate status, dimensionless
- :math:`g_{Na} \;\; mS/cm^2`, (ie: milli-Siemens per square centimetre),
  initially 120
- :math:`E_{Na} \;\; mV`, initially 35
- :math:`i_{Na} \;\; \mu A/cm^2`, (ie: micro-Amperes per square centimetre)
- :math:`Nao \;\; mM`, (ie: milli-moles), initially 140
- :math:`Nai \;\; mM`, initially 30
- :math:`RTF  \;\; mV`, initially 25
- :math:`Na_{conductance}  \;\;  mS/cm^2`

.. container:: dothis

    **1.d** Again call the validator to list the units you will need to add to
    the parent model.  Remember that these will include the units of any constant
    values present in the MathML block too.

.. container:: dothis

    **1.e** Validate that the model is now free of errors.

2: Create the m-gate component
------------------------------

.. container:: dothis

    **2.a** Create a new component for the m-gate and name it appropriately.

.. container:: dothis

    **2.b** Create the MathML required to represent the mathematics governing
    the m-gate, as in three equations shown below, and add to the component.
    Remember that you will need to add the appropriate units to the constants to
    ensure consistency throughout.

.. math::

    \alpha_m = \frac {0.1(V+25)}{e^{0.1(V+25)}-1}

    \beta_m=e^{\frac {V}{18}}

    \dot m = \frac {dm}{dt} = \alpha_m(1-m)-m\beta_m


.. container:: dothis

    **2.c** Call the validator and use it to summarise the variables you need
    to add into this component, along with their units and initial conditions.

- :math:`V` voltage, mV
- :math:`t` time, ms
- :math:`\alpha_m` rate constant, 1/ms
- :math:`\beta_m` rate constant, 1/ms
- :math:`m` gate status, dimensionless, initially 0.05

.. container:: dothis

    **2.d** Call the validator and use it to list any remaining units which
    are not yet defined in the model.  Add them in as needed.

.. container:: dothis

    **2.e** Validate that the model is now free of errors.


3: Create the h-gate component
------------------------------

.. container:: dothis

    **3.a-c** Repeat the procedure above to create the h-gate component and add
    it to the model.  Its governing equations are:

.. math::

    \alpha_h = 0.07 e^{0.05V}

    \beta_h = \frac {1} {e^{0.1(V+30)} + 1}

    \dot {h} = \frac {dh} {dt} = \alpha_h (1-h) - h\beta_h

where:

- :math:`\alpha_h` rate constant, 1/ms
- :math:`\beta_h` rate constant, 1/ms
- :math:`V` voltage, mV
- :math:`t` time, ms
- :math:`h` gate status, dimensionless, initially 0.6

.. container:: dothis

    **3.d** Check that the model is valid to this point.

4: Create the environment component
-----------------------------------

As in the previous Tutorial 5 we need to create an environment component which
we'll use to control the time and voltage in which the channels operate.  As
before we define two variables:

- :math:`V` voltage, mV
- :math:`t` time, ms

We will add the driving function later.

.. container:: dothis

    **4.a** Define the environment component, including its variables, and add
    to the model.  Call the validator to check that the model is still free of
    errors.

5: Connect the components
-------------------------

At this stage we should have three components in the hierarchy below:
::

    |--- the model
       |--- the environment component
       |--- the sodium channel component
          |--- the m-gate component
          |--- the h-gate component

You can use the :code:`printModelToTerminal` utility function to check that
this is indeed the structure that you have.

Just as we did before, we need to connect the environment variables throughout
the rest of the components.  Recall from :ref:`Tutorial 5<tutorial5>` that:

- only immediate siblings, children, and parents can be connected
- the kind of interface depends on the relationship between components.


.. container:: dothis

    **5.a** This model involves sharing several variables between components.
    For each of them, create the appriopriate variable equivalence using the
    :code:`libcellml::Variable::setVariableEquivalence` function.  The shared
    variables are:

- :math:`V` voltage
- :math:`t` time
- :math:`h` h-gate status
- :math:`m` m-gate status

.. container:: dothis

    **5.b** For each of the variables you connected in 5.a, set their
    appropriate interface type using the :code:`setInterfaceType` function.

6: Set the driving function
---------------------------

The last step in defining your model behaviour is the driving function.  As in
the other tutorials, this is a voltage clamp such that the voltage is held at
a value of -20mV in the interval 5ms < t < 15 ms and -85mV otherwise.
Recall that this driving function applies to the variables in the environment
component: the variable connections you have established in 5.a will propagate
these values throughout the model.

.. container:: dothis

    **6.a** Write the MathML required for the driving function behaviour above.
    You will need to use the :code:`<piecewise>` function.

.. container:: dothis

    **6.b** Validate the final model and confirm that it is error free.


7: Write the model to a CellML file
-----------------------------------

Finally - provided your model is valid - you can serialise it and output to a
file.  This file will be used in later tutorials when we combine it with the
potassium channel model to simulate a neuron **TODO??**.

.. container:: dothis

    **7.a** Use the :code:`Printer` functionality to serialise your model, and
    output it to a file.

.. container:: dothis

    **7.b** Go and have a cuppa - you're done!










