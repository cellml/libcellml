.. _examples_view_model:

View the contents of a ``Model``
================================

All CellML entities exist in a hierarchical structure as shown below.
In some circumstances additional links are made between items (equivalent variables, for example), but on the whole it follows a basic tree structure.

.. code:: text

  Model
    │
    ├─ Units item(s)
    │   └─ Unit item(s)
    │
    └─ Component item(s)
        │
        ├─ Variable item(s)
        │
        ├─ Reset item(s)
        │   ├─ ResetValue item
        │   └─ TestValue item
        │
        ├─ Math item
        ╎
        └─ Child Component item(s)
             ╎
             └─ Grandchild Component item(s)

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

.. container:: gotcha

    Before accessing a collection item using an index, you can use the :code:`xyzCount()` function to return the number of items in the collection.

The following example shows how all variables in a component can be listed.

.. tabs::

  .. code-tab:: c++

      // Loop through variables in the component myComponent and retrieve their names.
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

  .. code-tab:: py

      # Loop through variables in the component myComponent and retrieve their names.
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


Some gotchas
------------
The ownership of some collections can be a little counter-intuitive.
One example is that :code:`Units` items are referenced by :code:`Variable` items, but are owned by the :code:`Model`; this is so that units can be reused across more than one component.
Another example involving encapsulation and :code:`Component` item ownership is shown below.

Consider the following model:

.. code::

    model: Grandfather
      component: Uncle
      component: Mother
        component: Daughter
        component: Son

The raw CellML syntax stores each component individually as children of the model, and separately stores the encapsulation structure of the nested components.

.. container:: toggle

  .. container:: header

    See CellML syntax

  .. code-block:: xml

    <model>

      <!-- The components are listed individually as children of the model block. -->
      <component name="Uncle"/>
      <component name="Mother"/>
      <component name="Daughter"/>
      <component name="Son"/>

      <!-- The encapsulation structure is stored separate from the components. -->
      <encapsulation>
        <component_ref component="Mother">
          <component_ref component="Daughter"/>
          <component_ref component="Son"/>
        </component_ref>
      </encapsulation>
    </model>


In libCellML, the encapsulation structure is embedded in the ownership of the components, so that one component can be a parent of another.
This can be confusing if the simple :code:`componentCount()` function on a model is called naively, as shown below.

.. tabs::

  .. code-tab:: c++

      // The number of components owned by the grandfather model refers *only* to its direct children:
      auto grandfatherHasTwoKids = grandfather->componentCount(); // returns 2

      // Each component must be interrogated individually to determine its children.
      //    Note that the uncle component is the 0th child of the grandfather model.
      auto uncleHasNoKids = grandfather->component(0)->componentCount();          // returns 0
      auto motherHasTwoKids = grandfather->component("Mother")->componentCount(); // returns 2

  .. code-tab:: py

      # The number of components owned by the grandfather model refers *only* to its direct children:
      grandfather_has_two_kids = grandfather->componentCount() # returns 2

      # Each component must be interrogated individually to determine its children.
      #    Note that the uncle component is the 0th child of the grandfather model.
      uncle_has_no_kids = grandfather.component(0).componentCount()          # returns 0
      mother_has_two_kids = grandfather.component("Mother").componentCount() # returns 2


Useful snippets
===============

Some useful snippets for viewing parts of your model are shown below.

.. include:: ../snippets/snippet_print_units.rst

.. include:: ../snippets/snippet_edit_mathml.rst

.. include:: ../snippets/snippet_print_encapsulation.rst

.. include:: ../snippets/snippet_print_equivalent_variables.rst
