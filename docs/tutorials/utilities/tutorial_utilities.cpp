
/**
 *  TUTORIAL UTILITIES
 *  This file contains helper functions for the tutorials
 */

#include "tutorial_utilities.h"
#include "libcellml/types.h"
#include <libcellml>

void printModelToTerminal(libcellml::ModelPtr &model)
{
    printModelToTerminal(model, true);
}

void printModelToTerminal(libcellml::ModelPtr &model, bool includeMaths)
{
    std::string spacer = "    ";

    std::cout << " MODEL: '" << model->name() << "'";
    if (model->id() != "") {
        std::cout << ", id: '" << model->id() << "'";
    }
    std::cout << std::endl;

    std::cout << spacer << "UNITS: " << model->unitsCount() << " custom units" << std::endl;
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        std::cout << spacer << spacer << "[" << u << "]: " << model->units(u)->name() << std::endl;
    }

    std::cout << spacer << "COMPONENTS: " << model->componentCount() << " components" << std::endl;
    for (size_t c = 0; c < model->componentCount(); ++c) {
        auto component = model->component(c);
        printComponentToTerminal(component, c, spacer + spacer, includeMaths);
    }
}

void printComponentToTerminal(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer)
{
    printComponentToTerminal(component, c, spacer, true);
}

void printComponentToTerminal(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer, bool includeMaths)
{
    std::string local = "    ";

    std::cout << spacer << "[" << c << "]: " << component->name();
    if (component->id() != "") {
        std::cout << " id: " << component->id();
    }
    std::cout << std::endl;

    std::cout << spacer << local << "VARIABLES: " << component->variableCount() << " variables" << std::endl;

    // Printing the variables within the component.
    for (size_t v = 0; v < component->variableCount(); v++) {
        std::cout << spacer << local << local;
        std::cout << "[" << v << "]: " << component->variable(v)->name();
        if (component->variable(v)->units() != nullptr) {
            std::cout << " [" << component->variable(v)->units()->name() << "]";
        }
        if (component->variable(v)->initialValue() != "") {
            std::cout << ", initial = " << component->variable(v)->initialValue();
        }
        std::cout << std::endl;
        if (component->variable(v)->equivalentVariableCount() > 0) {
            std::cout << spacer << local << local << local;
            std::string con = "  └──> ";
            for (size_t e = 0; e < component->variable(v)->equivalentVariableCount(); ++e) {
                auto ev = component->variable(v)->equivalentVariable(e);
                if (ev == nullptr) {
                    std::cout << "WHOOPS! Null equivalent variable!";
                    continue;
                }
                libcellml::ComponentPtr ev_parent = std::dynamic_pointer_cast<libcellml::Component>(ev->parent());
                if (ev_parent == nullptr) {
                    std::cout << "WHOOPS! Null parent component for equivalent variable!";
                    continue;
                }
                std::cout << con << ev_parent->name() << ":" << ev->name();
                if (ev->units() != nullptr) {
                    std::cout << " [" << ev->units()->name() << "]";
                }
                con = ", ";
            }
            std::cout << std::endl;
        }
    }

    // Print the maths within the component.
    if (includeMaths) {
        if (component->math() != "") {
            std::cout << spacer << "  Maths in the component is:" << std::endl;
            std::cout << component->math() << std::endl;
        }
    }

    // Print the encapsulated components
    if (component->componentCount() > 0) {
        std::cout << spacer << local << "COMPONENT " << component->name() << " has "
                  << component->componentCount()
                  << " child components:" << std::endl;

        for (size_t c2 = 0; c2 < component->componentCount(); c2++) {
            auto child = component->component(c2);
            std::string oneMoreSpacer = spacer + local + local;
            printComponentToTerminal(child, c2, oneMoreSpacer, includeMaths);
        }
    }
}

void printErrorsToTerminal(libcellml::ValidatorPtr &item)
{
    //  2.b   Check whether there were errors returned from the item
    int numberOfValidationErrors = item->errorCount();

    std::cout << "The validator has found " << numberOfValidationErrors
              << " errors!" << std::endl;
    if (numberOfValidationErrors != 0) {
        // 2.c  Retrieve the errors, and print their description and
        //      reference to the terminal
        for (size_t e = 0; e < numberOfValidationErrors; ++e) {
            libcellml::IssuePtr validatorError = item->error(e);
            std::string errorReference = validatorError->referenceHeading();

            std::cout << "  Validator error[" << e << "]:" << std::endl;
            std::cout << "     Description: " << validatorError->description()
                      << std::endl;
            if (errorReference != "") {
                std::cout << "    See section " << errorReference
                          << " in the CellML specification." << std::endl;
            }
        }
    }
}

void printErrorsToTerminal(libcellml::GeneratorPtr &item)
{
    //  2.b   Check whether there were errors returned from the item
    int numberOfErrors = item->errorCount();

    std::cout << "The generator has found " << numberOfErrors
              << " errors!" << std::endl;
    if (numberOfErrors != 0) {
        // 2.c  Retrieve the errors, and print their description and
        //      reference to the terminal
        for (size_t e = 0; e < numberOfErrors; ++e) {
            libcellml::IssuePtr error = item->error(e);
            std::string errorReference = error->referenceHeading();

            std::cout << "  Generator error[" << e << "]:" << std::endl;
            std::cout << "     Description: " << error->description()
                      << std::endl;
            // std::cout << "     Kind: " << (int)validatorError->cause() << std::endl;
            if (errorReference != "") {
                std::cout << "    See section " << errorReference
                          << " in the CellML specification." << std::endl;
            }
        }
    }
}

std::string fileContents(const std::string &fileName)
{
    std::ifstream file(fileName);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

void switchUnitsInMaths(std::string &maths, std::string in, std::string out)
{
    //  Note that this function will replace any and all occurrences of the "in"
    //  string within the "maths" string with the "out" string.  It's worth noting that
    //  in order to be sure that only full name matches for units are replaced, we exploit
    //  the fact that the units names in the MathML string will be in quotation marks, and include
    //  these quotation marks on either side of the in and out strings for safety.

    std::string::size_type n = 0;
    std::string in_with_quotes = "\"" + in + "\"";
    std::string out_with_quotes = "\"" + out + "\"";

    while ((n = maths.find(in_with_quotes, n)) != std::string::npos) {
        maths.replace(n, in_with_quotes.size(), out_with_quotes);
        n += out_with_quotes.size();
    }

    std::cout << "Switched units '" << in << "' for units '" << out << "'" << std::endl;
}

void insertIntoMathMLString(std::string &maths, std::string &addMe)
{
    // Inserts the addMe string before any closing </math> characters in the
    // math string, or just adds it to the end.  Returns the altered math
    // string through the argument list.

    std::string tag = "</math>";
    maths.erase(maths.find_last_not_of(" \t\n\r\f\v") + 1);
    std::string before = maths.substr(0, maths.length() - tag.length() - 1);
    std::string after = maths.substr(maths.length() - tag.length());

    // test the final characters of the existing math string
    if (after == tag) {
        maths = before + addMe + tag;
    } else {
        maths = maths + addMe;
    }
}

// std::string getEquationFromMathML(std::string &maths, std::string &lhs)
// {
//     std::string equals = "<apply><eq/>";
//     // Remove header and footer, if present

//     // Split the string at equals tags

//     // Retrieve and return entire equation starting with the lhs variable name
// }

std::string getModelTypeFromEnum(libcellml::Generator::ModelType myType)
{
    std::string myTypeAsString = "dunno";

    switch (myType) {
    case libcellml::Generator::ModelType::UNKNOWN:
        myTypeAsString = "UNKNOWN";
        break;
    case libcellml::Generator::ModelType::ALGEBRAIC:
        myTypeAsString = "ALGEBRAIC";
        break;
    case libcellml::Generator::ModelType::ODE:
        myTypeAsString = "ODE";
        break;
    case libcellml::Generator::ModelType::INVALID:
        myTypeAsString = "INVALID";
        break;
    case libcellml::Generator::ModelType::UNDERCONSTRAINED:
        myTypeAsString = "UNDERCONSTRAINED";
        break;
    case libcellml::Generator::ModelType::OVERCONSTRAINED:
        myTypeAsString = "OVERCONSTRAINED";
        break;
    case libcellml::Generator::ModelType::UNSUITABLY_CONSTRAINED:
        myTypeAsString = "UNSUITABLY_CONSTRAINED";
        break;
    default:
        break;
    }
    return myTypeAsString;
}

std::string getProfileFromEnum(libcellml::GeneratorProfile::Profile myType)
{
    std::string myTypeAsString = "dunno";

    switch (myType) {
    case libcellml::GeneratorProfile::Profile::C:
        myTypeAsString = "C";
        break;
    case libcellml::GeneratorProfile::Profile::PYTHON:
        myTypeAsString = "PYTHON";
        break;
    }
    return myTypeAsString;
}

std::string getIssueLevelFromEnum(libcellml::Issue::Level myLevel)
{
    std::string myTypeAsString = "dunno";

    switch (myLevel) {
    case libcellml::Issue::Level::ERROR:
        myTypeAsString = "ERROR";
        break;
    case libcellml::Issue::Level::WARNING:
        myTypeAsString = "WARNING";
        break;
    case libcellml::Issue::Level::HINT:
        myTypeAsString = "HINT";
        break;
    }
    return myTypeAsString;
}

std::string getIssueCauseFromEnum(libcellml::Issue::Cause myCause)
{
    std::string myTypeAsString = "dunno";

    switch (myCause) {
    case libcellml::Issue::Cause::COMPONENT:
        myTypeAsString = "COMPONENT";
        break;
    case libcellml::Issue::Cause::CONNECTION:
        myTypeAsString = "CONNECTION";
        break;
    case libcellml::Issue::Cause::ENCAPSULATION:
        myTypeAsString = "ENCAPSULATION";
        break;
    case libcellml::Issue::Cause::IMPORT:
        myTypeAsString = "IMPORT";
        break;
    case libcellml::Issue::Cause::MATHML:
        myTypeAsString = "MATHML";
        break;
    case libcellml::Issue::Cause::MODEL:
        myTypeAsString = "MODEL";
        break;
    case libcellml::Issue::Cause::RESET:
        myTypeAsString = "RESET";
        break;
    case libcellml::Issue::Cause::UNDEFINED:
        myTypeAsString = "UNDEFINED";
        break;
    case libcellml::Issue::Cause::UNITS:
        myTypeAsString = "UNITS";
        break;
    case libcellml::Issue::Cause::VARIABLE:
        myTypeAsString = "VARIABLE";
        break;
    case libcellml::Issue::Cause::XML:
        myTypeAsString = "XML";
        break;
    case libcellml::Issue::Cause::GENERATOR:
        myTypeAsString = "GENERATOR";
        break;
    }
    return myTypeAsString;
}

libcellml::EntityPtr getItemFromIssue(libcellml::IssuePtr &issue)
{
    switch (issue->cause()) {
    case libcellml::Issue::Cause::COMPONENT:
        return issue->component();
    case libcellml::Issue::Cause::IMPORT:
        return issue->importSource();
    case libcellml::Issue::Cause::MODEL:
        return issue->model();
    case libcellml::Issue::Cause::RESET:
        return issue->reset();
    case libcellml::Issue::Cause::UNITS:
        return issue->units();
    case libcellml::Issue::Cause::VARIABLE:
        return issue->variable();
    }
    return nullptr;
}

void printEncapsulationStructureToTerminal(libcellml::ModelPtr &model)
{
    // Prints the encapsulation structure of the model to the terminal
    std::string spacer = "  - ";

    std::cout << "Model '" << model->name() << "' has " << model->componentCount()
              << " components" << std::endl;

    for (size_t c = 0; c < model->componentCount(); ++c) {
        auto child = model->component(c);
        printComponentOnlyToTerminal(child, spacer);
    }
}

void printComponentOnlyToTerminal(libcellml::ComponentPtr &component, std::string spacer)
{
    std::cout << spacer << "Component '" << component->name() << "' has " << component->componentCount() << " child components" << std::endl;
    for (size_t c = 0; c < component->componentCount(); c++) {
        std::string anotherSpacer = "    " + spacer;
        auto child = component->component(c);
        printComponentOnlyToTerminal(child, anotherSpacer);
    }
}

void listEquivalentVariables(const libcellml::VariablePtr &variable, std::vector<libcellml::VariablePtr> &variableList)
{
    if (variable == nullptr) {
        return;
    }

    for (size_t i = 0; i < variable->equivalentVariableCount(); ++i) {
        libcellml::VariablePtr equivalentVariable = variable->equivalentVariable(i);

        if (std::find(variableList.begin(), variableList.end(), equivalentVariable) == variableList.end()) {
            variableList.push_back(equivalentVariable);
            listEquivalentVariables(equivalentVariable, variableList);
        }
    }
}

void printEquivalentVariableSet(const libcellml::VariablePtr &variable)
{
    if (variable == nullptr) {
        std::cout << "NULL variable submitted to printEquivalentVariableSet." << std::endl;
        return;
    }
    std::vector<libcellml::VariablePtr> variableList;
    variableList.push_back(variable);
    listEquivalentVariables(variable, variableList);

    libcellml::ComponentPtr component = std::dynamic_pointer_cast<libcellml::Component>(variable->parent());

    if (component != nullptr) {
        std::cout << "Tracing: " << component->name() << " -> "
                  << variable->name();
        if (variable->units() != nullptr) {
            std::cout << " [" << variable->units()->name() << "]";
        }
        if (variable->initialValue() != "") {
            std::cout << ", initial = " << variable->initialValue();
        }
        std::cout << std::endl;
    }

    if (variableList.size() > 1) {
        for (auto &e : variableList) {
            component = std::dynamic_pointer_cast<libcellml::Component>(e->parent());
            if (component != nullptr) {
                std::cout << "    - " << component->name() << " -> " << e->name();
                if (e->units() != nullptr) {
                    std::cout << " [" << e->units()->name() << "]";
                }
                if (e->initialValue() != "") {
                    std::cout << ", initial = " << e->initialValue();
                }
                std::cout << std::endl;
            } else {
                std::cout << "Variable " << e->name() << " does not have a parent component." << std::endl;
            }
        }
    } else {
        std::cout << "    - Not connected to any equivalent variables." << std::endl;
    }
}
