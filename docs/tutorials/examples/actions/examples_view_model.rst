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

  .. container:: header-left

    Print a list of units required by a component

  .. container:: infospec

    There are two places that need a reference to :code:`Units` items.
    The first is the set of :code:`Variable` items stored in the :code:`Component`: the units name for each of these is accessible in the :code:`name()` attribute of its :code:`units()` item.

    .. tabs::

      .. code-tab:: c++

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

      .. code-tab:: py

          # This example assumes that you have a component already, containing variables and MathML.

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


.. container:: toggle

  .. container:: header-left

    Print the encapsulation structure of a model

  .. container:: infospec

    Because components may be nested to any depth within an encapsulation hierarchy, we need to use recursive functions in order to be sure of reaching the bottom level.
    The examples below define two functions - one to initiate the recursion, and one to carry it out.

    .. tabs::

      .. code-tab:: c++

        // This function is called to initiate the recursion:
        void printEncapsulationStructureToTerminal(libcellml::ModelPtr &model)
          {
              // Prints the encapsulation structure of the model to the terminal
              std::string spacer = "  - ";
              std::cout << "Model '" << model->name() << "' has " << model->componentCount()
                        << " components" << std::endl;
              for (size_t c = 0; c < model->componentCount(); ++c) {
                  auto child = model->component(c);
                  printComponentOnlyToTerminal(child, spacer);
              }
          }

          // This function performs the recursion to the full depth of the encapsulation:
          void printComponentOnlyToTerminal(libcellml::ComponentPtr &component, std::string spacer)
          {
              std::cout << spacer << "Component '" << component->name() << "' has " << component->componentCount() << " child components" << std::endl;
              for (size_t c = 0; c < component->componentCount(); c++) {
                  std::string anotherSpacer = "    " + spacer;
                  auto child = component->component(c);
                  printComponentOnlyToTerminal(child, anotherSpacer);
              }
          }

      .. code-tab:: py

        # Prints the encapsulation structure of the model to the terminal.  This
        # function intitiates the recursion through the encapsulation structure.
        def print_encapsulation_structure_to_terminal(model):
          spacer = "  - "
          print("Model '{m}' has {c} components".format(m=model.name(), c=model.componentCount()))

          for c in range(0, model.componentCount()):
              child_component = model.component(c)
              print_component_only_to_terminal(child_component, spacer)
          print()

        # This function performs the recursion, and explores all child components.
        def print_component_only_to_terminal(component, spacer):
            print("{s}Component '{c}' has {n} child components".format(
                s=spacer,
                c=component.name(),
                n=component.componentCount()))

            for c in range(0, component.componentCount()):
                another_spacer = "    " + spacer
                child_component = component.component(c)
                print_component_only_to_terminal(child_component, another_spacer)
            print()


.. container:: toggle

  .. container:: header-left

    Print the set of variables equivalent to a given variable

  .. container:: infospec

    This example traces variable equivalences throughout the model using recursion.
    The first function :code:`printEquivalentVaribleSet` initiates the recursion, and the second :code:`listEquivalentVariables` performs it.

    .. tabs::

      .. code-tab:: c++

        // Function to initiate a list of variables in the connected set, to start the recursion, and to print
        // the list to the terminal.
        void printEquivalentVariableSet(const libcellml::VariablePtr &variable)
        {
            if (variable == nullptr) {
                std::cout << "NULL variable submitted to printEquivalentVariableSet." << std::endl;
                return;
            }
            std::vector<libcellml::VariablePtr> variableList;
            variableList.push_back(variable);
            listEquivalentVariables(variable, variableList);

            // The parent() function returns an EntityPtr, which must be cast to a Component before its name()
            // function can be called.
            libcellml::ComponentPtr component = std::dynamic_pointer_cast<libcellml::Component>(variable->parent());

            if (component != nullptr) {
                std::cout << "Tracing: " << component->name() << " -> "
                          << variable->name();
                if (variable->units() != nullptr) {
                    std::cout << " [" << variable->units()->name() << "]";
                }
                if (variable->initialValue() != "") {
                    std::cout << ", initial = " << variable->initialValue();
                }
                std::cout << std::endl;
            }

            // The variableList contains the variable that was submitted for testing originally, so
            // if it's connected to other variables, it must have a length greater than 1.
            if (variableList.size() > 1) {
                for (auto &e : variableList) {
                    component = std::dynamic_pointer_cast<libcellml::Component>(e->parent());
                    if (component != nullptr) {
                        std::cout << "    - " << component->name() << " -> " << e->name();
                        if (e->units() != nullptr) {
                            std::cout << " [" << e->units()->name() << "]";
                        }
                        if (e->initialValue() != "") {
                            std::cout << ", initial = " << e->initialValue();
                        }
                        std::cout << std::endl;
                    } else {
                        std::cout << "Variable " << e->name() << " does not have a parent component." << std::endl;
                    }
                }
            } else {
                std::cout << "    - Not connected to any equivalent variables." << std::endl;
            }
        }

        // This function performs the recursive search through all connections until the set
        // has been completely covered.
        void listEquivalentVariables(const libcellml::VariablePtr &variable,
                                     std::vector<libcellml::VariablePtr> &variableList) {
            if (variable == nullptr) {
                return;
            }

            for (size_t i = 0; i < variable->equivalentVariableCount(); ++i) {
                libcellml::VariablePtr equivalentVariable = variable->equivalentVariable(i);
                if (std::find(variableList.begin(), variableList.end(), equivalentVariable) == variableList.end()) {
                    variableList.push_back(equivalentVariable);
                    listEquivalentVariables(equivalentVariable, variableList);
                }
            }
        }

      .. code-tab:: py

        def print_equivalent_variable_set(variable):

          if variable is None:
            print("None variable submitted to print_equivalent_variable_set.")
            return

          variable_set = set()
          variable_set.add(variable)
          list_equivalent_variables(variable, variable_set)

          component = variable.parent()
          print_me = ''
          if component != None:
            print_me += "Tracing: {c}.{v}".format(c=component.name(), v=variable.name())
            if variable.units() is not None:
              print_me += " [{u}]".format(u=variable.units().name())
            if variable.initialValue() != "":
                print_me += ", initial = {i}".format(i=variable.initialValue())

            print(print_me)

          # The variable_set contains the variable that was submitted for testing originally, so
          # if it's connected to other variables, it must have a length greater than 1.
          if len(variable_set) > 1:
            for e in variable_set:
              print_me = ''
              component = e.parent()
              if component is not None:
                print_me += "    - {c}.{v}".format(c=component.name(), v=e.name())
                if e.units() is not None:
                  print_me += " [{u}]".format(u=e.units().name())
                if e.initialValue() != "":
                  print_me += ", initial = {i}".format(i=e.initialValue())
                print(print_me)
              else:
                print("Variable {v} does not have a parent component.".format(v=e.name()))
          else:
            print("    - Not connected to any equivalent variables.")

        # This function performs the recursive search through all connections until the set
        # has been completely covered.
        def list_equivalent_variables(variable, variable_set):
          if variable is None:
            return
          for i in range(0, variable.equivalentVariableCount()):
            equivalent_variable = variable.equivalentVariable(i)
            if equivalent_variable not in variable_set:
              variable_set.push_back(equivalent_variable)
              list_equivalent_variables(equivalent_variable, variable_set)

.. container:: toggle

  .. container:: header-left

    Print the MathML block of a component

  .. container:: infospec

    MathML is stored as a single string within a component.
    Retrieving it is simple enough using the :code:`math()` function, but any manipulation (change units used, changing variable names, adding additional relationships, etc) are a little more complicated.

    .. tabs::

      .. code-tab:: c++

        // C++ example

      .. code-tab:: py

        # Python example
