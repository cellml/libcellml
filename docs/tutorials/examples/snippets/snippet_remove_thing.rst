.. _snippet_remove_thing:

.. container:: toggle

  .. container:: header-left

    Remove a thing from a collection

  This example demonstrates the addition and removal of items from a collection.
  Note that while removal of items from a collection can be done by pointer symbol, by name, and by index, adding them is only possible via pointer.

  .. tabs::

    .. code-tab:: c++

      // Setup. Create four variables and a component.
      auto variable1 = libcellml::Variable::create("variable1");
      auto variable2 = libcellml::Variable::create("variable2");
      auto variable3 = libcellml::Variable::create("variable3");
      auto variable4 = libcellml::Variable::create("variable4");
      auto component = libcellml::Component::create("component");

      // Add variable1 into the component.  Note that the argument is
      // the symbol, not the name. Expect success to be true.
      auto success = component->addVariable(variable1);
      assert(success);

      // Repeat for the others.
      success = component->addVariable(variable2);
      success = component->addVariable(variable3);
      success = component->addVariable(variable4);

      // Remove variable2 from the component by pointer.
      success = component->removeVariable(variable2);
      assert(success);

      // Remove variable3 from the component by name.
      success = component->removeVariable("variable3");
      assert(success == true);

      // Remove variable4 from the component by index.
      success = component->removeVariable(1);
      assert(success == true);

      // Operations that will not succeed include:
      //  - Adding a variable more than once to the same component.
      success = component->addVariable(variable1);
      assert(success == false);

      //  - Removing a variable that doesn't exist in that component.
      success = component->removeVariable(variable2);
      assert(success == false);

      //  - Removing a variable by name that doesn't exist.
      success = component->removeVariable("iDontExist");
      assert(success == false);

      //  - Removing a variable by out-of-range index.
      success = component->removeVariable(9999);
      assert(success == false);

      //  - Adding a null pointer.
      success = component->addVariable(nullptr);
      assert(success == false);

      //  - Removing a null pointer.
      success = component->removeVariable(nullptr);
      assert(success == false);

    .. code-tab:: py

      # TODO
