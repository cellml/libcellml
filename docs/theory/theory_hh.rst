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

.. figure:: _static/images/current_flow_leaky_cable.png
   :name: ocr_tut_cur_flow_leaky
   :alt: Current flow in a leaky cable
   :align: right
   :figwidth: 6.5cm

   Current flow in a leaky cable.

If the voltage is raised at the left hand end of the cable (shown by the
deep red in :numref:`ocr_tut_cur_flow_leaky`), a current :math:`i_{a}` (A) will flow that
depends on the voltage gradient, given by
:math:`\frac{\partial V}{\partial x}` (:math:`V.m^{-1}`) and the resistance
:math:`r_{a}` (:math:`\Omega.m^{-1}`), Ohm’s law gives
:math:`- \frac{\partial V}{\partial x} = r_{a}i_{a}` . But if the cable
leaks current :math:`i_{m}` (:math:`A.m^{-1}`) per unit length of cable,
conservation of current gives
:math:`\frac{\partial i_{a}}{\partial x} = i_{m}` and therefore,
substituting for :math:`i_{a}` ,
:math:`\frac{\partial}{\partial x}\left( - \frac{1}{r_{a}}\frac{\partial V}{\partial x} \right) = i_{m}`
. There are two sources of membrane current :math:`i_{m}` , one
associated with the capacitance :math:`C_{m}`
(:math:`\approx 1\mu F/\text{cm}^{2}`) of the membrane,
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

.. figure:: _static/images/current_flow_neuron.png
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

.. figure:: _static/images/current_voltage_trajectory.png
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

.. figure:: _static/images/hodgkin_1952.png
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

.. figure:: _static/images/overall_structure_hh.png
   :name: ocr_tut_over_str_hh
   :alt: Overall sturcture of HH CellML model
   :align: center
   :figwidth: 18cm

   Overall structure of the HH CellML model showing the
   encapsulation hierarchy (:purple:`purple`), the CellML model imports
   (:blue:`blue`) and the other key parts (:red:`units`, :green:`components`, and :orange:`mappings`) of the top level CellML model.

The HH model is the top level model. The *CellML Text* code for the HH
model, together with the leakage_channel model, is given below. The imported potassium_ion_channel model and
sodium_ion_channel model are unchanged from the previous sections

:download:`HH.cellml <resources/HH.cellml>`

.. code-block:: cell

   def model HH as
      def import using "sodium_ion_channel.cellml" for
         comp Na_channel using comp sodium_channel;
      enddef;
      def import using "potassium_ion_channel.cellml" for
         comp K_channel using comp potassium_channel;
      enddef;
      def import using "leakage_ion_channel.cellml" for
         comp L_channel using comp leakage_channel;
      enddef;
      def unit millisec as
         unit second {pref: milli};
      enddef;
      def unit millivolt as
         unit volt {pref: milli};
      enddef;
      def unit microA_per_cm2 as
         unit ampere {pref: micro};
         unit metre {pref: centi, expo: -2};
      enddef;
      def unit microF_per_cm2 as
         unit farad {pref: micro};
         unit metre {pref: centi, expo: -2};
      enddef;
      def group as encapsulation for
         comp membrane incl
            comp Na_channel;
            comp K_channel;
            comp L_channel;
         endcomp;
      enddef;
      def comp environment as
         var V: millivolt {init: -85, pub: out};
         var t: millisec {pub: out};
      enddef;
      def map between environment and membrane for
         vars V and V;
         vars t and t;
      enddef;
      def map between membrane and Na_channel for
         vars V and V;
         vars t and t;
         vars i_Na and i_Na;
      enddef;
      def map between membrane and K_channel for
         vars V and V;
         vars t and t;
         vars i_K and i_K;
      enddef;
      def map between membrane and L_channel for
         vars V and V;
         vars i_L and i_L;
      enddef;
      def comp membrane as
         var V: millivolt {pub: in, priv: out};
         var t: millisec {pub: in, priv: out};
         var i_Na: microA_per_cm2 {pub: out, priv: in};
         var i_K: microA_per_cm2 {pub: out, priv: in};
         var i_L: microA_per_cm2 {pub: out, priv: in};
         var Cm: microF_per_cm2 {init: 1};
         var i_Stim: microA_per_cm2;
         var i_Tot: microA_per_cm2;
         i_Stim = sel
         case (t >= 1{millisec}) and (t <= 1.2{millisec}):
            100{microA_per_cm2};
         otherwise:
            0{microA_per_cm2};
         endsel;
         i_Tot = i_Stim + i_Na + i_K + i_L;
         ode(V,t) = -i_Tot/Cm;
      enddef;
   enddef;

:download:`Leakage_ion_channel <resources/leakage_ion_channel.cellml>`

.. code-block:: cell

   def model leakage_ion_channel as
      def unit millisec as
         unit second {pref: milli};
      enddef;
      def unit millivolt as
         unit volt {pref: milli};
      enddef;
      def unit per_millivolt as
         unit millivolt {expo: -1};
      enddef;
      def unit microA_per_cm2 as
         unit ampere {pref: micro};
         unit metre {pref: centi, expo: -2};
      enddef;
      def unit milliS_per_cm2 as
         unit siemens {pref: milli};
         unit metre {pref: centi, expo: -2};
      enddef;
      def comp environment as
         var V: millivolt {init: 0, pub: out};
         var t: millisec {pub: out};
      enddef;
      def map between leakage_channel and environment for
         vars V and V;
      enddef;
      def comp leakage_channel as
         var V: millivolt {pub: in};
         var i_L: microA_per_cm2 {pub: out};
         var g_L: milliS_per_cm2 {init: 0.3};
         var E_L: millivolt {init: -54.4};
         i_L = g_L*(V-E_L);
      enddef;
   enddef;


Note that the *CellML Text* code for the potassium channel is :ref:`Potassium_ion_channel.cellml <ocr_tut_k_ion_ch_ctc>`
and for the sodium channel is :ref:`Sodium_ion_channel.cellml <ocr_tut_na_ion_ch_ctc>`.

Note that the only units that need to be defined for this top level HH
model are the ones explicitly required for the membrane component. All
the other units, required for the various imported sub-models, are
imported along with the imported components.

The results generated by the HH model are shown in :numref:`ocr_tut_hh_res_ocr`.

.. figure:: _static/images/hh_results_opencor.png
   :name: ocr_tut_hh_res_ocr
   :alt: HH results in OpenCOR
   :align: center
   :figwidth: 18cm

   Results from OpenCOR for the Hodgkin Huxley (HH) CellML
   model. The top panel shows the generated action potential. Note that the
   stimulus current is not really needed as the background outward leakage
   current is enough to drive the membrane potential up to the threshold
   for sodium channel opening.

Important note
==============

It is often convenient to have the sub-models – in this case the
sodium_ion_channel.cellml model, the potassium_ion_channel.cellml
model and the leakage_ion_channel.cellml model - loaded into OpenCOR
at the same time as the high level model (HH.cellml), as shown in :numref:`ocr_tut_hh_tabs_ocr`
. If you make changes to a model in the *CellML Text* view, you must
save the file (*CTRL-S*) before running a new simulation since the
simulator works with the saved model. Furthermore, a change to a
sub-model will only affect the high level model which imports it if you
also save the high level model (or use the *Reload* option under the
File menu). An asterisk appears next to the name of a file when a change
has been made and the file has not been saved. The asterisk disappears
when the file is saved.

.. figure:: _static/images/hh_opencor_tabs.png
   :name: ocr_tut_hh_tabs_ocr
   :alt: File tabs in OpenCOR
   :align: center
   :figwidth: 18cm

   The HH.cellml model and its three sub-models are
   available under separate tabs in OpenCOR.

---------------------------

.. rubric:: Footnotes

.. [#] http://en.wikipedia.org/wiki/Cable_theory

.. [#] This term is needed when determining the propagation of the action potential, including its wave speed.
