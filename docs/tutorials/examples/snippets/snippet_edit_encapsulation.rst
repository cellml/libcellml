
.. _snippet_edit_encapsulation1:

.. container:: toggle

  .. container:: header-left

    Edit encapsulation structure of a model

  This example shows how the component :code:`tomatoes` which was orininally a child of the :code:`vegetables` component, could be moved to become a child of the :code:`fruit` component instead.
  When run, this snippet will give the output:

  .. code-block:: terminal

    Model 'quickstart_editEncapsulation' has 2 components
      - Component 'fruit' has 0 child components
      - Component 'vegetables' has 1 child components
          - Component 'tomatoes' has 0 child components

    Model 'quickstart_editEncapsulation' has 2 components
      - Component 'fruit' has 1 child components
          - Component 'tomatoes' has 0 child components
      - Component 'vegetables' has 0 child components

  .. tabs::

    .. code-tab:: c++

      #include <fstream>
      #include <sstream>
      #include <libcellml>
      #include "../utilities/tutorial_utilities.h"

      int main()
      {
          // Parse example model and component from the file provided.
          std::string inFileName = "../resources/quickstart_editEncapsulation1.cellml";
          std::ifstream inFile(inFileName);
          std::stringstream inFileContents;
          inFileContents << inFile.rdbuf();
          auto parser = libcellml::Parser::create();
          auto model = parser->parseModel(inFileContents.str());

          printEncapsulationStructureToTerminal(model);

          auto fruit = model->component("fruit");
          auto veges = model->component("vegetables");

          // The tomatoes component starts off as a child of the vegetables component.
          auto tomatoes = veges->component("tomatoes");

          // Move the tomatoes into its correct fruit component, and check the return boolean is true.
          auto success = fruit->addComponent(tomatoes);
          assert(success);

          printEncapsulationStructureToTerminal(model);
      }

    .. code-tab:: py

      from libcellml import Parser
      from tutorial_utilities import print_encapsulation_structure_to_terminal

      if __name__ == "__main__":

          read_file = open("../resources/quickstart_editEncapsulation.cellml", "r")

          #  Create a parser and read the file.
          parser = Parser()
          model = parser.parseModel(read_file.read())

          # Print the current encapsulation structure to the terminal.
          print_encapsulation_structure_to_terminal(model)

          # Retrieve the components.  Note that the "tomatoes" component starts
          # out as a child of the "vegetables" component.
          vegetables = model.component("vegetables")
          fruit = model.component("fruit")
          tomatoes = model.component("tomatoes")

          # Move the "tomatoes" component into "fruit".
          success = fruit.addComponent(tomatoes)

          # Print the structure and check that the components have
          # been transferred as expected.
          print_encapsulation_structure_to_terminal(model)
