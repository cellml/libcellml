/**
 *      TUTORIAL 6: CODE GENERATION
 *
 *  This tutorial explores the ability of libCellML to generate files representing
 *  the model which can be solved in Python or C.  By the time you have worked
 *  through Tutorial 6 you will be able to:
 *      - use the Generator functionality to create models in Python or C format
 *      - use the simple solver provided to run the created models.
 *
 *  Tutorial 6 assumes that you are already comfortable with:
 *      - file manipulation and summarising using the utility functions
 *
 */

#include <iostream>
#include <libcellml>
#include <regex>

#include "../utilities/tutorial_utilities.h"

int main()
{
    //  0.a Create a new model instance representing the combined model and name it.
    auto model = libcellml::Model::create();
    model->setName("Tutorial8_HHModel");
    auto validator = libcellml::Validator::create();
    auto parser = libcellml::Parser::create();

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 1: Read the membrane component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a Read the model provided for you in the "Tutorial8_MembraneModel.cellml"
    //      file in the resources folder.
    std::string inFileName = "../resources/tutorial8_MembraneModel.cellml";
    std::ifstream inFile(inFileName);
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();
    std::cout << "Opening the CellML file: '" << inFileName << "'" << std::endl;

    // 1.b  Create a temporary model for the membrane
    auto membraneModel = parser->parseModel(inFileContents.str());
    membraneModel->setName("membraneModel");

    //  1.b Extract the membrane component from the parsed model and add it
    //      to the combined model.  Note that the membrane component's parent
    //      must be cleared before adding it to the model.
    auto membrane = membraneModel->component("membrane");
    membrane->removeParent();
    model->addComponent(membrane);

    //  1.c Validate the combined model.  We expect to see errors from:
    //      - missing units, as we have only added the component so far
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  1.d Import the units from the membraneModel into the combined model
    for (size_t u = 0; u < membraneModel->unitsCount(); ++u) {
        model->addUnits(membraneModel->units(u));
    }

    //  1.e No errors expected this time :)
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "      STEP 2: Read the sodium channel" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a Read the model created in Tutorial 7 representing the sodium channel.
    //      Note that if you didn't do that tutorial you can simply copy the CellML file
    //      from Tutorial7_SodiumChannelModel.cellml in the resources folder.
    inFileName = "../resources/tutorial7_SodiumChannelModel.cellml";
    inFile.close();
    inFile.open(inFileName);
    std::stringstream().swap(inFileContents);
    inFileContents << inFile.rdbuf();

    std::cout << "Opening the CellML file: '" << inFileName << "'" << std::endl;

    auto sodiumChannelModel = parser->parseModel(inFileContents.str());
    sodiumChannelModel->setName("sodiumChannelModel");

    //  2.b Extract the sodiumChannel component from the parsed model and add it
    //      to the one created at the beginning, and check the structure of the
    //      encapsulation using the utility function printEncapsulationStructureToTerminal(model)
    auto sodiumChannel = sodiumChannelModel->component("sodiumChannel");
    sodiumChannel->removeParent();
    membrane->addComponent(sodiumChannel);
    printEncapsulationStructureToTerminal(model);

    //  2.c Validate the combined model.  We expect to see errors from:
    //      - missing units, as we have only added the component so far,
    //      - illegal connections between equivalent varaibles, as now the environment
    //        component and the sodiumChannel component are no longer siblings.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  2.d Add all of the units from the sodium channel model which are not already
    //        present into the combined model.
    for (size_t u = 0; u < sodiumChannelModel->unitsCount(); ++u) {
        std::string unitName = sodiumChannelModel->units(u)->name();
        if (!model->hasUnits(unitName)) {
            std::cout << "Adding units called " << unitName << std::endl;
            model->addUnits(sodiumChannelModel->units(u));
        }
    }

    //  2.e Disconnect the sodiumChannel from its old environment component
    libcellml::Variable::removeEquivalence(
        sodiumChannel->variable("t"),
        sodiumChannelModel->component("environment")->variable("t"));
    libcellml::Variable::removeEquivalence(
        sodiumChannel->variable("V"),
        sodiumChannelModel->component("environment")->variable("V"));

    //  2.f Validate that there are no more errors in the combined model
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "       STEP 3: Read the potassium channel" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    inFileName = "../resources/tutorial5_PotassiumChannelModel.cellml";
    inFile.close();
    inFile.open(inFileName);
    std::stringstream().swap(inFileContents);
    inFileContents << inFile.rdbuf();
    std::cout << "Opening the CellML file: '" << inFileName << "'" << std::endl;

    //  3.a Deserialising the file and reading into the potassiumChannelModel
    auto potassiumChannelModel = parser->parseModel(inFileContents.str());
    potassiumChannelModel->setName("potassiumChannelModel");

    //  3.b Extract the potassiumChannel component from the parsed model and add it
    //      to the combined model, and check the contents
    auto potassiumChannel = potassiumChannelModel->component("potassiumChannel");
    potassiumChannel->removeParent();
    membrane->addComponent(potassiumChannel);

    //  3.c Validate the combined model.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  If you have used the files provided in the Resources folder, you can expect
    //  to see errors at this point relating to missing units.
    //  This is because even though both components require the same set of units,
    //  each of them has used different names for them.  At this stage you have a
    //  choice: either import all the units under their original names from the
    //  potassium channel as well, or rename the units throughout the potassiumChannel
    //  variables and maths.  Here we'll go with the former to illustrate the
    //  process, and to create a more compact model description.

    //  3.d Rename the units referred to by the variables in the potassiumChannel and nGate components
    potassiumChannel->variable("t")->setUnits("ms");
    potassiumChannel->variable("V")->setUnits("mV");
    potassiumChannel->variable("E_K")->setUnits("mV");
    potassiumChannel->variable("g_K")->setUnits("mS_per_cm2");
    potassiumChannel->variable("alpha_n")->setUnits("per_ms");
    potassiumChannel->variable("beta_n")->setUnits("per_ms");

    potassiumChannel->component("nGate")->variable("t")->setUnits("ms");
    potassiumChannel->component("nGate")->variable("V")->setUnits("mV");
    potassiumChannel->component("nGate")->variable("alpha_n")->setUnits("per_ms");
    potassiumChannel->component("nGate")->variable("beta_n")->setUnits("per_ms");

    //  3.e Replacing units in the MathML string in the nGate component.
    //      Note: There are no constants in the potassiumChannel maths, so we don't need to
    //      search and replace the maths there.  In the general case, you'd need to do the
    //      same in that component too.
    std::string nGateMaths = potassiumChannel->component("nGate")->math();
    switchUnitsInMaths(nGateMaths, "millivolt", "mV");
    switchUnitsInMaths(nGateMaths, "millisecond", "ms");
    switchUnitsInMaths(nGateMaths, "per_millisecond", "per_ms");
    switchUnitsInMaths(nGateMaths, "per_millivolt_millisecond", "per_mV_ms");
    switchUnitsInMaths(nGateMaths, "milliS_per_cm2", "mS_per_cm2");
    potassiumChannel->component("nGate")->setMath(nGateMaths);

    //  3.f Validating the model again.  This time we expect errors related to a mismatch in errors
    //      between equivalent variables ... which is a misleading error message because in the
    //      source model - PotassiumChannelModel, they *were* equivalent!  We haven't imported
    //      the environment component into our combined model yet, and that is the origin of this
    //      error.  We can solve the problem by creating the local environment component, and adding
    //      the equivalence to that instead.
    libcellml::Variable::removeEquivalence(
        potassiumChannel->variable("t"),
        potassiumChannelModel->component("environment")->variable("t"));
    libcellml::Variable::removeEquivalence(
        potassiumChannel->variable("V"),
        potassiumChannelModel->component("environment")->variable("V"));

    //  3.g Calling the validator again.  We do not expect errors here.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 4: Read the leakage component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    inFileName = "../resources/tutorial8_LeakageCurrentModel.cellml";
    inFile.close();
    inFile.open(inFileName);
    std::stringstream().swap(inFileContents);
    inFileContents << inFile.rdbuf();
    std::cout << "Opening the CellML file: '" << inFileName << "'" << std::endl;

    //  4.a Deserialising the file and reading into the leakageCurrentModel
    auto leakageCurrentModel = parser->parseModel(inFileContents.str());
    leakageCurrentModel->setName("leakageCurrentModel");

    //  4.b Extract the leakageCurrent component from the parsed model and add it
    //      to the combined model, and check the contents
    auto leakageCurrent = leakageCurrentModel->component("leakageCurrent");
    leakageCurrent->removeParent();
    membrane->addComponent(leakageCurrent);

    //  4.c Validate the combined model.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   STEP 5: Create the environment component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    printEncapsulationStructureToTerminal(model);

    //  5.a Creating the environment component and adding it to the model
    auto environment = libcellml::Component::create();
    environment->setName("environment");
    model->addComponent(environment);

    //  5.b Add variables to the environment component.
    {
        auto V = libcellml::Variable::create();
        V->setName("V");
        V->setInitialValue(-85);
        V->setUnits("mV");
        environment->addVariable(V);

        auto t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("ms");
        environment->addVariable(t);
    } // end of the environment scope for variables

    //  5.c Add the new component to the model and validate
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   STEP 6: Connect the equivalent variables" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  6.a Connecting the membrane to its sibling environment, and the channels to their
    //      parent membrane component.
    libcellml::Variable::addEquivalence(membrane->variable("t"), sodiumChannel->variable("t"));
    libcellml::Variable::addEquivalence(membrane->variable("t"), potassiumChannel->variable("t"));
    libcellml::Variable::addEquivalence(environment->variable("t"), membrane->variable("t"));
    libcellml::Variable::addEquivalence(membrane->variable("V"), sodiumChannel->variable("V"));
    libcellml::Variable::addEquivalence(membrane->variable("V"), potassiumChannel->variable("V"));
    libcellml::Variable::addEquivalence(membrane->variable("V"), leakageCurrent->variable("V"));
    libcellml::Variable::addEquivalence(environment->variable("V"), membrane->variable("V"));

    //  6.b Setting the interface types for those which haven't been inherited already
    environment->variable("t")->setInterfaceType("public");
    membrane->variable("t")->setInterfaceType("public_and_private");
    environment->variable("V")->setInterfaceType("public");
    membrane->variable("V")->setInterfaceType("public_and_private");

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   STEP 7: Add the driving function" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  7.a Create a MathML string to represent the stimulus current i_stim, which
    //      is set to 100 microA/cm^2 between t=1ms < t < t=1.2ms.
    std::string stimulusEquation =
            "<apply><eq/>\
                <ci>i_stim</ci>\
                <piecewise>\
                    <piece>\
                        <cn cellml:units=\"microA_per_cm2\">0</cn>\
                        <apply><lt/><ci>t</ci><cn cellml:units=\"ms\">1</cn></apply>\
                    </piece>\
                        <piece>\
                        <cn cellml:units=\"microA_per_cm2\">0</cn>\
                        <apply><gt/><ci>t</ci><cn cellml:units=\"ms\">1.2</cn></apply>\
                    </piece>\
                    <otherwise>\
                        <cn cellml:units=\"microA_per_cm2\">100</cn>\
                    </otherwise>\
                </piecewise>\
            </apply>";

    //  7.b Add before the closing </math> tag in the membrane component
    std::string membraneMathML = membrane->math();
    insertIntoMathMLString(membraneMathML, stimulusEquation);
    membrane->setMath(membraneMathML);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   STEP 8: Generate the model and print        " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    auto generator = libcellml::Generator::create();
    generator->processModel(model);

    printErrorsToTerminal(generator);



    auto printer=libcellml::Printer::create();
    std::string serialisedModelString = printer->printModel(model);
    std::string outFileName = "tutorial8_HodgkinHuxleyModel.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The created '" << model->name()
              << "' model has been printed to: " << outFileName << std::endl;





}
