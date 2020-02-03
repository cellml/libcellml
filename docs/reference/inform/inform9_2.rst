.. _inform9_2:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    There are two items related to units in CellML, and their naming can be
    confusing!  The plural - :code:`units` represents the actual final units
    (eg: :math:`cm^3/s`) to be used in the model.  This is a collection of
    smaller :code:`unit` items which transform the base dimensionality
    (eg: :math:`m, s`) into the form required by the final units
    (:math:`cm^3`, :math:`s^{-1}`).  This is done using

    The :code:`units` item and its requirements are described in
    :ref:`The units element information item<spec_units>`. For now we will
    just set a valid name for the units item:

    .. code-block:: xml

      <units name="cm3_per_second">
        ...
      </units>

    Now that we've named it, we also need to define what it actually means.
    In the example, we'll need to use two of the *built-in* base units,
    :code:`metre` and :code:`second`, and manipulate them accordingly.  This
    is done by including child :code:`unit` items.  First, we need to change
    the base units of :code:`metre` into :math:`cm^3`:

    .. code-block:: xml

      <units name="cm3_per_second">
         <unit units="metre" prefix="centi" exponent="3">  # default multiplier of 1
         ...
      </units>

    Next, we include the time dependency, changing the built-in units :code:`second` into
    :math:`s^{-1}`.  Note that sibling :code:`unit` items within a parent :code:`units`
    item are simply multplied together to form the final representation:

    .. code-block:: xml

      <units name="cm3_per_second">
        <unit units="metre" prefix="centi" exponent="3">
        <unit units="second" exponent="-1">
      </units>

    Note that this is exactly equivalent to the alterantives below:

    .. code-block:: xml

      <units name="cm3_per_second">
        <unit units="metre" prefix="-2" exponent="3">  # prefix can be specified as a power of 10
        <unit units="second" exponent="-1">
      </units>

      # or

      <units name="cm3_per_second">
        <unit units="metre" exponent="3" multiplier="0.01">  # multiplier specified instead
        <unit units="second" exponent="-1">
      </units>

      # or

      <units name="cm3_per_second">
        <unit units="metre" prefix="centi">  # default exponent of 1 ...
        <unit units="metre" prefix="centi">  # ... is repeated ...
        <unit units="metre" prefix="centi">  # ... to give the equivalent power of 3
        <unit units="second" exponent="-1">
      </units>
