.. _inform4:

The :code:`model` is the highest level in the CellML file, not including the
opening :code:`xml` tags.  And, just like the Highlander, there can be only one.

Please see the annotated example model below.  **TODO**

.. code-block:: xml

    <model name="myModelName">                           # a valid name must be present
        <component name="myComponentName"></component>   # a unique and valid name must be present
    </model>


Possible errors related to the :code:`model` item
-------------------------------------------------

**TODO** put list of errors/issues/hints from the validator/generator here.
