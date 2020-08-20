/**
 *  TUTORIAL 1: READING AND WRITING A CELLML FILE
 *
 *  By the time you have worked through Tutorial 1 you will be able to:
 *    - Read the contents of a CellML file;
 *    - Deserialise its contents using the Parser to create a Model structure;
 *    - Investigate the hierarchical contents of the Model, including the
 *      Components, Variables, and maths; and
 *    - Serialise the model and write to another file.
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

int main()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << " TUTORIAL 1: READING AND WRITING CELLML FILES" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    // ----------------------------------------------------------------------------
    //  STEP 1:   Create a CellML Model from the contents of a CellML file.
    //
    //  1.a   Open the file and read its contents into a buffer stream.

    std::string inFileName = "../resources/tutorial1.cellml";
    std::ifstream inFile(inFileName);
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();

    std::cout << "Opening the CellML file" << std::endl;

    //  1.b   Create a libCellML Parser, and use it to parse the fileContents
    //        string and convert it into a CellML Model structure.
    
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(inFileContents.str());

    // ---------------------------------------------------------------------------
    //  STEP 2:   Investigate the model we've just loaded and see what's inside it.
    //
    //  2.a   Return the name and id of the new model, and print to the terminal.

    std::string modelName = model->name();
    std::string modelId = model->id();

    std::cout << "The model name is: " << modelName << std::endl;
    std::cout << "The model id is: " << modelId << std::endl;

    //  2.b   Return the number of components contained in the model, and print
    //        to the screen.

    int numberOfComponents = model->componentCount();
    std::cout << "The " << modelName << " model has " << numberOfComponents
              << " component(s):" << std::endl;

    assert(numberOfComponents > 0);

    //  2.c   Return the name and id of the first component and print them to
    //        the screen.

    auto component = model->component(0);
    std::string componentName = component->name();
    std::string componentId = component->id();
    std::cout << "  Component[0] has name: " << componentName << std::endl;
    std::cout << "  Component[0] has id: " << componentId << std::endl;

    //  2.d   Retrieve the number of variables in this component, and print
    //        to the screen.

    int numberOfVariables = component->variableCount();
    std::cout << "  The " << componentName << " component has "
              << numberOfVariables << " variable(s):" << std::endl;

    //  2.e   Loop through the variables and print their names to the terminal.

    for (size_t v = 0; v < numberOfVariables; ++v) {
        auto variable = component->variable(v);
        std::string variableName = variable->name();

        std::cout << "    Variable[" << v << "] has name: " << variableName
                  << std::endl;
    }

    //  2.f   Investigate the maths which connects the variables in this
    //        component.  Note that maths in libCellML is stored as a
    //        single string, which could contain any number of MathML blocks.

    std::string mathsString = component->math();
    std::cout << "  Component " << componentName
              << " has a MathML string of: " << std::endl;
    std::cout << "  " << mathsString << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 3: Print the model to another CellML file.
    //  3.a   Create a Printer and use it to serialise the model to a string.

    auto printer = libcellml::Printer::create();
    std::string serialisedModelString = printer->printModel(model);

    //  3.b   Write the serialised string to a file.

    std::string outFileName = "tutorial1_printed.cellml";
    std::ofstream outFile(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The " << modelName << " has been printed to: " << outFileName
              << std::endl;

    //  3.c Go and have a cuppa, you're done!
}
