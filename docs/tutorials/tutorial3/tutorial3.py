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

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("     TUTORIAL 3: CREATE A MODEL USING THE API        ")
    print("-----------------------------------------------------")

    # ---------------------------------------------------------------------------
    #   STEP 1: Create the model
    #
    #   1.a   Create a model instance

    #   1.b   Create a component to use as an integrator, set its attributes and
    #         add it to the model

    #   Check that it worked by printing to the terminal

    #   1.c,d Create the MathML2 string representing the governing equation.  The
    #        header and footer are below already.
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    #   1.e   Include the MathML strings in the component

    #   1.f   Create a validator and use it to check the model so far

    #   1.g   Create some variables and add them to the component

    #   1.e   Assign units to the variables

    # Check it worked by printing the model, the maths, and the validation errors to the terminal

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

    #  2.b  Add the units to the model

    #  2.c  Validate the model again and output the errors

    #  2.d  Change the constant "b" to have a hard-coded value of 2.0 in the MathML
    #       and amend the component's math block.

    #  2.e  Create and define the constant "a" to have a value of 1.  Check that there
    #       are no more validation errors.

    # ---------------------------------------------------------------------------
    #  STEP 3: Output the model for solving
    #

    #  3.a  Create a Generator instance and use it to process the model.  Output
    #       any errors to the terminal using the utility function print_errors_to_terminal
    #       called with your generator as argument.

    #  3.b  Set the initial conditions of the distance variable such that x(t=0)=5 and
    #       check that there are no more errors reported.

    #  3.c  Check that the generator has the settings which we expect:
    #       - the number of variables
    #       - the language of output
    #       - the variable of integration
    #       - the type of model

    #  3.d  Create the implementation code and print to a Python file

    #  3.e  Go have a cuppa, you're done!

    # TODO Need to add instructions for how to solve the generated code ...
