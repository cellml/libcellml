"""
    TUTORIAL 3: MODEL CREATION THROUGH THE API

    By the time you have worked through Tutorial 3 you will be able to:
      - create a new model and its child entities from scratch using the API
      - define custom combinations of built-in units
      - define your own custom units independent from the built-in units

    This tutorial assumes that you are comfortable with:
      - accessing and adjusting names of items inside a model hierarchy (T2)
      - creating a validator and using it to check a model for errors (T2)
      - accessing the errors produced by a validator and using them to correct
        the model (T2)
      - serialising and printing a model to a CellML file (T1)
"""

from libcellml import Component, Generator, GeneratorProfile, Model, Units, Validator, Variable

from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("     TUTORIAL 3: CREATE A MODEL USING THE API        ")
    print("-----------------------------------------------------")

    # ---------------------------------------------------------------------------
    #   STEP 1: Create the model instance
    #
    #   1.a   Allocate the ModelPtr
    model = Model()
    model.setName("Tutorial3_model")

    #   1.b   Create a component to use as an integrator, set its attributes and
    #        add it to the model
    component = Component()
    component.setName("component")
    model.addComponent(component)

    #   Checking that it worked
    print_model_to_terminal(model)

    #   1.c,d Create the MathML2 string representing the governing equation.  The
    #        header and footer are below already.
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    equation = "<apply><eq/>\
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
                </apply>"

    #   1.e   Include the MathML strings in the component
    component.setMath(math_header)
    component.appendMath(equation)
    component.appendMath(math_footer)

    #  1.f   Create a validator and use it to check the model so far
    validator = Validator()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.g   Create some variables and add them to the component
    time = Variable()
    time.setName("t")
    component.addVariable(time)

    distance = Variable()
    distance.setName("x")
    component.addVariable(distance)

    #  1.e   Assign units to the variables
    time.setUnits("millisecond")
    distance.setUnits("league")

    # Check it work and print the validation errors to the terminal
    print("-----------------------------------------------------")
    print("     Printing the model at Step 1        ")
    print("-----------------------------------------------------")
    print_model_to_terminal(model)

    print("-----------------------------------------------------")
    print("     Printing the validation errors after Step 1     ")
    print("-----------------------------------------------------")
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    # ---------------------------------------------------------------------------
    #  STEP 2: Create the user-defined units
    #
    #  From the validation errors printed above you'll see that none of the three
    #  units we need are built-in. The good news is that we can create the ones
    #  we need from the set of built-in units, we just need to define the
    #  relationship.  NB: Even though units are used by Variables, which sit
    #  'inside' Components, Units sit inside the Model itself.  This helps you to
    #  reuse Units when you have more than one component (more on that in
    #  Tutorial 5)

    #  2.a  Define the relationship between our custom units and the built-in
    #       units. There is a list of built-in units and their definitions
    #       available in section 19.2 of the CellML2 specification.
    millisecond = Units()
    millisecond.setName("millisecond")
    millisecond.addUnit("second", "milli")
    # "second" is a built-in unit, used inside millisecond with the
    # prefix "milli".  NB this is equivalent to specifying a prefix
    # integer value of -3, corresponding to the power of 10 by
    # which the base is multiplied.

    league = Units()
    league.setName("league")
    league.addUnit("metre", 3, 1.0, 5.556)
    # "metre" is a built-in unit.  A league is equal to 5556m, but here
    # we illustrate the overloaded function by passing a prefix of 3
    # (indicating a factor of 10^3), an exponent of 1, and a
    # multiplier of 5.556.

    #  2.b  Add the units to the model
    model.addUnits(millisecond)
    model.addUnits(league)

    #  2.c  Validate the model again and output the errors
    # validator.validateModel(model)
    # print_errors_to_terminal(validator)

    #  2.d  Change the constant "b" to have a hard-coded value of 2.0 in the MathML
    #       and amend the component's math block.
    equation2 = '<apply><eq/>\
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
                        <cn cellml:units="league">2.0</cn>\
                    </apply>\
                </apply>'

    component.setMath(math_header)
    component.appendMath(equation2)
    component.appendMath(math_footer)

    #  2.e Create and define the constant "a" to have a value of -1.  Check that there
    #      are no more validation errors.
    a = Variable()
    a.setName("a")
    a.setUnits("dimensionless")
    a.setInitialValue(-1.0)
    component.addVariable(a)

    print("-----------------------------------------------------")
    print("     Printing the validation errors after Step 2     ")
    print("-----------------------------------------------------")
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    # ---------------------------------------------------------------------------
    #  STEP 3: Output the model for solving
    #

    #  3.a Create a Generator instance and use it to process the model.  Output
    #      any errors to the terminal using the utility function printErrorsToTerminal
    #      called with your generator as argument.
    generator = Generator()
    generator.processModel(model)
    print_errors_to_terminal(generator)

    #  3.b Set the initial conditions of the distance variable such that x(t=0)=5 and
    #      check that there are no more errors reported.
    distance.setInitialValue(5.0)
    generator.processModel(model)
    print_errors_to_terminal(generator)

    #  3.c Check that the generator has the settings which we expect:
    #      - the number of variables
    #      - the language of output
    #      - the variable of integration
    #      - the type of model
    print("-----------------------------------------------------")
    print("       Investigating the Generator settings          ")
    print("-----------------------------------------------------")

    print("Number of variables = {}".format(generator.variableCount()))
    print("Variable of integration = {}".format(generator.voi().name()))
    print("Number of states = {}".format(generator.stateCount()))
    # print("Model type = " + get_model_type_from_enum(generator.modelType()))

    #  3.d Change the Generator profile to be Python instead of the default C
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

    #  3.e Create the implementation code and print to a Python file

    implementation_code = generator.implementationCode()
    write_file = open("tutorial3_generated.py", "w")
    write_file.write(implementation_code)
    print("The {} has been printed to tutorial3_generated.py".format(model.name()))

    #  3.e Go have a cuppa, you're done!
