.. _informB5:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    The best way to understand how :code:`units` work is to read the
    next section which defines their child :code:`unit` items.

    The following examples show examples of what is not permitted in
    defining :code:`units` items.

    .. code-block:: xml

        <!-- the units name attribute is not a valid CellML identifier -->
        <units name="I'm not valid!"> ... </units>

        <!-- duplicted local units names are not allowed -->
        <units name="duplicatedName"> ... </units>
        <units name="duplicatedName"> ... </units>

        <!-- duplicated name of an imported units item is not allowed -->
        <import xlink:href="handyUnitsForImport.cellml">
            <units units_ref="myCustomUnits" name="duplicatedName">
        </import>

        <!-- duplicating the name of built-in units is not allowed -->
        <units name="metre"> ... </units>
