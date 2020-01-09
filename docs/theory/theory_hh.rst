.. _hh_background:

=====================================
A model of the nerve action potential
=====================================

Here we describe the first (and most famous) model of nerve fibre
electrophysiology based on the membrane ion channels that we have
discussed in the last two sections. This is the work by Alan Hodgkin and
Andrew Huxley in 1952 :cite:`10` that won them (together with John Eccles) the
1963 Noble prize in Physiology or Medicine for *"their discoveries
concerning the ionic mechanisms involved in excitation and inhibition in
the peripheral and central portions of the nerve cell membrane"*.

--------------
Cable equation
--------------

The *cable equation* was developed in 1890\ [#]_ to predict the
degradation of an electrical signal passing along the transatlantic
cable. It is derived as follows:

.. figure:: images/current_flow_leaky_cable.png
   :name: ocr_tut_cur_flow_leaky
   :alt: Current flow in a leaky cable
   :align: right
   :figwidth: 6.5cm

   Current flow in a leaky cable.

If the voltage is raised at the left hand end of the cable (shown by the
deep red in :numref:`ocr_tut_cur_flow_leaky`), a current :math:`i_{a}` (in A)
will flow.  This current depends on the voltage gradient according to Ohm's
Law, such that:

.. math::

  - \frac{\partial V}{\partial x} = r_{a}i_{a}

where :math:`\frac{\partial V}{\partial x}` is the voltage gradient along the
cable (in V.m :superscript:`-1`), and :math:`r_{a}` is the resistance (in
:math:`\Omega`.m :sup:`-1`).

If the cable leaks current :math:`i_{m}` (A.m :sup:`-1`) per unit length
of cable, then conservation of current gives
:math:`\frac{\partial i_{a}}{\partial x} = i_{m}` and,
substituting for :math:`i_{a}` we get:

.. math::

  \frac{\partial}{\partial x}\left( - \frac{1}{r_{a}}\frac{\partial V}{\partial x} \right) = i_{m}



MY TEST IS HERE: \textDelta\textbeta



There are two sources of membrane current, :math:`i_{m}`.
First, from the capacitance associated with the membrane, :math:`C_{m}`
(:math:`\approx 1\mu F/cm^2`) of the membrane,
:math:`C_{m}\frac{\partial V}{\partial t}`, and one associated with
holes or channels in the membrane, :math:`i_{\text{leak}}`. Inserting
these into the RHS gives

.. math::

   \frac{\partial}{\partial x}\left( - \frac{1}{r_{a}}\frac{\partial V}{\partial x} \right) = i_{m} = C_{m}\frac{\partial V}{\partial t} + i_{\text{leak}}

Rearranging gives the *cable equation* (for constant :math:`r_{a}`):

.. math::

   C_{m}\frac{\partial V}{\partial t} = - \frac{1}{r_{a}}\frac{\partial^{2}V}{\partial x^{2}} - i_{\text{leak}}

where all terms represent *current density* (current per membrane area)
and have units of :math:`\mu A/\text{cm}^{2}`.

-----------------
Action potentials
-----------------

.. figure:: images/current_flow_neuron.png
   :name: ocr_tut_cur_flow_neuron
   :alt: Current flow in a neuron
   :align: right
   :figwidth: 6.5cm

   Current flow in a neuron.

The cable equation can be used to model the propagation of an action
potential along a neuron or any other excitable cell. The ‘leak’ current
is associated primarily with the inward movement of sodium ions through
the membrane ‘sodium channel’, giving the **inward** membrane current
:math:`i_{\text{Na}}`, and the outward movement of potassium ions
through a membrane ‘potassium channel’, giving the **outward** current
:math:`i_{K}` (see :numref:`ocr_tut_cur_flow_neuron`). A further small leak current
:math:`i_{L} = g_{L}\left( V - E_{L} \right)` associated with chloride
and other ions is also included.

.. figure:: images/current_voltage_trajectory.png
   :name: ocr_tut_cur_volt_traj
   :alt: Current-voltage trajectory
   :align: right
   :figwidth: 8.5cm

   Current-voltage trajectory during an action potential.

When the membrane potential :math:`V` rises due to axial current flow,
the Na channels open and the K channels close, such that the membrane
potential moves towards the Nernst potential for sodium. The subsequent
decline of the Na channel conductance and the increasing K channel
conductance as the voltage drops rapidly repolarises the membrane to its
resting potential of -85mV (see :numref:`ocr_tut_cur_volt_traj`).

We can neglect\ [#]_ the term
(:math:`- \frac{1}{r_{a}}\frac{\partial^{2}V}{\partial x^{2}}`) (the
rate of change of axial current along the cable) for the present models
since we assume the whole cell is clamped with an axially uniform
potential. We can therefore obtain the membrane potential :math:`V` by
integrating the first order ODE

.. math::

   \frac{\text{dV}}{\text{dt}} = - \left( i_{\text{Na}} + \ i_{K} + i_{L} \right)/C_{m}.

.. figure:: images/hodgkin_1952.png
   :name: ocr_tut_hh_1952
   :alt: CellML schematic HH model
   :align: center
   :figwidth: 18cm

   A schematic cell diagram describing the current flows
   across the cell bilipid membrane that are captured in the Hodgkin-Huxley
   model. The membrane ion channels are a sodium (Na\ :sup:`+`) channel, a
   potassium (K\ :sup:`+`) channel, and a leakage (L) channel (for chloride
   and other ions) through which the currents I\ :sub:`Na`, I\ :sub:`K` and
   I\ :sub:`L` flow, respectively.

We use this example to demonstrate the importing feature of CellML.
CellML *imports* are used to bring a previously defined CellML model of
a component into the new model (in this case the Na and K channel
components defined in the previous two sections, together with a leakage
ion channel model specified below). Note that importing a component
brings the children components with it along with their connections and
units, but it does not bring the siblings of that component with it.

To establish a CellML model of the HH equations we first lay out the
model components with their public and private interfaces (:numref:`ocr_tut_over_str_hh`).

.. figure:: images/overall_structure_hh.png
   :name: ocr_tut_over_str_hh
   :alt: Overall sturcture of HH CellML model
   :align: center
   :figwidth: 18cm

   Overall structure of the HH CellML model showing the
   encapsulation hierarchy (:purple:`purple`), the CellML model imports
   (:blue:`blue`) and the other key parts (:red:`units`, :green:`components`, and :orange:`mappings`) of the top level CellML model.





---------------------------

.. rubric:: Footnotes

.. [#] http://en.wikipedia.org/wiki/Cable_theory

.. [#] This term is needed when determining the propagation of the action potential, including its wave speed.
