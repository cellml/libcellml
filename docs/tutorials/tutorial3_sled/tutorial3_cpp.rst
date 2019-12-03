.. _tutorial3_cpp:

==============================================
Tutorial 3 C++: Creating a model using the API
==============================================

The outline for this tutorial is shown on the :ref:`Tutorial 3<tutorial3>`
page. These are the C++ instructions.  For the same tutorial in Python
please see the :ref:`Tutorial 3 in Python<tutorial2_py>` page instead.

Requirements:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial
    - :download:`tutorial3.cpp` Either the skeleton code, or ..
    - :download:`tutorial3_complete.cpp` the completed tutorial code

--------
0: Setup
--------

Navigate into the :code:`tutorial3` folder and check that you can build the
template against the libCellML library successfully::

    make

Running the template::

    ./tutorial3

... should give the output:


.. container:: terminal

    | -----------------------------------------------
    |    TUTORIAL 3: CREATE A MODEL USING THE API
    | -----------------------------------------------
    |

---------------------------------
1: Set up the governing equations
---------------------------------

TODO Need something here about when to use shared pointers and when to use
concrete instances?

Just as you did in :ref:`Tutorial 2<tutorial2_cpp>`, we need to start by setting
up a :code:`Model` instance, and creating a component inside it.

.. container:: dothis

    **1.a**
    Create a new :code:`Model` using the
    ``libcellml::SomethingPtr something = libcellml::Something::create();``
    idiom.
    Set the name and id attributes of the model you created, and print them to
    the terminal to check them.

.. container:: dothis

    **1.b**
    Create a new :code:`Component` as above.  Name it and add it
    to the model you created in 1.a.

Now for the real bit.  In order to actually model anything, we need to include
the mathematical equations which represent the phyiscal situation of interest.
As you saw in :ref:`Tutorial 2<tutorial2_cpp>`, the maths and the
:code:`Variable` items which it references live inside a parent
:code:`Component` item.  At this point it should be noted that the *order* in
which you add your components, or models, or variables (or anything) is not
important to the final product, but it *can* affect how quickly you're able to
find and fix bugs along the way.  In these tutorials, we have suggested that
you add the mathematics first and use a :code:`Validator` to notify you of the
outstanding items, but you can really do this in any order you choose.

The system of equations which describe the populations are given by:

.. math::

    \frac{dy_s}{dt} =f(sharks, fishes, time) = a y_s + b y_s y_f

    \frac{dy_f}{dt} =f(sharks, fishes, time) = c y_f + d y_s y_f

where :math:`y_s` and :math:`y_f` are the number of sharks and fish
respectively, and the constants :math:`(a, b, c, d)=(1.2, -0.6, -0.8, 0.3)`
govern their behaviour.
In order to use this in our model we need to write it as a
MathML2 string.  The basic structure for these is described in the
:mathml2:`W3 resource pages regarding MathML2 <>`.

.. container:: nb

    **Note** that libCellML will **only** accept MathML2 markup, even though
    later versions (3 and 4) are now available.

Looking at the right hand side first, the MathML2 representation of
:math:`ax+b` is

.. code-block:: xml

                <apply><plus/>
                    <apply><times/>
                        <ci>a</ci>
                        <ci>x</ci>
                    </apply>
                    <ci>b</ci>
                </apply>

Three things can be seen here:

- the :code:`<apply>` opening and :code:`</apply>` closing tags which surround
  the *operations*,
- the *operations* tags like :code:`<times/>` and :code:`<plus/>` which stand
  alone rather than in an open/close pair,
- the :code:`<ci>` opening and :code:`</ci>` closing tags which surround the
  variable names.

The left-hand side, :math:`\frac{dx}{dt}` becomes:

.. code-block:: xml

                <apply><diff/>
                    <bvar>
                        <ci>t</ci>
                    </bvar>
                    <ci>x</ci>
                </apply>

Two further items to note:

- the base variable for the integration identified by the
  :code:`<bvar> ... </bvar>` tags,
- the :code:`<diff/>` operation signifying differentiation with respect to the
  base variable.

When both sides are defined we need to equate them by :code:`<apply>` -ing the
:code:`<eq/>` equals operator, and create a string so that we end up with:

.. code-block:: cpp

    std::string equation = "<apply><eq/>\
                                <apply><diff/>\
                                    <bvar>\
                                        <ci>t</ci>\
                                    </bvar>\
                                    <ci>x</ci>\
                                </apply>\
                                <apply><plus/>\
                                    <apply><times/>\
                                        <ci>a</ci>\
                                        <ci>x</ci>\
                                    </apply>\
                                    <ci>b</ci>\
                                </apply>\
                            </apply>";

.. container:: dothis

    **1.c**
    Copy the string above into your code.  We will complete the inclusion of the
    maths in the next step.

Next you need to define the namespace in which the maths will be applied
by enclosing it in the :code:`<math> ... </math>` tags with the two namespaces:

- the XML namespace :code:`xmlns` at http://www.w3.org/1998/Math/MathML
- the CellML2 namespace :code:`xmlns:cellml` at http://www.cellml.org/cellml/2.0#

It's simple to do this once in your code using a string to represent the
opening attributes and namespaces; this string can be reused easily
throughout your code as needed later:

.. code-block:: cpp

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"\
                                    xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

.. container:: dothis

    **1.d**
    Copy the opening and closing math strings above into your code.

Our last step in defining the mathematics is to link it into the component. The
functions available to manipulate maths are:

- a :code:`setMath` function, which overwrites any existing MathML strings
  stored in the :code:`Component` item.
- an :code:`appendMath` function, which performs a straightforward string
  concatenation with the current contents of the maths string in the
  :code:`Component`.
- a :code:`clearMath` function to remove all maths contents.

.. container:: dothis

    **1.e**
    Use the functions above to include the :code:`mathHeader`,
    :code:`equation`, and :code:`mathFooter` strings into your component.
    Note that the order in which these are added is important, as they are
    stored as a single string.

.. container:: dothis

    **1.f**
    Create a :code:`Validator` instance and use it to check for errors in the
    model at this point.  Use the utility function
    :code:`printErrorsToTerminal` to output the messages to the
    terminal.

You should see an output similar to that shown below:

.. container:: terminal

    | The validator has found 5 errors!
    | Validator error[0]:
    |    Description: MathML ci element has the child text 't' which does not correspond with any variable names present in component 'distance_finder'.
    | Validator error[1]:
    |    Description: MathML ci element has the child text 'x' which does not correspond with any variable names present in component 'distance_finder'.
    | Validator error[2]:
    |    Description: MathML ci element has the child text 'a' which does not correspond with any variable names present in component 'distance_finder'.
    | Validator error[3]:
    |    Description: MathML ci element has the child text 'x' which does not correspond with any variable names present in component 'distance_finder'.
    | Validator error[4]:
    |    Description: MathML ci element has the child text 'b' which does not correspond with any variable names present in component 'distance_finder'.


Running the validator will alert you variables in the MathML that don't (yet)
exist in your component.  This was explained in :ref:`Tutorial 2<tutorial2_cpp>`.

.. container:: dothis

    **1.g** Create :code:`VariablePtr` instances for each of the missing
    variables discovered above.  Remember that:

    - you will need to give each a name using the :code:`setName` function,
      where the name must match that inside your MathML string.
    - you will need to add each variable to the component using the
      :code:`addVariable` function.

At this stage you'll realise that you haven't yet added the :code:`Units` for
any of the variables.  Roll on Step 2 ...

--------------------------------
2: Built-in and customised units
--------------------------------
Linking variables to the *name* of their units is straightforward, but in
order to be able to use them we need to also define what the name actually
*means* by creating the units themselves.  Some basic units have been defined
and built into libCellML, others you can define by combining the built-in
ones using scaling factors and exponents, or you can define your own from
scratch if need be.

There are four different kinds of units used here.  The first are called
*irreducible* because they represent the physical base quantities which cannot
be further simplified:

- length (:code:`metre`)
- time (:code:`second`)
- amount of a substance (:code:`mole`)
- temperature (:code:`kelvin`)
- mass (:code:`kilogram`)
- current (:code:`ampere`)
- luminous intensity (:code:`candela`)
- non-dimensional (:code:`dimensionless`)

These *irreducible* units can be used to create all other physically-based
units by combining them using different exponents, multipliers, and prefixes.
Some of these combinations form our second type of units, the *built-in units*,
these being common relationships which have been constructed from combinations
of the irreducible units.  The combinations can involve:

- a scaling factor (the units :code:`millisecond` is equivalent to
  :code:`second` and a factor of 0.001)
- a combination of units (a :code:`coulomb` is a :code:`second` multiplied by
  an :code:`ampere`)
- powers of units (a :code:`Hertz` has a base of :code:`second` with an
  exponent of -1)
- any combination of the above.

A list of pre-existing *built-in* convenience units is shown in the
:ref:`Built-in Units page<builtinunits>`, along with
their relationships to the irreducible units.

The third type of units are those *combinations* which users can define for
themselves based on the built-in units, the irreducible units, any other units
already created, or (see below) their own custom irreducible units.

For example, let's say that you want to simulate the time variable,
:math:`t`, in units of milliseconds.  This isn't one of the built-in units, so
you'll need to define it, but it's easy to see that it's based on the built-in
:code:`second`, but needs a scaling factor.

For convenience libCellML gives a variety of options for defining such scaling
factors:

- | either through the use of named prefixes which are listed on the
   :ref:`Prefix page<prefixes>`:
  |    eg: :code:`millisecond` is :code:`second` with :code:`prefix="milli"`
- | by defining an integer or integer string as a prefix which represents the
    :math:`log_{10}` of the scaling factor:
  |    eg: :code:`millisecond` is :code:`second` with :code:`prefix=-3`
   gives a scaling factor of :math:`10^{-3}=0.001`
  |    NB: using an integer string like :code:`prefix="-3"` gives the same
   result
- | by defining the scaling factor directly, as a multiplier:
  |    eg: :code:`millisecond` is :code:`second` with :code:`multiplier=0.001`

The overloaded argument option list is shown below:

.. code-block:: cpp

    void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    void addUnit(const std::string &reference, Prefix prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    void addUnit(const std::string &reference, int prefix, double exponent,
                 double multiplier = 1.0, const std::string &id = "");

    void addUnit(const std::string &reference, double exponent, const std::string &id = "");

    void addUnit(const std::string &reference);

The creation of the :code:`millisecond` unit you need will
follow the same basic steps as other entities: declare it, name it, define
it, and then add it in.  For example:

.. code-block:: cpp

    // Declaring, naming, and defining the "millisecond" unit pointer
    libcellml::UnitsPtr ms = libcellml::Units::create();
    ms->setName("millisecond");

    // The manner of specification here is agnostic: all three definitions are identical.
    ms->addUnit("second", "milli");  // reference unit and built-in prefix
    // OR
    ms->addUnit("second", 1.0, -3);  // reference unit, multiplier, exponent
    // OR
    ms->addUnit("second", 1.0, 0, 0.001);  // reference unit, multiplier, exponent


.. container:: dothis

    **2.a** Use the example above to create, name and define two units:
    milliseconds and leagues (a league is 5556 metres).

.. container:: nb

    **Note:**

    - When you add different sub-unit parts into a :code:`Units` item, the function
      is :code:`addUnit` (singular), and it takes as argument the *name* of the
      sub-unit as a string (eg: :code:`"second"` used above)
    - When you add the final created combination into the :code:`Model` item,
      the function is :code:`addUnits` (plural), and it takes as argument the
      *reference* of the combined units (eg: :code:`ms` used below)

.. container:: dothis

    **2.b** Add the units which you've just created into your model, as
    in the example below.

.. code-block:: cpp

    // Add the millisecond unit to the model
    model->addUnits(ms);

Units can be defined based on one another as well.  For example, after defining
our :code:`millisecond` units, we could then use this definition to define the
:code:`per_millisecond` units by simply including it with an exponent of -1:

.. code-block:: cpp

    // Defining a per_millisecond unit based on millisecond^-1
    per_ms->addUnit(ms, -1.0);

This will be useful later in :ref:`Tutorial 5<tutorial5_cpp>`.

For completeness, the final type of unit is a custom irreducible unit.
While this is not common (all of the seven physical attriubutes are already
included), for those rare occasions where you might need to model something
not physically based, you're able to define your own.  Here's an example.

.. code-block:: cpp

    // Create a custom irreducible unit named "banana"
    libcellml::UnitsPtr uBanana = libcellml::Units::create();
    uBanana->setName("banana");

    // Note that when a UnitsPtr is defined with a name only, it is effectively
    // irreducible.

    // Create a new compound unit based on the "banana" unit above
    libcellml::UnitsPtr uBunchOfBananas = libcellml::Units::create();
    u2->setName("bunch_of_bananas");
    u2->addUnit("banana", 5.0);  // include bananas^5 in the bunch_of_bananas unit

.. container:: dothis

    **2.c** Now that you've created the units for each of your variables,
    call the validator to check your model for errors.  You should see an
    output similar to that shown below.

.. container:: terminal

    | The validator has found 2 errors!
    |   Validator error[0]:
    | Description: MathML ci element has the child text 'a' which does not correspond with any variable names present in component 'distance_finder'.
    |   Validator error[1]:
    | Description: MathML ci element has the child text 'b' which does not correspond with any variable names present in component 'distance_finder'.

These are referring to the two constants :math:`a` and :math:`b` that were
included in the MathML block which have not yet been defined.  At this point
there are two options:

- include the constants as real numbers within the MathML string directly, or
- create them as variables as above, defining their names, units and values.

We'll do one of each to demonstrate the process.

Because the dimensionality of the equation needs to be valid, all constants
must be associated with units.  These are defined within the tags, and must
also refer to the :code:`cellml` namespace::

    <cn cellml:units="bunch_of_bananas">1</cn>

... which gives us one bunch of bananas, without needing to create a
corresponding :code:`Variable` item.  Of course, you may need to create the
corresponding :code:`Units` item and add it to the model, if not already
present.

.. container:: dothis

    **2.d**  Create a copy of the MathML statement from step 1.c and change
    the value of :math:`b` to be a value of 2.0. You will
    need to deduce the appropriate units and include them in the MathML too.
    Recall that using the :code:`setMath()` function will overwrite the
    existing maths, and repeat the process you did in step 1.e to
    include the new MathML instead.  Remember that you will need to reinclude
    the opening and closing :code:`<math>` tags too.  Call the validator to
    check that the error related to :math:`b` has gone.

.. container:: dothis

    **2.e**  At this stage you should have just one validation error remaining.
    Since you already know how to create and add variables, go ahead and make
    one which represents :math:`a` in the governing equation.  Use the
    :code:`setInitialValue` function to set its value to :math:`1.0`.  Note
    that even though you're not going to change its value during the solution
    process, this is the only way in which the value of any variable can be set
    directly.  Check that the model is now free of validation errors.

----------------------------------------------------
3: Use code generation to change the output langauge
----------------------------------------------------
Some exciting new functionality of libCellML is its ability to generate a
runable file from a model description.  This means that if you already have
a solver in either C or Python, you can simply translate your model from here
into that language.  Let's give it a go.

The generator is instantiated in the same way as the other items:

.. code-block:: cpp

    // Instantiate the generator and submit the model to it for processing
    libcellml::GeneratorPtr generator=libcellml::Generator::create();
    generator->processModel(model);

.. container:: dothis

    **3.a**  Create a :code:`Generator` instance and follow the example above
    to process your model.  Call the utility function
    :code:`printErrorsToTerminal` for your generator to check it.  You should
    see an output similar to that shown below.

.. container:: terminal

    | The generator has found 1 errors!
    |   Generator error[0]:
    | Description: Variable 'x' in component 'distance_finder' of model
      'tutorial_3_model' is used in an ODE, but it is not initialised.

The error message above refers to the fact that though we've set the value of
the constant :math:`a`, we haven't constrained the model with sufficient
initial conditions.

.. container:: dothis

    **3.b** Set the initial value such that :math:`x(t=0)=5` and re-process
    the model. You should see no errors now.

The :code:`Generator` has to re-interpret all of the maths, including the
variables, their interaction with each other in different equations, values,
initial conditions and units before it can output your model in your choice
of language.  For the maths to make sense, the definitions in your model's
variables, maths blocks and units need to be solvable too.  There are several
requirements that need to be satisfied in order for the code generation
functionality to be able to work.  These are:

- the mathematical model definition must be appropriately constrained (not
  over- or under-constrained)
- initial conditions must be specified for variables which are integrated
- initial conditions must not be specified for variables which are the base of
  integration
- **TODO get full list of stuff here ...**

Parameters can be investigated using the same format of functions as
elsewhere:

- The :code:`voi()` function returns a *pointer* to the :code:`Variable` which
  is to be used as the variable of integration (VOI).  This is specified inside
  the MathML block using the :code:`<bvar>...</bvar>` tags.
  To return its *name* you can use :code:`generator->voi()->name()`.

- The :code:`variableCount()` function returns the number of variables which
  need to be solved for in the model.  As with elsewhere, you can access the
  variable at index :code:`i` using the :code:`variable(i)` function.  Note
  that this does *not* include:

  - :code:`Variable` items which are actually constants (as in the :math:`a`
    variable in your model)
  - :code:`Variable` items which are used as the base for integration.

- The :code:`stateCount()` function returns number of states in the model.
  In this context states are ... **??? TODO ??**


When the generator processes your model it will determine the model's type,
this being one of the following:

        - :code:`UNKNOWN` where ...
        - :code:`ALGEBRAIC` No integration is needed
        - :code:`ODE` One or more ordinary differential equations to solve
        - :code:`INVALID` Computer says no **TODO**
        - :code:`UNDERCONSTRAINED` Computer still says no
        - :code:`OVERCONSTRAINED` Computer says no AGAIN
        - :code:`UNSUITABLY_CONSTRAINED` OMG computer, what do you want from me

The :code:`modelType()` function returns the classification as an :code:`enum`,
so you'll need to interpret it by comparing to the enum list above.  In the
tutorials you're given a utility function that will return the name of the enum
for you, eg: :code:`getModelTypeFromEnum(generator->modelType())`.

The Generator functionality refers to its different language options
as *profiles*.  The default setting is for C, but you can change this using the
:code:`setProfile` function if you need to:

.. code-block:: cpp

    // Change the generated language from the default C to Python
    libcellml::GeneratorProfilePtr profile =
        libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);

**TODO** Check whether this is changed to create() for the GeneratorProfile

Of course, your choice of generator profile (language) will affect
*what* you need to export:

- If you're using C, then you will need both the header file as well as the
  source code.
- If you're using Python, you will only need the source code.

For code generation into C:

.. code-block:: cpp

    // Retrieve the interface or header code, and write to a file:
    std::string headerCode = generator->interfaceCode();

    // Retrieve the main source code and write to a file:
    std::string sourceCode = generator->implementationCode();

For code generation into Python:

.. code-block:: cpp

    // Retrieve the main script code only:
    std::string sourceCode = generator->implementationCode();

.. container:: dothis

    **3.d** Use the examples above to create your own interface code
    (that is, the \*.h file contents) and source code
    (that is, the \*.c file contents) from your model, and save them into
    appropriately named files.

**TODO** **Need to write run code here**

.. container:: dothis

    **3.e**
    Go and have a cuppa, you're done!
