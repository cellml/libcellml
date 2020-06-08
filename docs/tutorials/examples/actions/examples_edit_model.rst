.. _examples_edit_model:

Edit items in a model
=====================

All CellML entities exist in an hierarchical structure as shown below.
In some circumstances additional links are made between items (equivalent variables, for example), but on the whole it follows a basic tree structure.

Within the structure each item has two parts:

- A set of *attributes* specific to itself.
  Some of these attribute exist for many items (for example, the :code:`name` attribute), and others are specific to the item type (for example, the :code:`initialValue` attribute on a :code:`Variable` item).
- A set of *collections* which this - the parent item - curates.
  For example, the collection of :code:`Variable` items owned by a parent :code:`Component`.

Editing attributes
------------------
For any item type, each attribute :code:`xyz` may be edited using the general :code:`setXyz` function, whose arguments vary depending on the attribute.
Note that this is distinct from editing collections of items, which is discussed below.

Some example snippets are shown below.


.. include:: ../snippets/snippet_edit_names.rst


Editing collections
-------------------
