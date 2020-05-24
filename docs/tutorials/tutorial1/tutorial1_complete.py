"""
  TUTORIAL 1: READING AND WRITING A CELLML FILE

   By the time you have worked through Tutorial 1 you will be able to:
     - Read the contents of a CellML file;
     - Deserialise its contents using the Parser to create a Model structure;
     - Investigate the hierarchical contents of the Model, including the
       Components, Variables, and MathML block; and
     - Serialise the model and write to another file.

"""

from libcellml import Parser, Printer

if __name__ == "__main__":

    print("-----------------------------------------------------")
    print("    TUTORIAL 1: READING AND WRITING CellML2 FILES    ")
    print("-----------------------------------------------------")

    # ----------------------------------------------------------------------------
    #  STEP 1:   Create a CellML Model from the contents of a CellML file
    #
    #  1.a   Open the tutorial1.cellml file for reading
    read_file = open("../resources/tutorial1.cellml", "r")

    #  1.b   Create a libCellML Parser, and use it to parse the file
    #        string contents and convert it into a CellML Model structure
    parser = Parser()
    model = parser.parseModel(read_file.read())

    # ---------------------------------------------------------------------------
    #  STEP 2:   Investigate the model we've just loaded and see what's inside it
    #
    #  2.a   Return the name and id of the new model, and print to the terminal.
    model_name = model.name()
    model_id = model.id()

    print("The model name is: " + model_name)
    print("The model id is: " + model_id)

    #  2.b   Return the number of components contained in the model, and print to the screen.
    number_of_components = model.componentCount()
    print("The '{m}' model has {n} component(s):".format(
        m=model_name,
        n=number_of_components)
    )

    #  2.c   Return the name and id of the first component and print them to the screen.
    component = model.component(0)
    component_name = component.name()
    component_id = component.id()
    print("  Component[0] has name: ", component_name)
    print("  Component[0] has id: ", component_id)

    #  2.d   Retrieve the number of variables in the component, and print to the screen.
    number_of_variables = component.variableCount()
    print("  The '{c}' component has {n} variable(s):".format(
        c=component_name,
        n=number_of_variables)
    )
    #  2.e   Loop through the variables in the component, and print their names to the terminal.
    for v in range(0, number_of_variables):
        print("    Variable[{v}] has name: {n}".format(v=v, n=component.variable(v).name()))

    #  2.f   Investigate the maths which connects the variables in this component.  Note that
    #        maths in libCellML is stored as a single MathML2 string.
    maths_string = component.math()
    print("  Component '{c}' has a MathML string of: ".format(c=component_name))
    print("		"+maths_string)

    # ---------------------------------------------------------------------------
    #  STEP 3: Print the model to another CellML file
    #
    #  3.a   Create a Printer and use it to serialise the model to a string.
    printer = Printer()
    serialised_model = printer.printModel(model)

    #  3.b   Write the serialised string to a file.
    write_file = open("tutorial1_printed.cellml", "w")
    write_file.write(serialised_model)
    print("The {} has been printed to tutorial1_printed.cellml".format(model_name))

    #  3.c  Go and have a cuppa, you're done!
