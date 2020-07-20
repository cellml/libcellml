.. _snippet_add_thing:

.. container:: toggle

  .. container:: header-left

    Find an item by id

  The :code:`AnyItem` type is a :code:`std::pair` containing:

  - first: an enumerated value representing the kind of item retrieved; and
  - second: the item itself, stored in a :code:`std::any` container.

  Depending on whether you know the kind of item you're going to retrieve or not, you can use two different approaches.

  **You know the type of the item already**
  Where you know the type of item (eg: :code:`Component`, :code:`Variable` etc) before retrieving it, a collection of helper functions exist, as demonstrated below.
  Where the known type is an entity type, a pointer to the item is returned.
  Where the type is a non-entity type, pointers to significant related items are returned, as discussed earlier.

  .. tabs::

    .. code-tab:: c++

      // Create an Annotator.
      auto annotator = libcellml::Annotator::create();

      // Build the annotator to work with the model.
      annotator->build(model);

      // Retrieve entity items of known type using their id attribute.
      auto myComponent = annotator->component("myComponentId");
      auto myVariable = annotator->variable("myVariableId");
      auto myReset = annotator->reset("myResetId");
      auto myUnits = annotator->units("myUnitsId");
      auto myImportSource = annotator->importSource("myImportSourceId");
      auto myModel = annotator->model("myModelId");

      // Retrieve non-entity items of known type using their id attribute.
      // NOTE that the type of object returned by retriving a non-entity item
      // is defined in the text above.

      // Connections are returned as a VariablePair type, where the first and second
      // items in the pair define Variables in the first and second components of the
      // connection.  Note that as multiple variable pairs could exist between two
      // given components, the return value for this function is not unique.
      auto myConnection = annotator->connection("myConnectionId");

      // Variable equivalences (from the map_variables) are returned as a VariablePair,
      // where the first and second items in the pair define the Variables which are made
      // equivalent by this mapping.
      auto myMappedVariables = annotator->mapVariables("myMapVariablesId");

      // Unit items are returned as a UnitItem pair, where the first item is a pointer to
      // the parent Units item, and the second is the index at which the child unit item's
      // attributes can be found.
      auto myUnitItem = annotator->unit("myUnitId");
      std::string myUnitsReference;
      std::string myPrefix;
      std::string myId;
      double myExponent;
      double myMultiplier;

      // The first item in the pair is a pointer to the parent Units.
      myUnitItem.first->unitAttributes(myUnitItem.second, // The second item in the pair is the index.
                                       myReference, myPrefix, myExponent,
                                       myMultiplier,myId);

      // The location of a component in an encapsulation hierarchy is set by a component_ref
      // block.  Retrieving a component_ref item by id will return a pointer to the
      // Component item which is located at that position in the encapsulation.
      auto myReferencedComponent = annotator->componentRef("myComponentReferenceId");

      // The reset_value and test_value block children of a Reset item are returned as a
      // pointer to their parent Reset item.
      auto myTestValueParent = annotator->testValue("myTestValueId");
      auto myResetValueParent = annotator->resetValue("myResetValueId");
      // Their values can then be retrieved using the test_value() and
      // reset_value() functions on that Reset item parent.
      auto myTestValue = myTestValueParent->test_value();
      auto myResetValue = myResetValueParent->reset_value();

    .. code-tab:: python

      # Create an Annotator.
      annotator = Annotator()

      # Build the annotator to work with the model.
      annotator.build(model)

      # Retrieve entity items of known type using their id attribute.
      my_component = annotator.component("myComponentId")
      my_variable = annotator.variable("myVariableId")
      my_reset = annotator.reset("myResetId")
      my_units = annotator.units("myUnitsId")
      my_importSource = annotator.importSource("myImportSourceId")
      my_model = annotator.model("myModelId")

      # Retrieve non-entity items of known type using their id attribute.
      # NOTE that the type of object returned by retriving a non-entity item
      # is defined in the text above.

      # Connections are returned as a VariablePair type, where the first and second
      # items in the pair define Variables in the first and second components of the
      # connection.  Note that as multiple variable pairs could exist between two
      # given components, the return value for this function is not unique.
      my_connection = annotator.connection("myConnectionId")

      # Variable equivalences (from the map_variables) are returned as a VariablePair,
      # where the first and second items in the pair define the Variables which are made
      # equivalent by this mapping.
      my_mapped_variables = annotator.mapVariables("myMapVariablesId")

      # Unit items are returned as a UnitItem pair, where the first item is a pointer to
      # the parent Units item, and the second is the index at which the child unit item's
      # attributes can be found.
      my_unit_item = annotator.unit("myUnitId")

      # The first item in the pair is a pointer to the parent Units.
      # TODO: check how Python handles the std::pair class.

      # The location of a component in an encapsulation hierarchy is set by a component_ref
      # block.  Retrieving a component_ref item by id will return a pointer to the
      # Component item which is located at that position in the encapsulation.
      my_referenced_component = annotator.componentRef("myComponentReferenceId")

      # The reset_value and test_value block children of a Reset item are returned as a
      # pointer to their parent Reset item.
      my_test_value_parent = annotator.testValue("myTestValueId")
      my_reset_value_parent = annotator.resetValue("myResetValueId")
      # Their values can then be retrieved using the test_value() and
      # reset_value() functions on that Reset item parent.
      my_test_value = my_TestValueParent.test_value()
      my_reset_value = my_ResetValueParent.reset_value()
