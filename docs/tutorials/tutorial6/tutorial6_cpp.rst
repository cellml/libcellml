.. _tutorial6_cpp:

================================================
Tutorial 6 C++: Working with multiple components
================================================

The outline for this tutorial is shown on the :ref:`Tutorial 6<tutorial6>`
page. These are the C++ instructions.  For the same tutorial in Python
please see the :ref:`Tutorial 6 in Python<tutorial6_py>` page instead.

You will need to download these files first:

    - :download:`CMakeLists.txt` The CMake file for building this tutorial;
    - :download:`tutorial6.cpp` Either the skeleton code or :download:`tutorial6_complete.cpp` the completed tutorial code;
    - :download:`../utilities/tutorial_utilities.h` and
      :download:`../utilities/tutorial_utilities.cpp` Utility functions for
      use in the tutorials; and
    - :download:`../resources/tutorial6_controller.cellml` A CellML file required for the controller and initialisation components.

.. contents:: Contents
    :local:

Setup
=====
Navigate into the :code:`tutorial6` folder and check that you can build the
template against the libCellML library successfully:

.. code-block:: console

    cmake -DINSTALL_PREFIX=../../install .
    make -j

Running the template:

.. code-block:: console

    ./tutorial6

... should give the output of the section headings which you'll complete here:

.. code-block:: console

    ----------------------------------------------------------
       STEP 1: Define the potassiumChannel component
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 2: Create the nGate component
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 3: Connect the components together
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 4: Read the controller
    ----------------------------------------------------------
    ----------------------------------------------------------
       STEP 5: Generate the model and output
    ----------------------------------------------------------

Step 1: Define the potassium channel component
==============================================
In :ref:`Tutorial 5<tutorial5_cpp>` we created a simple ion channel.
In this tutorial we're going to extend that a little by making its dynamics specific to potassium.
We also introduce voltage dependence into the alpha and beta gate rates, and move them into a separate component to make it cleaner.
This will be done in step 2.

.. container:: dothis

    **1.a** Create a model, name it appropriately.
    Create a new model to represent the potassium channel and add it to your model.

The operation of the potassium channel is similar to the generic ion channel in the previous tutorial, except that the gate rates will be calculated in another component.
The governing mathematical equation becomes:

.. math::

    i_K = n^4 g_K (V - E_K)

... where :math:`i_K` is blah blah.

.. container:: dothis

    **1.b** Add a MathML string representing this equation to your component.
    Remember that you will need to include the MathML opening and closing tags, and namespace.
    If you need to, copy the code underneath the "Show MathML" link below.

    .. container:: toggle

        .. container:: header

            Show MathML

        .. code-block:: cpp

            std::string equation =
                "  <apply><eq/>\n"
                "    <ci>i_K</ci>"
                "    <apply><times/>"
                "       <apply><power/>"
                "           <ci>n</ci>"
                "           <cn cellml:units=\"dimensionless\">4</cn>"
                "       </apply>"
                "       <ci>g_K</ci>"
                "       <apply><minus/>"
                "           <ci>V</ci>"
                "           <ci>E_K</ci>"
                "       </apply>"
                "    </apply>"
                "  </apply>";

.. container:: dothis

    **1.c** Create and call a Validator instance, and use it to check the model so far.
    At this stage we will expect errors related to missing variables.

.. code-block:: console

    The validator has found 5 errors!
    Validator error[0]:
        Description: MathML ci element has the child text 'i_K' which does not correspond with any variable names present in component 'potassiumChannel'.
    ...

.. container:: dothis

    **1.d** Create the variables, specify their units, and add them to the potassium channel component.
    You may notice that during the process of creating models using the API that you might need to create more than one :code:`VariablePtr` instance with the symbol :code:`V` or :code:`t` (for example).
    The CellML2 specification says that you need to have variable names which are unique within the scope of the *component* in which they're contained, not the entire model.
    In C++ you can mimic this using curly brackets, :code:`{...}`, around your :code:`VariablePtr` definitions: this will make your code easier to follow.

    .. code-block:: cpp

        // Using curly braces here means that you can use "auto V ... " in another
        // component too.
        {
            auto V = libcellml::Variable::create("V");
            V->setUnits("millivolt");
            potassiumChannel->addVariable(V);
            // ... etc ...
        }

.. container:: dothis

    **1.e** Use the validator to recheck the model again.
    You can now expect errors related to missing units.

.. code-block:: console

    The validator has found 5 errors!
    Validator error[0]:
        Description: Variable 'E_K' in component 'potassiumChannel' has a units reference
        'millivolt' which is neither standard nor defined in the parent model.
        See section 11.1.1.2 in the CellML specification.

.. container:: dothis

    **1.f** Create and add the missing units.
    This was covered in :code:`Tutorial 5<tutorial5_cpp>` in case you need a recap.
    Since at the time that the units were specified for the variables, the related :code:`Units` items didn't exist, we also have to link the units in the model properly.
    Use the :code:`libcellml::ModelPtr::linkUnits()` function to do this.

.. container:: dothis

    **1.g** Revalidate the model and check that it is now free of errors.

Step 2: Create the n-gate component
===================================
Here we create the voltage dependency behavior of the potassium component.
This is accomplished by creating a second component, and embedding it within the one we already have.

.. container:: dothis

    **2.a** Create a new component to represent the n-gate, and add it to the potassium channel component.
    Adding it to the component instead of the model creates an encapsulation hierarchy, which affects which components have access to each other.
    It also means that if the potassium channel component is moved or imported somewhere else, then the n-gate child component will be included too.

Now it's time to define the mathematical behaviour of the voltage dependence.
This is give by a differential equation for :math:`n`, the gate status, and by the expressions for voltage control



Next we need to define this new dependency of the :math:`\alpha` and
:math:`\beta` rate constants on the voltage.  The mathematics for this is:

.. math::

    \alpha_n = \frac {0.01(V+10)} {\exp(0.1(V+10))-1}

    \beta_n = 0.125 \exp(0.0125V)

    \frac {dn} {dt} = \alpha_n(1-n) - \beta_n n

.. container:: dothis

    **2.b** Create the appropriate MathML to represent the equations above, and
    add to the n-gate component.
    If needed, you can copy the equation strings from the "Show MathML" block below.
    Validate the model.
    At this stage you can expect errors related to missing variables, and missing errors defined in the constants.

    .. container:: toggle

        .. container:: header

            Show MathML

        .. code-block:: cpp

            std::string equation1 =
                "  <apply><eq/>\n"
                "    <apply><diff/>\n"
                "      <bvar><ci>t</ci></bvar>\n"
                "      <ci>n</ci>\n"
                "    </apply>\n" // end diff
                "    <apply><minus/>\n"
                "      <apply><times/>\n"
                "        <ci>alpha_n</ci>\n"
                "        <apply><minus/>\n"
                "          <cn cellml:units=\"dimensionless\">1</cn>\n"
                "          <ci>n</ci>\n"
                "        </apply>\n" // end minus
                "      </apply>\n" // end times
                "      <apply><times/>\n"
                "        <ci>beta_n</ci>\n"
                "        <ci>n</ci>\n"
                "      </apply>\n" // end times
                "    </apply>\n" // end minus
                "  </apply>\n"; // end eq

            std::string equation2 =
                "  <apply><eq/>\n"
                "    <ci>alpha_n</ci>\n"
                "    <apply><divide/>\n"
                "      <apply><times/>\n"
                "        <cn cellml:units=\"per_millivolt_millisecond\">0.01</cn>\n"
                "        <apply><plus/>\n"
                "          <ci>V</ci>\n"
                "          <cn cellml:units=\"millivolt\">10</cn>\n"
                "        </apply>\n" // end plus
                "      </apply>\n" // end times, end denominator
                "      <apply><minus/>\n"
                "        <apply><exp/>\n"
                "          <apply><divide/>\n"
                "            <apply><plus/>\n"
                "              <ci>V</ci>\n"
                "              <cn cellml:units=\"millivolt\">10</cn>\n"
                "            </apply>\n" // end plus
                "            <cn cellml:units=\"millivolt\">10</cn>\n"
                "          </apply>\n" // end divide
                "        </apply>\n" // end exp
                "        <cn cellml:units=\"dimensionless\">1</cn>\n"
                "      </apply>\n" // end minus
                "    </apply>\n" // end divide
                "  </apply>\n"; // end eq

            std::string equation3 =
                "  <apply><eq/>\n"
                "    <ci>beta_n</ci>\n"
                "    <apply><times/>\n"
                "      <cn cellml:units=\"per_millisecond\">0.125</cn>\n"
                "      <apply><exp/>\n"
                "        <apply><divide/>\n"
                "          <ci>V</ci>\n"
                "          <cn cellml:units=\"millivolt\">80</cn>\n"
                "        </apply>\n" // end divide
                "      </apply>\n" // end exp
                "    </apply>\n" // end times
                "  </apply>\n"; // end eq

.. code-block:: console

    The validator has found 13 errors!
        Validator error[0]:
            Description: MathML ci element has the child text 't' which does not correspond
            with any variable names present in component 'nGate'.

        ...

        Validator error[7]:
            Description: Math has a cn element with a cellml:units attribute
            'per_millivolt_millisecond' that is not a valid reference to units in the model
            'Tutorial6_PotassiumChannelModel' or a standard unit.

.. container:: dothis

    **2.c** Add the missing variables to the n-gate component, and specify their units.
    Validate your model again, this time expecting only errors relating to units.

.. code-block:: console

    The validator has found 4 errors!
    Validator error[0]:
        Description: Variable 'alpha_n' in component 'nGate' has a units reference
        'per_millisecond' which is neither standard nor defined in the parent model.
        See section 11.1.1.2 in the CellML specification.
    ...

.. container:: dothis

    **2.d** Create the missing units and add them to the model.
    Link the units of the model again, and recheck using the validator.
    Expect the model to be free of errors.

Step 3: Load the controller components
======================================


Step 4: Connect the components together
=======================================
In order for components to be able to relate to one another, we have to define two things.
Firstly, the hierarchy in which they exist - this is called the *encapsulation* and determines which components are able to access others.
Each component is only visible to its direct parents, direct children, and siblings (those which share a direct parent).
Secondly, we need to define the way in which the varaibles within the component relate to those outside it.
This is done by creating *equivalent variables*.

In this tutorial, we have an arrangement like that shown below.

.. code::

    ─ model:
        ├─ component: controller
        └─ component: potassium channel
            ├─ component: potassium channel initialisation
            └─ component: n-gate
                └─ component: n-gate initialisation

.. container:: dothis

    **4.a** Print the model to the screen to check your component hierarchy.

After checking how the components are arranged, we need to define which variables can access each other, and how.
This is done by making variables in different components *equivalent* to one another:

.. code-block:: cpp

    // Making the firstVariable and secondVariable equivalent to each other
    libcellml::Variable::addEquivalence(firstVariable, secondVariable);

In our model we have defined an "controller" component which we'll use to control all of the independent variables (time, voltage) during the simulation process.

.. container:: dothis

    **4.b** Use the addEquivalence functionality to match the time and voltage variables in the "controller" component with those in the other two.
    Note that if you have used the curly brackets :code:`{ }` to denote a limited scope for your variable definitions earlier, you will need to retrieve the variables from their components using their names, as they don't exist in the general scope of the code:

.. code-block:: cpp

    // Retrieve the pointers to the variables via their names and add an equivalence:
    libcellml::Variable::addEquivalence(controller->variable("t"), nGate->variable("t"));

.. container:: dothis

    **4.c** Validate your model and print the errors to the terminal.
    You should see errors related to missing specification of interface types, and - if you followed the example above - also about invalid connections between the n-gate component and the controller component.

.. code-block:: console

    The validator has found 8 errors!
      ...
      Validator error[5]:
        Description: The equivalence between 't' in component 'nGate' and 't' in component 'controller' is invalid.
        Component 'nGate' and 'controller' are neither siblings nor in a parent/child relationship.

There are some restrictions on which variables can be connected.
Variables can only be made equivalent if they are in neighbouring components; that is, a direct parent, direct child, or sibling component (one with the same parent).
We can add these two variables into the potassium channel component
as they are *sibling* components (their parent is the model):

.. code-block:: cpp

    // Valid: the potassiumChannel and nGate are parent and child:
    libcellml::Variable::addEquivalence(potassiumChannel->variable("t"), nGate->variable("t"));

    // Valid: the controller and potassiumChannel are siblings:
    libcellml::Variable::addEquivalence(controller->variable("t"), potassiumChannel->variable("t"));

... but we *cannot* make an equivalence between the :code:`t` variable in the
:code:`controller` component and the :code:`t` variable in the :code:`nGate` component, because that relationship is too distant.
Instead, we need to use the :code:`potassiumChannel` component as a go-between: it is a sibling of the :code:`controller` as well as a direct parent of the :code:`nGate`.

.. container:: dothis

    **4.d** Alter the equivalence arrangement you created in step 4.c so that the neighbouring component rule is followed.
    You will need to do this for the variables representing time :math:`t` and voltage :math:`V` between all components.
    Validate your model again.
    You should now see validation messages only related to interfaces, as shown below.

.. code-block:: console

    Validator error[0]:
      Description: Variable 'E_K' in component 'potassiumChannel' has no
      interface type set. The interface type required is 'private'.
      ...
    Validator error[2]:
      Description: Variable 'V' in component 'potassiumChannel' has no
      interface type set. The interface type required is 'public'.
      ...
    Validator error[5]:
      Description: Variable 'n' in component 'nGate' has no interface type set.
      The interface type required is 'public_and_private'.

The errors above are caused by the need to specify explicitly the kind of equivalence relationship which is allowed for each variable.
The default is :code:`none`, which prevents any equivalent connections, hence the errors above.

Here's how to think about equivalent variable interface types.
Imagine a family of components such that the mother has two children.
The interface types between the variables in these components needs to be specified as follows:

- Between the siblings, the :code:`public` interface type.
  Siblings know everything about each other.
- Between the children and their mother, the :code:`public` interface for the children, but the :code:`private` interface for the mother.
  Parents can know everything about their children, but children do not know everything about their parents.
- A third option is included to enable more than one kind of relationship to a variable, the :code:`public_and_private` type.
  This is used where successive generations mean that a variable needs to be :code:`private` in one relationship and :code:`public` in another.
  An uncle (the mother's brother) and the mother have a sibling-type (ie: :code:`public`) interface, but the mother must keep a :code:`private` interface for her children too.

.. container:: dothis

    **4.f**  Use the :code:`setInterfaceType` function for each of the shared variables to specify their avaiable interfaces using the recommendation from the error messages.
    Re-validate your model and confirm that it is now free of errors.
