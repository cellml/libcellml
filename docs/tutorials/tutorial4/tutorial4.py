"""
    TUTORIAL 4: GENERATING CODE AND SIMULATION

    By the time you have worked through Tutorial 4 you will be able to:
      - investigate and understand the contents of files created by the Generator
      - integrate generated code into a simple solver to run a simulation

    This tutorial assumes that you are comfortable with:
      - interacting with a model and its entities using the API (see Tutorial 3)
      - using the Generator functionality to output files in C or Python (Tutorial 3)

"""
from libcellml import versionString

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("     TUTORIAL 4: CODE GENERATION AND SIMULATION      ")
    print("-----------------------------------------------------")

    # ---------------------------------------------------------------------------
    #  STEP 1: Include the generated code in this project

    #  1.a Import the entirety of the module generated as "model"

    #  1.b Check that the libcellml and generated libcellml versions match

    # ---------------------------------------------------------------------------
    # STEP 2: Investigate the contents of the generated files

    #  2.a Get the number of variables and print their information to the terminal.
    #      Variables are anything which does not require integration as part of the
    #      solution, and could have types COMPUTED_CONSTANT (needs to be calculated
    #      but doesn't need integration), CONSTANT (no calculation needed), or
    #      ALGEBRAIC (TODO??) as defined in the VariableType enum.
    #      They are stored in an array of VariableInfoWithType structs called
    #      VARIABLE_INFO which is VARIABLE_COUNT long.  The VariableInfoWithType contains:
    #          - name
    #          - units
    #          - component
    #          - VariableType

    #  2.b Get the number of state variables and print their information to the terminal.
    #      State variables are those which need integration as part of their solution.
    #      They are stored in an array of VariableInfo structs called STATE_INFO which
    #      is STATE_COUNT long.  The VariableInfo struct contains:
    #          - name
    #          - units
    #          - component

    #  2.c Get the integration variable and print the information to the terminal. This
    #      is stored in a VariableInfo struct called VOI_INFO

    # ---------------------------------------------------------------------------
    # STEP 3: Investigate the functions provided in the generated files

    #  3.a Retrieve appropriately allocated arrays which contain the state variables
    #      and variables

    #  3.b Initialise the arrays and print them to the screen for checking

    #  3.c Compute the constants and variables

    # --------------------------------------------------------------------------
    #  STEP 4: Iterate through the solution
    #  This part will make use of a simple routine to step through the solution
    #  iterations using the Euler method to update the state variables.

    #  4.a Set the variables which determine how long the solution will run for:
    #      - step size
    #      - number of steps to take

    #  4.b Create an array for the rates.  You can use the createStatesArray function
    #      to allocate this as they have the same size. TODO rename this function??

    #  4.c Create a file for output and open it.

    #  4.d Iterate through the time domain and write the solution at each step.
    #      The Euler update method is: x[n+1] = x[n] + x'[n]*step_size
    #      At each step you will need to:
    #          - compute the variables
    #          - compute the rates
    #          - compute the state variables using the update method above
    #          - print to a file

    # --------------------------------------------------------------------------
    #  STEP 5: Output the results

    #  5.a Go and have a cuppa, you're done!

