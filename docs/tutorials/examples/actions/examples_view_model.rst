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

.. code-block:: cpp

    // The number of components owned by the grandfather model refers *only* to its direct children:
    auto grandfatherHasTwoKids = grandfather->componentCount(); // returns 2

    // Each component must be interrogated individually to determine its children.
    //    Note that the uncle component is the 0th child of the grandfather model.
    auto uncleHasNoKids = grandfather->component(0)->componentCount();          // returns 0
    auto motherHasTwoKids = grandfather->component("Mother")->componentCount(); // returns 2

.. code-block:: python

    # The number of components owned by the grandfather model refers *only* to its direct children:
    grandfather_has_two_kids = grandfather->componentCount() # returns 2

    # Each component must be interrogated individually to determine its children.
    #    Note that the uncle component is the 0th child of the grandfather model.
    uncle_has_no_kids = grandfather.component(0).componentCount()          # returns 0
    mother_has_two_kids = grandfather.component("Mother").componentCount() # returns 2


Useful snippets
===============

Some useful snippets for viewing parts of your model are shown below.

.. container:: toggle

  .. container:: header

    Print a list of units required by a component



  There are two places that need a reference to :code:`Units` items.
  The first is the set of :code:`Variable` items stored in the :code:`Component`: the units name for each of these is accessible in the :code:`name()` attribute of its :code:`units()` item.

  .. container:: toggle

    .. container:: header

      See C++ code example

    .. code-block:: cpp

      // This example assumes you already have a component defined.
      // You will need to include <unordered_set> in your #include statements.
      std::unordered_set<std::string> unitsNames;

      // Iterate through the variables in this component, and add their units' names to the set.
      for (size_t v = 0; v < component->variableCount(); ++v) {
          // Get the units for this variable:
          auto myUnits = component->variable(v)->units();
          // Check that this is not the nullptr, otherwise skip.
          if (myUnits != nullptr) {
              // Add name to set if not already there.
              unitsNames.insert(myUnits->name());
          }
      }

      // Parse the MathML string to find any units used by <cn> constants:
      std::string delimiter = "cellml:units=";
      std::string maths = component->math();
      size_t pos = maths.find(delimiter); // Start looking for the name after the first delimiter.
      size_t pos2;
      std::string segment;
      std::string name;
      while ((pos = maths.find(delimiter)) != std::string::npos) {
          segment = maths.substr(0, pos);
          segment.erase(0, segment.find("\"")); // Remove the first quote mark after the delimiter.
          pos2 = segment.find("\""); // Find the second quote mark.
          name = segment.substr(0, pos2); // Units name is between the two quotes.
          if (name.length()) { // Sanity check that the string is not empty.
              unitsNames.insert(name);
          }
          maths.erase(0, pos + delimiter.length()); // Remove this segment from the main string.
      }
      // Search the final remaining segment.
      segment = maths;
      segment.erase(0, 1);
      pos2 = segment.find("\"");
      name = segment.substr(0, pos2);
      if (name.length()) {
          unitsNames.insert(name);
      }

      // Print the unique units for this component to the terminal.
      for (const auto &name : unitsNames) {
          std::cout << "  - " << name << std::endl;
      }

  .. container:: toggle

    .. container:: header

      See Python code example

    .. code-block:: py

        # Retrieve the component as a pointer.
        component = model.component("component")

        # Initialise an empty set to save the units names.
        units_names = set()

        # Iterate through the variables in this component, and add their units' names to the set.
        for v in range(0, component.variableCount()):
            # Get the units for this variable:
            my_units = component.variable(v).units()
            # Check that this is not the nullptr, otherwise skip.
            if my_units is not None:
                # Add name to set if not already there.
                units_names.add(my_units.name())

        # Parse the MathML string to find any units used by <cn> constants:
        delimiter = "cellml:units="
        maths_string = component.math()
        segments = maths_string.split(delimiter)
        # Start looking for the name after the first delimiter.
        for segment in segments[1:]:
            # Split the segment at quotation marks, and take the one at index 1
            name = segment.split('"')[1]
            if (len(name)):  # Sanity check that the string is not empty.
                units_names.add(name)

        # Print the unique units for this component to the terminal.
        print("The units needed by component {c} are:".format(c=component.name()))
        for name in units_names:
            print("  - {n}".format(n=name))










Print the encapsulation structure of a model

Print the set of variables equivalent to a given variable

Print the MathML block of a component







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
