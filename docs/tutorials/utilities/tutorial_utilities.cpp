
/**
 *  TUTORIAL UTILITIES
 *  This file contains helper functions for the tutorials
 */

#include "tutorial_utilities.h"

void printModelToTerminal(libcellml::ModelPtr &model)
{
    std::cout << "The model name is: '" << model->name() << "'" << std::endl;
    if (model->id() != "") {
        std::cout << "The model id is: '" << model->id() << "'" << std::endl;
    }

    // 2.a    Print any custom units of the model
    std::cout << "The model defines " << model->unitsCount()
              << " custom units:" << std::endl;
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        std::cout << "  Units[" << u << "] is '" << model->units(u)->name() << "'"
                  << std::endl;
    }

    // 2.b    Print the components of the model
    std::cout << "The model has " << model->componentCount()
              << " components:" << std::endl;
    for (size_t c = 0; c < model->componentCount(); ++c) {
        // 2.c  Printing the attributes of the component
        auto component = model->component(c);
        std::string spacer = "  ";
        printComponentToTerminal(component, c, spacer);
    }
}

void printComponentToTerminal(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer)
{
    std::cout << spacer << "Component[" << c << "] has name: '"
              << component->name() << "'" << std::endl;
    if (component->id() != "") {
        std::cout << spacer << "Component[" << c << "] has id: '"
                  << component->id() << "'" << std::endl;
    }

    std::cout << spacer << "Component[" << c << "] has "
              << component->variableCount()
              << " variables:" << std::endl;

    // Printing the variables within the component
    for (size_t v = 0; v < component->variableCount(); v++) {
        std::cout << spacer << "  Variable[" << v << "] has name: '"
                  << component->variable(v)->name() << "'" << std::endl;
        if (component->variable(v)->initialValue() != "") {
            std::cout << spacer << "  Variable[" << v << "] has initial_value: '"
                      << component->variable(v)->initialValue() << "'"
                      << std::endl;
        }
        if (component->variable(v)->units() != nullptr) {
            std::cout << spacer << "  Variable[" << v << "] has units: '"
                      << component->variable(v)->units()->name() << "'" << std::endl;
        }
    }

    // Print the maths within the component
    if (component->math() != "") {
        std::cout << spacer << "  Maths in the component is:" << std::endl;
        std::cout << component->math() << std::endl;
    }

    // Print the encapsulated components
    if (component->componentCount() > 0) {
        std::cout << spacer << "Component[" << c << "] has "
                  << component->componentCount()
                  << " child components:" << std::endl;

        for (size_t c2 = 0; c2 < component->componentCount(); c2++) {
            auto child = component->component(c2);
            std::string oneMoreSpacer = spacer + "  ";
            printComponentToTerminal(child, c2, oneMoreSpacer);
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
        // 2.c  Retrieve the errors, and print their description and specification
        //      reference to the terminal
        for (size_t e = 0; e < numberOfValidationErrors; ++e) {
            libcellml::ErrorPtr validatorError = item->error(e);
            std::string errorSpecificationReference =
                validatorError->specificationHeading();

            std::cout << "  Validator error[" << e << "]:" << std::endl;
            std::cout << "     Description: " << validatorError->description()
                      << std::endl;
            // std::cout << "     Kind: " << (int)validatorError->kind() << std::endl;
            if (errorSpecificationReference != "") {
                std::cout << "    See section " << errorSpecificationReference
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
        // 2.c  Retrieve the errors, and print their description and specification
        //      reference to the terminal
        for (size_t e = 0; e < numberOfErrors; ++e) {
            libcellml::ErrorPtr error = item->error(e);
            std::string errorSpecificationReference =
                error->specificationHeading();

            std::cout << "  Generator error[" << e << "]:" << std::endl;
            std::cout << "     Description: " << error->description()
                      << std::endl;
            // std::cout << "     Kind: " << (int)validatorError->kind() << std::endl;
            if (errorSpecificationReference != "") {
                std::cout << "    See section " << errorSpecificationReference
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

    std::string tag = "</math>\n";
    std::string before = maths.substr(0, maths.length() - tag.length() - 1);
    std::string after = maths.substr(maths.length() - tag.length());
    maths.erase(maths.find_last_not_of(" \t\n\r\f\v") + 1);

    // test the final characters of the existing math string
    if (after == tag) {
        maths = before + addMe + tag;
    } else {
        maths = maths + addMe;
    }
}

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
