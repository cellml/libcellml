.. _snippet_annotator_retrieve_duplicated_ids:

.. container:: toggle

  .. container:: header-left

    Retrieve items with duplicated ids

  Items with a unique id can be retrieved using the :code:`item("uniqueId")` function, items whose ids are not unique must be retrieved with the :code:`items("duplicatedId")` function instead.
  
  .. tabs::

    .. code-tab:: c++

      // Create an Annotator instance.
      auto annotator = libcellml::Annotator::create();

      // Pass the model to the annotator and build the index.
      annotator->buildModelIndex(model);

      auto duplicatedIdItems = annotator->items("duplicatedId");
      // The duplicateIdItems is a vector of AnyItem items; pairs whose first
      // attribute is an Annotator::Type enum, and the second is an std::any cast
      // of the item.

    .. code-tab:: python

      # Create an Annotator instance.
      annotator = Annotator()

      # Pass the model to the annotator and build the index.
      annotator.buildModelIndex(model)

      duplicatedIdItems = annotator.items("duplicatedId")
      # The duplicateIdItems is a vector of items with "duplicatedId" 
      # as an id attribute.
