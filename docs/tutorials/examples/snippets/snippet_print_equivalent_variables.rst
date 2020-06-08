.. _snippet_print_equivalent_variables:

.. container:: toggle

  .. container:: header-left

    Show example code

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
