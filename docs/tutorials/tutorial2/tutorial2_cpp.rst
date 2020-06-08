..  _tutorial2_cpp:

========================================================
Tutorial 2 C++: Debugging, error checking and validating
========================================================

The outline for this tutorial is shown on the :ref:`Tutorial 2<tutorial2>` page.
These are the C++ instructions.
For the same tutorial in Python please see the :ref:`Tutorial 2 in Python<tutorial2_py>` page instead.

**Requirements**

- :download:`CMakeLists.txt` The CMake file for building this tutorial;
- :download:`tutorial2.cpp` Either the skeleton code or :download:`tutorial2_complete.cpp` the completed tutorial code;
- :download:`../resources/tutorial2.cellml` The input CellML file to read;
- :download:`../utilities/tutorial_utilities.h` and :download:`../utilities/tutorial_utilities.cpp` Utility functions for
  use in the tutorials.

.. contents:: Contents
    :local:

0: Setup
========
Navigate into the :code:`tutorial2` folder and check that you can build the template against the libCellML library successfully:

.. code-block:: console

    cmake -DINSTALL_PREFIX=../../install .
    make -j

Running the template:

.. code-block:: console

    ./tutorial2

... should give the output:

.. code-block:: console

    -----------------------------------------------
       TUTORIAL 2: ERROR CHECKING AND VALIDATION
    -----------------------------------------------

Step 1: Create a ``Model`` from the contents of a CellML file
=============================================================

.. container:: dothis

    **1.a** As you did in :ref:`Tutorial 1<tutorial1_cpp>`, use the :code:`Parser` to create a model from the "Tutorial2.cellml" file provided.

Step 2: Print the contents of the file to the screen
====================================================

Instead of duplicating the work you did throughout the middle steps of :ref:`Tutorial 1<tutorial1_cpp>`, we've provided you with a set of utility functions in the :code:`utility/tutorial_utilities.[cpp,h]` files which will help with some of the repeated bits of these tutorials.

.. container:: dothis

    **2.a** Use the utility function :code:`printModelToTerminal(yourModelHere)` to output the contents of the model you just created to the terminal so that you can see it properly.

Within the libCellML library is the :code:`Validator` class.
This has one job: to make sure that what you give it is *valid* in terms of its CellML2.0 compliance.
Does it mean that your simulations will work the way you expect?
Nope, you can still write rubbish!
You can think of the validation being the spell-checker for your model.
It doesn't judge the meaning of *what* you've written, just the nitty-gritty of *how* you've written it.

The validator can also help you as you create and edit models by pointing out what's missing or incorrect as you go.
This is really easy:

.. code-block:: cpp

    auto validator = libcellml::Validator::create();
    validator->validateModel(yourModelHere);

.. container:: dothis

    **2.b** Create a validator instance and pass your model to it, as above.

When you've created a :code:`Validator` object and called it to check a model, a record of any errors is stored inside the validator.
To figure out what's going on, you need to retrieve the pointers to these :code:`Issue` objects.

As in :ref:`Tutorial 1<tutorial1_cpp>`, we can call a :code:`count` function (in the case of a validator, this is the :code:`errorCount()` function to determine whether any errors have been raised.

.. container:: dothis

    **2.c** Retrieve the number of errors from the validator, and print it to the terminal.

Now we need to create an iterative loop to retrieve all the errors (and there should be a few in this particular model!) from the validator.
Again following the same retrieval idiom as in Tutorial 1 for items in sets, we can access the errors using an index:

.. code-block:: cpp

    libcellml::IssuePtr theFifteenthError = validator->error(14);

Inside an :code:`Issue` structure are two fields which are really useful.
These are the :code:`description` (which does what you'd think) and the :code:`referenceHeading`, which points you to the section in the CellML2.0 specification document for reference.

.. container:: dothis

    **2.d** Create a loop (to the number of errors found in 2.c), retrieve each error pointer, and print the description and specification reference to the screen.
    This is what we've used:

.. code-block:: cpp

    for (size_t e = 0; e < validator->errorCount(); ++e) {

        // Retrieve the e'th error as a pointer:
        libcellml::IssuePtr validatorError = validator->error(e);

        std::cout << "  Validator error[" << e << "]:" << std::endl;

        // Print the description to the screen:
        std::cout << "     Description: " << validatorError->description()
                  << std::endl;

        // Print the specification reference to the screen:
        std::cout << "    See section " << validatorError->referenceHeading()
                  << " in the CellML specification." << std::endl;
    }

Step 3: Fix the errors that were reported
=========================================
As you go through these tutorials you should be able to compile and run your code at any stage.
If you haven't been doing so already, then do it now, and take a look at what you've printed.
This section works through each of the errors found and shows you how to fix them.

.. code-block:: console

    Validator error[0]:
        Description: CellML identifiers must not begin with a European numeric character [0-9].
        See section 3.1.4 in the CellML specification.
    Validator error[1]:
        Description: Variable does not have a valid name attribute.
        See section 11.1.1.1 in the CellML specification.

These errors refer to the same thing, but are better read in reverse order.
Variables (and everything else in CellML which specifies a name attribute) must have the correct format.
Comparing the error to the names of entities printed in the terminal we can see that :code:`variable[0]` in :code:`component[0]` doesn't have a valid name (because it starts with a digit).
Let's fix that.

Remembering from the last tutorial that we can access items through their indices, now we can use the :code:`setSomething(someValue)` idiom to fix the variable name:

.. code-block:: cpp

    // Access the 0th variable of the 0th component and set its name to "A":
    yourModelHere->component(0)->variable(0)->setName("A");

.. container:: dothis

    **3.a** Add the fix above and check that it has indeed removed those errors from the list reported.

-----

On to the next error.

.. code-block:: console

    Validator error[2]:
        Description: Variable 'b' has an invalid units reference 'i_am_not_a_unit'
        that does not correspond with a standard unit or units in the variable's
        parent component or model.
        See section 11.1.1.2 in the CellML specification.

Variables must have a unit defined.
These can be either something from the built-in list within libCellML (which you can read in the specifications document), or something you define yourself.
We'll look at user defined units in :ref:`Tutorial 3<tutorial3_cpp>`, but for now it's enough to see that the units which are associated with variable :code:`b` are not valid.
We'll change it to be :code:`"dimensionless"` instead.

.. container:: NB

    **Remember** that items can be accessed through their name (as below) or their index (as above).

.. code-block:: cpp

    // Access the variable named "b" inside the "i_am_a_component" component
    // and set its units to be "dimensionless".
    yourModelHere->component("i_am_a_component")->variable("b")->setUnits("dimensionless");

.. container:: dothis

    **3.b** Add the fix for this error and check that it's worked by running your code.

-----

.. code-block:: console

    Validator error[3]:
        Description: Variable 'c' has an invalid initial value
        'this_variable_doesnt_exist'. Initial values must be a real number
        string or a variable reference.
        See section 11.1.2.2 in the CellML specification.

We can either access members by their index or their name, as shown above, or we can create a pointer to them instead (as below).
Initial values (if set) must be a valid variable name in the same component, or a real number.

.. code-block:: cpp

    // Retrieve a pointer for the problem variable with a combo of names and index.
    auto variableC = model->component(0)->variable("c");

    // Fix the initial value of the variable.  Note that this could also be a
    // variable name in the same component.
    variableC->setInitialValue(20.0);

.. container:: dothis

    **3.c** Add the fix for this error and check that it's worked by running your code.

-----

.. code-block:: console

    Validator error[4]:
        Description: CellML identifiers must contain one or more
        basic Latin alphabetic characters.
        See section 3.1.3 in the CellML specification.
    Validator error[5]:
        Description: Variable 'd' does not have a valid units attribute.
        See section 11.1.1.2 in the CellML specification.

**TODO** update error messages

These two errors go together too.
Because we haven't defined a :code:`units` attribute for variable :code:`d`, it effectively has a blank name, which is not
allowed.
Simply assigning units to the variable will fix both errors.

.. container:: dothis

    **3.d** You already know how to add units to a variable (as in step 3.a) so go ahead and fix this error any way you see fit.

-----

.. code-block:: console

    Description: MathML ci element has the child text 'a' which does not
        correspond with any variable names present in component
        'i_am_a_component' and is not a variable defined within a bvar element.


The maths block is complaining that it is being asked to compute :math:`a = b + c` but in the component there is no variable called :code:`"a"`.
Since we corrected - or tried to - this earlier by naming the first variable in component[0] :code:`"A"`, you need to go back and change it to lower-case instead.

.. container:: dothis

    **3.e** Fix up this last error, and check for yourself that your corrected model is now error-free.

Step 4: Have a look at the corrected model
==========================================
Let's have a look at our corrected model by calling that same utility function which we used earlier to print it to the screen.
You should see something like this:

.. code-block:: console

        The model name is: 'tutorial_2_model'
        The model id is: 'tutorial 2 id has spaces'
        The model defines 0 custom units:
        The model has 1 components:
            Component[0] has name: 'i_am_a_component'
            Component[0] has id: 'my_component_id'
            Component[0] has 4 variables:
                Variable[0] has name: 'a'
                Variable[0] has units: 'dimensionless'
                Variable[1] has name: 'b'
                Variable[1] has units: 'dimensionless'
                Variable[2] has name: 'c'
                Variable[2] has initial_value: '20'
                Variable[2] has units: 'dimensionless'
                Variable[3] has name: 'd'
                Variable[3] has units: 'dimensionless'

Step 5: Serialise and output the model to a file
================================================

.. container:: dothis

    **5.a** Just as you did in :ref:`Tutorial 1<tutorial1_cpp>`, create a :code:`Printer` and use it to serialise your model to a string.

.. container:: dothis

    **5.b** Finally, write your model string to a :code:`*.cellml` file.

.. container:: dothis

    **5.c** Go and have a cuppa, you're done!
