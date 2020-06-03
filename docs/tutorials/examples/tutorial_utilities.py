import string


def print_model_to_terminal(model):
    print("The model name is: '{}'".format(model.name()))
    if model.id() != "":
        print("The model id is: '{}'".format(model.id()))

    print("The model defines {} custom units:".format(model.unitsCount()))
    for u in range(0, model.unitsCount()):
        print("  Units[{u}] is '{n}'".format(u=u, n=model.units(u).name()))

        print("The model has {n} components:".format(n=model.componentCount()))

        for c in range(0, model.componentCount()):
            component = model.component(c)
            spacer = "  "
            print_component_to_terminal(component, c, spacer)

        return


def print_component_to_terminal(component, c, spacer):
    # Print this component
    print("{s}Component[{c}] has name: '{n}'".format(
        s=spacer,
        c=c,
        n=component.name()))
    if component.id() != "":
        print("{s}Component[{c}] has id: '{n}'".format(
            s=spacer,
            c=c,
            n=component.id()))
    print("{s}Component[{c}] has id: '{n}'".format(
        s=spacer,
        c=c,
        n=component.id()))

    # Print variables in this component
    for v in range(0, component.variableCount()):
        print("{s}  Variable[{v}] has name: '{n}'".format(
            s=spacer,
            v=v,
            n=component.variable(v).name()
        ))
        if component.variable(v).initialValue() != "":
            print("{s}  Variable[{v}] has initial_value: '{n}'".format(
                s=spacer,
                v=v,
                n=component.variable(v).initialValue()
            ))
        print("{s}  Variable[{v}] has units: '{n}'".format(
            s=spacer,
            v=v,
            n=component.variable(v).units().name()
        ))

    # Print the encapsulated components inside this one
    if component.componentCount() > 0:
        print("{s}Component[{c}] has {n} child components".format(
            s=spacer,
            c=c,
            n=component.componentCount()))

        for c2 in range(0, component.componentCount()):
            child = component.component(c2)
            one_more_spacer = spacer + "  "
            print_component_to_terminal(child, c2, one_more_spacer)


def print_errors_to_terminal(item):
    number_of_validation_errors = item.errorCount()

    print("\nThe {t} has found {n} errors!".format(
        t=type(item).__name__.lower(),
        n=number_of_validation_errors)
    )

    if number_of_validation_errors != 0:
        for e in range(0, number_of_validation_errors):
            validation_error = item.error(e)
            specification = validation_error.referenceHeading()
            print("  Validator error[{e}]:".format(e=e))
            print("    Description: {d}".format(d=validation_error.description()))
            if specification != "":
                print("    See section {s} in the CellML specification.".format(s=specification))


def switch_units_in_maths(maths, units_in, units_out):
    #   Note that this function will replace any and all occurrences of the "units_in"
    #   string within the "maths" string with the "units_out" string.  It's worth noting that
    #   in order to be sure that only full name matches for units are replaced, we exploit
    #   the fact that the units names in the MathML string will be in quotation marks, and include
    #   these quotation marks on either side of the in and out strings for safety.

    in_with_quotes = "\"" + units_in + "\""
    out_with_quotes = "\"" + units_out + "\""

    new_maths = maths.replace(in_with_quotes, out_with_quotes)

    return new_maths


def insert_into_mathml_string(maths, add_me):
    # Inserts the add_me string before any closing </math> characters in the
    # math string, or just adds it to the end.

    tag = "</math>"

    # Removes all whitespace and special characters from the maths string
    math_strip = maths.translate(str.maketrans("", "", string.whitespace))

    if math_strip[-len(tag):] == tag:

        # then find the last occurrence of the < character in the maths string, and split it there
        pos = maths.rfind("<")
        before = maths[0:pos]
        after = maths[pos:]
        maths = before + add_me + after
    else:
        # otherwise just add the new section to the end
        maths = maths + add_me

    return maths


def print_encapsulation_structure_to_terminal(model):
    # Prints the encapsulation structure of the model to the terminal
    spacer = "  - "
    print("Model '{m}' has {c} components".format(m=model.name(), c=model.componentCount()))

    for c in range(0, model.componentCount()):
        child_component = model.component(c)
        print_component_only_to_terminal(child_component, spacer)


def print_component_only_to_terminal(component, spacer):
    print("{s}Component '{c}' has {n} child components".format(
        s=spacer,
        c=component.name(),
        n=component.componentCount()))

    for c in range(0, component.componentCount()):
        another_spacer = "    " + spacer
        child_component = component.component(c)
        print_component_only_to_terminal(child_component, another_spacer)



def get_model_type_from_enum(my_type):

    my_type_as_string = "dunno"

    if my_type == Generator.ModelType.UNKNOWN:
        my_type_as_string = "UNKNOWN"
    elif my_type == Generator.ModelType.ALGEBRAIC:
        my_type_as_string = "ALGEBRAIC"
    elif my_type == Generator.ModelType.ODE:
        my_type_as_string = "ODE"
    elif my_type == Generator.ModelType.INVALID:
        my_type_as_string = "INVALID"
    elif my_type == Generator.ModelType.UNDERCONSTRAINED:
        my_type_as_string = "UNDERCONSTRAINED"
    elif my_type == Generator.ModelType.OVERCONSTRAINED:
        my_type_as_string = "OVERCONSTRAINED"
    elif my_type == Generator.ModelType.UNSUITABLY_CONSTRAINED:
        my_type_as_string = "UNSUITABLY_CONSTRAINED"

    return my_type_as_string


def get_profile_from_enum(my_type):

    my_type_as_string = "dunno"

    if my_type == GeneratorProfile.Profile.C:
        my_type_as_string = "C"
    elif my_type == GeneratorProfile.Profile.PYTHON:
        my_type_as_string = "PYTHON"

    return my_type_as_string


def get_issue_level_from_enum(my_level):

    my_type_as_string = "dunno"

    if my_level == Issue.Level.ERROR:
        my_type_as_string = "ERROR"
    elif my_level == Issue.Level.WARNING:
        my_type_as_string = "WARNING"
    elif my_level == Issue.Level.HINT:
        my_type_as_string = "HINT"

    return my_type_as_string


def get_issue_cause_from_enum(my_cause):

    my_type_as_string = "dunno"

    if my_cause == Issue.Cause.COMPONENT:
        my_type_as_string = "COMPONENT"

    elif my_cause == Issue.Cause.CONNECTION:
        my_type_as_string = "CONNECTION"

    elif my_cause == Issue.Cause.ENCAPSULATION:
        my_type_as_string = "ENCAPSULATION"

    elif my_cause == Issue.Cause.IMPORT:
        my_type_as_string = "IMPORT"

    elif my_cause == Issue.Cause.MATHML:
        my_type_as_string = "MATHML"

    elif my_cause == Issue.Cause.MODEL:
        my_type_as_string = "MODEL"

    elif my_cause == Issue.Cause.RESET:
        my_type_as_string = "RESET"

    elif my_cause == Issue.Cause.UNDEFINED:
        my_type_as_string = "UNDEFINED"

    elif my_cause == Issue.Cause.UNITS:
        my_type_as_string = "UNITS"

    elif my_cause == Issue.Cause.VARIABLE:
        my_type_as_string = "VARIABLE"

    elif my_cause == Issue.Cause.XML:
        my_type_as_string = "XML"

    elif my_cause == Issue.Cause.GENERATOR:
        my_type_as_string = "GENERATOR"

    return my_type_as_string
