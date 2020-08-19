.. _snippet_annotator_find_item_unknown_type:

.. container:: toggle

  .. container:: header-left

    Retrieve an item of unknown type by id

  In situations where you have an id string, but don't know the type of the object it identifies, the item can be retrieved using a general :code:`Annotator::item(itemId)` function.
  The general :code:`item` function will return an :code:`AnyItem` pair.
  The first part of the pair is an enum of the type of the object.
  The second part is an :code:`std::any` type object, which can be cast into the correct type.
  This is demonstrated below.

  .. tabs::

    .. code-tab:: c++

      // Create an Annotator.
      auto annotator = libcellml::Annotator::create();

      // Build the annotator to work with the model.
      annotator->buildModelIndex(model);

      // Retrieve an item of unknown type from the annotator.
      auto anyItem = annotator->item("findThisId");

      // Depending on the item's type (which is stored in the first part of the AnyItem
      // pair), cast the second part to the appropriate pointer type. Note that this means
      // first declaring a range of variables of different types to which the cast
      // pointer can be assigned.

      libcellml::ComponentPtr itemComponent;
      libcellml::VariablePtr itemVariable;
      libcellml::ResetPtr itemReset;
      libcellml::UnitsPtr itemUnits;
      libcellml::ImportSourcePtr itemImportSource;
      libcellml::VariablePair itemVariablePair;
      libcellml::UnitItem itemUnit;

      switch (anyItem.first) {
          case libcellml::Annotator::Type::COMPONENT:
          case libcellml::Annotator::Type::COMPONENT_REF:
              itemComponent = std::any_cast<libcellml::ComponentPtr>(anyItem.second);
              break;
          case libcellml::Annotator::Type::CONNECTION:
          case libcellml::Annotator::Type::MAP_VARIABLES:
              itemVariablePair = std::any_cast<libcellml::VariablePair>(anyItem.second);
              break;
          case libcellml::Annotator::Type::IMPORT:
              itemImportItem = std::any_cast<libcellml::ImportSourcePtr>(anyItem.second);
              break;
          case libcellml::Annotator::Type::ENCAPSULATION:
          case libcellml::Annotator::Type::MODEL:
              itemModel = std::any_cast<libcellml::ModelPtr>(anyItem.second);
              break;
          case libcellml::Annotator::Type::RESET:
          case libcellml::Annotator::Type::RESET_VALUE:
          case libcellml::Annotator::Type::TEST_VALUE:
              itemReset = std::any_cast<libcellml::ResetPtr>(anyItem.second);
              break;
          case libcellml::Annotator::Type::UNIT:
              itemUnit = std::any_cast<libcellml::UnitItem>(anyItem.second);
              break;
          case libcellml::Annotator::Type::UNITS:
              itemUnits = std::any_cast<libcellml::UnitsPtr>(anyItem.second);
              break;
          case libcellml::Annotator::Type::VARIABLE:
              itemVariable = std::any_cast<libcellml::VariablePtr>(anyItem.second);
              break;
          }
      }

      // Note also that attempting to cast into the wrong type will trigger a
      // "bad any cast" exception.
      try {
          assert(itemVariable.first == Annotator::Type::VARIABLE);
          auto thisWillNotWork = std::any_cast<libcellml::UnitsPtr>(itemVariable.second);
      }
      catch(const std::bad_any_cast& e) {
          // Depending on your system, this will return a "bad any cast", "bad any_cast"
          // or "bad_any_cast" message.
          std::cout << e.what() << std::endl;
      }

    .. code-tab:: python

      # TODO
