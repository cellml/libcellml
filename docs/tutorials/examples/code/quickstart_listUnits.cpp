
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include <libcellml>

int main()
{
    // Parse example model and component from the file provided.
    std::string inFileName = "../resources/quickstart_listUnits.cellml";
    std::ifstream inFile(inFileName);
    std::stringstream inFileContents;
    inFileContents << inFile.rdbuf();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(inFileContents.str());
    auto component = model->component("component");

    // Initialise an empty set in which to store unique units names.
    std::unordered_set<std::string> unitsNames;

    // Iterate through the variables in this component, and add their units' names to the set.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        // Get the units for this variable:
        auto myUnits = component->variable(v)->units();
        // Check that this is not the nullptr, otherwise skip.
        if (myUnits != nullptr) {
            // Add name to set if not already there.
            unitsNames.insert(myUnits->name());
        }
    }

    // Parse the MathML string to find any units used by <cn> constants:
    std::string delimiter = "cellml:units=\"";
    std::string maths = component->math();
    size_t pos1 = maths.find(delimiter);
    size_t pos2;
    std::string segment;
    std::string name;
    do {
        std::string segment(maths, pos1);
        segment.erase(0, segment.find_first_of('"') + 1); // Trim up to and including the first quote mark after the delimiter.
        pos2 = segment.find_first_of('"'); // Find the closing quote mark.
        name = segment.substr(0, pos2); // Units name is between the two quotes.
        unitsNames.insert(name); // Add name to the set if it's not already present.
        maths.erase(0, pos1 + delimiter.length()); // Remove this segment from the main string.
        pos1 = maths.find(delimiter);
    } while (pos1 != std::string::npos);

    // Print the unique units for this component to the terminal.
    for (const auto &name : unitsNames) {
        std::cout << "  - " << name << std::endl;
    }
}
