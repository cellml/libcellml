.. _examples_parse_model:

Parse an existing ``Model`` from a file
=======================================
The following code will read a file called :code:`quickstart.cellml` and deserialise its contents into a :code:`ModelPtr` instance.

.. tabs::

    .. code-tab:: c++

        std::ifstream inFile("../resources/quickstart.cellml");
        std::stringstream inFileContents;
        inFileContents << inFile.rdbuf();

        // Create a Parser instance.
        auto parser = libcellml::Parser::create();

        // Deserialise the CellML contents of the parsed file into a Model.
        auto model = parser->parseModel(inFileContents.str());

    .. code-tab:: py

        from libcellml import Parser

        #  Open the CellML file for reading.
        read_file = open("../resources/quickstart.cellml", "r")

        #  Create a libCellML Parser, and use it to parse the file string contents
        #  and convert it into a CellML Model structure.
        parser = Parser()
        model = parser.parseModel(read_file.read())

Note that the :code:`Parser` class will make a note of any issues it finds, which can be accessed as described in the :ref:`Retrieve Issue items<examples_get_issues>` page.
