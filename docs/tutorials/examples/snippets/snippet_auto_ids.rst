.. _snippet_auto_ids:

.. container:: toggle

  .. container:: header-left

    Set automatic ids throughout the model

  For times when you don't want to manually set id attributes through the model, you can use the :code:`Printer` to do it for you.
  When serialising a model using the :code:`printModel` function, the optional second argument is a boolean switch indicating whether or not to assign automatic :code:`id` attributes to any items which don't already have one.
  Existing :code:`id` attributes are unchanged by this process, and by default it is turned off.

  The automatic ids adhere to the :cellml2:`XML standard for id attributes<reference/formal_and_informative/specA2.html#xml-id-attributes>`, and take the form of a 6-digit hexadecimal number, beginning with a letter.

  .. tabs::

    .. code-tab:: c++

      // Create a Parser to deserialise a CellML (inString) string into a model.
      auto parser = libcellml::Parser::create();
      auto model = parser->parseModel(inString);

      // Create a Printer to serialse the model back to a string, but
      // use the option to create automatic ids.
      auto printer = libcellml::Printer::create();
      auto outString = printer->printModel(model, true);

      // The outString will have the same model contents, but with id attributes set throughout.

    .. code-tab:: python

      # Create a Parser to deserialise a CellML (in_string) string into a model.
      parser = libcellml.Parser()
      model = parser.parseModel(in_string)

      # Create a Printer to serialse the model back to a string, but
      # use the option to create automatic ids.
      printer = libcellml.Printer()
      out_string = printer.printModel(model, true)

      # The out_string will have the same model contents, but witht id attributes set throughout.
