.. _snippet_print_units:

.. container:: toggle

  .. container:: header-left

     Retrieve units needed by a component: variables and mathematics

  There are two places that need a reference to :code:`Units` items.
  The first is the set of :code:`Variable` items stored in the :code:`Component`: the units name for each of these is accessible in the :code:`name()` attribute of its :code:`units()` item.

  .. tabs::

    .. code-tab:: c++

      // This example assumes you already have a component defined.
      // You will need to #include <unordered_set> in your #include statements.
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
