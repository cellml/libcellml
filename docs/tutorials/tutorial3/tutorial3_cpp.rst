.. _tutorial3_cpp:

==============================================
Tutorial 3 C++: Creating a model using the API
==============================================

The outline for this tutorial is shown on the :ref:`Tutorial 3<tutorial3>` page.
These are the C++ instructions.
For the same tutorial in Python please see the :ref:`Tutorial 3 in Python<tutorial2_py>` page instead.

**Requirements**

- :download:`CMakeLists.txt` The CMake file for building this tutorial
- :download:`tutorial3.cpp` Either the skeleton code, or ..
- :download:`tutorial3_complete.cpp` the completed tutorial code

.. contents:: Contents
    :local:

Step 0: Setup
=============
Navigate into the :code:`tutorial3` folder and check that you can build the template against the libCellML library successfully:

.. code-block:: console

    cmake -DINSTALL_PREFIX=../../install .
    make -j

Running the template:

.. code-block:: console

    ./tutorial3

... should give the output:

.. code-block:: console

    ---------------------------------------------------------------
        TUTORIAL 3: MODEL CREATION AND CODE GENERATION WITH THE API
    ---------------------------------------------------------------

Step 1: Set up the governing equations
======================================
Just as you did in :ref:`Tutorial 2<tutorial2_cpp>`, we need to start by setting up a :code:`Model` instance, and creating a :code:`Component` inside it.

.. container:: dothis

    **1.a** Create a new :code:`Model` using the :code:`auto something = libcellml::Something::create("myThingName");` idiom to create and name your model.

.. container:: dothis

    **1.b** Create a new :code:`Component` as above with a name, and add it to the model you created in 1.a.
    This will be the integrator of the equations.

Now for the real bit.
In order to actually model anything, we need to include the mathematical equations which represent the phyiscal situation of interest.
As you saw in :ref:`Tutorial 2<tutorial2_cpp>`, the maths and the :code:`Variable` items which it references live inside a parent :code:`Component` item.
At this point it should be noted that the *order* in which you add your components, or models, or variables (or anything) is not important to the final product, but it *can* affect how quickly you're able to find and fix bugs along the way.
In these tutorials, we have suggested that you add the mathematics first and use a :code:`Validator` to notify you of the
outstanding items, but you can really do this in any order you choose.

The system of equations which describe the populations are given by:

.. math::

    c = a + 2.0

    \frac{dy_s}{dt} =f(sharks, fish, time) = a y_s + b y_s y_f

    \frac{dy_f}{dt} =f(sharks, fish, time) = c y_f + d y_s y_f


where :math:`y_s` and :math:`y_f` are the number of sharks and thousands of fish respectively, and the constants :math:`(a, b, d)=(-0.8, 0.3, -0.6)` govern their behaviour.
It's clear that the value of constant :math:`c` is easily calculable from the first equation, but we will leave it in this form
to better illustrate the operation of the :code:`Generator` later on.

In order to use this in our model we need to write it as a MathML2 string.
The basic structure for these is described in the :mathml2help:`W3 resource pages regarding MathML2 <>`.

.. container:: NB

    **Note** that libCellML will **only** accept MathML2 markup, even though later versions (3 and 4) are now available.

Looking at the top equation first, the MathML2 representation of :math:`c = a - 2.0` is:

.. code-block:: xml

    <apply><eq/>
       <ci>c</ci>
       <apply><plus/>
           <ci>a</ci>
           <cn>2.0</cn>
       </apply>
    </apply>

Four things can be seen here:

- The :code:`<apply>` opening and :code:`</apply>` closing tags which surround the *operations*;
- The *operations* tags like :code:`<eq/>` and :code:`<plus/>` (or :code:`<minus/>`, :code:`<times/>`, :code:`<divide/>`) which stand alone rather than in an open/close pair;
- The :code:`<ci>` opening and :code:`</ci>` closing tags which surround the variable names; and
- The :code:`<cn>` opening and :code:`</cn>` closing tags which surround the constant :math:`2.0` value.

.. container:: dothis

  **1.c** Create a string containing the MathML which represents equation 1 above.

Differential terms, such as those on the left-hand side of equations 2 and 3 :math:`\frac{dx}{dt}` in MathML become:

.. code-block:: xml

                <apply><diff/>
                    <bvar>
                        <ci>t</ci>
                    </bvar>
                    <ci>x</ci>
                </apply>

Two further items to note:

- The base variable for the integration is identified by the :code:`<bvar> ... </bvar>` tags.
  These variables are refered to as *variables of integration* or *base variables*.
- The :code:`<diff/>` operation signifies differentiation with respect to the base variable.

The right-hand side becomes a collection of nested operations, all bracketed by :code:`<apply>...</apply>` tags for each operation:

.. code-block:: xml

    <apply><plus/>
      <apply><times/>
        <ci>a</ci>
        <ci>y_s</ci>
      </apply>
      <apply><times/>
        <ci>b</ci>
        <ci>y_s</ci>
        <ci>y_f</ci>
      </apply>
    </apply>

When both sides are defined we need to equate them by :code:`<apply>` -ing the :code:`<eq/>` equals operator, and create a string so that we end up with:

.. code-block:: cpp

    std::string equation2 =
        "<apply><eq/>"
        "   <apply><diff/>"
        "     <bvar><ci>time</ci></bvar>"
        "     <ci>y_s</ci>"
        "   </apply>"
        "   <apply><plus/>"
        "       <apply><times/>"
        "           <ci>a</ci>"
        "           <ci>y_s</ci>"
        "      </apply>"
        "      <apply><times/>"
        "          <ci>b</ci>"
        "          <ci>y_s</ci>"
        "          <ci>y_f</ci>"
        "      </apply>"
        "   </apply>"
        "</apply>";

.. container:: dothis

    **1.d** Copy the string above representing equation 2 into your code.

.. container:: dothis

    **1.e** Create a third string representing equation 3.


Next you need to define the namespace in which the maths will be applied by enclosing it in the :code:`<math> ... </math>` tags with the two namespaces:

- the MathML2 namespace :code:`xmlns` at http://www.w3.org/1998/Math/MathML
- the CellML2 namespace :code:`xmlns:cellml` at http://www.cellml.org/cellml/2.0#

It's simple to do this once in your code using a string to represent the opening attributes and namespaces; this string can be reused easily throughout your code as needed later:

.. code-block:: cpp

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"\
                                    xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

.. container:: dothis

    **1.f** Copy the opening and closing math strings above into your code.

Our last step in defining the mathematics is to link it into the component.
The functions available to manipulate maths are:

- A :code:`setMath(yourMathsHere)` function, which overwrites any existing MathML strings
  stored in the :code:`Component` item;
- An :code:`appendMath(yourMathsHere)` function, which performs a straightforward string
  concatenation with the current contents of the maths string in the
  :code:`Component`; and
- A :code:`clearMath()` function to remove all maths contents.

.. container:: dothis

    **1.g**
    Use the functions above to include the :code:`mathHeader`, :code:`equation`, and :code:`mathFooter` strings into your component.

.. container:: NB

    Note that the order in which strings are added might be important, as they are stored as a single concatenated string.
    However, the order in which complete MathML equations occur in the overall MathML string is not important.

.. container:: dothis

    **1.h** Create a :code:`Validator` and use it to check for errors in the model at this point.
    Use the utility function :code:`printErrorsToTerminal` to output the messages to the terminal.

You should see an output similar to that shown below:

.. code-block:: console

     The validator has found 18 errors!
       Validator error[0]:
         Description: MathML ci element has the child text 'c' which does not correspond with any variable
         names present in component 'predator_prey_component'.
       ...
       Validator error[3]:
         Description: Math cn element with the value '2.0' does not have a valid cellml:units attribute.
       ...

Running the validator will alert you variables in the MathML that don't (yet) exist in your component.
This was explained in :ref:`Tutorial 2<tutorial2_cpp>`.

Step 2: Create the variables
============================

.. container:: dothis

    **2.a** Create :code:`Variable` items for each of the missing variables discovered above.
    Remember that:

    - Each must have a name, either using the naming constructor :code:`Variable::create("myNewVariable")` or by manually calling the :code:`setName` function; and
    - Each name must match that inside your MathML string.

.. container:: dothis

    **2.b** Add each of your new variables to the component using the :code:`addVariable(myNewVariable)` function.

.. container:: dothis

    **2.c** Call the validator again to check for errors.
    At this stage you can expect errors like those below relating to missing units for the variables.
    Note that both these errors refer to the same thing: when the unit is missing the variable sees its name field as being blank, hence the first error.

.. code-block:: console

     Validator error[0]:
       Description: CellML identifiers must contain one or more basic Latin :term:`alphabetic<Basic Latin alphabetic character>` characters.
         See section 3.1.3 in the CellML specification.
     Validator error[1]:
       Description: Variable 'a' does not have a valid units attribute.
         See section 11.1.1.2 in the CellML specification.

Step 3: Built-in and customised units
=====================================
Linking variables to the *name* of their units is straightforward, but in order to be able to use them we need to also define what the name actually *means* by creating the units themselves.
Some basic units have been defined and built into libCellML, others you can define by combining the built-in ones using scaling factors and exponents, or you can define your own from scratch if need be.

.. container:: toggle

    .. container:: header

        Read more about units

    .. container:: infospec

        .. include:: ../asides/aside_units.rst

To create a :code:`Units` item you need will follow the same basic steps as other entities: declare it, name it, define it, and then add it in.
For example:

.. code-block:: cpp

    // Declare, name, and define a "millisecond" unit pointer.
    auto ms = libcellml::Units::create("millisecond");

    // The manner of specification here is agnostic: all three definitions are identical.
    ms->addUnit("second", "milli");  // reference unit and built-in prefix
    // OR
    ms->addUnit("second", 1.0, -3);  // reference unit, multiplier, exponent
    // OR
    ms->addUnit("second", 1.0, 0, 0.001);  // reference unit, multiplier, exponent

.. container:: dothis

    **3.a** Use the example above to create, name and define the units of "month" which will represent your time variable.  This should be defined as a multiple of the built-in unit :code:`second`.

Units can be defined based on one another as well.
For example, after defining our :code:`millisecond` units, we could then use this definition to define the :code:`per_millisecond` units by simply including it with an exponent of -1:

.. code-block:: cpp

    // Define a per_millisecond unit based on millisecond^-1:
    per_ms->addUnit(ms, -1.0);

.. container:: dothis

    **3.b** Create a :code:`Units` item called "per_month" based on the one you just created, as shown above.

.. container:: dothis

    **3.c** Create the irreducible units needed by the shark and fish populations.
    Call these "number_of_sharks" and "thousands_of_fish" respectively.

Finally we need to create the units for the constants :code:`b` and :code:`d`.
These will be combinations of those which we've already created, as defined by the need for dimensional consistency in our governing equations.

.. container:: dothis

    **3.d** Create two units representing "per shark month" (for the :code:`b` variable) and "per fish month" (for the :code:`d` variable).

The final two steps are to associate each variable with its appropriate units, and to include the units in the model.

.. container:: NB

    - When you add different sub-unit parts into a :code:`Units` item, the function is :code:`addUnit` (singular), and it takes as argument the *name* of the sub-unit as a string (eg: :code:`"second"` used above).
    - When you add the final created combination into the :code:`Model` item, the function is :code:`addUnits` (plural), and it takes as argument the *reference* of the combined units (eg: :code:`ms`).

.. container:: dothis

    **3.e** Add the units to their variables using :code:`myVariable->setUnits(myUnits)`.
    Add the units to the model using :code:`myModel->addUnits(myUnits)`.

.. container:: NB

    **Gotcha!** When you specify the :code:`Units` for a :code:`Variable` using its name then you may need to call the :code:`Model::linkUnits()` function before validating the model.
    If you see errors related to missing units which do in fact exist, then a call to the :code:`Model::linkUnits()` function is needed.

.. container:: dothis

    **3.f** Call the validator to check your model for errors.
    You should see an output similar to that shown below.

.. code-block:: console

     The validator has found 2 errors!
       Validator error[0]:
         Description: CellML identifiers must contain one or more basic Latin characters.
         See section 3.1.3 in the CellML specification.
       Validator error[1]:
         Description: Math cn element with the value '2.0' does not have a valid cellml:units attribute.

These messages are really referring to just one issue.
In the first MathML equation we used a real number :code:`<cn>2.0</cn>` without specifying any units for it.

Because the dimensionality of the equation needs to be valid, all real numbers must be associated with units, just the same way that variables are.
These are defined within the tags of the MathML, and must also refer to the :code:`cellml` namespace.  For example:

.. code-block:: xml

    <cn cellml:units="bunch_of_bananas">1</cn>

... which gives us one bunch of bananas, without needing to create a corresponding :code:`Variable` item.
Of course, you may need to create the corresponding :code:`Units` item and add it to the model, if it is not already present.

.. container:: dothis

    **3.g**  Create a copy of the MathML statement from step 1.c and add the namespace and units definition as in the example above into the string.
    Recall that using the :code:`setMath()` function will overwrite the existing maths, and repeat the process you did in step 1.e to include the new MathML instead.
    Remember that you will need to reinclude the opening and closing :code:`<math>` tags and other equations too.

.. container:: dothis

    **3.h** Check that the model is now free of validation errors.

Step 4: Use code generation to change the output langauge
=========================================================
Some exciting new functionality of libCellML is its ability to generate a runable file from a model description.
This means that if you already have a solver in either C or Python, you can simply translate your model from here into that language.
Let's give it a go.

The generator is instantiated in the same way as the other items:

.. code-block:: cpp

    // Instantiate the generator and submit the model to it for processing.
    auto generator=libcellml::Generator::create();
    generator->processModel(model);

The :code:`Generator` has to re-interpret all of the maths, including the variables, their interaction with each other in different equations, values, initial conditions and units before it can output your model in your choice of language.
For the maths to make sense, the definitions in your model's variables, maths blocks and units need to be solvable too.
There are several requirements that need to be satisfied in order for the code generation functionality to be able to work, *beyond* the CellML syntax requirements.
These are:

- The mathematical model definition must be appropriately constrained (not over- or under-constrained);
- Initial conditions must be specified for variables which are integrated; **TODO** need to elaborate ...
- Initial conditions must not be specified for variables which are the base of integration;
- The values of constants must be specified or calculable; and
- **TODO get full list of stuff here ...**

.. container:: dothis

    **4.a** Create a :code:`Generator` instance and follow the example above to process your model.

.. container:: dothis

    **4.b** Call the utility function :code:`printErrorsToTerminal` for your generator to check it.
    You should see an output similar to that shown below.

.. code-block:: console

     The generator has found 6 errors!
      Generator error[0]:
        Description: Variable 'a' in component 'predator_prey_component' of model 'tutorial_3_model'
        is not computed.
      Generator error[1]:
         Description: Variable 'b' in component 'predator_prey_component' of model 'tutorial_3_model'
         is not computed.
      Generator error[2]:
         Description: Variable 'c' in component 'predator_prey_component' of model 'tutorial_3_model'
         is not computed.
      Generator error[3]:
         Description: Variable 'd' in component 'predator_prey_component' of model 'tutorial_3_model'
         is not computed.
      Generator error[4]:
         Description: Variable 'y_f' in component 'predator_prey_component' of model 'tutorial_3_model'
         is used in an ODE, but it is not initialised.
      Generator error[5]:
         Description: Variable 'y_s' in component 'predator_prey_component' of model 'tutorial_3_model'
         is used in an ODE, but it is not initialised.

The error messages above refer to the fact that though our model has passed validation tests, it's not yet sufficiently constrained to allow it to be solved, which is what the :code:`Generator` checks for.
We need to set initial conditions for the variables we're solving for, the populations of sharks and fish, using the :code:`setInitialValue` function.
The values of the constants :code:`a, b, c, d` are just that - constant - and their values are set using the same :code:`setInitialValue` function.

.. container:: dothis

    **4.c** Set the values of the constants :math:`(a, b, d)=(-0.8, 0.3, -0.6)` and the initial conditions such that :math:`y_f(t=0)=2.0` and :math:`y_s(t=0)=1.0`.
    Note that:

    - The constant :math:`c` will be calculated by our equation 1, so does not need to be specified; and
    - The base variable (or "variable of integration", or "voi") :math:`t` must *not* have an initial condition set.

.. container:: dothis

    **4.d** Reprocess the model and verify that the generator returns no errors.

Once the generator is happy we can use it to retrieve code generated according to the :code:`GeneratorProfile`, either C or Python.
Of course, your choice of generator profile (language) will affect *what* you need to export:

- If you're using the C profile, then you will need both the header file as well as the source code.
- If you're using Python, you will only need the source code.

By default the :code:`GeneratorProfile` is set to C so we can use it as-is to generate implementation code (source code) and interface code (header code) like this:

.. code-block:: cpp

    // Retrieve the interface or header code, and write to a file:
    std::ofstream outFile("tutorial3_PredatorPrey_generated.h");
    outFile << generator->interfaceCode();
    outFile.close();

    // Retrieve the main source code and write to a file:
    outFile.open("tutorial3_PredatorPrey_generated.c");
    outFile << generator->implementationCode();
    outFile.close();

.. container:: dothis

    **4.e** Use the examples above to create your own interface code (that is, the \*.h file contents) and source code (that is, the \*.c file contents) from your model, and save them into appropriately named files.

We can change the profile to Python using the following expression:

.. code-block:: cpp

    // Change the generated language from the default C to Python.
    auto profile =
        libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);

.. container:: dothis

    **4.f** Use the example above to change the generator profile to Python.

.. container:: dothis

    **4.g** In the same way as earlier, retrieve the implementation code and write it to a Python file.
    For the Python profile you will not need interface code.

Check that you have indeed created three new files.

.. container:: dothis

    **4.h**
    Go and have a cuppa, you're done (for now).
    The contents of these generated files and their usage is described in the next tutorial, :ref:`Tutorial 4<tutorial4_cpp>`.
