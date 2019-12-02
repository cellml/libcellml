.. _theory_ode_solutions:

============================================================
Solution methods for sets of Ordinary Differential Equations
============================================================

Differential equations provide the governing mathematics for most of the
simulations used in computational biology and engineering.  This document is
a very simplified explanation for how the output files from the libCellml
:code:`Generator` functionality can be coupled with a numerical integrator
in order to solve generated model's system of equations.

The basic premise of differential equations is that we know something about
a derivative quantity (like speed) which we need to integrate to find the
variable we care about (like distance).  Because most numerical integrators
can handle only one order of differentiation, in situations involving higher
orders (like acceleration) or more than one variable of influence or interest
(like drag) we need to use a set of connected equations instead of one alone.

For example:

- a first order system, :math:`\frac{dx}{dt}=f(x,t)` representing the effects
  of speed-dependent drag forces on the motion of an object,
- a second order system, :math:`\frac{d^2x}{dt^2} = f(\frac {dx}{dt}, x, t)`
  representing a spring-mass-damper system like that in shock absorbers,
- a multi-variable system, :math:`\frac{dx}{dt} = f(x, y, t)` representing
  population dynamics between predator and prey species over time.

For each variable we need to know:

- How to evaluate the variable's first derivative as the solution progresses.
  This is known as the *gradient function evaluation* step, and includes
  anything and everything - including other unknown variables, constants,
  etc - which affect the gradient of this variable.
- The initial condition for the variable so we have somewhere to start from.
  If this value is dependent on other variable values, it must nonetheless be
  known at the time of submitting the solver.  **TODO check whether this is
  allowed in the generator?? **
- How large a step to take through the independent variable space (like time).
  This is often made consistent between all variables so that their solutions
  progress together, though adaptive step sizing methods (in which the step
  size adjusts itself during the solution process) and mixed methods (in which
  different steps are used for different variables) are possible. In the
  examples here we will use a constant step-size for all variables and all
  steps.

A simple numerical integration method like :euler_method:`Euler's method <>`
involves stepping from the variable's initial value, along the gradient (as
evaluated by the *gradient function evaluation*), to a new value.  This new
value is used in turn to update all of the other gradient functions for other
variables, and the process is repeated for all variables and all time points
within the solution time interval.  More complicated stepping procedures
involve the combination of many points at which to evaluate the gradient
function as well as relaxation and hybrid techniques. In this example we will
use Euler's method as being the simplest possible.

Euler's method updates each variable according to:

.. math::

    x_next = x_current + (gradient\text{ }function\text{ }value).timestep

    x(t_k+\Delta t) = x_k + f(t_k, x_k)\times\Delta t

where the gradients of each variable are given by evaluating the current
value of the appropriate gradient function, :math:`f(t_k, x_k,...)`.
It is these *gradient function evaluations* which determine the nature of
the physical situation represented by the model.

The :code:`Generator` interprets your CellML model into a structure which can
easily be passed to a numerical integrator.  Consider the file created by
completing :ref:`Tutorial 3<tutorial3>` to model a first-order ODE.  The
governing equations - that is, the definitions of the variable gradients -
were specified in the MathML block within the CellML as:

.. code-block:: xml

  # Gradient function for variable "sharks" based on the current shark and fish populations
  <apply><eq/>
    <apply><diff/>
      <ci>sharks</ci>
      <bvar>time</bvar>
    </apply>
    <apply><plus/>
      <apply><times/>
        <ci>a</ci>
        <ci>sharks</ci>
      </apply>
      <apply><times/>
        <ci>b</ci>
        <ci>sharks</ci>
        <ci>fishes</ci>
      </apply>
    </apply>
  </apply>

  # Gradient function for variable "fishes" based on the current shark and fish populations
    <apply><eq/>
    <apply><diff/>
      <ci>sharks</ci>
      <bvar>time</bvar>
    </apply>
    <apply><plus/>
      <apply><times/>
        <ci>a</ci>
        <ci>sharks</ci>
      </apply>
      <apply><times/>
        <ci>b</ci>
        <ci>sharks</ci>
        <ci>fishes</ci>
      </apply>
    </apply>
  </apply>

These equations are interpreted by the :code:`Generator` as:

.. code-block:: cpp

  // Inside the








dfs
