/**
 *  TUTORIAL 4: Mathematical behaviour and units
 *
 *  This tutorial assumes that you can already:
 *      - read and deserialise a CellML model from a file (Tutorial 1)
 *      - retrieve the name and id of models, components, and variables (Tutorial 2),
 *      - navigate through the hierarchy of the model (Tutorial 2)
 *      - serialise and print a Model structure to a CellML file (Tutorial 1)
 *      - create and include user-defined units (Tutorial 3)
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

#include "../../utilities/tutorial_utilities.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 1: Create the model and component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a   Create the model instance
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("Tutorial4_FirstOrderModel");

    //  1.b   Create a component and add it into the model
    libcellml::ComponentPtr component = libcellml::Component::create();
    component->setName("IonChannel");
    model->addComponent(component);

    //  1.c   Call the validator and print the messages to the terminal.
    //        No errors are expected at this stage.
    libcellml::Validator validator;
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Define the mathematical behaviour" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a   Define the mathematics.
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";

    // dy/dt = alpha_y*(1-y) - beta_y*y
    std::string equation1 =
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
                        <cn cellml:units=\"dimensionless\">1</cn>\
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
    // i_y = g_y*power(y,gamma)*(V-E_y)
    std::string equation2 =
        "<apply>\
            <eq/>\
            <ci>i_K</ci>\
            <apply>\
                <times/>\
                <ci>g_K</ci>\
                <apply>\
                    <minus/>\
                    <ci>V</ci>\
                    <ci>E_K</ci>\
                </apply>\
                <apply>\
                    <power/>\
                    <ci>n</ci>\
                    <ci>gamma</ci>\
                </apply>\
            </apply>\
        </apply>";
    std::string mathFooter = "</math>";

    //  2.b   Add the maths to the component.  Note that there is only one maths
    //        string stored, so parts which are appended must create a viable
    //        MathML2 string when concantenated.  To clear any string which is
    //        already stored, simply call setMath("") with an empty string.
    component->setMath(mathHeader);
    component->appendMath(equation1);
    component->appendMath(equation2); // TODO adding a second apply block causes a segfault
    component->appendMath(mathFooter);

    //  2.c:  Call the validator and print the messages to the terminal.
    //        Expected errors refer to variables referenced in the maths which
    //        are not (yet) defined in the component, as well as cn element units
    //        which are not defined yet either.
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Define the variables and their units" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a,b Declaring the variables, their names, units, and initial conditions
    //        Note that the names given to variables must be the same as that used
    //        within the <ci> blocks in the MathML string we created in step 2.a.

    libcellml::VariablePtr t = libcellml::Variable::create();
    t->setName("t");
    t->setUnits("millisecond");
    // Note: time is our integration base variable so is not initialised

    libcellml::VariablePtr V = libcellml::Variable::create();
    V->setName("V");
    V->setUnits("millivolt");
    V->setInitialValue(0.0);

    libcellml::VariablePtr alpha_n = libcellml::Variable::create();
    alpha_n->setName("alpha_n");
    alpha_n->setUnits("per_millisecond");
    alpha_n->setInitialValue(1.0);

    libcellml::VariablePtr beta_n = libcellml::Variable::create();
    beta_n->setName("beta_n");
    beta_n->setUnits("per_millisecond");
    beta_n->setInitialValue(2.0);

    libcellml::VariablePtr n = libcellml::Variable::create();
    n->setName("n");
    n->setUnits("dimensionless");
    n->setInitialValue(1.0);

    libcellml::VariablePtr E_K = libcellml::Variable::create();
    E_K->setName("E_K");
    E_K->setUnits("millivolt");
    E_K->setInitialValue(-85.0);

    libcellml::VariablePtr i_K = libcellml::Variable::create();
    i_K->setName("i_K");
    i_K->setUnits("microA_per_cm2");
    // Note that no initial value is needed for this variable as its value
    // is defined by equation2

    libcellml::VariablePtr g_K = libcellml::Variable::create();
    g_K->setName("g_K");
    g_K->setUnits("milliS_per_cm2");
    g_K->setInitialValue(36.0);

    libcellml::VariablePtr gamma = libcellml::Variable::create();
    gamma->setName("gamma");
    gamma->setUnits("dimensionless");
    gamma->setInitialValue(4.0);

    //  3.c Adding the variables to the component.  Note that Variables are
    //      added by their pointer (cf. their name)
    component->addVariable(t);
    component->addVariable(V);
    component->addVariable(E_K);
    component->addVariable(gamma);
    component->addVariable(i_K);
    component->addVariable(g_K);
    component->addVariable(alpha_n);
    component->addVariable(beta_n);
    component->addVariable(n);

    //  3.d Call the validator and print the messages to the terminal.
    //      Expected errors refer to units refered to by these variables, but
    //      which don't (yet) exist in the model.
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Define the units and add to the model" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  4.a Defining the units of millisecond, millivolt, per_millisecond,
    //      microA_per_cm2, and milliS_per_cm2. Note that the dimensionless
    //      units are part of those built-in already, so do not need to be
    //      defined here.
    libcellml::UnitsPtr ms = libcellml::Units::create();
    ms->setName("millisecond");
    ms->addUnit("second", "milli");

    libcellml::UnitsPtr mV = libcellml::Units::create();
    mV->setName("millivolt");
    mV->addUnit("volt", "milli");

    libcellml::UnitsPtr per_ms = libcellml::Units::create();
    per_ms->setName("per_millisecond");
    per_ms->addUnit("millisecond", -1.0);

    libcellml::UnitsPtr microA_per_cm2 = libcellml::Units::create();
    microA_per_cm2->setName("microA_per_cm2");
    microA_per_cm2->addUnit("ampere", "micro");
    microA_per_cm2->addUnit("metre", "centi", -2.0);

    libcellml::UnitsPtr mS_per_cm2 = libcellml::Units::create();
    mS_per_cm2->setName("milliS_per_cm2");
    mS_per_cm2->addUnit("siemens", "milli");
    mS_per_cm2->addUnit("metre", "centi", -2.0);

    //  4.b Add these units into the model
    model->addUnits(ms);
    model->addUnits(mV);
    model->addUnits(per_ms);
    model->addUnits(microA_per_cm2);
    model->addUnits(mS_per_cm2);

    //  4.c Validate the final arrangement.  No errors are expected at this stage.
    validator.validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Serialise and print the model" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    libcellml::Printer printer;
    std::string serialisedModelString = printer.printModel(model);
    std::string outFileName = "tutorial4_IonChannelModel.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The created '" << model->name()
              << "' model has been printed to: " << outFileName << std::endl;



}