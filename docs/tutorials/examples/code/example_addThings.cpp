
#include <libcellml>

int main()
{
    // #MARKER1

    auto myVariable = libcellml::Variable::create("myVariableName");
    auto myComponent = libcellml::Component::create("myComponentName");
    bool success = false;

    // Before adding, the variable has no parent, and the component has no
    // variables.
    assert(myComponent->variableCount() == 0);
    assert(myVariable->parent() == nullptr);

    // Add the variable myVariable to component myComponent.
    success = myComponent->addVariable(myVariable);

    // At this point, if the operation was successful, the variable
    // myVariable has a parent of myComponent, and exists in the collection
    // of variables.  The component's variable count has been updated too.
    assert(success == true);
    assert(myComponent->variableCount() == 1);
    assert(myVariable->parent() == myComponent);
    assert(myComponent->variable(0) == myVariable);

    // Now see what happens if that same variable is added to another
    // Component item, myOtherComponent, which is initially empty.
    auto myOtherComponent = libcellml::Component::create("myOtherComponentName");
    assert(myOtherComponent->variableCount() == 0);

    success = myOtherComponent->addVariable(myVariable);

    // If successful, the variable will have been moved to the new component, and
    // removed from the old one.
    assert(success == true);
    assert(myOtherComponent->variableCount() == 1);
    assert(myOtherComponent->variable(0) == myVariable);
    assert(myVariable->parent() == myOtherComponent);
    assert(myComponent->variableCount() == 0);

    // #MARKER2
}
