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

    // Create a new controller model, containing the controller component and a parameters component.
    //    This will be written separately to the main model so that its values can be changed easily.
    auto controllerModel = libcellml::Model::create("Tutorial8_parameters");
    auto parameters = libcellml::Component::create("parameters");
    controllerModel->addComponent(parameters);

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
    membrane->setImportReference("membrane");

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
    assert(model->hasUnresolvedImports() == false);
    std::cout << "Imports are RESOLVED" << std::endl;

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

    // Add voltage and Cm initialisation variables to the external parameters component, as well as their units to the controller model
    {
        auto Cm = libcellml::Variable::create("Cm");
        parameters->addVariable(Cm);
        parameters->variable("Cm")->setUnits("microF_per_cm2");
        parameters->variable("Cm")->setInterfaceType("public_and_private");
        Cm->setInitialValue(1);

        auto microF_per_cm2 = libcellml::Units::create("microF_per_cm2");
        microF_per_cm2->addUnit("farad", "micro");
        microF_per_cm2->addUnit("metre", "centi", -2);
        controllerModel->addUnits(microF_per_cm2);

        auto V = libcellml::Variable::create("V");
        parameters->addVariable(V);
        parameters->variable("V")->setUnits("mV");
        parameters->variable("V")->setInterfaceType("public_and_private");
        V->setInitialValue(0);

        auto mV = libcellml::Units::create("mV");
        mV->addUnit("volt", "milli");
        controllerModel->addUnits(mV);
    }

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

    //  2.d Create dummy variables for voltage, time, current:
    {
        auto V = libcellml::Variable::create("V");
        sodiumChannel->addVariable(V);
        auto t = libcellml::Variable::create("t");
        sodiumChannel->addVariable(t);
        auto i_Na = libcellml::Variable::create("i_Na");
        sodiumChannel->addVariable(i_Na);
    }
    // Create dummy variables for m and h gate status so that they can be initialised:
    {
        auto h = libcellml::Variable::create("h");
        sodiumChannel->addVariable(h);
        auto m = libcellml::Variable::create("m");
        sodiumChannel->addVariable(m);

        auto g_Na = libcellml::Variable::create("g_Na");
        sodiumChannel->addVariable(g_Na);
        auto E_Na = libcellml::Variable::create("E_Na");
        sodiumChannel->addVariable(E_Na);
    }

    // Create concrete variables in the membrane component for any variables that will need initialisation too
    {
        auto h = libcellml::Variable::create("h");
        membrane->addVariable(h);
        auto m = libcellml::Variable::create("m");
        membrane->addVariable(m);

        auto g_Na = libcellml::Variable::create("g_Na");
        membrane->addVariable(g_Na);
        auto E_Na = libcellml::Variable::create("E_Na");
        membrane->addVariable(E_Na);

        h->setInterfaceType("public_and_private");
        m->setInterfaceType("public_and_private");
        g_Na->setInterfaceType("public_and_private");
        E_Na->setInterfaceType("public_and_private");

        h->setUnits("dimensionless");
        m->setUnits("dimensionless");
        g_Na->setUnits("mS_per_cm2");
        E_Na->setUnits("mV");
    }

    // Create concrete variables in the external parameters component to allow for initialisation
    {
        auto h = libcellml::Variable::create("h");
        parameters->addVariable(h);
        h->setInterfaceType("public_and_private");
        h->setUnits("dimensionless");
        h->setInitialValue(0.6);

        auto m = libcellml::Variable::create("m");
        parameters->addVariable(m);
        m->setInterfaceType("public_and_private");
        m->setUnits("dimensionless");
        m->setInitialValue(0.05);

        auto E_Na = libcellml::Variable::create("E_Na");
        parameters->addVariable(E_Na);
        E_Na->setInterfaceType("public_and_private");
        E_Na->setUnits("mV");
        E_Na->setInitialValue(35);

        auto g_Na = libcellml::Variable::create("g_Na");
        parameters->addVariable(g_Na);
        g_Na->setInterfaceType("public_and_private");
        g_Na->setUnits("mS_per_cm2");
        g_Na->setInitialValue(120);

        // Add missing units to the controller model
        auto mS_per_cm2 = libcellml::Units::create("mS_per_cm2");
        mS_per_cm2->addUnit("siemens", "milli");
        mS_per_cm2->addUnit("metre", "centi", -2);
        controllerModel->addUnits(mS_per_cm2);
    }

    model->resolveImports("");
    assert(model->hasUnresolvedImports() == false);

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Import the potassium channel component " << std::endl;
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

    model->resolveImports("");
    assert(model->hasUnresolvedImports() == false);

    {
        auto V = libcellml::Variable::create("V");
        potassiumChannel->addVariable(V);
        auto t = libcellml::Variable::create("t");
        potassiumChannel->addVariable(t);
        auto i_K = libcellml::Variable::create("i_K");
        potassiumChannel->addVariable(i_K);

        auto n = libcellml::Variable::create("n");
        potassiumChannel->addVariable(n);
        auto g_K = libcellml::Variable::create("g_K");
        potassiumChannel->addVariable(g_K);
        auto E_K = libcellml::Variable::create("E_K");
        potassiumChannel->addVariable(E_K);
    }

    // Add these variables to the membrane component too
    {
        auto n = libcellml::Variable::create("n");
        membrane->addVariable(n);
        auto g_K = libcellml::Variable::create("g_K");
        membrane->addVariable(g_K);
        auto E_K = libcellml::Variable::create("E_K");
        membrane->addVariable(E_K);

        n->setInterfaceType("public_and_private");
        g_K->setInterfaceType("public_and_private");
        E_K->setInterfaceType("public_and_private");
        n->setUnits("dimensionless");
        g_K->setUnits("milliS_per_cm2");
        E_K->setUnits("millivolt");
    }

    // Add variables to the external parameters component for initialisation
    {
        auto n = libcellml::Variable::create("n");
        parameters->addVariable(n);
        n->setInterfaceType("public_and_private");
        n->setUnits("dimensionless");
        n->setInitialValue(0.325);

        auto g_K = libcellml::Variable::create("g_K");
        parameters->addVariable(g_K);
        g_K->setInterfaceType("public_and_private");
        g_K->setUnits("mS_per_cm2");
        g_K->setInitialValue(36);

        auto E_K = libcellml::Variable::create("E_K");
        parameters->addVariable(E_K);
        E_K->setInterfaceType("public_and_private");
        E_K->setUnits("mV");
    }

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

    // Dummy variables to leakage component
    {
        auto V = libcellml::Variable::create("V");
        leakage->addVariable(V);
        auto t = libcellml::Variable::create("t");
        leakage->addVariable(t);
        auto i_L = libcellml::Variable::create("i_L");
        leakage->addVariable(i_L);

        auto g_L = libcellml::Variable::create("g_L");
        leakage->addVariable(g_L);
        auto E_L = libcellml::Variable::create("E_L");
        leakage->addVariable(E_L);
    }

    // Concrete variables in membrane component
    {
        auto g_L = libcellml::Variable::create("g_L");
        g_L->setInterfaceType("public_and_private");
        g_L->setUnits("mS_per_cm2");
        membrane->addVariable(g_L);

        auto E_L = libcellml::Variable::create("E_L");
        E_L->setUnits("mV");
        E_L->setInterfaceType("public_and_private");
        membrane->addVariable(E_L);
    }

    // Concrete variables to the external parameters component
    {
        auto g_L = libcellml::Variable::create("g_L");
        g_L->setInterfaceType("public_and_private");
        g_L->setUnits("mS_per_cm2");
        parameters->addVariable(g_L);

        auto E_L = libcellml::Variable::create("E_L");
        E_L->setUnits("mV");
        E_L->setInterfaceType("public_and_private");

        parameters->addVariable(E_L);
    }

    model->resolveImports("");
    assert(model->hasUnresolvedImports() == false);

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Export the parameters                  " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    // Set the initial conditions
    {
        // sodium channel
        parameters->variable("E_Na")->setInitialValue(-115);
        parameters->variable("g_Na")->setInitialValue(120);
        // h-gate
        parameters->variable("h")->setInitialValue(0.6);
        // m-gate
        parameters->variable("m")->setInitialValue(0.05);

        // potassium channel
        parameters->variable("E_K")->setInitialValue(12);
        parameters->variable("g_K")->setInitialValue(36);
        // n-gate
        parameters->variable("n")->setInitialValue(0.325);

        // leakage
        parameters->variable("g_L")->setInitialValue(0.3);
        parameters->variable("E_L")->setInitialValue(-10.613);

        // membrane
        parameters->variable("V")->setInitialValue(0);
        parameters->variable("Cm")->setInitialValue(1);
    }

    // Validate controller model
    controllerModel->linkUnits();
    validator->validateModel(controllerModel);
    printErrorsToTerminal(validator);

    // Write the parameters and controller model so that it can be imported below:
    auto printer = libcellml::Printer::create();
    std::ofstream outFile("tutorial8_HodgkinHuxley_controller.cellml");
    outFile << printer->printModel(controllerModel);
    outFile.close();

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 6: Import the parameters                  " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  5.a Repeat all the tasks in Step 2, this time for the
    //      parameters components in the model supplied inside
    //      resources/tutorial8_controller.cellml.
    parameters = libcellml::Component::create("parameters");
    model->addComponent(parameters);

    auto parametersImporter = libcellml::ImportSource::create();
    parametersImporter->setUrl("tutorial8_HodgkinHuxley_controller.cellml");

    parameters->setImportSource(parametersImporter);
    parameters->setImportReference("parameters");

    //  5.b Set up a dummy variable for voltage so that the parameters component
    //      can initialise the ODE in the membrane component.
    {
        // Membrane component
        auto V = libcellml::Variable::create("V");
        parameters->addVariable(V);
        auto Cm = libcellml::Variable::create("Cm");
        parameters->addVariable(Cm);

        // Sodium channel
        auto h = libcellml::Variable::create("h");
        parameters->addVariable(h);
        auto m = libcellml::Variable::create("m");
        parameters->addVariable(m);
        auto E_Na = libcellml::Variable::create("E_Na");
        parameters->addVariable(E_Na);
        auto g_Na = libcellml::Variable::create("g_Na");
        parameters->addVariable(g_Na);

        // Potassium channel
        auto n = libcellml::Variable::create("n");
        parameters->addVariable(n);
        auto E_K = libcellml::Variable::create("E_K");
        parameters->addVariable(E_K);
        auto g_K = libcellml::Variable::create("g_K");
        parameters->addVariable(g_K);

        // Leakage
        auto E_L = libcellml::Variable::create("E_L");
        parameters->addVariable(E_L);
        auto g_L = libcellml::Variable::create("g_L");
        parameters->addVariable(g_L);
    }

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 6: Connect variables between components   " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  6.a Now that we've got all the imports done, we need to connect the imported
    //      components and their dummy variables together.  The variables to connect are:
    //          - voltage:  parameters -> membrane -> sodium channel, potassium channel, leakage
    //          - time: membrane -> sodium channel, potassium channel
    //          - current variables (i_Na, i_K, i_L): membrane -> channels
    //          - Cm: parameters -> membrane

    assert(libcellml::Variable::addEquivalence(parameters->variable("V"), membrane->variable("V")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("Cm"), membrane->variable("Cm")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("h"), membrane->variable("h")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("m"), membrane->variable("m")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("n"), membrane->variable("n")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("g_K"), membrane->variable("g_K")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("g_Na"), membrane->variable("g_Na")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("g_L"), membrane->variable("g_L")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("E_K"), membrane->variable("E_K")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("E_Na"), membrane->variable("E_Na")));
    assert(libcellml::Variable::addEquivalence(parameters->variable("E_L"), membrane->variable("E_L")));

    assert(libcellml::Variable::addEquivalence(membrane->variable("V"), sodiumChannel->variable("V")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("t"), sodiumChannel->variable("t")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("i_Na"), sodiumChannel->variable("i_Na")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("E_Na"), sodiumChannel->variable("E_Na")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("g_Na"), sodiumChannel->variable("g_Na")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("h"), sodiumChannel->variable("h")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("m"), sodiumChannel->variable("m")));

    assert(libcellml::Variable::addEquivalence(membrane->variable("V"), potassiumChannel->variable("V")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("t"), potassiumChannel->variable("t")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("i_K"), potassiumChannel->variable("i_K")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("E_K"), potassiumChannel->variable("E_K")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("g_K"), potassiumChannel->variable("g_K")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("n"), potassiumChannel->variable("n")));

    assert(libcellml::Variable::addEquivalence(membrane->variable("V"), leakage->variable("V")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("i_L"), leakage->variable("i_L")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("g_L"), leakage->variable("g_L")));
    assert(libcellml::Variable::addEquivalence(membrane->variable("E_L"), leakage->variable("E_L")));

    //  6.b Serialise and write the model to a CellML file.  In the steps below the model will
    //      be flattened for code generation, but it's good to keep an unflattened copy too.
    outFile.open("tutorial8_HodgkinHuxleyModel.cellml");
    outFile << printer->printModel(model);
    outFile.close();

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 7: Resolve imports and flatten the model  " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  7.a Resolve the model's imports to the folder where all of the files are located, and
    //      check that there are no unresolved imports outstanding.
    model->resolveImports("");
    assert(model->hasUnresolvedImports() == false);

    //  7.b Flatten the model, and print the flattened model structure to the terminal for checking.
    model->flatten();
    printEncapsulationStructureToTerminal(model);
    printModelToTerminal(model, false);

    //  7.c Validate the flattened model, expecting that there are no errors.
    validator->validateModel(model);
    printErrorsToTerminal(validator);
    assert(validator->errorCount() == 0);

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "  STEP 8: Generate the model and output          " << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //  8.a Create a Generator instance and submit the model for processing.
    //      Expect that there are no errors logged in the generator afterwards.
    auto generator = libcellml::Generator::create();
    generator->processModel(model);
    printErrorsToTerminal(generator);

    assert(generator->errorCount() == 0);

    //  8.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.
    outFile.open("tutorial8_HodgkinHuxleyModel.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial8_HodgkinHuxleyModel.c");
    outFile << generator->implementationCode();
    outFile.close();

    //  8.c Change the generator profile to Python and reprocess the model.
    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);
    generator->processModel(model);

    //  8.d Retrieve and write the implementation code (*.py) to a file.
    outFile.open("tutorial8_HodgkinHuxleyModel.py");
    outFile << generator->implementationCode();
    outFile.close();

    std::cout << "The model has been output into tutorial8_HodgkinHuxleyModel.[c,h,py,cellml]"
              << std::endl;

    //  8.e Please seen the tutorial instructions for how to run this simulation using
    //      the simple solver provided.  Then go and have a cuppa, you're done!
}
