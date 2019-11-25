"""
    TUTORIAL 7: Creating the Sodium Channel

    This tutorial is an opportunity to practise creating models from
    scratch using the libCellML API.  The model you create here will
    be used later on in Tutorial 8.
 
    Tutorial 7 assumes that you are already comfortable with:
        - the concept of component hierarchy and encapsulation (Tutorial 5)
        - the use of the API to create all of the entities in a model (Tutorial 3)
        - the content MathML2 markup for mathematical equations (Tutorial 4)
        - serialisation and printing of a model to a CellML file (Tutorial 1)

"""

if __name__ == "__main__":
    #  0 Set up stuff that is used throughout: a Validator, a Model, and the MathML header and footer
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    print("-----------------------------------------------")
    print("  STEP 1: Creating the sodium channel")
    print("-----------------------------------------------")

    #  1.a  Create the component instance, name it, and add to the model

    #  1.b  Add the MathML representing the governing equations

    #  1.c  Add the variables

    #  1.d  Add the units

    #  1.e  Print validation errors to the terminal

    print("-----------------------------------------------")
    print("  STEP 2: Creating the m-gate")
    print("-----------------------------------------------")

    #  2.a  Create the component representing the m-gate and add it to the sodium channel component

    #  2.b  Add the MathML strings which govern the behavior of this gate

    #  2.c  Call the validator - expect errors related to missing variables, then add the variables needed

    #  2.d  Call the validator to check the model - expect errors related to units missing from the model.
    #       Add them in as needed.

    print("-----------------------------------------------")
    print("  STEP 3: Creating the h-gate")
    print("-----------------------------------------------")

    #  3.a  Create the hGate component and add it to the sodium channel component

    #  3.b  Adding the MathML strings

    #  3.c  Adding the variables

    #  3.d  Add the missing units

    print("-----------------------------------------------")
    print("  STEP 4: Creating the environment component")
    print("-----------------------------------------------")

    #  4.a  Create the new environment component

    #  4.b  Add variables to the component

    #  4.c  Add the new component to the model and validate

    print("-----------------------------------------------")
    print("  STEP 5: Connecting variables and components")
    print("-----------------------------------------------")

    #  5.a  Connect the equivalent variables between all the components

    print("-----------------------------------------------")
    print("       STEP 6: Set the driving function")
    print("-----------------------------------------------")

    #  6.a Create the MathML controlling the driving function

    #  6.b Validate the final model

    print("-----------------------------------------------")
    print("    STEP 7: Serialise and print the model ")
    print("-----------------------------------------------")

    #  7.a  Serialise and output the model to a CellML file

    #  7.b  Go and have a cuppa, you're done!
