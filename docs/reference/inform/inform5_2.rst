.. _inform5_2:

.. _inform_import2:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

  The only items which can be imported directly are :code:`component` and
  :code:`units` items.  The intention is that these are modular building
  blocks, able to be passed between models easily through this import
  functionality.

  When you import a :code:`component`, all its :code:`variables` and
  encapsulated child :code:`component` items are imported too,
  along with any its governing :code:`math` block and any :code:`units`
  items it uses.

  When you import a :code:`units` item, the child :code:`unit` items which
  it contain are imported as well.
