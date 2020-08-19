.. _snippet_print_encapsulation:

.. container:: toggle

  .. container:: header-left

    Print encapsulation structure

  Because components may be nested to any depth within an encapsulation hierarchy, we need to use recursive functions to be sure of reaching the bottom level.
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
