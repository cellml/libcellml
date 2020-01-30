.. _inform6:

.. container:: infospec

  Two kinds of items may be imported from other CellML models: the
  :code:`Units` and :code:`Component` types.  Importing units means
  that you're assured of consistency between your models, and allows
  for a more modular reuse of the components which use them.

  For example:

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

  In this example, the name :code:`potOfPaint` is used for the locally
  defined units

  Using libCellML there are a couple of things to watch out for.  If you
  import a :code:`Units` item which has a :code:`name` attribute that
  already exists in the importing model, the imported item's :code:`name`
  will be changed.  It will have an underscore :code:`_` added, followed
  by an unique integer.  Note that this does *not* imply that the units
  are equivalent, only that their name has been used before.
