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
    //  0 Setup stuff that is used throughout
    auto validator = libcellml::Validator::create();
    auto model = libcellml::Model::create("Tutorial7_SodiumChannelModel");

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n";
    std::string mathFooter = "</math>";

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << " STEP 1: Creating the sodium channel component " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a Create the compont instance, name it, and add to the model
    auto sodiumChannel = libcellml::Component::create();
    sodiumChannel->setName("sodiumChannel");
    model->addComponent(sodiumChannel);

    //  1.b Add the MathML representing the governing equations
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

    //  1.c Add the variables
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

    //  1.d Add the units
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

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Creating the m-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a Create the component and add it to the sodium channel component
    auto mGate = libcellml::Component::create("mGate");
    sodiumChannel->addComponent(mGate);

    //  2.b Add the MathML strings which govern the behaviour of this gate
    {
        std::string equation1 =
            "  <apply><eq/>\n"
            "    <ci>alpha_m</ci>\n"
            "    <apply><divide/>\n"
            "      <apply><times/>\n"
            "        <apply><minus/>\n"
            "          <cn cellml:units=\"per_mV_ms\">0.1</cn>\n"
            "        </apply>\n"
            "        <apply><plus/>\n"
            "          <ci>V</ci>\n"
            "          <cn cellml:units=\"mV\">50</cn>\n"
            "        </apply>\n"
            "      </apply>\n"
            "      <apply><minus/>\n"
            "        <apply><exp/>\n"
            "          <apply><divide/>\n"
            "            <apply><minus/>\n"
            "              <apply><plus/>\n"
            "                <ci>V</ci>\n"
            "                <cn cellml:units=\"mV\">50</cn>\n"
            "              </apply>\n"
            "            </apply>\n"
            "            <cn cellml:units=\"mV\">10</cn>\n"
            "          </apply>\n"
            "        </apply>\n"
            "        <cn cellml:units=\"dimensionless\">1</cn>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        std::string equation2 =
            "  <apply><eq/>\n"
            "    <ci>beta_m</ci>\n"
            "    <apply><times/>\n"
            "      <cn cellml:units=\"per_ms\">4</cn>\n"
            "      <apply><exp/>\n"
            "        <apply><divide/>\n"
            "          <apply><minus/>\n"
            "            <apply><plus/>\n"
            "              <ci>V</ci>\n"
            "              <cn cellml:units=\"mV\">75</cn>\n"
            "            </apply>\n"
            "          </apply>\n"
            "          <cn cellml:units=\"mV\">18</cn>\n"
            "        </apply>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        std::string equation3 =
            "  <apply><eq/>\n"
            "    <apply><diff/>\n"
            "      <bvar>\n"
            "        <ci>t</ci>\n"
            "      </bvar>\n"
            "      <ci>m</ci>\n"
            "    </apply>\n"
            "    <apply><minus/>\n"
            "      <apply><times/>\n"
            "        <ci>alpha_m</ci>\n"
            "        <apply><minus/>\n"
            "          <cn cellml:units=\"dimensionless\">1</cn>\n"
            "          <ci>m</ci>\n"
            "        </apply>\n"
            "      </apply>\n"
            "      <apply><times/>\n"
            "        <ci>m</ci>\n"
            "        <ci>beta_m</ci>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        mGate->setMath(mathHeader);
        mGate->appendMath(equation1);
        mGate->appendMath(equation2);
        mGate->appendMath(equation3);
        mGate->appendMath(mathFooter);

    } // end scope of maths for mGate component

    //  2.c Call the validator - expect errors related to missing variables, then
    //      add the variables needed
    validator->validateModel(model);
    printErrorsToTerminal(validator);
    {
        auto V = libcellml::Variable::create("V");
        V->setUnits("mV");
        mGate->addVariable(V);

        auto t = libcellml::Variable::create("t");
        t->setUnits("ms");
        mGate->addVariable(t);

        auto alpha_m = libcellml::Variable::create("alpha_m");
        alpha_m->setUnits("per_ms");
        mGate->addVariable(alpha_m);

        auto beta_m = libcellml::Variable::create("beta_m");
        beta_m->setUnits("per_ms");
        mGate->addVariable(beta_m);

        auto m = libcellml::Variable::create("m");
        m->setUnits("dimensionless");
        mGate->addVariable(m);
    } // ends local scope for mGate component

    //  2.d Call the validator to check the model - expect errors related to
    //      units missing from the model.  Add them in as needed.
    auto per_mV_ms = libcellml::Units::create("per_mV_ms");
    per_mV_ms->addUnit("second", "milli", -1);
    per_mV_ms->addUnit("volt", "milli", -1);
    model->addUnits(per_mV_ms);

    auto per_ms = libcellml::Units::create("per_ms");
    per_ms->addUnit("second", "milli", -1);
    model->addUnits(per_ms);

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Creating the h-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a Create the hGate component and add it to the sodium channel component
    auto hGate = libcellml::Component::create("hGate");
    sodiumChannel->addComponent(hGate);

    //  3.b Adding the MathML strings
    {
        std::string equation1 =
            "  <apply><eq/>\n"
            "    <ci>alpha_h</ci>\n"
            "    <apply><times/>\n"
            "      <cn cellml:units=\"per_ms\">0.07</cn>\n"
            "      <apply><exp/>\n"
            "        <apply><divide/>\n"
            "          <apply><minus/>\n"
            "            <apply><plus/>\n"
            "              <ci>V</ci>\n"
            "              <cn cellml:units=\"mV\">75</cn>\n"
            "            </apply>\n"
            "          </apply>\n"
            "          <cn cellml:units=\"mV\">20</cn>\n"
            "        </apply>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        std::string equation2 =
            "  <apply><eq/>\n"
            "    <ci>beta_h</ci>\n"
            "    <apply><divide/>\n"
            "      <cn cellml:units=\"per_ms\">1</cn>\n"
            "      <apply><plus/>\n"
            "        <apply><exp/>\n"
            "          <apply><divide/>\n"
            "            <apply><minus/>\n"
            "              <apply><plus/>\n"
            "                <ci>V</ci>\n"
            "                <cn cellml:units=\"mV\">45</cn>\n"
            "              </apply>\n"
            "            </apply>\n"
            "            <cn cellml:units=\"mV\">10</cn>\n"
            "          </apply>\n"
            "        </apply>\n"
            "        <cn cellml:units=\"dimensionless\">1</cn>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        std::string equation3 =
            "  <apply><eq/>\n"
            "    <apply><diff/>\n"
            "       <bvar>\n"
            "         <ci>t</ci>\n"
            "       </bvar>\n"
            "       <ci>h</ci>\n"
            "    </apply>\n"
            "    <apply><minus/>\n"
            "      <apply><times/>\n"
            "        <ci>alpha_h</ci>\n"
            "        <apply><minus/>\n"
            "          <cn cellml:units=\"dimensionless\">1</cn>\n"
            "          <ci>h</ci>\n"
            "        </apply>\n"
            "      </apply>\n"
            "      <apply><times/>\n"
            "        <ci>h</ci>\n"
            "        <ci>beta_h</ci>\n"
            "      </apply>\n"
            "    </apply>\n"
            "  </apply>\n";

        hGate->setMath(mathHeader);
        hGate->appendMath(equation1);
        hGate->appendMath(equation2);
        hGate->appendMath(equation3);
        hGate->appendMath(mathFooter);
    } // ends local scope for hGate maths

    //  3.c Add the variables
    {
        auto V = libcellml::Variable::create("V");
        V->setUnits("mV");
        hGate->addVariable(V);

        auto t = libcellml::Variable::create("t");
        t->setUnits("ms");
        hGate->addVariable(t);

        auto alpha_h = libcellml::Variable::create("alpha_h");
        alpha_h->setUnits("per_ms");
        hGate->addVariable(alpha_h);

        auto beta_h = libcellml::Variable::create("beta_h");
        beta_h->setUnits("per_ms");
        hGate->addVariable(beta_h);

        auto h = libcellml::Variable::create("h");
        h->setUnits("dimensionless");
        hGate->addVariable(h);
    } // ends local scope for hGate variables

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Creating the environment component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  4.a Create the new environment component
    auto environment = libcellml::Component::create("environment");
    model->addComponent(environment);

    //  4.b Add variables to the component.
    {
        auto V = libcellml::Variable::create("V");
        V->setUnits("mV");
        environment->addVariable(V);

        auto t = libcellml::Variable::create("t");
        t->setUnits("ms");
        environment->addVariable(t);
    } // end of the environment scope for variables

    //  4.c Validate
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 5: Connecting variables and components" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  5.a Connecting the equivalent variables between all the components
    libcellml::Variable::addEquivalence(environment->variable("t"), sodiumChannel->variable("t"));
    libcellml::Variable::addEquivalence(sodiumChannel->variable("t"), mGate->variable("t"));
    libcellml::Variable::addEquivalence(sodiumChannel->variable("t"), hGate->variable("t"));
    environment->variable("t")->setInterfaceType("public");
    sodiumChannel->variable("t")->setInterfaceType("public_and_private");
    mGate->variable("t")->setInterfaceType("public");
    hGate->variable("t")->setInterfaceType("public");

    libcellml::Variable::addEquivalence(environment->variable("V"), sodiumChannel->variable("V"));
    libcellml::Variable::addEquivalence(sodiumChannel->variable("V"), mGate->variable("V"));
    libcellml::Variable::addEquivalence(sodiumChannel->variable("V"), hGate->variable("V"));
    environment->variable("V")->setInterfaceType("public");
    sodiumChannel->variable("V")->setInterfaceType("public_and_private");
    mGate->variable("V")->setInterfaceType("public");
    hGate->variable("V")->setInterfaceType("public");

    libcellml::Variable::addEquivalence(sodiumChannel->variable("m"), mGate->variable("m"));
    sodiumChannel->variable("m")->setInterfaceType("private");
    mGate->variable("m")->setInterfaceType("public");

    libcellml::Variable::addEquivalence(sodiumChannel->variable("h"), hGate->variable("h"));
    sodiumChannel->variable("h")->setInterfaceType("private");
    hGate->variable("h")->setInterfaceType("public");

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   STEP 6: Set the driving function" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  6.a Create the MathML controlling the driving function
    {
        std::string voltageClampMaths =
            "  <apply><eq/>\n"
            "    <ci>V</ci>\n"
            "    <piecewise>\n"
            "      <piece>\n"
            "        <cn cellml:units=\"mV\">-85</cn>\n"
            "        <apply><lt/><ci>t</ci><cn cellml:units=\"ms\">5</cn></apply>\n"
            "      </piece>\n"
            "      <piece>\n"
            "        <cn cellml:units=\"mV\">-85</cn>\n"
            "        <apply><gt/><ci>t</ci><cn cellml:units=\"ms\">15</cn></apply>\n"
            "      </piece>\n"
            "      <otherwise>\n"
            "        <cn cellml:units=\"mV\">-20</cn>\n"
            "      </otherwise>\n"
            "    </piecewise>\n"
            "  </apply>\n";
        environment->setMath(mathHeader);
        environment->appendMath(voltageClampMaths);
        environment->appendMath(mathFooter);
    }

    //  6.b Validate the final model
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 7: Generate and initialise " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  7.a Create a Generator instance and submit the model for processing.
    //      Expect errors related to uninitialised variables.
    auto generator = libcellml::Generator::create();
    generator->processModel(model);
    printErrorsToTerminal(generator);

    //  7.b Add the initial conditions that are required.
    //          g_Na(t=0) = 120
    //          E_Na(t=0) = 35
    //          h(t=0)=0.6
    //          m(t=0)=0.05
    sodiumChannel->variable("g_Na")->setInitialValue(120);
    sodiumChannel->variable("E_Na")->setInitialValue(35);
    hGate->variable("h")->setInitialValue(0.6);
    mGate->variable("m")->setInitialValue(0.05);

    //  7.c Process the model again and check that it is now free of errors.
    generator->processModel(model);
    printErrorsToTerminal(generator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 8: Output the model " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  8.a Write the interface code (.h header) and implementation code
    //      (.c source) to files.
    std::ofstream outFile;
    outFile.open("tutorial7_SodiumChannelModel.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial7_SodiumChannelModel.c");
    outFile << generator->implementationCode();
    outFile.close();

    //  8.b Create a `GeneratorProfile` and use it to change to Python.
    //      Reprocess the model, and write the implementation code (.py source) to
    //      a file.
    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);
    generator->processModel(model);

    outFile.open("tutorial7_SodiumChannelModel.py");
    outFile << generator->implementationCode();
    outFile.close();

    //  8.c Create a Printer to serialise your model, and output it to a CellML file.
    auto printer = libcellml::Printer::create();
    outFile.open("tutorial7_SodiumChannelModel.cellml");
    outFile << printer->printModel(model);
    outFile.close();

    std::cout << "The model has been output into tutorial7_SodiumChannelModel.[c,h,py,cellml]"
              << std::endl;

    //  8.d Please seen the tutorial instructions for how to run this simulation using
    //      the simple solver provided.  Then go and have a cuppa, you're done!
}
