"""
    TUTORIAL 6: COMPONENTS AND CONNECTIONS

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
 """

from libcellml import Component, Generator, GeneratorProfile, Model, Parser, Printer, \
    Units, Variable, Validator

from tutorial_utilities import print_model_to_terminal, print_errors_to_terminal, \
    print_encapsulation_structure_to_terminal

if __name__ == "__main__":

    print("-----------------------------------------------------")
    print("    STEP 1: Read the ion channel component           ")
    print("-----------------------------------------------------")

    # TODO Temporarily removing this section until the parent pointers are working properly
    # #  1.a Read the model created in Tutorial 4.  Note that if you didn't
    # #      do that tutorial you can simply copy the CellML file
    # #      from resources/tutorial4_IonChannelModel.cellml
    # read_file = open("../resources/tutorial5_IonChannelModel.cellml", "r")
    # parser = Parser()
    # model = parser.parseModel(read_file.read())
    # model.setName("Tutorial6_PotassiumChannelModel")

    # #  1.b Print the parsed model to the terminal and check its contents
    # print_model_to_terminal(model)

    # #  1.c Create a Validator and use it to check that the model is ok so far
    # #      by printing the errors to the terminal
    # validator = Validator()
    # validator.validateModel(model)
    # print_errors_to_terminal(validator)

    # #  1.d Retrieve the component and name it "potassiumChannel"
    # potassium_channel = model.component(0)
    # potassium_channel.setName("potassiumChannel")

    validator = Validator()
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">\n'
    math_footer = '</math>'

    model = Model("Tutorial6_PotassiumChannelModel")
    n_gate = Component("nGate")
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


    n_gate.setMath(math_header)
    n_gate.appendMath(equation1)
    n_gate.appendMath(equation2)
    n_gate.appendMath(equation3)
    n_gate.appendMath(math_footer)

    t = Variable("t")
    t.setUnits("millisecond")
    n_gate.addVariable(t)

    V = Variable("V")
    V.setUnits("millivolt")
    n_gate.addVariable(V)

    alpha_n = Variable("alpha_n")
    alpha_n.setUnits("per_millisecond")
    n_gate.addVariable(alpha_n)

    beta_n = Variable("beta_n")
    beta_n.setUnits("per_millisecond")
    n_gate.addVariable(beta_n)

    n = Variable("n")
    n.setUnits("dimensionless")
    n.setInitialValue(0.325)
    n_gate.addVariable(n)

    ms = Units("millisecond")
    ms.addUnit("second", "milli")

    mV = Units("millivolt")
    mV.addUnit("volt", "milli")

    per_ms = Units("per_millisecond")
    per_ms.addUnit("millisecond", -1.0)

    per_mV_ms = Units("per_millivolt_millisecond")
    per_mV_ms.addUnit("per_millisecond")
    per_mV_ms.addUnit("millivolt", -1)

    #  Add these units into the model
    model.addUnits(ms)
    model.addUnits(mV)
    model.addUnits(per_ms)
    model.addUnits(per_mV_ms)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print(" STEP 2: Define the potassium_channel component ")
    print("-----------------------------------------------")

    #  2.a Create the potassium_channel component and add to the model.
    potassium_channel = Component("potassium_channel")
    model.addComponent(potassium_channel)
    potassium_channel.addComponent(n_gate)

    # #  2.b Move the variables out of the n_gate and into to the potassium_channel component.
    # potassium_channel.addVariable(n_gate.variable("E_K"))
    # potassium_channel.addVariable(n_gate.variable("i_K"))
    # potassium_channel.addVariable(n_gate.variable("g_K"))

    # # TODO removing the variables from their old component, shouldn't be needed??
    # n_gate.removeVariable("E_K")
    # n_gate.removeVariable("i_K")
    # n_gate.removeVariable("g_K")
    # n_gate.removeVariable("gamma") # this one needs removal anyway?

    #  2.c Create the remaining variables for the potassium channel
    E_K = Variable("E_K")
    E_K.setUnits("millivolt")
    # E_K.setInitialValue(-85.0)
    potassium_channel.addVariable(E_K)

    i_K = Variable("i_K")
    i_K.setUnits("microA_per_cm2")
    potassium_channel.addVariable(i_K)

    g_K = Variable("g_K")
    g_K.setUnits("milliS_per_cm2")
    g_K.setInitialValue(36.0)
    potassium_channel.addVariable(g_K)

    V = Variable("V")
    V.setUnits("millivolt")
    potassium_channel.addVariable(V)

    t = Variable("t")
    t.setUnits("millisecond")
    potassium_channel.addVariable(t)

    n = Variable("n")
    n.setUnits("dimensionless")
    potassium_channel.addVariable(n)

    Ko = Variable("Ko")
    Ko.setUnits("millimol")
    potassium_channel.addVariable(Ko)

    Ki = Variable("Ki")
    Ki.setUnits("millimol")
    potassium_channel.addVariable(Ki)

    RTF = Variable("RTF")
    RTF.setUnits("millivolt")
    potassium_channel.addVariable(RTF)

    K_conductance = Variable("K_conductance")
    K_conductance.setUnits("milliS_per_cm2")
    potassium_channel.addVariable(K_conductance)

    #  2.d Defining the maths inside the potassium_channel component
    equation1 = \
            '  <apply><eq/>\n'\
            '    <ci>E_K</ci>\n'\
            '    <apply><times/>\n'\
            '      <ci>RTF</ci>\n'\
            '      <apply><ln/>\n'\
            '        <apply><divide/>\n'\
            '          <ci>Ko</ci>\n'\
            '          <ci>Ki</ci>\n'\
            '        </apply>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'
    equation2 = \
            '  <apply><eq/>\n'\
            '    <ci>K_conductance</ci>\n'\
            '    <apply><times/>\n'\
            '      <ci>g_K</ci>\n'\
            '      <apply><power/>\n'\
            '        <ci>n</ci>\n'\
            '        <cn cellml:units="dimensionless">4</cn>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'
    equation3 = \
            '  <apply><eq/>\n'\
            '    <ci>i_K</ci>\n'\
            '    <apply><times/>\n'\
            '      <ci>K_conductance</ci>\n'\
            '      <apply><minus/>\n'\
            '        <ci>V</ci>\n'\
            '        <ci>E_K</ci>\n'\
            '      </apply>\n'\
            '    </apply>\n'\
            '  </apply>\n'

    potassium_channel.setMath(math_header)
    potassium_channel.appendMath(equation1)
    potassium_channel.appendMath(equation2)
    potassium_channel.appendMath(equation3)
    potassium_channel.appendMath(math_footer)

    #  2.e Check for errors.  Expect warnings about the undefined units in the maths and in the
    #      new variables added.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  2.f Add the missing units and recheck the validation
    mM = Units("millimol")
    mM.addUnit("mole", "milli")

    microA_per_cm2 = Units()
    microA_per_cm2.setName("microA_per_cm2")
    microA_per_cm2.addUnit("ampere", "micro")
    microA_per_cm2.addUnit("metre", "centi", -2.0)

    mS_per_cm2 = Units()
    mS_per_cm2.setName("milliS_per_cm2")
    mS_per_cm2.addUnit("siemens", "milli")
    mS_per_cm2.addUnit("metre", "centi", -2.0)

    model.addUnits(mM)
    model.addUnits(microA_per_cm2)
    model.addUnits(mS_per_cm2)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 3: Create the environment component")
    print("-----------------------------------------------")

    #  3.a Creating the new environment component
    environment = Component()
    environment.setName("environment")

    #  3.b Add variables to the component.
    V = Variable("V")
    V.setUnits("millivolt")
    environment.addVariable(V)

    t = Variable("t")
    t.setUnits("millisecond")
    environment.addVariable(t)

    #  3.c Add the new component to the model
    model.addComponent(environment)

    #  3.d Calling the validator to check that our model is valid so far.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("   STEP 4: Define the component hierarchy      ")
    print("-----------------------------------------------")

    #  4.a Change the n_gate component to be a child of the potassium_channel component
    # n_gate.removeParent()
    # model.removeComponent(n_gate)
    # potassium_channel.addComponent(n_gate)

    #  4.b Verify the component hierarchy by printing the model to the screen
    print_model_to_terminal(model)

    #  4.c Define the equivalent variables between components.  Note that because
    #      the variables have been defined within a limited scope (using the {} above)
    #      you will need to retrieve them from each component first.
    Variable.addEquivalence(environment.variable(
        "t"), potassium_channel.variable("t"))
    Variable.addEquivalence(environment.variable(
        "V"), potassium_channel.variable("V"))

    # TODO not sure what's happening here - this line below should fail as not neighbouring components,
    # creates a validation error but should be allowed?
    # Variable::addEquivalence(environment.variable("t"), n_gate.variable("t"))

    #  4.d Validating the model: this should show an error reporting that an
    #      invalid connection has been made between the environment and n_gate
    #      components

    # TODO This should produce a validation error but currently does not?
    # validator.validateModel(model)
    # print_errors_to_terminal(validator)

    #  4.e  Fix the connection error above, and add the voltage and gating variable equivalences
    # Variable::removeEquivalence(environment.variable("t"), n_gate.variable("t"))

    Variable.addEquivalence(
        potassium_channel.variable("t"), n_gate.variable("t"))
    Variable.addEquivalence(
        potassium_channel.variable("V"), n_gate.variable("V"))
    Variable.addEquivalence(
        potassium_channel.variable("n"), n_gate.variable("n"))

    # TODO This should produce a validation error but currently does not?
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  4.f Add the interface specification.  The environment component is a sibling of the potassium_channel
    #      component, so they will both use the public interface.  The n_gate component is a child of the
    #      potassium_channel, so will use the public interface.  The potassium_channel is the parent of the
    #      n_gate component, so will need an additional private interface.  The n_gate will have a public
    #      interface to its parent, the potassium_channel.  Thus for the V and t variables:
    #          - environment . public
    #          - potassium_channel . public_and_private
    #          - n_gate . public
    #      Because the n variable is shared only between the potassium_channel and the n_gate, we don't need to
    #      use the public_and_private designation there just private on the parent and public on the child.

    environment.variable("t").setInterfaceType("public")
    environment.variable("V").setInterfaceType("public")
    potassium_channel.variable("t").setInterfaceType("public_and_private")
    potassium_channel.variable("V").setInterfaceType("public_and_private")
    n_gate.variable("t").setInterfaceType("public")
    n_gate.variable("V").setInterfaceType("public")
    potassium_channel.variable("n").setInterfaceType("private")
    n_gate.variable("n").setInterfaceType("public")

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("     STEP 5: Define the driving function       ")
    print("-----------------------------------------------")

    #  5.a Define a MathML string representing the voltage clamp
    voltage_clamp_maths = \
        '  <apply><eq/>\n'\
        '    <ci>V</ci>\n'\
        '    <piecewise>\n'\
        '      <piece>\n'\
        '        <cn cellml:units="millivolt">0</cn>\n'\
        '        <apply><lt/><ci>t</ci><cn cellml:units="millisecond">5</cn></apply>\n'\
        '      </piece>\n'\
        '      <piece>\n'\
        '        <cn cellml:units="millivolt">0</cn>\n'\
        '        <apply><gt/><ci>t</ci><cn cellml:units="millisecond">15</cn></apply>\n'\
        '      </piece>\n'\
        '      <otherwise>\n'\
        '        <cn cellml:units="millivolt">-85</cn>\n'\
        '      </otherwise>\n'\
        '    </piecewise>\n'\
        '  </apply>\n'\

    #  5.b Add this to the maths for the environment component.
    environment.setMath(math_header)
    environment.appendMath(voltage_clamp_maths)
    environment.appendMath(math_footer)

    #  5.c Validate the model including this new maths block
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("    STEP 6: Generate code and output model     ")
    print("-----------------------------------------------")

    #  6.a Call the generator to process the model and output errors to the terminal
    #      Expect errors related to initialisation/non-computation of variables in the potassium channel.
    generator = Generator()
    generator.processModel(model)
    print_errors_to_terminal(generator)

    #  6.b Initialise the variables: Ko = 3, Ki = 90, RTF = 25,
    potassium_channel.variable("Ko").setInitialValue(3)
    potassium_channel.variable("Ki").setInitialValue(90)
    potassium_channel.variable("RTF").setInitialValue(25)

    generator.processModel(model)
    print_errors_to_terminal(generator)

    header_file = open("tutorial6_PotassiumChannelModel_generated.h", "w")
    header_file.write(generator.interfaceCode())
    header_file.close()

    source_file = open("tutorial6_PotassiumChannelModel_generated.c", "w")
    source_file.write(generator.implementationCode())
    source_file.close()

    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)
    generator.processModel(model)

    python_file = open("tutorial6_PotassiumChannelModel_generated.py", "w")
    python_file.write(generator.implementationCode())
    python_file.close()

    print("The generated '"+model.name() +
          "' model has been writen to: tutorial6_PotassiumChannelModel_generated.[c,h,py]")

    #  6.a Serialise the model and output to a CellML file
    printer = Printer()
    out_file = open("tutorial6_PotassiumChannelModel.cellml", "w")
    out_file.write(printer.printModel(model))
    out_file.close()

    print("The created '" + model.name() +
          "' model has been printed to tutorial6_PotassiumChannelModel.cellml")
