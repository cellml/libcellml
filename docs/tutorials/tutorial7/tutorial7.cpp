/**
 *      TUTORIAL 7: Creating the Sodium Channel
 *  This tutorial is an opportunity to practise creating models from
 *  scratch using the libCellML API.  The model you create here will
 *  be used later on in Tutorial ??.
 *
 *  Tutorial 7 assumes that you are already comfortable with:
 *    - the concept of component hierarchy and encapsulation (Tutorial 5)
 *    - the use of the API to create all of the entities in a model (Tutorial 3)
 *    - the content MathML2 markup for mathematical equations (Tutorial 4)
 *    - serialisation and printing of a model to a CellML file (Tutorial 1)
 */

#include <iostream>
#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main()
{
    //  0 Setup stuff that is used throughout
    auto validator = libcellml::Validator::create();

    auto model = libcellml::Model::create();
    model->setName("Tutorial7_SodiumChannelModel");

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 1: Creating the sodium channel" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a Create the compont instance, name it, and add to the model

    //  1.b Add the MathML representing the governing equations

    //  1.c Add the variables

    //  1.d Add the units

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Creating the m-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a Create the component and add it to the sodium channel component

    //  2.b Add the MathML strings which govern the behavior of this gate

    //  2.c Call the validator - expect errors related to missing variables. Then
    //      go ahead and add the variables needed

    //  2.d Call the validator to check the model - expect errors related to
    //      units missing from the model.  Add them in as needed.


    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Creating the h-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a Create the hGate component and add it to the sodium channel component

    //  3.b Adding the MathML strings for this component

    //  3.c Adding the variables for this component

    //  3.d Add the missing units

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Creating the environment component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  4.a Creating the new environment component

    //  4.b Add variables to the component.

    //  4.c Add the new component to the model and validate

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Connecting variables and components" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  5.a Connecting the equivalent variables between all the components

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "       STEP 6: Set the driving function" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  6.a Create the MathML controlling the driving function

    //  6.b Validate the final model

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 7: Serialse and print the model " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;


}
