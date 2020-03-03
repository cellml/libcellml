.. _inform4_2:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    .. code-block:: xml

      <model name="myModel">
        <component name="myFirstComponent"> ... </component>
        <component name="aDuplicatedComponentName"> ... </component>

        <!-- INVALID: This component is not valid because it has the same name as an existing one -->
        <component name="aDuplicatedComponentName"> ... </component>

        <units name="myUnits"> ... </units>
        <units name="myOtherUnits"> ... </units>
        <units name="aDuplicatedUnitName"> ... </units>

        <!-- INVALID This units item is not valid because it has the same name as an existing units item -->
        <units name="aDuplicatedUnitName"> ... </units>

        <!-- A model can contain any number of import items -->
        <import />
        <import />

        <!-- A model can contain any number of connection items, as long as the things they connect are unique -->
        <connection />
        <connection />

        <encapsulation>...</encapsulation>
        <!-- INVALID: A model must contain only ONE encapsulation item -->
        <encapsulation>...</encapsulation>

        <!-- INVALID: The only child elements of the model are those stated. -->
        <apples> ... </apples>

      </model>
