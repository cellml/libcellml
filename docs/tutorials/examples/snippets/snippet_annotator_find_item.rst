.. _snippet_add_thing:

.. container:: toggle

  .. container:: header-left

    Find an item by id

  The :code:`AnyItem` type is a :code:`std::pair` containing:

  - first: an enumerated value representing the kind of item retrieved; and
  - second: the item itself, stored in a :code:`std::any` container.

  .. tabs::

    .. code-tab:: c++

      // Create an Annotator.
      auto annotator = libcellml::Annotator::create();

      // Build the annotator to work with the model.
      annotator->build(model);

      // Retrieve an item using its id attribute.
      AnyItem myItem = annotator->item("myItemId");

      // Declare a void pointer to the item before it's cast.
      void item;

      // Cast the item into its correct form using std::any_cast.
      switch(myItem.first){
        case libcellml::Annotator::Type::COMPONENT:
          item = std::any_cast<libcellml::Component>(myItem.second);



    .. code-tab:: python
