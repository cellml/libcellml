.. _examples_annotate_model:

Annotate a ``Model``
====================

libCellML does not provide annotation functionality directly, but it can help with some of the things that you might need to know in order to implement your own.
Each annotation is attached to an unique ID locator which can be retrieved and edited.

Item types that may have an ID are:

- :code:`Model` items;
- :code:`Component` items;
- :code:`Variable` items;
- :code:`Units` items;
- :code:`Reset` items; and
- :code:`ImportSource` items.

Each item of the above types can be retrieved using the :code:`id()` function, or set through the :code:`setId()` function.
The ID attribute must be set according to the specification rules: please see :cellml2:`1.2.5 XML ID attributes<specA2.html?issue=1.2.5>` for details.

**TODO** Update when there are other utility functions?
