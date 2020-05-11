/**
 *  TUTORIAL 2: Utilities
 *  This file contains helper functions for Tutorial 2
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <libcellml>

/**
 * @brief Prints the basic contents of a Model to the terminal
 */
void printModelToTerminal(libcellml::ModelPtr &model);
void printModelToTerminal(libcellml::ModelPtr &model, bool includeMaths);

/**
 * @brief Prints the validation errors to the terminal
 */
void printErrorsToTerminal(libcellml::ValidatorPtr &item);
void printErrorsToTerminal(libcellml::GeneratorPtr &item);
void printComponentToTerminal(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer);
void printComponentToTerminal(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer, bool includeMaths);
void printEncapsulationStructureToTerminal(libcellml::ModelPtr &model);
void printComponentOnlyToTerminal(libcellml::ComponentPtr &component, std::string spacer);

std::string fileContents(const std::string &fileName);

void switchUnitsInMaths(std::string &maths, std::string in, std::string out);
void insertIntoMathMLString(std::string &maths, std::string &addMe);

std::string getModelTypeFromEnum(libcellml::Generator::ModelType myType);
std::string getProfileFromEnum(libcellml::GeneratorProfile::Profile myType);

void solveWithEuler(double stepSize, int stepCount, std::string outFileName);

void listEquivalentVariables(const libcellml::VariablePtr &variable, std::vector<libcellml::VariablePtr> &variableList);

void printEquivalentVariableSet(const libcellml::VariablePtr &variable);
