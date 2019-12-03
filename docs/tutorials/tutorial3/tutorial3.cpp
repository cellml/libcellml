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

/**
 *  TUTORIAL 3: MODEL CREATION THROUGH THE API
 *
 *  By the time you have worked through Tutorial 3 you will be able to:
 *    - create a new model and its child entities from scratch using the API
 *    - define custom combinations of built-in units
 *    - define your own custom units independent from the built-in units
 *
 *  This tutorial assumes that you are comfortable with:
 *    - accessing and adjusting names of items inside a model hierarchy (T2)
 *    - creating a validator and using it to check a model for errors (T2)
 *    - accessing the errors produced by a validator and using them to correct
 *      the model (T2)
 *    - serialising and printing a model to a CellML file (T1)
 */

/**
 *  TUTORIAL 3: MODEL CREATION AND GENERATION THROUGH THE API
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   TUTORIAL 3: CREATE A MODEL USING THE API" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 1: Create the model, component and maths
    //
    //  1.a   Create the Model and name it

    //  1.b   Create a Component, name it, and add it to the model

    //  1.c,d,e Create strings representing the governing equations in MathML2.
    //          The header and footer strings are provided for you below.
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

    //  1.g Assemble the entire MathML into the component

    //  1.h Call the validator and check for error so far.  We expect there to be 20 errors found,
    //      related to missing variables in the component.

    // ---------------------------------------------------------------------------
    //  STEP 2: Create the variables and add them to the component

    //  2.a Create the variables with names listed by the validator: d, a, b, c, time, y_s, y_f
    //      Note that the variables can have any symbol, but their names must match exactly those
    //      used in the MathML.

    //  2.b Add the variables into the component

    //  2.c Call the validator to check.  Expect errors related to missing units.

    // ---------------------------------------------------------------------------
    //  STEP 3: Create the Units and add them to the model

    //  3.a,b Create the day and per_day units

    //  3.c Create the sharks and fishes base units, "number_of_sharks" and "thousands_of_fish"

    //  3.d Create the combined units for the constants

    //  3.e Add the units to their variables

    //  3.f Call the validator to check the model.  We expect one error regarding the missing units in the MathML.

    //  3.g Units for constants inside the MathML must be specified inside MathML the time.  This means
    //      we need to adjust equation1 to include the per_day units.  Remove all the maths from the component,
    //      and replace with the correct version of equation1.

    //  3.h Call the validator to check.  Expect no errors.

    // ---------------------------------------------------------------------------
    //  STEP 4: Code generation

    //  4.a Create a generator instance and pass it the model for processing.  The
    //      default profile is to generate C code, but we can change this later.

    //  4.b Check for errors found in the generator.  Expect errors related to missing initial conditions.

    //  4.c Add initial conditions to all variables except the base variable, time
    //      and the constant c which will be computed.

    //  4.d Reprocess the model.

    //  4.e Because we've used the default profile (C) we need to output both the
    //      interfaceCode (the header file) and the implementationCode (source file)
    //      from the generator and write them.

    //  4.f Change the generator profile to Python

    //  4.g Retrieve the Python implementation code and write to a file

    //  4.h Go and have a cuppa, you're done!
}
