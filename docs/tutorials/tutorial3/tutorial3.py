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
    #   1.a   Create a Model

    #   1.b   Create a component, set its name and add it to the model

    #   1.c,d,e Create the MathML2 string representing the governing equations.  The
    #        header and footer are below already.
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    #   1.f   Include the MathML strings in the component

    #  1.g   Create a validator and use it to check the model so far

    # ---------------------------------------------------------------------------
    #   STEP 2: Create the variables
    #

    #  2.a  Create the variables listed by the validator: d, a, b, c, time, y_s, y_f

    #  2.b  Add the variables into the component

    #  2.c  Call the validator again to check the model

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


    #  3.b  Create the sharks and fishes base units.

    #  3.c  Create the combined units for the constants.  Note that each item included
    #       with the addUnit command is multiplied to create the final Units definition

    #  3.d  Set the units to their respective variables

    #  3.e  Call the validator again to check the model.
    #       Expect one error regarding a missing unit in the MathML.

    #  3.f  Units for constants inside the MathML must be specified at the time.
    #       This means we need to adjust equation1 to include the per_day units.
    #       We have to wipe all the existing MathML and replace it.

    #  3.g  Validate once more, and expect there to be no errors this time.

    # ---------------------------------------------------------------------------
    #  STEP 4: Code generation
    #

    #  4.a Create a generator instance and pass it the model for processing.  The
    #      default profile is to generate C code, but we can change this later.

    #  4.b Check for errors found in the generator

    #  4.c Add initial conditions to all variables except the base variable, time
    #      and the constant c which will be computed. Reprocess the model.

    #  4.d Because we've used the default profile (C) we need to output both the
    #      interfaceCode (the header file) and the implementationCode (source file)
    #      from the generator and write them.

    #  4.e Change the Generator profile to be Python instead of the default C

    #  4.f Create the implementation code and print to a Python file

    #  4.g Go have a cuppa, you're done!
