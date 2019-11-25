/**
 *  TUTORIAL 3: MODEL CREATION THROUGH THE API
 *
 *  By the time you have worked through Tutorial 3 you will be able to:
 *    - create a new model and its child entities from scratch using the API
 *    - define custom combinations of built-in units
 *    - define your own custom units independent from the built-in units
 *    - call the Generator to output code in languages other than CellML
 *
 *  This tutorial assumes that you are comfortable with:
 *    - accessing and adjusting names of items inside a model hierarchy (Tutorial 2)
 *    - creating a validator and using it to check a model for errors (Tutorial 2)
 *    - accessing the errors produced by a validator and using them to correct
 *      the model (Tutorial 2)
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

#include "../../utilities/tutorial_utilities.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   TUTORIAL 3: CREATE A MODEL USING THE API" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 1: Create the model instance
    //
    //  1.a   Allocate the ModelPtr
    //  TODO Need some more specific info on how to think about smart pointers
    //  here
    
    
    //  1.b   Create a component to use as an integrator, set its attributes and
    //        add it to the model

    //  1.c,d Create the MathML2 string representing the governing equation.  The
    //        header and footer are below already.

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

    //  1.e   Include the MathML strings in the component

    //  1.f   Create a validator and use it to check the model so far.

    //  1.g   Create some variables and add them to the component

    //  1.e   Assign units to the variables


    // ---------------------------------------------------------------------------
    //  STEP 2: Create the user-defined units
    //
    //  From the validation errors printed above you'll see that none of the three
    //  units we need are built-in. The good news is that we can create the ones
    //  we need from the set of built-in units, we just need to define the
    //  relationship.  NB: Even though units are used by Variables, which sit
    //  'inside' Components, Units sit inside the Model itself.  This helps you to
    //  reuse Units when you have more than one component (more on that in
    //  Tutorial 5)

    //  2.a  Define the relationship between our custom units and the built-in
    //       units. There is a list of built-in units and their definitions
    //       available in section 19.?? of the CellML2 specification.

    //  2.b  Add the units to the model

    //  2.c  Validate the model again and output the errors

    //  2.d  Change the constant "b" to have a hard-coded value of 2.0 in the MathML
    //       and amend the component's math block.

    //  2.e Create and define the constant "a" to have a value of 1.  Check that there
    //      are no more validation errors.

    // ---------------------------------------------------------------------------
    //  STEP 3: Output the model for solving
    //

    //  3.a Create a Generator instance and use it to process the model.  Output
    //      any errors to the terminal using the utility function printErrorsToTerminal
    //      called with your generator as argument.

    //  3.b Set the initial conditions of the distance variable such that x(t=0)=5 and
    //      check that there are no more errors reported.

    //  3.c Check that the generator has the settings which we expect:
    //      - the number of variables
    //      - the language of output
    //      - the variable of integration
    //      - the type of model

    //  3.d Create the interface code (*.h file contents) and implementation code (*.c file
    //      contents) and print them to files.

    //  3.e Go have a cuppa, you're done!
}