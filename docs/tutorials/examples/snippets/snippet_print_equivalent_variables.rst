.. _snippet_print_equivalent_variables:

.. container:: toggle

  .. container:: header-left

    Trace equivalent variables

  This example traces variable equivalences throughout the model using recursion.
  The CellML file read contains a model as shown below, where two pairs of equivalent variables (:code:`A` to :code:`B`, and :code:`B` to :code:`C`) connect three variables together.

  .. code:: text

    model:
        ├─ component: componentA
        │   └─ variable: A [dimensionless] <╴╴╴╮
        │                                      ╷
        │                                  equivalent
        ├─ component: componentB               ╵
        │   └─ variable: B [dimensionless] <╴╴╴╯<╴╴╴╮
        │                                           ╷
        │                                       equivalent
        └─ component: componentC                    ╵
            └─ variable: C [dimensionless] <╴╴╴╴╴╴╴╴╯

  .. container:: toggle

    .. container:: header

      Show CellML syntax

    .. code-block:: xml

      <?xml version="1.0" encoding="UTF-8"?>
        <model xmlns="http://www.cellml.org/cellml/2.0#"
          xmlns:cellml="http://www.cellml.org/cellml/2.0#" name="quickstart_traceEquivalence">
          <component name="componentA">
            <variable units="dimensionless" name="A" interface="public" />
          </component>
          <component name="componentB">
            <variable units="dimensionless" name="B" interface="public" />
          </component>
          <component name="componentC">
            <variable units="dimensionless" name="C" interface="public" />
          </component>
          <connection component_1="componentA" component_2="componentB">
            <map_variables variable_1="A" variable_2="B"/>
          </connection>
          <connection component_1="componentB" component_2="componentC">
            <map_variables variable_1="B" variable_2="C"/>
          </connection>
        </model>

  The example should output the connections between the variables, including discerning that :code:`A` is connected to :code:`C`, even though no direct relationship is specified in the model.

  .. code-block:: console

    Variable 'A' in component 'componentA' is connected to:
     - variable 'B' [dimensionless] in component 'componentB'
     - variable 'C' [dimensionless] in component 'componentC'

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

      from libcellml import Parser

      # This function will initialise the information strings to test, start
      # the search, and print the results.
      def print_equivalent_variable_set(variable):

          if variable is None:
              print("None variable submitted to print_equivalent_variable_set.")
              return

          variable_list = list()
          variable_list.append([variable.name(),
                               variable.parent().name(),
                               variable.units().name(),
                               variable.initialValue()])
          list_equivalent_variables(variable, variable_list)

          if len(variable_list) > 1:
              print("Variable '{v}' in component '{c}' is connected to:".format(
                  v=variable.name(), c=variable.parent().name()))
              for e in variable_list[1:]:
                  if e[3] != '':
                      print(" - variable '{v}'(t=0)={i} [{u}] in component '{c}'".format(
                          v=e[0], i=e[3], u=e[2], c=e[1]))
                  else:
                      print(" - variable '{v}' [{u}] in component '{c}'".format(
                          v=e[0], u=e[2], c=e[1]))
          else:
              print("Variable '{v}' is not connected to other variables.".format(
                  v=variable.name()))

      # This function performs the recursive search through all connections until the set
      # has been completely covered.
      def list_equivalent_variables(variable, variable_list):
          if variable is None:
              return
          for i in range(0, variable.equivalentVariableCount()):
              equivalent_variable = variable.equivalentVariable(i)
              # Form a list of strings that describe the equivalent variable.
              test = [equivalent_variable.name(),
                      equivalent_variable.parent().name(),
                      equivalent_variable.units().name(),
                      equivalent_variable.initialValue()]
              # If the equivalent variable has not already been checked, then start another recursion.
              if test not in variable_list:
                  variable_list.append(test)
                  list_equivalent_variables(equivalent_variable, variable_list)


      if __name__ == "__main__":

          read_file = open("../resources/quickstart_traceEquivalence.cellml", "r")

          #  Create a parser and read the file.
          parser = Parser()
          model = parser.parseModel(read_file.read())

          # Retrieve a variable from the parsed model
          A = model.component("componentA").variable("A")

          # Initiate the tracing for equivalent variables of variable "A"
          print_equivalent_variable_set(A)
