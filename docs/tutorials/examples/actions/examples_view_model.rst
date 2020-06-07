.. _examples_view_model:

View the contents of a ``Model``
================================

All CellML entities exist in an hierarchical structure as shown below.
In some circumstances additional links are made between items (equivalent variables, for example),
but on the whole it follows a basic tree structure.

Within the structure each item has two parts:
- A set of *attributes* specific to itself.
  Some of these attribute exist for many items (for example, the :code:`name` attribute), and others are specific to the item type (for example, the :code:`initialValue` attribute on a :code:`Variable` item).
- A set of *collections* which this - the parent item - curates.
  For example, the collection of :code:`Variable` items owned by a parent :code:`Component`.

View attributes of an item
--------------------------
Retrieving the value of an item's attribute is simple, and follows the same general pattern throughout libCellML.
Get the attribute :code:`xyz` using the camelCase function :code:`xyx()` without arguments.

For example:

.. code-block:: cpp

    // Retrieving the name attribute from the myModel item:
    std::string myModelName = myModel->name();

    // Retrieving the initial value of the myVariable item:
    std::string myInitialValue = myVariable->initialValue();

.. code-block:: py

    # Retrieving the name attribute from the my_model item:
    my_model_name = my_model.name()

    # Retrieving the initial value of the myVariable item:
    my_initial_value = my_variable.initialValue()

Note that the return value's type will vary depending on the function.
For example, a :code:`Variable` item pointer is returned as the :code:`testVariable()` attribute value for a :code:`Reset` item:

.. code-block:: cpp

  // Retrieve the test variable from the myReset item:
  libcellml::VariablePtr myTestVariable = myReset->testVariable();

.. code-block:: python

  # Retrieve the test variable from the my_reset item:
  my_test_varible = my_reset->testVariable()

View collections owned by an item
---------------------------------
In order to access items within a collection use the same general format as above, but with an indicator (name or index) of the child item to be retrieved from the collection.
In other words, get the child item of type :code:`xyz` using the camelCase function :code:`xyx(myIndex)` or :code:`xyz(myName)`.

.. container:: nb

    Before accessing a collection item using an index, you can use the :code:`countXyz()` function to return the number of items in the collection.

The following example shows how all variables in a component can be listed.

.. code-block:: cpp

    // Looping through variables in the component myComponent and retrieve their names.
    //    NOTE that indexing starts from zero.
    for(size_t v = 0; v < myComponent->variableCount(); ++v) {

      // Retrieve the Variable item at index v:
      auto myVariable = myComponent->variable(v);

      // Retrieve the name of the myVariable item:
      auto myVariableName = myVariable->name();
    }

    // Retrieve a variable called "helloThere" by name.
    //    NOTE that a nullptr will be returned if no variable of that name is found.
    auto myHelloThereVariable = myComponent->variable("helloThere");

    // In this case, the myMissingVariable will be a nullptr:
    auto myMissingVariable = myComponent->variable("nameThatDoesntExist");

    // This will cause a segfault as myMissingVariable is null:
    auto myMissingName = myMissingVariable->name();

.. code-block:: py

    # Looping through variables in the component myComponent and retrieve their names.
    #    NOTE that indexing starts from zero:
    for v in range(0, my_component.variableCount()):

      # Retrieve the Variable item at index v:
      my_variable = my_component.variable(v)

      # Retrieve the name of the myVariable item:
      my_variable_name = my_variable.name()

    # Retrieve a variable called "helloThere" by name.
    #    NOTE that None will be returned if no variable of that name is found.
    my_hello_there_variable = my_component.variable("helloThere")

    # In this case, the my_missing_variable will be None:
    my_missing_variable = myComponent.variable("nameThatDoesntExist")

    # This will cause a segfault as my_missing_variable is None:
    my_missing_name = my_missing_variable.name()





.. container:: dashlist

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
