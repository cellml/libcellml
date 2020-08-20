
#include <libcellml>

int main()
{
    // Create a variable and a component.
    auto myVariable = libcellml::Variable::create("myVariableName");
    auto myComponent = libcellml::Component::create("myComponentName");
    bool success = false;

    // Before adding, the variable has no parent, and the component has no
    // variables.
    // Add the variable myVariable to component myComponent.
    success = myComponent->addVariable(myVariable);

    // At this point, if the operation was successful, the variable
    // myVariable has a parent of myComponent, and exists in the collection
    // of variables.  If successful:
    //  - success = true
    //  - myComponent->variableCount() = 1
    //  - myVariable->parent() = myComponent
    //  - myComponent->variable(0) = myVariable.
    
    // Now see what happens if that same variable is added to another
    // Component item, myOtherComponent, which is initially empty.
    auto myOtherComponent = libcellml::Component::create("myOtherComponentName");
    success = myOtherComponent->addVariable(myVariable);

    // If successful, the variable will have been moved to the new component, and
    // removed from the old one, thus:
    // - success = true
    // - myOtherComponent->variableCount() = 1
    // - myOtherComponent->variable(0) = myVariable
    // - myVariable->parent() = myOtherComponent
    // - myComponent->variableCount() == 0.
}
