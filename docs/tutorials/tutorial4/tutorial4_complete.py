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
import tutorial3_PredatorPrey as model

if __name__ == "__main__":
    print("-----------------------------------------------------")
    print("     TUTORIAL 4: CODE GENERATION AND SIMULATION      ")
    print("-----------------------------------------------------")

    # ---------------------------------------------------------------------------
    #  STEP 1: Include the generated code in this project

    #  1.a Import the entirety of the module generated as "model"

    #  1.b Check that the libcellml and generated libcellml versions match
    print("The generated code used libCellML version: " + model.LIBCELLML_VERSION)
    print("The library version of libCellML is: " + versionString())

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
    print("VARIABLE_COUNT = {}".format(model.VARIABLE_COUNT))
    for v in range(0, model.VARIABLE_COUNT):
        print("Variable {}:".format(v))
        print("  name = {}".format(model.VARIABLE_INFO[v]['name']))
        print("  units = {}".format(model.VARIABLE_INFO[v]['units']))
        print("  component = {}".format(model.VARIABLE_INFO[v]['component']))
        print("  type = {}".format(model.VARIABLE_INFO[v]['type']))

    #  2.b Get the number of state variables and print their information to the terminal.
    #      State variables are those which need integration as part of their solution.
    #      They are stored in an array of VariableInfo structs called STATE_INFO which
    #      is STATE_COUNT long.  The VariableInfo struct contains:
    #          - name
    #          - units
    #          - component
    print("STATE_COUNT = {}".format(model.STATE_COUNT))
    for s in range(0, model.STATE_COUNT):
        print("State variable {}:".format(s))
        print("  name = {}".format(model.STATE_INFO[s]['name']))
        print("  units = {}".format(model.STATE_INFO[s]['units']))
        print("  component = {}".format(model.STATE_INFO[s]['component']))

    #  2.c Get the integration variable and print the information to the terminal. This
    #      is stored in a VariableInfo struct called VOI_INFO
    print("VOI_INFO")
    print("  name = {}".format(model.VOI_INFO['name']))
    print("  units = {}".format(model.VOI_INFO['units']))
    print("  component = {}".format(model.VOI_INFO['component']))

    # ---------------------------------------------------------------------------
    # STEP 3: Investigate the functions provided in the generated files

    #  3.a Retrieve appropriately allocated arrays which contain the state variables
    #      and variables
    my_variables = model.create_variables_array()
    my_state_variables = model.create_states_array()
    my_rates = model.create_states_array()

    #  3.b Initialise the arrays and print them to the screen for checking
    time = 0.0
    model.initialize_states_and_constants(my_state_variables, my_variables)
    model.compute_rates(time, my_state_variables, my_rates, my_variables)
    model.compute_variables(time, my_state_variables, my_rates, my_variables)

    print("The initial conditions for variables are:")
    for v in range(0, model.VARIABLE_COUNT):
        print("  {} = {}".format(model.VARIABLE_INFO[v]['name'],my_variables[v]))

    print("The initial conditions for state variables are:")
    for v in range(0, model.STATE_COUNT):
        print("  {} = {}".format(model.STATE_INFO[v]['name'],my_state_variables[v]))

    #  3.c Compute the constants and variables
    time = 0.0
    model.compute_computed_constants(my_variables)
    model.compute_variables(time, my_state_variables, my_rates, my_variables)
    model.compute_rates(time, my_state_variables, my_rates, my_variables)
    print("The completed initial conditions for variables are:")
    for v in range(0, model.VARIABLE_COUNT):
        print("  {} = {}".format(model.VARIABLE_INFO[v]['name'],my_variables[v]))

    # --------------------------------------------------------------------------
    #  STEP 4: Iterate through the solution
    #  This part will make use of a simple routine to step through the solution
    #  iterations using the Euler method to update the state variables.

    #  4.a Set the variables which determine how long the solution will run for:
    #      - step size
    #      - number of steps to take
    step_size = 0.01
    step_count = 2000

    #  4.b Create an array for the rates.  You can use the create_states_array function
    #      to allocate this as they have the same size. TODO rename this function??
    my_rates = model.create_states_array()

    #  4.c Create a file for output and open it.
    row = "iteration\t{}({})".format(model.VOI_INFO['name'], model.VOI_INFO['units'])
    for s in range(0, model.STATE_COUNT):
        row += "\t{}({})".format(model.STATE_INFO[s]['name'], model.STATE_INFO[s]['units'])
    for s in range(0, model.VARIABLE_COUNT):
        row += "\t{}({})".format(model.VARIABLE_INFO[s]['name'], model.VARIABLE_INFO[s]['units'])
    row += "\n"

    write_file = open("tutorial4_solution.txt", "w")
    write_file.write(row)

    #  4.d Iterate through the time domain and write the solution at each step.
    #      The Euler update method is: x[n+1] = x[n] + x'[n]*step_size
    #      At each step you will need to:
    #          - compute the variables
    #          - compute the rates
    #          - compute the state variables using the update method above
    #          - print to a file

    for step in range(0, step_count):
        time = step * step_size

        # Computing the rates at this step
        model.compute_rates(time, my_state_variables, my_rates, my_variables)
        row = "{}\t{}".format(step,time)

        # Computing the solution at the next step using Euler to advance
        for s in range(0, model.STATE_COUNT):
            my_state_variables[s] = my_state_variables[s] + my_rates[s] * step_size
            row += "\t{}".format(my_state_variables[s])

        # Update the variables
        model.compute_variables(time, my_state_variables, my_rates, my_variables)
        for s in range(0, model.VARIABLE_COUNT):
            row += "\t{}".format(my_variables[s])

        row+= "\n"
        write_file.write(row)

    write_file.close()

    # --------------------------------------------------------------------------
    #  STEP 5: Check the results

    #  5.a You can retrieve the solution from the file you've just closed and plot
    #      them in the program of your choice.

    #  5.b Go and have a cuppa, you're done!
    print("The results have been written to 'tutorial4_solution.txt'")
