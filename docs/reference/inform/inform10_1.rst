.. _inform10_1:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    Components are the largest building blocks of the model, and have three
    important parts to them. The first is their naming and contents, similar
    to all the other CellML items, and described below.  The second relates
    to their structure in relation to other :code:`component` items: this
    structure is called their *encapsulation* and is described in
    :ref:`The encapsulation item<spec_encapsulation>`.  The third relates to the
    :code:`import_component` item, as described in
    :ref:`The import_component item<spec_import_component>`.

    Components are a convenient way to modularise the model, allowing parts to be
    removed, replaced, and reused easily.  They define the scope of their contents,
    meaning that the items within a component need only be uniquely named in that
    local scope.  Commonly needed variables (like *time*, for example)
    can be given the same name in multiple components without triggering an error.
