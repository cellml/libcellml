'''
       TUTORIAL 6: POTASSIUM CHANNEL MODEL

   This tutorial explores the ability of CellML to represent more than one
   modelled process at a time using components with connections between them.
   By the time you have worked through Tutorial 6 you will be able to:
       - Assemble a multi-component model using the API; and
       - Inter-connect the components using the equivalent variables functionality.

   Tutorial 6 assumes that you are already comfortable with:
       - File manipulation and summarising using the utility functions;
       - Model creation through the API; and
       - Debugging the model using the Validator functionality.
'''

from libcellml import Component, Generator, GeneratorProfile, Model, Parser, Printer, Units, Validator, Variable
from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal

if __name__ == "__main__":

    #  0.a Setup useful things
    validator = Validator()
    mathHeader = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">\n'
    mathFooter = '</math>'

    print("----------------------------------------------------------")
    print("   STEP 1: Define the potassiumChannel component ")
    print("----------------------------------------------------------")

    #  STEP 1: Define the potassiumChannel component.
    #      As in the previous Tutorial 5, we define an ion channel, but this time make it
    #      specific to potassium.  We also introduce voltage dependence into the alpha and
    #      beta gate rates, and move them into a separate component to make it cleaner.
    #      This separate component is the nGate component, and will be defined in Step 2.

    #  1.a Create a model and add to it a new potassiumChannel component.
    model = Model()
    model.setName("Tutorial6_PotassiumChannelModel")

    potassiumChannel = Component()
    potassiumChannel.setName("potassiumChannel")
    model.addComponent(potassiumChannel)

    #  1.b Define the maths inside the potassiumChannel component.  You might like to use
    #      braces {} to limit the scope of your definition.
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

        potassiumChannel.setMath(mathHeader)
        potassiumChannel.appendMath(equation)
        potassiumChannel.appendMath(mathFooter)
    # end scope of maths in this component

    #  1.c Call the validator and expect it to report errors related to missing variables and units.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.d Create the variables needed and add them to the potassium channel component
    E_K = Variable()
    E_K.setName("E_K")
    E_K.setUnits("millivolt")
    potassiumChannel.addVariable(E_K)

    i_K = Variable()
    i_K.setName("i_K")
    i_K.setUnits("microA_per_cm2")
    potassiumChannel.addVariable(i_K)

    g_K = Variable()
    g_K.setName("g_K")
    g_K.setUnits("milliS_per_cm2")
    potassiumChannel.addVariable(g_K)

    V = Variable()
    V.setName("V")
    V.setUnits("millivolt")
    potassiumChannel.addVariable(V)

    t = Variable()
    t.setName("t")
    t.setUnits("millisecond")
    potassiumChannel.addVariable(t)

    n = Variable()
    n.setName("n")
    n.setUnits("dimensionless")
    potassiumChannel.addVariable(n)

    #  1.e Check for errors.  Expect warnings about the undefined units in the maths and in the
    #      new variables added.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.f Add the missing units.  Verify that the model is now free of validation errors.
    #  NOTE: If, even after adding the Units the validator continues to return an error, you
    #      need to call the Model.linkUnits() function to link the units.  Unlinked units
    #      can occur when variables call their setUnits() function with
    #      a string argument of the Units item's name, rather than the Units item itself.
    mV = Units()
    mV.setName("millivolt")
    mV.addUnit("volt", "milli")

    microA_per_cm2 = Units()
    microA_per_cm2.setName("microA_per_cm2")
    microA_per_cm2.addUnit("ampere", "micro")
    microA_per_cm2.addUnit("metre", "centi", -2.0)

    mS_per_cm2 = Units()
    mS_per_cm2.setName("milliS_per_cm2")
    mS_per_cm2.addUnit("siemens", "milli")
    mS_per_cm2.addUnit("metre", "centi", -2.0)

    ms = Units()
    ms.setName("millisecond")
    ms.addUnit("second", "milli")

    mM = Units()
    mM.setName("millimol")
    mM.addUnit("mole", "milli")

    model.addUnits(ms)
    model.addUnits(mV)
    model.addUnits(mM)
    model.addUnits(microA_per_cm2)
    model.addUnits(mS_per_cm2)

    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print("----------------------------------------------------------")
    print("   STEP 2: Create the nGate component  ")
    print("----------------------------------------------------------")

    #  STEP 2: Create the nGate component
    #      This model differs from the one in Tutorial 5 in that voltage dependence is
    #      introduced into the opening and closing rates.  This dependence is handled in
    #      a separate component, the nGate component, which you'll define here.

    #  2.a Create an nGate component, and add it to the potassiumChannel component (NB: not the model!).
    #      Adding it to the component creates an encapsulation hierarchy, which affects which components
    #      have access to each other.  It also means that if the potassiumChannel component is
    #      moved or imported somewhere else, then the nGate child component will be included too.
    nGate = Component()
    nGate.setName("nGate")
    potassiumChannel.addComponent(nGate)

    #  2.b Add the mathematics to the nGate component and validate the model.
    #      Expect errors relating to missing variables.
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

    nGate.setMath(mathHeader)
    nGate.appendMath(equation1)
    nGate.appendMath(equation2)
    nGate.appendMath(equation3)
    nGate.appendMath(mathFooter)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  2.c Add the missing variables to the nGate component, link the units, and validate again.
    #      Expect errors relating to missing units.
    t = Variable()
    t.setName("t")
    t.setUnits("millisecond")
    nGate.addVariable(t)

    V = Variable()
    V.setName("V")
    V.setUnits("millivolt")
    nGate.addVariable(V)

    alpha_n = Variable()
    alpha_n.setName("alpha_n")
    alpha_n.setUnits("per_millisecond")
    nGate.addVariable(alpha_n)

    beta_n = Variable()
    beta_n.setName("beta_n")
    beta_n.setUnits("per_millisecond")
    nGate.addVariable(beta_n)

    n = Variable()
    n.setName("n")
    n.setUnits("dimensionless")
    nGate.addVariable(n)

    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  2.d Create the missing units and add them to the model.  Link the model's
    #      units and validate again.  Expect the model to be free of errors.
    per_ms = Units()
    per_ms.setName("per_millisecond")
    per_ms.addUnit("second", "milli", -1)
    model.addUnits(per_ms)

    per_mV_ms = Units()
    per_mV_ms.setName("per_millivolt_millisecond")
    per_mV_ms.addUnit("per_millisecond")
    per_mV_ms.addUnit("millivolt", -1)
    model.addUnits(per_mV_ms)

    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print("----------------------------------------------------------")
    print("   STEP 3: Read the controllers ")
    print("----------------------------------------------------------")

    #  STEP 3: The controller is a component at the top level of this model.
    #      This allows for it to be more easily interchangable between runs and stimulus
    #      conditions.  In later tutorials we will move this component into an external file so that the
    #      model is separate from the running parameters and initial conditions.

    #  3.a Create a Parser, and use it to read a temporary model from the controller file supplied.
    read_file = open("../resources/tutorial6_controller.cellml", "r")
    parser = Parser()
    parsed_model = parser.parseModel(read_file.read())

    #  3.b From the parsed model, retrieve the component named "controller", remove its parent,
    #      and add it to the current model at the top level.
    controller = parsed_model.component("controller")
    controller.removeParent()
    model.addComponent(controller)

    #  3.c Repeat the process to retrieve the "parameters" component and add to
    #      the current model at the top level.
    parameters = parsed_model.component("parameters")
    parameters.removeParent()
    model.addComponent(parameters)

    #  3.d Print the model to the terminal and check its component hierarchy matches:
    #      ─ model:
    #          ├─ component: controller
    #          ├─ component: parameters
    #          └─ component: potassium channel
    #              └─ component: n-gate
    print_model_to_terminal(model)

    #  3.e Link units and revalidate the model.  Check that there are no errors.
    model.linkUnits()
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print("----------------------------------------------------------")
    print("   STEP 4: Connect the components together ")
    print("----------------------------------------------------------")

    #  STEP 4: Connect the components together.
    #      In order for the voltage dependence of the alpha and beta rates within
    #      the nGate component to affect the current in the potassiumChannel component
    #      some of the variables need to share their values between the components.
    #      This is done using variable equivalence and interfaces.

    #  4.a Set the equivalent variable pairs between the nGate and potassiumChannel components.
    #      These are:
    #          - voltage, V
    #          - time, t
    #          - gate status, n
    #      Use the Variable.addEquivalence(VariablePtr, VariablePtr) function.

    Variable.addEquivalence(potassiumChannel.variable("n"), nGate.variable("n"))
    Variable.addEquivalence(controller.variable("V"), potassiumChannel.variable("V"))
    Variable.addEquivalence(controller.variable("t"), potassiumChannel.variable("t"))
    Variable.addEquivalence(controller.variable("t"), nGate.variable("t"))
    Variable.addEquivalence(controller.variable("V"), nGate.variable("V"))

    Variable.addEquivalence(parameters.variable("E_K"), potassiumChannel.variable("E_K"))
    Variable.addEquivalence(parameters.variable("g_K"), potassiumChannel.variable("g_K"))
    Variable.addEquivalence(parameters.variable("n"), nGate.variable("n"))

    #  4.b Validate the model.  Expect errors related to unspecified interface types and invalid connections.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  4.c (if required) Remove the equivalences between too-distant components using the
    #  Variable.removeEquivalence(VariablePtr, VariablePtr) function, and connect to the correct
    #  component variables instead.

    Variable.removeEquivalence(controller.variable("t"), nGate.variable("t"))
    Variable.removeEquivalence(controller.variable("V"), nGate.variable("V"))
    Variable.removeEquivalence(parameters.variable("n"), nGate.variable("n"))

    Variable.addEquivalence(potassiumChannel.variable("t"), nGate.variable("t"))
    Variable.addEquivalence(potassiumChannel.variable("V"), nGate.variable("V"))
    Variable.addEquivalence(parameters.variable("n"), potassiumChannel.variable("n"))
    Variable.addEquivalence(nGate.variable("n"), potassiumChannel.variable("n"))

    #  4.d Set the recommended interface types for all of the variables with connections.
    potassiumChannel.variable("t").setInterfaceType("public_and_private")
    potassiumChannel.variable("V").setInterfaceType("public_and_private")
    potassiumChannel.variable("E_K").setInterfaceType("public_and_private")
    potassiumChannel.variable("g_K").setInterfaceType("public_and_private")
    potassiumChannel.variable("n").setInterfaceType("public_and_private")
    nGate.variable("n").setInterfaceType("public_and_private")
    nGate.variable("t").setInterfaceType("public")
    nGate.variable("V").setInterfaceType("public")

    #  4.e Revalidate the model, and check that it is now free of errors.
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    assert(validator.errorCount() == 0)

    print("----------------------------------------------------------")
    print("   STEP 5: Generate the model and output")
    print("----------------------------------------------------------")

    #  5.a Create a Generator instance and pass it the model for processing.  Check for errors and
    #      print them to the terminal.  We expect to see errors reporting that some variables are not
    #      computed or not initialised.
    generator = Generator()
    generator.processModel(model)
    print_errors_to_terminal(generator)

    #  5.b Create a Printer instance and use it to serialise the model.  Print this to a *.cellml file.
    printer = Printer()
    serialised_model = printer.printModel(model)

    write_file = open("tutorial6_PotassiumChannelModel.cellml", "w")
    write_file.write(serialised_model)
    write_file.close()

    #  5.c Write the interface code to a .h file.
    write_file = open("tutorial6_PotassiumChannelModel.h", "w")
    write_file.write(generator.interfaceCode())
    write_file.close()

    #  5.d Write the implementation code to a .c file.
    write_file = open("tutorial6_PotassiumChannelModel.c", "w")
    write_file.write(generator.implementationCode())
    write_file.close()

    #  5.e Change the profile to Python and reprocess the model.
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)
    generator.processModel(model)

    #  5.f Write the Python implementation code to a .py file.
    write_file = open("tutorial6_PotassiumChannelModel.py", "w")
    write_file.write(generator.implementationCode())
    write_file.close()

    print("The created '" + model.name() +
          "' model has been output to tutorial6_PotassiumChannelModel.[cellml,py,c,h]")

    #  5.g Please see the instructions in the tutorial for how to run a
    #      simulation of this model using the simple solver provided.
    #      Then go and have a cuppa, you're done!
