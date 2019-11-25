..  _tutorial1:

----------------------------------------
Tutorial 1: Reading, writing, 'rithmetic
----------------------------------------

Welcome to the introductory tutorial for the use of the libCellML library.
Using these tutorials in sequence will walk you through the functionality and
build your knowledge step by step. If, however, you just need to jump in and
figure out one specific idea, you can find a tutorial related to that subject
using the index.

After completing this tutorial you will be able to:

- read the contents of a CellML file
- deserialse its contents using the Parser to create a Model structure
- investigate the hierarchical contents of the Model, including the
  Components, Variables, and maths
- serialise the model and write to another file

Where you see the green indentation >> in this document it means that there's
something you need to do, and if you're stuck at any stage you can refer to
the completed "tutorial1_completed.cpp" file for help.

Step 0: Setup
-------------

For each of the tutorials, there is template code provided for you to get
started in each of the tutorial folders.

.. container:: dothis

    **>>** Navigate into the "tutorial1" folder and confirm that you're able to compile
    and run this template against the libCellML library

.. code::

    make

Running the template::

    ./tutorial1

... should give the output::

    -----------------------------------------------
    TUTORIAL 1: READING AND WRITING CELLML FILES
    -----------------------------------------------

Step 1: Deserialising a CellML file
-----------------------------------

CellML is a format in which all the information is stored in a strict
hierarchical way.  In order for this information to be transformed into a
format which can be *used* for modelling and simulation it needs to be
*deserialised* into the internal :code:`Model` format.  The hard work of
this transformation is done by the :code:`Parser` object which will take
a raw CellML string which represents a model and return its corresponding
:code:`Model` item.

.. container:: dothis

    **1.a** The first step is to read the file contents as-is:

.. code-block:: cpp

    std::ifstream inFile("tutorial1.cellml");
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();

At this stage our :code:`inFileContents` contains the raw CellML from the
input file provided, :code:`tutorial1.cellml`.

**Note** that all the files for each tutorial are provided for you in the
:code:`resources` folder: though they are designed to build from one to the
next, you're able to use the ready-made ones if you want to jump in at any
point.

.. container:: dothis

    **1.b** Now we need to transform the raw CellML import into the linked
    :code:`Model` using the :code:`Parser`.  This is quite straightforward:

.. code-block:: cpp

    // Create a parser instance
    libcellml::Parser parser;

    // Create a ModelPtr instance and populate it with the string contents
    // from the inFileContents item:
    libcellml::ModelPtr myFirstModel = parser.parseModel(inFileContents.str());

Now we have a *deserialsied* CellML model which we can manipulate using the
libCellML library.

Step 2: Investigate the contents of the model
---------------------------------------------

Now that we have a model, let's see what's inside it.  All retrieval functions
- where you want to read something about any item - are callable from simple
functions naming the thing you want. For example, to find the name of the model
we simply call its :code:`name()` function:

.. code-block:: cpp

    std::string modelName = myFirstModel->name();
    std::string modelId = myFirstModel->id();

Obviously, the type of item you're retrieving will determine how you declare
it: names and ids are returned as strings.

.. container:: dothis

    **2.a** Find out the name and id of your model and print it to the
    terminal.

The :code:`Model` itself stores two kinds of objects: a set of :code:`Units`
objects, and a set of :code:`Component` objects.  There are
generic :code:`somethingCount` functions which will return the number of
:code:`Something` items within that object:

.. code-block:: cpp

    int numberOfComponents = model->componentCount();

.. container:: dothis

    **2.b**
    Find out the number of :code:`Component` items in the model, and
    print it to the terminal.

Items like components and units (and later, variables) which are stored in sets
can be accessed by their index as well as by their name.  At this stage, we
don't *know* the name of the components, so we'll have to use their index to
access them for printing to the terminal.  The indices begin from :code:`0`.

Each :code:`Component` itself (or later, :code:`Units` or :code:`Variable`) is
retrieved from its parent item as a pointer (that is, a :code:`ComponentPtr`
type) using the same idiom as the names and ids:

.. code-block:: cpp

    // Retrieving the 33rd component from myFirstModel.  Note the indexing
    // from zero.
    libcellml::ComponentPtr thirtyThirdComponent = myFirstModel->component(32);

.. container:: dothis

    **2.c** Retrieve the first component from the model, and print its name and
    id to the terminal.

:code:`Component` items in turn contain four kinds of items, these being:

- a set of :code:`Variable` items
- a :code:`MathML` string which controls the governing mathematical equations
  of the model behaviour,
- (for later) a set of :code:`Reset` items, and
- (also for later) an optional nested subset of :code:`Component` items too.

In this tutorial we'll only look at the variables and maths, leaving the nested
components for Tutorial 6.

.. container:: dothis

    **2.d** Retrieve the number of variables inside your component, and print
    it to the screen.

.. container:: dothis

    **2.e** Create a loop through the variables, and print the names of each
    to the screen.

.. container:: dothis

    **2.f** We will look more at what the MathML string actually *means* in
    later tutorials, but for now, retrieve the MathML string from your
    component using the :code:`math()` function, and print it to the screen.

Step 3: Serialise the model and output
--------------------------------------
Now that you've seen how to *deserialise* a CellML file into a model using the
:code:`Parser`, it's time to go in the other direction.  This reverse operation
is handled by the :code:`Printer`, which will transform a model into a string
for file output.

.. code-block:: cpp

    libcellml::Printer printer;
    std::string serialisedModelString = printer.printModel(myFirstModel);

.. container:: dothis

    **3.a** Create a printer and use it to deserialise your model

.. container:: dothis

    **3.b** Write that serialised string to a new :code:`.cellml` file.

.. container:: dothis

    **4** Go and have a cuppa, you're done :)
















