"""
    TUTORIAL 2: ERROR CHECKING AND VALIDATION

    By the time you have worked through Tutorial 2 you will be able to:
        - Use the Parser to report errors enountered when reading a file
          or deserialising a string; and
        - Use the Validator to check for errors related to a model's
          description as compared to the CellML2.0 specifications.

    This tutorial assumes that you can already:
    - Read and deserialise a CellML model from a file;
    - Retrieve the name and id of models, components, and variables;
    - Navigate through the hierarchy of the model (model contains
      component(s) contain(s) variable(s) and maths); and
    - Serialise and print a Model structure to a CellML file.
"""

from libcellml import Parser, Printer, Validator

from tutorial_utilities import print_model_to_terminal

if __name__ == "__main__":
    print("------------------------------------------------------------")
    print("     TUTORIAL 2: Debugging, error checking and validation   ")
    print("------------------------------------------------------------")

    # ---------------------------------------------------------------------------
    #  STEP 1:  Create the model
    print("-----------------------------------------------")
    print("       Step 1: Print the parsed model          ")
    print("-----------------------------------------------")
    #  1.a  Create a CellML Model from the contents of a CellML file.  You will
    #       need to create a Parser and then pass it the file contents to read,
    #       as you did in Tutorial 1.
    read_file = open("../resources/tutorial2.cellml", "r")
    parser = Parser()
    model = parser.parseModel(read_file.read())

    #  1.b  Print the contents of the model to the terminal so that we can read
    #       it more easily. This step makes use of a function in the
    #       'tutorial_utilities.py' file called "print_model_to_terminal".
    print_model_to_terminal(model)

    # ---------------------------------------------------------------------------
    #  STEP 2: Check that the model meets the CellML2.0 specifications using the Validator.
    #
    #  2.a   Create a Validator and pass the model into it
    print("-----------------------------------------------")
    print("       Step 2: Validate the parsed model")
    print("-----------------------------------------------")
    validator = Validator()
    validator.validateModel(model)

    #  2.b  Check whether there were errors returned from the validator.
    number_of_validation_errors = validator.errorCount()

    if number_of_validation_errors != 0:
        print("The validator has found {n} errors!".format(n=number_of_validation_errors))

        # 2.c  Retrieve the errors, and print their description and specification reference to the terminal.
        for e in range(0, number_of_validation_errors):
            validator_error = validator.error(e)

            specification_heading = validator_error.referenceHeading()

            print("  Validator error[{e}]: ".format(e=e))
            print("     Description: " + validator_error.description())

            if specification_heading != "":
                print("    See section {r} in the CellML specification.".format(r=specification_heading))

    # ---------------------------------------------------------------------------
    #  STEP 3:   Fix the errors that were reported in Step 2
    #
    print("-----------------------------------------------")
    print("       Step 3: Fix the parsed model")
    print("-----------------------------------------------")

    # 3.a
    #   Validator error[0]:
    #       Description: CellML identifiers must not begin with a European numeric
    #       character [0-9].
    #       See section 3.1.4 in the CellML specification.
    #   Validator error[1]:
    #       Description: Variable does not have a valid name attribute.
    #       See section 11.1.1.1 in the CellML specification.
    #
    # These errors refer to the same thing, but are better read in reverse order.
    # Variables (and everything else in CellML) which specify a name attribute
    # can must have the correct format.  Comparing the error to the names of
    # entities printed in the terminal we can see that variable[0] in
    # component[0] doesn't have a valid name, so let's fix it.
    model.component(0).variable(0).setName("a")

    # 3.b
    #   Validator error[2]:
    #       Description: Variable 'b' has an invalid units reference 'i_am_not_a_unit'
    #       that does not correspond with a standard unit or units in the variable's
    #       parent component or model.
    #       See section 11.1.1.2 in the CellML specification.
    #
    #  Variables must have a unit defined.  These can be either something from
    #  the built-in list within libCellML (which you can read in the
    #  specifications document), or something you define yourself.  We'll look at
    #  user defined units in Tutorial 3, but for now it's enough to see that the
    #  units which are associated with variable 'b' is not valid.  We'll change
    #  it to be 'dimensionless' instead.  NB items can be accessed through their
    #  name (as here) or their index (as above).
    model.component("i_am_a_component").variable("b").setUnits("dimensionless")

    # 3.c
    #   Validator error[3]:
    #       Description: Variable 'c' has an invalid initial value
    #       'this_variable_doesnt_exist'. Initial values must be a real number
    #       string or a variable reference.
    #       See section 11.1.2.2 in the CellML specification.
    #
    #  We can either access members by their index or their name, as shown above,
    #  or we can create a pointer to them instead. Initial values (if set) must
    #  be a valid variable name in the same component, or a real number.

    variableC = model.component(0).variable("c")
    variableC.setInitialValue(20.0)

    # 3.d
    #   Validator error[4]:
    #       Description: CellML identifiers must contain one or more basic Latin
    #       alphabetic characters.
    #       See section 3.1.3 in the CellML specification.
    #   Validator error[5]:
    #       Description: Variable 'd' does not have a valid units attribute.
    #       See section 11.1.1.2 in the CellML specification.
    #
    #  These two errors go together too.  Because we haven't defined a units
    #  attribute for variable 'd', it effectively has a blank name, which is not
    #  allowed.  Simply assigning a unit to the variable will fix both errors.

    variableD = model.component(0).variable("d")
    variableD.setUnits("dimensionless")

    # 3.e
    #   Validator error[6]:
    #       Description: MathML ci element has the child text 'a' which does not
    #       correspond with any variable names present in component
    #       'i_am_a_component' and is not a variable defined within a bvar element.
    #
    #  The maths block is complaining that it is being asked to compute:
    #    a = b + c
    #  but in the component there was no variable called 'a'.  Since we
    #  corrected this earlier by naming the first variable in component[0] as 'a'
    #  this error will be fixed already.

    # ---------------------------------------------------------------------------
    #  STEP 4:   Check our changes.
    print("-----------------------------------------------")
    print("       Step 4: Check the corrected model")
    print("-----------------------------------------------")

    #   4.a Print the corrected model to the terminal.
    print_model_to_terminal(model)

    #   4.b Validate that the corrected model is now free of errors.
    validator.validateModel(model)
    number_of_validation_errors = validator.errorCount()
    print("The validator found {n} errors in the model.".format(n=number_of_validation_errors))

    # ---------------------------------------------------------------------------
    #  STEP 5:   Print the corrected model to a file.
    print("-----------------------------------------------")
    print("       Step 5: Output the corrected model")
    print("-----------------------------------------------")

    #   5.a Create a printer instance, and use it to serialise your model into a string.
    printer = Printer()
    serialised_model = printer.printModel(model)

    #   5.b Write the serialised string to a file.
    write_file = open("tutorial2_printed.cellml", "w")
    write_file.write(serialised_model)
    print("The {} has been printed to tutorial2_printed.cellml".format(model.name()))

    #   5.c Go and have a cuppa, you're done!
