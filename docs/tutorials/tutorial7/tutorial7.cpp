/**
 *  TUTORIAL 7: Creating the Sodium Channel
 *  By the time you have finished this tutorial you will be able to:
 *      - Use the import functionality to use components from other models; and
 *      - Use model flattening to resolve imported components for code generation.
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
    std::cout << " STEP 1: Create the sodium channel" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    //  1.a Create a model and name it appropriately.

    //  1.b Create a component instance for the sodium channel, name it, and add to the model.

    //  1.c Add the MathML representing the governing equations to the component, and validate the model.

    //  1.d Add the variables required by the validator.

    //  1.e Add the units as required by the validator.

    //  1.f Link the model's units and use the validator to make sure that there
    //      are no more errors in the model.

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Creating the m-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a Create component to represent the m-gate and add it to the sodium channel component.

    //  2.b Add the MathML strings which govern the behaviour of this gate.

    //  2.c Call the validator and expect errors related to missing variables.
    //      Add the variables that are needed.

    //  2.d Call the validator to check the model - expect errors related to
    //      units missing from the model. Add the units that are required.

    //  2.e Link in the units to the model, and check that there are no more
    //      validation errors in the model.

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << " STEP 3: Create the h-gate component " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a Create the hGate component and add it to the sodium channel component.

    //  3.b Add the MathML strings that govern the gate behaviour.

    //  3.c Call the validator to list missing variables.  Add them as needed.

    //  3.d Recheck the model, and expect it to be free of errors.

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 4: Import the controller " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 4: When a Component (or Units) item is imported it needs:
    //          - to be connected to an ImportSource item
    //              - which in turn stores the url of the source file to be opened
    //          - the name of the item in the source file to be retrieved
    //          - a destination component (or units) item in which to store the
    //            imported information

    //  4.a Create a pointer to an ImportSource item using the create() idiom.

    //  4.b Use the ImportSource::setUrl() function to pass the file name containing the controller.
    //      In this case we'll use "tutorial7_controller.cellml".

    //  4.c Create the destination component into which the imported component
    //      will be saved, and name it as usual.  This will be the controller component, and will be at the
    //      top level of the model's encapsulation hierarchy.

    //  4.d Call the Component::setSourceComponent(ImportSource, std::string) function to
    //      associate the destination controller component with the importer, and
    //      the importer with the name of the item to retrieve.  If you're using the
    //      file from the resources folder, the name of the component to import is "sodiumChannel_controller".

    //  4.e Validate the model, expecting it to be free of errors.  Note that the validator does not check
    //      the contents of imports - this is done at the time that they're resolved (see step 5.c below).

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 5: Import the initial conditions " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 5: Import the initial conditions
    //      Similar to the way in which we imported the controller for the independent variables,
    //      we can also import components to initialise the values within the sodium channel and its
    //      gating components.  This procedure is the same as for the controller in Step 4,
    //      the only difference being that the initialising components should be siblings or
    //      children of the components to which they give values.
    //
    //      In this example the initialising components exist in the tutorial6_controller.cellml
    //      file, so we can reuse the importer from Step 4.b, and simply repeat steps 4.c-e to
    //      initalise the variables in the sodiumChannel and nGate components.  The items
    //      to retrieve are called "potassiumChannel_initialiser" and "nGate_initialiser" respectively.

    //  5.a Repeat steps 4.c-e for both the potassiumChannel and nGate components, and add the
    //      new components as children of the components they initialise.

    //  5.b At this stage our model can be written to a CellML file.  As the model
    //      contains import statements, the serialised and printed model would also maintain those
    //      same dependencies, and would need to exist alongside the tutorial7_controller.cellml
    //      file specified earlier.  In later steps we'll disconnect this dependency to allow for
    //      the code generation step.
    //
    //      Check that the model is valid, then create a Printer, and use it to serialise the model.
    //      Write the serialised model to a file.

    //  5.c Now that all the imports are specified, we need to first resolve them with respect to a
    //      directory location.  This location is either specified with an absolute path, or
    //      relative to the current working directory.
    //      Call the Model::resolveImports(directoryPath) function to resolve the imports.  Check that
    //      it has worked as expected by checking that Model::hasUnresolvedImports() returns false.
    //      Note that:
    //          - The argument of the resolveImports() function is the directory path.
    //          - For files in the same directory, use a blank string, "".

    //  5.d Finally it's time to flatten the model so that it can be used to generate runable code.
    //      This operation will create new local instances of all of the imported items, thereby
    //      removing the model's dependency on imports. Use the Model::flatten() function to do this.
    //      Print the model to the terminal and check that it makes sense.

    //  5.e After flattening a model it's important to note that the model itself has been completely overwritten
    //      with its "flat" version.  This means that any imported items which you'd previously assigned to pointers
    //      (such as the components defined as destinations for the imports: the controller and initialising components)
    //      have become obsolete.
    //      The easiest thing to do is to refresh their pointers by fetching them from the flattened model.
    //      You can do this using their "destination" name, eg: controller = model->component("controller"); etc.

    //  5.f Once you've refreshed the component pointers, add in all of the necessary variable equivalences.
    //      These are listed in the tutorial instructions.

    //  5.g Validate the model and expect messages related to unspecified interfaces.  Add these to the
    //      variables according to the recommendations.

    //  5.h Link the units and validate the model a final time.  Expect no errors.

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 6: Generate and output the model " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  6.a Create a Generator instance and submit the model for processing.
    //      Expect no errors.

    //  6.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.

    //  6.c Change the generator profile to Python and reprocess the model.

    //  6.d Retrieve and write the implementation code (*.py) to a file.

    //  6.e Please seen the tutorial instructions for how to run this simulation using
    //      the simple solver provided.  Then go and have a cuppa, you're done!
}
