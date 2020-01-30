.. _inform6_2:

.. container:: infospec

  You can read the import statement in lines 5-7 above as: "retrieve the :code:`Units`
  called :code:`twoLitrePot` from the file :code:`paint_pot_sizes.cellml`, and store it
  here in this model under the name :code:`potOfPaint`.

  .. code-block:: xml

     <import xlink:href="paint_pot_sizes.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
        <units units_ref="twoLitrePot" name="potOfPaint"/>
     </import>

  Note that if you've already defined the namespace inside the :code:`<model>` tags then you
  would not need to repeat it here.
