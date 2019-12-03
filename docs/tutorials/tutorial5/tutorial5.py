"""
    TUTORIAL 4: Mathematical behaviour and units

    This tutorial assumes that you can already:
        - read and deserialise a CellML model from a file (Tutorial 1)
        - retrieve the name and id of models, components, and variables (Tutorial 2),
        - navigate through the hierarchy of the model (Tutorial 2)
        - serialise and print a Model structure to a CellML file (Tutorial 1)
        - create and include user-defined units (Tutorial 3)
"""

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("    STEP 1: Create the model and component           ")
    print("-----------------------------------------------------")

    #  1.a   Create the model instance

    #  1.b   Create a component and add it into the model

    #  1.c   Call the validator and print the messages to the terminal. No errors are expected at this stage.

    print("-----------------------------------------------")
    print("  STEP 2: Define the mathematical behaviour    ")
    print("-----------------------------------------------")

    #  2.a   Define the mathematics.  The header and footer are provided for you.
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    #  2.b   Add the maths to the component.  Note that there is only one maths
    #        string stored, so parts which are appended must create a viable
    #        MathML2 string when concatenated.  To clear any string which is
    #        already stored, simply call setMath("") with an empty string.

    #  2.c:  Call the validator and print the messages to the terminal.
    #        Expected errors refer to variables referenced in the maths which
    #        are not (yet) defined in the component, as well as cn element units
    #        which are not defined yet either.

    print("-----------------------------------------------")
    print("  STEP 3: Define the variables and their units ")
    print("-----------------------------------------------")

    #  3.a,b Declare the variables, their names, units, and initial conditions
    #        Note that the names given to variables must be the same as that used
    #        within the <ci> blocks in the MathML string we created in step 2.a.

    #  3.c  Add the variables to the component.  Note that Variables are
    #       added by their pointer (cf. their name)

    #  3.d  Call the validator and print the messages to the terminal.
    #       Expected errors refer to units referred to by these variables, but
    #       which don't (yet) exist in the model.

    print("-----------------------------------------------")
    print("  STEP 4: Define the units and add to the model")
    print("-----------------------------------------------")

    #  4.a  Define the units of millisecond, millivolt, per_millisecond,
    #       microA_per_cm2, and milliS_per_cm2. Note that the dimensionless
    #       units are part of those built-in already, so do not need to be
    #       defined here.

    #  4.b  Add these units into the model

    #  4.c  Validate the final arrangement.  No errors are expected at this stage.

    print("-----------------------------------------------")
    print("  STEP 5: Serialise and print the model")
    print("-----------------------------------------------")

    #  5.a  Create a Printer item and submit your model for serialisation.

    #  5.b  Write the serialised string output from the printer to a file.

    #  5.c  Go and have a cuppa, you're done!
