.. _inform6:

.. container:: infospec

  Two kinds of items may be imported from other CellML models: the
  :code:`Units` and :code:`Component` types.  Importing units means
  that you're assured of consistency between your models, and allows
  for a more modular reuse of the components which use them.

  In the example below, the name :code:`potOfPaint` is used for the locally
  defined units in line 2, but the same name is used as the name for the
  imported units in line 6.  This is not permitted as it violates 6.1.1.

  .. code-block:: xml
     :emphasizelines:2, 6

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

  Using libCellML there are a couple of things to watch out for.  It
  will allow you import a :code:`Units` item which has a :code:`name`
  attribute that already exists in the importing model (as in this
  example), but will change the imported item's :code:`name` to avoid
  clashes.  The name will have an underscore :code:`_` added, followed
  by an unique integer.  The example would contain two :code:`Units`
  items called :code:`potOfPaint` (the locally defined one) and
  :code:`potOfPaint_1` (the imported one).

  Note that this does *not* imply that the units are equivalent, only
  that the name has been used before.  You can check whether or not two
  :code:`Units` are indeed dimensionally equivalent using the function:

  .. code-block:: cpp
