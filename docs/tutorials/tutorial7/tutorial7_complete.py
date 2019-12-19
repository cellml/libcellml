"""
    TUTORIAL 7: Creating the Sodium Channel

    This tutorial is an opportunity to practise creating models from
    scratch using the libCellML API.  The model you create here will
    be used later on in Tutorial ??.

    Tutorial 7 assumes that you are already comfortable with:
        - the concept of component hierarchy and encapsulation (Tutorial 5)
        - the use of the API to create all of the entities in a model (Tutorial 3)
        - the content MathML2 markup for mathematical equations (Tutorial 4)
        - serialisation and printing of a model to a CellML file (Tutorial 1)

"""

from libcellml import Component, Generator, GeneratorProfile, Model, Printer, Units, Validator, Variable

from tutorial_utilities import print_errors_to_terminal

if __name__ == "__main__":
    #  0 Setup stuff that is used throughout
    validator = Validator()
    model = Model()
    model.setName("Tutorial7_SodiumChannelModel")

    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    print("-----------------------------------------------")
    print("  STEP 1: Creating the sodium channel")
    print("-----------------------------------------------")

    #  1.a Create the component instance, name it, and add to the model
    sodium_channel = Component()
    sodium_channel.setName("sodiumChannel")
    model.addComponent(sodium_channel)

    #  1.b Add the MathML representing the governing equations
    if True:
        equation1 = \
            '<apply><eq/>\
                <ci>Na_conductance</ci>\
                <apply><times/>\
                    <ci>g_Na</ci>\
                    <ci>h</ci>\
                    <apply><power/>\
                        <ci>m</ci>\
                        <cn cellml:units=\"dimensionless\">3</cn>\
                    </apply>\
                </apply>\
            </apply>'

        equation2 = \
            '<apply><eq/>\
                <ci>i_Na</ci>\
                <apply><times/>\
                    <ci>Na_conductance</ci>\
                    <apply><minus/>\
                        <ci>V</ci>\
                        <ci>E_Na</ci>\
                    </apply>\
                </apply>\
            </apply>'

        sodium_channel.setMath(math_header)
        sodium_channel.appendMath(equation1)
        sodium_channel.appendMath(equation2)
        sodium_channel.appendMath(math_footer)

    #  1.c Add the variables
    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("mV")
        sodium_channel.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("ms")
        sodium_channel.addVariable(t)

        h = Variable()
        h.setName("h")
        h.setUnits("dimensionless")
        h.setInitialValue(1.0)
        sodium_channel.addVariable(h)

        m = Variable()
        m.setName("m")
        m.setUnits("dimensionless")
        sodium_channel.addVariable(m)

        g_Na = Variable()
        g_Na.setName("g_Na")
        g_Na.setUnits("mS_per_cm2")
        g_Na.setInitialValue(120)
        sodium_channel.addVariable(g_Na)

        E_Na = Variable()
        E_Na.setName("E_Na")
        E_Na.setUnits("mV")
        sodium_channel.addVariable(E_Na)

        i_Na = Variable()
        i_Na.setName("i_Na")
        i_Na.setUnits("microA_per_cm2")
        sodium_channel.addVariable(i_Na)

        Na_conductance = Variable()
        Na_conductance.setName("Na_conductance")
        Na_conductance.setUnits("mS_per_cm2")
        sodium_channel.addVariable(Na_conductance)

    #  1.d Add the units

    mV = Units()
    mV.setName("mV")
    mV.addUnit("volt", "milli")
    model.addUnits(mV)

    ms = Units()
    ms.setName("ms")
    ms.addUnit("second", "milli")
    model.addUnits(ms)

    mS_per_cm2 = Units()
    mS_per_cm2.setName("mS_per_cm2")
    mS_per_cm2.addUnit("siemens", "milli")
    mS_per_cm2.addUnit("metre", "centi", -2)
    model.addUnits(mS_per_cm2)

    microA_per_cm2 = Units()
    microA_per_cm2.setName("microA_per_cm2")
    microA_per_cm2.addUnit("ampere", "micro")
    microA_per_cm2.addUnit("metre", "centi", -2)
    model.addUnits(microA_per_cm2)

    mM = Units()
    mM.setName("mM")
    mM.addUnit("mole", "milli")
    model.addUnits(mM)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 2: Creating the m-gate")
    print("-----------------------------------------------")

    #  2.a Create the component and add it to the sodium channel component
    mGate = Component()
    mGate.setName("mGate")
    sodium_channel.addComponent(mGate)

    #  2.b Add the MathML strings which govern the behavior of this gate
    if True:
        equation1 = \
            '<apply><eq/>\
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
            </apply>'

        equation2 = \
            '<apply><eq/>\
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
            </apply>'

        equation3 = \
            '<apply><eq/>\
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
            </apply>'

        mGate.setMath(math_header)
        mGate.appendMath(equation1)
        mGate.appendMath(equation2)
        mGate.appendMath(equation3)
        mGate.appendMath(math_footer)

    #  2.c Call the validator - expect errors related to missing variables, then
    #      add the variables needed

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
    #      units missing from the model.  Add them in as needed.

    per_mV_ms = Units()
    per_mV_ms.setName("per_mV_ms")
    per_mV_ms.addUnit("second", "milli", -1)
    per_mV_ms.addUnit("volt", "milli", -1)
    model.addUnits(per_mV_ms)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 3: Creating the h-gate")
    print("-----------------------------------------------")

    #  3.a Create the hGate component and add it to the sodium channel component
    hGate = Component()
    hGate.setName("hGate")
    sodium_channel.addComponent(hGate)

    #  3.b Adding the MathML strings
    if True:
        equation1 = \
            '<apply><eq/>\
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
            </apply>'

        equation2 = \
            '<apply><eq/>\
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
            </apply>'

        equation3 = \
            '<apply><eq/>\
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
            </apply>'

        hGate.setMath(math_header)
        hGate.appendMath(equation1)
        hGate.appendMath(equation2)
        hGate.appendMath(equation3)
        hGate.appendMath(math_footer)

    #  3.c Adding the variables
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

    #  3.d Add the missing units
    per_ms = Units()
    per_ms.setName("per_ms")
    per_ms.addUnit("second", "milli", -1)
    model.addUnits(per_ms)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 4: Creating the environment component")
    print("-----------------------------------------------")

    #  4.a Creating the new environment component
    environment = Component()
    environment.setName("environment")

    #  4.b Add variables to the component.
    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("mV")
        environment.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("ms")
        environment.addVariable(t)

    #  4.c Add the new component to the model and validate
    model.addComponent(environment)

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 5: Connecting variables and components")
    print("-----------------------------------------------")

    #  5.a Connecting the equivalent variables between all the components
    Variable.addEquivalence(environment.variable("t"),
                            sodium_channel.variable("t"))
    Variable.addEquivalence(sodium_channel.variable("t"), mGate.variable("t"))
    Variable.addEquivalence(sodium_channel.variable("t"), hGate.variable("t"))
    environment.variable("t").setInterfaceType("public")
    sodium_channel.variable("t").setInterfaceType("public_and_private")
    mGate.variable("t").setInterfaceType("public")
    hGate.variable("t").setInterfaceType("public")

    Variable.addEquivalence(environment.variable("V"),
                            sodium_channel.variable("V"))
    Variable.addEquivalence(sodium_channel.variable("V"), mGate.variable("V"))
    Variable.addEquivalence(sodium_channel.variable("V"), hGate.variable("V"))
    environment.variable("V").setInterfaceType("public")
    sodium_channel.variable("V").setInterfaceType("public_and_private")
    mGate.variable("V").setInterfaceType("public")
    hGate.variable("V").setInterfaceType("public")

    Variable.addEquivalence(sodium_channel.variable("m"), mGate.variable("m"))
    sodium_channel.variable("m").setInterfaceType("private")
    mGate.variable("m").setInterfaceType("public")

    Variable.addEquivalence(sodium_channel.variable("h"), hGate.variable("h"))
    sodium_channel.variable("h").setInterfaceType("private")
    hGate.variable("h").setInterfaceType("public")

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("       STEP 6: Set the driving function")
    print("-----------------------------------------------")

    #  6.a Create the MathML controlling the driving function
    if True:
        voltage_clamp_maths = \
            '<apply><eq/>\
                <ci>V</ci>\
                <piecewise>\
                    <piece>\
                        <cn cellml:units="mV">-85</cn>\
                        <apply><lt/><ci>t</ci><cn cellml:units="ms">5</cn></apply>\
                    </piece>\
                        <piece>\
                        <cn cellml:units="mV">-85</cn>\
                        <apply><gt/><ci>t</ci><cn cellml:units="ms">15</cn></apply>\
                    </piece>\
                    <otherwise>\
                        <cn cellml:units="mV">-20</cn>\
                    </otherwise>\
                </piecewise>\
            </apply>'

        environment.setMath(math_header)
        environment.appendMath(voltage_clamp_maths)
        environment.appendMath(math_footer)

    #  6.b Validate the final model
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("    STEP 7: Set the initial conditions")
    print("-----------------------------------------------")

    sodium_channel.variable("g_Na").setInitialValue(120)
    sodium_channel.variable("E_Na").setInitialValue(35)
    hGate.variable("h").setInitialValue(0.6)
    mGate.variable("m").setInitialValue(0.05)

    print("-----------------------------------------------")
    print("   STEP 8: Generate a Python file")
    print("-----------------------------------------------")

    generator = Generator()
    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

    generator.processModel(model)
    print_errors_to_terminal(generator)

    implementation_code = generator.implementationCode()
    write_file = open("tutorial7_generated.py", "w")
    write_file.write(implementation_code)
    print("The {} has been printed to tutorial7_generated.py".format(model.name()))

    printer = Printer()
    serialised_model = printer.printModel(model)
    out_file = "tutorial7_SodiumChannelModel.cellml"
    write_file = open(out_file, "w")
    write_file.write(serialised_model)
    print("The {m} has been printed to {n}".format(m=model.name(), n=out_file))
