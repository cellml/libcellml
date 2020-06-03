.. _examples_view_model:

View the contents of a ``Model``
++++++++++++++++++++++++++++++++

All CellML entities exist in an hierarchical structure as shown below.

.. container:: shortlist

  :code:`Model` is the top level item.
    ├─ :code:`Units` items are children of the :code:`Model`.

    │   ├─ :code:`name()` returns the name of the :code:`Units` item.

    │   └─ :code:`unitCount()` returns the number of :code:`Unit` items in this Units item.

    │

    ├─ model->componentCount() returns the number of :code:`Component` items which are direct children of the :code:`Model`.

    └─ :code:`component = model->component(c)` returns a pointer to the :code:`Component` item at index :code:`c`.

        └─ :code:`Component` items belong either to a :code:`Model` or nested within other :code:`Component` items.

            ├─ name() returns the name of the component.

            │

            ├─ component->variableCount() returns the number of :code:`Variable` items in the component.

            ├─ component->variable(v) returns a pointer to the :code:`Variable` at index :code:`v`.

            │     ├─ :code:`Variable` items belong to a component.

            │     ├─ name() returns the name of the variable.

            │     ├─ initialValue() returns the value to which this variable is initialised.

            │     ├─ interfaceType() returns an enum of the interface type.

            │     ├─ units() returns the name of the associated :code:`Units` item or built in units.

            │     │

            │     ├─ equivalentVariablesCount() returns the number of :code:`Variable` items connected to this one.

            │     └─ equivalentVariable(e) returns a pointer to the connected :code:`Variable` at index :code:`e`.

            │

            ├─ math() returns the MathML string for this :code:`Component`.

            │

            └─ resetCount() returns the number of :code:`Reset` items in the :code:`Component`.

                  ├─ testVariable() returns a pointer to the test variable
