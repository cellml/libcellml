/**
 *  SIMPLE SOLVER
 *
 *  Very simple implementation of an Euler-stepping solver intended to solve
 *  files created using the libCellML::Generator functionality.  This file needs to be
 *  built with the accompanying CMakeLists file, which will copy the input file to a
 *  the "modelToSolve.[c|h]" files which this solver uses.  A new solver executable is
 *  created for each different input model file.
 *
 *  Inputs:
 *      -n the number of steps to take
 *      -dt the stepsize to use
 *
 *  Outputs:
 *      - a tab-delimited text file with the columns: iteration, VOI, state1, state2, ...
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

// #include "../utilities/tutorial_utilities.h"
#include "modelToSolve.h"

std::map<std::string, std::string> processArguments(int argc, char **argv);

int main(int argc, char **argv)
{
    std::map<std::string, std::string> args = processArguments(argc, argv);

    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "   SIMPLE SOLVER  " << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "       model = " << args["input"] << std::endl;
    std::cout << "       timestep = " << args["dt"] << std::endl;
    std::cout << "       number of steps = " << args["n"] << std::endl
              << std::endl;

    std::cout << "   STATE VARIABLES (units) " << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < STATE_COUNT; ++i) {
        std::cout << "      " << STATE_INFO[i].name << " (" << STATE_INFO[i].units << ")" << std::endl;
    }
    std::cout << std::endl;

    double time = 0.0;
    double stepSize = std::stod(args["dt"]);
    int stepCount = std::stoi(args["n"]);
    auto myVariables = createVariablesArray();
    auto myStateVariables = createStatesArray();
    auto myRates = createStatesArray();

    initializeStatesAndConstants(myStateVariables, myVariables);
    computeComputedConstants(myVariables);
    computeRates(time, myStateVariables, myRates, myVariables);
    computeVariables(time, myStateVariables, myRates, myVariables);

    std::cout << "   INITIAL CONDITIONS" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < STATE_COUNT; ++i) {
        std::cout << "      " << STATE_INFO[i].name << "(" << VOI_INFO.name << " = 0) = " << myStateVariables[i] << std::endl;
    }
    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        std::cout << "      " << VARIABLE_INFO[i].name << "(" << VOI_INFO.name << " = 0) = " << myVariables[i] << std::endl;
    }

    std::cout << std::endl;
    std::string outFileName = args["input"] + "_solution.txt";
    std::ofstream outFile(outFileName);

    // Header line for output file
    outFile << "iteration";
    outFile << "\t" << VOI_INFO.name << " (" << VOI_INFO.units << ")";
    for (size_t s = 0; s < STATE_COUNT; ++s) {
        outFile << "\t" << STATE_INFO[s].name;
    }
    for (size_t s = 0; s < VARIABLE_COUNT; ++s) {
        outFile << "\t" << VARIABLE_INFO[s].name;
    }
    outFile << std::endl;

    // Initial conditions in output file
    outFile << 0;
    outFile << "\t" << 0;
    for (size_t s = 0; s < STATE_COUNT; ++s) {
        outFile << "\t" << myStateVariables[s];
    }
    for (size_t s = 0; s < VARIABLE_COUNT; ++s) {
        outFile << "\t" << myVariables[s];
    }
    outFile << std::endl;


    // Solution columns in output file
    for (size_t step = 1; step < stepCount; ++step) {
        time = step * stepSize;
        computeRates(time, myStateVariables, myRates, myVariables);
        outFile << step << "\t " << time;
        for (size_t s = 0; s < STATE_COUNT; ++s) {
            myStateVariables[s] = myStateVariables[s] + myRates[s] * stepSize;
            outFile << "\t" << myStateVariables[s];
        }
        computeVariables(time, myStateVariables, myRates, myVariables); // update states before updating variables?
        for (size_t s = 0; s < VARIABLE_COUNT; ++s) {
            outFile << "\t" << myVariables[s];
        }
        outFile << "\n";
    }
    outFile.close();

    deleteArray(myStateVariables);
    deleteArray(myVariables);
    deleteArray(myRates);

    std::cout << "   OUTPUT" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "      The results have been written to:"<<std::endl;
    std::cout << "          "<< outFileName << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
}

std::map<std::string, std::string> processArguments(int argc, char **argv)
{
    if (argc == 1) {
        std::cout << "Usage:" << std::endl;
        std::cout << "  -n maxSteps -dt stepSize" << std::endl;
        std::cout << "     -n     the number of steps to take before stopping" << std::endl;
        std::cout << "     -dt    the step size to use" << std::endl;
        exit(1);
    }

    std::map<std::string, std::string> argMap;
    std::string value = argv[0];
    value.erase(0, 8); // removes the "solve_" from the start of the executable name to get back to the input
    argMap["input"] = value;

    for (size_t i = 0; i < argc - 1; ++i) {
        if (argv[i][0] == '-') {
            std::string key = argv[i];
            key.erase(0, 1);
            value = argv[i + 1];
            argMap[key] = value;
            i++;
        }
    }
    return argMap;
}
