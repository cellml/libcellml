.. _quickstart:

==============================
Quickstart and common examples
==============================

If you're reading this it's presumed that you're already familiar with the structure and usage of CellML models, and you want to get started on creating or reading your own as soon as possible.
If that doesn't sound like you, and you'd rather start with a gentler introduction, please start from :ref:`Tutorial 0<tutorial0>` instead.

**TODO** instalation guide to go here once processes are finalised.

This section explains the basic classes inside libCellML, and the most commonly used functionality associated with them.

.. contents::

General API strategy for use
============================
The tutorials here have taken a top-down approach to model creation. They start by creating components which define mathematical behaviour.
The :code:`Validator` is then called to list the variables and units which the mathematics requires.
This process is repeated until all the components needed have been created or imported, and the combined model is ready for output.
Model output takes one of two forms - either serialisation by writing to a CellML2.0 file using the Printer functionality, or code generation into C or Python using the Generator functionality.
Of course you are welcome to use the API in a top-down or bottom-up manner as you see fit.




Serialise a ``Model`` into CellML2 for printing to a file
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
The :code:`Printer` class has the opposite functionality to the :code:`Parser` class.
It accepts an existing :code:`ModelPtr` and creates a :code:`string` which can be written to a file.
As with the :code:`Parser` and the :code:`Validator`, the :code:`Printer` also records errors which can be accessed as above.

In C++:

.. code-block:: cpp

    // Create a Printer instance and pass the model into it.
    libcellml::PrinterPtr printer = libcellml::Printer::create();

    // The output of the printModel function is a string representing the serialised model.
    std::string serialisedModelString = printer->printModel(model);

    // Check the printer for errors.
    for (size_t e = 0; e < printer->errorCount(); ++e) {
        libcellml::IssuePtr error = printer->error(e);
        std::cout << error->description() << std::endl;
        std::cout << error->specificationReference() << std::endl
                  << std::endl;
    }

    // Write the serialised string to a file.
    std::string outFileName = "my_printed_file.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

In Python:

.. code-block:: python

    from libcellml import Printer

    # Create a Printer instance and pass the model into it.
    printer = Printer()

    # The output of the printModel function is a string representing the serialised model.
    serialised_model = printer.printModel(model)

    # Check the printer for errors.
    for e in range(0, printer.errorCount()):
        print(printer.error(e).description())
        print(printer.error(e).referenceHeading())

    # Write the string to a file.
    write_file = open("my_printed_file.cellml", "w")
    write_file.write(serialised_model)
    write_file.close()

Generate a C or Python version of a CellML2 model
+++++++++++++++++++++++++++++++++++++++++++++++++
Once you have a model, and have checked that it is free of validation errors, you can call the :code:`Generator` instance to create code which represents your model in either C or Python format.
For more information on the `Generator` please see the :ref:`Generator information<generator_notes>` pages.

Convert a CellML1.1 model to CellML2.0
++++++++++++++++++++++++++++++++++++++
libCellML deals exclusively with models which meet the :cellml2:`CellML2.0 specification`.
To use libCellML with a previous version (1.0, 1.1) you will need to first translate it into CellML2 using the :cellml1to2:`cellML1to2 <>` tool.

**TODO** Needs more instructions for how to use this and perhaps move to main repo?

Functionality associated with each class
========================================

Using the ``Model`` class
+++++++++++++++++++++++++
In C++:

.. code-block:: cpp

    // Create a new named model
    auto model = libcellml::Model::create("my_model");
    // Retrieve the name
    std::string modelName = model->name();

    // Add a component
    model->addComponent(component);
    // Count the direct child components
    int numComponents = model->componentCount();
    // Retrieve a component by index
    indexedComponent = model->component(0);
    // Retrieve a component by name
    namedComponent = model->component("my_component");

    // Add units
    model->addUnits(units);
    // Retrieve the number of units
    int numUnits = model->unitsCount();
    // Retrieve units by index
    indexedUnits = model->units(0);
    // Retrieve units by name
    namedUnits = model->units("my_units");


.. code-block:: python

    # Create a new model
    auto model = Model.create()
    # Set the name
    model.setName("my_model")
    # Retrieve the name
    modelName = model.name()

    # Add a component
    model.addComponent(component)
    # Count the direct child components
    numComponents = model.componentCount()
    # Retrieve a component by index
    indexedComponent = model.component(0)
    # Retrieve a component by name
    namedComponent = model.component("my_component")

    # Add units
    model.addUnits(units)
    # Retrieve the number of units
    numUnits = model.unitsCount()
    # Retrieve units by index
    indexedUnits = model.units(0)
    # Retrieve units by name
    namedUnits = model.units("my_units")


Using the ``Component`` class
+++++++++++++++++++++++++++++
Components are the building blocks of the CellML modelling process.
They are a modular representation of anything which is to be simulated, including the governing equations and their variables, and the relationship of this component to any of the others in the model.

Because components are named items, their basic use follows the same format as for other types of named items.

In C++

.. code-block:: cpp

    // Add a component to a model
    model->addComponent(component);
    // Add a child component to its parent
    parentComponent->addComponent(encapsulatedChildComponent);
    // Remove a child component: The childComponent now has a null parent() pointer
    parentComponent->removeComponent(childComponent);
    // Remove all child components
    parentComponent->removeAllComponents();

    // Count the child components
    int numberOfChildComponents = parentComponent->componentCount();
    // Access a child component by index (this returns a pointer to the second child)
    childComponent = parentComponent->component(1);
    // Access a child component by name
    childComponent = parentComponent->component("my_child");



**TODO** Not sure if this is the best strategy for documentation??


Create and naming items: ``Model``, ``Component``, ``Variable``, ``Units``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
The same idiom applies to all named items: these being :code:`Model`, :code:`Component`, :code:`Variable`, and :code:`Units` items.
For convenience, some constructors are overloaded with attributes which they'll need anyway.

In C++:

.. code-block:: cpp

    // Create items using the overloaded constructor to specify a name.
    auto m1 = libcellml::Model::create("my_model");
    auto c1 = libcellml::Component::create("my_component");
    auto v1 = libcellml::Variable::create("my_variable");
    auto u1 = libcellml::Units::create("my_units");

    // Create un-named items and use the setName() function to name them.
    auto m2 = libcellml::Model::create();
    m2->setName("my_model");

    auto c1 = libcellml::Component::create();
    c1->setName("my_component");

    auto v1 = libcellml::Variable::create();
    v1->setName("my_variable");

    auto u1 = libcellml::Units::create();
    u1->setName("my_units");


Retrieving named items: ``Model``, ``Component``, ``Variable``, ``Units``
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

**TODO**
