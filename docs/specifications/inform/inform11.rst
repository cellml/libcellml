.. _inform11:



.. container:: infospec

  CellML :code:`variable` items differ a little from other items as they
  require more attributes to be defined.  In addition to the standard
  :code:`name` attribute, each :code:`variable` must also define a
  :code:`units` attribute too.

  Reusing the example from :ref:`Section 10: The component item<spec10>` we
  can see three variables are given fuller definitions:

  .. code-block:: xml

    <component name="mass_into_energy">
        <math>
        ...
        </math>
        <variable name="E" units="joule"/>
        <variable name="m" units="kilogram"/>
        <variable name="c" units="metres_per_second"/>
    </component>
