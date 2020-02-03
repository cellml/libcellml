.. _inform7:

.. container:: toggle

  .. container:: header

      See more

  .. container:: infospec

    The ablility to import and reuse :code:`Component` items is one of the
    most powerful features in CellML, as it allows modellers to easily
    plug-n-play different variations and model parts.  There are three
    ingredients required in importing an item:

      - a destination in the importing model (this is the :code:`component`
        item called :code:`pi_calculator` in the example below)

      - a file to import from, specified using the :code:`xlink:href`
        attribute of the parent :code:`import` block.  This is discussed in
        more detail in
        :ref:`The import element information item<spec_import>`.  In the
        example below this is the :code:`pi_approximators.cellml` file.

      - the specific item name to retrieve from the imported file. In the
        example below this is the :code:`circumference_over_diameter` value
        passed to the :code:`component_ref` attribute.

    Thus we can read the import statement below as: "retrieve the
    :code:`Component` named :code:`circumference_over_diameter` from the file
    :code:`pi_approximators.cellml`, and store it here in this model under the
    name :code:`pi_calculator`".

    .. code-block:: xml

      <import xlink:href="pi_approximators.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
         <component component_ref="circumference_over_diameter" name="pi_calculator"/>
      </import>

    Things to watch out for:

    1) **The namespace**.  Note that if you've already defined the
    :code:`xmlns:xlink` namespace inside the :code:`<model>` tags then you
    would not need to repeat it here.

    2) **The name attribute**.  Imported items have the same restrictions as
    locally defined items regarding the uniqueness of their names and their
    format.  In the
    example below, the name :code:`pi_calculator` is used for the locally
    defined component in line 2, but the same name is used as the name for the
    imported component in line 6.  This is not permitted as it violates 7.1.1.
    The second imported component uses an invalid name attribute
    (see :ref:`Data representation formats in CellML<spec_data_representation>`)
    so is not permitted either.

    .. code-block:: xml

      <model name="circle">
        <component name="pi_calculator">
          ...
        </component>

        <!-- This destination name conflicts with the locally defined name above -->
        <import xlink:href="series_approx_of_pi.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
          <component component_ref="GregoryLeibnizApproximator" name="pi_calculator"/>
        </import>

        <!-- This destination name is not valid CellML as it contains whitespace and special characters -->
        <import xlink:href="series_approx_of_pi.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
          <component component_ref="GregoryLeibnizApproximator" name="pi calculator!"/>
        </import>

      </model>

    3) **The component_ref attribute**. This must be a valid CellML identifier
    (see :ref:`Data representation formats in CellML<spec_data_representation>`).
    It also has to actually exist as a :code:`component` in the given
    :code:`href` location! Neither of the imports below are permitted:

    .. code-block:: xml

      <model name="circle">

        <!-- This component_ref name does not exist at in the file specified -->
        <import xlink:href="series_approx_of_pi.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
          <component component_ref="I_dont_exist" name="pi_calculator"/>
        </import>

        <!-- This component_ref name is not a valid CellML identifier -->
        <import xlink:href="series_approx_of_pi.cellml" xmlns:xlink="http://www.w3.org/1999/xlink">
          <component component_ref="I have spaces so am not a valid ID" name="pi_calculator"/>
        </import>

      </model>
