/**
 *  TUTORIAL 7: Creating the Sodium Channel
 * 
 * This tutorial is in two parts.  The first demonstrates how to create a model in
 * which the use of importing functionality is specified; and the second demonstrates
 * how to resolve those imports ready for flattening.
 * 
 *  By the time you have finished this tutorial you will be able to:
 *      - Specify import functionality for models you create; 
 *      - Use the import functionality to retrieve items from other models; and
 *      - Use model flattening to resolve imported components ready for code generation.
 *
 *  Tutorial 7 assumes that you are already comfortable with:
 *      - The concept of component hierarchy and encapsulation (Tutorial 6);
 *      - The use of the API to create all of the entities in a model (Tutorial 3);
 *      - The content MathML2 markup for mathematical equations (Tutorial 3);
 *      - Serialisation and printing of a model to a CellML file (Tutorial 1); and
 *      - Model generation and simulation (Tutorial 3, 4).
 */

#include <iostream>
#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main()
{
    // Setup: Create useful things that are used throughout the code.
    auto validator = libcellml::Validator::create();
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n";
    std::string mathFooter = "</math>";

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 1: Create the sodium channel component" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    //  1.a Create a model and name it appropriately.

    //  1.b Create a component instance for the sodium channel, name it, and add to the model.

    //  1.c Add the MathML representing the governing equations to the component, and validate the model.

    //  1.d Add the variables required by the validator.

    //  1.e Add the units as required by the validator.

    //  1.f Link the model's units and use the validator to make sure that there
    //      are no more errors in the model.

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 2: Specify the imported component 'mGate'" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    //  2.a Create a component representing the mGate, name it appropriately, and
    //      add it as a child of the sodium channel component.

    //  2.b Create an ImportSource item and attach it to the component.  This indicates
    //      that the component's contents will be imported from another model.

    //  2.c Set the URL of the ImportSource to the location at which the other model
    //      can be found.  This can be absolute, or relative to the current model's location.
    //      For this example, use the file in the resources folder named "tutorial7_mGate.cellml".

    //  2.d Set the component's import reference to be the name of the component in the
    //      other model whose contents will be imported into this one.  For this example, use "mGate".

    // Specifying imports in this way does not create anything in the model itself, it just
    // saves a set of instructions for how to create those components (or units) later on.
    // The process of verifying that the instructions work is called "resolving" the imports,
    // and the process of actually creating the imported items in this model is called "flattening"
    // the model.
    // Because it's easier to work with unflattened models later on (if you want to
    // vary their ingredients etc), you will probably find that you need to connect imported
    // components to local ones, or to other imported ones before the model is flattened.
    // This creates a problem as the variables in those imported components can't yet
    // be referenced: they don't exist yet in this model.
    // The way around this is to create "dummy" variables in the imported component
    // placeholders you created.  Note that these need to have the same names as the variables
    // in the import, and will be over-written by the "real" ones when the model is flattened.
    // Because they will be over-written, you only need to specify their names and nothing else.

    //  2.e Create dummy variables representing time "t", voltage "V", and gate status "m" and
    //      add to this component.

    //  2.f Add variable equivalences between the dummy variables you just created and their counterparts
    //      in the sodium channel component.

    //  2.g Submit to the validator for checking.  Expect errors related to the interface types on the
    //      variables you have just created equivalences for.

    //  2.h Fix the interface types for the sodium channel variables by setting them to "public_and_private".

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 3: Specify the imported component 'hGate'" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    // Step 3: Repeat the steps within Step 2 for the hGate component, and include it as a child of the
    // sodium channel component.
    //  - It is defined inside the file called "tutorial7_hGate.cellml" in the resources folder.
    //  - Import the component reference "hGate" from that file.
    //  - You will need to create and link dummy variables named "h", "V", and "t".
    //  - You will need to set the sodium channel variable "h" to have an interface type "public_and_private".

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << " STEP 4: Specify the imported component 'controller'" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    
    // Step 4: Repeat the steps within Step 2 for the controller component, and include it as a child of the
    // model.
    //  - It is defined inside the file called "tutorial7_controller.cellml" in the resources folder;
    //  - Import the component reference "controller" from that file.
    //  - You will need to create and link dummy variables named "V" and "t".
    //  - You will need to set the sodium channel variables to have an interface type "public_and_private".

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << " STEP 5: Specify the imported component 'parameters'" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    // Step 5: Repeat the steps within Step 2 for the parameters component, and include it
    // as a child of the model. Note that since this step will access the same file as was used in Step 4
    // ("tutorial7_controller.cellml" in the resources folder), you can simply reuse the same ImportSource
    // item you created there for this component.
    //  - Import the component reference "parameters" from that file.
    //  - You will need to create and link dummy variables named "m", "h", "g_Na", and "E_Na".
    //  - You will need to set the corresponding sodium channel variables to have an interface type "public".

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 6: Serialise and output the model" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    // Step 6: Tidy and output the model.

    // 6.a  Even though it won't be used in this tutorial, we need to set the interface types on any variable
    //      in the sodium channel component that will need to be accessible to other components later.  It's
    //      worth thinking about these at the time of writing the component, as it increases its reusability
    //      and usefulness later on.  In this case, we'll only need to set the i_Na sodium current variable
    //      to have a public interface.

    //  6.b At this stage our model can be written to a CellML file.  As the model
    //      contains import statements, the serialised and printed model would also maintain those
    //      same dependencies, and would need to exist alongside the tutorial7_controller.cellml
    //      file specified earlier.  In later steps we'll disconnect this dependency to allow for
    //      the code generation step.
    //
    //      Check that the model is valid, then create a Printer, and use it to serialise the model.
    //      Write the serialised model to a file.
}
