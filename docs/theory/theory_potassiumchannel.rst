.. include:: resources/roles.txt

.. _theory_potassiumchannel:

================================
A model of the potassium channel
================================

We now deal specifically with the application of the ion channel model
discussed in :ref:`the previous chapter on ion gates
theory<theory_iongates>` to
the Hodgkin and Huxley (HH) potassium channel. Following the convention
introduced by Hodgkin and Huxley, the gating variable for the potassium
channel is :math:`n` and the number of gates in series is
:math:`\gamma = 4`, therefore:

.. math::

    i_{K} = \bar{i_K}n^{4} = n^{4}\bar{g}_{K}\left( V - E_{K} \right)

where :math:`\bar{g}_{K} = \ 36 \text{ mS.cm}^{-2}`,
and with intra- and extra-cellular concentrations
:math:`\left\lbrack K^{+} \right\rbrack_{i} = 90\text{ mM}` and
:math:`\left\lbrack K^{+} \right\rbrack_{o} = 3\text{ mM}`, respectively, the
Nernst potential for the potassium channel (:math:`z = 1` representing the one
positive charge on :math:`K^{+}`) is:

.. math::

    E_{k} = \frac{RT}{zF} \ln\frac{\left\lbrack K^{+}
    \right\rbrack_{o}}{\left\lbrack K^{+} \right\rbrack_{i}} =
    25\ln\frac{3}{90} = - 85\text{ mV}

As noted above, this is called the *equilibrium potential* since it is
the potential across the cell membrane when the channel is open but no
current is flowing because the electrostatic driving force from the
potential (voltage) difference between internal and external ion charges
is exactly matched by the entropic driving force from the ion
concentration difference. :math:`n^{4}\bar{g}_{K}` is
the channel conductance.

The gating kinetics are described (as before) by:

.. math::

    \frac{dn}{dt} = \alpha_{n}\left( 1 - n \right) - \beta_{n}n

with time constant:

.. math::
    \tau_{n} = \frac{1}{\alpha_{n} + \beta_{n}}

The main difference from the gating model in our previous example is
that Hodgkin and Huxley found it necessary to make the rate constants
:math:`\alpha_n` and :math:`\beta_n`
functions of the membrane potential :math:`V`
(see :numref:`ocr_tut_volt_deps_gates`) as
follows \ [#]_:

.. math::

    \alpha_{n} = \frac{- 0.01\left( V + 65 \right)}{\exp \left({-0.1 \left( V + 65 \right)}\right) - 1} \\[16pt]
    \beta_{n} = 0.125\exp{\left( \frac{- \left( V + 75 \right) } {80} \right) }

.. figure:: images/volt_deps_of_gate_consts.png
   :name: ocr_tut_volt_deps_gates
   :alt: Voltage dependencies of gate constants
   :align: center
   :figwidth: 8cm

   Voltage dependence of rate constants :math:`\alpha_n` and
   :math:`\beta_n (\text{ms}^{-1})`,
   time constant :math:`\tau_n (\text{ms})` and
   relative conductance :math:`\frac{g_{ss}}{\bar{g}_Y}`.

Note that under steady state conditions when
:math:`t \rightarrow \infty` and
:math:`\frac{dn}{dt} \rightarrow 0`:

.. math::

    \left. \ n \right|_{t = \infty} = n_{\infty} =
    \frac{\alpha_{n}}{\alpha_{n} + \beta_{n}}

The voltage dependence of the steady state channel conductance is then:

.. math::

    g_{ss} = \left( \frac{\alpha_{n}}{\alpha_{n} + \beta_{n}} \right)^{4}.\bar{g}_{Y}

(see :numref:`ocr_tut_volt_deps_gates`). The steady state current-voltage
relation for the channel is illustrated in :numref:`ocr_tut_ss_cur_volt`.

.. figure:: images/ss_cur_volt.png
   :name: ocr_tut_ss_cur_volt
   :alt: Steady-state current voltage
   :figwidth: 8cm
   :align: center

   The steady-state current-voltage relation for the potassium channel.

Interpretation into a CellML model
----------------------------------
Defining components serves two purposes: it preserves a modular
structure for CellML models, and allows these component modules to be
imported into other models, as demonstrated in
:ref:`Tutorial 5<tutorial5>`. For the
potassium channel model we define components representing (i) the
environment, (ii) the potassium channel conductivity, and (iii) the
dynamics of the :math:`n`-gate as shown in **TODO**.

Since certain variables (:math:`t`, :math:`V` and :math:`n`) are shared
between components, we need to also define the component maps or equivalent
variables as described below.

An aside: Equivalent variables
------------------------------
Variables are contained within components in order to make the models
modular, and enabling the sharing and reuse of their different entities.
But along with this containment functionality comes the need for the
enclosed variables to communicate with one another across these artificial
walls.  This is done by creating *equivalent variable maps*, where a variable
in one component is mapped through an interface to a corresponding variable in
another.  More information about how components can be nested to
create a hierarchical *encapsulation structure* is shown in more detail in
the next chapter, :ref:`A model of a sodium channel<theory_sodiumchannel>` and
demonstrated in :ref:`Tutorial 5<tutorial5>`.

**TODO image here of model structure for equivalent variables**

This potassium channel model will be used - together with a sodium
channel model (in :ref:`Tutorial 7<tutorial7>`) and a leakage channel
model - to form the Hodgkin-Huxley
neuron model (in :ref:`Tutorial 8<tutorial8>`), where the membrane ion
channel current flows are coupled to the equations governing current flow
along the axon to generate an action potential.

The next chapter describes the theory behind the
:ref:`sodium channel model<theory_sodiumchannel>`.

---------------------------

.. rubric:: Footnotes

.. [#] The original expression in the HH paper used
       :math:`\alpha_n = \frac{0.01(v+10)}{\exp\left(0.1(v+10)\right)-1}` and
       :math:`\beta_n = 0.125\exp \left( {\frac{v}{80}} \right)`, where
       :math:`v` is defined
       relative to the resting potential (:math:`-75\text{ mV}`) with positive
       corresponding to positive *inward* current and :math:`v = -(V+75)`.
