"""
    TUTORIAL 8:

"""
from libcellml import Component, Generator, GeneratorProfile, ImportSource, Model, Parser, Printer, \
    Units, Validator, Variable

from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal, \
    print_encapsulation_structure_to_terminal

if __name__ == "__main__":

    print("-------------------------------------------------")
    print("  STEP 1: Create the external parameters model   ")
    print("-------------------------------------------------")

    # 1.a  Create a new controller model, containing the controller component and a parameters component.
    #      This will be written separately to the main model so that its values can be changed easily.

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

    #  2.c Because we want to be able to initialise the variables in this component, we need to
    #      add the corresponding variables into the parameters component.  Looking at your print out
    #      of the component above, any variables which need to be initialised will need to be added
    #      in to the external parameters component too.  Here, they are Cm and V.
    #      Add two variables to the parameters component, with an interface type of "public".
    #      You will need to keep track of the units which you add to this component as you go, and
    #      add in any new ones.  In this case, both are new and will need to be created and added
    #      to the controller model as normal.

    print("-------------------------------------------------")
    print("  STEP 3: Import the sodium channel component    ")
    print("-------------------------------------------------")

    #  In order to use the import functionality we need to know three things:
    #      - the import destination (the component/unit to which the imported item will be assigned)
    #      - the file we're importing it from (the url to the model containing the item to be imported)
    #      - which item within the file should be imported (the name of the component/units inside the import model file)
    #  We'll address these now.

    #  3.a First we need to know the contents of the component we're importing.  This step is necessary
    #      so that we can create dummy variables with the same name and units in step 2.e.
    #      If you don't happen to know the contents of the components, simply parse the models
    #      and print them to the terminal for viewing.

    #  3.b Create a component representing the sodium channel.  This will be encapsulated inside the membrane
    #      component, so add it there instead of adding it to the model.

    #  3.c Create an importer for the sodium channel, and point it to the file you created in Tutorial 7.
    #      Note that you will need to make sure it exists in the same path as the earlier files.
    #      If you did not complete Tutorial 7 you can use the tutorial7_SodiumChannelModel.cellml
    #      file in the resources folder.

    #  3.d Link the sodium channel component to the importer and set the reference to import.
    #      In the file provided this is named "sodiumChannel".  You will need to change this to
    #      whatever you named the component in Tutorial 7.

    #  3.e Looking at your printout in step 3.a, any variables in the imported model which were
    #      connected to its local parameters or controller components will now need to be connected
    #      to its new membrane component parent instead.
    #      Dummy variables are those which already exist in the component to be imported, but must be
    #      added here manually so that we can create the connections between equivalent variables before
    #      flattening the model.
    #      Because these are dummy variables will be overwritten, you do not need to specify units or interfaces.

    #  3.g Because any values for initialisation must also be passed through the membrane component, we have to
    #      add intermediate variables for h, m, g_Na, and E_Na there too.
    #      Because these are concrete variables (ie: they will not be overwritten by an import), you will need
    #      to specify units and interfaces.  Note that because these variables will need to connect to child
    #      components as well as sibling components, they should have the interface type "public_and_private".

    #  3.h Create concrete variables in the external parameters component, where their initial values will
    #      be set (eventually).  As you did in step 2.c you'll need to also add any units that these variables
    #      need into the controller model too.
    #      Create variables for h, m, E_Na, g_Na.
    #      Create the units for the g_Na term of milli Siemens per cm^2 and add them to the controller model.

    print("-------------------------------------------------")
    print("  STEP 4: Import the potassium channel component ")
    print("-------------------------------------------------")

    #  4.a Repeat all the tasks in Step 3, this time for the potassium channel model you created in
    #      Tutorial 6.  If you did not complete Tutorial 6 you can use the tutorial6_PotassiumChannelModel.cellml
    #      from the resources folder, importing the component called "potassiumChannel".
    #      The dummy variables involved are: V, t, i_K, n, g_K, and E_K.

    print("-------------------------------------------------")
    print("  STEP 5: Import the leakage component           ")
    print("-------------------------------------------------")

    #  5.a Repeat all the tasks in Step 3, this time for the leakageCurrent component in
    #      the model supplied inside resources/tutorial8_LeakageModel.cellml.

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

    #  6.b Validate the controller model and expect there to be no errors.  You may need to
    #      link the units if you find errors related to missing units.

    #  6.c Create a Printer instance, and serialise the controller model for output to a
    #      file.  Name your file appropriately - you will need to use its name to import
    #      it in step 7.

    print("-------------------------------------------------")
    print("  STEP 7: Import the parameters                  ")
    print("-------------------------------------------------")

    #  7.a Repeat the tasks in Step 3.a-c, this time for the parameters component
    #      in the model which you wrote in step 6.c.
    #      You will need to use the same names for the file and the parameter
    #      component as you wrote earlier.

    #  7.b Set up dummy variables for all of the variables in the parameters component
    #      so that they can be connected before flattening the model.
    #      Because these dummy variables will be overwritten, you do not need to specify
    #      the interface types, initial values, or units.

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

    #  8.b Serialise and write the model to a CellML file.  In the steps below the model will
    #      be flattened for code generation, but we need to keep an writeFile = open("tutorial8_HodgkinHuxleyModel.cellml")

    print("-------------------------------------------------")
    print("  STEP 9: Resolve imports and flatten the model  ")
    print("-------------------------------------------------")

    #  9.a Resolve the model's imports to the folder where all of the files are located, and
    #      check that there are no unresolved imports outstanding.

    #  9.b Flatten the model, and print the flattened model structure to the terminal for checking.

    #  9.c Validate the flattened model, expecting that there are no errors.

    print("-------------------------------------------------")
    print("  STEP 10: Generate the model and output          ")
    print("-------------------------------------------------")

    #  10.a Create a Generator instance and submit the model for processing.
    #      Expect that there are no errors logged in the generator afterwards.

    #  10.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.

    #  10.c Change the generator profile to Python and reprocess the model.

    #  10.d Retrieve and write the implementation code (*.py) to a file.

    #  10.e Please seen the tutorial instructions for how to run this simulation using
    #      the simple solver provided.  Then go and have a cuppa, you're done!
