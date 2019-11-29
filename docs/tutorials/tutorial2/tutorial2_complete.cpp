/**
 *  TUTORIAL 2: ERROR CHECKING AND VALIDATION
 *
 *  By the time you have worked through Tutorial 2 you will be able to:
 *    - use the Parser to report errors enountered when reading a file or
 *      deserialising a string
 *    - use the Validator to check for errors related to a model's description
 *      as compared to the CellML2.0 specifications
 *
 *  This tutorial assumes that you can already:
 *    - read and deserialise a CellML model from a file
 *    - retrieve the name and id of models, components, and variables,
 *    - navigate through the hierarchy of the model (model contains component(s)
 *      contain(s) variable(s) and maths)
 *    - serialise and print a Model structure to a CellML file.
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <libcellml>

#include "../utilities/tutorial_utilities.h"

int main() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "   TUTORIAL 2: ERROR CHECKING AND VALIDATION" << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;

  // ---------------------------------------------------------------------------
  //  STEP 1:   Create a CellML Model from the contents of a CellML file
  //
  std::string inFileName = "../resources/tutorial2.cellml";
  std::ifstream inFile(inFileName);
  std::stringstream inFileContents;
  inFileContents << inFile.rdbuf();
  std::cout << "Opening the CellML file: '" << inFileName << "'" << std::endl;
  libcellml::ParserPtr parser = libcellml::Parser::create();
  libcellml::ModelPtr model = parser->parseModel(inFileContents.str());

  // ---------------------------------------------------------------------------
  //  STEP 2:   Print the contents of the model to the terminal so that we can
  //            read it more easily. This step makes use of the utilities in the
  //            'tutorial_utilities.cpp/h' files
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "       Printing the parsed model" << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  printModelToTerminal(model);

  // ---------------------------------------------------------------------------
  //  STEP 3: Check that the model meets the CellML2.0 specifications using the
  //          Validator
  //
  //  2.a   Create a Validator and pass the model into it
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "       Validating the parsed model" << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  libcellml::ValidatorPtr validator = libcellml::Validator::create();
  validator->validateModel(model);

  //  2.b   Check whether there were errors returned from the validator
  int numberOfValidationErrors = validator->errorCount();
  if (numberOfValidationErrors != 0) {
    std::cout << "The validator has found " << numberOfValidationErrors
              << " errors!" << std::endl;

    // 2.c  Retrieve the errors, and print their description and specification
    //      reference to the terminal
    for (size_t e = 0; e < numberOfValidationErrors; ++e) {
      libcellml::ErrorPtr validatorError = validator->error(e);
      std::string errorSpecificationReference =
          validatorError->specificationHeading();

      std::cout << "  Validator error[" << e << "]:" << std::endl;
      std::cout << "     Description: " << validatorError->description()
                << std::endl;
      std::cout << "     Kind: " << (int)validatorError->kind() << std::endl;
      if (errorSpecificationReference != "") {
        std::cout << "    See section " << errorSpecificationReference
                  << " in the CellML specification." << std::endl;
      }
    }
  }

  // ---------------------------------------------------------------------------
  //  STEP 3:   Fix the errors that were printed in Step 2
  //

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
  model->component("i_am_a_component")
      ->variable("b")
      ->setUnits("dimensionless");

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
  //  allowed.  Simply assigning a unit to the variable will fix both errors.
  libcellml::VariablePtr variableD = model->component(0)->variable("d");
  variableD->setUnits("dimensionless");

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

  // ---------------------------------------------------------------------------
  //  STEP 4:   Check our changes by viewing the model again
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "       Printing the corrected model" << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  printModelToTerminal(model);

  //  STEP 5:   Validate the newer model and check for errors
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "       Validating the corrected model" << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  validator->validateModel(model);
  std::cout << "The validator found " << validator->errorCount()
            << " errors in the model." << std::endl;

  //  STEP 6:   Print corrected model to a file
  libcellml::PrinterPtr printer=libcellml::Printer::create();
  std::string serialisedModelString = printer->printModel(model);
  std::string outFileName = "tutorial1_printed.cellml";
  std::ofstream outFile(outFileName);
  outFile << serialisedModelString;
  outFile.close();

  std::cout << "The corrected '" << model->name()
            << "' model has been printed to: " << outFileName << std::endl;
}
