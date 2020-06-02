.. _quickstart_parse_model:

Parse an existing ``Model`` from a file
+++++++++++++++++++++++++++++++++++++++
The following code will read a file called :code:`quickstart.cellml` and deserialise its contents into a :code:`ModelPtr` instance:

In C++:

.. code-block:: cpp

    std::ifstream inFile("../resources/quickstart.cellml");
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();

    // Creating a Parser instance
    auto parser = libcellml::Parser::create();

    // Deserialising the CellML contents of the parsed file into a Model pointer
    libcellml::ModelPtr model = parser->parseModel(inFileContents.str());

    // Checking the Parser for errors
    for(size_t e = 0; e < parser->errorCount(); ++e) {
      std::cout<<parser->error(e)->description()<<std::endl;
      std::cout<<parser->error(e)->referenceHeading()<<std::endl;
    }

In Python:

.. code-block:: python

    from libcellml import Parser

    #  Open the CellML file for reading
    read_file = open("../resources/quickstart.cellml", "r")

    #  Create a libCellML Parser, and use it to parse the file string contents
    #  and convert it into a CellML Model structure
    parser = Parser()
    model = parser.parseModel(read_file.read())

    # Check the parser for errors
    for e in range(0, parser.errorCount()):
        print(parser.error(e).description())
        print(parser.error(e).referenceHeading())
