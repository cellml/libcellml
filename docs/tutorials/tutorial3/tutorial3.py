"""
    TUTORIAL 3: MODEL CREATION THROUGH THE API

    By the time you have worked through Tutorial 3 you will be able to:
      - Create a new model and its child entities from scratch using the API;
      - Define custom combinations of built-in units;
      - Define your own custom units independent from the built-in units; and
      - Use the Generator to create C or Python code representing the model.

    This tutorial assumes that you are comfortable with:
      - Accessing and adjusting names of items inside a model hierarchy (T2);
      - Creating a validator and using it to check a model for errors (T2);
      - Accessing the errors produced by a validator and using them to correct
        the model (T2); and
      - Serialising and printing a model to a CellML file (T1).
"""

from libcellml import Component, Generator, GeneratorProfile, Model, Units, Validator, Variable

from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal

if __name__ == "__main__":
    print("-------------------------------------------------------------")
    print(" TUTORIAL 3: MODEL CREATION AND CODE GENERATION WITH THE API ")
    print("-------------------------------------------------------------")

    # ---------------------------------------------------------------------------
    #  STEP 1: Create the model instance
    #
    #  1.a   Create a Model and name it.

    #  1.b   Create a component to use as an integrator, set its attributes and
    #        add it to the model.

    #  1.c,d,e Create the MathML2 string representing the governing equation.

    #  1.f,g   Include the MathML strings in the component.

    #  1.h   Create a validator and use it to check the model so far.

    # ---------------------------------------------------------------------------
    #  STEP 2: Create the variables
    #

    #  2.a  Create the variables listed by the validator: d, a, b, c, time, y_s, y_f.

    #  2.b  Add the variables into the component.

    #  2.c  Call the validator again to check the model.

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
    #       First we create the "month" units, which will be equivalent to
    #       60*60*24*30 = 2,592,000 seconds.

    #  3.b  Create units which represent "per_month", which
    #       is simply the inverse of the "month" unit above.

    #  3.c  Create the sharks and thouseands_of_fish base units.

    #  3.d  Create the combined units for the constants.  Note that each item included
    #       with the addUnit command is multiplied to create the final Units definition.

    #  3.e  Set the units to their respective variables.

    #  3.f  Call the validator again to check the model.
    #       Expect one error regarding a missing unit in the MathML.

    #  3.g  Units for constants inside the MathML must be specified at the time.
    #       This means we need to adjust equation1 to include the per_month units.
    #       We have to wipe all the existing MathML and replace it.

    #  3.h  Validate once more, and expect there to be no errors this time.

    # ---------------------------------------------------------------------------
    #  STEP 4: Code generation
    #

    #  4.a Create a generator instance and pass it the model for processing.  The
    #      default profile is to generate C code, but we can change this later.

    #  4.b Check for errors found in the generator

    #  4.c Add initial conditions to all variables except the base variable, time
    #      and the constant c which will be computed. Reprocess the model.

    #  4.d Reprocess the model and check that the generator is now free of errors.

    #  4.e Because we've used the default profile (C) we need to output both the
    #      interfaceCode (the header file) and the implementationCode (source file)
    #      from the generator and write them.

    #  4.f Change the Generator profile to be Python instead of the default C

    #  4.g Retrieve the implementation code and print to a Python file

    #  4.h Go have a cuppa, you're done!
