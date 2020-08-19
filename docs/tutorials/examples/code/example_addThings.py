from libcellml import Component, Variable

if __name__ == '__main__':

    my_variable = Variable()
    my_variable.setName("myVariable")
    my_component = Component()
    my_component.setName("myComponent")
    success = False

    # Before adding, the variable has no parent, and the component has no
    # variables.
    assert(my_component.variableCount() == 0)
    assert(my_variable.parent() == None)

    # Add the variable my_variable to component my_variable.
    success = my_component.addVariable(my_variable)

    # At this point, if the operation was successful, the variable
    # my_variable has a parent of my_variable, and exists in the collection
    # of variables.  The component's variable count has been updated too.
    assert(success == true)
    assert(my_component.variableCount() == 1)
    assert(my_variable.parent() == my_variable)
    assert(my_component.variable(0) == my_variable)

    # Now see what happens if that same variable is added to another
    # Component item, my_other_component, which is initially empty.
    my_other_component = Component()
    my_other_component.setName('myOtherComponent')
    assert(my_other_component.variableCount() == 0)

    success = my_other_component.addVariable(my_variable)

    # If successful, the variable will have been moved to the new component, and
    # removed from the old one.
    assert(success == true)
    assert(my_other_component.variableCount() == 1)
    assert(my_other_component.variable(0) == my_variable)
    assert(my_variable.parent() == my_other_component)
    assert(my_component.variableCount() == 0)
