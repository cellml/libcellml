.. _inform9_2:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    There are two items related to units in CellML, and their naming can be
    confusing!  The plural - :code:`units` represents the actual final units
    to be used in the model.  This is a collection of
    smaller :code:`unit` items which transform the base dimensionality
    into the form required by the final units by way of prefixes,
    multipliers, and exponents.

    In the example, we'll need to use two of the *built-in* base units,
    :code:`metre` and :code:`second`, and manipulate them to form
    :math:`cm^3/s`.  This is done by including child :code:`unit` items.
    First, we need to change the base units of :code:`metre` into :math:`cm^3`:

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
        <unit units="metre" prefix="centi" exponent="3">  # default multiplier of 1
        <unit units="second" exponent="-1"> # default prefix of 0, default multiplier of 1
      </units>

    This is exactly equivalent to the alterantives below:

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
        <unit units="metre" prefix="centi">     # default exponent of 1 ...
        <unit units="metre" prefix="-1">        # ... is repeated ...
        <unit units="metre" multiplier="0.01">  # ... to give the equivalent power of 3
        <unit units="second" exponent="-1">
      </units>

    For more information on :code:`Units` items please refer to the
