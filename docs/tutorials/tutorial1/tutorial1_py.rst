..  _tutorial1_py:

================================================================
Tutorial 1 Python: Reading and writing CellML files
================================================================

For overview, please see the :ref:`Tutorial 1 overview page<tutorial1>`.
These are the Python instructions.
For C++ please see the :ref:`Tutorial 1 C++<tutorial1_cpp>` page instead.

**Resources:**

- :download:`tutorial1.py` Either the skeleton code; or ...
- :download:`tutorial1_complete.py` the completed tutorial code; and
- :download:`../resources/tutorial1.cellml` The input CellML file to read.

.. contents:: Contents
    :local:

Setup
=====

For each of the tutorials, there is template code provided for you to get started in each of the :code:`tutorial*.py` files.

.. container:: dothis

    **0.a** Confirm that you're able to run the :code:`tutorial1.py` template against the libCellML library.
    Navigate into the :code:`tutorial1` directory and run the skeleton code file, :code:`tutorial1.py`.

.. code-block:: console

    cd tutorial1
    python tutorial1.py

This should give the output:

.. code-block:: console

    -----------------------------------------------------
        TUTORIAL 1: READING AND WRITING CellML2 FILES
    -----------------------------------------------------

Step 1: Deserialising a CellML file
===================================
CellML is a format in which all the information is stored in a strictly hierarchical  - or *serialised* - way.
In order for this information to be transformed into a format which can be used for modelling and simulation it needs to be *de-serialised* into the internal :code:`Model` format.
The hard work of this transformation is done by a :code:`Parser` object which will take a raw CellML string which represents a serialised model and return its corresponding de-serialised :code:`Model` item.

.. container:: dothis

    **1.a** Open the file and read its contents.

.. code-block:: python

    #  1.a   Open the tutorial1.cellml file for reading.
    read_file = open("../resources/tutorial1.cellml", "r")
    read_file_contents = read_file.read()

At this stage our :code:`read_file_contents` contains the raw CellML from the input file provided, :code:`tutorial1.cellml`.

**Note** that all the files for each tutorial are provided for you in the :code:`resources` folder: though they are designed to build from one to the next, you're able to use the ready-made ones if you want to jump in at any point.

.. container:: dothis

    **1.b** Now we need to transform the raw CellML import into the linked :code:`Model` using the :code:`Parser`.
    This is quite straightforward:

.. code-block:: python

    #  1.b   Create a libCellML Parser, and use it to parse the file
    #        string contents and convert it into a CellML Model structure.
    parser = libcellml.Parser()
    model = parser->parseModel(read_file_contents)

Now we have a *deserialsied* CellML model which we can manipulate using the libCellML library.

Step 2: Investigate the contents of the model
=============================================
Now that we have a model, let's see what's inside it.
All retrieval functions - where you want to read something about any item - are callable from simple functions naming the thing you want.
For example, to find the name of the model we simply call its :code:`name()` function:

.. code-block:: python

    my_model_name = my_first_model.name()
    my_model_id = my_first_model.id()

Obviously, the type of item you're retrieving will determine how you declare it: names and ids are returned as strings.

.. container:: dothis

    **2.a** Find out the name and id of your model and print it to the terminal.

The :code:`Model` itself stores two kinds of objects: a set of :code:`Units` objects, and a set of :code:`Component` objects.  There are generic :code:`somethingCount` functions which will return the number of :code:`Something` items within that object:

.. code-block:: python

    number_of_components = model.componentCount()

.. container:: dothis

    **2.b** Find out the number of :code:`Component` items in the model, and print it to the terminal.

Items like components and units (and later, variables) which are stored in sets can be accessed by their index as well as by their name.
At this stage, we don't *know* the name of the components, so we'll have to use their index to access them for printing to the terminal.
The indices begin from :code:`0`.

Each :code:`Component` itself (or later, :code:`Units` or :code:`Variable`) is retrieved from its parent item using the same idiom as the names and ids:

.. code-block:: python

    # Retrieve the 33rd component from my_first_model.  Note the indexing from zero.
    component_33 = my_first_model.component(32)

.. container:: dothis

    **2.c** Retrieve the first component from the model, and print its name and id to the terminal.

:code:`Component` items in turn contain four kinds of items, these being:

- a set of :code:`Variable` items;
- a :code:`MathML` string which controls the governing mathematical equations of the model behaviour;
- (for later) a set of :code:`Reset` items; and
- (also for later) an optional nested subset of :code:`Component` items too.

In this tutorial we'll only look at the variables and maths, leaving the nested components for :ref:`Tutorial 5<tutorial6_py>`.

.. container:: dothis

    **2.d** Retrieve the number of variables inside the component, and print it to the screen.

.. container:: dothis

    **2.e** Create a loop through the variables, retrieve the names of each, and them to the screen.

.. container:: dothis

    **2.f** We will look more at what the MathML string actually *means* in later tutorials, but for now, retrieve the MathML string from your component using the :code:`math()` function, and print it to the screen.

Step 3: Serialise the model and output
======================================
Now that you've seen how to *deserialise* a CellML file into a model using the :code:`Parser`, it's time to go in the other direction.
This reverse operation is handled by the :code:`Printer`, which will transform a model into a string for file output.

.. code-block:: python

    # Create a printer instance.
    printer = libcellml.Printer()

    # Use the printer to serialse a model into a string.
    serialised_model_string = printer->printModel(my_first_model)

.. container:: dothis

    **3.a** Create a printer and use it to serialise your model.

.. container:: dothis

    **3.b** Write that serialised string to a new :code:`.cellml` file.

.. container:: dothis

    **3.c** Go and have a cuppa, you're done :)
