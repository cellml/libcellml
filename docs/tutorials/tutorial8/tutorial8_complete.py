"""
    TUTORIAL 6: CODE GENERATION

    This tutorial explores the ability of libCellML to generate files representing
    the model which can be solved in Python or C.  By the time you have worked
    through Tutorial 6 you will be able to:
        - use the Generator functionality to create models in Python or C format
        - use the simple solver provided to run the created models.

    Tutorial 6 assumes that you are already comfortable with:
        - file manipulation and summarising using the utility functions

"""
from libcellml import Component, Generator, GeneratorProfile, Model, Parser, Printer, Validator, Variable

from utilities.tutorial_utilities import print_errors_to_terminal, print_encapsulation_structure_to_terminal, \
    switch_units_in_maths, insert_into_mathml_string

if __name__ == "__main__":

    #  0.a Create a new model instance representing the combined model and name it.
    model = Model()
    model.setName("Tutorial8_HHModel")
    validator = Validator()
    parser = Parser()

    print("-----------------------------------------------")
    print("    STEP 1: Read the membrane component")
    print("-----------------------------------------------")

    #  1.a Read the model provided for you in the "Tutorial8_MembraneModel.cellml"
    #      file in the resources folder.
    read_file1 = open("../resources/tutorial8_MembraneModel.cellml", "r")

    # 1.b  Create a temporary model for the membrane
    membrane_model = parser.parseModel(read_file1.read())
    membrane_model.setName("membraneModel")

    #  1.b Extract the membrane component from the parsed model and add it
    #      to the combined model.  Note that the membrane component's parent
    #      must be removed before adding it to the model.
    membrane = membrane_model.component("membrane")
    membrane.removeParent()
    model.addComponent(membrane)

    #  1.c Validate the combined model.  We expect to see errors from:
    #      - missing units, as we have only added the component so far
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.d Import the units from the membraneModel into the combined model
    for u in range(0, membrane_model.unitsCount()):
        model.addUnits(membrane_model.units(u))

    #  1.e No errors expected this time :)
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("      STEP 2: Read the sodium channel")
    print("-----------------------------------------------")

    #  2.a Read the model created in Tutorial 7 representing the sodium channel.
    #      Note that if you didn't do that tutorial you can simply copy the CellML file
    #      from Tutorial7_SodiumChannelModel.cellml in the resources folder.

    read_file2 = open("../resources/tutorial7_SodiumChannelModel.cellml", "r")

    sodium_channel_model = parser.parseModel(read_file2.read())
    sodium_channel_model.setName("sodiumChannelModel")
    validator.validateModel(sodium_channel_model)
    print_errors_to_terminal(validator)

    #  2.b Extract the sodiumChannel component from the parsed model and add it
    #      to the one created at the beginning, and check the structure of the
    #      encapsulation using the utility function printEncapsulationStructureToTerminal(model)
    sodium_channel = sodium_channel_model.component("sodiumChannel")
    sodium_channel.removeParent()
    membrane.addComponent(sodium_channel)
    print_encapsulation_structure_to_terminal(model)

    #  2.c Validate the combined model.  We expect to see errors from:
    #      - missing units, as we have only added the component so far,
    #      - illegal connections between equivalent variables, as now the environment
    #        component and the sodiumChannel component are no longer siblings.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  2.d Add all of the units from the sodium channel model which are not already
    #        present into the combined model.
    for u in range(0, sodium_channel_model.unitsCount()):
        unitName = sodium_channel_model.units(u).name()
        if not model.hasUnits(unitName):
            print("Adding units called {}".format(unitName))
            model.addUnits(sodium_channel_model.units(u))

    #  2.e Disconnect the sodiumChannel from its old environment component
    Variable.removeEquivalence(
        sodium_channel.variable("t"),
        sodium_channel_model.component("environment").variable("t"))
    Variable.removeEquivalence(
        sodium_channel.variable("V"),
        sodium_channel_model.component("environment").variable("V"))

    #  2.f Validate that there are no more errors in the combined model
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("       STEP 3: Read the potassium channel")
    print("-----------------------------------------------")

    print("Opening the CellML file: 'tutorial5_PotassiumChannelModel.cellml'")
    read_file3 = open("../resources/tutorial5_PotassiumChannelModel.cellml", "r")

    #  3.a Deserialising the file and reading into the potassium_channel_model
    potassium_channel_model = parser.parseModel(read_file3.read())

    #  3.b Extract the potassiumChannel component from the parsed model and add it
    #      to the combined model, and check the contents
    potassium_channel = potassium_channel_model.component("potassiumChannel")
    potassium_channel.removeParent()
    membrane.addComponent(potassium_channel)

    #  3.c Validate the combined model.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  If you have used the files provided in the resources folder, you can expect
    #  to see errors at this point relating to missing units.
    #  This is because even though both components require the same set of units,
    #  each of them has used different names for them.  At this stage you have a
    #  choice: either import all the units under their original names from the
    #  potassium channel as well, or rename the units throughout the potassiumChannel
    #  variables and maths.  Here we'll go with the former to illustrate the
    #  process, and to create a more compact model description.

    #  3.d Rename the units referred to by the variables in the potassium_channel and nGate components
    potassium_channel.variable("t").setUnits("ms")
    potassium_channel.variable("V").setUnits("mV")
    potassium_channel.variable("E_K").setUnits("mV")
    potassium_channel.variable("g_K").setUnits("mS_per_cm2")
    potassium_channel.variable("alpha_n").setUnits("per_ms")
    potassium_channel.variable("beta_n").setUnits("per_ms")

    potassium_channel.component("nGate").variable("t").setUnits("ms")
    potassium_channel.component("nGate").variable("V").setUnits("mV")
    potassium_channel.component("nGate").variable("alpha_n").setUnits("per_ms")
    potassium_channel.component("nGate").variable("beta_n").setUnits("per_ms")

    #  3.e Replacing units in the MathML string in the nGate component.
    #      Note: There are no constants in the potassiumChannel maths, so we don't need to
    #      search and replace the maths there.  In the general case, you'd need to do the
    #      same in that component too.
    nGateMaths = potassium_channel.component("nGate").math()
    nGateMaths = switch_units_in_maths(nGateMaths, "millivolt", "mV")
    nGateMaths = switch_units_in_maths(nGateMaths, "millisecond", "ms")
    nGateMaths = switch_units_in_maths(nGateMaths, "per_millisecond", "per_ms")
    nGateMaths = switch_units_in_maths(nGateMaths, "per_millivolt_millisecond", "per_mV_ms")
    nGateMaths = switch_units_in_maths(nGateMaths, "milliS_per_cm2", "mS_per_cm2")
    potassium_channel.component("nGate").setMath(nGateMaths)

    #  3.f Validating the model again.  This time we expect errors related to a mismatch in errors
    #      between equivalent variables ... which is a misleading error message because in the
    #      source model - PotassiumChannelModel, they *were* equivalent!  We haven't imported
    #      the environment component into our combined model yet, and that is the origin of this
    #      error.  We can solve the problem by creating the local environment component, and adding
    #      the equivalence to that instead.
    Variable.removeEquivalence(
        potassium_channel.variable("t"),
        potassium_channel_model.component("environment").variable("t"))
    Variable.removeEquivalence(
        potassium_channel.variable("V"),
        potassium_channel_model.component("environment").variable("V"))

    #  3.g Calling the validator again.  We do not expect errors here.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("    STEP 4: Read the leakage component")
    print("-----------------------------------------------")

    print("Opening the CellML file: 'tutorial8_LeakageCurrentModel.cellml'")
    read_file4 = open("../resources/tutorial8_LeakageCurrentModel.cellml", "r")

    #  4.a Deserialising the file and reading into the leakageCurrentModel
    leakage_current_model = parser.parseModel(read_file4.read())
    leakage_current_model.setName("leakageCurrentModel")

    #  4.b Extract the leakageCurrent component from the parsed model and add it
    #      to the combined model, and check the contents
    leakage_current = leakage_current_model.component("leakageCurrent")
    leakage_current.removeParent()
    membrane.addComponent(leakage_current)

    #  4.c Validate the combined model.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("   STEP 5: Create the environment component")
    print("-----------------------------------------------")

    print_encapsulation_structure_to_terminal(model)

    #  5.a Creating the environment component and adding it to the model
    environment = Component()
    environment.setName("environment")
    model.addComponent(environment)

    #  5.b Add variables to the environment component.
    if True:
        V = Variable()
        V.setName("V")
        V.setInitialValue(-85)
        V.setUnits("mV")
        environment.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("ms")
        environment.addVariable(t)

    #  5.c Add the new component to the model and validate
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("   STEP 6: Connect the equivalent variables")
    print("-----------------------------------------------")

    #  6.a Connecting the membrane to its sibling environment, and the channels to their
    #      parent membrane component.
    Variable.addEquivalence(membrane.variable("t"), sodium_channel.variable("t"))
    Variable.addEquivalence(membrane.variable("t"), potassium_channel.variable("t"))
    Variable.addEquivalence(environment.variable("t"), membrane.variable("t"))
    Variable.addEquivalence(membrane.variable("V"), sodium_channel.variable("V"))
    Variable.addEquivalence(membrane.variable("V"), potassium_channel.variable("V"))
    Variable.addEquivalence(membrane.variable("V"), leakage_current.variable("V"))
    Variable.addEquivalence(environment.variable("V"), membrane.variable("V"))

    Variable.addEquivalence(sodium_channel.variable("i_Na"), membrane.variable("i_Na"))
    Variable.addEquivalence(potassium_channel.variable("i_K"), membrane.variable("i_K"))
    Variable.addEquivalence(leakage_current.variable("i_L"), membrane.variable("i_L"))

    #  6.b Setting the interface types for those which haven't been inherited already
    environment.variable("t").setInterfaceType("public")
    membrane.variable("t").setInterfaceType("public_and_private")
    environment.variable("V").setInterfaceType("public")
    membrane.variable("V").setInterfaceType("public_and_private")

    # TODO Check what these should be
    sodium_channel.variable("i_Na").setInterfaceType("public_and_private")
    potassium_channel.variable("i_K").setInterfaceType("public_and_private")
    leakage_current.variable("i_L").setInterfaceType("public_and_private")

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("   STEP 7: Add the driving function")
    print("-----------------------------------------------")

    #  7.a Create a MathML string to represent the stimulus current i_stim, which
    #      is set to 100 microA/cm^2 between t=1ms < t < t=1.2ms.
    stimulusEquation = \
        '<apply><eq/>\
            <ci>i_stim</ci>\
            <piecewise>\
                <piece>\
                    <cn cellml:units="microA_per_cm2">0</cn>\
                    <apply><lt/><ci>t</ci><cn cellml:units="ms">1</cn></apply>\
                </piece>\
                    <piece>\
                    <cn cellml:units="microA_per_cm2">0</cn>\
                    <apply><gt/><ci>t</ci><cn cellml:units="ms">1.2</cn></apply>\
                </piece>\
                <otherwise>\
                    <cn cellml:units="microA_per_cm2">100</cn>\
                </otherwise>\
            </piecewise>\
        </apply>'

    #  7.b Add before the closing </math> tag in the membrane component and print to check it
    membrane_math = membrane.math()
    membrane_math = insert_into_mathml_string(membrane_math, stimulusEquation)
    membrane.setMath(membrane_math)
    print(membrane_math)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("\n-----------------------------------------------")
    print("   STEP 8: Output the final model")
    print("-----------------------------------------------")

    generator = Generator()
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

    potassium_channel.variable("V").removeInitialValue()
    membrane.variable("V").removeInitialValue()

    # Generator currently segfauts here
    generator.processModel(model)
    print("procesed ... ")
    print_errors_to_terminal(generator)
