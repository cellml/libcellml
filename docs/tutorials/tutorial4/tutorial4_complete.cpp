/**
 *  TUTORIAL 4: INTERACT WITH GENERATED CODE
 *
 *  By the time you have worked through Tutorial 4 you will be able to:
 *    - investigate and understand the contents of files created by the Generator
 *    - integrate generated code into a simple solver to run a simulation
 *
 *  This tutorial assumes that you are comfortable with:
 *    - interacting with a model and its entities using the API (see Tutorial 3)
 *    - using the Generator functionality to output files in C or Python (Tutorial 3)
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

#include "../utilities/tutorial_utilities.h"
#include "tutorial3_PredatorPrey_generated.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   TUTORIAL 4: INTERACT WITH GENERATED CODE" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 1: Include the generated code in this project

    //  1.a Enter the path to the generated header/interface *.h file in the #includes above

    //  1.b Add the name and path of the implementation *.c file in the CMakeLists.txt file

    //  1.c Open your generated source *.cpp file and change the name of the header it includes
    //      using the #includ` statement to be the name of your generated header *.h file.
    //      By default this is #include "model.h".

    //  1.d Check that the versions match
    std::cout << "The generated code used libCellML version " << LIBCELLML_VERSION << std::endl;
    std::cout << "The library version of libCellML is " << libcellml::versionString() << std::endl;

    // ---------------------------------------------------------------------------
    // STEP 2: Investigate the contents of the generated files

    //  2.a Get the number of variables and print their information to the terminal.
    //      Variables are anything which does not require integration as part of the
    //      solution, and could have types COMPUTED_CONSTANT (needs to be calculated
    //      but doesn't need integration), CONSTANT (no calculation needed), or
    //      ALGEBRAIC (TODO??) as defined in the VariableType enum.
    //      They are stored in an array of VariableInfoWithType structs called
    //      VARIABLE_INFO which is VARIABLE_COUNT long.  The VariableInfoWithType contains:
    //          - name
    //          - units
    //          - component
    //          - VariableType
    std::cout << std::endl;
    std::cout << "VARIABLE_COUNT = " << VARIABLE_COUNT << std::endl;
    for (size_t v = 0; v < VARIABLE_COUNT; ++v) {
        std::cout << "Variable " << v << ": " << std::endl;
        std::cout << "  name = " << VARIABLE_INFO[v].name << std::endl;
        std::cout << "  units = " << VARIABLE_INFO[v].units << std::endl;
        std::cout << "  component = " << VARIABLE_INFO[v].component << std::endl;
        std::cout << "  type = " << VARIABLE_INFO[v].type << std::endl;
    }

    //  2.b Get the number of state variables and print their information to the terminal.
    //      State variables are those which need integration as part of their solution.
    //      They are stored in an array of VariableInfo structs called STATE_INFO which
    //      is STATE_COUNT long.  The VariableInfo struct contains:
    //          - name
    //          - units
    //          - component
    std::cout << std::endl;
    std::cout << "STATE_COUNT = " << STATE_COUNT << std::endl;
    for (size_t s = 0; s < STATE_COUNT; ++s) {
        std::cout << "State variable " << s << ": " << std::endl;
        std::cout << "  name = " << STATE_INFO[s].name << std::endl;
        std::cout << "  units = " << STATE_INFO[s].units << std::endl;
        std::cout << "  component = " << STATE_INFO[s].component << std::endl;
    }

    //  2.c Get the integration variable and print the information to the terminal. This
    //      is stored in a VariableInfo struct called VOI_INFO
    std::cout << std::endl;
    std::cout << "VOI_INFO" << std::endl;
    std::cout << "  name = " << VOI_INFO.name << std::endl;
    std::cout << "  units = " << VOI_INFO.units << std::endl;
    std::cout << "  component = " << VOI_INFO.component << std::endl;

    // ---------------------------------------------------------------------------
    // STEP 3: Investigate the functions provided in the generated files

    //  3.a Retrieve appropriately allocated arrays which contain the state variables
    //      and variables
    auto myVariables = createVariablesArray();
    auto myStateVariables = createStatesArray();

    //  3.b Initialise the arrays and print them to the screen for checking
    initializeStatesAndConstants(myStateVariables, myVariables);
    std::cout << std::endl;
    std::cout << "The initial conditions for variables are:" << std::endl;
    for (size_t v = 0; v < VARIABLE_COUNT; ++v) {
        std::cout << VARIABLE_INFO[v].name << " = " << myVariables[v] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "The initial conditions for state variables are:" << std::endl;
    for (size_t v = 0; v < STATE_COUNT; ++v) {
        std::cout << STATE_INFO[v].name << " = " << myStateVariables[v] << std::endl;
    }

    //  3.c Compute the constants and variables
    computeComputedConstants(myVariables);
    std::cout << std::endl;
    std::cout << "The initial conditions for variables are:" << std::endl;
    for (size_t v = 0; v < VARIABLE_COUNT; ++v) {
        std::cout << VARIABLE_INFO[v].name << " = " << myVariables[v] << std::endl;
    }

    // --------------------------------------------------------------------------
    //  STEP 4: Iterate through the solution
    //  This part will make use of a simple routine to step through the solution
    //  iterations using the Euler method to update the state variables.

    //  4.a Set the variables which determine how long the solution will run for:
    //      - step size
    //      - number of steps to take
    double time = 0.0;
    double stepSize = 0.01;
    int stepCount = 2000;

    //  4.b Create an array for the rates.  You can use the createStatesArray function
    //      to allocate this as they have the same size. TODO rename this function??
    auto myRates = createStatesArray();

    //  4.c Create a file for output and open it.
    std::ofstream outFile("solution.txt");
    outFile << "iteration";
    outFile << "\t" << VOI_INFO.name << " (" << VOI_INFO.units << ")";
    for (size_t s = 0; s < STATE_COUNT; ++s) {
        outFile << "\t" << STATE_INFO[s].name;
    }
    outFile << std::endl;

    //  4.d Iterate through the time domain and write the solution at each step.
    //      The Euler update method is: x[n+1] = x[n] + x'[n]*stepSize
    //      At each step you will need to:
    //          - compute the variables
    //          - compute the rates
    //          - compute the state variables using the update method above
    //          - print to a file
    for (size_t step = 0; step < stepCount; ++step) {
        time = step * stepSize;

        // Compute the variables at this step
        computeVariables(time, myStateVariables, myRates, myVariables);

        // Computing the rates at this step
        computeRates(time, myStateVariables, myRates, myVariables);

        outFile << step << "\t " << time;
        // Computing the solution at the next step using Euler to advance
        for (size_t s = 0; s < STATE_COUNT; ++s) {
            myStateVariables[s] = myStateVariables[s] + myRates[s] * stepSize;
            outFile << "\t" << myStateVariables[s];
        }
        outFile << "\n";
    }
    outFile.close();

    // --------------------------------------------------------------------------
    //  STEP 5: Output the results

    //  5.a Housekeeping - delete the allocated arrays
    deleteArray(myStateVariables);
    deleteArray(myVariables);
    deleteArray(myRates);

    //  5.b Go and have a cuppa, you're done!
    std::cout << "The results have been written to 'solution.txt'" << std::endl;
}
