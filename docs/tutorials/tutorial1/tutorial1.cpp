/**
 *  TUTORIAL 1: READING AND WRITING A CELLML FILE
 *
 *  By the time you have worked through Tutorial 1 you will be able to:
 *    - read the contents of a CellML file;
 *    - deserialise its contents using the Parser to create a Model structure;
 *    - investigate the hierarchical contents of the Model, including the
 *      Components, Variables, and maths; and
 *    - serialise the model and write to another file.
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

int main() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << " TUTORIAL 1: READING AND WRITING CELLML FILES" << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  // ----------------------------------------------------------------------------
  //  STEP 1:   Create a CellML Model from the contents of a CellML file
  //
  //  1.a   Open the file and read its contents into a buffer stream

  //  1.b   Create a libCellML Parser, and use it to parse the fileContents
  //        string and convert it into a CellML Model structure

  // ---------------------------------------------------------------------------
  //  STEP 2:   Investigate the model we've just loaded and see what's inside it
  //
  //  2.a   Return the name and id of the new model, and print to the terminal

  //  2.b   Return the number of components contained in the model, and print
  //        to the screen

  //  2.c   Return the name and id of the first component and print them to 
  //        the screen.

  //  2.d   Investigate the variables inside the component, and print their
  //        names to terminal

  //  2.e   Investigate the maths which connects the variables in this
  //        component.  Note that maths in libCellML is stored as a
  //        single MathML2 string.

  // ---------------------------------------------------------------------------
  //  STEP 3: Print the model to another CellML file
  //  3.a   Create a Printer and use it to serialise the model to a string

  //  3.b   Write the serialised string to a file

  // ---------------------------------------------------------------------------
  //  STEP 4: Go and have a cuppa, you're done!
}