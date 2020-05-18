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
from libcellml import Model, Parser, Validator

if __name__ == "__main__":
    #  0    Create a new model instance representing the combined model and name it.
    model = Model()
    model.setName("Tutorial8_HHModel")
    validator = Validator()
    parser = Parser()

    print("-----------------------------------------------")
    print("    STEP 1: Read the membrane component")
    print("-----------------------------------------------")

    #  1.a  Read the model provided for you in the "Tutorial8_MembraneModel.cellml"
    #       file in the resources folder.

    #  1.b  Create a temporary model for the membrane

    #  1.b  Extract the membrane component from the parsed model and add it
    #       to the combined model.  Note that the membrane component's parent
    #       must be cleared before adding it to the model.

    #  1.c  Validate the combined model.  We expect to see errors from missing units, as we have
    #       only added the component so far

    #  1.d  Import the units from the membraneModel into the combined model

    #  1.e  Validate the model.  No errors expected this time :)

    print("\n-----------------------------------------------")
    print("      STEP 2: Read the sodium channel")
    print("-----------------------------------------------")

    #  2.a  Read the model created in Tutorial 7 representing the sodium channel.
    #       Note that if you didn't do that tutorial you can simply copy the CellML file
    #       from Tutorial7_SodiumChannelModel.cellml in the resources folder.

    #  2.b  Extract the sodiumChannel component from the parsed model and add it
    #       to the one created at the beginning, and check the structure of the
    #       encapsulation using the utility function printEncapsulationStructureToTerminal(model)

    #  2.c  Validate the combined model.  We expect to see errors from:
    #       - missing units, as we have only added the component so far,
    #       - illegal connections between equivalent variables, as now the environment component
    #       and the sodiumChannel component are no longer siblings.

    #  2.d  Add all of the units from the sodium channel model which are not already present
    #       into the combined model.

    #  2.e  Disconnect the sodiumChannel from its old environment component

    #  2.f  Validate that there are no more errors in the combined model

    print("\n-----------------------------------------------")
    print("       STEP 3: Read the potassium channel")
    print("-----------------------------------------------")

    #  3.a  De-serialise the file and reading into the potassium_channel_model

    #  3.b  Extract the potassiumChannel component from the parsed model and add it
    #       to the combined model, and check the contents

    #  3.c  Validate the combined model.

    # If you have used the files provided in the resources folder, you can expect
    # to see errors at this point relating to missing units.
    # This is because even though both components require the same set of units,
    # each of them has used different names for them.  At this stage you have a
    # choice: either import all the units under their original names from the
    # potassium channel as well, or rename the units throughout the potassiumChannel
    # variables and maths.  Here we'll go with the former to illustrate the
    # process, and to create a more compact model description.

    #  3.d  Rename the units referred to by the variables in the potassium_channel and nGate components

    #  3.e  Replace units in the MathML string in the nGate component.
    #       Note: There are no constants in the potassiumChannel maths, so we don't need to
    #       search and replace the maths there.  In the general case, you'd need to do the
    #       same in that component too.  There's a utility function provided for you to help with this:
    #           new_maths = switch_units_in_maths(old_maths, units_old, units_new)

    #  3.f  Validate the model again.  This time we expect errors related to a mismatch in errors
    #       between equivalent variables ... which is a misleading error message because in the
    #       source model - PotassiumChannelModel, they *were* equivalent!  We haven't imported
    #       the environment component into our combined model yet, and that is the origin of this
    #       error.  We can solve the problem by creating the local environment component, and adding
    #      the equivalence to that instead.

    #  3.g Call the validator again.  We do not expect errors here.

    print("\n-----------------------------------------------")
    print("    STEP 4: Read the leakage component")
    print("-----------------------------------------------")

    #  4.a  De-serialise the file and reading into the leakageCurrentModel from the file provided in
    #       resources/Tutorial8_LeakageCurrentModel.cellml

    #  4.b  Extract the leakageCurrent component from the parsed model and add it to the combined
    #       model, and check the contents

    #  4.c  Validate the combined model.

    print("\n-----------------------------------------------")
    print("   STEP 5: Create the environment component")
    print("-----------------------------------------------")

    #  5.a  Create the environment component and adding it to the model

    #  5.b  Add variables to the environment component.

    #  5.c  Add the new component to the model and validate

    print("\n-----------------------------------------------")
    print("   STEP 6: Connect the equivalent variables")
    print("-----------------------------------------------")

    #  6.a  Connect the membrane to its sibling environment, and the channels to their
    #       parent membrane component.

    #  6.b  Setting the interface types for those which haven't been inherited already, and validate the model again

    print("\n-----------------------------------------------")
    print("   STEP 7: Add the driving function")
    print("-----------------------------------------------")

    #  7.a  Create a MathML string to represent the stimulus current i_stim, which
    #       is set to 100 microA/cm^2 between t=1ms < t < t=1.2ms.

    #  7.b  Add before the closing </math> tag in the membrane component and print to check it

    print("\n-----------------------------------------------")
    print("   STEP 8: Output the final model")
    print("-----------------------------------------------")

    #  8.a  Serialise your final model using the Printer, and output to a CellML file.

    #  8.b  Go and have a cuppa, you're done!
