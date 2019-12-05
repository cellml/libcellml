"""
    TUTORIAL 4: GENERATING CODE AND SIMULATION

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
from tutorial3_PredatorPrey_generated import * as model

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("     TUTORIAL 4: CREATE A MODEL USING THE API        ")
    print("-----------------------------------------------------")

    # ---------------------------------------------------------------------------
    #  STEP 1: Include the generated code in this project

    #  1.a Import the entirety of the module generated 

    #  1.b Check that the libcellml and generated libcellml versions match
    print("The generated code used libCellML version: " + model.LIBCELLML_VERSION)
    print("The library version of libCellML is: "+ libcellml.versionString())

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
    
    print("VARIABLE_COUNT = " + model.VARIABLE_COUNT)

    for v in range(0, model.VARIABLE_COUNT):
        print("Variable " + v + ": " )
        print("  name = " + model.VARIABLE_INFO[v].name )
        print("  units = " + model.VARIABLE_INFO[v].units )
        print("  component = " + model.VARIABLE_INFO[v].component )
        print("  type = " + model.VARIABLE_INFO[v].type )

    #  2.b Get the number of state variables and print their information to the terminal.
    #      State variables are those which need integration as part of their solution.
    #      They are stored in an array of VariableInfo structs called STATE_INFO which
    #      is STATE_COUNT long.  The VariableInfo struct contains:
    #          - name
    #          - units
    #          - component
    
    print("STATE_COUNT = " + model.STATE_COUNT )
    for s in range(0, model.STATE_COUNT):
        print("State variable " + s + ": " )
        print("  name = " + model.STATE_INFO[s].name )
        print("  units = " + model.STATE_INFO[s].units )
        print("  component = " + model.STATE_INFO[s].component )
    

    #  2.c Get the integration variable and print the information to the terminal. This
    #      is stored in a VariableInfo struct called VOI_INFO

    print("VOI_INFO" )
    print("  name = " + model.VOI_INFO.name )
    print("  units = " + model.VOI_INFO.units )
    print("  component = " + model.VOI_INFO.component )

    # ---------------------------------------------------------------------------
    # STEP 3: Investigate the functions provided in the generated files

    #  3.a Retrieve appropriately allocated arrays which contain the state variables
    #      and variables
    my_variables = model.createVariablesArray()
    my_state_variables = model.createStatesArray()

    #  3.b Initialise the arrays and print them to the screen for checking
    model.initializeStatesAndConstants(myStateVariables, myVariables)

    print("The initial conditions for variables are:" )
    for v in range(0, model.VARIABLE_COUNT):
        print(VARIABLE_INFO[v].name + " = " + myVariables[v] )
    
    print("The initial conditions for state variables are:" )
    for v in range(0, model.VARIABLE_COUNT):
        print(model.STATE_INFO[v].name + " = " + myStateVariables[v] )
    
    #  3.c Compute the constants and variables
    model.computeComputedConstants(myVariables)
    print("The completed initial conditions for variables are:" )
    for v in range(0, model.VARIABLE_COUNT):
        print(model.STATE_INFO[v].name + " = " + myStateVariables[v] )

    # --------------------------------------------------------------------------
    #  STEP 4: Iterate through the solution
    #  This part will make use of a simple routine to step through the solution
    #  iterations using the Euler method to update the state variables.

    #  4.a Set the variables which determine how long the solution will run for:
    #      - step size
    #      - number of steps to take
    time = 0.0
    stepSize = 0.01
    stepCount = 2000

    #  4.b Create an array for the rates.  You can use the createStatesArray function
    #      to allocate this as they have the same size. TODO rename this function??
    my_rates = model.createStatesArray()

    #  4.c Create a file for output and open it.
    std::ofstream outFile("solution.txt");
    outFile + "iteration";
    outFile + "\t" + VOI_INFO.name + " (" + VOI_INFO.units + ")";
    for (size_t s = 0; s < STATE_COUNT; ++s) {
        outFile + "\t" + STATE_INFO[s].name;
    }
    outFile )

    #  4.d Iterate through the time domain and write the solution at each step.
    #      The Euler update method is: x[n+1] = x[n] + x'[n]*stepSize
    #      At each step you will need to:
    #          - compute the variables
    #          - compute the rates
    #          - compute the state variables using the update method above
    #          - print to a file
    for (size_t step = 0; step < stepCount; ++step) {
        time = step * stepSize;

        # Compute the variables at this step
        computeVariables(time, myStateVariables, myRates, myVariables);

        # Computing the rates at this step
        computeRates(time, myStateVariables, myRates, myVariables);

        outFile + step + "\t " + time;
        # Computing the solution at the next step using Euler to advance
        for (size_t s = 0; s < STATE_COUNT; ++s) {
            myStateVariables[s] = myStateVariables[s] + myRates[s] * stepSize;
            outFile + "\t" + myStateVariables[s];
        }
        outFile + "\n";
    }
    outFile.close();

    # --------------------------------------------------------------------------
    #  STEP 5: Output the results

    #  5.a Housekeeping - delete the allocated arrays
    deleteArray(myStateVariables);
    deleteArray(myVariables);
    deleteArray(myRates);

    #  5.b Go and have a cuppa, you're done!
    print("The results have been written to 'solution.txt'" )
}
