.. _aside_constant_vs_variable:

Aside: Constants vs variables
=============================

In your model, there is mathematics.
And in your mathematics, there are variables.
Some of these variables will, well, *vary* in value, but others might not.
This note is to help you understand the different ways in which :code:`variable` elements are assigned value, and what it means to your whole model's interpretation.

There are six ways to assign a value to a :code:`variable` element:

1. **In the ``math`` blocks, to a number:** These are classed as "eternal truths", and are statements which are held to be true throughout the entirety of the simulation.
   If you use a :code:`math` block statement to assign value to a :code:`variable` element using a hard-coded numerical value, then that value can **never** be changed.
   Any attempt to change it will make the model over-defined.
   In the example below, :code:`A` is a constant with value 1 for the entire simulation.

   .. code-block:: xml

      <math>
        <apply><eq/>
          <ci>A</ci>
          <cn cellml:units="dimensionless">1</cn>
        </apply>
      </math>

2. **In the ``math`` block, to another variable or expression:**  As above, these are classed as "eternal truths", but of course the actual value held by the variables may change as the expression is evaluated at different times.
   The :code:`math` statements are not *assignments* (as you'd expect in a programming language), but rather *equations* (as you'd expect in mathematics).
   This means that writing :math:`B = C` is equivalent to writing :math:`C = B`, just as it is in normal mathematics, and can be read "The value of B is always the same as the value of C".
   Compare that to the assignment statement we're familiar with in programming, :code:`B := C` ("set the value of B to be the current value of C") which is *not* the same as :code:`C := B` ("set the value of C to be the current value of B").
   Of course :math:`B = C` is perhaps the simplest equation possible, and yours will be a lot more complicated than this!

3. **In the ``initial_value`` attribute:** The term "initial value" might lead you to believe that the :code:`initial_value` attributes are only used for variables of integration.
   In reality, *any* variable which will have a non-constant value during the simulation *may* be set using this attribute.
   This includes values which are changed by resets, or by solving a differential or algebraic equation.
   The only situation where you don't need to set a variable's value like this is where the variable is defined by evaluation of a :code:`math` block statement.
   In that situation, having an initial value specified as well as a maths definition will make the model over-defined.

  .. code-block:: xml

    <!-- The variable B can change in value during the simulation. -->
    <variable name="B" initial_value="1" units="dimensionless" />

    <!-- The variable C does not use initialisation, as it is
         constrained by the maths below to always have the same
         value as B, which has been initialised. -->
    <variable name="C" units="dimensionless" />
    <math>
      <apply><eq/>
        <ci>B</ci>
        <ci>C</ci>
      </apply>
    </math>

    <!-- The statement above is an equation, not an assignment,
         so is equivalent to: -->
    <math>
      <apply><eq/>
        <ci>C</ci>
        <ci>B</ci>
      </apply>
    </math>

4. **By solving a differential equation:** This is similar to point 2 above, in that the variable's definition is contained within a mathematical statement.
   The difference is that when a :code:`variable` element is a state variable (ie: the numerator of a differential equation), it *must* have a value which is specified (either locally or somewhere in its equivalent variable set) by an :code:`initial_value` attribute.

   .. code-block:: xml

      <!-- A state variable must have an initial value specified.
           Note that this could be applied to a connected variable in another component. -->
      <variable name="E" units="dimensionless" initial_value="3" />
      <math>
        <apply><eq/>
          <diff>
            <ci>E</ci>
            <bvar>t</bvar>
          </diff>
          <cn cellml:units="dimensionless">1</cn>
        </apply>
      </math>

5. **By applying a ``reset``:** Resets allow a variable to have prescribed discontinuity in value at some stage in the simulation process.
   This means that the value of the variable must be allowed to change (that is, it must not appear in a statement like in point 1 above).
   In contrast to the mathematical *equations* defined inside :code:`math` elements, the MathML statements within a reset's :code:`reset_value` block is an *assignment*.
   By their nature, the mathematics of resets are only temporarily true, and so anything written there is a one-off assignment when the reset item is active.
   This means that even though the reset variable's value can't be defined as a constant (as in point 1), it could still be part of an equation (as in point 2).
   It must not be a variable of integration (as in point 4) or a base variable (as in point 6).

6. **By being a base variable:** **TODO** how to define where these get their value from??
