'''
       TUTORIAL 6: POTASSIUM CHANNEL MODEL

   This tutorial explores the ability of CellML to represent more than one
   modelled process at a time using components with connections between them.
   By the time you have worked through Tutorial 6 you will be able to:
       - Assemble a multi-component model using the API; and
       - Inter-connect the components using the equivalent variables functionality.

   Tutorial 6 assumes that you are already comfortable with:
       - File manipulation and summarising using the utility functions;
       - Model creation through the API; and
       - Debugging the model using the Validator functionality.
'''

from libcellml import Component, Generator, GeneratorProfile, Model, Parser, Printer, Units, Validator, Variable
from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal

if __name__ == "__main__":

    #  0.a Setup useful things
    validator = Validator()
    mathHeader = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">\n'
    mathFooter = '</math>'

    print("----------------------------------------------------------")
    print("   STEP 1: Define the potassiumChannel component ")
    print("----------------------------------------------------------")

    #  STEP 1: Define the potassiumChannel component.
    #      As in the previous Tutorial 5, we define an ion channel, but this time make it
    #      specific to potassium.  We also introduce voltage dependence into the alpha and
    #      beta gate rates, and move them into a separate component to make it cleaner.
    #      This separate component is the nGate component, and will be defined in Step 2.

    #  1.a Create a model and add to it a new potassiumChannel component.

    #  1.b Define the maths inside the potassiumChannel component.  You might like to use
    #      the if True: idiom to limit the scope of your definition.

    #  1.c Call the validator and expect it to report errors related to missing variables and units.

    #  1.d Create the variables needed and add them to the potassium channel component

    #  1.e Check for errors.  Expect warnings about the undefined units in the maths and in the
    #      new variables added.

    #  1.f Add the missing units.  Verify that the model is now free of validation errors.
    #  NOTE: If, even after adding the Units the validator continues to return an error, you
    #      need to call the Model.linkUnits() function to link the units.  Unlinked units
    #      can occur when variables call their setUnits() function with
    #      a string argument of the Units item's name, rather than the Units item itself.

    print("----------------------------------------------------------")
    print("   STEP 2: Create the nGate component  ")
    print("----------------------------------------------------------")

    #  STEP 2: Create the nGate component
    #      This model differs from the one in Tutorial 5 in that voltage dependence is
    #      introduced into the opening and closing rates.  This dependence is handled in
    #      a separate component, the nGate component, which you'll define here.

    #  2.a Create an nGate component, and add it to the potassiumChannel component (NB: not the model!).
    #      Adding it to the component creates an encapsulation hierarchy, which affects which components
    #      have access to each other.  It also means that if the potassiumChannel component is
    #      moved or imported somewhere else, then the nGate child component will be included too.

    #  2.b Add the mathematics to the nGate component and validate the model.
    #      Expect errors relating to missing variables.

    #  2.c Add the missing variables to the nGate component, link the units, and validate again.
    #      Expect errors relating to missing units.

    #  2.d Create the missing units and add them to the model.  Link the model's
    #      units and validate again.  Expect the model to be free of errors.

    print("----------------------------------------------------------")
    print("   STEP 3: Read the controllers ")
    print("----------------------------------------------------------")

    #  STEP 3: The controller is a component at the top level of this model.
    #      This allows for it to be more easily interchangable between runs and stimulus
    #      conditions.  In later tutorials we will move this component into an external file so that the
    #      model is separate from the running parameters and initial conditions.

    #  3.a Create a Parser, and use it to read a temporary model from the controller file supplied.

    #  3.b From the parsed model, retrieve the component named "controller", remove its parent,
    #      and add it to the current model at the top level.

    #  3.c Repeat the process to retrieve the "parameters" component and add to
    #      the current model at the top level.

    #  3.d Print the model to the terminal and check its component hierarchy matches:
    #      ─ model:
    #          ├─ component: controller
    #          ├─ component: parameters
    #          └─ component: potassium channel
    #              └─ component: n-gate

    #  3.e Link units and revalidate the model.  Check that there are no errors.

    print("----------------------------------------------------------")
    print("   STEP 4: Connect the components together ")
    print("----------------------------------------------------------")

    #  STEP 4: Connect the components together.
    #      In order for the voltage dependence of the alpha and beta rates within
    #      the nGate component to affect the current in the potassiumChannel component
    #      some of the variables need to share their values between the components.
    #      This is done using variable equivalence and interfaces.

    #  4.a Set the equivalent variable pairs between the nGate and potassiumChannel components.
    #      These are:
    #          - voltage, V
    #          - time, t
    #          - gate status, n
    #      Use the Variable.addEquivalence(VariablePtr, VariablePtr) function.

    #  4.b Validate the model.  Expect errors related to unspecified interface types and invalid connections.

    #  4.c (if required) Remove the equivalences between too-distant components using the
    #  Variable.removeEquivalence(VariablePtr, VariablePtr) function, and connect to the correct
    #  component variables instead.

    #  4.d Set the recommended interface types for all of the variables with connections.

    #  4.e Revalidate the model, and check that it is now free of errors.

    print("----------------------------------------------------------")
    print("   STEP 5: Generate the model and output")
    print("----------------------------------------------------------")

    #  5.a Create a Generator instance and pass it the model for processing.  Check for errors and
    #      print them to the terminal.  We expect to see errors reporting that some variables are not
    #      computed or not initialised.

    #  5.b Create a Printer instance and use it to serialise the model.  Print this to a *.cellml file.

    #  5.c Write the interface code to a .h file.

    #  5.d Write the implementation code to a .c file.

    #  5.e Change the profile to Python and reprocess the model.

    #  5.f Write the Python implementation code to a .py file.

    #  5.g Please see the instructions in the tutorial for how to run a
    #      simulation of this model using the simple solver provided.
    #      Then go and have a cuppa, you're done!
