/**
 *      TUTORIAL 5: IMPORTS, COMPONENTS, AND CONNECTIONS
 * 
 *  This tutorial explores the ability of CellML to represent more than one
 *  modelled process at a time using components with connections between them.
 *  By the time you have worked through Tutorial 5 you will be able to:
 *      - import a Component or Units item from an existing CellML file
 *      - assemble a multi-component model using the API
 *      - inter-connect the components using the equivalent variables 
 *        functionality
 *      - validate and debug the constructed model
 * 
 *  Tutorial 5 assumes that you are already comfortable with:
 *      - file manipulation and summarising using the utility functions
 *      - model creation through the API
 *      - debugging the model using the Validator functionality
 */

#include <iostream>
#include <libcellml>

#include "../../utilities/tutorial_utilities.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 1: Read the ion channel component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a Read the model created in Tutorial 4.  Note that if you didn't
    //      do that tutorial you can simply copy the CellML file
    //      from Resources/Tutorial4_IonChannelModel.cellml

    std::string inFileName = "../../resources/tutorial4_IonChannelModel.cellml";
    std::ifstream inFile(inFileName);
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();
    std::cout << "Opening the CellML file: '" << inFileName << "'" << std::endl;

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(inFileContents.str());

    //  1.b Print the parsed model to the terminal and check its contents
    printModelToTerminal(model);

    //  1.c Create a Validator and use it to check that the model is ok so far
    libcellml::Validator validator;
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    //  1.d Retrieve and rename the component
    model->setName("Tutorial5_PotassiumChannelModel");
    libcellml::ComponentPtr potassiumChannel = model->component(0);
    potassiumChannel->setName("potassiumChannel");

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Create the environment component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a Creating the new environment component
    libcellml::ComponentPtr environment = libcellml::Component::create();
    environment->setName("environment");

    //  2.b Add variables to the component.  Use brackets to define the scope of
    //      these variables. This means that we can use variables with the same
    //      symbol elsewhere.
    {
        libcellml::VariablePtr V = libcellml::Variable::create();
        V->setName("V");
        V->setUnits("millivolt");
        environment->addVariable(V);

        libcellml::VariablePtr t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("millisecond");
        environment->addVariable(t);
    } // end of the environment scope for variables

    //  2.c Add the new component to the model
    model->addComponent(environment);

    //  2.d Calling the validator to check that our model is valid so far.
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Define the n-gate component " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a Creating the n-gate component and the variables it contains
    libcellml::ComponentPtr nGate = libcellml::Component::create();
    nGate->setName("nGate");
    {
        libcellml::VariablePtr V = libcellml::Variable::create();
        V->setName("V");
        V->setUnits("millivolt");
        nGate->addVariable(V);

        libcellml::VariablePtr t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("millisecond");
        nGate->addVariable(t);

        libcellml::VariablePtr alpha_n = libcellml::Variable::create();
        alpha_n->setName("alpha_n");
        alpha_n->setUnits("per_millisecond");
        nGate->addVariable(alpha_n);

        libcellml::VariablePtr beta_n = libcellml::Variable::create();
        beta_n->setName("beta_n");
        beta_n->setUnits("per_millisecond");
        nGate->addVariable(beta_n);

        libcellml::VariablePtr n = libcellml::Variable::create();
        n->setName("n");
        n->setUnits("dimensionless");
        nGate->addVariable(n);

        // //  3.b Creating the MathML for the n-gate component and adding it in.
        std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
        std::string equation1 =
            "<apply>\
                <eq/>\
                <ci>alpha_n</ci>\
                <apply>\
                    <divide/>\
                    <apply>\
                        <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"per_millivolt_millisecond\">0.01</cn>\
                        <apply>\
                            <plus/>\
                            <ci>V</ci>\
                            <cn cellml:units=\"millivolt\">10</cn>\
                        </apply>\
                    </apply>\
                    <apply>\
                        <minus/>\
                        <apply>\
                            <exp/>\
                            <apply>\
                                <divide/>\
                                <apply>\
                                    <plus/>\
                                    <ci>V</ci>\
                                    <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"millivolt\">10</cn>\
                                </apply>\
                                <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"millivolt\">10</cn>\
                            </apply>\
                        </apply>\
                        <cn cellml:units=\"dimensionless\">1</cn>\
                    </apply>\
                </apply>\
            </apply>";

        std::string equation2 =
            "<apply>\
                <eq/>\
                <ci>beta_n</ci>\
                <apply>\
                    <times/>\
                    <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"per_millisecond\">0.125</cn>\
                    <apply>\
                        <exp/>\
                        <apply>\
                            <divide/>\
                            <ci>V</ci>\
                            <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"millivolt\">80</cn>\
                        </apply>\
                    </apply>\
                </apply>\
            </apply>";
        std::string equation3 =
            "<apply>\
                <eq/>\
                <apply>\
                    <diff/>\
                    <bvar>\
                        <ci>t</ci>\
                    </bvar>\
                    <ci>n</ci>\
                </apply>\
                <apply>\
                    <minus/>\
                    <apply>\
                        <times/>\
                        <ci>alpha_n</ci>\
                        <apply>\
                            <minus/>\
                            <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"dimensionless\">1</cn>\
                            <ci>n</ci>\
                        </apply>\
                    </apply>\
                    <apply>\
                        <times/>\
                        <ci>beta_n</ci>\
                        <ci>n</ci>\
                    </apply>\
                </apply>\
            </apply>";

        std::string mathFooter = "</math>";
        nGate->setMath(mathHeader);
        nGate->appendMath(equation1);
        nGate->appendMath(equation2);
        nGate->appendMath(equation3);
        nGate->appendMath(mathFooter);
    } // end scope of variables and maths in this component

    //  3.c Add the n-gate component into the model.
    model->addComponent(nGate);
    //validator.validateModel(model);
    //printErrorsToTerminal(validator);

    //  3.d Add the missing units (connected to the constant in equation 1) and recheck the validation
    libcellml::UnitsPtr per_mVms = libcellml::Units::create();
    per_mVms->setName("per_millivolt_millisecond");
    per_mVms->addUnit("volt", "milli", -1);
    per_mVms->addUnit("second", "milli", -1);
    model->addUnits(per_mVms);
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Define the component hierarchy " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  4.a Change the nGate component to be a child of the potassiumChannel component
    potassiumChannel->addComponent(nGate);

    //  4.b Verify the component hierarchy by printing the model to the screen
    printModelToTerminal(model);

    //  4.c Define the equivalent variables between components.  Note that because
    //      the variables have been defined within a limited scope (using the {} above)
    //      you will need to retrieve them from each component first.
    libcellml::Variable::addEquivalence(environment->variable("t"), potassiumChannel->variable("t"));

    // TODO not sure what's happening here - this line below should fail as not neighbouring components,
    // creates a validation error but should be allowed?
    libcellml::Variable::addEquivalence(environment->variable("t"), nGate->variable("t"));

    //  4.d Validating the model: this should show an error reporting that an
    //      invalid connection has been made between the environment and nGate
    //      components

    // TODO This should produce a validation error but currently does not?
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    //  4.e  Fix the connection error above, and add the voltage and gating variable equivalences
    libcellml::Variable::removeEquivalence(environment->variable("t"), nGate->variable("t"));
    libcellml::Variable::addEquivalence(potassiumChannel->variable("t"), nGate->variable("t"));
    libcellml::Variable::addEquivalence(environment->variable("V"), potassiumChannel->variable("V"));
    libcellml::Variable::addEquivalence(potassiumChannel->variable("V"), nGate->variable("V"));
    libcellml::Variable::addEquivalence(potassiumChannel->variable("n"), nGate->variable("n"));

    // TODO This should produce a validation error but currently does not?
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    //  4.f Add the interface specification.  The environment component is a sibling of the potassiumChannel
    //      component, so they will both use the public interface.  The nGate component is a child of the
    //      potassiumChannel, so will use the public interface.  The potassiumChannel is the parent of the
    //      nGate component, so will need an additional private interface.  The nGate will have a public
    //      interface to its parent, the potassiumChannel.  Thus for the V and t variables:
    //          - environment -> public
    //          - potassiumChannel -> public_and_private
    //          - nGate -> public
    //      Because the n variable is shared only between the potassiumChannel and the nGate, we don't need to
    //      use the public_and_private designation there; just private on the parent and public on the child.
    environment->variable("t")->setInterfaceType("public");
    environment->variable("V")->setInterfaceType("public");
    potassiumChannel->variable("t")->setInterfaceType("public_and_private");
    potassiumChannel->variable("V")->setInterfaceType("public_and_private");
    nGate->variable("t")->setInterfaceType("public");
    nGate->variable("V")->setInterfaceType("public");
    potassiumChannel->variable("n")->setInterfaceType("private");
    nGate->variable("n")->setInterfaceType("public");

    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Define the driving function " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  5.a Define a MathML string representing the voltage clamp
    std::string voltageClampMaths =
        "<apply>\
            <eq/>\
            <ci>V</ci>\
            <piecewise>\
                <piece>\
                    <cn cellml:units=\"millivolt\">0</cn>\
                    <apply><lt/><ci>t</ci><cn cellml:units=\"millisecond\">5</cn></apply>\
                </piece>\
                    <piece>\
                    <cn cellml:units=\"millivolt\">0</cn>\
                    <apply><gt/><ci>t</ci><cn cellml:units=\"millisecond\">15</cn></apply>\
                </piece>\
                <otherwise>\
                    <cn cellml:units=\"millivolt\">-85</cn>\
                </otherwise>\
            </piecewise>\
        </apply>";

    //  5.b Add this to the maths for the environment component.
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" \
        xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";
    environment->setMath(mathHeader);
    environment->appendMath(voltageClampMaths);
    environment->appendMath(mathFooter);

    //  5.c Validate the model including this new maths block
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 6: Serialse and print the model " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    libcellml::Printer printer;
    std::string serialisedModelString = printer.printModel(model);
    std::string outFileName = "tutorial5_PotassiumChannelModel.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The created '" << model->name()
              << "' model has been printed to: " << outFileName << std::endl;
}
