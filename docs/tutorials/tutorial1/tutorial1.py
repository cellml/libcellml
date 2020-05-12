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
    #  1.a   Open the tutorial1.cellml file for reading.  This is currently in the
    #        resources folder.

    #  1.b   Create a libCellML Parser, and use it to parse the file
    #        string contents and convert it into a CellML Model structure

    # ---------------------------------------------------------------------------
    #  STEP 2:   Investigate the model we've just loaded and see what's inside it
    #
    #  2.a   Return the name and id of the new model, and print to the terminal.

    #  2.b   Return the number of components contained in the model, and print to the screen.

    #  2.c   Return the name and id of the first component and print them to the screen.

    #  2.d   Investigate the variables inside the component, and print their names to terminal.

    #  2.e   Investigate the maths which connects the variables in this component.  Note that
    #        maths in libCellML is stored as a single MathML2 string.

    # ---------------------------------------------------------------------------
    #  STEP 3: Print the model to another CellML file
    #
    #  3.a   Create a Printer and use it to serialise the model to a string.

    #  3.b   Write the serialised string to a file.

    #  3.c  Go and have a cuppa, you're done!
