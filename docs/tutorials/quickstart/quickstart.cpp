/**
 *  QUICKSTART: Summary of commonly used functionality
 *
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

int main()
{
    // ----------------------------------------------------------------------------
    //  STEP 1:   Deserialise a CellML Model from the contents of a CellML file

    //  1.a   Open the file and read its contents into a buffer stream
    std::ifstream inFile("../resources/quickstart.cellml");
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();

    //  1.b   Create a libCellML Parser, and use it to parse the inFileContents
    //        stream and return it as a ModelPtr instance
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(inFileContents.str());

    // ----------------------------------------------------------------------------
    //  STEP 2:   Validate the contents of a model

    //  2.a   Create a Validator instance and pass it the model pointer for
    //        checking
    libcellml::Validator validator;
    validator.validateModel(model);

    //  2.b   Retrieve the errors from the validator and access their
    //        specificiation reference and description
    for (size_t e = 0; e < validator.errorCount(); ++e) {
        libcellml::ErrorPtr error = validator.error(e);
        std::cout << error->description() << std::endl;
        std::cout << error->specificationReference() << std::endl
                  << std::endl;
    }

    // ---------------------------------------------------------------------------
    //  STEP 3:   Investigate the model we've just loaded and see what's inside it

    //  3.a   Return the name, id, number of components, and number of units of
    //        the new model, and print to the terminal

    std::string modelName = model->name();
    std::string modelId = model->id();
    int numberOfComponents = model->componentCount();

    std::cout << "The model name is: " << modelName << std::endl;
    std::cout << "  with id: " << modelId << std::endl;
    std::cout << "  and " << numberOfComponents << " components," << std::endl;
    std::cout << "  and " << numberOfUnits << " units." << std::endl
              << std::endl;

    //  2.b   Instantiate an item as a pointer for local changes

    libcellml::ComponentPtr component = model->component(0);
    std::string componentName = component->name();
    std::string componentId = component->id();

    std::cout << "Component[0] has name: " << componentName << std::endl;
    std::cout << "  with id: " << componentId << std::endl;
    std::cout << "  and " << component->numberOfVariables() << " variables," << std::end;
    std::cout << "  and " << component->numberOfComponents() << " nested components." << std::end;

    //  2.c   Retrieve an item without instantiating it using its name or index

    //  2.d   Investigate the variables inside the component, and print their
    //        names to terminal

    int numberOfVariables = component->variableCount();
    std::cout << "  The " << componentName << " component has "
              << numberOfVariables << " variable(s):" << std::endl;

    for (size_t v = 0; v < numberOfVariables; ++v) {
        libcellml::VariablePtr variable = component->variable(v);
        std::string variableName = variable->name();

        std::cout << "    Variable[" << v << "] has name: " << variableName
                  << std::endl;
    }

    //  2.e   Investigate the maths which connects the variables in this
    //        component.  Note that maths in libCellML is stored as a
    //        single MathML2 string.

    std::string mathsString = component->math();
    std::cout << "  Component " << componentName
              << " has a MathML string of: " << std::endl;
    std::cout << "  " << mathsString << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 3: Print the model to another CellML file
    //  3.a   Create a Printer and use it to serialise the model to a string

    libcellml::Printer printer;
    std::string serialisedModelString = printer.printModel(model);

    //  3.b   Write the serialised string to a file
    std::string outFileName = "tutorial1_printed.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The " << modelName << " has been printed to: " << outFileName
              << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 4: Go and have a cuppa, you're done!
}
