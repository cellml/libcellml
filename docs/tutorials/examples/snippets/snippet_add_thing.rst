.. _snippet_add_thing:

.. container:: toggle

  .. container:: header-left

    Add a thing to a collection

  When you add an item to a collection, you also set its parent.
  Effectively, adding an item which is already a member of one collection to another collection actually *moves* it from the first to the second.
  This means that:

  - the item's parent will be the second collection parent;
  - the first collection will not contain the item any more; and
  - the second collection will contain the item.

  .. tabs::

    .. tab:: C++

      .. literalinclude:: ../code/example_addThings.cpp
        :language: c++

    .. tab:: Python

      .. literalinclude:: ../code/example_addThings.py
        :language: python
      