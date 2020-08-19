.. _examples_print_model:

Serialise a ``Model`` into CellML 2.0 for printing to a file
============================================================
The :code:`Printer` class has the opposite functionality to the :code:`Parser` class.
It accepts an existing :code:`ModelPtr` and creates a :code:`string` which can be written to a file.
As with the :code:`Parser` and the :code:`Validator`, the :code:`Printer` also records a collection of :code:`Issue` items which can be accessed as shown below.

.. tabs::

  .. code-tab:: c++

    // Create a Printer instance.
    auto printer = libcellml::Printer::create();

    // The output of the printModel function is a string representing the serialised input model.
    std::string serialisedModelString = printer->printModel(model);

    // Check the printer for issues.
    assert(printer->issueCount() == 0);

    // Write the serialised string to a file.
    std::string outFileName = "my_printed_file.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

  .. code-tab:: py

    from libcellml import Printer

    # Create a Printer instance.
    printer = Printer()

    # The output of the printModel function is a string representing the serialised input model.
    serialised_model = printer.printModel(model)

    # Check the printer for issues.
    assert(printer.issueCount() == 0)

    # Write the string to a file.
    write_file = open("my_printed_file.cellml", "w")
    write_file.write(serialised_model)
    write_file.close()

Details of any issues that the printer encounters and records can be retrieved as described on the :ref:`Retrieve Issue items<examples_get_issues>` page.
