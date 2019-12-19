/**
 *      TUTORIAL 7: Creating the Sodium Channel
 *  This tutorial is an opportunity to practise creating models from
 *  scratch using the libCellML API.  The model you create here will
 *  be used later on in Tutorial ??.
 *
 *  Tutorial 7 assumes that you are already comfortable with:
 *    - the concept of component hierarchy and encapsulation (Tutorial 5)
 *    - the use of the API to create all of the entities in a model (Tutorial 3)
 *    - the content MathML2 markup for mathematical equations (Tutorial 4)
 *    - serialisation and printing of a model to a CellML file (Tutorial 1)
 */

#include <iostream>
#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main()
{
    //  0 Setup stuff that is used throughout
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("Tutorial7_SodiumChannelModel");

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << " STEP 1: Creating the sodium channel component " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  1.a Create the compont instance, name it, and add to the model
    libcellml::ComponentPtr sodiumChannel = libcellml::Component::create();
    sodiumChannel->setName("sodiumChannel");
    model->addComponent(sodiumChannel);

    //  1.b Add the MathML representing the governing equations
    {
        std::string equation1 =
            "<apply><eq/>\
                <ci>Na_conductance</ci>\
                <apply><times/>\
                    <ci>g_Na</ci>\
                    <ci>h</ci>\
                    <apply><power/>\
                        <ci>m</ci>\
                        <cn cellml:units=\"dimensionless\">3</cn>\
                    </apply>\
                </apply>\
            </apply>";

        std::string equation2 =
            "<apply><eq/>\
                <ci>i_Na</ci>\
                <apply><times/>\
                    <ci>Na_conductance</ci>\
                    <apply><minus/>\
                        <ci>V</ci>\
                        <ci>E_Na</ci>\
                    </apply>\
                </apply>\
            </apply>";

        sodiumChannel->setMath(mathHeader);
        sodiumChannel->appendMath(equation1);
        sodiumChannel->appendMath(equation2);
        sodiumChannel->appendMath(mathFooter);
    }

    //  1.c Add the variables
    {
        libcellml::VariablePtr V = libcellml::Variable::create();
        V->setName("V");
        V->setUnits("mV");
        sodiumChannel->addVariable(V);

        libcellml::VariablePtr t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("ms");
        sodiumChannel->addVariable(t);

        libcellml::VariablePtr h = libcellml::Variable::create();
        h->setName("h");
        h->setUnits("dimensionless");
        sodiumChannel->addVariable(h);

        libcellml::VariablePtr m = libcellml::Variable::create();
        m->setName("m");
        m->setUnits("dimensionless");
        sodiumChannel->addVariable(m);

        libcellml::VariablePtr g_Na = libcellml::Variable::create();
        g_Na->setName("g_Na");
        g_Na->setUnits("mS_per_cm2");

        sodiumChannel->addVariable(g_Na);

        libcellml::VariablePtr E_Na = libcellml::Variable::create();
        E_Na->setName("E_Na");
        E_Na->setUnits("mV");
        sodiumChannel->addVariable(E_Na);

        libcellml::VariablePtr i_Na = libcellml::Variable::create();
        i_Na->setName("i_Na");
        i_Na->setUnits("microA_per_cm2");
        sodiumChannel->addVariable(i_Na);

        libcellml::VariablePtr Na_conductance = libcellml::Variable::create();
        Na_conductance->setName("Na_conductance");
        Na_conductance->setUnits("mS_per_cm2");
        sodiumChannel->addVariable(Na_conductance);
    }

    //  1.d Add the units

    libcellml::UnitsPtr mV = libcellml::Units::create();
    mV->setName("mV");
    mV->addUnit("volt", "milli");
    model->addUnits(mV);

    libcellml::UnitsPtr ms = libcellml::Units::create();
    ms->setName("ms");
    ms->addUnit("second", "milli");
    model->addUnits(ms);

    libcellml::UnitsPtr mS_per_cm2 = libcellml::Units::create();
    mS_per_cm2->setName("mS_per_cm2");
    mS_per_cm2->addUnit("siemens", "milli");
    mS_per_cm2->addUnit("metre", "centi", -2);
    model->addUnits(mS_per_cm2);

    libcellml::UnitsPtr microA_per_cm2 = libcellml::Units::create();
    microA_per_cm2->setName("microA_per_cm2");
    microA_per_cm2->addUnit("ampere", "micro");
    microA_per_cm2->addUnit("metre", "centi", -2);
    model->addUnits(microA_per_cm2);

    libcellml::UnitsPtr mM = libcellml::Units::create();
    mM->setName("mM");
    mM->addUnit("mole", "milli");
    model->addUnits(mM);

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 2: Creating the m-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  2.a Create the component and add it to the sodium channel component
    libcellml::ComponentPtr mGate = libcellml::Component::create();
    mGate->setName("mGate");
    sodiumChannel->addComponent(mGate);

    //  2.b Add the MathML strings which govern the behavior of this gate
    {
        std::string equation1 =
            "<apply><eq/>\
                <ci>alpha_m</ci>\
                <apply><divide/>\
                    <apply><times/>\
                        <apply><minus/>\
                            <cn cellml:units=\"per_mV_ms\">0.1</cn>\
                        </apply>\
                        <apply><plus/>\
                            <ci>V</ci>\
                            <cn cellml:units=\"mV\">50</cn>\
                        </apply>\
                    </apply>\
                    <apply><minus/>\
                        <apply><exp/>\
                            <apply><divide/>\
                                <apply><minus/>\
                                    <apply><plus/>\
                                        <ci>V</ci>\
                                        <cn cellml:units=\"mV\">50</cn>\
                                    </apply>\
                                </apply>\
                                <cn cellml:units=\"mV\">10</cn>\
                            </apply>\
                        </apply>\
                        <cn cellml:units=\"dimensionless\">1</cn>\
                    </apply>\
                </apply>\
            </apply>";

        std::string equation2 =
            "<apply><eq/>\
                <ci>beta_m</ci>\
                <apply><times/>\
                    <cn cellml:units=\"per_ms\">4</cn>\
                    <apply><exp/>\
                        <apply><divide/>\
                            <apply><minus/>\
                                <apply><plus/>\
                                    <ci>V</ci>\
                                    <cn cellml:units=\"mV\">75</cn>\
                                </apply>\
                            </apply>\
                            <cn cellml:units=\"mV\">18</cn>\
                        </apply>\
                    </apply>\
                </apply>\
            </apply>";

        std::string equation3 =
            "<apply><eq/>\
                <apply><diff/>\
                    <bvar>\
                        <ci>t</ci>\
                    </bvar>\
                    <ci>m</ci>\
                </apply>\
                <apply><minus/>\
                    <apply><times/>\
                        <ci>alpha_m</ci>\
                        <apply><minus/>\
                            <cn cellml:units=\"dimensionless\">1</cn>\
                            <ci>m</ci>\
                        </apply>\
                    </apply>\
                    <apply><times/>\
                        <ci>m</ci>\
                        <ci>beta_m</ci>\
                    </apply>\
                </apply>\
            </apply>";

        mGate->setMath(mathHeader);
        mGate->appendMath(equation1);
        mGate->appendMath(equation2);
        mGate->appendMath(equation3);
        mGate->appendMath(mathFooter);

    } // end scope of maths for mGate component

    //  2.c Call the validator - expect errors related to missing variables, then
    //      add the variables needed

    {
        libcellml::VariablePtr V = libcellml::Variable::create();
        V->setName("V");
        V->setUnits("mV");
        mGate->addVariable(V);

        libcellml::VariablePtr t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("ms");
        mGate->addVariable(t);

        libcellml::VariablePtr alpha_m = libcellml::Variable::create();
        alpha_m->setName("alpha_m");
        alpha_m->setUnits("per_ms");
        mGate->addVariable(alpha_m);

        libcellml::VariablePtr beta_m = libcellml::Variable::create();
        beta_m->setName("beta_m");
        beta_m->setUnits("per_ms");
        mGate->addVariable(beta_m);

        libcellml::VariablePtr m = libcellml::Variable::create();
        m->setName("m");
        m->setUnits("dimensionless");

        mGate->addVariable(m);
    } // ends local scope for mGate component

    //  2.d Call the validator to check the model - expect errors related to
    //      units missing from the model.  Add them in as needed.

    libcellml::UnitsPtr per_mV_ms = libcellml::Units::create();
    per_mV_ms->setName("per_mV_ms");
    per_mV_ms->addUnit("second", "milli", -1);
    per_mV_ms->addUnit("volt", "milli", -1);
    model->addUnits(per_mV_ms);

    libcellml::UnitsPtr per_ms = libcellml::Units::create();
    per_ms->setName("per_ms");
    per_ms->addUnit("second", "milli", -1);
    model->addUnits(per_ms);

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 3: Creating the h-gate" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  3.a Create the hGate component and add it to the sodium channel component
    libcellml::ComponentPtr hGate = libcellml::Component::create();
    hGate->setName("hGate");
    sodiumChannel->addComponent(hGate);

    //  3.b Adding the MathML strings
    {
        std::string equation1 =
            "<apply><eq/>\
                <ci>alpha_h</ci>\
                <apply><times/>\
                    <cn cellml:units=\"per_ms\">0.07</cn>\
                    <apply><exp/>\
                        <apply><divide/>\
                            <apply><minus/>\
                                <apply><plus/>\
                                    <ci>V</ci>\
                                    <cn cellml:units=\"mV\">75</cn>\
                                </apply>\
                            </apply>\
                            <cn cellml:units=\"mV\">20</cn>\
                        </apply>\
                    </apply>\
                </apply>\
            </apply>";

        std::string equation2 =
            "<apply><eq/>\
                <ci>beta_h</ci>\
                <apply><divide/>\
                    <cn cellml:units=\"per_ms\">1</cn>\
                    <apply><plus/>\
                        <apply><exp/>\
                            <apply><divide/>\
                                <apply><minus/>\
                                    <apply><plus/>\
                                        <ci>V</ci>\
                                        <cn cellml:units=\"mV\">45</cn>\
                                    </apply>\
                                </apply>\
                                <cn cellml:units=\"mV\">10</cn>\
                            </apply>\
                        </apply>\
                        <cn cellml:units=\"dimensionless\">1</cn>\
                    </apply>\
                </apply>\
            </apply>";

        std::string equation3 =
            "<apply><eq/>\
                <apply><diff/>\
                    <bvar>\
                        <ci>t</ci>\
                    </bvar>\
                    <ci>h</ci>\
                </apply>\
                <apply><minus/>\
                    <apply><times/>\
                        <ci>alpha_h</ci>\
                        <apply><minus/>\
                            <cn cellml:units=\"dimensionless\">1</cn>\
                            <ci>h</ci>\
                        </apply>\
                    </apply>\
                    <apply><times/>\
                        <ci>h</ci>\
                        <ci>beta_h</ci>\
                    </apply>\
                </apply>\
            </apply>";

        hGate->setMath(mathHeader);
        hGate->appendMath(equation1);
        hGate->appendMath(equation2);
        hGate->appendMath(equation3);
        hGate->appendMath(mathFooter);
    } // ends local scope for hGate maths

    //  3.c Adding the variables
    {
        libcellml::VariablePtr V = libcellml::Variable::create();
        V->setName("V");
        V->setUnits("mV");
        hGate->addVariable(V);

        libcellml::VariablePtr t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("ms");
        hGate->addVariable(t);

        libcellml::VariablePtr alpha_h = libcellml::Variable::create();
        alpha_h->setName("alpha_h");
        alpha_h->setUnits("per_ms");
        hGate->addVariable(alpha_h);

        libcellml::VariablePtr beta_h = libcellml::Variable::create();
        beta_h->setName("beta_h");
        beta_h->setUnits("per_ms");
        hGate->addVariable(beta_h);

        libcellml::VariablePtr h = libcellml::Variable::create();
        h->setName("h");
        h->setUnits("dimensionless");
        hGate->addVariable(h);
    } // ends local scope for hGate variables

    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  STEP 4: Creating the environment component" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //  4.a Creating the new environment component
    libcellml::ComponentPtr environment = libcellml::Component::create();
    environment->setName("environment");

    //  4.b Add variables to the component.
    {
        libcellml::VariablePtr V = libcellml::Variable::create();
        V->setName("V");
        V->setUnits("mV");
        environment->addVariable(V);

        libcellml::VariablePtr t = libcellml::Variable::create();
        t->setName("t");
        t->setUnits("ms");
        environment->addVariable(t);
    } // end of the environment scope for variables

    //  4.c Add the new component to the model and validate
    model->addComponent(environment);

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
            "<apply><eq/>\
                <ci>V</ci>\
                <piecewise>\
                    <piece>\
                        <cn cellml:units=\"mV\">-85</cn>\
                        <apply><lt/><ci>t</ci><cn cellml:units=\"ms\">5</cn></apply>\
                    </piece>\
                        <piece>\
                        <cn cellml:units=\"mV\">-85</cn>\
                        <apply><gt/><ci>t</ci><cn cellml:units=\"ms\">15</cn></apply>\
                    </piece>\
                    <otherwise>\
                        <cn cellml:units=\"mV\">-20</cn>\
                    </otherwise>\
                </piecewise>\
            </apply>";
        environment->setMath(mathHeader);
        environment->appendMath(voltageClampMaths);
        environment->appendMath(mathFooter);
    }

    //  6.b Validate the final model
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 7: Set the initial conditions " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    sodiumChannel->variable("g_Na")->setInitialValue(120);
    sodiumChannel->variable("E_Na")->setInitialValue(35);
    hGate->variable("h")->setInitialValue(0.6);
    mGate->variable("m")->setInitialValue(0.05);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "    STEP 8: Generate and output the model " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    libcellml::GeneratorPtr generator = libcellml::Generator::create();
    generator->processModel(model);
    printErrorsToTerminal(generator);

    std::ofstream outFile;
    outFile.open("tutorial7_SodiumChannelModel.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial7_SodiumChannelModel.c");
    outFile << generator->implementationCode();
    outFile.close();

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);
    generator->processModel(model);

    outFile.open("tutorial7_SodiumChannelModel.py");
    outFile << generator->implementationCode();
    outFile.close();

    libcellml::PrinterPtr printer=libcellml::Printer::create();
    outFile.open("tutorial7_SodiumChannelModel.cellml");
    outFile << printer->printModel(model);
    outFile.close();

    std::cout << "The model has been output into tutorial7_SodiumChannelModel.[c,h,py,cellml]"
              << std::endl;

}
