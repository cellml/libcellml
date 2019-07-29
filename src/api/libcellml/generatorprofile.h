/*
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

#pragma once

#include "libcellml/exportdefinitions.h"

namespace libcellml {

class LIBCELLML_EXPORT GeneratorProfile
{
public:
    enum class Profile
    {
        C,
        PYTHON,
    };

    explicit GeneratorProfile(Profile profile = Profile::C); /**< Constructor */
    ~GeneratorProfile(); /**< Destructor */
    GeneratorProfile(const GeneratorProfile &rhs); /**< Copy constructor */
    GeneratorProfile(GeneratorProfile &&rhs) noexcept; /**< Move constructor */
    GeneratorProfile &operator=(GeneratorProfile rhs); /**< Assignment operator */

    /**
     * @brief Set the @c Profile.
     *
     * Set this @c GeneratorProfile to the given @c Profile .
     *
     * @param profile The @c Profile to use.
     */
    void setProfile(Profile profile);

    // Relational and logical operators

    /**
     * @brief Get the @c std::string for the assignment operator.
     *
     * Return the @c std::string for the assignment operator.
     *
     * @return The @c std::string for the assignment operator.
     */
    std::string eqString() const;
    /**
     * @brief Set the @c std::string for the assignment operator.
     *
     * Set this @c std::string for the assignment operator.
     *
     * @param eqString The @c std::string to use for the assignment operator.
     */
    void setEqString(const std::string &eqString);

    /**
     * @brief Get the @c std::string for the == relational operator.
     *
     * Return the @c std::string for the == relational operator.
     *
     * @return The @c std::string for the == relational operator.
     */
    std::string eqEqString() const;
    /**
     * @brief Set the @c std::string for the == relational operator.
     *
     * Set this @c std::string for the == relational operator.
     *
     * @param eqString The @c std::string to use for the == relational operator.
     */
    void setEqEqString(const std::string &eqEqString);

    /**
     * @brief Get the @c std::string for the != relational operator.
     *
     * Return the @c std::string for the != relational operator.
     *
     * @return The @c std::string for the != relational operator.
     */
    std::string neqString() const;
    /**
     * @brief Set the @c std::string for the != relational operator.
     *
     * Set this @c std::string for the != relational operator.
     *
     * @param eqString The @c std::string to use for the != relational operator.
     */
    void setNeqString(const std::string &neqString);

    /**
     * @brief Get the @c std::string for the < relational operator.
     *
     * Return the @c std::string for the < relational operator.
     *
     * @return The @c std::string for the < relational operator.
     */
    std::string ltString() const;
    /**
     * @brief Set the @c std::string for the < relational operator.
     *
     * Set this @c std::string for the < relational operator.
     *
     * @param eqString The @c std::string to use for the < relational operator.
     */
    void setLtString(const std::string &ltString);

    /**
     * @brief Get the @c std::string for the <= relational operator.
     *
     * Return the @c std::string for the <= relational operator.
     *
     * @return The @c std::string for the <= relational operator.
     */
    std::string leqString() const;
    /**
     * @brief Set the @c std::string for the <= relational operator.
     *
     * Set this @c std::string for the <= relational operator.
     *
     * @param eqString The @c std::string to use for the <= relational operator.
     */
    void setLeqString(const std::string &leqString);

    /**
     * @brief Get the @c std::string for the > relational operator.
     *
     * Return the @c std::string for the > relational operator.
     *
     * @return The @c std::string for the > relational operator.
     */
    std::string gtString() const;
    /**
     * @brief Set the @c std::string for the > relational operator.
     *
     * Set this @c std::string for the > relational operator.
     *
     * @param eqString The @c std::string to use for the > relational operator.
     */
    void setGtString(const std::string &gtString);

    /**
     * @brief Get the @c std::string for the >= relational operator.
     *
     * Return the @c std::string for the >= relational operator.
     *
     * @return The @c std::string for the >= relational operator.
     */
    std::string geqString() const;
    /**
     * @brief Set the @c std::string for the >= relational operator.
     *
     * Set this @c std::string for the >= relational operator.
     *
     * @param eqString The @c std::string to use for the >= relational operator.
     */
    void setGeqString(const std::string &geqString);

    /**
     * @brief Get the @c std::string for the and logical operator.
     *
     * Return the @c std::string for the and logical operator.
     *
     * @return The @c std::string for the and logical operator.
     */
    std::string andString() const;
    /**
     * @brief Set the @c std::string for the and logical operator.
     *
     * Set this @c std::string for the and logical operator.
     *
     * @param eqString The @c std::string to use for the and logical operator.
     */
    void setAndString(const std::string &andString);

    /**
     * @brief Get the @c std::string for the or logical operator.
     *
     * Return the @c std::string for the or logical operator.
     *
     * @return The @c std::string for the or logical operator.
     */
    std::string orString() const;
    /**
     * @brief Set the @c std::string for the or logical operator.
     *
     * Set this @c std::string for the or logical operator.
     *
     * @param eqString The @c std::string to use for the or logical operator.
     */
    void setOrString(const std::string &orString);

    /**
     * @brief Get the @c std::string for the xor logical operator.
     *
     * Return the @c std::string for the xor logical operator.
     *
     * @return The @c std::string for the xor logical operator.
     */
    std::string xorString() const;
    /**
     * @brief Set the @c std::string for the xor logical operator.
     *
     * Set this @c std::string for the xor logical operator.
     *
     * @param eqString The @c std::string to use for the xor logical operator.
     */
    void setXorString(const std::string &xorString);

    /**
     * @brief Get the @c std::string for the not logical operator.
     *
     * Return the @c std::string for the not logical operator.
     *
     * @return The @c std::string for the not logical operator.
     */
    std::string notString() const;
    /**
     * @brief Set the @c std::string for the not logical operator.
     *
     * Set this @c std::string for the not logical operator.
     *
     * @param eqString The @c std::string to use for the not logical operator.
     */
    void setNotString(const std::string &notString);

    bool hasEqEqOperator() const;
    void setHasEqEqOperator(bool hasEqEqOperator);

    bool hasNeqOperator() const;
    void setHasNeqOperator(bool hasNeqOperator);

    bool hasLtOperator() const;
    void setHasLtOperator(bool hasLtOperator);

    bool hasLeqOperator() const;
    void setHasLeqOperator(bool hasLeqOperator);

    bool hasGtOperator() const;
    void setHasGtOperator(bool hasGtOperator);

    bool hasGeqOperator() const;
    void setHasGeqOperator(bool hasGeqOperator);

    bool hasAndOperator() const;
    void setHasAndOperator(bool hasAndOperator);

    bool hasOrOperator() const;
    void setHasOrOperator(bool hasOrOperator);

    bool hasXorOperator() const;
    void setHasXorOperator(bool hasXorOperator);

    bool hasNotOperator() const;
    void setHasNotOperator(bool hasNotOperator);

    // Arithmetic operators

    std::string plusString() const;
    void setPlusString(const std::string &plusString);

    std::string minusString() const;
    void setMinusString(const std::string &minusString);

    std::string timesString() const;
    void setTimesString(const std::string &timesString);

    std::string divideString() const;
    void setDivideString(const std::string &divideString);

    std::string powerString() const;
    void setPowerString(const std::string &powerString);

    std::string squareRootString() const;
    void setSquareRootString(const std::string &squareRootString);

    std::string squareString() const;
    void setSquareString(const std::string &squareString);

    std::string absoluteValueString() const;
    void setAbsoluteValueString(const std::string &absoluteValueString);

    std::string exponentialString() const;
    void setExponentialString(const std::string &exponentialString);

    std::string napierianLogarithmString() const;
    void setNapierianLogarithmString(const std::string &napierianLogarithmString);

    std::string commonLogarithmString() const;
    void setCommonLogarithmString(const std::string &commonLogarithmString);

    std::string ceilingString() const;
    void setCeilingString(const std::string &ceilingString);

    std::string floorString() const;
    void setFloorString(const std::string &floorString);

    std::string minString() const;
    void setMinString(const std::string &minString);

    std::string maxString() const;
    void setMaxString(const std::string &maxString);

    std::string remString() const;
    void setRemString(const std::string &remString);

    bool hasPowerOperator() const;
    void setHasPowerOperator(bool hasPowerOperator);

    // Trigonometric operators

    std::string sinString() const;
    void setSinString(const std::string &sinString);

    std::string cosString() const;
    void setCosString(const std::string &cosString);

    std::string tanString() const;
    void setTanString(const std::string &tanString);

    std::string secString() const;
    void setSecString(const std::string &secString);

    std::string cscString() const;
    void setCscString(const std::string &cscString);

    std::string cotString() const;
    void setCotString(const std::string &cotString);

    std::string sinhString() const;
    void setSinhString(const std::string &sinhString);

    std::string coshString() const;
    void setCoshString(const std::string &coshString);

    std::string tanhString() const;
    void setTanhString(const std::string &tanhString);

    std::string sechString() const;
    void setSechString(const std::string &sechString);

    std::string cschString() const;
    void setCschString(const std::string &cschString);

    std::string cothString() const;
    void setCothString(const std::string &cothString);

    std::string asinString() const;
    void setAsinString(const std::string &asinString);

    std::string acosString() const;
    void setAcosString(const std::string &acosString);

    std::string atanString() const;
    void setAtanString(const std::string &atanString);

    std::string asecString() const;
    void setAsecString(const std::string &asecString);

    std::string acscString() const;
    void setAcscString(const std::string &acscString);

    std::string acotString() const;
    void setAcotString(const std::string &acotString);

    std::string asinhString() const;
    void setAsinhString(const std::string &asinhString);

    std::string acoshString() const;
    void setAcoshString(const std::string &acoshString);

    std::string atanhString() const;
    void setAtanhString(const std::string &atanhString);

    std::string asechString() const;
    void setAsechString(const std::string &asechString);

    std::string acschString() const;
    void setAcschString(const std::string &acschString);

    std::string acothString() const;
    void setAcothString(const std::string &acothString);

    // Piecewise statement
    // Note: the parentheses around #cond is not needed (because of precedence
    //       rules). It's just that it looks better/clearer to have them
    //       (somewhat subjective indeed).

    std::string conditionalOperatorIfString() const;
    void setConditionalOperatorIfString(const std::string &conditionalOperatorIfString);

    std::string conditionalOperatorElseString() const;
    void setConditionalOperatorElseString(const std::string &conditionalOperatorElseString);

    std::string piecewiseIfString() const;
    void setPiecewiseIfString(const std::string &piecewiseIfString);

    std::string piecewiseElseString() const;
    void setPiecewiseElseString(const std::string &piecewiseElseString);

    bool hasConditionalOperator() const;
    void setHasConditionalOperator(bool hasConditionalOperator);

    // Constants

    std::string trueString() const;
    void setTrueString(const std::string &trueString);

    std::string falseString() const;
    void setFalseString(const std::string &falseString);

    std::string eString() const;
    void setEString(const std::string &eString);

    std::string piString() const;
    void setPiString(const std::string &piString);

    std::string infString() const;
    void setInfString(const std::string &infString);

    std::string nanString() const;
    void setNanString(const std::string &nanString);

    // Mathematical functions

    std::string eqEqFunctionString() const;
    void setEqEqFunctionString(const std::string &eqEqFunctionString);
    std::string neqFunctionString() const;
    void setNeqFunctionString(const std::string &neqFunctionString);
    std::string ltFunctionString() const;
    void setLtFunctionString(const std::string &ltFunctionString);
    std::string leqFunctionString() const;
    void setLeqFunctionString(const std::string &leqFunctionString);
    std::string gtFunctionString() const;
    void setGtFunctionString(const std::string &gtFunctionString);
    std::string geqFunctionString() const;
    void setGeqFunctionString(const std::string &geqFunctionString);
    std::string andFunctionString() const;
    void setAndFunctionString(const std::string &andFunctionString);
    std::string orFunctionString() const;
    void setOrFunctionString(const std::string &orFunctionString);
    std::string xorFunctionString() const;
    void setXorFunctionString(const std::string &xorFunctionString);
    std::string notFunctionString() const;
    void setNotFunctionString(const std::string &notFunctionString);

    std::string minFunctionString() const;
    void setMinFunctionString(const std::string &minFunctionString);
    std::string maxFunctionString() const;
    void setMaxFunctionString(const std::string &maxFunctionString);

    std::string secFunctionString() const;
    void setSecFunctionString(const std::string &secFunctionString);
    std::string cscFunctionString() const;
    void setCscFunctionString(const std::string &cscFunctionString);
    std::string cotFunctionString() const;
    void setCotFunctionString(const std::string &cotFunctionString);
    std::string sechFunctionString() const;
    void setSechFunctionString(const std::string &sechFunctionString);
    std::string cschFunctionString() const;
    void setCschFunctionString(const std::string &cschFunctionString);
    std::string cothFunctionString() const;
    void setCothFunctionString(const std::string &cothFunctionString);
    std::string asecFunctionString() const;
    void setAsecFunctionString(const std::string &asecFunctionString);
    std::string acscFunctionString() const;
    void setAcscFunctionString(const std::string &acscFunctionString);
    std::string acotFunctionString() const;
    void setAcotFunctionString(const std::string &acotFunctionString);
    std::string asechFunctionString() const;
    void setAsechFunctionString(const std::string &asechFunctionString);
    std::string acschFunctionString() const;
    void setAcschFunctionString(const std::string &acschFunctionString);
    std::string acothFunctionString() const;
    void setAcothFunctionString(const std::string &acothFunctionString);

    // Miscellaneous

    std::string headerString() const;
    void setHeaderString(const std::string &headerString);

    std::string variableOfIntegrationString() const;
    void setVariableOfIntegrationString(const std::string &variableOfIntegrationString);

    std::string statesArrayString() const;
    void setStatesArrayString(const std::string &statesArrayString);

    std::string ratesArrayString() const;
    void setRatesArrayString(const std::string &ratesArrayString);

    std::string variablesArrayString() const;
    void setVariablesArrayString(const std::string &variablesArrayString);

    std::string beginInitializeConstantsMethodString() const;
    void setBeginInitializeConstantsMethodString(const std::string &beginInitializeConstantsMethodString);

    std::string endInitializeConstantsMethodString() const;
    void setEndInitializeConstantsMethodString(const std::string &endInitializeConstantsMethodString);

    std::string beginComputeComputedConstantsMethodString() const;
    void setBeginComputeComputedConstantsMethodString(const std::string &beginComputeComputedConstantsMethodString);

    std::string endComputeComputedConstantsMethodString() const;
    void setEndComputeComputedConstantsMethodString(const std::string &endComputeComputedConstantsMethodString);

    std::string beginComputeRatesMethodString() const;
    void setBeginComputeRatesMethodString(const std::string &beginComputeRatesMethodString);

    std::string endComputeRatesMethodString() const;
    void setEndComputeRatesMethodString(const std::string &endComputeRatesMethodString);

    std::string beginComputeVariablesMethodString() const;
    void setBeginComputeVariablesMethodString(const std::string &beginComputeVariablesMethodString);

    std::string endComputeVariablesMethodString() const;
    void setEndComputeVariablesMethodString(const std::string &endComputeVariablesMethodString);

    std::string emptyMethodString() const;
    void setEmptyMethodString(const std::string &emptyMethodString);

    std::string indentString() const;
    void setIndentString(const std::string &indentString);

    std::string openArrayString() const;
    void setOpenArrayString(const std::string &openArrayString);

    std::string closeArrayString() const;
    void setCloseArrayString(const std::string &closeArrayString);

    std::string commandSeparatorString() const;
    void setCommandSeparatorString(const std::string &commandSeparatorString);

private:
    void swap(GeneratorProfile &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorProfileImpl;
    GeneratorProfileImpl *mPimpl;
};

} // namespace libcellml
