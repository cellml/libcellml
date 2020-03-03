.. _informB7_2:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    :code:`Component` items, as with every other part of CellML, must use
    names which are unique to their scope, and obey the format definitions
    outlined in
    :ref:`Data representation formats<spec_data_representation>`.  For example:

    .. code-block:: xml

      <!-- This is valid -->
      <component name="myValidName"> ... </component>

      <!-- the units name attribute is not a valid CellML identifier -->
      <component name="I'm not valid!"> ... </component>

      <!-- duplicted component names are not allowed -->
      <component name="duplicatedName"> ... </component>
      <component name="duplicatedName"> ... </component>

      <!-- duplicated name of an imported component item is not allowed -->
      <import xlink:href="handyComponentsForImport.cellml">
        <component component_ref="myComponentRef" name="duplicatedName">
      </import>
