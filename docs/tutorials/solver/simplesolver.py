"""
    SIMPLE SOLVER for CellML models generated using the Python profile.

    This script uses Euler updates to solve a set of differential equations.

    Usage:
        python3 simplesolver.py:
            -m generated file to run
            -n number of steps to take
            -dt step size to use.

    The solution will be written to a tab-delimited text file in the same directory
    as the running file, with the extension _solution.txt added to the run file name.

"""

import sys
import importlib


def process_arguments(argv):

    if (len(argv) == 1):
        print("Usage:")
        print("   -m     generated file to run")
        print("   -n     the number of steps to take before stopping")
        print("   -dt    the step size to use")
        exit(0)

    arg_map = {}
    i = 0
    while i < len(argv):
        if argv[i][0] == '-':
            key = argv[i][1:]
            value = argv[i + 1]
            arg_map[key] = value
            i += 1
        else:
            i += 1

    # Cleaning up the inputs to save in the right form
    error_string = ''
    try:
        arg_map['m'][-3:] == ".py"
        arg_map['m'] = arg_map['m'][:-3]
    except:
        error_string += "/n - missing argument: -m file to run"

    try:
        arg_map['n'] = int(arg_map['n'])
    except:
        error_string += "/n - missing argument: -n number of steps to take"

    try:
        arg_map['dt'] = float(arg_map['dt'])
    except:
        error_string += "/n - missing argument: -dt step size"

    if error_string != "":
        print(error_string)
        exit(1)

    return arg_map


def module_from_file(input):

    # Shouldn't need to check this if the extension is stripped during input
    if input[-3:] != '.py':
        module_file = input + ".py"
        module_name = input.split("/")[-1]
    else:
        module_file = input
        module_name = ".".join(input.split("/")[-1].split(".")[:-1])

    spec = importlib.util.spec_from_file_location(module_name, module_file)
    module = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = module
    spec.loader.exec_module(module)
    return module


if __name__ == "__main__":
    args = process_arguments(sys.argv)
    model = module_from_file(args['m'])

    print("\n")
    print("\n")
    print("====================================================================")
    print("   SIMPLE SOLVER: {}".format(args['m']))
    print("--------------------------------------------------------------------")
    print("\n")
    print("   VARIABLE OF INTEGRATION (units, stepsize)")
    print("--------------------------------------------------------------------")
    print("      {} ({}, {})".format(model.VOI_INFO['name'],
                                     model.VOI_INFO['units'],
                                     args['dt']))
    print("      {} steps".format(args['n']))
    print("\n")
    print("   STATE VARIABLES (units, initial value)")
    print("--------------------------------------------------------------------")

    time = 0.0
    my_variables = model.create_variables_array()
    my_state_variables = model.create_states_array()
    my_rates = model.create_states_array()
    model.initialize_states_and_constants(my_state_variables, my_variables)
    model.compute_computed_constants(my_variables)
    model.compute_rates(0, my_state_variables, my_rates, my_variables)
    model.compute_variables(0, my_state_variables, my_rates, my_variables)

    for i in range(0, model.STATE_COUNT):
        print("      {} ({}, {})".format(model.STATE_INFO[i]['name'],
                                         model.STATE_INFO[i]['units'],
                                         my_state_variables[i]))

    print("\n")
    print("   VARIABLES (units, initial value)")
    print("--------------------------------------------------------------------")

    for v in range(0, model.VARIABLE_COUNT):
        print("      {} ({}, {})".format(model.VARIABLE_INFO[v]['name'],
                                         model.VARIABLE_INFO[v]['units'],
                                         my_variables[v]))

    # Writing the column headers to the output file
    row = "iteration\t{}({})".format(
        model.VOI_INFO['name'], model.VOI_INFO['units'])
    for s in range(0, model.STATE_COUNT):
        row += "\t{}({})".format(model.STATE_INFO[s]
                                 ['name'], model.STATE_INFO[s]['units'])
    for s in range(0, model.VARIABLE_COUNT):
        row += "\t{}({})".format(model.VARIABLE_INFO[s]
                                 ['name'], model.VARIABLE_INFO[s]['units'])
    row += "\n"

    write_file_name = "{}_solution.txt".format(args['m'])
    write_file = open(write_file_name, "w")
    write_file.write(row)

    # Stepping through the Euler steps to solve
    for step in range(0, args['n']):
        time = step * args['dt']

        model.compute_rates(time, my_state_variables, my_rates, my_variables)

        row = "{}\t{}".format(step, time)
        for s in range(0, model.STATE_COUNT):
            my_state_variables[s] = my_state_variables[s] + \
                my_rates[s] * args['dt']
            row += "\t{}".format(my_state_variables[s])

        model.compute_variables(
            time, my_state_variables, my_rates, my_variables)

        for s in range(0, model.VARIABLE_COUNT):
            row += "\t{}".format(my_variables[s])

        row += "\n"
        write_file.write(row)

    write_file.close()

    print("\n")
    print("   SOLUTION written to {}".format(write_file_name))
    print("====================================================================")
    print("\n")
    print("\n")
