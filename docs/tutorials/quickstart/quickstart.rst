.. _quickstart:

==============================
Quickstart and common examples
==============================

If you're reading this it's presumed that you're already familiar with the
structure and usage of CellML models, and you want to get started on creating
or reading your own as soon as possible.

**TODO** installation guide to go here once processes are finalised

This section explains the basic classes inside libCellML, and the most commonly
used functionality associated with them.

.. toctree::
 :maxdepth: 3


Change a CellML1.1 model to CellML2.0
+++++++++++++++++++++++++++++++++++++
libCellML deals exclusively with models which meet the CellML2 specification.
To use libCellML with a previous version (1.0, 1.1) you will need to first
translate it into CellML2 using the :cellml1to2:`cellML1to2 <>` tool.

**TODO** Needs more instructions for how to use this and perhaps move to main repo?

.. _include_libcellml_library:
Include the libCellML library in your project
+++++++++++++++++++++++++++++++++++++++++++++
If you've followed :ref:`the instructions for installing libCellML<tutorial0>`
then the library is available for use like this:

.. code-block:: cpp

  // main.cpp
  #include <libcellml>

Note that this doesn't invoke the libCellML namespace, so classes are accessed
using the ``libcellml::`` prefix.

.. code-block:: python

  # main.py
  import libcellml                       # imports the entire library
  from libcellml import Model, Variable  # import specific classes as needed


Parse an existing model from a file
+++++++++++++++++++++++++++++++++++
The following code will read a file called ``quickstart.cellml`` and deserialise
its contents into a ``ModelPtr`` instance:

In C++:

.. code-block:: cpp

    std::ifstream inFile("../resources/quickstart1.cellml");
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();

    // Creating a Parser instance
    libcellml::Parser parser;

    // Deserialising the CellML contents of the parsed file into a Model pointer
    libcellml::ModelPtr model = parser.parseModel(inFileContents.str());

    // Check the Parser for errors
    for(size_t e = 0; e < parser.errorCount(); ++e) {
      std::cout<<parser.error(e)->description()<<std::endl;
      std::cout<<parser.error(e)->specificationHeading()<<std::endl;
    }

In Python:

.. code-block:: python

    #  Open the CellML file for reading
    read_file = open("../resources/tutorial1.cellml", "r")

    #  Create a libCellML Parser, and use it to parse the file string contents
    #  and convert it into a CellML Model structure
    parser = Parser()
    model = parser.parseModel(read_file.read())

    # Check the parser for errors
    for e in range(0, parser.errorCount()):
        print(parser.error(e).description())
        print(parser.error(e).specificationHeading())


Debug and validate a model
++++++++++++++++++++++++++
The ``Validator`` class is used to check your final model for errors before
export or code generation, but it can also be used as a debugger
during the process of your model creation or editing.  The error descriptions
should give enough information to allow you to find and fix the problem, and
the specification heading refers to the section within the
:ref:`formal CellML2.0 description<formal_specification>` which is affected
by the error.

In C++:

.. code-block:: cpp

    // Create a Validator instance and pass the model to it for checking
    libcellml::Validator validator;
    validator.validateModel(model);

    // Retrieve the errors from the validator and print their specificiation
    // reference and description
    for (size_t e = 0; e < validator.errorCount(); ++e) {
        libcellml::ErrorPtr error = validator.error(e);
        std::cout << error->description() << std::endl;
        std::cout << error->specificationReference() << std::endl
                  << std::endl;
    }

In Python:

.. code-block:: python

    from libcellml import Validator

    # Create a Validator instance and pass it the model for checking
    validator = libcellml.Validator()
    validator.validateModel(model)

    # Check the validator for errors
    for e in range(0, validator.errorCount()):
        print(validator.error(e).description())
        print(validator.error(e).specificationHeading())


Serialise a model into CellML2 for printing to a file
+++++++++++++++++++++++++++++++++++++++++++++++++++++
The ``Printer`` class has the opposite functionality to the ``Parser`` class.
It accepts an existing ``ModelPtr`` and creates a ``string`` which can be
written to a file.  As with the ``Parser`` and the ``Validator``, the
``Printer`` also records errors which can be accessed as above.

In C++:

.. code-block:: cpp

    // Create a Printer instance and pass the model into it
    libcellml::Printer printer;

    // The output of the printModel function is a string representing the serialised model
    std::string serialisedModelString = printer.printModel(model);

    // Check the printer for errors
    for (size_t e = 0; e < printer.errorCount(); ++e) {
        libcellml::ErrorPtr error = printer.error(e);
        std::cout << error->description() << std::endl;
        std::cout << error->specificationReference() << std::endl
                  << std::endl;
    }

    // Write the serialised string to a file
    std::string outFileName = "my_printed_file.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

In Python:

.. code-block:: python

    from libcellml import Printer

    # Create a Printer instance and pass the model into it
    printer = Printer()

    # The output of the printModel function is a string representing the serialised model
    serialised_model = printer.printModel(model)

    # Check the printer for errors
    for e in range(0, printer.errorCount()):
        print(printer.error(e).description())
        print(printer.error(e).specificationHeading())

    # Write the string to a file
    write_file = open("my_printed_file.cellml", "w")
    write_file.write(serialised_model)
    write_file.close()

Generate a C or Python version of a model
+++++++++++++++++++++++++++++++++++++++++
Once you have a model, and have checked that it is free of validation errors,
you can call the ``Generator`` isntance to create code which represents your
model in either C or Python format.  For more information on the
``Generator`` please see the :ref:`Generator information<generator_notes>`
pages.

Create or edit a model using the API
++++++++++++++++++++++++++++++++++++
To create a new model

Create or edit a component
==========================================

Create or edit a variable
==========================================

Create or edit units
==========================================

Control mathematical behaviour
==========================================
