.. _inform4:


.. container:: toggle

  .. container:: header

    Show/hide more information

  .. container:: infospec

    The :code:`model` is the highest level in the CellML file, not including the
    opening :code:`xml` tags.  And, just like the Highlander, there can be only one.

    Please see the annotated example model below.  **TODO**

    .. code-block:: xml

        <model name="myModelName">                           <!-- a valid name must be present -->
            <component name="myComponentName"></component>   <!-- a unique and valid name must be present -->
        </model>
