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

#include "../utilities/tutorial_utilities.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 1: Create the model and component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a   Create the model instance
    auto model = libcellml::Model::create("Tutorial4_FirstOrderModel");

    //  1.b   Create a component and add it into the model
    auto component = libcellml::Component::create("IonChannel");
    model->addComponent(component);

    //  1.c   Call the validator and print the messages to the terminal.
    //        No errors are expected at this stage.
    auto validator = libcellml::Validator::create();
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Define the mathematical behaviour" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a   Define the mathematics.
    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n";

    // dy/dt = alpha_y*(1-y) - beta_y*y
    std::string equation1 =
        "<apply>\n"
        "    <eq/>\n"
        "    <apply>\n"
        "        <diff/>\n"
        "        <bvar>\n"
        "            <ci>t</ci>\n"
        "        </bvar>\n"
        "        <ci>n</ci>\n"
        "    </apply>\n"
        "    <apply>\n"
        "        <minus/>\n"
        "        <apply>\n"
        "            <times/>\n"
        "            <ci>alpha_n</ci>\n"
        "            <apply>\n"
        "                <minus/>\n"
        "                <cn cellml:units=\"dimensionless\">1</cn>\n"
        "                <ci>n</ci>\n"
        "            </apply>\n"
        "        </apply>\n"
        "        <apply>\n"
        "            <times/>\n"
        "            <ci>beta_n</ci>\n"
        "            <ci>n</ci>\n"
        "        </apply>\n"
        "    </apply>\n"
        "</apply>";
    // i_y = g_y*power(y,gamma)*(V-E_y)
    std::string equation2 =
        "<apply>\n"
        "    <eq/>\n"
        "    <ci>i_K</ci>\n"
        "    <apply>\n"
        "        <times/>\n"
        "        <ci>g_K</ci>\n"
        "        <apply>\n"
        "            <minus/>\n"
        "            <ci>V</ci>\n"
        "            <ci>E_K</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "            <power/>\n"
        "            <ci>n</ci>\n"
        "            <ci>gamma</ci>\n"
        "        </apply>\n"
        "    </apply>\n"
        "</apply>\n";
    std::string mathFooter = "</math>";

    //  2.b   Add the maths to the component.  Note that there is only one maths
    //        string stored, so parts which are appended must create a viable
    //        MathML2 string when concantenated.  To clear any string which is
    //        already stored, simply call setMath("") with an empty string.
    component->setMath(mathHeader);
    component->appendMath(equation1);
    component->appendMath(equation2);
    component->appendMath(mathFooter);

    //  2.c:  Call the validator and print the messages to the terminal.
    //        Expected errors refer to variables referenced in the maths which
    //        are not (yet) defined in the component, as well as cn element units
    //        which are not defined yet either.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Define the variables and their units" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a,b Declaring the variables, their names, units, and initial conditions
    //        Note that the names given to variables must be the same as that used
    //        within the <ci> blocks in the MathML string we created in step 2.a.

    auto t = libcellml::Variable::create("t");
    t->setUnits("millisecond");

    auto V = libcellml::Variable::create("V");
    V->setUnits("millivolt");

    auto alpha_n = libcellml::Variable::create("alpha_n");
    alpha_n->setUnits("per_millisecond");

    auto beta_n = libcellml::Variable::create("beta_n");
    beta_n->setUnits("per_millisecond");

    auto n = libcellml::Variable::create("n");
    n->setUnits("dimensionless");

    auto E_K = libcellml::Variable::create("E_K");
    E_K->setUnits("millivolt");

    auto i_K = libcellml::Variable::create("i_K");
    i_K->setUnits("microA_per_cm2");

    auto g_K = libcellml::Variable::create("g_K");
    g_K->setUnits("milliS_per_cm2");

    auto gamma = libcellml::Variable::create("gamma");
    gamma->setUnits("dimensionless");

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
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Define the units and add to the model" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  4.a Defining the units of millisecond, millivolt, per_millisecond,
    //      microA_per_cm2, and milliS_per_cm2. Note that the dimensionless
    //      units are part of those built-in already, so do not need to be
    //      defined here.
    auto ms = libcellml::Units::create("millisecond");
    ms->addUnit("second", "milli");

    auto mV = libcellml::Units::create("millivolt");
    mV->addUnit("volt", "milli");

    auto per_ms = libcellml::Units::create("per_millisecond");
    per_ms->addUnit("millisecond", -1.0);

    auto microA_per_cm2 = libcellml::Units::create("microA_per_cm2");
    microA_per_cm2->addUnit("ampere", "micro");
    microA_per_cm2->addUnit("metre", "centi", -2.0);

    auto mS_per_cm2 = libcellml::Units::create("milliS_per_cm2");
    mS_per_cm2->addUnit("siemens", "milli");
    mS_per_cm2->addUnit("metre", "centi", -2.0);

    //  4.b Add these units into the model
    model->addUnits(ms);
    model->addUnits(mV);
    model->addUnits(per_ms);
    model->addUnits(microA_per_cm2);
    model->addUnits(mS_per_cm2);

    //  4.c Validate the final arrangement.  No errors are expected at this stage.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Set the initial conditions" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  5.a Finally we can set the initial conditions for the simulation.  Note that
    //      variables of integration (VOI, in this case, time, t) must not be
    //      initialised; to do so will cause an error to be returned from the Generator
    //      later.  Variables whose value can be calculated from the equations
    //      do not need to be initialised either.
    V->setInitialValue(0.0);
    alpha_n->setInitialValue(1.0);
    beta_n->setInitialValue(2.0);
    n->setInitialValue(1.0);
    E_K->setInitialValue(-85.0);
    g_K->setInitialValue(36.0);
    gamma->setInitialValue(4.0);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 6: Output the model" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  6.a Create a Generator item, set the profile (that is, the output
    //      language) to your choice of C (the default) or Python (see below), and
    //      submit the model for processing.
    auto generator = libcellml::Generator::create();
    generator->processModel(model);

    //  6.b Check that the Generator has not encountered any errors.
    printErrorsToTerminal(generator);
    assert(generator->errorCount() == 0);

    //  6.c Retrieve the output code from the Generator, remembering
    //      that for output in C you will need both the interfaceCode (the
    //      header file contents) as well as the implementationCode (the source
    //      file contents), whereas for Python you need only output the
    //      implementationCode.  Write the file(s).
    std::ofstream outFile("tutorial5_IonChannelModel_generated.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial5_IonChannelModel_generated.c");
    outFile << generator->implementationCode();
    outFile.close();

    auto profile =
        libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);
    generator->processModel(model);

    outFile.open("tutorial5_IonChannelModel_generated.py");
    outFile << generator->implementationCode();
    outFile.close();

    //  6.d Create a Printer item and submit your model for serialisation.
    auto printer = libcellml::Printer::create();
    std::string serialisedModelString = printer->printModel(model);

    //  6.e Write the serialised string output from the printer to a file.
    std::string outFileName = "tutorial5_IonChannelModel.cellml";
    outFile.open(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The created '" << model->name()
              << "' model has been printed to: " << outFileName << std::endl;

    //  6.f Please see the instructions for how to run your simulation using
    //      the simple solver provided.  Then go and have a cuppa, you're done!
}
