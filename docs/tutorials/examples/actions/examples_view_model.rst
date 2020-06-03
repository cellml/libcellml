.. _examples_view_model:

View the contents of a ``Model``
++++++++++++++++++++++++++++++++

All CellML entities exist in an hierarchical structure as shown below.

.. container:: shortlist

  - :code:`Model` is the top level item.

    - :code:`unitsCount()` returns the number of :code:`Units` items in the :code:`Model`.
    - :code:`units(u)` returns a pointer to the :code:`Units` item at index :code:`u`.
    - :code:`units("unitsName")` returns a pointer to the :code:`Units` item with name :code:`"unitsName"`.

      - :code:`name()` returns the name of the :code:`Units` item.
      - :code:`unitCount()` returns the number of :code:`Unit` items in this Units item.

    - :code:`componentCount()` returns the number of :code:`Component` items which are direct children of the :code:`Model`.
    - :code:`component = model->component(c)` returns a pointer to the :code:`Component` item at index :code:`c`.
    - :code:`component = model->component("componentName")` returns a pointer to the :code:`Component` item with name :code:`"componentName"`.

      - :code:`name()` returns the name of the component.

      - :code:`component->variableCount()` returns the number of :code:`Variable` items in the component.
      ─ :code:`component->variable(v)` returns a pointer to the :code:`Variable` at index :code:`v`.
      - :code:`component->variable(variableName)` returns a pointer to the :code:`Variable` with name :code:`variableName`.

        - :code:`name()` returns the name of the variable.
        - :code:`initialValue()` returns the value to which this variable is initialised.
        - :code:`interfaceType()` returns an enum of the interface type.
        - :code:`units()` returns the name of the associated :code:`Units` item or built in units.

        - :code:`equivalentVariablesCount()` returns the number of :code:`Variable` items connected to this one.
        - :code:`equivalentVariable(e)` returns a pointer to the connected :code:`Variable` at index :code:`e`.

        - :code:`math()` returns the MathML string for this :code:`Component`.

        - :code:`resetCount()` returns the number of :code:`Reset` items in this :code:`Component`.

          - :code:`testVariable()` returns a pointer to the test variable for this :code:`Reset`.
          - :code:`variable()` returns a pointer to the reset variable for this :code:`Reset`.
          - :code:`testValue()` returns the MathML string which will determine whether this :code:`Reset` is active.
          - :code:`resetValue()` returns the MathML string which will determine the value given when this reset is active.
          - :code:`order()` returns the order of this reset.
