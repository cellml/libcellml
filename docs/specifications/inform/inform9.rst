.. _inform9:

.. container:: infospec

  To continue the example from :ref:`the previous section<spec8>`, we now need
  to define what the units of :code:`cm3_per_second` actually means.
  First, we need to change the base unit of :code:`metre` into :math:`cm^3` as
  follows:

  .. code-block:: xml

    <units name="cm3_per_second">
       <unit units="metre" prefix="centi" exponent="3">  # default multiplier of 1
       ...
    </units>

  Next, we include other part, changing the base units of :code:`second` into
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
