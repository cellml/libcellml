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

/**
 *  TUTORIAL 3: MODEL CREATION AND GENERATION THROUGH THE API
 *
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
    //  STEP 1: Create the model, component and maths
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
    component->setName("predator_prey_component");
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

    //  1.c,d,e Create the MathML2 strings representing the governing equations
    std::string equation1 =
        "<apply><eq/>"
        "   <ci>c</ci>"
        "   <apply><minus/>"
        "       <ci>a</ci>"
        "       <cn>2.0</cn>"
        "   </apply>"
        "</apply>";
    std::string equation2 =
        "<apply><eq/>"
        "   <apply><diff/>"
        "   <bvar><ci>time</ci></bvar>"
        "   <ci>y_s</ci>"
        "   </apply>"
        "   <apply><plus/>"
        "       <apply><times/>"
        "           <ci>a</ci>"
        "           <ci>y_s</ci>"
        "      </apply>"
        "      <apply><times/>"
        "          <ci>b</ci>"
        "          <ci>y_s</ci>"
        "          <ci>y_f</ci>"
        "      </apply>"
        "   </apply>"
        "</apply>";
    std::string equation3 =
        "<apply><eq/>"
        "   <apply><diff/>"
        "   <bvar><ci>time</ci></bvar>"
        "   <ci>y_f</ci>"
        "   </apply>"
        "   <apply><plus/>"
        "       <apply><times/>"
        "           <ci>c</ci>"
        "           <ci>y_f</ci>"
        "      </apply>"
        "      <apply><times/>"
        "          <ci>d</ci>"
        "          <ci>y_s</ci>"
        "          <ci>y_f</ci>"
        "      </apply>"
        "   </apply>"
        "</apply>";

    std::string mathHeader = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">";
    std::string mathFooter = "</math>";

    //  1.f Add the maths strings in to the component
    component->setMath(mathHeader);
    component->appendMath(equation1);
    component->appendMath(equation2);
    component->appendMath(equation3);
    component->appendMath(mathFooter);

    //  1.g Call the validator and check for error so far.  We expect there to be 20 errors found, related to missing variables
    //      in the component.
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    // ---------------------------------------------------------------------------
    //  STEP 2: Create the variables and add them to the component

    //  2.a Create the variables listed by the validator: d, a, b, c, time, y_s, y_f

    libcellml::VariablePtr sharks = libcellml::Variable::create("y_s");
    libcellml::VariablePtr fish = libcellml::Variable::create("y_f");
    libcellml::VariablePtr time = libcellml::Variable::create("time");
    libcellml::VariablePtr a = libcellml::Variable::create("a");
    libcellml::VariablePtr b = libcellml::Variable::create("b");
    libcellml::VariablePtr c = libcellml::Variable::create("c");
    libcellml::VariablePtr d = libcellml::Variable::create("d");

    //  2.b Add the variables into the component

    component->addVariable(a);
    component->addVariable(b);
    component->addVariable(c);
    component->addVariable(d);
    component->addVariable(sharks);
    component->addVariable(fish);
    component->addVariable(time);

    //  2.c Call the Validator again to check
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    // ---------------------------------------------------------------------------
    //  STEP 3: Create the Units and add them to the model

    //  3.a Create the day and per_day units
    libcellml::UnitsPtr day = libcellml::Units::create("day");
    day->addUnit("second", 0, 1, 86400); // base unit, prefix, exponent, multiplier
    model->addUnits(day);

    libcellml::UnitsPtr per_day = libcellml::Units::create("per_day");
    per_day->addUnit("day", -1); // base unit, exponent
    model->addUnits(per_day);

    //  3.b Create the sharks and fishes base units
    libcellml::UnitsPtr number_of_sharks = libcellml::Units::create("number_of_sharks");
    libcellml::UnitsPtr thousands_of_fish = libcellml::Units::create("thousands_of_fish");
    model->addUnits(number_of_sharks);
    model->addUnits(thousands_of_fish);

    //  3.c Combined units for the constants
    libcellml::UnitsPtr b_units = libcellml::Units::create("per_shark_day");
    b_units->addUnit("per_day");
    b_units->addUnit("number_of_sharks", -1);
    model->addUnits(b_units);

    libcellml::UnitsPtr d_units = libcellml::Units::create("per_1000fish_day");
    d_units->addUnit("per_day");
    d_units->addUnit("thousands_of_fish", -1);
    model->addUnits(d_units);

    //  3.d Add the units to their variables
    time->setUnits(day);
    a->setUnits(per_day);
    b->setUnits(b_units);
    c->setUnits(per_day);
    d->setUnits(d_units);
    sharks->setUnits(number_of_sharks);
    fish->setUnits(thousands_of_fish);

    //  3.e Call the validator to check the model.  We expect one error regarding the missing units in the MathML.
    validator->validateModel(model);
    printErrorsToTerminal(validator);

    //  3.f Units for constants inside the MathML must be specified at the time.  This means we need to adjust
    //      equation1 to include the per_day units.  We have to wipe all the existing MathML and replace it.
    component->removeMath();
    component->setMath(mathHeader);
    equation1 =
        "<apply><eq/>"
        "   <ci>c</ci>"
        "   <apply><minus/>"
        "       <ci>a</ci>"
        "       <cn cellml:units=\"per_day\">2.0</cn>"
        "   </apply>"
        "</apply>";

    component->appendMath(equation1);
    component->appendMath(equation2);
    component->appendMath(equation3);
    component->appendMath(mathFooter);

    //  3.g Expect there to be no errors.
    validator->validateModel(model);
    printErrorsToTerminal(validator);
    assert(validator->errorCount()==0);

    // ---------------------------------------------------------------------------
    //  STEP 4: Code generation

    //  4.a Create a generator instance and pass it the model for processing.  The
    //      default profile is to generate C code, but we can change this later.
    libcellml::GeneratorPtr generator = libcellml::Generator::create();
    generator->processModel(model);

    //  4.b Check for errors found in the generator
    printErrorsToTerminal(generator);

    //  4.c Add initial conditions to all variables except the base variable, time
    //      and the constant c which will be computed. Reprocess the model.
    a->setInitialValue(1.2);
    b->setInitialValue(-0.6);
    d->setInitialValue(0.3);
    sharks->setInitialValue(2.0);
    fish->setInitialValue(1.0);

    generator->processModel(model);
    printErrorsToTerminal(generator);

    //  4.d Because we've used the default profile (C) we need to output both the
    //      interfaceCode (the header file) and the implementationCode (source file)
    //      from the generator and write them.
    std::ofstream outFile("tutorial3_PredatorPrey_generated.h");
    outFile << generator->interfaceCode();
    outFile.close();

    outFile.open("tutorial3_PredatorPrey_generated.c");
    outFile << generator->implementationCode();
    outFile.close();

    //  4.e Change the generator profile to Python
    libcellml::GeneratorProfilePtr profile =
        libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);

    //  4.f Retrieve the Python implementation code and write to a file
    outFile.open("tutorial3_PredatorPrey_generated.py");
    outFile << generator->implementationCode();
    outFile.close();

    //  4.g Go and have a cuppa, you're done!
}
