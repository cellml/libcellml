/**
 *  QUICKSTART: Summary of commonly used functionality
 *
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include "../utilities/tutorial_utilities.h"
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
    auto parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(inFileContents.str());

    //  1.c   Print to the terminal to see the model contents
    printModelToTerminal(model);

    // ----------------------------------------------------------------------------
    //  STEP 2:   Validate the contents of a model

    //  2.a   Create a Validator instance and pass it the model pointer for
    //        checking
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(model);

    //  2.b   Retrieve the errors from the validator and access their
    //        specificiation reference and description
    // printErrorsToTerminal(validator);

    for (size_t e = 0; e < validator->issueCount(); ++e) {
        libcellml::IssuePtr issue = validator->issue(e);

        // Retrieve and print the description of the issue.
        std::cout << issue->description() << std::endl;

        // Retrieve and print the reference heading number, if related to CellML2.0 specification and format.
        std::cout << issue->referenceHeading() << std::endl;

        // Retrieve and print the URL for more help and information about the issue.
        std::cout << issue->url() << std::endl;

        // Retrieve and print the cause - a libcellml::Issue::CAUSE enum - for the issue.
        std::cout << getCauseFromEnum(issue->cause()) << std::endl;

        // Retrieve and print the level - a libcellml::Issue::LEVEL enum - for the issue.
        std::cout << getIssueLevelFromEnum(issue->level()) << std::endl;

    }

    // ---------------------------------------------------------------------------
    //  STEP 3:   Fix errors thrown by the validator

    // 3.a
    //  Validator error[0]:
    //    Description: CellML identifiers must not begin with a European numeric
    //    character [0-9].
    //    See section 3.1.4 in the CellML specification.
    //  Validator error[1]:
    //    Description: Variable does not have a valid name attribute.
    //    See section 11.1.1.1 in the CellML specification.

    // These errors refer to the same thing, but are better read in reverse order.
    // Variables (and everything else in CellML) which specify a name attribute
    // can must have the correct format.  Comparing the error to the names of
    // entities printed in the terminal we can see that variable[0] in
    // component[0] doesn't have a valid name, so let's fix it.
    model->component(0)->variable(0)->setName("a");

    // 3.b
    //  Validator error[2]:
    //    Description: Variable 'b' has an invalid units reference
    //    'i_am_not_a_unit' that does not correspond with a standard unit or units
    //    in the variable's parent component or model.
    //    See section 11.1.1.2 in the CellML specification.

    //  Variables must have a unit defined.  These can be either something from
    //  the built-in list within libCellML (which you can read in the
    //  specifications document), or something you define yourself.  We'll look at
    //  user defined units in Tutorial 3, but for now it's enough to see that the
    //  units which are associated with variable 'b' is not valid.  We'll change
    //  it to be 'dimensionless' instead.  NB items can be accessed through their
    //  name (as here) or their index (as above)
    model->component("i_am_a_component")->variable("b")->setUnits("dimensionless");

    // 3.c
    // Validator error[3]:
    //    Description: Variable 'c' has an invalid initial value
    //    'this_variable_doesnt_exist'. Initial values must be a real number
    //    string or a variable reference.
    //    See section 11.1.2.2 in the CellML specification.

    //  We can either access members by their index or their name, as shown above,
    //  or we can create a pointer to them instead.
    //  Initial values (if set) must be a valid variable name in the same
    //  component, or a real number.
    libcellml::VariablePtr variableC = model->component(0)->variable("c");
    variableC->setInitialValue(20.0);

    // 3.d
    // Validator error[4]:
    //    Description: CellML identifiers must contain one or more basic Latin
    //    alphabetic characters.
    //    See section 3.1.3 in the CellML specification.
    // Validator error[5]:
    //    Description: Variable 'd' does not have a valid units attribute.
    //    See section 11.1.1.2 in the CellML specification.

    //  These two errors go together too.  Because we haven't defined a units
    //  attribute for variable 'd', it effectively has a blank name, which is not
    //  allowed.  Of course we could simply assign a unit to the variable which
    //  would suppress both errors, but because variable 'd' is
    //  not actually needed, we should really just remove it.
    model->component(0)->removeVariable("d");

    // 3.e
    // Validator error[6]:
    //    Description: MathML ci element has the child text 'a' which does not
    //    correspond with any variable names present in component
    //    'i_am_a_component' and is not a variable defined within a bvar element.
    //  The maths block is complaining that it is being asked to compute:
    //    a = b + c
    //  but in the component there was no variable called 'a'.  Since we
    //  corrected this earlier by naming the first variable in component[0] as 'a'
    //  this error will be fixed already.

    validator->validateModel(model);
    printModelToTerminal(model);
    printErrorsToTerminal(validator);

    // ---------------------------------------------------------------------------
    //  STEP 4: Call the Generator to process the model to a C or Python format

    //  4.a  Create a Generator instance and call it to process the model, and
    //       check for errors
    auto generator = libcellml::Generator::create();
    generator->processModel(model);
    printErrorsToTerminal(generator);

    //  4.b  Fix the errors thrown by the generator by giving variable 'b' an intitial value
    model->component(0)->variable("b")->setInitialValue(20.0);
    generator->processModel(model);
    printErrorsToTerminal(generator);

    //  4.d  Retrieve the generated strings for output.  In Python you need only
    //       retrieve the implementationCode (suitable for a single *.py file), but
    //       in C you will need both the "implementation code" (the contents of the *.c)
    //       file and the "interface code" (the contents of the *.h file).
    //       Both are returned from the generator as strings which can be written to
    //       suitably named files as normal.
    std::string headerCode = generator->interfaceCode();
    std::string sourceCode = generator->implementationCode();

    std::string outFileName = "quickstart_fixed.c";
    std::ofstream outFile(outFileName);
    outFile << sourceCode;
    outFile.close();
    std::cout << "The " << outFileName << " has been written." << std::endl;

    outFileName = "quickstart_fixed.h";
    outFile.open(outFileName);
    outFile << headerCode;
    outFile.close();
    std::cout << "The " << outFileName << " has been written." << std::endl;

    //  4.e  Change the generator profile from C to Python and reprocess
    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);
    generator->setProfile(profile);
    generator->processModel(model);

    std::string pythonCode = generator->implementationCode();
    outFileName = "quickstart_fixed.py";
    outFile.open(outFileName);
    outFile << pythonCode;
    outFile.close();
    std::cout << "The " << outFileName << " has been written." << std::endl;

    // ---------------------------------------------------------------------------
    //  STEP 5 Print the model to another CellML file
    //  5.a   Create a Printer and use it to serialise the model to a string

    auto printer = libcellml::Printer::create();
    std::string serialisedModelString = printer->printModel(model);

    //  5.b   Write the serialised string to a file
    outFileName = "quickstart_fixed.cellml";
    outFile.open(outFileName);
    outFile << serialisedModelString;
    outFile.close();

    std::cout << "The " << outFileName << " has been written." << std::endl;

    std::cout << "Finished!" << std::endl;
}
