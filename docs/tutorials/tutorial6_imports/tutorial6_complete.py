'''
       TUTORIAL 6: POTASSIUM CHANNEL MODEL

   This tutorial explores the ability of CellML to represent more than one
   modelled process at a time using components with connections between them.
   By the time you have worked through Tutorial 6 you will be able to:
       - import a Component or Units item from an existing CellML file
       - assemble a multi-component model using the API
       - inter-connect the components using the equivalent variables
         functionality
       - validate and debug the constructed model

   Tutorial 6 assumes that you are already comfortable with:
       - file manipulation and summarising using the utility functions
       - model creation through the API
       - debugging the model using the Validator functionality

 '''

from libcellml import Component, Generator, GeneratorProfile, ImportSource, Model, Printer, Units, Validator, \
    Variable

from tutorial_utilities import print_errors_to_terminal

if __name__ == '__main__':
    #  0.a Setup useful things
    validator = Validator()
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">\n'
    math_footer = '</math>'

    print('----------------------------------------------------------')
    print('   STEP 1: Define the potassiumChannel component ')
    print('----------------------------------------------------------')

    #  STEP 1: Define the potassiumChannel component
    #      As in the previous Tutorial 5, we define an ion channel, but this time make it
    #      specific to potassium.  We also introduce voltage dependence into the alpha and
    #      beta gate rates, and move them into a separate component to make it cleaner.
    #      This separate component is the nGate component, and will be defined in Step 2.

    #  1.a Create a model and add to it a new potassiumChannel component.
    model = Model('Tutorial6_PotassiumChannelModel')
    potassiumChannel = Component('potassiumChannel')
    model.addComponent(potassiumChannel)

    #  1.b Define the maths inside the potassiumChannel component.  You might like to use
    #      the "if True:" idiom to limit the scope of your definition.
    if True:
        equation = \
            '  <apply><eq/>\n'\
            '    <ci>i_K</ci>\n'\
            '    <apply><times/>\n'\
            '       <apply><power/>\n'\
            '           <ci>n</ci>\n'\
            '           <cn cellml:units="dimensionless">4</cn>\n'\
            '       </apply>\n'\
            '       <ci>g_K</ci>\n'\
            '       <apply><minus/>\n'\
            '           <ci>V</ci>\n'\
            '           <ci>E_K</ci>\n'\
            '       </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        potassiumChannel.setMath(math_header)
        potassiumChannel.appendMath(equation)
        potassiumChannel.appendMath(math_footer)
    # end scope of maths in this component

    #  1.c Call the validator and expect it to report errors related to missing variables and units.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.d Create the variables needed and add them to the potassium channel component
    if True:
        E_K = Variable('E_K')
        E_K.setUnits('millivolt')
        potassiumChannel.addVariable(E_K)

        i_K = Variable('i_K')
        i_K.setUnits('microA_per_cm2')
        potassiumChannel.addVariable(i_K)

        g_K = Variable('g_K')
        g_K.setUnits('milliS_per_cm2')
        potassiumChannel.addVariable(g_K)

        V = Variable('V')
        V.setUnits('millivolt')
        potassiumChannel.addVariable(V)

        t = Variable('t')
        t.setUnits('millisecond')
        potassiumChannel.addVariable(t)

        n = Variable('n')
        n.setUnits('dimensionless')
        potassiumChannel.addVariable(n)

    #  1.e Check for errors.  Expect warnings about the undefined units in the maths and in the
    #      new variables added.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.f Add the missing units.  Verify that the model is now free of validation errors.
    #
    #  NOTE: If, even after adding the Units the validator continues to return an error, you
    #      need to call the Model.linkUnits() function to link the units.  Unlinked units
    #      can occur when variables call their setUnits() function with
    #      a string argument of the Units' name, rather than the Units item itself.
    mV = Units('millivolt')
    mV.addUnit('volt', 'milli')

    microA_per_cm2 = Units('microA_per_cm2')
    microA_per_cm2.addUnit('ampere', 'micro')
    microA_per_cm2.addUnit('metre', 'centi', -2.0)

    mS_per_cm2 = Units('milliS_per_cm2')
    mS_per_cm2.addUnit('siemens', 'milli')
    mS_per_cm2.addUnit('metre', 'centi', -2.0)

    ms = Units('millisecond')
    ms.addUnit('second', 'milli')

    mM = Units('millimol')
    mM.addUnit('mole', 'milli')

    model.addUnits(ms)
    model.addUnits(mV)
    model.addUnits(mM)
    model.addUnits(microA_per_cm2)
    model.addUnits(mS_per_cm2)

    model.linkUnits()

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print('----------------------------------------------------------')
    print('   STEP 2: Create the nGate component  ')
    print('----------------------------------------------------------')

    #  STEP 2: Create the nGate component
    #      This model differs from the one in Tutorial 5 in that voltage dependence is
    #      introduced into the opening and closing rates.  This dependence is handled in
    #      a separate component, the nGate component, which you'll define here.

    #  2.a Create an nGate component, and add it to the potassiumChannel component (not the model)
    #      Adding it to the component creates an encapsulation hierarchy, which affects which components
    #      have access to each other.  It also means that if the potassiumChannel component is
    #      moved or imported, the nGate child component will be included too.
    nGate = Component('nGate')
    potassiumChannel.addComponent(nGate)

    #  2.b Add the mathematics to the nGate component and validate the model.
    #      Expect errors relating to missing variables.
    if True:
        equation1 = \
            '  <apply><eq/>\n'\
            '    <apply><diff/>\n'\
            '      <bvar><ci>t</ci></bvar>\n'\
            '      <ci>n</ci>\n'\
            '    </apply>\n'\
            '    <apply><minus/>\n'\
            '      <apply><times/>\n'\
            '        <ci>alpha_n</ci>\n'\
            '        <apply><minus/>\n'\
            '          <cn cellml:units="dimensionless">1</cn>\n'\
            '          <ci>n</ci>\n'\
            '        </apply>\n'\
            '      </apply>\n'\
            '      <apply><times/>\n'\
            '        <ci>beta_n</ci>\n'\
            '        <ci>n</ci>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        equation2 = \
            '  <apply><eq/>\n'\
            '    <ci>alpha_n</ci>\n'\
            '    <apply><divide/>\n'\
            '      <apply><times/>\n'\
            '        <cn cellml:units="per_millivolt_millisecond">0.01</cn>\n'\
            '        <apply><plus/>\n'\
            '          <ci>V</ci>\n'\
            '          <cn cellml:units="millivolt">10</cn>\n'\
            '        </apply>\n'\
            '      </apply>\n'\
            '      <apply><minus/>\n'\
            '        <apply><exp/>\n'\
            '          <apply><divide/>\n'\
            '            <apply><plus/>\n'\
            '              <ci>V</ci>\n'\
            '              <cn cellml:units="millivolt">10</cn>\n'\
            '            </apply>\n'\
            '            <cn cellml:units="millivolt">10</cn>\n'\
            '          </apply>\n'\
            '        </apply>\n'\
            '        <cn cellml:units="dimensionless">1</cn>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        equation3 = \
            '  <apply><eq/>\n'\
            '    <ci>beta_n</ci>\n'\
            '    <apply><times/>\n'\
            '      <cn cellml:units="per_millisecond">0.125</cn>\n'\
            '      <apply><exp/>\n'\
            '        <apply><divide/>\n'\
            '          <ci>V</ci>\n'\
            '          <cn cellml:units="millivolt">80</cn>\n'\
            '        </apply>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        nGate.setMath(math_header)
        nGate.appendMath(equation1)
        nGate.appendMath(equation2)
        nGate.appendMath(equation3)
        nGate.appendMath(math_footer)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  2.c Add the missing variables to the nGate component, link the units, and validate again.
    #      Expect errors relating to missing units.
    t = Variable('t')
    t.setUnits('millisecond')
    nGate.addVariable(t)

    V = Variable('V')
    V.setUnits('millivolt')
    nGate.addVariable(V)

    alpha_n = Variable('alpha_n')
    alpha_n.setUnits('per_millisecond')
    nGate.addVariable(alpha_n)

    beta_n = Variable('beta_n')
    beta_n.setUnits('per_millisecond')
    nGate.addVariable(beta_n)

    n = Variable('n')
    n.setUnits('dimensionless')
    nGate.addVariable(n)

    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  2.d Create the missing units and add them to the model.  Link the model's
    #      units and validate again.  Expect the model to be free of errros.
    per_mV_ms = Units('per_millivolt_millisecond')
    per_mV_ms.addUnit('per_millisecond')
    per_mV_ms.addUnit('millivolt', -1)
    model.addUnits(per_mV_ms)

    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print('----------------------------------------------------------')
    print('   STEP 3: Connect the components together ')
    print('----------------------------------------------------------')

    #  STEP 3: Connect the components together.
    #      In order for the voltage dependence of the alpha and beta rates within
    #      the nGate component to affect the current in the potassiumChannel component
    #      some of the variables need to share their values between the components.
    #      This is done using variable equivalence and interfaces.

    #  3.a Set the equivalent variable pairs between the nGate and potassiumChannel components.
    #      These are:
    #          - voltage, V
    #          - time, t
    #          - gate status, n
    #      Use the Variable.addEquivalence(VariablePtr, VariablePtr) function.
    Variable.addEquivalence(
        potassiumChannel.variable('t'), nGate.variable('t'))
    Variable.addEquivalence(
        potassiumChannel.variable('V'), nGate.variable('V'))
    Variable.addEquivalence(
        potassiumChannel.variable('n'), nGate.variable('n'))

    validator.validateModel(model)
    print_errors_to_terminal(validator)
    # ** TODO This should return a validation error saying that the interfaces are not specified **

    potassiumChannel.variable('t').setInterfaceType('public_and_private')
    potassiumChannel.variable('V').setInterfaceType('public_and_private')
    nGate.variable('t').setInterfaceType('public')
    nGate.variable('V').setInterfaceType('public')
    potassiumChannel.variable('n').setInterfaceType('private')
    nGate.variable('n').setInterfaceType('public')

    print('----------------------------------------------------------')
    print('   STEP 4: Import the controller ')
    print('----------------------------------------------------------')

    #  STEP 4: The controller is a component sitting outside the current model in a separate
    #      file.  This allows for it to be more easily interchangable between runs and stimulus
    #      conditions.  We introduce the import functionality here for that purpose.
    #      When a Component (or Units) item is imported it needs:
    #          - to be connected to an ImportSource item
    #            - which in turn stores the url of the source file to be opened
    #          - the name of the item in the source file to be retrieved
    #          - a destination component (or units) item in which to store the
    #            imported information

    #  4.a Create a pointer to an ImportSource item using the create() idiom.
    importer = ImportSource()

    #  4.b Use the ImportSource.setUrl() function to pass the file name containing the controller.
    importer.setUrl('tutorial6_controller.cellml')

    #  4.c Create the destination component into which the imported component
    #      will be saved, and name it.  This will be the controller component.
    controller = Component('controller')

    #  4.d Call the Component.setSourceComponent(ImportSource, std.string) function to
    #      associate the destination controller component with the importer, and
    #      the importer with the name of the item to retrieve.  If you're using the
    #      file from the resources folder, the name of the component to import is 'potassiumChannel_controller'.
    controller.setSourceComponent(importer, 'potassiumChannel_controller')

    #  4.e Add the controller component to the model in the normal way.
    model.addComponent(controller)

    print('----------------------------------------------------------')
    print('   STEP 5: Import the initial conditions ')
    print('----------------------------------------------------------')

    #  STEP 5: Import the initial conditions
    #      Similar to the way in which we imported the controller for the independent variables,
    #      we can also import components to initialise the values within the potassiumChannel
    #      and nGate components.  This procedure is the same as for the controller in Step 4,
    #      the only difference being that the initialising components should be siblings or
    #      children of the components to which they give values.
    #
    #      In this example the initialising components exist in the tutorial6_controller.cellml
    #      file, so we can reuse the importer from Step 4.b, and simply repeat steps 4.c-e to
    #      initalise the variables in the potassiumChannel and nGate components.  The items
    #      to retrieve are called 'potassiumChannel_initialiser' and 'nGate_initialiser' respectively.

    #  5.a Repeat steps 4.c-e for both the potassiumChannel and nGate components, and add the
    #      new components as children of the components they initialise.
    potassiumChannelInit = Component('potassiumChannelInit')
    potassiumChannelInit.setSourceComponent(
        importer, 'potassiumChannel_initialiser')
    potassiumChannel.addComponent(potassiumChannelInit)

    nGateInit = Component('nGateInit')
    nGateInit.setSourceComponent(importer, 'nGate_initialiser')
    nGate.addComponent(nGateInit)

    #  5.b (optional)  At this stage our model could be written to a CellML file.  As the model
    #      contains import statements, the serialised and printed model would also maintain those
    #      same dependencies, and would need to exist alongside the tutorial6_controller.cellml
    #      file specified earlier.  In later steps we'll disconnect this dependency to allow for
    #      the code generation step.
    #
    #      Check that the model is valid, then create a Printer, and use it to serialise the model.
    #      Write the serialised model to a file.
    printer = Printer()
    serialised_model = printer.printModel(model)
    out_file = 'tutorial6_PotassiumChannelModel.cellml'
    write_file = open(out_file, 'w')
    write_file.write(serialised_model)
    print('The {m} has been printed to {n}'.format(m=model.name(), n=out_file))

    #  5.c Now that all the imports are specified, we need to first resolve them with respect to a
    #      directory location.  This location is either specified with an absolute path, or
    #      relative to the current working directory.
    #      Call the Model.resolveImports(directoryPath) function to resolve the imports.  Check that
    #      it has worked as expected by checking that Model.hasUnresolvedImports() returns false.
    model.resolveImports('')
    if model.hasUnresolvedImports():
        print('The model has UNRESOLVED imports :(')
    else:
        print('The model has resolved all its imports :)')

    #  5.d Finally it's time to flatten the model.  This operation will create new local instances of all
    #      of the imported items, thereby removing the model's dependency on imports. Use the Model.flatten()
    #      function to do this.
    model.flatten()

    #  5.e After flattening it's important to note that any imported items (such as the components
    #      potassiumChannelInit, nGateInit, and controller) now exist within the model slightly differently.
    #      The easiest thing to do is to refresh their pointers by fetching the components from the flattened model.
    #      You can do this using their 'destination' name, eg: controller = model.component('controller') etc.
    controller = model.component('controller')
    nGateInit = nGate.component('nGateInit')
    potassiumChannelInit = potassiumChannel.component('potassiumChannelInit')
    model.linkUnits()

    print('----------------------------------------------------------')
    print('   STEP 6: Generate the model ')
    print('----------------------------------------------------------')

    # TODO It would be better to do the checking currently in the Generator outside it ...
    #      This is coming (soon?) see https://github.com/cellml/libcellml/issues/499

    #  6.a Create a Generator instance and pass it the model for processing.  Check for errors and
    #      print them to the terminal.  We expect to see errors reporting that some variables are not
    #      computed or not initialised.
    generator = Generator()
    generator.processModel(model)
    print_errors_to_terminal(generator)

    #  6.b The Generator needs variables to have values or to be computed.  The initial values
    #      for all the variables in the model are stored in the controller and initialisation components, so we
    #      need to connect these together, just as in step 3.a, using the Variable.addEquivalence function.
    Variable.addEquivalence(potassiumChannelInit.variable(
        'E_K'), potassiumChannel.variable('E_K'))
    Variable.addEquivalence(potassiumChannelInit.variable(
        'g_K'), potassiumChannel.variable('g_K'))
    Variable.addEquivalence(nGateInit.variable('n'), nGate.variable('n'))
    Variable.addEquivalence(controller.variable(
        'V'), potassiumChannel.variable('V'))
    Variable.addEquivalence(controller.variable(
        't'), potassiumChannel.variable('t'))

    #  6.c We also need to specify the interface types for these variable equivalnences.
    potassiumChannel.variable('E_K').setInterfaceType('public_and_private')
    potassiumChannel.variable('g_K').setInterfaceType('public_and_private')
    nGate.variable('n').setInterfaceType('public_and_private')

    #  6.c Pass the model back to the generator for re-processing, and check that now there are no more errors.
    generator.processModel(model)
    print_errors_to_terminal(generator)

    print('----------------------------------------------------------')
    print('   STEP 7: Output the final generated model ')
    print('----------------------------------------------------------')

    #  7.a Change the profile to Python and process the model
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)
    generator.processModel(model)

    #  7.b Write the Python implementation code to a .py file
    implementation_code = generator.implementationCode()
    write_file = open('tutorial6_PotassiumChannel_generated.py', 'w')
    write_file.write(implementation_code)
    print('The {m} model has been printed to tutorial6_PotassiumChannel_generated.py'.format(
        model.name()))

    #  7.c Serialise the model using a Printer and write to a CellML file.
    serialised_model = printer.printModel(model)
    write_file = open('tutorial6_PotassiumChannel_flattened.cellml', 'w')
    write_file.write(serialised_model)

    print('The created ' + model.name() +
          ' model has been output to tutorial6_PotassiumChannel_flattened.cellml')

    #  7.f Please see the instructions in the tutorial for how to run a
    #      simulation of this model using the simple solver provided.
    #      Then go and have a cuppa, you're done!
