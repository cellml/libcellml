.. _informB7_3:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    .. container:: heading3

      The mathematics of a component

    Perhaps the most important part of a :code:`component` item is the
    mathematics it contains.  This is stored inside a single :code:`<math>` block
    as described in :ref:`Section 14: The math item<specB11>`.  The :code:`math`
    then defines the operation of the local :code:`variable` items and how they
    relate to each other mathematically.

    For example, a component to calculate Einstein's :math:`E=mc^2` could be
    represented by:

    .. code-block:: xml

      <component name="mass_into_energy">
        <math>
          <apply><eq/>
            <ci>E</ci>
            <apply><times/>
              <ci>m</ci>
              <apply><power/>
                <ci>c</ci>
                <cn cellml:units="dimensionless">2</cn>
              </apply>
            </apply>
          </apply>
        </math>
        ...
      </component>

    Please refer to :ref:`The math information item<spec_math>` for
    information on the :code:`math` items and MathML format.

    .. container:: heading3

      The variables of a component

    The MathML block above refers to three variables, named :code:`E`,
    :code:`m` and :code:`c`.  These variable names be the same as the
    :code:`name` attributes of the child :code:`variable` items in this
    component.

    .. code-block:: xml

      <component name="mass_into_energy">
        ...
        <variable name="E" ... >
        <variable name="m" ... >
        <variable name="c" ... >
      </component>

    Please refer to :ref:`The variable information item<spec_variable>` for
    information on the :code:`variable` items.

    .. container:: heading3

      The reset items of a component

    **TODO** when resets are finalised
