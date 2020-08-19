.. _snippet_annotator_auto_ids:

.. container:: toggle

  .. container:: header-left

    Locate items with duplicate ids

  The :code:`Annotator` functionality can be used to report id strings which have been duplicated within a model's scope, as well as to return all items associated with a duplicated id string.
  
  .. tabs::

    .. code-tab:: c++

      // Create an Annotator instance.
      auto annotator = libcellml::Annotator::create();

      // Create a model, with the id string "duplicateId" used on a component
      // and a variable item, and an id string "anotherDuplicateId" on a units
      // and encapsulation item.
      auto model = libcellml::Model::create("myModelName");
      auto component = libcellml::Component::create("myComponentName");
      auto variable = libcellml::Variable::create("myVariableName");
      auto units = libcellml::Units::create("myUnitsName");

      model->addComponent(component);
      model->addUnits(units);
      component->addVariable(variable);

      // Set the ids.
      component->setId("duplicateId");
      variable->setId("duplicateId");
      units->setId("anotherDuplicateId");
      model->setEncapsulationId("anotherDuplicateId");

      // Pass the model to the annotator and build the index.
      annotator->buildModelIndex(model);

      // Retrieve a list of duplicated ids from the annotator.
      auto duplicateIdList = annotator->duplicateIds();

      // Now duplicateIdList is a vector of strings of the ids which are duplicated.
      // In this example it will contain "duplicateId", and "anotherDuplicateId".

    .. code-tab:: python

      # Create an Annotator instance.
      annotator = Annotator()

      # Create a model, with the id string "duplicateId" used on a component
      # and a variable item, and an id string "anotherDuplicateId" on a units
      # and encapsulation item.
      model = Model("myModelName")
      component = Component("myComponentName")
      variable = Variable("myVariableName")
      units = Units("myUnitsName")

      model.addComponent(component)
      model.addUnits(units)
      component.addVariable(variable)

      # Set the ids.
      component.setId("duplicateId")
      variable.setId("duplicateId")
      units.setId("anotherDuplicateId")
      model.setEncapsulationId("anotherDuplicateId")

      # Pass the model to the annotator and build the index.
      annotator.buildModelIndex(model)

      # Retrieve a list of duplicated ids from the annotator.
      duplicateIdList = annotator.duplicateIds()

      # Now duplicateIdList is a vector of strings of the ids which are duplicated.
      # In this example it will contain "duplicateId", and "anotherDuplicateId".
