.. _inform6_1:

.. container:: infospec

  Two kinds of items may be imported from other CellML models: the
  :code:`Units` and :code:`Component` types.  Importing units means
  that you're assured of consistency between your models, and allows
  for a more modular reuse of the components which use them.

  In the example below, the name :code:`potOfPaint` is used for the locally
  defined units in line 2, but the same name is used as the name for the
  imported units in line 6.  This is not permitted as it violates 6.1.1.

  .. code-block:: xml

    <model name="paintingTheHouse">
      <units name="potOfPaint">
        <unit units="metre" exponent="3" multiplier="0.002">
      </units>
      <import xlink:href="paint_pot_sizes.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
        <units units_ref="twoLitrePot" name="potOfPaint"/>
      </import>
      <component name="paintCalculator">
        ...
      </component>
    </model>
