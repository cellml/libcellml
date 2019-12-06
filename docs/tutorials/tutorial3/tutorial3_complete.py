"""
    TUTORIAL 3: MODEL CREATION THROUGH THE API

    By the time you have worked through Tutorial 3 you will be able to:
      - create a new model and its child entities from scratch using the API
      - define custom combinations of built-in units
      - define your own custom units independent from the built-in units
      - use the Generator to create C or Python code representing the model

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
    print("-------------------------------------------------------------")
    print(" TUTORIAL 3: MODEL CREATION AND CODE GENERATION WITH THE API")
    print("-------------------------------------------------------------")

    # ---------------------------------------------------------------------------
    #   STEP 1: Create the model instance
    #
    #   1.a   Allocate the ModelPtr
    model = Model()
    model.setName("tutorial3_model")

    #   1.b   Create a component to use as an integrator, set its attributes and
    #         add it to the model
    component = Component()
    component.setName("component")
    model.addComponent(component)

    #   Checking that it worked
    print_model_to_terminal(model)

    #   1.c,d,e Create the MathML2 string representing the governing equation.  The
    #        header and footer are below already.
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    equation1 = \
        "<apply><eq/>"\
        "   <ci>c</ci>"\
        "   <apply><plus/>"\
        "       <ci>a</ci>"\
        "       <cn>2.0</cn>"\
        "   </apply>"\
        "</apply>"

    equation2 = \
        "<apply><eq/>"\
        "   <apply><diff/>"\
        "   <bvar><ci>time</ci></bvar>"\
        "   <ci>y_s</ci>"\
        "   </apply>"\
        "   <apply><plus/>"\
        "       <apply><times/>"\
        "           <ci>a</ci>"\
        "           <ci>y_s</ci>"\
        "      </apply>"\
        "      <apply><times/>"\
        "          <ci>b</ci>"\
        "          <ci>y_s</ci>"\
        "          <ci>y_f</ci>"\
        "      </apply>"\
        "   </apply>"\
        "</apply>"

    equation3 =\
        "<apply><eq/>"\
        "   <apply><diff/>"\
        "   <bvar><ci>time</ci></bvar>"\
        "   <ci>y_f</ci>"\
        "   </apply>"\
        "   <apply><plus/>"\
        "       <apply><times/>"\
        "           <ci>c</ci>"\
        "           <ci>y_f</ci>"\
        "      </apply>"\
        "      <apply><times/>"\
        "          <ci>d</ci>"\
        "          <ci>y_s</ci>"\
        "          <ci>y_f</ci>"\
        "      </apply>"\
        "   </apply>"\
        "</apply>"

    #   1.f   Include the MathML strings in the component
    component.setMath(math_header)
    component.appendMath(equation1)
    component.appendMath(equation2)
    component.appendMath(equation3)
    component.appendMath(math_footer)

    #  1.g   Create a validator and use it to check the model so far
    validator = Validator()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    # ---------------------------------------------------------------------------
    #   STEP 2: Create the variables
    #

    #  2.a  Create the variables listed by the validator: d, a, b, c, time, y_s, y_f
    sharks = Variable("y_s")
    fish = Variable("y_f")
    time = Variable("time")
    a = Variable("a")
    b = Variable("b")
    c = Variable("c")
    d = Variable("d")

    #  2.b  Add the variables into the component
    component.addVariable(sharks)
    component.addVariable(fish)
    component.addVariable(time)
    component.addVariable(a)
    component.addVariable(b)
    component.addVariable(c)
    component.addVariable(d)

    #  2.c  Call the validator again to check the model
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    # ---------------------------------------------------------------------------
    #  STEP 3: Create the user-defined units
    #
    #  From the validation errors printed above you'll see that none of the
    #  units we need are built-in. The good news is that we can create the ones
    #  we need from the set of built-in units, we just need to define the
    #  relationship.  NB: Even though units are used by Variables, which sit
    #  'inside' Components, Units sit inside the Model itself.  This helps you to
    #  reuse Units when you have more than one component (more on that in
    #  Tutorial 5)

    #  3.a  Define the relationship between our custom units and the built-in
    #       units. There is a list of built-in units and their definitions
    #       available in section 19.2 of the CellML2 specification.
    #       First we create the "day" and "per_day" units
    day = Units()
    day.setName("day")
    day.addUnit("second", "3", 1, 86.4)
    model.addUnits(day)
    # "second" is a built-in unit, used inside "day" with the
    # multiplier 84600.  NB this is equivalent to specifying a prefix
    # string value of 3, corresponding to the power of 10 by
    # which the base is multiplied, as well as a multiplier of 86.4, etc

    # The "per_day" unit is simply the inverse of the "day"
    per_day = Units()
    per_day.setName("per_day")
    per_day.addUnit("day", -1)
    model.addUnits(per_day)

    #  3.b  Create the sharks and fishes base units.
    number_of_sharks = Units()
    number_of_sharks.setName("number_of_sharks")
    model.addUnits(number_of_sharks)
    thousands_of_fish = Units()
    thousands_of_fish.setName("thousands_of_fish")
    model.addUnits(thousands_of_fish)

    #  3.c  Create the combined units for the constants.  Note that each item included
    #       with the addUnit command is multiplied to create the final Units definition
    b_units = Units()
    b_units.setName("per_shark_day")
    b_units.addUnit("per_day")
    b_units.addUnit("number_of_sharks", -1)
    model.addUnits(b_units)

    d_units = Units()
    d_units.setName("per_fish_day")
    d_units.addUnit("per_day")
    d_units.addUnit("thousands_of_fish", -1)
    model.addUnits(d_units)

    #  3.d  Set the units to their respective variables
    time.setUnits(day)
    sharks.setUnits(number_of_sharks)
    fish.setUnits(thousands_of_fish)
    a.setUnits(per_day)
    b.setUnits(b_units)
    c.setUnits(per_day)
    d.setUnits(d_units)

    #  3.e  Call the validator again to check the model.
    #       Expect one error regarding a missing unit in the MathML.
    validator.validateModel(model)

    #  3.f  Units for constants inside the MathML must be specified at the time.
    #       This means we need to adjust equation1 to include the per_day units.
    #       We have to wipe all the existing MathML and replace it.
    component.removeMath()
    component.setMath(math_header)
    equation1 = \
        "<apply><eq/>"\
        "   <ci>c</ci>"\
        "   <apply><plus/>"\
        "       <ci>a</ci>"\
        "       <cn cellml:units=\"per_day\">2.0</cn>"\
        "   </apply>"\
        "</apply>"
    component.appendMath(equation1)
    component.appendMath(equation2)
    component.appendMath(equation3)
    component.appendMath(math_footer)

    #  3.g  Validate once more, and expect there to be no errors this time.

    # ---------------------------------------------------------------------------
    #  STEP 4: Code generation
    #

    #  4.a Create a generator instance and pass it the model for processing.  The
    #      default profile is to generate C code, but we can change this later.
    generator = Generator()
    generator.processModel(model)

    # 4.b Check for errors found in the generator
    print_errors_to_terminal(generator)

    #  4.c Add initial conditions to all variables except the base variable, time
    #      and the constant c which will be computed. Reprocess the model.
    a.setInitialValue(-0.8)
    b.setInitialValue(0.3)
    d.setInitialValue(-0.6)
    sharks.setInitialValue(1.0)
    fish.setInitialValue(2.0)

    generator.processModel(model)
    print_errors_to_terminal(generator)

    #  4.d Because we've used the default profile (C) we need to output both the
    #      interfaceCode (the header file) and the implementationCode (source file)
    #      from the generator and write them.
    implementation_code_C = generator.implementationCode()
    write_file = open("tutorial3_PredatorPrey_generated.c", "w")
    write_file.write(implementation_code_C)
    write_file.close()

    interface_code = generator.interfaceCode()
    write_file = open("tutorial3_PredatorPrey_generated.h","w")
    write_file.write(interface_code)
    write_file.close()

    #  4.e Change the Generator profile to be Python instead of the default C
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

    #  4.f Create the implementation code and print to a Python file
    implementation_code_python = generator.implementationCode()
    write_file = open("tutorial3_PredatorPrey_generated.py", "w")
    write_file.write(implementation_code_python)

    print("All the files have been printed.")

    #  4.g Go have a cuppa, you're done!
