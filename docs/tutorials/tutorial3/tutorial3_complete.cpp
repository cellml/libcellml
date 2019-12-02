/**
 *  TUTORIAL 3: MODEL CREATION THROUGH THE API
 *
 *  By the time you have worked through Tutorial 3 you will be able to:
 *    - create a new model and its child entities from scratch using the API
 *    - define custom combinations of built-in units
 *    - define your own custom units independent from the built-in units
 *
 *  This tutorial assumes that you are comfortable with:
 *    - accessing and adjusting names of items inside a model hierarchy (T2)
 *    - creating a validator and using it to check a model for errors (T2)
 *    - accessing the errors produced by a validator and using them to correct
 *      the model (T2)
 *    - serialising and printing a model to a CellML file (T1)
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "   TUTORIAL 3: CREATE A MODEL USING THE API" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 1: Create the model instance
    //
    //  1.a   Create the ModelPtr
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("tutorial_3_model");
    model->setId("tutorial_3_model_id");

    //  Check that it worked
    std::cout << "Model has name: '" << model->name() << "'" << std::endl;
    std::cout << "Model has id: '" << model->id() << "'" << std::endl;

    //  1.b   Create a component to use as an integrator, set its attributes and
    //        add it to the model
    libcellml::ComponentPtr component = libcellml::Component::create();
    component->setName("distance_finder");
    model->addComponent(component);

    //  Check that it worked
    std::cout << "Model has " << model->componentCount()
              << " components:" << std::endl;
    for (size_t c = 0; c < model->componentCount(); ++c) {
        std::cout << "  Component [" << c << "] has name: '"
                  << model->component(c)->name() << "'" << std::endl;
        std::cout << "  Component [" << c << "] has id: '"
                  << model->component(c)->id() << "'" << std::endl;
    }

    //  1.c,d Create the MathML2 string representing the governing equation
    std::string equation = "<apply><eq/>\
                                <apply><diff/>\
                                    <bvar>\
                                        <ci>t</ci>\
                                    </bvar>\
                                    <ci>x</ci>\
                                </apply>\
                                <apply><plus/>\
                                    <apply><times/>\
                                        <ci>a</ci>\
                                        <ci>x</ci>\
                                    </apply>\
                                    <ci>b</ci>\
                                </apply>\
                            </apply>";

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

    //  1.e   Include the MathML strings in the component
    component->setMath(mathHeader);
    component->appendMath(equation);
    component->appendMath(mathFooter);

    //  1.f   Create a validator and use it to check the model so far.
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  1.g   Create some variables and add them to the component
    libcellml::VariablePtr time = libcellml::Variable::create();
    libcellml::VariablePtr distance = libcellml::Variable::create();

    time->setName("t");
    distance->setName("x");

    component->addVariable(time);
    component->addVariable(distance);

    //  1.e   Assign units to the variables
    time->setUnits("millisecond");
    distance->setUnits("league");

    //  Check that it all worked
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "         Printing the model at Step 1" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    printModelToTerminal(model);

    validator->validateModel(model);
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  Printing the validation errors after Step 1" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    printErrorsToTerminal(validator);

    // ---------------------------------------------------------------------------
    //  STEP 2: Create the user-defined units
    //
    //  From the validation errors printed above you'll see that none of the three
    //  units we need are built-in. The good news is that we can create the ones
    //  we need from the set of built-in units, we just need to define the
    //  relationship.  NB: Even though units are used by Variables, which sit
    //  'inside' Components, Units sit inside the Model itself.  This helps you to
    //  reuse Units when you have more than one component (more on that in
    //  Tutorial 5)

    //  2.a   Define the relationship between our custom units and the built-in
    //        units. There is a list of built-in units and their definitions
    //        available in section 19.s of the CellML2 specification.

    libcellml::UnitsPtr millisecond = libcellml::Units::create();
    millisecond->setName("millisecond");
    millisecond->addUnit(
        "second",
        "milli");
    // second is a built-in unit, used inside millisecond with the
    // prefix "milli".  NB this is equivalent to specifying a prefix
    // integer value of -3, corresponding to the power of 10 by
    // which the base is multiplied.

    libcellml::UnitsPtr league = libcellml::Units::create();
    league->setName("league");
    league->addUnit(
        "metre", 3, 1.0,
        5.556);
    // metre is a built-in unit.  A league is equal to 5556m, but here
    // we illustrate the overloaded function by passing a prefix of 3
    // (indicating a factor of 10^3), an exponent of 1, and a
    // multiplier of 5.556.

    //  2.b   Add the units to the model
    model->addUnits(millisecond);
    model->addUnits(league);

    //  2.c   Validate the model again
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  2.d  Change the constant "b" to have a hard-coded value of 5.0 in the MathML
    std::string equation2 = "<apply><eq/>\
                                <apply><diff/>\
                                    <bvar>\
                                        <ci>t</ci>\
                                    </bvar>\
                                    <ci>x</ci>\
                                </apply>\
                                <apply><plus/>\
                                    <cn cellml:units=\"league\">5.0</cn>\
                                    <apply><times/>\
                                        <ci>a</ci>\
                                        <ci>x</ci>\
                                    </apply>\
                                </apply>\
                            </apply>";
    component->setMath(mathHeader);
    component->appendMath(equation2);
    component->appendMath(mathFooter);

    //  2.e Create and define the constant "a" to have a value of -0.2
    libcellml::VariablePtr a = libcellml::Variable::create();
    a->setName("a");
    a->setUnits("dimensionless");
    a->setInitialValue(-0.2);
    component->addVariable(a);

    validator->validateModel(model);
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "  Printing the validation errors after Step 2  " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    printErrorsToTerminal(validator);

    // ---------------------------------------------------------------------------
    //  STEP 3: Output the model for solving
    //

    //  3.a Create a Generator instance and use it to process the model.  Output
    //      any errors to the terminal using the utility function printErrorsToTerminal
    //      called with your generator as argument.
    libcellml::GeneratorPtr generator = libcellml::Generator::create();
    // generator->processModel(model);
    // printErrorsToTerminal(generator);

    //  3.b Set the initial conditions of the distance variable such that x(t=0)=5 and
    //      check that there are no more errors reported.
    distance->setInitialValue(5.0);
    generator->processModel(model);
    printErrorsToTerminal(generator);

    //  3.c Check that the generator has the settings which we expect:
    //      - the number of variables
    //      - the language of output
    //      - the variable of integration
    //      - the type of model
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "     Investigating the Generator settings" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::cout << "Number of variables = " << generator->variableCount() << std::endl;
    std::cout << "Variable of integration = " << generator->voi()->name() << std::endl;
    std::cout << "Number of states = " << generator->stateCount() << std::endl;
    std::cout << "Model type = " << getModelTypeFromEnum(generator->modelType()) << std::endl;
    // TODO std::cout << "Langauge = " << getProfileFromEnum(generator->profile()) << std::endl;

    //  3.d Create the interface code (*.h file contents) and implementation code (*.c file
    //      contents) and print them to files.

    std::ofstream outFile("tutorial3_generated.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial3_generated.c");
    outFile << generator->implementationCode();
    outFile.close();

    std::cout << "The generated code has been output into tutorial3_generated.c and
                 tutorial3_generated.h." << std::endl;
}
