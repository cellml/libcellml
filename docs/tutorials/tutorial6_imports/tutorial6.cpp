/**
 *      TUTORIAL 6: POTASSIUM CHANNEL MODEL
 *
 *  This tutorial explores the ability of CellML to represent more than one
 *  modelled process at a time using components with connections between them.
 *  By the time you have worked through Tutorial 6 you will be able to:
 *      - assemble a multi-component model using the API
 *      - inter-connect the components using the equivalent variables
 *        functionality
 *      - import a Component or Units item from an existing CellML file
 *
 *  Tutorial 6 assumes that you are already comfortable with:
 *      - file manipulation and summarising using the utility functions
 *      - model creation through the API (Tutorial 3)
 *      - debugging the model using the Validator functionality (Tutorial 2)
 *      - model generation using the Generator (Tutorial 3)
 */

#include <iostream>
#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main()
{
    //  0.a Setup useful things
    auto validator = libcellml::Validator::create();
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n";
    std::string mathFooter = "</math>";

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 1: Define the potassiumChannel component " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 1: Define the potassiumChannel component
    //      As in the previous Tutorial 5, we define an ion channel, but this time make it
    //      specific to potassium.  We also introduce voltage dependence into the alpha and
    //      beta gate rates, and move them into a separate component to make it cleaner.
    //      This separate component is the nGate component, and will be defined in Step 2.

    //  1.a Create a model and add to it a new potassiumChannel component.

    //  1.b Define the maths inside the potassiumChannel component.  You might like to use
    //      braces {} to limit the scope of your definition.

    //  1.c Call the validator and expect it to report errors related to missing variables and units.

    //  1.d Create the variables needed and add them to the potassium channel component.  Again, braces
    //      here will help you to use variables with intuititive names.

    //  1.e Check for errors.  Expect warnings about the undefined units in the maths and in the
    //      new variables added.

    //  1.f Add the missing units.  Verify that the model is now free of validation errors.
    //
    //  NOTE: If, even after adding the Units the validator continues to return an error, you
    //      need to call the Model::linkUnits() function to link the units.  Unlinked units
    //      can occur when variables call their setUnits() function with
    //      a string argument of the Units' name, rather than the Units item itself.

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 2: Create the nGate component  " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 2: Create the nGate component
    //      This model differs from the one in Tutorial 5 in that voltage dependence is
    //      introduced into the opening and closing rates.  This dependence is handled in
    //      a separate component, the nGate component, which you'll define here.

    //  2.a Create an nGate component, and add it to the potassiumChannel component (not the model)
    //      Adding it to the component creates an encapsulation hierarchy, which affects which components
    //      have access to each other.  It also means that if the potassiumChannel component is
    //      moved or imported, the nGate child component will be included too.

    //  2.b Add the mathematics to the nGate component and validate the model.
    //      Expect errors relating to missing variables.

    //  2.c Add the missing variables to the nGate component, link the units, and validate again.
    //      Expect errors relating to missing units.

    //  2.d Create the missing units and add them to the model.  Link the model's
    //      units and validate again.  Expect the model to be free of errros.

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 3: Connect the components together " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 3: Connect the components together.
    //      In order for the voltage dependence of the alpha and beta rates within
    //      the nGate component to affect the current in the potassiumChannel component
    //      some of the variables need to share their values between the components.
    //      This is done using variable equivalence and interfaces.

    //  3.a Set the equivalent variable pairs between the nGate and potassiumChannel components.
    //      These are:
    //          - voltage, V
    //          - time, t
    //          - gate status, n
    //      Use the Variable::addEquivalence(VariablePtr, VariablePtr) function.

    // ** TODO This should return a validation error saying that the interfaces are not specified **

    //  3.b Set the appropriate interface types on all the shared variables.  Note that if you used
    //  the braces {} earlier to limit scope, you can still access the variables using their name
    //  and parent component.

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 4: Import the controller " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 4: The controller is a component sitting outside the current model in a separate
    //      file.  This allows for it to be more easily interchangable between runs and stimulus
    //      conditions.  We introduce the import functionality here for that purpose.
    //      When a Component (or Units) item is imported it needs:
    //          - to be connected to an ImportSource item
    //            - which in turn stores the url of the source file to be opened
    //          - the name of the item in the source file to be retrieved
    //          - a destination component (or units) item in which to store the
    //            imported information

    //  4.a Create a pointer to an ImportSource item using the create() idiom.
    auto importer = libcellml::ImportSource::create();

    //  4.b Use the ImportSource::setUrl() function to pass the file name containing the controller.
    importer->setUrl("tutorial6_controller.cellml");

    //  4.c Create the destination component into which the imported component
    //      will be saved, and name it.  This will be the controller component.
    auto controller = libcellml::Component::create("controller");

    //  4.d Call the Component::setSourceComponent(ImportSource, std::string) function to
    //      associate the destination controller component with the importer, and
    //      the importer with the name of the item to retrieve.  If you're using the
    //      file from the resources folder, the name of the component to import is "potassiumChannel_controller".
    controller->setSourceComponent(importer, "potassiumChannel_controller");

    //  4.e Add the controller component to the model in the normal way.


    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 5: Import the initial conditions " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  STEP 5: Import the initial conditions
    //      Similar to the way in which we imported the controller for the independent variables,
    //      we can also import components to initialise the values within the potassiumChannel
    //      and nGate components.  This procedure is the same as for the controller in Step 4,
    //      the only difference being that the initialising components should be siblings or
    //      children of the components to which they give values.
    //
    //      In this example the initialising components exist in the tutorial6_controller.cellml
    //      file, so we can reuse the importer from Step 4.b, and simply repeat steps 4.c-e to
    //      initalise the variables in the potassiumChannel and nGate components.  The items
    //      to retrieve are called "potassiumChannel_initialiser" and "nGate_initialiser" respectively.

    //  5.a Repeat steps 4.c-e for both the potassiumChannel and nGate components, and add the
    //      new components as children of the components they initialise.

    //  5.b At this stage our model could be written to a CellML file.  As the model
    //      contains import statements, the serialised and printed model would also maintain those
    //      same dependencies, and would need to exist alongside the tutorial6_controller.cellml
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

    //  5.d Finally it's time to flatten the model.  This operation will create new local instances of all
    //      of the imported items, and remove their dependency on imports. Use the Model::flatten() function
    //      to do this.

    //  5.e After flattening it's important to note that any imported items (such as the components
    //      potassiumChannelInit, nGateInit, and controller) now exist within the model slightly differently.
    //      The easiest thing to do is to refresh their pointers by fetching the components from the flattened model.
    //      You can do this using their "destination" name, eg: controller = model->component("controller"); etc.

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 6: Generate the model " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    // TODO It would be better to do the checking currently in the Generator outside it ...
    //      This is coming (soon?) see https://github.com/cellml/libcellml/issues/499

    //  6.a Create a Generator instance and pass it the model for processing.  Check for errors and
    //      print them to the terminal.  We expect to see errors reporting that some variables are not
    //      computed or not initialised.

    //  6.b The Generator needs variables to have values or to be computed.  The initial values
    //      for all the variables in the model are stored in the controller and initialisation components, so we
    //      need to connect these together, just as in step 3.a, using the Variable::addEquivalence function.

    //  6.c We also need to specify the interface types for these variable equivalnences.

    //  6.d Pass the model back to the generator for re-processing, and check that now there are no more errors.


    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "   STEP 7: Output the final generated model " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    //  7.a Write the interface code to a .h file

    //  7.b Write the implementation code to a .c file

    //  7.c Change the profile to Python and reprocess the model

    //  7.d Write the Python implementation code to a .py file

    //  7.e Serialise the model using a Printer and write to a CellML file.

    //  7.f Please see the instructions in the tutorial for how to run a
    //      simulation of this model using the simple solver provided.
    //      Then go and have a cuppa, you're done!
}
