"""
    TUTORIAL 8:

"""
from libcellml import Component, Generator, GeneratorProfile, ImportSource, Model, Parser, Printer, \
    Units, Validator, Variable

from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal, \
    print_encapsulation_structure_to_terminal

if __name__ == "__main__":

    validator = Validator()

    print("-------------------------------------------------")
    print("  STEP 1: Create the external parameters model   ")
    print("-------------------------------------------------")

    # 1.a  Create a new controller model, containing the controller component and a parameters component.
    #      This will be written separately to the main model so that its values can be changed easily.
    controllerModel = Model("Tutorial8_parameters")
    parameters = Component("parameters")
    controllerModel.addComponent(parameters)

    print("-------------------------------------------------")
    print("  STEP 2: Parse the membrane model               ")
    print("-------------------------------------------------")

    #  2.a Create a Parser and use it to read in the contents of the resources/tutorial8_MembraneModel.cellml
    #      file provided.  Use this to create a new model instance.
    #      Note that the only reason to *parse* and not *import* this model is because we need to change it.
    #      The changes will involve:
    #          - Adding encapsulated components (in steps 2-4)
    #          - Adding intermediate variables to allow for initialisation of those components (steps 2-4)
    #          - Creating connections to external parameters components (step 5) and
    #          - Creating connections to the encapsulated components' variables (step 7).

    parser = Parser()
    readFile = open("tutorial8_MembraneModel.cellml")
    model = parser.parseModel(readFile.read())

    #  2.b Print the parsed model to the terminal and verify it contains:
    #  MODEL: 'Tutorial8_MembraneModel'
    #     UNITS: 5 custom units
    #         [0]: mV
    #         [1]: ms
    #         [2]: mS_per_cm2
    #         [3]: microA_per_cm2
    #         [4]: microF_per_cm2
    #     COMPONENTS: 1 components
    #         [0]: membrane
    #             VARIABLES: 7 variables
    #                 [0]: V [mV]                  integrated variable, initialised by parameters component
    #                 [1]: t [ms]                  base variable of integration
    #                 [2]: i_K [microA_per_cm2]    potassium current, calculated by imported component
    #                 [3]: i_Na [microA_per_cm2]   sodium current, calculated by imported componnet
    #                 [4]: i_L [microA_per_cm2]    leakage current, calculated by imported component
    #                 [5]: i_stim [microA_per_cm2] stimulus current, specified locally in the membrane
    #                 [6]: Cm [microF_per_cm2]     constant, membrane capacitance, initialised by parameters component
    print_model_to_terminal(model)

    #  2.c Because we want to be able to initialise the variables in this component, we need to
    #      add the corresponding variables into the parameters component.  Looking at your print out
    #      of the component above, any variables which need to be initialised will need to be added
    #      in to the external parameters component too.  Here, they are Cm and V.
    #      Add two variables to the parameters component, with an interface type of "public".
    #      You will need to keep track of the units which you add to this component as you go, and
    #      add in any new ones.  In this case, both are new and will need to be created and added
    #      to the controller model as normal.
    if True:
        Cm = Variable("Cm")
        parameters.addVariable(Cm)
        parameters.variable("Cm").setUnits("microF_per_cm2")
        parameters.variable("Cm").setInterfaceType("public")

        microF_per_cm2 = Units("microF_per_cm2")
        microF_per_cm2.addUnit("farad", "micro")
        microF_per_cm2.addUnit("metre", "centi", -2)
        controllerModel.addUnits(microF_per_cm2)

        V = Variable("V")
        parameters.addVariable(V)
        parameters.variable("V").setUnits("mV")
        parameters.variable("V").setInterfaceType("public")

        mV = Units("mV")
        mV.addUnit("volt", "milli")
        controllerModel.addUnits(mV)

    print("-------------------------------------------------")
    print("  STEP 3: Import the sodium channel component    ")
    print("-------------------------------------------------")

    #  In order to use the import functionality we need to know three things:
    #      - the import destination (the component/unit to which the imported item will be assigned)
    #      - the file we're importing it from (the url to the model containing the item to be imported)
    #      - which item within the file should be imported (the name of the component/units inside the import model file)
    #  We'll address these now.
    sodiumChannelFile = "tutorial7_SodiumChannelModel.cellml"

    #  3.a First we need to know the contents of the component we're importing.  This step is necessary
    #      so that we can create dummy variables with the same name and units in step 2.e.
    #      If you don't happen to know the contents of the components, simply parse the models
    #      and print them to the terminal for viewing.
    if True:
        readFile = open(sodiumChannelFile)
        temp = parser.parseModel(readFile.read())
        temp.resolveImports("")
        temp.flatten()
        print_model_to_terminal(temp)

    #  3.b Create a component representing the sodium channel.  This will be encapsulated inside the membrane
    #      component, so add it there instead of adding it to the model.
    sodiumChannel = Component("sodium_channel")
    model.component("membrane").addComponent(sodiumChannel)

    #  3.c Create an importer for the sodium channel, and point it to the file you created in Tutorial 7.
    #      Note that you will need to make sure it exists in the same path as the earlier files.
    #      If you did not complete Tutorial 7 you can use the tutorial7_SodiumChannelModel.cellml
    #      file in the resources folder.
    sodiumImporter = ImportSource()
    sodiumImporter.setUrl(sodiumChannelFile)

    #  3.d Link the sodium channel component to the importer and set the reference to import.
    #      In the file provided this is named "sodiumChannel".  You will need to change this to
    #      whatever you named the component in Tutorial 7.
    sodiumChannel.setImportSource(sodiumImporter)
    sodiumChannel.setImportReference("sodiumChannel")

    #  3.e Looking at your printout in step 3.a, any variables in the imported model which were
    #      connected to its local parameters or controller components will now need to be connected
    #      to its new membrane component parent instead.
    #      Dummy variables are those which already exist in the component to be imported, but must be
    #      added here manually so that we can create the connections between equivalent variables before
    #      flattening the model.
    #      Because these are dummy variables will be overwritten, you do not need to specify units or interfaces.
    if True:
        V = Variable("V")
        sodiumChannel.addVariable(V)
        t = Variable("t")
        sodiumChannel.addVariable(t)
        i_Na = Variable("i_Na")
        sodiumChannel.addVariable(i_Na)
        h = Variable("h")
        sodiumChannel.addVariable(h)
        m = Variable("m")
        sodiumChannel.addVariable(m)
        g_Na = Variable("g_Na")
        sodiumChannel.addVariable(g_Na)
        E_Na = Variable("E_Na")
        sodiumChannel.addVariable(E_Na)

    #  3.g Because any values for initialisation must also be passed through the membrane component, we have to
    #      add intermediate variables for h, m, g_Na, and E_Na there too.
    #      Because these are concrete variables (ie: they will not be overwritten by an import), you will need
    #      to specify units and interfaces.  Note that because these variables will need to connect to child
    #      components as well as sibling components, they should have the interface type "public_and_private".
    if True:
        h = Variable("h")
        h.setInterfaceType("public_and_private")
        h.setUnits("dimensionless")
        model.component("membrane").addVariable(h)

        m = Variable("m")
        m.setInterfaceType("public_and_private")
        m.setUnits("dimensionless")
        model.component("membrane").addVariable(m)

        g_Na = Variable("g_Na")
        g_Na.setInterfaceType("public_and_private")
        g_Na.setUnits("mS_per_cm2")
        model.component("membrane").addVariable(g_Na)

        E_Na = Variable("E_Na")
        E_Na.setInterfaceType("public_and_private")
        E_Na.setUnits("mV")
        model.component("membrane").addVariable(E_Na)

    #  3.h Create concrete variables in the external parameters component, where their initial values will
    #      be set (eventually).  As you did in step 2.c you'll need to also add any units that these variables
    #      need into the controller model too.
    #      Create variables for h, m, E_Na, g_Na.
    #      Create the units for the g_Na term of milli Siemens per cm^2 and add them to the controller model.
    if True:
        h = Variable("h")
        parameters.addVariable(h)
        h.setInterfaceType("public_and_private")
        h.setUnits("dimensionless")

        m = Variable("m")
        parameters.addVariable(m)
        m.setInterfaceType("public_and_private")
        m.setUnits("dimensionless")

        E_Na = Variable("E_Na")
        parameters.addVariable(E_Na)
        E_Na.setInterfaceType("public_and_private")
        E_Na.setUnits("mV")

        g_Na = Variable("g_Na")
        parameters.addVariable(g_Na)
        g_Na.setInterfaceType("public_and_private")
        g_Na.setUnits("mS_per_cm2")

        # Add missing units to the controller model
        mS_per_cm2 = Units("mS_per_cm2")
        mS_per_cm2.addUnit("siemens", "milli")
        mS_per_cm2.addUnit("metre", "centi", -2)
        controllerModel.addUnits(mS_per_cm2)

    model.resolveImports("")
    assert(model.hasUnresolvedImports() == False)

    print("-------------------------------------------------")
    print("  STEP 4: Import the potassium channel component ")
    print("-------------------------------------------------")

    #  4.a Repeat all the tasks in Step 3, this time for the potassium channel model you created in
    #      Tutorial 6.  If you did not complete Tutorial 6 you can use the tutorial6_PotassiumChannelModel.cellml
    #      from the resources folder, importing the component called "potassiumChannel".
    #      The dummy variables involved are: V, t, i_K, n, g_K, and E_K.
    potassiumChannelFile = "tutorial6_PotassiumChannelModel.cellml"
    if True:
        readFile = open(potassiumChannelFile)
        temp = parser.parseModel(readFile.read())
        temp.resolveImports("")
        temp.flatten()
        print_model_to_terminal(temp)

    potassiumChannel = Component("potassium_channel")
    model.component("membrane").addComponent(potassiumChannel)

    potassiumImporter = ImportSource()
    potassiumImporter.setUrl(potassiumChannelFile)

    potassiumChannel.setImportSource(potassiumImporter)
    potassiumChannel.setImportReference("potassiumChannel")

    model.resolveImports("")
    assert(model.hasUnresolvedImports() == False)

    # Local dummy variables:
    if True:
        V = Variable("V")
        potassiumChannel.addVariable(V)
        t = Variable("t")
        potassiumChannel.addVariable(t)
        i_K = Variable("i_K")
        potassiumChannel.addVariable(i_K)

        n = Variable("n")
        potassiumChannel.addVariable(n)
        g_K = Variable("g_K")
        potassiumChannel.addVariable(g_K)
        E_K = Variable("E_K")
        potassiumChannel.addVariable(E_K)

    # Intermediate concrete variables in the membrane component:
    if True:
        n = Variable("n")
        n.setInterfaceType("public_and_private")
        n.setUnits("dimensionless")
        model.component("membrane").addVariable(n)

        g_K = Variable("g_K")
        g_K.setInterfaceType("public_and_private")
        g_K.setUnits("milliS_per_cm2")
        model.component("membrane").addVariable(g_K)

        E_K = Variable("E_K")
        E_K.setInterfaceType("public_and_private")
        E_K.setUnits("millivolt")
        model.component("membrane").addVariable(E_K)

    # Concrete variables in the external parameters component:
    if True:
        n = Variable("n")
        parameters.addVariable(n)
        n.setInterfaceType("public_and_private")
        n.setUnits("dimensionless")

        g_K = Variable("g_K")
        parameters.addVariable(g_K)
        g_K.setInterfaceType("public_and_private")
        g_K.setUnits("mS_per_cm2")

        E_K = Variable("E_K")
        parameters.addVariable(E_K)
        E_K.setInterfaceType("public_and_private")
        E_K.setUnits("mV")

    model.resolveImports("")
    assert(model.hasUnresolvedImports() == False)

    print("-------------------------------------------------")
    print("  STEP 5: Import the leakage component           ")
    print("-------------------------------------------------")

    #  5.a Repeat all the tasks in Step 3, this time for the leakageCurrent component in
    #      the model supplied inside resources/tutorial8_LeakageModel.cellml.

    leakageFile = "tutorial8_LeakageCurrentModel.cellml"
    if True:
        readFile = open(leakageFile)
        temp = parser.parseModel(readFile.read())
        temp.resolveImports("")
        temp.flatten()
        print_model_to_terminal(temp)

    leakage = Component("leakage")
    model.component("membrane").addComponent(leakage)

    leakageImporter = ImportSource()
    leakageImporter.setUrl(leakageFile)

    leakage.setImportSource(leakageImporter)
    leakage.setImportReference("leakageCurrent")

    # Dummy variables in the leakage component:
    if True:
        V = Variable("V")
        leakage.addVariable(V)
        t = Variable("t")
        leakage.addVariable(t)
        i_L = Variable("i_L")
        leakage.addVariable(i_L)
        g_L = Variable("g_L")
        leakage.addVariable(g_L)
        E_L = Variable("E_L")
        leakage.addVariable(E_L)

    # Concrete variables in the membrane component:
    if True:
        g_L = Variable("g_L")
        g_L.setInterfaceType("public_and_private")
        g_L.setUnits("mS_per_cm2")
        model.component("membrane").addVariable(g_L)

        E_L = Variable("E_L")
        E_L.setUnits("mV")
        E_L.setInterfaceType("public_and_private")
        model.component("membrane").addVariable(E_L)

    # Concrete variables in the external parameters component:
    if True:
        g_L = Variable("g_L")
        g_L.setInterfaceType("public_and_private")
        g_L.setUnits("mS_per_cm2")
        parameters.addVariable(g_L)

        E_L = Variable("E_L")
        E_L.setUnits("mV")
        E_L.setInterfaceType("public_and_private")
        parameters.addVariable(E_L)

    model.resolveImports("")
    assert(model.hasUnresolvedImports() == False)

    validator.validateModel(controllerModel)
    print_errors_to_terminal(validator)

    print("-------------------------------------------------")
    print("  STEP 6: Export the parameters                  ")
    print("-------------------------------------------------")

    #  6.a Now that we've imported all the components and added the variables which
    #      need initial values into the parameters component, we can write the controller
    #      model (which contains that parameters component) to a separate file.
    #      This makes it easier to locate the parameters of interest and change them later.

    #      Set the initial conditions in the parameters component of:
    #      sodium channel
    #          E_Na(t=0) = 40
    #          g_Na(t=0) = 120
    #      h-gate
    #          h(t=0) = 0.6
    #      m-gate
    #          m(t=0) = 0.05
    #      potassium channel
    #          E_K(t=0) = -87
    #          g_K(t=0) = 36
    #      n-gate
    #          n(t=0) = 0.325
    #      leakage current
    #          g_L(t=0) = 0.3
    #          E_L(t=0) = -64.387
    #      membrane
    #          V(t=0) = -75
    #          Cm(t=0) = 1

    if True:
        # sodium channel
        parameters.variable("E_Na").setInitialValue(40)
        parameters.variable("g_Na").setInitialValue(120)
        # h-gate
        parameters.variable("h").setInitialValue(0.6)
        # m-gate
        parameters.variable("m").setInitialValue(0.05)

        # potassium channel
        parameters.variable("E_K").setInitialValue(-87)
        parameters.variable("g_K").setInitialValue(36)
        # n-gate
        parameters.variable("n").setInitialValue(0.325)

        # leakage
        parameters.variable("g_L").setInitialValue(0.3)
        parameters.variable("E_L").setInitialValue(-64.387)

        # membrane
        parameters.variable("V").setInitialValue(-75)
        parameters.variable("Cm").setInitialValue(1)

    #  6.b Validate the controller model and expect there to be no errors.  You may need to
    #      link the units if you find errors related to missing units.
    controllerModel.linkUnits()
    validator.validateModel(controllerModel)
    print_errors_to_terminal(validator)

    #  6.c Create a Printer instance, and serialise the controller model for output to a
    #      file.  Name your file appropriately - you will need to use its name to import
    #      it in step 7.
    printer = Printer()
    write_file = open("tutorial8_HodgkinHuxley_controller.cellml", "w")
    write_file.write(printer.printModel(controllerModel))
    write_file.close()

    print("-------------------------------------------------")
    print("  STEP 7: Import the parameters                  ")
    print("-------------------------------------------------")

    #  7.a Repeat the tasks in Step 3.a-c, this time for the parameters component
    #      in the model which you wrote in step 6.c.
    #      You will need to use the same names for the file and the parameter
    #      component as you wrote earlier.
    parameters = Component("parameters")
    model.addComponent(parameters)

    parametersImporter = ImportSource()
    parametersImporter.setUrl("tutorial8_HodgkinHuxley_controller.cellml")

    parameters.setImportSource(parametersImporter)
    parameters.setImportReference("parameters")

    #  7.b Set up dummy variables for all of the variables in the parameters component
    #      so that they can be connected before flattening the model.
    #      Because these dummy variables will be overwritten, you do not need to specify
    #      the interface types, initial values, or units.
    if True:
        # Membrane component
        V = Variable("V")
        parameters.addVariable(V)
        Cm = Variable("Cm")
        parameters.addVariable(Cm)

        # Sodium channel
        h = Variable("h")
        parameters.addVariable(h)
        m = Variable("m")
        parameters.addVariable(m)
        E_Na = Variable("E_Na")
        parameters.addVariable(E_Na)
        g_Na = Variable("g_Na")
        parameters.addVariable(g_Na)

        # Potassium channel
        n = Variable("n")
        parameters.addVariable(n)
        E_K = Variable("E_K")
        parameters.addVariable(E_K)
        g_K = Variable("g_K")
        parameters.addVariable(g_K)

        # Leakage
        E_L = Variable("E_L")
        parameters.addVariable(E_L)
        g_L = Variable("g_L")
        parameters.addVariable(g_L)

    print("-------------------------------------------------")
    print("  STEP 8: Connect variables between components   ")
    print("-------------------------------------------------")

    #  8.a Now that we've got all the imports done, we need to connect the imported
    #      components and their dummy variables together.  The variables to connect are:
    #          - voltage:  parameters . membrane . sodium channel, potassium channel, leakage
    #          - time: membrane . sodium channel, potassium channel
    #          - current variables (i_Na, i_K, i_L): membrane . channels
    #          - conductance variables (g_Na, g_K, g_L): membrane . channels
    #          - potential variables (E_Na, E_K, E_L): membrane . channels
    #          - gating variables (h, m, n): membrane . channels
    #          - Cm: parameters . membrane

    assert(Variable.addEquivalence(parameters.variable(
        "V"), model.component("membrane").variable("V")))
    assert(Variable.addEquivalence(parameters.variable(
        "Cm"), model.component("membrane").variable("Cm")))
    assert(Variable.addEquivalence(parameters.variable(
        "h"), model.component("membrane").variable("h")))
    assert(Variable.addEquivalence(parameters.variable(
        "m"), model.component("membrane").variable("m")))
    assert(Variable.addEquivalence(parameters.variable(
        "n"), model.component("membrane").variable("n")))
    assert(Variable.addEquivalence(parameters.variable(
        "g_K"), model.component("membrane").variable("g_K")))
    assert(Variable.addEquivalence(parameters.variable("g_Na"),
                                   model.component("membrane").variable("g_Na")))
    assert(Variable.addEquivalence(parameters.variable(
        "g_L"), model.component("membrane").variable("g_L")))
    assert(Variable.addEquivalence(parameters.variable(
        "E_K"), model.component("membrane").variable("E_K")))
    assert(Variable.addEquivalence(parameters.variable("E_Na"),
                                   model.component("membrane").variable("E_Na")))
    assert(Variable.addEquivalence(parameters.variable(
        "E_L"), model.component("membrane").variable("E_L")))

    assert(Variable.addEquivalence(model.component(
        "membrane").variable("V"), sodiumChannel.variable("V")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("t"), sodiumChannel.variable("t")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("i_Na"), sodiumChannel.variable("i_Na")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("E_Na"), sodiumChannel.variable("E_Na")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("g_Na"), sodiumChannel.variable("g_Na")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("h"), sodiumChannel.variable("h")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("m"), sodiumChannel.variable("m")))

    assert(Variable.addEquivalence(model.component(
        "membrane").variable("V"), potassiumChannel.variable("V")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("t"), potassiumChannel.variable("t")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("i_K"), potassiumChannel.variable("i_K")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("E_K"), potassiumChannel.variable("E_K")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("g_K"), potassiumChannel.variable("g_K")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("n"), potassiumChannel.variable("n")))

    assert(Variable.addEquivalence(model.component(
        "membrane").variable("V"), leakage.variable("V")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("i_L"), leakage.variable("i_L")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("g_L"), leakage.variable("g_L")))
    assert(Variable.addEquivalence(model.component(
        "membrane").variable("E_L"), leakage.variable("E_L")))

    #  8.b Serialise and write the model to a CellML file.  In the steps below the model will
    #      be flattened for code generation, but we need to keep an writeFile = open("tutorial8_HodgkinHuxleyModel.cellml")
    write_file = open("tutorial8_HodgkinHuxleyModel.cellml", "w")
    write_file.write(printer.printModel(model))
    write_file.close()

    print("-------------------------------------------------")
    print("  STEP 9: Resolve imports and flatten the model  ")
    print("-------------------------------------------------")

    #  9.a Resolve the model's imports to the folder where all of the files are located, and
    #      check that there are no unresolved imports outstanding.
    model.resolveImports("")
    assert(model.hasUnresolvedImports() == False)

    #  9.b Flatten the model, and print the flattened model structure to the terminal for checking.
    model.flatten()
    print_encapsulation_structure_to_terminal(model)
    print_model_to_terminal(model)

    #  9.c Validate the flattened model, expecting that there are no errors.
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print("-------------------------------------------------")
    print("  STEP 10: Generate the model and output          ")
    print("-------------------------------------------------")

    #  10.a Create a Generator instance and submit the model for processing.
    #      Expect that there are no errors logged in the generator afterwards.
    generator = Generator()
    generator.processModel(model)
    print_errors_to_terminal(generator)

    assert(generator.errorCount() == 0)

    #  10.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.
    write_file = open("tutorial8_HodgkinHuxleyModel.h", "w")
    write_file.write(generator.interfaceCode())
    write_file.close()

    write_file = open("tutorial8_HodgkinHuxleyModel.c", "w")
    write_file.write(generator.implementationCode())
    write_file.close()

    #  10.c Change the generator profile to Python and reprocess the model.
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)
    generator.processModel(model)

    #  10.d Retrieve and write the implementation code (*.py) to a file.
    write_file = open("tutorial8_HodgkinHuxleyModel.py", "w")
    write_file.write(generator.implementationCode())
    write_file.close()

    print(
        "The model has been output into tutorial8_HodgkinHuxleyModel.[c,h,py,cellml]")

    #  10.e Please seen the tutorial instructions for how to run this simulation using
    #      the simple solver provided.  Then go and have a cuppa, you're done!
