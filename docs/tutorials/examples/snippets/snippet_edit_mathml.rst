.. _snippet_edit_mathml:

.. container:: toggle

  .. container:: header-left

    Print the MathML block of a component

  .. container:: heading

    Print the MathML block of a component

  MathML is stored as a single string within a component.
  Retrieving it is simple enough using the :code:`math()` function, but any manipulation (change units used, changing variable names, adding additional relationships, etc) are a little more complicated.

  .. tabs::

    .. code-tab:: c++

      // C++ example

    .. code-tab:: py

      # Python example
