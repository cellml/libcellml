'''
  TUTORIAL 7: Creating the Sodium Channel
  By the time you have finished this tutorial you will be able to:
      - Use the import functionality to use components from other models and
      - Use model flattening to resolve imported components for code generation.

  Tutorial 7 assumes that you are already comfortable with:
      - The concept of component hierarchy and encapsulation (Tutorial 6)
      - The use of the API to create all of the entities in a model (Tutorial 3)
      - The content MathML2 markup for mathematical equations (Tutorial 3)
      - Serialisation and printing of a model to a CellML file (Tutorial 1) and
      - Model generation and simulation (Tutorial 3, 4).
'''

from libcellml import Component, Generator, GeneratorProfile, ImportSource, Model, Printer, Units, Validator, Variable

from tutorial_utilities import print_errors_to_terminal

if __name__ == '__main__":

    # Setup: Create useful things that are used throughout the code.
    validator = Validator.create()
    mathHeader = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">\n'
    mathFooter = '</math >"

    print('--------------------------------------------------')
    print(' STEP 1: Create the sodium channel')
    print('--------------------------------------------------')

    #  1.a Create a model and name it appropriately.
    model = Model.create("Tutorial7_SodiumChannelModel")

    #  1.b Create a component instance for the sodium channel, name it, and add to the model.
    sodiumChannel.setName()
    sodiumChannel.setName("sodiumChannel")
    model.addComponent(sodiumChannel)

    #  1.c Add the MathML representing the governing equations to the component, and validate the model.
    {
        equation1 =
            '  <apply><eq/>\n'
            '    <ci>Na_conductance</ci>\n'
            '    <apply><times/>\n'
            '      <ci>g_Na</ci>\n'
            '      <ci>h</ci>\n'
            '      <apply><power/>\n'
            '        <ci>m</ci>\n'
            '        <cn cellml:units="dimensionless">3</cn>\n'
            '      </apply>\n'
            '    </apply>\n'
            '  </apply>\n'

        equation2 =
            '  <apply><eq/>\n'
            '    <ci>i_Na</ci>\n'
            '    <apply><times/>\n'
            '      <ci>Na_conductance</ci>\n'
            '      <apply><minus/>\n'
            '        <ci>V</ci>\n'
            '        <ci>E_Na</ci>\n'
            '      </apply>\n'
            '    </apply>\n'
            '  </apply>\n'

        sodiumChannel.setMath(mathHeader)
        sodiumChannel.appendMath(equation1)
        sodiumChannel.appendMath(equation2)
        sodiumChannel.appendMath(mathFooter)
    }

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.d Add the variables required by the validator.
    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("mV")
        sodiumChannel.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("ms")
        sodiumChannel.addVariable(t)

        h = Variable()
        h.setName("h")
        h.setUnits("dimensionless")
        sodiumChannel.addVariable(h)

        m = Variable()
        m.setName("m")
        m.setUnits("dimensionless")
        sodiumChannel.addVariable(m)

        g_na = Variable()
        g_Na.setName("g_Na")
        g_Na.setUnits("mS_per_cm2")
        sodiumChannel.addVariable(g_Na)

        E_Na = Variable()
        E_Na.setName("E_Na")
        E_Na.setUnits("mV")
        sodiumChannel.addVariable(E_Na)

        i_Na = Variable()
        i_Na.setName("i_Na")
        i_Na.setUnits("microA_per_cm2")
        sodiumChannel.addVariable(i_Na)

        Na_conductance = Variable()
        Na_conductance.setName("Na_conductance")
        Na_conductance.setUnits("mS_per_cm2")
        sodiumChannel.addVariable(Na_conductance)

    #  1.e Add the units as required by the validator.
    if True:
        mV = Units()
        mV.setName("mV")
        mV.addUnit("volt", 'milli")
        model.addUnits(mV)

        ms = Units()
        ms.setName("ms")
        ms.addUnit("second", 'milli")
        model.addUnits(ms)

        mS_per_cm2 = Units()
        mS_per_cm2.setName("mS_per_cm2")
        mS_per_cm2.addUnit("siemens", 'milli")
        mS_per_cm2.addUnit("metre", 'centi", -2)
        model.addUnits(mS_per_cm2)

        microA_oer_cm2 = Units()
        microA_per_cm2.setName("microA_per_cm2")
        microA_per_cm2.addUnit("ampere", 'micro")
        microA_per_cm2.addUnit("metre", 'centi", -2)
        model.addUnits(microA_per_cm2)

        mM = Units()
        mM.setName("mM")
        mM.addUnit("mole", 'milli")
        model.addUnits(mM)

    #  1.f Link the model's units and use the validator to make sure that there
    #      are no more errors in the model.
    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print('-----------------------------------------------')
    print('  STEP 2: Creating the m-gate')
    print('-----------------------------------------------')

    #  2.a Create component to represent the m-gate and add it to the sodium channel component.
    mGate.setName("mGate")
    sodiumChannel.addComponent(mGate)

    #  2.b Add the MathML strings which govern the behaviour of this gate.
    {
        equation1 =
            '  <apply><eq/>\n'
            '    <ci>alpha_m</ci>\n'
            '    <apply><divide/>\n'
            '      <apply><times/>\n'
            '        <apply><minus/>\n'
            '          <cn cellml:units="per_mV_ms">0.1</cn>\n'
            '        </apply>\n'
            '        <apply><plus/>\n'
            '          <ci>V</ci>\n'
            '          <cn cellml:units="mV">50</cn>\n'
            '        </apply>\n'
            '      </apply>\n'
            '      <apply><minus/>\n'
            '        <apply><exp/>\n'
            '          <apply><divide/>\n'
            '            <apply><minus/>\n'
            '              <apply><plus/>\n'
            '                <ci>V</ci>\n'
            '                <cn cellml:units="mV">50</cn>\n'
            '              </apply>\n'
            '            </apply>\n'
            '            <cn cellml:units="mV">10</cn>\n'
            '          </apply>\n'
            '        </apply>\n'
            '        <cn cellml:units="dimensionless">1</cn>\n'
            '      </apply>\n'
            '    </apply>\n'
            '  </apply>\n'

        equation2 =
            '  <apply><eq/>\n'
            '    <ci>beta_m</ci>\n'
            '    <apply><times/>\n'
            '      <cn cellml:units="per_ms">4</cn>\n'
            '      <apply><exp/>\n'
            '        <apply><divide/>\n'
            '          <apply><minus/>\n'
            '            <apply><plus/>\n'
            '              <ci>V</ci>\n'
            '              <cn cellml:units="mV">75</cn>\n'
            '            </apply>\n'
            '          </apply>\n'
            '          <cn cellml:units="mV">18</cn>\n'
            '        </apply>\n'
            '      </apply>\n'
            '    </apply>\n'
            '  </apply>\n'

        equation3 =
            '  <apply><eq/>\n'
            '    <apply><diff/>\n'
            '      <bvar>\n'
            '        <ci>t</ci>\n'
            '      </bvar>\n'
            '      <ci>m</ci>\n'
            '    </apply>\n'
            '    <apply><minus/>\n'
            '      <apply><times/>\n'
            '        <ci>alpha_m</ci>\n'
            '        <apply><minus/>\n'
            '          <cn cellml:units="dimensionless">1</cn>\n'
            '          <ci>m</ci>\n'
            '        </apply>\n'
            '      </apply>\n'
            '      <apply><times/>\n'
            '        <ci>m</ci>\n'
            '        <ci>beta_m</ci>\n'
            '      </apply>\n'
            '    </apply>\n'
            '  </apply>\n'

        mGate.setMath(mathHeader)
        mGate.appendMath(equation1)
        mGate.appendMath(equation2)
        mGate.appendMath(equation3)
        mGate.appendMath(mathFooter)

    }  # end scope of maths for mGate component

    #  2.c Call the validator and expect errors related to missing variables.
    #      Add the variables that are needed.
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("mV")
        mGate.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("ms")
        mGate.addVariable(t)

        alpha_m = Variable()
        alpha_m.setName("alpha_m")
        alpha_m.setUnits("per_ms")
        mGate.addVariable(alpha_m)

        beta_m = Variable()
        beta_m.setName("beta_m")
        beta_m.setUnits("per_ms")
        mGate.addVariable(beta_m)

        m = Variable()
        m.setName("m")
        m.setUnits("dimensionless")
        mGate.addVariable(m)

    #  2.d Call the validator to check the model - expect errors related to
    #      units missing from the model. Add the units that are required.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    per_mV_ms = Units()
    per_mV_ms.setName("per_mV_ms")
    per_mV_ms.addUnit("second", 'milli", -1)
    per_mV_ms.addUnit("volt", 'milli", -1)
    model.addUnits(per_mV_ms)

    per_ms = Units()
    per_ms.setName("per_ms")
    per_ms.addUnit("second", 'milli", -1)
    model.addUnits(per_ms)

    #  2.e Link in the units to the model, and check that there are no more
    #      validation errors in the model.
    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print('-----------------------------------------------')
    print(' STEP 3: Create the h-gate component ')
    print('-----------------------------------------------')

    #  3.a Create the hGate component and add it to the sodium channel component.
    hGate = Component()
    hGate.setName("hGate")
    sodiumChannel.addComponent(hGate)

    #  3.b Add the MathML strings that govern the gate behaviour.
    if True:
        equation1 =
            '  <apply><eq/>\n'\
            '    <ci>alpha_h</ci>\n'\
            '    <apply><times/>\n'\
            '      <cn cellml:units="per_ms">0.07</cn>\n'\
            '      <apply><exp/>\n'\
            '        <apply><divide/>\n'\
            '          <apply><minus/>\n'\
            '            <apply><plus/>\n'\
            '              <ci>V</ci>\n'\
            '              <cn cellml:units="mV">75</cn>\n'\
            '            </apply>\n'\
            '          </apply>\n'\
            '          <cn cellml:units="mV">20</cn>\n'\
            '        </apply>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        equation2 =
            '  <apply><eq/>\n'\
            '    <ci>beta_h</ci>\n'\
            '    <apply><divide/>\n'\
            '      <cn cellml:units="per_ms">1</cn>\n'\
            '      <apply><plus/>\n'\
            '        <apply><exp/>\n'\
            '          <apply><divide/>\n'\
            '            <apply><minus/>\n'\
            '              <apply><plus/>\n'\
            '                <ci>V</ci>\n'\
            '                <cn cellml:units="mV">45</cn>\n'\
            '              </apply>\n'\
            '            </apply>\n'\
            '            <cn cellml:units="mV">10</cn>\n'\
            '          </apply>\n'\
            '        </apply>\n'\
            '        <cn cellml:units="dimensionless">1</cn>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        equation3 =
            '  <apply><eq/>\n'\
            '    <apply><diff/>\n'\
            '       <bvar>\n'\
            '         <ci>t</ci>\n'\
            '       </bvar>\n'\
            '       <ci>h</ci>\n'\
            '    </apply>\n'\
            '    <apply><minus/>\n'\
            '      <apply><times/>\n'\
            '        <ci>alpha_h</ci>\n'\
            '        <apply><minus/>\n'\
            '          <cn cellml:units="dimensionless">1</cn>\n'\
            '          <ci>h</ci>\n'\
            '        </apply>\n'\
            '      </apply>\n'\
            '      <apply><times/>\n'\
            '        <ci>h</ci>\n'\
            '        <ci>beta_h</ci>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

        hGate.setMath(mathHeader)
        hGate.appendMath(equation1)
        hGate.appendMath(equation2)
        hGate.appendMath(equation3)
        hGate.appendMath(mathFooter)
    # ends local scope for hGate maths

    #  3.c Call the validator to list missing variables.  Add them as needed.
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("mV")
        hGate.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("ms")
        hGate.addVariable(t)

        alpha_h = Variable()
        alpha_h.setName("alpha_h")
        alpha_h.setUnits("per_ms")
        hGate.addVariable(alpha_h)

        beta_h = Variable()
        beta_h.setName("beta_h")
        beta_h.setUnits("per_ms")
        hGate.addVariable(beta_h)

        h = Variable()
        h.setName("h")
        h.setUnits("dimensionless")
        hGate.addVariable(h)

    #  3.d Recheck the model, and expect it to be free of errors.
    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print('----------------------------------------------------------')
    print('   STEP 4: Import the controller and parameters')
    print('----------------------------------------------------------')

    #  STEP 4: When a Component (or Units) item is imported it needs:
    #          - to be connected to an ImportSource item
    #              - which in turn stores the url of the source file to be opened
    #          - the name of the item in the source file to be retrieved
    #          - a destination component (or units) item in which to store the
    #            imported information

    #  4.a Create a pointer to an ImportSource item using the create() idiom.
    importer = ImportSource()

    #  4.b Use the ImportSource.setUrl() function to pass the file name containing the controller.
    #      In this case we'll use 'tutorial7_controller.cellml".
    importer.setUrl("tutorial7_controller.cellml")

    #  4.c Create the destination component into which the imported component
    #      will be saved, and name it as usual.  This will be the controller component, and will be at the
    #      top level of the model's encapsulation hierarchy.
    controller = Component()
    controller.setName("controller")
    model.addComponent(controller)

    #  4.d Call the Component.setSourceComponent(ImportSource, std.string) function to
    #      associate the destination controller component with the importer, and
    #      the importer with the name of the item to retrieve.  If you're using the
    #      file from the resources folder, the name of the component to import is 'sodiumChannel_controller".
    controller.setSourceComponent(importer, 'sodiumChannel_controller")

    #  4.e Repeat the above processes to import the component called 'parameters' from the same file.
    #      Note that since they're in the same file, you can reuse the ImportSource instance, and simply
    #      repeat steps 4.c-d.
    parameters = Component()
    parameters.setName("parameters")
    parameters.setSourceComponent(importer, 'parameters")
    model.addComponent(parameters)

    #  4.f Validate the model, expecting it to be free of errors.  Note that the validator does not check
    #      the contents of imports - this is done at the time that they're resolved (see step 5.c below).
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print('----------------------------------------------------------')
    print('   STEP 5: Connect the components ')
    print('----------------------------------------------------------')

    #  STEP 5: Connecting the components together.
    #      When you import something, it isn't instantiated in the model properly until
    #      the model is flattened.  Because it's easier to work with unflattened models
    #      later on (if you want to vary their ingredients etc), you will probably find
    #      that you need to connect imported components to local ones, or to other imported
    #      ones before the model is flattened.
    #      This creates a problem as the variables in those imported components can't yet
    #      be referenced.
    #      The way around this is to create 'dummy' variables in the imported component
    #      placeholders you created (as in step 4.c, for example).  Note that these need
    #      to have the same name as the variables in the import, and will be over-written
    #      by the 'real' ones when the model is flattened.

    #  5.a Create the dummy variables as you would normally, and add them to the imported components.
    #      These are:
    #          - parameters: h, m, E_Na, g_Na
    #          - controller: t, V
    if True:
        h = Variable()
        h.setName("h")
        parameters.addVariable(h)

        m = Variable()
        m.setName("m")
        parameters.addVariable(m)

        E_Na = Variable()
        E_Na.setName("E_Na")
        parameters.addVariable(E_Na)

        g_Na = Variable()
        g_Na.setName("g_Na")
        parameters.addVariable(g_Na)

        t = Variable()
        t.setName("t")
        controller.addVariable(t)

        V = Variable()
        V.setName("V")
        controller.addVariable(V)

    # TODO This is here temporarily to define units and interfaces for the dummy variables.  It shouldn't
    #      really be needed ...
    if True:
        parameters.variable("h").setUnits("dimensionless")
        parameters.variable("m").setUnits("dimensionless")
        parameters.variable("E_Na").setUnits("mV")
        parameters.variable("g_Na").setUnits("mS_per_cm2")
        controller.variable("V").setUnits("mV")
        controller.variable("t").setUnits("ms")

        parameters.variable("h").setInterfaceType("public")
        parameters.variable("m").setInterfaceType("public")
        parameters.variable("E_Na").setInterfaceType("public")
        parameters.variable("g_Na").setInterfaceType("public")
        controller.variable("t").setInterfaceType("public")
        controller.variable("V").setInterfaceType("public")

    #  5.b Add the equivalences between variables throughout the model.  Recall that only variables with
    #      a sibling or parent/child relationship can be connected.

    assert(Variable.addEquivalence(controller.variable("t"), sodiumChannel.variable("t")))
    assert(Variable.addEquivalence(sodiumChannel.variable("t"), mGate.variable("t")))
    assert(Variable.addEquivalence(sodiumChannel.variable("t"), hGate.variable("t")))
    assert(Variable.addEquivalence(controller.variable("V"), sodiumChannel.variable("V")))
    assert(Variable.addEquivalence(sodiumChannel.variable("V"), mGate.variable("V")))
    assert(Variable.addEquivalence(sodiumChannel.variable("V"), hGate.variable("V")))

    assert(Variable.addEquivalence(sodiumChannel.variable("m"), parameters.variable("m")))
    assert(Variable.addEquivalence(mGate.variable("m"), sodiumChannel.variable("m")))
    assert(Variable.addEquivalence(sodiumChannel.variable("h"), parameters.variable("h")))
    assert(Variable.addEquivalence(hGate.variable("h"), sodiumChannel.variable("h")))

    assert(Variable.addEquivalence(sodiumChannel.variable("E_Na"), parameters.variable("E_Na")))
    assert(Variable.addEquivalence(sodiumChannel.variable("g_Na"), parameters.variable("g_Na")))

    #  5.c Validate the model and expect messages related to unspecified interfaces.  Add these to the
    #      variables according to the recommendations.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    sodiumChannel.variable("V").setInterfaceType("public_and_private")
    sodiumChannel.variable("t").setInterfaceType("public_and_private")
    sodiumChannel.variable("g_Na").setInterfaceType("public_and_private")
    sodiumChannel.variable("E_Na").setInterfaceType("public_and_private")
    sodiumChannel.variable("h").setInterfaceType("public_and_private")
    sodiumChannel.variable("m").setInterfaceType("public_and_private")

    mGate.variable("t").setInterfaceType("public")
    mGate.variable("m").setInterfaceType("public_and_private")
    mGate.variable("V").setInterfaceType("public")
    hGate.variable("t").setInterfaceType("public")
    hGate.variable("h").setInterfaceType("public_and_private")
    hGate.variable("V").setInterfaceType("public")

    # 5.e  Even though it won't be used in this tutorial, we need to set the interface types on any variable
    #      in the sodium channel component that will need to be accessible to other components later.  It's
    #      worth thinking about these at the time of writing the component, as it increases its reusability
    #      and usefulness later on.  In this case, we'll only need to set the i_Na sodium current variable
    #      to have a public interface.
    sodiumChannel.variable("i_Na").setInterfaceType("public")

    #  5.f At this stage our model can be written to a CellML file.  As the model
    #      contains import statements, the serialised and printed model would also maintain those
    #      same dependencies, and would need to exist alongside the tutorial7_controller.cellml
    #      file specified earlier.  In later steps we'll disconnect this dependency to allow for
    #      the code generation step.
    #
    #      Check that the model is valid, then create a Printer, and use it to serialise the model.
    #      Write the serialised model to a file.
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    printer = Printer()
    write_file = open("tutorial7_SodiumChannelModel.cellml", "w")
    write_file.write(printer.printModel(model))
    write_file.close()

    print('----------------------------------------------------------')
    print('   STEP 6: Resolve the imports and flatten the model')
    print('----------------------------------------------------------')

    #  6.a Now that all the imports are specified, we need to first resolve them with respect to a
    #      directory location.  This location is either specified with an absolute path, or
    #      relative to the current working directory.
    #      Call the Model.resolveImports(directoryPath) function to resolve the imports.  Check that
    #      it has worked as expected by checking that Model.hasUnresolvedImports() returns false.
    #      Note that:
    #          - The argument of the resolveImports() function is the directory path, ending with a slash.
    #          - For files in the working directory, use a blank string, '".
    model.resolveImports("")
    assert(model.hasUnresolvedImports() == false)

    #  6.b Finally it's time to flatten the model so that it can be used to generate runable code.
    #      This operation will create new local instances of all of the imported items, thereby
    #      removing the model's dependency on imports. Use the Model.flatten() function to do this.
    #      Print the model to the terminal and check that it makes sense.
    model.flatten()
    print_model_to_terminal(model, false)

    #  6.c After flattening a model it's important to note that the model itself has been completely overwritten
    #      with its 'flat' version.  This means that any imported items which you'd previously assigned to pointers
    #      (such as the components defined as destinations for the imports: the controller and initialising components)
    #      have become obsolete.
    #      The easiest thing to do is to refresh their pointers by fetching them from the flattened model.
    #      You can do this using their 'destination' name, eg: controller = model.component("controller") etc.
    controller = model.component("controller")
    parameters = mGate.component("parameters")

    #  6.d Link the units and validate the model a final time.  Expect no errors.
    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print('-----------------------------------------------')
    print('    STEP 7: Generate and output the model ')
    print('-----------------------------------------------')

    #  7.a Create a Generator instance and submit the model for processing.
    #      Expect no errors.
    generator = Generator.create()
    generator.processModel(model)
    print_errors_to_terminal(generator)
    assert(generator.errorCount() == 0)

    #  7.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.
    printer = Printer()
    serialised_model = printer.printModel(model)

    write_file = open("tutorial7_SodiumChannelModel.cellml", "w")
    write_file.write(serialised_model)
    write_file.close()

    #  7.b Retrieve and write the interface code (*.h) and implementation code (*.c) to files.
    write_file = open("tutorial7_SodiumChannelModel.h", "w")
    write_file.write(generator.interfaceCode())
    write_file.close()

    write_file = open("tutorial7_SodiumChannelModel.c", "w")
    write_file.write(generator.implementationCode())
    write_file.close()

    #  7.c Change the profile to Python and reprocess the model.
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)
    generator.processModel(model)

    #  7.d Write the Python implementation code to a .py file.
    write_file = open("tutorial7_SodiumChannelModel.py", "w")
    write_file.write(generator.implementationCode())
    write_file.close()

    print(
        'The model has been output into tutorial7_SodiumChannelModel.[c,h,py,cellml]')

    #  7.e Please seen the tutorial instructions for how to run this simulation using
    #      the simple solver provided.  Then go and have a cuppa, you're done!
}
