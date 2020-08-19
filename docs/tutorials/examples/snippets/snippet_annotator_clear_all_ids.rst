.. _snippet_annotator_clear_all_ids:

.. container:: toggle

  .. container:: header-left

    Remove ids from all items

  In addition to creating id attributes, the :code:`Annotator` can be used to clear them from all items in the model.
  There are two ways in which this can be done.
  First, a :code:`Model` instance can be passed to the annotator for clearing. 
  This process will replace any previously stored model with the new one, as well as clearing all ids from the given model.
  Alternatively, if a model is already stored in the annotator instance, the ids of that stored model can be cleared by calling the `clearAllIds()` function without arguments.

  .. tabs::

    .. code-tab:: c++

      // Assuming we have two models, with references model1, and model2.

      // Create an Annotator instance.
      auto annotator = libcellml::Annotator::create();

      // EITHER: Pass a new Model to the annotator so that its ids can be cleared.
      annotator->clearAllIds(model1);  // This will clear ids in model1, 
                                       // and associate model1 with the annotator.

      // Note: There is no need to build the annotator's index beforehand as 
      // clearing the ids will also clear the index.  The model1 given will be
      // stored as the current model within the annotator.

      // OR: Clear all ids in a model which is was previously associated with the annotator.
      annotator->buildModelIndex(model2);
      annotator->clearAllIds();  // This will clear ids in model2, the model stored in the annotator.

    .. code-tabs:: python

      # Assuming we have two models, with references model1, and model2.

      # Create an Annotator instance.
      annotator = Annotator()

      # EITHER: Pass a new Model to the annotator so that its ids can be cleared.
      annotator.clearAllIds(model1)   # This will clear ids in model1, 
                                       # and associate model1 with the annotator.

      # Note: There is no need to build the annotator's index beforehand as 
      # clearing the ids will also clear the index.  The model1 given will be
      # stored as the current model within the annotator.

      # OR: Clear all ids in a model which is was previously associated with the annotator.
      annotator.buildModelIndex(model2)
      annotator.clearAllIds()  # This will clear ids in model2, the model stored in the annotator.
