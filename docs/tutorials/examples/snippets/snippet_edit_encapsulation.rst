


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

    .. code-tab:: python

      from libcellml import Parser
      from tutorial_utilities import print_encapsulation_structure_to_terminal

      if __name__ == "__main__":

          read_file = open("../resources/quickstart_editEncapsulation.cellml", "r")

          #  Create a parser and read the file.
          parser = Parser()
          model = parser.parseModel(read_file.read())

          # Print the current encapsulation structure to the terminal.
          print_encapsulation_structure_to_terminal(model)

          # Retrieve the "tomato" component from the "vegetable" component
          vegetables = model.component("vegetables")
          fruit = model.component("fruit")
          tomatoes = model.component("tomatoes")

          # Move the "tomatoes" component into "fruit".
          success = fruit.addComponent(tomatoes)

          # Print the structure and check that the components have
          # been transferred as expected.
          print_encapsulation_structure_to_terminal(model)
