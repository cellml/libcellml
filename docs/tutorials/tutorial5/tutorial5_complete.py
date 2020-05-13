"""
    TUTORIAL 5: Modelling a gated ion channel

    This tutorial assumes that you can already:
        - read and deserialise a CellML model from a file (Tutorial 1)
        - retrieve the name and id of models, components, and variables (Tutorial 2),
        - navigate through the hierarchy of the model (Tutorial 2)
        - serialise and print a Model structure to a CellML file (Tutorial 1)
        - create and include user-defined units (Tutorial 3)
        - use the Generator to output a runable model (Tutorial 3, 4)
        - use the simple solver to simulate behaviour (Tutorial 4)
"""

from libcellml import Component, Generator, GeneratorProfile, Model, Printer, Validator, Variable, Units

from tutorial_utilities import print_errors_to_terminal

if __name__ == "__main__":

    print("-----------------------------------------------")
    print("  STEP 1: Create the model and component       ")
    print("-----------------------------------------------")

    #  1.a   Create the model instance.
    model = Model()
    model.setName("Tutorial4_model")

    #  1.b   Create a component and add it into the model.
    component = Component()
    component.setName("component")
    model.addComponent(component)

    #  1.c   Call the validator and print the messages to the terminal.
    #        No errors are expected at this stage.
    validator = Validator()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 2: Define the mathematical behaviour    ")
    print("-----------------------------------------------")

    #  2.a   Define the mathematics.
    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">\n'
    equation1 = \
        '  <apply><eq/>\n'\
        '    <apply><diff/>\n'\
        '      <bvar>\n'\
        '        <ci>t</ci>\n'\
        '      </bvar>\n'\
        '      <ci>y</ci>\n'\
        '    </apply>\n'\
        '    <apply><minus/>\n'\
        '      <apply><times/>\n'\
        '        <ci>alpha_y</ci>\n'\
        '        <apply><minus/>\n'\
        '          <cn cellml:units="dimensionless">1</cn>\n'\
        '          <ci>y</ci>\n'\
        '        </apply>\n'\
        '      </apply>\n'\
        '      <apply><times/>\n'\
        '        <ci>beta_y</ci>\n'\
        '        <ci>y</ci>\n'\
        '      </apply>\n'\
        '    </apply>\n'\
        '  </apply>\n'

    equation2 = \
        '  <apply><eq/>\n'\
        '    <ci>i_y</ci>\n'\
        '    <apply><times/>\n'\
        '      <ci>g_y</ci>\n'\
        '      <apply><minus/>\n'\
        '        <ci>V</ci>\n'\
        '        <ci>E_y</ci>\n'\
        '      </apply>\n'\
        '      <apply><power/>\n'\
        '        <ci>y</ci>\n'\
        '        <ci>gamma</ci>\n'\
        '      </apply>\n'\
        '    </apply>\n'\
        '  </apply>\n'
    math_footer = '</math>'

    #  2.b   Add the maths to the component.  Note that there is only one maths
    #        string stored, so parts which are appended must create a viable
    #        MathML2 string when concatenated.  To completly clear any string which is
    #        already stored, simply call setMath("") with an empty string.
    component.setMath(math_header)
    component.appendMath(equation1)
    component.appendMath(equation2)
    component.appendMath(math_footer)

    #  2.c:  Call the validator and print the messages to the terminal.
    #        Expected errors refer to variables referenced in the maths which
    #        are not (yet) defined in the component, as well as cn element units
    #        which are not defined yet either.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 3: Define the variables and their units ")
    print("-----------------------------------------------")

    #  3.a,b Declaring the variables, their names, units, and initial conditions
    #        Note that the names given to variables must be the same as that used
    #        within the <ci> blocks in the MathML string you created in step 2.a.
    t = Variable()
    t.setName("t")
    t.setUnits("millisecond")

    V = Variable()
    V.setName("V")
    V.setUnits("millivolt")

    alpha_y = Variable()
    alpha_y.setName("alpha_y")
    alpha_y.setUnits("per_millisecond")

    beta_y = Variable()
    beta_y.setName("beta_y")
    beta_y.setUnits("per_millisecond")

    y = Variable()
    y.setName("y")
    y.setUnits("dimensionless")

    E_y = Variable()
    E_y.setName("E_y")
    E_y.setUnits("millivolt")

    i_y = Variable()
    i_y.setName("i_y")
    i_y.setUnits("microA_per_cm2")

    g_y = Variable()
    g_y.setName("g_y")
    g_y.setUnits("milliS_per_cm2")

    gamma = Variable()
    gamma.setName("gamma")
    gamma.setUnits("dimensionless")

    #  3.c Adding the variables to the component.  Note that Variables are
    #      added by their pointer (cf. their name).
    component.addVariable(t)
    component.addVariable(V)
    component.addVariable(E_y)
    component.addVariable(gamma)
    component.addVariable(i_y)
    component.addVariable(g_y)
    component.addVariable(alpha_y)
    component.addVariable(beta_y)
    component.addVariable(y)

    #  3.d Call the validator and print the messages to the terminal.
    #      Expected errors refer to units referred to by these variables, but
    #      which don't (yet) exist in the model.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-------------------------------------------------")
    print("  STEP 4: Define the units and add to the model")
    print("-------------------------------------------------")

    #  4.a Defining the units of millisecond, millivolt, per_millisecond,
    #      microA_per_cm2, and milliS_per_cm2. Note that the dimensionless
    #      units are part of those built-in already, so do not need to be
    #      defined here.
    ms = Units()
    ms.setName("millisecond")
    ms.addUnit("second", "milli")

    mV = Units()
    mV.setName("millivolt")
    mV.addUnit("volt", "milli")

    per_ms = Units()
    per_ms.setName("per_millisecond")
    per_ms.addUnit("millisecond", -1.0)

    microA_per_cm2 = Units()
    microA_per_cm2.setName("microA_per_cm2")
    microA_per_cm2.addUnit("ampere", "micro")
    microA_per_cm2.addUnit("metre", "centi", -2.0)

    mS_per_cm2 = Units()
    mS_per_cm2.setName("milliS_per_cm2")
    mS_per_cm2.addUnit("siemens", "milli")
    mS_per_cm2.addUnit("metre", "centi", -2.0)

    #  4.b Add these units into the model.
    model.addUnits(ms)
    model.addUnits(mV)
    model.addUnits(per_ms)
    model.addUnits(microA_per_cm2)
    model.addUnits(mS_per_cm2)

    #  4.c Validate the final arrangement.  No errors are expected at this stage.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print(" STEP 5: Serialise the model and generate code ")
    print("-----------------------------------------------")

    #  5.a Create a generator instance and pass it the model for processing.
    generator = Generator()
    generator.processModel(model)

    #  5.b Check for errors found in the generator. Add the initial values as needed,
    #      and reprocess the model.
    print_errors_to_terminal(generator)

    V.setInitialValue(0.0)
    alpha_y.setInitialValue(1.0)
    beta_y.setInitialValue(2.0)
    y.setInitialValue(0.0)
    E_y.setInitialValue(-85.0)
    g_y.setInitialValue(36.0)
    gamma.setInitialValue(4.0)

    generator.processModel(model)

    #  5.c Retrieve the output code from the Generator, remembering
    #      that for output in C you will need both the interfaceCode (the
    #      header file contents) as well as the implementationCode (the source
    #      file contents), whereas for Python you need only output the
    #      implementationCode.  Write the file(s).
    profile = GeneratorProfile(GeneratorProfile.Profile.C)
    generator.setProfile(profile)

    implementation_code_C = generator.implementationCode()
    write_file = open("tutorial5_IonChannelModel.c", "w")
    write_file.write(implementation_code_C)
    write_file.close()

    interface_code = generator.interfaceCode()
    write_file = open("tutorial5_IonChannelModel.h", "w")
    write_file.write(interface_code)
    write_file.close()

    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

    implementation_code_python = generator.implementationCode()
    write_file = open("tutorial5_IonChannelModel.py", "w")
    write_file.write(implementation_code_python)
    write_file.close()

    #  5.d Create a Printer item and submit the model for serialisaion
    printer = Printer()
    serialised_model_string = printer.printModel(model)

    #  5.e Write the serialsied model to a file
    write_file = open("tutorial5_IonChannelModel.cellml", "w")
    write_file.write(serialised_model_string)
    write_file.close()

    print(
        "The generated files and serialised CellML files have been written to tutorial5_IonChannelModel.[py,c,h,cellml]")

    #  5.f Check that the files have been written correctly, then please see the
    #      tutorial for instructions on how to simulate the gate behaviour.
