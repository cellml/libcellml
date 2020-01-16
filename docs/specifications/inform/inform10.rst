.. _inform10:

.. container:: infospec

  Components are the largest building blocks of the model, and have three
  important parts to them. The first is their naming and contents, similar
  to all the other CellML items.  The second relates to their structure
  in relation to each other: this structure is called their
  :code:`encapsulation` and is described in
  :ref:`Section 15: The encapsulation item<spec15>`.  The third relates to the
  :code:`import_component` item, as described in
  :ref:`Section 7: The import_component item`.

  Components are a convenient way to modularise the model, allowing parts to be
  removed, replaced, or reused easily.  They define the scope of their contents,
  meaning that the things within a component need only be unique in that local
  scope.  This means that common variables (like time, for example) can be
  given the same name in multiple components, without triggering an error.

  Perhaps the most important part of a :code:`component` item is the
  mathematics it contains.  This is stored inside a single :code:`<math>` block
  as described in :ref:`Section 14: The math item<spec14>`.  The :code:`math`
  then defines the operation of the local :code:`variable` items and how they
  relate to each other mathematically.

  For example, a component to calculate Einstein's :math:`E=mc^2` could be
  represented by:

  .. code-block:: xml

    <component name="einstein">
      <math>                    # Please refer to Section 14 for information about the MathML syntax
        <apply><eq/>
          <ci>E</ci>
          <apply><times/>
            <ci>m</ci>
            <apply><power/>
              <ci>c</ci>
              <cn cellml:units="dimensionless">2</cn>
            </apply>
          </apply>
        </apply>
      </math>
      ...
    </component>

  The MathML block refers to three variables, named :code:`E`, :code:`m` and
  :code:`c`.  These must be the same as the :code:`name` attributes of the
  child :code:`variable` items in this component.

  .. code-block:: xml

    <component name="einstein">
      <math> ... </math>
      <variable name="E" ... >  # Please refer to Section 11 for information about variable items
      <variable name="m" ... >
      <variable name="c" ... >
    </component>

  The final child in a :code:`component` is the :code:`reset` item.  **TODO**
