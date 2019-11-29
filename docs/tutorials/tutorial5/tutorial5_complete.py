"""
    TUTORIAL 5: COMPONENTS AND CONNECTIONS

    This tutorial explores the ability of CellML to represent more than one
    modelled process at a time using components with connections between them.
    By the time you have worked through Tutorial 5 you will be able to:
        - import a Component or Units item from an existing CellML file
        - assemble a multi-component model using the API
        - inter-connect the components using the equivalent variables
        functionality
        - validate and debug the constructed model

    Tutorial 5 assumes that you are already comfortable with:
        - file manipulation and summarising using the utility functions
        - model creation through the API
        - debugging the model using the Validator functionality
 """

from libcellml import Component, Parser, Printer, Units, Variable, Validator

from utilities.tutorial_utilities import print_model_to_terminal, print_errors_to_terminal, \
    print_encapsulation_structure_to_terminal

if __name__ == "__main__":

    print("-----------------------------------------------------")
    print("    STEP 1: Read the ion channel component           ")
    print("-----------------------------------------------------")

    #  1.a Read the model created in Tutorial 4.  Note that if you didn't
    #      do that tutorial you can simply copy the CellML file
    #      from resources/tutorial4_IonChannelModel.cellml
    read_file = open("../resources/tutorial4_IonChannelModel.cellml", "r")
    parser = Parser()
    model = parser.parseModel(read_file.read())
    model.setName("Tutorial5_PotassiumChannelModel")

    #  1.b Print the parsed model to the terminal and check its contents
    print_model_to_terminal(model)

    #  1.c Create a Validator and use it to check that the model is ok so far
    #      by printing the errors to the terminal
    validator = Validator()
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    #  1.d Retrieve the component and name it "potassiumChannel"
    potassium_channel = model.component(0)
    potassium_channel.setName("potassiumChannel")

    print("-----------------------------------------------")
    print("  STEP 2: Create the environment component")
    print("-----------------------------------------------")

    #  2.a  Creating the new environment component
    environment = Component()
    environment.setName("environment")

    #  2.b  Add variables to the component.  Use the if True statement to create a limited scope for the variable
    #       definition

    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("millivolt")
        environment.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("millisecond")
        environment.addVariable(t)

    #  2.c Add the new component to the model
    model.addComponent(environment)

    #  2.d Calling the validator to check that our model is valid so far.
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 3: Define the n-gate component ")
    print("-----------------------------------------------")

    #  3.a Creating the n-gate component and the variables it contains

    nGate = Component()
    nGate.setName("nGate")

    math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
    math_footer = '</math>'

    if True:
        V = Variable()
        V.setName("V")
        V.setUnits("millivolt")
        nGate.addVariable(V)

        t = Variable()
        t.setName("t")
        t.setUnits("millisecond")
        nGate.addVariable(t)

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

        #  3.b Creating the MathML for the n-gate component and adding it in.
        equation1 = \
            '<apply>\
                <eq/>\
                <ci>alpha_n</ci>\
                <apply>\
                    <divide/>\
                    <apply>\
                        <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="per_millivolt_millisecond">0.01</cn>\
                        <apply>\
                            <plus/>\
                            <ci>V</ci>\
                            <cn cellml:units="millivolt">10</cn>\
                        </apply>\
                    </apply>\
                    <apply>\
                        <minus/>\
                        <apply>\
                            <exp/>\
                            <apply>\
                                <divide/>\
                                <apply>\
                                    <plus/>\
                                    <ci>V</ci>\
                                    <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="millivolt">10</cn>\
                                </apply>\
                                <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="millivolt">10</cn>\
                            </apply>\
                        </apply>\
                        <cn cellml:units="dimensionless">1</cn>\
                    </apply>\
                </apply>\
            </apply>'

        equation2 = \
            '<apply>\
                <eq/>\
                <ci>beta_n</ci>\
                <apply>\
                    <times/>\
                    <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="per_millisecond">0.125</cn>\
                    <apply>\
                        <exp/>\
                        <apply>\
                            <divide/>\
                            <ci>V</ci>\
                            <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="millivolt">80</cn>\
                        </apply>\
                    </apply>\
                </apply>\
            </apply>'

        equation3 = \
            '<apply>\
                <eq/>\
                <apply>\
                    <diff/>\
                    <bvar>\
                        <ci>t</ci>\
                    </bvar>\
                    <ci>n</ci>\
                </apply>\
                <apply>\
                    <minus/>\
                    <apply>\
                        <times/>\
                        <ci>alpha_n</ci>\
                        <apply>\
                            <minus/>\
                            <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="dimensionless">1</cn>\
                            <ci>n</ci>\
                        </apply>\
                    </apply>\
                    <apply>\
                        <times/>\
                        <ci>beta_n</ci>\
                        <ci>n</ci>\
                    </apply>\
                </apply>\
            </apply>'

        nGate.setMath(math_header)
        nGate.appendMath(equation1)
        nGate.appendMath(equation2)
        nGate.appendMath(equation3)
        nGate.appendMath(math_footer)

    #  3.c Add the n-gate component into the model.
    model.addComponent(nGate)

    #  3.d Add the missing units (connected to the constant in equation 1) and recheck the validation
    per_mVms = Units()
    per_mVms.setName("per_millivolt_millisecond")
    per_mVms.addUnit("volt", "milli", -1)
    per_mVms.addUnit("second", "milli", -1)
    model.addUnits(per_mVms)
    validator.validateModel(model)
    print_errors_to_terminal(validator)
    print_encapsulation_structure_to_terminal(model)

    print("-----------------------------------------------")
    print("  STEP 4: Define the component hierarchy       ")
    print("-----------------------------------------------")

    #  4.a Change the nGate component to be a child of the potassiumChannel component
    model.removeComponent(nGate)
    potassium_channel.addComponent(nGate)

    #  4.b Verify the component hierarchy by printing the model to the screen
    print_encapsulation_structure_to_terminal(model)

    #  4.c Define the equivalent variables between components.  Note that because
    #      the variables have been defined within a limited scope (using the if True as above)
    #      you will need to retrieve them from each component first.
    # Variable.addEquivalence(environment.variable("t"), potassium_channel.variable("t"))

    #  4.d Validating the model: this should show an error reporting that an
    #      invalid connection has been made between the environment and nGate
    #      components
    # TODO This should produce a validation error but currently does not?
    print(2)
    validator.validateModel(model)
    print(3)
    print_errors_to_terminal(validator)

    #  4.e  Fix the connection error above, and add the voltage and gating variable equivalences
    Variable.removeEquivalence(environment.variable("t"), nGate.variable("t"))
    Variable.addEquivalence(potassium_channel.variable("t"), nGate.variable("t"))
    Variable.addEquivalence(environment.variable("V"), potassium_channel.variable("V"))
    Variable.addEquivalence(potassium_channel.variable("V"), nGate.variable("V"))
    Variable.addEquivalence(potassium_channel.variable("n"), nGate.variable("n"))

    #  4.f Add the interface specification.  The environment component is a sibling of the potassiumChannel
    #      component, so they will both use the public interface.  The nGate component is a child of the
    #      potassiumChannel, so will use the public interface.  The potassiumChannel is the parent of the
    #      nGate component, so will need an additional private interface.  The nGate will have a public
    #      interface to its parent, the potassiumChannel.  Thus for the V and t variables:
    #          - environment -> public
    #          - potassiumChannel -> public_and_private
    #          - nGate -> public
    #      Because the n variable is shared only between the potassiumChannel and the nGate, we don't need to
    #      use the public_and_private designation there just private on the parent and public on the child.

    environment.variable("t").setInterfaceType("public")
    environment.variable("V").setInterfaceType("public")
    potassium_channel.variable("t").setInterfaceType("public_and_private")
    potassium_channel.variable("V").setInterfaceType("public_and_private")
    nGate.variable("t").setInterfaceType("public")
    nGate.variable("V").setInterfaceType("public")
    potassium_channel.variable("n").setInterfaceType("private")
    nGate.variable("n").setInterfaceType("public")

    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("  STEP 5: Define the driving function ")
    print("-----------------------------------------------")

    #  5.a Define a MathML string representing the voltage clamp
    voltageClampMaths = \
        '<apply>\
            <eq/>\
            <ci>V</ci>\
            <piecewise>\
                <piece>\
                    <cn cellml:units="millivolt">0</cn>\
                    <apply><lt/><ci>t</ci><cn cellml:units="millisecond">5</cn></apply>\
                </piece>\
                    <piece>\
                    <cn cellml:units="millivolt">0</cn>\
                    <apply><gt/><ci>t</ci><cn cellml:units="millisecond">15</cn></apply>\
                </piece>\
                <otherwise>\
                    <cn cellml:units="millivolt">-85</cn>\
                </otherwise>\
            </piecewise>\
        </apply>'

    #  5.b Add this to the maths for the environment component.
    environment.setMath(math_header)
    environment.appendMath(voltageClampMaths)
    environment.appendMath(math_footer)

    #  5.c Validate the model including this new maths block
    validator.validateModel(model)
    print_errors_to_terminal(validator)

    print("-----------------------------------------------")
    print("    STEP 6: Serialise and print the model      ")
    print("-----------------------------------------------")

    #  6.a Create a Printer item and submit your model for serialisation.
    printer = Printer()
    serialised_model = printer.printModel(model)
    write_file = open("Tutorial5_PotassiumChannelModel.cellml", "w")
    write_file.write(serialised_model)
    print("The {} has been printed to Tutorial5_PotassiumChannelModel.cellml".format(model.name()))

    #  6.b Go and have a cuppa, you're done!
