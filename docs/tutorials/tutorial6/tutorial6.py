"""
    TUTORIAL 5: COMPONENTS AND CONNECTIONS

    This tutorial explores the ability of CellML to represent more than one
    modelled process at a time using components with connections between them.
    By the time you have worked through Tutorial 5 you will be able to:
        - import a Component or Units item from an existing CellML file
        - assemble a multi-component model using the API
        - inter-connect the components using the equivalent variables
        functionality
        - validate and debug the constructed model

    Tutorial 5 assumes that you are already comfortable with:
        - file manipulation and summarising using the utility functions (Tutorial 1)
        - model creation through the API (Tutorial 3)
        - debugging the model using the Validator functionality (Tutorial 2)
 """

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("    STEP 1: Read the ion channel component           ")
    print("-----------------------------------------------------")

    #  1.a  Read the model created in Tutorial 4.  Note that if you didn't do that tutorial you can simply
    #       copy the CellML file from resources/tutorial4_IonChannelModel.cellml

    #  1.b  Print the parsed model to the terminal and check its contents

    #  1.c  Create a Validator and use it to check that the model is ok so far by printing the errors to the terminal

    #  1.d  Retrieve the component and name it "potassiumChannel"

    print("-----------------------------------------------")
    print("  STEP 2: Create the environment component")
    print("-----------------------------------------------")

    #  2.a  Create the new environment component

    #  2.b  Add variables to the component.

    #  2.c  Add the new component to the model

    #  2.d  Call the validator to check that your model is valid so far.

    print("-----------------------------------------------")
    print("  STEP 3: Define the n-gate component ")
    print("-----------------------------------------------")

    #  3.a  Create the n-gate component and the variables it contains

    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    #  3.b  Create the MathML for the n-gate component and adding it in.

    #  3.c  Add the n-gate component into the model.

    #  3.d  Add the missing units (connected to the constant in the first equation) and recheck the validation

    print("-----------------------------------------------")
    print("  STEP 4: Define the component hierarchy ")
    print("-----------------------------------------------")

    #  4.a  Change the nGate component to be a child of the potassiumChannel component

    #  4.b  Verify the component hierarchy by printing the model to the screen

    #  4.c  Define the equivalent variables between components.  Note that if
    #       the variables have been defined within a limited scope (using an if True statement)
    #       you will need to retrieve them from each component first.

    #  4.d  Validate the model: this should show an error reporting that an
    #       invalid connection has been made between the environment and nGate
    #       components

    #  4.e  Fix the connection error above, and add the voltage and gating variable equivalences

    #  4.f  Add the interface specification.  The environment component is a sibling of the potassiumChannel
    #       component, so they will both use the public interface.  The nGate component is a child of the
    #       potassiumChannel, so will use the public interface.  The potassiumChannel is the parent of the
    #       nGate component, so will need an additional private interface.  The nGate will have a public
    #       interface to its parent, the potassiumChannel.  Thus for the V and t variables:
    #          - environment . public
    #          - potassiumChannel . public_and_private
    #          - nGate . public
    #       Because the n variable is shared only between the potassiumChannel and the nGate, we don't need to
    #       use the public_and_private designation there just private on the parent and public on the child.

    print("-----------------------------------------------")
    print("  STEP 5: Define the driving function ")
    print("-----------------------------------------------")

    #  5.a  Define a MathML string representing the voltage clamp

    #  5.b  Add this to the maths for the environment component.

    #  5.c  Validate the model including this new maths block

    print("-----------------------------------------------")
    print("    STEP 6: Serialise and print the model      ")
    print("-----------------------------------------------")

    #  6.a  Create a Printer item and submit your model for serialisation.

    #  6.b  Go and have a cuppa, you're done!
