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
    auto model = libcellml::Model::create("Tutorial7_SodiumChannelModel");

    //  1.b Create a component instance for the sodium channel, name it, and add to the model.
    auto sodiumChannel = libcellml::Component::create();
    sodiumChannel->setName("sodiumChannel");
    model->addComponent(sodiumChannel);

    //  1.c Add the MathML representing the governing equations to the component, and validate the model.
    {
        std::string equation1 =
            "  <apply><eq/>\n"
            "    <ci>Na_conductance</ci>\n"
            "    <apply><times/>\n"
            "      <ci>g_Na</ci>\n"
            "      <ci>h</ci>\n"
            "      <apply><power/>\n"
            "        <ci>m</ci>\n"
            "        <cn cellml:units=\"dimensionless\">3</cn>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        std::string equation2 =
            "  <apply><eq/>\n"
            "    <ci>i_Na</ci>\n"
            "    <apply><times/>\n"
            "      <ci>Na_conductance</ci>\n"
            "      <apply><minus/>\n"
            "        <ci>V</ci>\n"
            "        <ci>E_Na</ci>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        sodiumChannel->setMath(mathHeader);
        sodiumChannel->appendMath(equation1);
        sodiumChannel->appendMath(equation2);
        sodiumChannel->appendMath(mathFooter);
    }

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  1.d Add the variables required by the validator.
    {
        auto V = libcellml::Variable::create("V");
        V->setUnits("mV");
        sodiumChannel->addVariable(V);

        auto t = libcellml::Variable::create("t");
        t->setUnits("ms");
        sodiumChannel->addVariable(t);

        auto h = libcellml::Variable::create("h");
        h->setUnits("dimensionless");
        sodiumChannel->addVariable(h);

        auto m = libcellml::Variable::create("m");
        m->setUnits("dimensionless");
        sodiumChannel->addVariable(m);

        auto g_Na = libcellml::Variable::create("g_Na");
        g_Na->setUnits("mS_per_cm2");
        sodiumChannel->addVariable(g_Na);

        auto E_Na = libcellml::Variable::create("E_Na");
        E_Na->setUnits("mV");
        sodiumChannel->addVariable(E_Na);

        auto i_Na = libcellml::Variable::create("i_Na");
        i_Na->setUnits("microA_per_cm2");
        sodiumChannel->addVariable(i_Na);

        auto Na_conductance = libcellml::Variable::create("Na_conductance");
        Na_conductance->setUnits("mS_per_cm2");
        sodiumChannel->addVariable(Na_conductance);
    }

    //  1.e Add the units as required by the validator.
    {
        auto mV = libcellml::Units::create("mV");
        mV->addUnit("volt", "milli");
        model->addUnits(mV);

        auto ms = libcellml::Units::create("ms");
        ms->addUnit("second", "milli");
        model->addUnits(ms);

        auto mS_per_cm2 = libcellml::Units::create("mS_per_cm2");
        mS_per_cm2->addUnit("siemens", "milli");
        mS_per_cm2->addUnit("metre", "centi", -2);
        model->addUnits(mS_per_cm2);

        auto microA_per_cm2 = libcellml::Units::create("microA_per_cm2");
        microA_per_cm2->addUnit("ampere", "micro");
        microA_per_cm2->addUnit("metre", "centi", -2);
        model->addUnits(microA_per_cm2);

        auto mM = libcellml::Units::create("mM");
        mM->addUnit("mole", "milli");
        model->addUnits(mM);
    }

    //  1.f Link the model's units and use the validator to make sure that there
    //      are no more errors in the model.
    model->linkUnits();
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 2: Specify the imported component 'mGate'" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    //  2.a Create a component representing the mGate, name it appropriately, and
    //      add it as a child of the sodium channel component.
    auto mGate = libcellml::Component::create("mGate");
    sodiumChannel->addComponent(mGate);

    //  2.b Create an ImportSource item and attach it to the component.  This indicates
    //      that the component's contents will be imported from another model.
    auto mGateImportSource = libcellml::ImportSource::create();
    mGate->setImportSource(mGateImportSource);

    //  2.c Set the URL of the ImportSource to the location at which the other model
    //      can be found.  This can be absolute, or relative to the current model's location.
    //      For this example, use the file in the resources folder named "tutorial7_mGate.cellml".
    mGateImportSource->setUrl("tutorial7_mGate.cellml");

    //  2.d Set the component's import reference to be the name of the component in the 
    //      other model whose contents will be imported into this one.  For this example, use "mGate".
    mGate->setImportReference("mGate");

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
    mGate->addVariable(libcellml::Variable::create("t"));
    mGate->addVariable(libcellml::Variable::create("V"));
    mGate->addVariable(libcellml::Variable::create("m"));

    //  2.f Add variable equivalences between the dummy variables you just created and their counterparts
    //      in the sodium channel component.
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("t"), mGate->variable("t")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("V"), mGate->variable("V")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("m"), mGate->variable("m")));

    //  2.g Submit to the validator for checking.  Expect errors related to the interface types on the
    //      variables you have just created equivalences for.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  2.h Fix the interface types for the sodium channel variables by setting them to "public_and_private".
    sodiumChannel->variable("t")->setInterfaceType("public_and_private");
    sodiumChannel->variable("V")->setInterfaceType("public_and_private");
    sodiumChannel->variable("m")->setInterfaceType("public_and_private");
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    // Step 3: Repeat the steps within Step 2 for the hGate component, and include it as a child of the 
    // sodium channel component.
    //  - It is defined inside the file called "tutorial7_hGate.cellml" in the resources folder.
    //  - Import the component reference "hGate" from that file.
    //  - You will need to create and link dummy variables named "h", "V", and "t".
    //  - You will need to set the sodium channel variable "h" to have an interface type "public_and_private".

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 3: Specify the imported component 'hGate'" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    auto hGate = libcellml::Component::create("hGate");
    sodiumChannel->addComponent(hGate);

    auto hGateImportSource = libcellml::ImportSource::create();
    hGateImportSource->setUrl("tutorial7_hGate.cellml");
    hGate->setImportSource(hGateImportSource);
    hGate->setImportReference("hGate");

    hGate->addVariable(libcellml::Variable::create("t"));
    hGate->addVariable(libcellml::Variable::create("V"));
    hGate->addVariable(libcellml::Variable::create("h"));
    
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("t"), hGate->variable("t")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("V"), hGate->variable("V")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("h"), hGate->variable("h")));

    sodiumChannel->variable("h")->setInterfaceType("public_and_private");

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    // Step 4: Repeat the steps within Step 2 for the controller component, and include it as a child of the 
    // model.  
    //  - It is defined inside the file called "tutorial7_controller.cellml" in the resources folder;
    //  - Import the component reference "controller" from that file.
    //  - You will need to create and link dummy variables named "V" and "t".
    //  - You will need to set the sodium channel variables to have an interface type "public_and_private".

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << " STEP 4: Specify the imported component 'controller'" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    auto controller = libcellml::Component::create("controller");
    model->addComponent(controller);

    auto importSource = libcellml::ImportSource::create();
    importSource->setUrl("tutorial7_controller.cellml");

    controller->setImportSource(importSource);
    controller->setImportReference("controller");
    controller->addVariable(libcellml::Variable::create("t"));
    controller->addVariable(libcellml::Variable::create("V"));

    assert(libcellml::Variable::addEquivalence(controller->variable("t"), sodiumChannel->variable("t")));
    assert(libcellml::Variable::addEquivalence(controller->variable("V"), sodiumChannel->variable("V")));
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    // Step 5: Repeat the steps within Step 2 for the parameters component, and include it 
    // as a child of the model. Note that since this step will access the same file as was used in Step 4 
    // ("tutorial7_controller.cellml" in the resources folder), you can simply reuse the same ImportSource
    // item you created there for this component.  
    //  - Import the component reference "parameters" from that file.
    //  - You will need to create and link dummy variables named "m", "h", "g_Na", and "E_Na".
    //  - You will need to set the corresponding sodium channel variables to have an interface type "public".

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << " STEP 5: Specify the imported component 'parameters'" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    auto parameters = libcellml::Component::create("parameters");
    parameters->setImportSource(importSource);
    parameters->setImportReference("parameters");

    model->addComponent(parameters);

    parameters->addVariable(libcellml::Variable::create("m"));
    parameters->addVariable(libcellml::Variable::create("h"));
    parameters->addVariable(libcellml::Variable::create("E_Na"));
    parameters->addVariable(libcellml::Variable::create("g_Na"));

    sodiumChannel->variable("E_Na")->setInterfaceType("public");
    sodiumChannel->variable("g_Na")->setInterfaceType("public");
    
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("m"), parameters->variable("m")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("h"), parameters->variable("h")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("E_Na"), parameters->variable("E_Na")));
    assert(libcellml::Variable::addEquivalence(sodiumChannel->variable("g_Na"), parameters->variable("g_Na")));

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 6: Serialise and output the model" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    // Step 6: Tidy and output the model.

    // 6.a  Even though it won't be used in this tutorial, we need to set the interface types on any variable
    //      in the sodium channel component that will need to be accessible to other components later.  It's
    //      worth thinking about these at the time of writing the component, as it increases its reusability
    //      and usefulness later on.  In this case, we'll only need to set the i_Na sodium current variable
    //      to have a public interface.

    sodiumChannel->variable("i_Na")->setInterfaceType("public");

    //  6.b At this stage our model can be written to a CellML file.  As the model
    //      contains import statements, the serialised and printed model would also maintain those
    //      same dependencies, and would need to exist alongside the tutorial7_controller.cellml
    //      file specified earlier.  In later steps we'll disconnect this dependency to allow for
    //      the code generation step.
    //
    //      Check that the model is valid, then create a Printer, and use it to serialise the model.
    //      Write the serialised model to a file.

    auto printer = libcellml::Printer::create();
    std::ofstream outFile("tutorial7_SodiumChannelModel.cellml");
    outFile << printer->printModel(model);
    outFile.close();

    std::cout << "The model has been written to tutorial7_SodiumChannelModel.cellml" << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 7: Resolve imports and flatten the model" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    // Step 7: Resolve the imports and flatten the model.

    //  7.a Create an Importer item.
    auto importer = libcellml::Importer::create();

    //  7.b Call the Model::hasUnresolvedImports() function to check that the imports have 
    //      not yet been resolved.  It should return true.
    assert(model->hasUnresolvedImports());

    //  7.c The importer needs to know the path to where the import dependencies are located.
    //      This should be relative to the current working directory, and should end with a slash.
    //      Call the Importer::resolveImports function with the model and the pathway to the resources
    //      folder from your working directory.
    importer->resolveImports(model, "../resources/");

    //  7.d Check that the imports have been resolved by repeating 7.b and expecting it to return false.
    assert(!model->hasUnresolvedImports());

    //  7.e Check that there are no issues recorded in the importer.
    printErrorsToTerminal(importer);
    
    //  7.f Now it's time to flatten the model.  This process will leave the original model untouched
    //      and return a flattened copy.  Create a flattened model by calling the Importer::flattenModel
    //      function.  Note that if you call the flattenModel function on a model which still has
    //      unresolved imports, it will return a null pointer.  
    auto flatModel = importer->flattenModel(model);

    //  7.g Check that the flattened model is not null, and then pass it to the validator and 
    //      check that there are no errors.
    assert(flatModel != nullptr);
    validator->validateModel(flatModel);
    printErrorsToTerminal(validator);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " STEP 7: Generate and output the model" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    //  8.a Create a Generator instance and pass it the flattened model for processing.
    //      Check that there are no errors reported by the generator.
    auto generator = libcellml::Generator::create();
    generator->processModel(flatModel);
    printErrorsToTerminal(generator);

    //  8.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.
    outFile.open("tutorial7_SodiumChannelModel.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial7_SodiumChannelModel.c");
    outFile << generator->implementationCode();
    outFile.close();

    //  8.c Change the generator profile to Python and reprocess the model.
    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);
    generator->processModel(flatModel);

    //  8.d Retrieve and write the implementation code (*.py) to a file.
    outFile.open("tutorial7_SodiumChannelModel.py");
    outFile << generator->implementationCode();
    outFile.close();

    std::cout << "The model has been output into tutorial7_SodiumChannelModel.[c,h,py,cellml]"
              << std::endl;

    //  8.e The files can now be submitted to the simple solver for simulation.  Or,
    //      go and have a cuppa, you're done.
}
