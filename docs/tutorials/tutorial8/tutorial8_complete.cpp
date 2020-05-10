/**
 *      TUTORIAL 8: IMPORTS and FLATTENING
 *
 *
 */

#include <iostream>
#include <libcellml>
#include <regex>

#include "../utilities/tutorial_utilities.h"

int main()
{
    //  0.a Create a new model instance representing the combined model and name it.
    auto model = libcellml::Model::create("Tutorial8_HHModel");
    auto validator = libcellml::Validator::create();

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 1: Import the membrane component          " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  In order to use the import functionality we need to know three things:
    //      - the import destination (the component/unit to which the imported item will be assigned)
    //      - the file we're importing it from (the url to the model containing the item to be imported)
    //      - which item within the file should be imported (the name of the component/units inside the import model file)
    //  We'll address these now.

    //  1.a As previously, create a component to represent the membrane in the HH model,
    //      and add it to the model.  This deals with the first point above: the import destination
    auto membrane = libcellml::Component::create("membrane");
    model->addComponent(membrane);

    //  1.b Next we need to create an ImportSource item and use its setUrl() function to specify the
    //      name (without the path) of the file contianing the model to be imported.
    auto membraneImporter = libcellml::ImportSource::create();
    membraneImporter->setUrl("tutorial8_MembraneModel.cellml");

    //  1.c Thirdly we need to link our import source to the import destination using the
    //      Component::setImportSource() function on the membrane component, and to use the
    //      Component::setImportReference() function to specify the name of the component inside
    //      the import model to retrieve.
    membrane->setImportSource(membraneImporter);
    membrane->setImportReference("membrane_for_importing");

    //  1.d At this stage, our model has only one component in it, and even though we've specified the
    //      imports completely, we still need to resolve the imports and flatten the model before the
    //      imported items will be instantiated here.
    //      Use the Model::hasUnresolvedImports() function to show that the imports have not been resolved yet.

    if (model->hasUnresolvedImports()) {
        std::cout << "Imports are UNRESOLVED" << std::endl;
    } else {
        std::cout << "Imports are found" << std::endl;
    }

    //  1.e Print the model to the terminal to show that it contains only one empty component at this stage.
    printModelToTerminal(model, false);

    //  1.f Use the Model::resolveImports() function of the model to (erm) resolve the imports.  This takes an
    //      argument of a string representing the full absolute path to the directory in which the import
    //      file specified in 1.b is stored, and must end with a slash.
    model->resolveImports("");

    //  1.g Call the Model::hasUnreolvedImports() function again and verify that they are now resolved.
    if (model->hasUnresolvedImports()) {
        std::cout << "Imports are UNRESOLVED" << std::endl;
    } else {
        std::cout << "Imports are found" << std::endl;
    }

    //  1.h Call the Model::flatten() function.  This will recursively search through all of the imported items
    //      in the model, and create local instances of them here.
    //      Note that:
    //          - if you call the flatten() function without first resolving the imports, nothing will change.
    //          - flattening a model fundamentally changes it ... and cannot be undone.
    model->flatten();
    membrane = model->component("membrane");

    //  1.i Print the flattened model to the terminal and verify that it now contains:
    //      - 4 units
    //      - 1 component with
    //          - 8 variables
    //          - a mathml block
    //  from the imported file.
    printModelToTerminal(model, false);

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Import the sodium channel component    " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  2.a Create a component representing the sodium channel.  This will be encapsulated inside the membrane
    //      component, so add it there instead of adding it to the model.
    auto sodiumChannel = libcellml::Component::create("sodium_channel");
    membrane->addComponent(sodiumChannel);

    //  2.b Create an importer for the sodium channel, and point it to the file you created in Tutorial 7.
    //      Note that you will need to make sure it exists in the same path as the earlier files.
    //      If you did not complete Tutorial 7 you can use the tutorial7_SodiumChannelModel.cellml
    //      file in the resources folder.
    auto sodiumImporter = libcellml::ImportSource::create();
    sodiumImporter->setUrl("tutorial7_SodiumChannelModel.cellml");

    //  2.c Link the sodium channel component to the importer and set the reference to import.
    //      In the file provided this is named "sodiumChannel".  You will need to change this to
    //      whatever you named the component in Tutorial 7.
    sodiumChannel->setImportSource(sodiumImporter);
    sodiumChannel->setImportReference("sodiumChannel");

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Import the potassium channel component  " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  3.a Repeat all the tasks in Step 2, this time for the potassium channel model you created in
    //      Tutorial 6.  If you did not complete Tutorial 6 you can use the tutorial6_PotassiumChannelModel.cellml
    //      from the resources folder, importing the component called "potassiumChannel"
    auto potassiumChannel = libcellml::Component::create("potassium_channel");
    membrane->addComponent(potassiumChannel);

    auto potassiumImporter = libcellml::ImportSource::create();
    potassiumImporter->setUrl("tutorial6_PotassiumChannelModel.cellml");

    potassiumChannel->setImportSource(potassiumImporter);
    potassiumChannel->setImportReference("potassiumChannel");

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Import the leakage component           " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  4.a Repeat all the tasks in Step 2, this time for the leakageCurrent component in
    //      the model supplied inside resources/tutorial8_LeakageModel.cellml.
    auto leakage = libcellml::Component::create("leakage");
    membrane->addComponent(leakage);

    auto leakageImporter = libcellml::ImportSource::create();
    leakageImporter->setUrl("tutorial8_LeakageCurrentModel.cellml");

    leakage->setImportSource(leakageImporter);
    leakage->setImportReference("leakageCurrent");

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Import a controller component          " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  5.a Repeat all the tasks in Step 2, this time for the controller component in
    //      the model supplied inside resources/tutorial8_controller.cellml.
    auto controller = libcellml::Component::create("controller");
    model->addComponent(controller);

    auto controllerImporter = libcellml::ImportSource::create();
    controllerImporter->setUrl("tutorial8_controller.cellml");

    controller->setImportSource(controllerImporter);
    controller->setImportReference("membrane_controller");

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 6: Resolve imports and flatten the model  " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    model->resolveImports("");
    if (model->hasUnresolvedImports()) {
        std::cout << "Imports are UNRESOLVED :(" << std::endl;
    } else {
        std::cout << "Imports are resolved :)" << std::endl;
    }

    model->flatten();
    printEncapsulationStructureToTerminal(model);
    printModelToTerminal(model, false);

    controller = model->component("controller");
    membrane = model->component("membrane");
    leakage = membrane->component("leakage");
    sodiumChannel = membrane->component("sodium_channel");
    potassiumChannel = membrane->component("potassium_channel");

    // Link all the equivalent variables together:
    assert(libcellml::Variable::addEquivalence(controller->variable("V"), membrane->variable("V")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("V"), sodiumChannel->variable("V")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("V"), potassiumChannel->variable("V")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("V"), leakage->variable("V")));

    assert(libcellml::Variable::addEquivalence(controller->variable("t"), membrane->variable("t")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("t"), sodiumChannel->variable("t")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("t"), potassiumChannel->variable("t")));

    assert(libcellml::Variable::addEquivalence(membrane->variable("i_Na"), sodiumChannel->variable("i_Na")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("i_K"), potassiumChannel->variable("i_K")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("i_L"), leakage->variable("i_L")));

    validator->validateModel(model);
    printErrorsToTerminal(validator);
    assert(validator->errorCount() == 0);
    printModelToTerminal(model, false);

    auto V = membrane->variable("V");
    std::cout << traceEquivalentVariableSet(V)<<std::endl;

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 6: Generate the model and output  " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    auto generator = libcellml::Generator::create();
    generator->processModel(model);



    printErrorsToTerminal(generator);
}
