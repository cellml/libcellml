﻿/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "common.h"
#include "utilities.h"
#include "xmldoc.h"

#include "libcellml/component.h"
#include "libcellml/error.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/namespaces.h"
#include "libcellml/parser.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"
#include "libcellml/when.h"

#include <libxml/uri.h>

#include <algorithm>
#include <cmath> // Adding this to make the Ubuntu build happy ...
#include <deque>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <set>

namespace libcellml {

/**
* @brief The Validator::ValidatorImpl struct.
*
* The private implementation for the Validator class.
*/
struct Validator::ValidatorImpl
{
    Validator *mValidator;

    /**
    * @brief Check that the specified _ref item exists in the specified import url
    *
    * Any errors will be logged in the @c Validator.
    *
    */
    void checkImportIsAvailable(const std::string &find_path, 
                           const std::string &find_ref, 
                           const std::string &find_name,
                           const std::string &find_type,
                           std::vector<std::pair<std::string, std::string>> &history);

    /**
    * @brief A preliminary check of the importing file tree.
    *
    * If the Model was created by parsing a file, check that no other imported entity refers
    * to that original filename, and that there are no cycles present.  Any errors will be 
    * logged in the @c Validator.
    *
    */
    void validateImportSources(const ModelPtr &model, std::string &filename, std::string &working_directory);

    /**
        * @brief Validate the @p component using the CellML 2.0 Specification.
        * @cellml2_10 Validate the @p component using the CellML 2.0 Specification.
        *
        * Validate the given @p component and its encapsulated entities using
        * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
        *
        * @param component The component to validate.
        */
    void validateComponent(const ComponentPtr &component);

    /**
        * @brief Validate the @p units using the CellML 2.0 Specification.
        * @cellml2_8 Validate the @p units using the CellML 2.0 Specification.
        * Validate the given @p units and its encapsulated entities using
        * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
        *
        * @param units The units to validate.
        * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
        */
    void validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames);

    /**
        * @brief Validate the variable connections in the @p model using the CellML 2.0 Specification.
        * @cellml2_17 Validate the variable connections in the @p model using the CellML 2.0 Specification.
        * Validate the variable connections in the given @p model using
        * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
        *
        * @param model The model which may contain variable connections to validate.
        */
    void validateConnections(const ModelPtr &model);

    /**
    * @brief Validate that there are no cycles in the equivalance network in the @p model
    * using the CellML 2.0 Specification.  Called from the @c validateConnections function.
    * Any errors will be logged in the @c Validator.
    *
    * @param model The model which may contain variable connections to validate.
    * @param hintlist The helper string returned containing the list(s) of cyclic variables
    */
    bool isModelVariableCycleFree(const ModelPtr &model, std::vector<std::string> &hintlist);

    /**
    * @brief Utility function called recursively from the @c isModelVariableCycleFree function
    *
    * @param parent Previous variable
    * @param child Connected variable to start checking from
    * @param check_list The helper string returned containing the list(s) of cyclic variables
    */
    bool cycleVariableFound(VariablePtr &parent, VariablePtr &child, std::deque<libcellml::VariablePtr> &check_list);

    /**
        * @brief Check if the provided @p name is a valid CellML identifier.
        *
        * Check if the provided @p name is a valid CellML identifier according
        * to the CellML 2.0 specification. This requires a non-zero length Unicode
        * character sequence containing basic Latin alphanumeric characters or
        * underscores that does not start with a number.
        *
        * @param name The @c std::string name to check the validity of.
        *
        * @return @c true if @name is a valid CellML identifier and @c false otherwise.
        */
    bool isCellmlIdentifier(const std::string &name);

    /**
        * @brief Validate the @c unit at index @c index from @p units using the CellML 2.0 Specification.
        *
        * Validate the @c unit at index @c index from @p units using
        * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
        *
        * @param index The index of the @c unit to validate from @p units.
        * @param units The units to validate.
        * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
        */
    void validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames);

    /**
        * @brief Validate the @p variable using the CellML 2.0 Specification.
        * @cellml2_11 Validate the variable using the CellML 2.0 Specification
        * Validate the given @p variable using the CellML 2.0 Specification.
        * Any errors will be logged in the @c Validator.
        *
        * @param variable The variable to validate.
        * @param variableNames A vector list of the name attributes of the @p variable and its siblings.
        */
    void validateVariable(const VariablePtr &variable, std::vector<std::string> &variableNames);

    /**
        * @brief Validate the @p reset using the CellML 2.0 Specification.
        * @cellml2_12 Validate the @p reset using the CellML 2.0 Specification.
        * Examine the @p reset for conformance to the CellML 2.0 specification.  Any
        * errors will be logged in the @c Validator.
        *
        * @param reset The reset to validate.
        * @param component The component the reset belongs to.
        */
    void validateReset(const ResetPtr &reset, const ComponentPtr &component);

    /**
        * @brief Validate the @p when using the CellML 2.0 specification.
        * @cellml2_13 Validate the @p when using the CellML 2.0 specification.
        * Examine the @p when for conformance to the CellML 2.0 specification.  Any
        * errors will be logged in the @c Validator.
        *
        * @param when The when to validate.
        * @param reset The reset the when belongs to.
        * @param component The component the reset belongs to.
        */
    void validateWhen(const WhenPtr &when, const ResetPtr &reset, const ComponentPtr &component);

    /**
        * @brief Validate the math @p input @c std::string.
        * @cellml2_14 Validate the math @p input @c std::string.
        * Validate the math @p input @c std::string using the CellML 2.0 Specification and
        * the W3C MathML DTD. Any errors will be logged in the @c Validator.
        *
        * @param input The math @c std::string to validate.
        * @param component The component containing the math @c std::string to be validated.
        */
    void validateMath(const std::string &input, const ComponentPtr &component);

    /**
        * @brief Populate @p bvarNames with new variables declared in MathML @c bvar elements.
        *
        * Populate @p bvarNames with new variables declared in MathML @c bvar elements found within
        * the XmlNode @p node.
        *
        * @param node The @c XmlNode to search for @c bvar element names.
        * @param bvarNames The @c std::string @c vector to populate with MathML @c bvar element names.
        */
    void gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames);

    /**
        * @brief Traverse the node tree for invalid MathML elements.
        *
        * Traverse the Xml node tree checking that all MathML elements are listed in the
        * supported MathML elements table from the CellML specification 2.0 document.
        *
        * @param node The node to check children and sibling nodes.
        * @param component The component the MathML belongs to.
        */
    void validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component);

    /**
        * @brief Validate CellML variables and units in MathML @c ci and @c cn variables. Removes CellML units from the @p node.
        *
        * Validates CellML variables found in MathML @c ci elements and new variables from @c bvar elements. Validates @c cellml:units
        * attributes found on @c ci and @c cn elements and removes them from the @c XmlNode @p node to leave MathML that may then
        * be validated using the MathML DTD.
        *
        * @param node The @c XmlNode to validate CellML entities on and remove @c cellml:units from.
        * @param component The component that the math @c XmlNode @p node is contained within.
        * @param variableNames A @c vector list of the names of variables found within the @p component.
        * @param bvarNames A @c vector list of the names of new MathML @c bvar variables in this @c XmlNode @p node.
        */
    void validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames, const std::vector<std::string> &bvarNames);

    /**
        * @brief Remove the @c std::string @p pattern from the @c std::string @p input.
        *
        * Remove all occurrences of the @c std::string @p pattern from the @c std::string @p input.
        *
        * @param input The @c std::string to remove all occurrences of the @p pattern from.
        * @param pattern The @c std::string to remove from the @c std::string @p input.
        */
    void removeSubstring(std::string &input, std::string &pattern);

    /**
        * @brief Check if the provided @p name is a standard unit.
        *
        * Checks if the provided @p name is one of the standard units in the
        * @c Units::StandardUnit @c enum. Returns @c true if @name is a standard unit
        * and @c false otherwise.
        *
        * @param name The @c std::string name to check against the list of standard units.
        *
        * @return @c true if @name is a standard unit and @c false otherwise.
        */
    bool isStandardUnitName(const std::string &name);

    /**
        * @brief Check if the provided @p name is a standard prefix.
        *
        * Checks if the provided @p name is one of the standard prefixes in the
        * @c Prefix @c enum. Returns @c true if @name is a standard prefix
        * and @c false otherwise.
        *
        * @param name The @c std::string name to check against the list of standard prefixes.
        *
        * @return @c true if @name is a standard prefix and @c false otherwise.
        */
    bool isStandardPrefixName(const std::string &name);

    /**
        * @brief Check if the provided @p node is a supported MathML element.
        *
        * Checks if the provided @p node is one of the supported MathML elements defined in the table
        * of supported MathML elements from the CellML specification version 2.0 document.
        *
        * @param node The @c XmlNode node to check against the list of supported MathML elements.
        * @return @c true if @node is a supported MathML element and @c false otherwise.
        */
    bool isSupportedMathMLElement(const XmlNodePtr &node);

    /**
    * @brief Validate that equivalent variable pairs in the @p model
    * have equivalent units.
    * @cellml2_19 Validate that equivalent variable pairs in the @p model
    * have equivalent units
    * Any errors will be logged in the @c Validator.
    *
    * @param model The model containing the variables
    * @param v1 The variable which may contain units.
    * @param v2 The equivalent variable which may contain units.
    * @param hints String containing error messages to be passed back to calling function for logging
    */
    bool unitsAreEquivalent(const ModelPtr &model, const VariablePtr &v1, const VariablePtr &v2, std::string &hints);

    /**
    * @brief Utility function used by unitsAreEquivalent to compare base units of two varaibles
    *
    * @param model The model containing the variables
    * @param unitmap A list of the exponents of base varaibles.
    * @param uName String name of the current variable being investigated.
    * @param standardList Nested map of the conversion between built-in units and the base units they contain
    * @param uExp Exponent of the current unit in its parent.  
    */
    void incrementBaseUnitCount(const ModelPtr &model, 
                                std::map<std::string,double> &unitmap, 
                                double &multmap,
                                const std::string uName,
                                const double uExp,
                                const double logMult);

    /**
    * @brief Utility function used by unitsAreEquivalent to compare base units of two varaibles
    *
    * @param model The model containing the variables
    * @param unitmap A list of the exponents of base varaibles.
    * @param uName String name of the current variable being investigated.
    * @param standardList Nested map of the conversion between built-in units and the base units they contain
    * @param uExp Exponent of the current unit in its parent.  
    */
    void decrementBaseUnitCount(const ModelPtr &model, 
                                std::map<std::string,double> &unitmap, 
                                double &multmap,
                                const std::string uName,
                              /*  const std::map< std::string, std::map<std::string, double>> &standardList,
                                std::map<std::string,double> &standardMultList,
                                const std::map<std::string, double> &prefixList,*/
                                const double uExp,
                                const double logMult);

    /**
    * @brief Checks dependency heirarchies of units in the model 
    *
    * @param model The model containing the units to be tested
    */
    void validateNoUnitsAreCyclic(const ModelPtr &model);

    /**
    * @brief Utility function called recursively by validateNoUnitsAreCyclic
    *
    * @param model The model containing the units to be tested
    * @param parent The current Units pointer to test
    * @param history A vector of the chained dependencies.  Cyclic variables exist where the first and 
    *                last units are equal.
    */
    void checkUnitForCycles(const ModelPtr &model, const UnitsPtr &parent,
                            std::vector<std::string> &history);

};

Validator::Validator()
    : mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = this;
}

Validator::~Validator()
{
    delete mPimpl;
}

Validator::Validator(const Validator &rhs)
    : Logger(rhs)
    , mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = rhs.mPimpl->mValidator;
}

Validator::Validator(Validator &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Validator& Validator::operator=(Validator v)
{
    Logger::operator =(v);
    v.swap(*this);
    return *this;
}

void Validator::swap(Validator &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Validator::validateModel(const ModelPtr &model) {
    // If a filename is not specified, trigger zero-depth import checking as working directory is unknown
    validateModel(model, "",""); 
}

void Validator::validateModel(const ModelPtr &model, std::string filename) {
    // Splitting full path filename into path and filename for validation
    std::string f = "";
    std::string p = "";
    size_t i = filename.find_last_of("/\\");
    if (i != std::string::npos) {
        f = filename.substr(i + 1, filename.length() - i);
        p = filename.substr(0, i + 1);
    }
    validateModel(model, f, p);
}

void Validator::validateModel(const ModelPtr &model, std::string filename, std::string working_directory) {
    // Clear any pre-existing errors in the validator instance.
    clearErrors();
    /// @cellml2_4 4.2.1 Check for a valid name format
    if (!mPimpl->isCellmlIdentifier(model->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Model does not have a valid name attribute.");
        err->setModel(model);
        err->setRule(SpecificationRule::MODEL_NAME);
        addError(err);
    }

    // Checking that the filename is indeed relative
    if (filename != "") {
        bool is_relative = isRelativePath(filename);
        if ((is_relative) && (working_directory != "")) {
            mPimpl->validateImportSources(model, filename, working_directory);
        }
        else if (!is_relative) {
            size_t i = filename.find_last_of("/\\", filename.length());
            std::string f = "";
            std::string p = "";
            if (i != std::string::npos) {
                f = filename.substr(i+1, filename.length() - i);
                p = filename.substr(0,i+1);
            }
            // TODO Return warning that working directory is changed to root of file path
            mPimpl->validateImportSources(model, f, p);
        }  
    }

    // Check for components in this model.
    /// @cellml2_4 4.2.3 Check for unique encapsulation is not required as more than one cannot be stored
    /// @cellml2_4 4.2.2 Check for presence of components in this model.
    if (model->componentCount() > 0) {
        std::vector<std::string> componentNames;
        std::vector<std::string> componentRefs;  
        std::vector<std::string> componentImportSources;
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);

            std::string componentName = component->getName();
            if (componentName.length()) {
                if (component->isImport()) {
                    // Check for a component_ref; assumes imported if the import source is not null
                    /// @cellml2_7 7.1.2 Check that the name of the component given by the component_ref 
                    /// is in a valid format.  NB: Does not check what it refers to.
                    std::string component_ref = component->getImportReference(); 
                    std::string import_source = component->getImportSource()->getUrl(); 

                    if (!mPimpl->isCellmlIdentifier(component_ref)) {
                        
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported component '" + componentName +
                                            "' does not have a valid component_ref attribute.");
                        err->setComponent(component);
                        err->setRule(SpecificationRule::IMPORT_COMPONENT_REF);
                        addError(err);
                    }
                    /// @cellml2_7 7.1.2 Check that a xlink:href attribute is present
                    if (!import_source.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of component '" + componentName +
                                            "' does not have a valid locator xlink:href attribute.");
                        err->setImportSource(component->getImportSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                    }
                    /// @cellml2_5 5.1.1 Check that xlink:href meets XLink specs
                    else {
                        xmlURIPtr URIPtr = xmlParseURI(import_source.c_str());
                        if (URIPtr == NULL) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Import of component '" + componentName +
                                                "' has an invalid URI in the href attribute, '" + import_source + "'. ");
                            err->setImportSource(component->getImportSource());
                            err->setRule(SpecificationRule::IMPORT_HREF);
                            addError(err);
                            
                        }
                        else xmlFreeURI(URIPtr);
                    }                   
                    // Push back the unique sources and refs.
                    componentImportSources.push_back(import_source);
                    componentRefs.push_back(component_ref);
                }
                /// @cellml2_10 10.1.1 Check for duplicate component names in this model.
                if(std::find(componentNames.begin(), componentNames.end(), componentName) != componentNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->getName() +
                                        "' contains multiple components with the name '" + componentName +
                                        "'. Valid component names must be unique to their model.");
                    err->setModel(model);
                    addError(err);
                }
                componentNames.push_back(componentName);
            }
            /// @cellml2_4 4.2.1 Validates components in this model.
            /// @cellml2_10 10.1.1 This function call validates the names and other aspects of the components in the model.
            mPimpl->validateComponent(component);
        }
    }
    /// @cellml2_4 4.2.2.5 Check for presence of units in this model 
    if (model->unitsCount() > 0) {
        std::vector<std::string> unitsNames;
        std::vector<std::string> unitsRefs;
        std::vector<std::string> unitsImportSources;
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            UnitsPtr units = model->getUnits(i);
            std::string unitsName = units->getName();
            if (unitsName.length()) {
                if (units->isImport()) {
                    /// @cellml2_6 6.1.2 Check for a units_ref in this import units instance
                    std::string unitsRef = units->getImportReference();
                    std::string import_source = units->getImportSource()->getUrl();
                    /// @cellml2_6 6.1.2 Check that the name given by the units_ref matches the naming specifications
                    if (!mPimpl->isCellmlIdentifier(unitsRef)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported units '" + unitsName +
                                            "' does not have a valid units_ref attribute.");
                        err->setUnits(units);
                        err->setRule(SpecificationRule::IMPORT_UNITS_REF);
                        addError(err);
                    }
                    /// @cellml2_6 6.1.2 Check that a xlink:href is present 
                    if (!import_source.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of units '" + unitsName +
                                            "' does not have a valid locator xlink:href attribute.");
                        err->setImportSource(units->getImportSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                    }
                    /// @cellml2_5 5.1.1 Check that xlink:href meets XLink specs 
                    else {
                        xmlURIPtr URIPtr = xmlParseURI(import_source.c_str());
                        if (URIPtr == NULL) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Import of units '" + unitsName +
                                                "' has an invalid URI in the href attribute, '" + import_source + "'. ");
                            err->setImportSource(units->getImportSource());
                            err->setRule(SpecificationRule::IMPORT_HREF);
                            addError(err);
                        } 
                        else xmlFreeURI(URIPtr);
                    }
                    // Push back the unique sources and refs.
                    unitsImportSources.push_back(import_source);
                    unitsRefs.push_back(unitsRef);
                }
                /// @cellml2_8 8.1.2 Check for duplicate units names in this model.
                if(std::find(unitsNames.begin(), unitsNames.end(), unitsName) != unitsNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->getName() +
                                        "' contains multiple units with the name '" + unitsName +
                                        "'. Valid units names must be unique to their model.");
                    err->setModel(model);
                    err->setRule(SpecificationRule::UNITS_NAME_UNIQUE);
                    addError(err);
                }
                unitsNames.push_back(unitsName);
            }
        }
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            /// @cellml2_4 4.2.2.5 Validate units in this model
            /// @cellml2_8 Validate units in this model
            UnitsPtr units = model->getUnits(i);
            mPimpl->validateUnits(units, unitsNames);
        }
    }

    /// @cellml2_9 9.1.1.2 Validate that unit definitions are not cyclic
    // Have to have this out of the if statement so that we only test checked units
    if(model->unitsCount() > 0)
        mPimpl->validateNoUnitsAreCyclic(model);

    /// @cellml2_4 4.2.2.2 Validate any connections / variable equivalence networks in the model.
    mPimpl->validateConnections(model);
}

void Validator::ValidatorImpl::validateImportSources(const ModelPtr &model, std::string &filename, 
                                                     std::string &working_directory) {
    // Check against the working directory location (assumed same as path to filename or model import filename)
    if (model->componentCount() > 0) {
        std::vector<std::string> componentNames;
        std::vector<std::string> componentRefs;
        std::vector<std::string> componentImportSources;
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);
            std::string componentName = component->getName();
            if (componentName.length()) {
                if (component->isImport()) {
                    // Check that a concrete instance of a component exists at the end of import chain
                    std::string component_ref = component->getImportReference();
                    std::string import_source = working_directory + component->getImportSource()->getUrl();
                    std::vector<std::pair<std::string, std::string>> history;
                    history.push_back(std::make_pair(componentName, filename));
                    checkImportIsAvailable(working_directory, import_source, component_ref, "component", history);
                    std::vector<std::pair<std::string,std::string>>().swap(history);  
                }
            }
        }
    }

    if (model->unitsCount() > 0) {
        std::vector<std::string> unitsNames;
        std::vector<std::string> unitsRefs;
        std::vector<std::string> unitsImportSources;
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            UnitsPtr units = model->getUnits(i);
            std::string unitsName = units->getName();
            if (unitsName.length()) {
                if (units->isImport()) {
                    // Check that a concrete instance of units exists at the end of the import chain
                    std::string unitsRef = units->getImportReference();
                    std::string import_source = working_directory + units->getImportSource()->getUrl();
                    std::vector<std::pair<std::string, std::string>> history;
                    history.push_back(std::make_pair(unitsName, filename));
                    checkImportIsAvailable(working_directory, import_source, unitsRef, "units", history);
                    std::vector<std::pair<std::string,std::string>>().swap(history);  
                }
            }
        }
    }
}

void Validator::ValidatorImpl::checkImportIsAvailable(const std::string &find_path,
                                                 const std::string &find_ref,
                                                 const std::string &find_name, 
                                                 const std::string &find_type,
                                                 std::vector<std::pair<std::string, std::string>> &history )
{
    // Function to locate the imported entity of type=find_type in file=find_ref with name=find_name 
    std::string file_to_open = "";
    std::string working_directory = "";
    
    if (isRelativePath(find_ref)) {
        // Add parent's working directory to file path
        file_to_open = find_path + find_ref;
        working_directory = find_path;
    } else {
        file_to_open = find_ref;
        // Update working directory to the path of this file for future relative imports
        working_directory = find_ref.substr(0, find_ref.find_last_of("/\\") + 1);
    }

    // Check that this pair of item name, type and file has not been included in the history already
    auto p = std::make_pair(find_name,file_to_open);
    if(std::find(history.begin(), history.end(), p) == history.end())
        history.push_back(p);
    else {
        history.push_back(p);
        ErrorPtr err = std::make_shared<Error>();
        std::string e("");
        std::string sep("         ");
        std::string separator(" which imports ");
        for (const auto& i : history) {
            e += sep+"\n ('" + i.first + "' in " + i.second + ")";
            sep = separator;
        }
        err->setDescription("Import of "+find_type+" '"+history[0].first+"' has circular dependencies:"+e);
        err->setKind(Error::Kind::IMPORT);
        mValidator->addError(err);
        return;
    }

    XmlDocPtr doc = std::make_shared<XmlDoc>();
    std::ifstream t(file_to_open);
    if (t.fail()) {
        ErrorPtr err = std::make_shared<Error>();
        std::string e("");
        std::string sep = "         ";
        std::string separator(" which imports");
        for (const auto& i : history) {
            e += sep+"\n ('" + i.first + "' in " + i.second + ")";
            sep = separator;
        }
        err->setDescription(
            "Import of " + find_type + " '" + history[0].first + 
            "' has failed: " + 
            e + " but the file was not found.");
        mValidator->addError(err);
        return;
    }

    std::stringstream buffer;
    buffer << t.rdbuf();
    doc->parse(buffer.str());

    // Copy any XML parsing errors into the common parser error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Error found when reading " + file_to_open +
                                ": " + doc->getXmlError(i));
            err->setKind(Error::Kind::XML);
            mValidator->addError(err);
        }
    }

    const XmlNodePtr node = doc->getRootNode();

    if (!node) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Could not get a valid XML root node from the provided input.");
        err->setKind(Error::Kind::XML);
        mValidator->addError(err);
        return;
    } 
    else if (!node->isCellmlElement("model")) {
        ErrorPtr err = std::make_shared<Error>();
        if (node->getName() == "model") {
            std::string nodeNamespace = node->getNamespace();
            if (nodeNamespace.empty())
                nodeNamespace = "null";
            err->setDescription("Model element is in invalid namespace '" + nodeNamespace +
                                "'. A valid CellML root node should be in namespace '" + CELLML_2_0_NS +
                                "'.");
        } else {
            err->setDescription("Model element is of invalid type '" + node->getName() +
                                "'. A valid CellML root node should be of type 'model'.");
        }
        mValidator->addError(err);
        return;
    }

    // Get model name
    XmlAttributePtr attribute = node->getFirstAttribute();
    std::string model_name;
    while (attribute) {
        if (attribute->isType("name")) {
            model_name = attribute->getValue();
        } else if (attribute->isType("id")) {
            // Skip
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + node->getAttribute("name") +
                                "' imported from '"+ file_to_open +
                                "' has an invalid attribute '" + attribute->getName() + "'.");
            mValidator->addError(err);
        }
        attribute = attribute->getNext();
    }

    // Get model children (CellML entities), the only valid imported entities are components or units
    XmlNodePtr childNode = node->getFirstChild();
    std::string other_type = find_type == "component" ? "units" : "component";

    while (childNode) {
        if (childNode->isCellmlElement(find_type.c_str())) {
            // Concrete type: check name attribute for find_name
            XmlAttributePtr attribute = childNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("name")) {
                    if (attribute->getValue() == find_name) {
                        // Stop searching, have reached concrete definition for this item, delete history and return
                        std::vector<std::pair<std::string,std::string>>().swap(history);
                        return;
                    }
                } else if (attribute->isType("id")) {
                    // Skip
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Element 'import "+find_type+"' in file '" + file_to_open +
                                        "' has an invalid attribute '" + attribute->getName() + "'.");
                    mValidator->addError(err);
                }
                attribute = attribute->getNext();
            } 
        }
        else if (childNode->isCellmlElement("import")) {
            XmlAttributePtr importAttribute = childNode->getFirstAttribute();
            std::string import_child_ref = "";
            while (importAttribute) {
                if (importAttribute->isType("href", XLINK_NS)) {
                    import_child_ref = importAttribute->getValue();
                } else if (importAttribute->isType("id")) {
                    // Skip
                } else if (importAttribute->isType("xlink")) {
                    // Skip
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import from '" + find_ref +
                                        "' has an invalid attribute '" + importAttribute->getName() + "'.");
                    mValidator->addError(err);
                }
                importAttribute = importAttribute->getNext();
            }

            // Import type: check children for find_type
            XmlNodePtr importChild = childNode->getFirstChild();
            std::string find_type_ref = find_type + "_ref";
            
            while (importChild) {
                if (importChild->isCellmlElement(find_type.c_str())) {
                    XmlAttributePtr importAttribute = importChild->getFirstAttribute();
                    std::string import_name = "";
                    bool use_me = false;

                    while (importAttribute) {
                        if ((importAttribute->isType("name")) && (importAttribute->getValue()== find_name)) {
                            use_me = true;
                        } else if (importAttribute->isType(find_type_ref.c_str())) {
                            import_name = importAttribute->getValue();
                        } else if (importAttribute->isType("id")) {
                            // Skip
                        } else {
                            // TODO Add some error here?
                        }
                        importAttribute = importAttribute->getNext();
                    } 

                    if (use_me) {
                        checkImportIsAvailable(working_directory, import_child_ref, import_name, find_type, history);
                        return;
                    }
                } else if (importChild->isCellmlElement(other_type.c_str())) {
                    // Skip other type of imports in this block
                } 
                else if (importChild->isText()) {
                    std::string textNode = importChild->convertToString();
                    // Ignore whitespace when parsing.
                    if (hasNonWhitespaceCharacters(textNode)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Model '" + model_name +
                                            " in file " + file_to_open +
                                            " has an invalid non-whitespace child text element '" + textNode + "'.");
                        err->setRule(SpecificationRule::MODEL_CHILD);
                        mValidator->addError(err);
                    }
                } else if (importChild->isComment()) {
                    // Do nothing.
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model_name +
                                        " in file " + file_to_open +
                                        "' has an invalid child element '" + importChild->getName() + "'.");
                    err->setRule(SpecificationRule::MODEL_CHILD);
                    mValidator->addError(err);
                }
                importChild = importChild->getNext();
            }
        }
        else if ((childNode->isCellmlElement(other_type.c_str())) 
                 || (childNode->isCellmlElement("encapsulation")) 
                 || (childNode->isCellmlElement("connection")) 
                 || (childNode->isComment())) {
            // Skip - only want the type and name we're currently looking for          
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Model '" + model_name + "' from file " + file_to_open +
                                    " has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setRule(SpecificationRule::MODEL_CHILD);
                mValidator->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + model_name + "' from file " + file_to_open +
                                "' has an invalid child element '" + childNode->getName() + "'.");
            err->setRule(SpecificationRule::MODEL_CHILD);
            mValidator->addError(err);
        }
        childNode = childNode->getNext();
    }

    ErrorPtr err = std::make_shared<Error>();
    std::string e("");
    std::string sep = "         ";
    std::string separator(" imports ");
    for (const auto& i : history) {
        e += sep+"\n ('" + i.first + "' in " + i.second + ")";
        sep = separator;
    }
    err->setDescription(
        "Import of " + find_type + " '" + history[0].first + 
        "' has failed. Tried: " + 
        e + " which was not found in the file.");
    mValidator->addError(err);
}

void Validator::ValidatorImpl::validateNoUnitsAreCyclic(const ModelPtr &model) {

    std::vector<std::string> history;
    for (size_t i = 0; i < model->unitsCount(); ++i) {
        // Test each units' dependencies for presence of self in tree
        UnitsPtr u = model->getUnits(i);
        history.push_back(u->getName());
        checkUnitForCycles(model, u, history); 
        // Have to delete this each time to prevent reinitialisation with previous base variables
        std::vector<std::string>().swap(history);
    }
}

void Validator::ValidatorImpl::checkUnitForCycles(const ModelPtr &model, const UnitsPtr &parent, 
                                                  std::vector<std::string> &history) {
    if (parent->isBaseUnit()) return;

    // Recursive function to check for self-referencing in unit definitions
    std::string ref, id, prefix;
    double exp, mult;

    // Take history, and copy it for each new branch
    for (size_t i = 0; i < parent->unitCount(); ++i) {
        parent->getUnitAttributes(i, ref, prefix, exp, mult, id);
        if (std::find(history.begin(), history.end(), ref) != history.end()) {
            history.push_back(ref);
            // Print to error output *only* when the first and last units are the same
            // otherwise we get lasso shapes reported 
            if (history.front() == history.back()) {
                ErrorPtr err = std::make_shared<Error>();
                std::string des = "'";
                for (size_t i = 0; i < history.size() - 1; ++i) {
                    des += history[i] + "' -> '";
                }
                des += history[history.size() - 1]+"'";
                err->setDescription("Cyclic units exist: " + des);
                err->setModel(model);
                err->setKind(Error::Kind::UNITS);
                mValidator->addError(err);
            }
        }
        else {
            // Step into dependencies if they are not built-in units
            if (model->hasUnits(ref)) {
                UnitsPtr child = model->getUnits(ref);
                history.push_back(ref);
                // Making a copy of the history vector to this point
                std::vector<std::string> child_history(history);
                checkUnitForCycles(model, child, child_history);
                std::vector<std::string>().swap(child_history);
            } 
        }
    }
}

void Validator::ValidatorImpl::validateComponent(const ComponentPtr &component)
{
    /// @cellml2_10 10.1.1 Check for a valid name attribute. 
    if (!isCellmlIdentifier(component->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setComponent(component);
        if (component->isImport()) {
            err->setDescription("Imported component does not have a valid name attribute.");
            err->setRule(SpecificationRule::IMPORT_COMPONENT_NAME);
        } else {
            err->setDescription("Component does not have a valid name attribute.");
            err->setRule(SpecificationRule::COMPONENT_NAME);
        }
        mValidator->addError(err);
    }
    /// @cellml2_10 10.1.2.1 Check the variables in this component.  
    std::vector<std::string> variableNames;
    if (component->variableCount() > 0) {
        /// @cellml2_11 11.1.1 Check for duplicate variable names in imported components
        // Check for duplicate variable names and construct vector of valid names in case
        // we have a variable initial_value set by reference.
        for (size_t i = 0; i < component->variableCount(); ++i) {
            std::string variableName = component->getVariable(i)->getName();
            if (variableName.length()) {
                if (std::find(variableNames.begin(), variableNames.end(), variableName) != variableNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->getName() +
                                        "' contains multiple variables with the name '" + variableName +
                                        "'. Valid variable names must be unique to their component.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::VARIABLE_NAME);
                    mValidator->addError(err);
                }
                variableNames.push_back(variableName);
            }
        }
        /// @cellml2_11 11.1.1 Validates variable(s) in a componenet
        for (size_t i = 0; i < component->variableCount(); ++i) {
            VariablePtr variable = component->getVariable(i);
            validateVariable(variable, variableNames);
        }
    }
    /// @cellml2_10 10.1.2.2 Check for presence of resets in this component
    if (component->resetCount() > 0) {
        /// @cellml2_12 12.1.1.2 Check for duplicate order values in resets in this component
        std::vector<int> resetOrders;
        for (size_t i = 0; i < component->resetCount(); ++i) {
            ResetPtr reset = component->getReset(i);
            int resetOrder = reset->getOrder();
            if (reset->isOrderSet()) {
                if (std::find(resetOrders.begin(), resetOrders.end(), resetOrder) != resetOrders.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->getName() +
                                        "' contains multiple resets with order '" + convertIntToString(resetOrder) + "'.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::RESET_ORDER);
                    mValidator->addError(err);
                } else {
                    resetOrders.push_back(resetOrder);
                }
            }
        }
        /// @cellml2_10 10.1.2.2 Validate resets in this component's variables
        for (size_t i = 0; i < component->resetCount(); ++i) {
            ResetPtr reset = component->getReset(i);
            validateReset(reset, component);
        }
    }
    /// @cellml2_10 10.1.2.3 Validate math through the private implementation (for XML handling) in this component
    if (component->getMath().length()) {
        validateMath(component->getMath(), component);
    }
}

void Validator::ValidatorImpl::validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames)
{
    /// @cellml2_8 8.1.1 check that the units' name field is present
    if (!isCellmlIdentifier(units->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setUnits(units);
        if (units->isImport()) {
            err->setDescription("Imported units does not have a valid name attribute.");
            err->setRule(SpecificationRule::IMPORT_UNITS_NAME);
        } else {
            err->setDescription("Units does not have a valid name attribute.");
            err->setRule(SpecificationRule::UNITS_NAME);
        }
        mValidator->addError(err);
    } else {
        /// @cellml2_8 8.1.3 Checks for duplicated names in the standard/built-in units.
        if (isStandardUnitName(units->getName())) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units is named '" + units->getName() +
                                "', which is a protected standard unit name.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNITS_STANDARD);
            mValidator->addError(err);
        }
    }
    if (units->unitCount() > 0) {
        /// @cellml2_8 8.1.4 Validates each unit in units.
        for (size_t i = 0; i < units->unitCount(); ++i) {
            validateUnitsUnit(i, units, unitsNames);
        }
    }
}

void Validator::ValidatorImpl::validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames)
{
    // Validate the unit at the given index.
    std::string reference, prefix, id;
    double exponent, multiplier;

    // TODO This function silently sets invalid numbers to 1.0, maybe should give a better error message?
    units->getUnitAttributes(index, reference, prefix, exponent, multiplier, id);
    /// @cellml2_9 9.1.1 Check that the unit element has a units reference
    if (isCellmlIdentifier(reference)) {
        if ((std::find(unitsNames.begin(), unitsNames.end(), reference) == unitsNames.end()) &&
            (!isStandardUnitName(reference))) {
            /// @cellml2_8 8.1.1 Check that units point to a standard or local unit base
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units reference '" + reference + "' in units '" + units->getName() +
                                    "' is not a valid reference to a local units or a standard unit type.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNIT_UNITS_REF);
            mValidator->addError(err);
        }
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Unit in units '" + units->getName() +
                            "' does not have a valid units reference.");
        err->setUnits(units);
        err->setRule(SpecificationRule::UNIT_UNITS_REF);
        mValidator->addError(err);
    }
    if (prefix.length()) {
        /// cellml2_9 9.1.2.1 Check the prefix. If the prefix is not in the list of valid prefix names, 
        /// check that it is an integer.
        if (!isStandardPrefixName(prefix)) {

            if (!isCellMLInteger(prefix)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Prefix '" + prefix + "' of a unit referencing '" + reference +
                                    "' in units '" + units->getName() +
                                    "' is not a valid integer or a SI prefix.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_PREFIX);
                mValidator->addError(err);
            }
            else {
                try {
                    int test = std::stoi(prefix);
                    (void)test;
                }
                catch (std::out_of_range&) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Prefix '" + prefix + "' of a unit referencing '" + reference +
                                        "' in units '" + units->getName() +
                                        "' is out of the integer range.");
                    err->setUnits(units);
                    err->setRule(SpecificationRule::UNIT_PREFIX);
                    mValidator->addError(err);
                }
            }
        }
    }
}

void Validator::ValidatorImpl::validateVariable(const VariablePtr &variable, std::vector<std::string> &variableNames)
{
    /// @cellml2_11 11.1.1.1 Check for a valid name attribute. Validator::ValidatorImpl::validateVariable
    if (!isCellmlIdentifier(variable->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable does not have a valid name attribute.");
        err->setVariable(variable);
        err->setRule(SpecificationRule::VARIABLE_NAME);
        mValidator->addError(err);
    }
    /// @cellml2_11 11.1.1.2 Check that this variable specifies units which have an identifier
    if (!isCellmlIdentifier(variable->getUnits())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable '" + variable->getName() +
                            "' does not have a valid units attribute.");
        err->setVariable(variable);
        err->setRule(SpecificationRule::VARIABLE_UNITS);
        mValidator->addError(err);
    } else if (!isStandardUnitName(variable->getUnits())) {
        Component* component = static_cast<Component*>(variable->getParent());
        Model* model = static_cast<Model*>(component->getParent());
        /// @cellml2_11 11.1.2 Check that this variable has units which, if non-standard, are specified in the model
        if (model && !model->hasUnits(variable->getUnits())) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->getName() +
                                "' has an invalid units reference '" + variable->getUnits() +
                                "' that does not correspond with a standard unit or units in the variable's parent component or model.");
            err->setVariable(variable);
            err->setRule(SpecificationRule::VARIABLE_UNITS);
            mValidator->addError(err);
        }
    }
    
    if (variable->getInterfaceType().length()) {
        std::string interfaceType = variable->getInterfaceType();
        /// @cellml2_11 11.1.2.1 If this variable specifies an interface, checks that its type is public, private, 
        /// public_and_private, or none.
        if ((interfaceType != "public") && (interfaceType != "private") &&
            (interfaceType != "none") && (interfaceType != "public_and_private")) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->getName() +
                                "' has an invalid interface attribute value '" + interfaceType + "'.");
            err->setVariable(variable);
            err->setRule(SpecificationRule::VARIABLE_INTERFACE);
            mValidator->addError(err);
        }
    }
    
    if (variable->getInitialValue().length()) {
        std::string initialValue = variable->getInitialValue();
        // Check if initial value is a variable reference
        /// @cellml2_11 11.1.2.2 If this variable specifies an initial value, checks that it has a valid reference
        if(!(std::find(variableNames.begin(), variableNames.end(), initialValue) != variableNames.end())) {
            // Otherwise, check that the initial value can be converted to a double
            /// @cellml2_11 11.1.2.2 If the initial value is not a reference, then check it's convertible to a double
            if (!isCellMLReal(initialValue)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + variable->getName() +
                                    "' has an invalid initial value '" + initialValue +
                                    "'. Initial values must be a real number string or a variable reference.");
                err->setVariable(variable);
                err->setRule(SpecificationRule::VARIABLE_INITIAL_VALUE);
                mValidator->addError(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateReset(const ResetPtr &reset, const ComponentPtr &component)
{
    /// @cellml2_12 12.1.1.2 Check that this reset order is set
    std::string orderString;
    if (reset->isOrderSet()) {
        orderString = "with order '" + convertIntToString(reset->getOrder()) + "'";
    } else {
        orderString = "does not have an order set,";
    }

    /// @cellml2_12 12.1.1.1 Check that this reset references a variable 
    std::string variableString;
    std::string variableContinuation = "";
    if (reset->getVariable() == nullptr) {
        variableString = "does not reference a variable";
        variableContinuation = ",";
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() +
                            "' " + orderString +
                            " " + variableString + ".");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_VARIABLE_REFERENCE);
        mValidator->addError(err);
    } else {
        variableString = "referencing variable '" + reset->getVariable()->getName() + "'";
    }

    if (!reset->isOrderSet()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() +
                            "' " + orderString +
                            " " + variableString + ".");
        err->setComponent(component);
        err->setRule(SpecificationRule::RESET_ORDER);
        mValidator->addError(err);
    }

    /// @cellml2_12 12.1.1.2 Checking for duplicate order values for each 'when' entry in this reset
    if (reset->whenCount() > 0) {
        // Check for duplicate when order values.
        std::vector<int> whenOrders;
        for (size_t i = 0; i < reset->whenCount(); ++i) {
            WhenPtr when = reset->getWhen(i);
            if (when->isOrderSet()) {
                int whenOrder = when->getOrder();
                if (std::find(whenOrders.begin(), whenOrders.end(), whenOrder) != whenOrders.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Reset in component '" + component->getName() +
                                        "' " + orderString +
                                        " " + variableString + variableContinuation +
                                        " has multiple whens with order '" + convertIntToString(whenOrder) + "'.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::RESET_ORDER);
                    mValidator->addError(err);
                } else {
                    whenOrders.push_back(whenOrder);
                }
            }

        }
        /// @cellml2_12 12.1.1.3 Validates all 'when' children
        for (size_t i = 0; i < reset->whenCount(); ++i) {
            WhenPtr when = reset->getWhen(i);
            validateWhen(when, reset, component);
        }
    } else {
        ///@cellml2_12 12.1.1.3 Check there is at least one 'when' child
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() +
                            "' " + orderString +
                            " " + variableString + variableContinuation +
                            " does not have at least one child When.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_CHILD);
        mValidator->addError(err);
    }

    /// @cellml2_12 TODO Need to check whether there is an implied 1-to-1 correspondence between 
    /// the 'when' element(s) and the 'order' integers? If so, does it need to be validated?  Is this specified in 
    /// 13.1.1 When specifications?
}

void Validator::ValidatorImpl::validateWhen(const WhenPtr &when, const ResetPtr &reset, const ComponentPtr &component)
{
    std::string orderString;
    std::string resetOrderString;
    std::string resetVariableString;
    std::string resetVariableContinuation;

    /// @cellml2_13 13.1.1 Check that there is an order attribute specified for input when
    if (when->isOrderSet()) {
        orderString = "with order '" + convertIntToString(when->getOrder()) + "'";
    } else {
        orderString = "does not have an order set,";
    }

    /// @cellml2_12 12.1.1.3 Check that there is an order attribute specified for input reset element
    if (reset->isOrderSet()) {
        resetOrderString = "with order '" + convertIntToString(reset->getOrder()) + "'";
    } else {
        resetOrderString = "which does not have an order set,";
    }

    /// @cellml2_12 12.1.1.1 (?) Check that input reset references a variable
    if (reset->getVariable() == nullptr) {
        resetVariableString = "which does not reference a variable";
        resetVariableContinuation = ",";
    } else {
        resetVariableContinuation = "";
        resetVariableString = "referencing variable '" + reset->getVariable()->getName() + "'";
    }

    /// @cellml2_13 13.1.1 Check that input when has an order  (? checks when->isOrder but returns error
    /// from reset?)
    if (!when->isOrderSet()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString +
                            " " + resetVariableString + resetVariableContinuation +
                            " does not have an order set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_ORDER);
        mValidator->addError(err);
    }

    /// @cellml2_13 13.1.2 13.? Check maths condition of the input component (? Checks component but returns error based on reset?)
    if (when->getCondition().length() > 0) {
        validateMath(when->getCondition(), component);
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString +
                            " " + resetVariableString + resetVariableContinuation +
                            " " + orderString +
                            " does not have a MathML condition set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_CHILD);
        mValidator->addError(err);
    }

    /// @cellml2_13 13.? Check maths value of the input component (? Checks component but returns error based on reset?)
    /// @cellml2_14 14.? Check maths value of the input component (? Checks component but returns error based on reset?)
    if (when->getValue().length() > 0) {
        validateMath(when->getValue(), component);
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString +
                            " " + resetVariableString + resetVariableContinuation +
                            " " + orderString +
                            " does not have a MathML value set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_CHILD);
        mValidator->addError(err);
    }

}

void Validator::ValidatorImpl::validateMath(const std::string &input, const ComponentPtr &component)
{
    /// @cellml2_14 14.1.1 Check input XML is valid for a component
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    // Parse as XML first.
    doc->parse(input);
    // Copy any XML parsing errors into the common validator error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(doc->getXmlError(i));
            err->setKind(Error::Kind::XML);
            mValidator->addError(err);
        }
    }
    XmlNodePtr node = doc->getRootNode();
    /// @cellml2_14 14.1.1 Check input XML is valid MathML with valid root node for input component
    if (!node) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Could not get a valid XML root node from the math on component '" + component->getName() + "'.");
        err->setKind(Error::Kind::XML);
        err->setComponent(component);
        mValidator->addError(err);
        return;
    } else if (!node->isElement("math", MATHML_NS)) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Math root node is of invalid type '" + node->getName() +
                            "' on component '" + component->getName() +
                            "'. A valid math root node should be of type 'math'.");
        err->setComponent(component);
        err->setKind(Error::Kind::XML);
        mValidator->addError(err);
        return;
    }
    XmlNodePtr nodeCopy = node;
    std::vector<std::string> bvarNames;
    std::vector<std::string> variableNames;
    // making a list of unique variable names inside component
    /// @cellml2_14 TODO Should variable names inside a component be validated to prevent duplicates 
    /// instead of removing silently from check list?
    for (size_t i = 0; i < component->variableCount(); ++i) {
        std::string variableName = component->getVariable(i)->getName();
        if (std::find(variableNames.begin(), variableNames.end(), variableName) == variableNames.end()) {
            variableNames.push_back(variableName);
        }
      
    }

    /// @cellml2_14 14.1.3 Check that the variables in the MathML are supported, see hard-coded list at
    /// bool Validator::ValidatorImpl::isSupportedMathMLElement(const XmlNodePtr &node)
    validateMathMLElements(nodeCopy, component);

    // Get the bvar names in this math element.
    // TODO: may want to do this with XPath instead...
    /// @cellml2_14 TODO Change to XPath instead? 
    /// @cellml2_14 14.? Check that there are no duplicates between bound (bvar) and unbound variable names
    gatherMathBvarVariableNames(nodeCopy, bvarNames);
    // Check that no variable names match new bvar names.
    for (std::string &variableName : variableNames) {
        if (std::find(bvarNames.begin(), bvarNames.end(), variableName) != bvarNames.end())
        {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math in component '" + component->getName() +
                                "' contains '" + variableName + "' as a bvar ci element but it is already a variable name.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
    // Iterate through ci/cn elements and remove cellml units attributes.
    XmlNodePtr mathNode = node;
    validateAndCleanMathCiCnNodes(node, component, variableNames, bvarNames);

    /// @cellml2_14 TODO Is there a better way to do this?  Get the MathML string (with cellml:units attributes already removed)
    /// and remove the CellML namespace.  While the removeSubstring() approach for removing the cellml namespace before 
    /// validating with the MathML DTD is not ideal, libxml does not appear to have a better way to remove a namespace 
    /// declaration from the tree.
    std::string cellml2NamespaceString = std::string(" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\"");
    std::string cleanMathml = mathNode->convertToString();
    removeSubstring(cleanMathml, cellml2NamespaceString);

    /// @cellml2_14 14.? Check 'clean/unitless' math string against W3C MathML 
    // Parse/validate the clean math string with the W3C MathML DTD.
    XmlDocPtr mathmlDoc = std::make_shared<XmlDoc>();
    mathmlDoc->parseMathML(cleanMathml);
    // Copy any MathML validation errors into the common validator error handler.
    if (mathmlDoc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < mathmlDoc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(mathmlDoc->getXmlError(i));
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
}

void Validator::ValidatorImpl::validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames,
                                                             const std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->getFirstChild();
    std::string textNode;
    bool ciType = node->isElement("ci", MATHML_NS);
    bool cnType = node->isElement("cn", MATHML_NS);
    if (ciType || cnType) {
        if (childNode) {
            if (childNode->isText()) {
                textNode = childNode->convertToString();
                if (hasNonWhitespaceCharacters(textNode)) {
                    /// @cellml2_14 14.1.3 Check that ci elements reference a variable or bound variable within the same container
                    if (ciType) {
                        // It's fine in MathML to have whitespace around variable names, we will strip it out when looking for
                        // variable names.
                        textNode.erase(textNode.begin(),find_if_not(textNode.begin(),textNode.end(),[](int c){return isspace(c);}));
                        textNode.erase(find_if_not(textNode.rbegin(),textNode.rend(),[](int c){return isspace(c);}).base(), textNode.end());
                        // Check whether we can find this text as a variable name in this component.
                        if ((std::find(variableNames.begin(), variableNames.end(), textNode) == variableNames.end()) &&
                            (std::find(bvarNames.begin(), bvarNames.end(), textNode) == bvarNames.end())) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("MathML ci element has the child text '" + textNode +
                                                "', which does not correspond with any variable names present in component '" + component->getName() +
                                                "' and is not a variable defined within a bvar element.");
                            err->setComponent(component);
                            err->setKind(Error::Kind::MATHML);
                            mValidator->addError(err);
                        }
                    }
                } else {
                    /// @cellml2_14 14.? Check that names of children are not whitespace only TODO Checking whether this needs to be explicit in specs
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("MathML " + node->getName() + " element has a whitespace-only child element.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        } else {
            /// @cellml2_14 14.1.3 Check that element has a child, whether or not it is ci or cn
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("MathML " + node->getName() + " element has no child.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        // Get cellml:units attribute.
        XmlAttributePtr attribute = node->getFirstAttribute();
        std::string unitsName;
        XmlAttributePtr unitsAttribute = nullptr;
        while (attribute) {
            if (attribute->getValue().length() > 0) {
                /// @cellml2_14 14.1.4 Check for units in both cn and ci types and compares to CellML namespace  

                if (attribute->isType("units", CELLML_2_0_NS)) {
                    unitsName = attribute->getValue();
                    unitsAttribute = attribute;
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Math " + node->getName() + " element has an invalid attribute type '" +
                                        attribute->getName() + "' in the cellml namespace.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
            attribute = attribute->getNext();
        }

        bool checkUnitsIsInComponent = false;
        // Check that cellml:units has been set.
        /// @cellml2_14 14.1.3 Check that ci element does not have units TODO Check that this is clear in specification doc
        if (ciType) {
            if (unitsAttribute != nullptr) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Math ci element with value '" + textNode +
                                    "' has a cellml:units attribute with name '" + unitsAttribute->getValue() + "'.");
            }
        } else if (cnType) {
            /// @cellml2_14 14.1.4 Check that cn elements has a units name
            if (isCellmlIdentifier(unitsName)) {
                checkUnitsIsInComponent = true;
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Math cn element with the value '" + textNode +
                                    "' does not have a valid cellml:units attribute.");
                err->setComponent(component);
                err->setKind(Error::Kind::MATHML);
                mValidator->addError(err);
            }
        }

        // Check that a specified units is valid.
        /// @cellml2_14  14.1.4 Check that the units exist, either locally in the component or the standard list
        if (checkUnitsIsInComponent) {
            // Check for a matching units in this component.
            Model* model = static_cast<Model*>(component->getParent());
            if (!model->hasUnits(unitsName)) {
                // Check for a matching standard units.
                if (!isStandardUnitName(unitsName)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Math has a " + node->getName() + " element with a cellml:units attribute '" + unitsName +
                                        "' that is not a valid reference to units in component '" +
                                        component->getName() + "' or a standard unit.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        }
        // Now that we've validated this XML node's cellml:units attribute, remove it from the node.
        // This is done so we can validate a "clean" MathML string using the MathML DTD. The math
        // string stored on the component will not be affected.
        if (unitsAttribute) {
            unitsAttribute->removeAttribute();
        }
    } else {
        // Check children for ci/cn elements.
        if (childNode) {
            validateAndCleanMathCiCnNodes(childNode, component, variableNames, bvarNames);
        }
    }
    // Check siblings for ci/cn.
    node = node->getNext();
    if (node) {
        validateAndCleanMathCiCnNodes(node, component, variableNames, bvarNames);
    }
}

void Validator::ValidatorImpl::validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component)
{

    /// @cellml2_14 14.1.2 Check that each child of a math element is supported, recursive over own children
    XmlNodePtr childNode = node->getFirstChild();
    if (childNode) {
        if (!childNode->isText() && !isSupportedMathMLElement(childNode)) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math has a '" + childNode->getName() + "' element" +
                                " that is not a supported MathML element.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        validateMathMLElements(childNode, component);
    }

    XmlNodePtr nextNode = node->getNext();
    if (nextNode) {
        if (!nextNode->isText() && !isSupportedMathMLElement(nextNode)) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math has a '" + nextNode->getName() + "' element" +
                                " that is not a supported MathML element.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        validateMathMLElements(nextNode, component);
    }
}

void Validator::ValidatorImpl::gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->getFirstChild();
    if (node->isElement("bvar", MATHML_NS)) {
        if ((childNode) && (childNode->isElement("ci", MATHML_NS))) {
            XmlNodePtr grandchildNode = childNode->getFirstChild();
            if (grandchildNode) {
                if (grandchildNode->isText()) {
                    std::string textNode = grandchildNode->convertToString();
                    if (hasNonWhitespaceCharacters(textNode)) {
                        bvarNames.push_back(textNode);
                    }
                }
            }
        }
    } else {
        // Check children for bvars.
        if (childNode) {
            gatherMathBvarVariableNames(childNode, bvarNames);
        }
    }
    // Check siblings for bvars.
    node = node->getNext();
    if (node) {
        gatherMathBvarVariableNames(node, bvarNames);
    }
}

void Validator::ValidatorImpl::validateConnections(const ModelPtr &model)
{
    /// @cellml2_17 TODO need checks of 17.1.1-4 as not present here?
    std::string hints;
    std::vector<std::string> hintlist;

    // Check the components in this model.
    if (model->componentCount() > 0) {
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);

            // Check the variables in this component.
            for (size_t j = 0; j < component->variableCount(); ++j) {
                VariablePtr variable = component->getVariable(j);

                // Check the equivalent variables in this variable.
                if (variable->equivalentVariableCount() > 0) {
                    for (size_t k = 0; k < variable->equivalentVariableCount(); ++k) {
                        VariablePtr equivalentVariable = variable->getEquivalentVariable(k);

                        /// @cellml2_17 17.1.2 Check that we do not have a variable equivalent to itself
                        if (variable == equivalentVariable) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Variable '" + variable->getName() +
                                                "' has an equivalent variable '" + equivalentVariable->getName() +
                                                "' equal to itself. "
                            );
                            err->setModel(model);
                            err->setKind(Error::Kind::CONNECTION);
                            mValidator->addError(err);
                        }
                        // TODO: validate variable interfaces according to 19.10.8
                        /// @cellml2_17 TODO Validate variable interfaces according to 19.10.8
                        /// @cellml2_19 19.10.6 Validate that equivalent varaible pairs have equivalent units
                        if (!unitsAreEquivalent(model, variable, equivalentVariable, hints)) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Variable '" + variable->getName() +
                                "' has units of '" + variable->getUnits() +
                                "' and an equivalent variable '" + equivalentVariable->getName() +
                                "' with non-matching units of '" + equivalentVariable->getUnits() +
                                "'. The mismatch is: " + hints
                            );
                            err->setModel(model);
                            err->setKind(Error::Kind::UNITS);
                            mValidator->addError(err);
                        }

                        /// @cellml2_18 18.1.3 Don't need to check that connections do not duplicate variable pairs (19.10.4)
                        /// as duplicates are not stored (?).

                        if (equivalentVariable->hasEquivalentVariable(variable)) {
                            // Check that the equivalent variable has a valid parent component.
                            Component* component2 = static_cast<Component*>(equivalentVariable->getParent());
                            if (!component2->hasVariable(equivalentVariable)) {
                                ErrorPtr err = std::make_shared<Error>();
                                err->setDescription("Variable '" + equivalentVariable->getName() +
                                    "' is an equivalent variable to '" + variable->getName() +
                                    "' but has no parent component.");
                                err->setModel(model);
                                err->setKind(Error::Kind::CONNECTION);
                                mValidator->addError(err);
                            }
                        }
                        else {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Variable '" + variable->getName() +
                                "' has an equivalent variable '" + equivalentVariable->getName() +
                                "'  which does not reciprocally have '" + variable->getName() +
                                "' set as an equivalent variable.");
                            err->setModel(model);
                            err->setKind(Error::Kind::CONNECTION);
                            mValidator->addError(err);
                        }
                    }
                }
            }
        }
         /// @cellml2_19 19.10.5 Check that the variable equivalence network does not contain cycles
         if (!isModelVariableCycleFree(model, hintlist)) {
            ErrorPtr err = std::make_shared<Error>();
            std::string des;
            std::string loops;
            loops = hintlist.size() > 1 ? " loops" : " loop";
            for (auto s : hintlist) {
                des += s;
            }
            err->setDescription("Cyclic variables exist, " + std::to_string(hintlist.size())+loops+" found (Component, Variable):\n"+des);
            err->setModel(model);
            err->setKind(Error::Kind::VARIABLE);
            mValidator->addError(err);
        }
    }
}

bool Validator::ValidatorImpl::isModelVariableCycleFree(const ModelPtr &model, std::vector<std::string> &hintlist) {

    bool found = false;
    std::deque<libcellml::VariablePtr> check_list = {};
    std::vector<std::deque<libcellml::VariablePtr>> total_list = {};

    if (model->componentCount() > 0) {
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);

            for (size_t j = 0; j < component->variableCount(); ++j) {
                VariablePtr variable = component->getVariable(j);

                if (variable->equivalentVariableCount() < 2)
                    continue;

                for (size_t k = 0; k < variable->equivalentVariableCount(); ++k) {

                    std::deque<libcellml::VariablePtr>().swap(check_list);
                    check_list.push_back(variable);

                    VariablePtr eq = variable->getEquivalentVariable(k);

                    if (cycleVariableFound(variable, eq, check_list)) {
                        total_list.push_back(check_list);
                        found = true;
                    }
                }
            }
        }
    }
    if (found) {
        // Only report the loops which start with the lowest alphabetical variable name to reduce duplicate reporting 
        for (auto list : total_list) {
            std::string min = list.front()->getName();
            bool use_me = true;
            for (auto var : list) {
                if (min.compare(var->getName()) > 0) {
                    use_me = false;
                    break;
                }
            }
            if (use_me) {
                std::string description = "";
                std::string reverse_description = "";
                std::string separator = "";

                for (VariablePtr v : list) {
                    Component* parent = static_cast<Component*>(v->getParent());
                    description += separator + "('" + parent->getName() + "', '" + v->getName() + "')";
                    reverse_description = "('" + parent->getName() + "', '" + v->getName() + "')" + separator + reverse_description;
                    separator = " -> ";
                }
                description += "\n";
                reverse_description += "\n";

                if ((std::find(hintlist.begin(), hintlist.end(), description) == hintlist.end()) 
                    && (std::find(hintlist.begin(), hintlist.end(), reverse_description) == hintlist.end())) {
                    hintlist.push_back(description);
                }
            }
        }
    }
    return (!found);
}

bool Validator::ValidatorImpl::cycleVariableFound(VariablePtr &parent, VariablePtr &child, std::deque<libcellml::VariablePtr> &check_list) {

    if(std::find(check_list.begin(), check_list.end(), child) != check_list.end()) {
        check_list.push_back(child);
        // Removing items from the start of the loop to avoid lasso shapes
        while (check_list.front() != check_list.back()) {
            check_list.pop_front();
        }
        return true;
    }
    else {
        check_list.push_back(child);
        for (size_t k = 0; k < child->equivalentVariableCount(); ++k) {
            VariablePtr eq = child->getEquivalentVariable(k);
            if (eq == parent) {
                continue;
            }
            if (cycleVariableFound(child, eq, check_list)) {
                return true;
            }
        }
    }
    return false;
}

bool Validator::ValidatorImpl::unitsAreEquivalent(const ModelPtr &model, 
    const VariablePtr &v1, const VariablePtr &v2, std::string &hints) 
{

    bool status;
    double multmap = 0.0;
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr mu = std::make_shared<libcellml::Units>();
    std::map<std::string, double> unitmap = {};

    for (std::vector<std::string>::const_iterator pos = baseUnitsList.begin(); pos != baseUnitsList.end(); ++pos) {
        unitmap[*pos] = 0.0;
    }

    std::string myRef, myPre, myId;
    std::map<std::string, double> myBase;
    hints = "";
    
    if (model->hasUnits(v1->getUnits())) {  
        u1 = model->getUnits(v1->getUnits());
        incrementBaseUnitCount(model, unitmap, multmap, u1->getName(),1, 0);
    }
    else if (unitmap.find(v1->getUnits()) != unitmap.end() ) {  
        myRef = v1->getUnits();
        unitmap.at(myRef) += 1.0;
    }
    else if (isStandardUnitName(v1->getUnits())) {
        incrementBaseUnitCount(model, unitmap, multmap, v1->getUnits(), 1, 0);
    }

    if ( model->hasUnits(v2->getUnits())) {
        u2 = model->getUnits(v2->getUnits());
        decrementBaseUnitCount(model, unitmap, multmap, u2->getName(),  1, 0);
    }
    else if (unitmap.find(v2->getUnits()) != unitmap.end() ) {  
        myRef = v2->getUnits();
        unitmap.at(v2->getUnits()) -= 1.0;
    }
    else if (isStandardUnitName(v2->getUnits())) {
        decrementBaseUnitCount(model, unitmap, multmap, v2->getUnits(), 1, 0);
    }

    // Remove "dimensionless" from base unit testing 
    unitmap.erase("dimensionless");

    status = true;
    for (const auto &basepair : unitmap) {
        if (basepair.second != 0.0) {
            std::string num = std::to_string(basepair.second);
            num.erase(num.find_last_not_of("0")+1,num.length());
            if (num.back() == '.') 
                num.pop_back();
            hints += basepair.first + "^" + num + ", ";
            status = false;
        }
    }
    if (multmap != 0.0) {
        std::string num = std::to_string(multmap);
        num.erase(num.find_last_not_of("0")+1,num.length());
        if (num.back() == '.') 
            num.pop_back();
        hints += "multiplication factor of 10^" + num + ", ";
        status = false;
    }

    return status;
}

void Validator::ValidatorImpl::incrementBaseUnitCount(const ModelPtr &model,
                                                      std::map<std::string,double> &unitmap, 
                                                      double &multmap,
                                                      const std::string uName, 
                                                      const double uExp,
                                                      const double logMult) { 
    std::string myRef, myPre, myId;
    double myExp, myMult, m;
    std::map<std::string, double> myBase;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr uRef = std::make_shared<libcellml::Units>();

    if (model->hasUnits(uName)) {
        u = model->getUnits(uName);
        if (!u->isBaseUnit()) {
            for (size_t i = 0; i < u->unitCount(); ++i) {
                u->getUnitAttributes(i, myRef, myPre, myExp, m, myId);
                myMult = std::log10(m);
                if (!isStandardUnitName(myRef))
                    incrementBaseUnitCount(model, unitmap, multmap, myRef,
                                           uExp*myExp,  // effective exponent
                                           logMult + myMult*uExp + standardPrefixList.at(myPre)*uExp); // effective multiplier
                else {
                    myBase = standardUnitsList.at(myRef);
                    for (const auto &iter : myBase) {
                        unitmap.at(iter.first) += iter.second*myExp*uExp;
                    }
                    multmap += logMult + (
                            standardMultiplierList.at(myRef) + 
                            myMult + 
                            standardPrefixList.at(myPre)
                        )*uExp;
                }
            }
        } else if (unitmap.find(uName) == unitmap.end()) {
            // Empty unit, add to base list
            unitmap.emplace(std::pair<std::string, double>(uName, uExp));
            multmap += logMult;
        }
    } 
    else if (isStandardUnitName(uName)) {
        myBase = standardUnitsList.at(uName);
        for (const auto &iter : myBase) {
            unitmap.at(iter.first) += iter.second*uExp;
        }   
        multmap += logMult + standardMultiplierList.at(uName);
    }
}

void Validator::ValidatorImpl::decrementBaseUnitCount(const ModelPtr &model,
                                                      std::map<std::string,double> &unitmap, 
                                                      double &multmap,
                                                      const std::string uName, 
                                                      const double uExp,
                                                      const double logMult) {

    std::string myRef, myPre, myId;
    double myExp, myMult, m;
    std::map<std::string, double> myBase;
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    if (model->hasUnits(uName)) {
        u = model->getUnits(uName);

        if (!u->isBaseUnit()) {
            for (size_t i = 0; i < u->unitCount(); ++i) {
                u->getUnitAttributes(i, myRef, myPre, myExp, m, myId);
                myMult = std::log10(m);
                if (!isStandardUnitName(myRef))
                    decrementBaseUnitCount(model, unitmap, multmap, myRef, 
                                           myExp*uExp,
                                           logMult + myMult*uExp + standardPrefixList.at(myPre)*uExp); // effective multiplier
                else {
                    myBase = standardUnitsList.at(myRef);
                    for (const auto &iter : myBase) {
                        unitmap.at(iter.first) -= iter.second*myExp*uExp;
                    }
                    multmap -= logMult + (
                        standardMultiplierList.at(myRef) + 
                        myMult + 
                        standardPrefixList.at(myPre)
                        )*uExp;
                }
            } 
        } else if (unitmap.find(uName) == unitmap.end()) { 
            unitmap.emplace(std::pair<std::string, double>(uName, -1.0*uExp));
            multmap -= logMult;
        }
    }
    else if (isStandardUnitName(uName)) {
        myBase = standardUnitsList.at(uName);
        for (const auto &iter : myBase) {
            unitmap.at(iter.first) -= iter.second*uExp;
        }
        multmap -= logMult + standardMultiplierList.at(uName);     
    }  
}

void Validator::ValidatorImpl::removeSubstring(std::string &input, std::string &pattern) {
  std::string::size_type n = pattern.length();
  for (std::string::size_type i = input.find(pattern);
      i != std::string::npos;
      i = input.find(pattern))
      input.erase(i, n);
}

bool Validator::ValidatorImpl::isSupportedMathMLElement(const XmlNodePtr &node)
{
    /// @cellml2_14 14.1.2 Lists the hard-coded supported MathML elements tags
    return    !node->getNamespace().compare(MATHML_NS)
           && std::find(supportedMathMLElements.begin(), supportedMathMLElements.end(), node->getName()) != supportedMathMLElements.end();
}

bool Validator::ValidatorImpl::isStandardUnitName(const std::string &name)
{
    bool result = false;
    if (standardUnitsList.count(name) != 0) {
        result = true;
    }
    return result;
}

bool Validator::ValidatorImpl::isStandardPrefixName(const std::string &name)
{
    bool result = false;
    if (standardPrefixList.count(name) != 0) {
        result = true;
    }
    return result;
}

bool Validator::ValidatorImpl::isCellmlIdentifier(const std::string &name)
{
    bool result = true;
    /// @cellml2_3 3.1.3 Check that length of a name is greater than 0
    if (name.length() > 0) {
        /// @cellml2_3 3.1.4 Check that name does not start with a numeric character.
        if (isdigit(name[0])) {
            result = false;
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("CellML identifiers must not begin with a European numeric character [0-9].");
            err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
            mValidator->addError(err);
        } else {
            /// @cellml2_3 3.1.2 Check that name consists of Basic Latin alphanumeric characters and underscores only.
            if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos) {
                result = false;
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("CellML identifiers must not contain any characters other than [a-zA-Z0-9_].");
                err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
                mValidator->addError(err);
            }
        }
    } else {
        result = false;
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("CellML identifiers must contain one or more basic Latin alphabetic characters.");
        err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
        mValidator->addError(err);
    }
    return result;
}

}


