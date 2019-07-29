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
     * @brief Get the @c std::string for an assignment.
     *
     * Return the @c std::string for an assignment.
     *
     * @return The @c std::string for an assignment.
     */
    std::string eqString() const;
    /**
     * @brief Set the @c std::string for an assignment.
     *
     * Set this @c std::string for an assignment.
     *
     * @param eqString The @c std::string to use for an assignment.
     */
    void setEqString(const std::string &eqString);

    /**
     * @brief Get the @c std::string for an equivalence.
     *
     * Return the @c std::string for an equivalence.
     *
     * @return The @c std::string for an equivalence.
     */
    std::string eqEqString() const;
    /**
     * @brief Set the @c std::string for an equivalence.
     *
     * Set this @c std::string for an equivalence.
     *
     * @param eqString The @c std::string to use for an equivalence.
     */
    void setEqEqString(const std::string &eqEqString);

    /**
     * @brief Get the @c std::string for a nonequivalence.
     *
     * Return the @c std::string for a nonequivalence.
     *
     * @return The @c std::string for a nonequivalence.
     */
    std::string neqString() const;
    /**
     * @brief Set the @c std::string for a nonequivalence.
     *
     * Set this @c std::string for a nonequivalence.
     *
     * @param eqString The @c std::string to use for a nonequivalence.
     */
    void setNeqString(const std::string &neqString);

    /**
     * @brief Get the @c std::string for lower than.
     *
     * Return the @c std::string for lower than.
     *
     * @return The @c std::string for lower than.
     */
    std::string ltString() const;
    /**
     * @brief Set the @c std::string for lower than.
     *
     * Set this @c std::string for lower than.
     *
     * @param eqString The @c std::string to use for lower than.
     */
    void setLtString(const std::string &ltString);

    /**
     * @brief Get the @c std::string for lower or equal than.
     *
     * Return the @c std::string for lower or equal than.
     *
     * @return The @c std::string for lower or equal than.
     */
    std::string leqString() const;
    /**
     * @brief Set the @c std::string for lower or equal than.
     *
     * Set this @c std::string for lower or equal than.
     *
     * @param eqString The @c std::string to use for lower or equal than.
     */
    void setLeqString(const std::string &leqString);

    /**
     * @brief Get the @c std::string for greater than.
     *
     * Return the @c std::string for greater than.
     *
     * @return The @c std::string for greater than.
     */
    std::string gtString() const;
    /**
     * @brief Set the @c std::string for greater than.
     *
     * Set this @c std::string for greater than.
     *
     * @param eqString The @c std::string to use for greater than.
     */
    void setGtString(const std::string &gtString);

    /**
     * @brief Get the @c std::string for greater or equal than.
     *
     * Return the @c std::string for greater or equal than.
     *
     * @return The @c std::string for greater or equal than.
     */
    std::string geqString() const;
    /**
     * @brief Set the @c std::string for greater or equal than.
     *
     * Set this @c std::string for greater or equal than.
     *
     * @param eqString The @c std::string to use for greater or equal than.
     */
    void setGeqString(const std::string &geqString);

    /**
     * @brief Get the @c std::string for and.
     *
     * Return the @c std::string for and.
     *
     * @return The @c std::string for and.
     */
    std::string andString() const;
    /**
     * @brief Set the @c std::string for and.
     *
     * Set this @c std::string for and.
     *
     * @param eqString The @c std::string to use for and.
     */
    void setAndString(const std::string &andString);

    /**
     * @brief Get the @c std::string for or.
     *
     * Return the @c std::string for or.
     *
     * @return The @c std::string for or.
     */
    std::string orString() const;
    /**
     * @brief Set the @c std::string for or.
     *
     * Set this @c std::string for or.
     *
     * @param eqString The @c std::string to use for or.
     */
    void setOrString(const std::string &orString);

    /**
     * @brief Get the @c std::string for xor.
     *
     * Return the @c std::string for xor.
     *
     * @return The @c std::string for xor.
     */
    std::string xorString() const;
    /**
     * @brief Set the @c std::string for xor.
     *
     * Set this @c std::string for xor.
     *
     * @param eqString The @c std::string to use for xor.
     */
    void setXorString(const std::string &xorString);

    /**
     * @brief Get the @c std::string for not.
     *
     * Return the @c std::string for not.
     *
     * @return The @c std::string for not.
     */
    std::string notString() const;
    /**
     * @brief Set the @c std::string for not.
     *
     * Set this @c std::string for not.
     *
     * @param eqString The @c std::string to use for not.
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

    /**
     * @brief Get the @c std::string for an addition.
     *
     * Return the @c std::string for an addition.
     *
     * @return The @c std::string for an addition.
     */
    std::string plusString() const;
    /**
     * @brief Set the @c std::string for an addition.
     *
     * Set this @c std::string for an addition.
     *
     * @param eqString The @c std::string to use for an addition.
     */
    void setPlusString(const std::string &plusString);

    /**
     * @brief Get the @c std::string for a subtraction.
     *
     * Return the @c std::string for a subtraction.
     *
     * @return The @c std::string for a subtraction.
     */
    std::string minusString() const;
    /**
     * @brief Set the @c std::string for a subtraction.
     *
     * Set this @c std::string for a subtraction.
     *
     * @param eqString The @c std::string to use for a subtraction.
     */
    void setMinusString(const std::string &minusString);

    /**
     * @brief Get the @c std::string for a multiplication.
     *
     * Return the @c std::string for a multiplication.
     *
     * @return The @c std::string for a multiplication.
     */
    std::string timesString() const;
    /**
     * @brief Set the @c std::string for a multiplication.
     *
     * Set this @c std::string for a multiplication.
     *
     * @param eqString The @c std::string to use for a multiplication.
     */
    void setTimesString(const std::string &timesString);

    /**
     * @brief Get the @c std::string for a division.
     *
     * Return the @c std::string for a division.
     *
     * @return The @c std::string for a division.
     */
    std::string divideString() const;
    /**
     * @brief Set the @c std::string for a division.
     *
     * Set this @c std::string for a division.
     *
     * @param eqString The @c std::string to use for a division.
     */
    void setDivideString(const std::string &divideString);

    /**
     * @brief Get the @c std::string for power.
     *
     * Return the @c std::string for power.
     *
     * @return The @c std::string for power.
     */
    std::string powerString() const;
    /**
     * @brief Set the @c std::string for power.
     *
     * Set this @c std::string for power.
     *
     * @param eqString The @c std::string to use for power.
     */
    void setPowerString(const std::string &powerString);

    /**
     * @brief Get the @c std::string for square root.
     *
     * Return the @c std::string for square root.
     *
     * @return The @c std::string for square root.
     */
    std::string squareRootString() const;
    /**
     * @brief Set the @c std::string for square root.
     *
     * Set this @c std::string for square root.
     *
     * @param eqString The @c std::string to use for square root.
     */
    void setSquareRootString(const std::string &squareRootString);

    /**
     * @brief Get the @c std::string for square.
     *
     * Return the @c std::string for square.
     *
     * @return The @c std::string for square.
     */
    std::string squareString() const;
    /**
     * @brief Set the @c std::string for square.
     *
     * Set this @c std::string for square.
     *
     * @param eqString The @c std::string to use for square.
     */
    void setSquareString(const std::string &squareString);

    /**
     * @brief Get the @c std::string for absolute.
     *
     * Return the @c std::string for absolute.
     *
     * @return The @c std::string for absolute.
     */
    std::string absoluteValueString() const;
    /**
     * @brief Set the @c std::string for absolute.
     *
     * Set this @c std::string for absolute.
     *
     * @param eqString The @c std::string to use for absolute.
     */
    void setAbsoluteValueString(const std::string &absoluteValueString);

    /**
     * @brief Get the @c std::string for exponential.
     *
     * Return the @c std::string for exponential.
     *
     * @return The @c std::string for exponential.
     */
    std::string exponentialString() const;
    /**
     * @brief Set the @c std::string for exponential.
     *
     * Set this @c std::string for exponential.
     *
     * @param eqString The @c std::string to use for exponential.
     */
    void setExponentialString(const std::string &exponentialString);

    /**
     * @brief Get the @c std::string for Napierian logarithm.
     *
     * Return the @c std::string for Napierian logarithm.
     *
     * @return The @c std::string for Napierian logarithm.
     */
    std::string napierianLogarithmString() const;
    /**
     * @brief Set the @c std::string for Napierian logarithm.
     *
     * Set this @c std::string for Napierian logarithm.
     *
     * @param eqString The @c std::string to use for Napierian logarithm.
     */
    void setNapierianLogarithmString(const std::string &napierianLogarithmString);

    /**
     * @brief Get the @c std::string for common logarithm.
     *
     * Return the @c std::string for common logarithm.
     *
     * @return The @c std::string for common logarithm.
     */
    std::string commonLogarithmString() const;
    /**
     * @brief Set the @c std::string for common logarithm.
     *
     * Set this @c std::string for common logarithm.
     *
     * @param eqString The @c std::string to use for common logarithm.
     */
    void setCommonLogarithmString(const std::string &commonLogarithmString);

    /**
     * @brief Get the @c std::string for ceiling.
     *
     * Return the @c std::string for ceiling.
     *
     * @return The @c std::string for ceiling.
     */
    std::string ceilingString() const;
    /**
     * @brief Set the @c std::string for ceiling.
     *
     * Set this @c std::string for ceiling.
     *
     * @param eqString The @c std::string to use for ceiling.
     */
    void setCeilingString(const std::string &ceilingString);

    /**
     * @brief Get the @c std::string for floor.
     *
     * Return the @c std::string for floor.
     *
     * @return The @c std::string for floor.
     */
    std::string floorString() const;
    /**
     * @brief Set the @c std::string for floor.
     *
     * Set this @c std::string for floor.
     *
     * @param eqString The @c std::string to use for floor.
     */
    void setFloorString(const std::string &floorString);

    /**
     * @brief Get the @c std::string for minimum.
     *
     * Return the @c std::string for minimum.
     *
     * @return The @c std::string for minimum.
     */
    std::string minString() const;
    /**
     * @brief Set the @c std::string for minimum.
     *
     * Set this @c std::string for minimum.
     *
     * @param eqString The @c std::string to use for minimum.
     */
    void setMinString(const std::string &minString);

    /**
     * @brief Get the @c std::string for maximum.
     *
     * Return the @c std::string for maximum.
     *
     * @return The @c std::string for maximum.
     */
    std::string maxString() const;
    /**
     * @brief Set the @c std::string for maximum.
     *
     * Set this @c std::string for maximum.
     *
     * @param eqString The @c std::string to use for maximum.
     */
    void setMaxString(const std::string &maxString);

    /**
     * @brief Get the @c std::string for remainder.
     *
     * Return the @c std::string for remainder.
     *
     * @return The @c std::string for remainder.
     */
    std::string remString() const;
    /**
     * @brief Set the @c std::string for remainder.
     *
     * Set this @c std::string for remainder.
     *
     * @param eqString The @c std::string to use for remainder.
     */
    void setRemString(const std::string &remString);

    bool hasPowerOperator() const;
    void setHasPowerOperator(bool hasPowerOperator);

    // Trigonometric operators

    /**
     * @brief Get the @c std::string for sine.
     *
     * Return the @c std::string for sine.
     *
     * @return The @c std::string for sine.
     */
    std::string sinString() const;
    /**
     * @brief Set the @c std::string for sine.
     *
     * Set this @c std::string for sine.
     *
     * @param eqString The @c std::string to use for sine.
     */
    void setSinString(const std::string &sinString);

    /**
     * @brief Get the @c std::string for cosine.
     *
     * Return the @c std::string for cosine.
     *
     * @return The @c std::string for cosine.
     */
    std::string cosString() const;
    /**
     * @brief Set the @c std::string for cosine.
     *
     * Set this @c std::string for cosine.
     *
     * @param eqString The @c std::string to use for cosine.
     */
    void setCosString(const std::string &cosString);

    /**
     * @brief Get the @c std::string for tangent.
     *
     * Return the @c std::string for tangent.
     *
     * @return The @c std::string for tangent.
     */
    std::string tanString() const;
    /**
     * @brief Set the @c std::string for tangent.
     *
     * Set this @c std::string for tangent.
     *
     * @param eqString The @c std::string to use for tangent.
     */
    void setTanString(const std::string &tanString);

    /**
     * @brief Get the @c std::string for secant.
     *
     * Return the @c std::string for secant.
     *
     * @return The @c std::string for secant.
     */
    std::string secString() const;
    /**
     * @brief Set the @c std::string for secant.
     *
     * Set this @c std::string for secant.
     *
     * @param eqString The @c std::string to use for secant.
     */
    void setSecString(const std::string &secString);

    /**
     * @brief Get the @c std::string for cosecant.
     *
     * Return the @c std::string for cosecant.
     *
     * @return The @c std::string for cosecant.
     */
    std::string cscString() const;
    /**
     * @brief Set the @c std::string for cosecant.
     *
     * Set this @c std::string for cosecant.
     *
     * @param eqString The @c std::string to use for cosecant.
     */
    void setCscString(const std::string &cscString);

    /**
     * @brief Get the @c std::string for cotangent.
     *
     * Return the @c std::string for cotangent.
     *
     * @return The @c std::string for cotangent.
     */
    std::string cotString() const;
    /**
     * @brief Set the @c std::string for cotangent.
     *
     * Set this @c std::string for cotangent.
     *
     * @param eqString The @c std::string to use for cotangent.
     */
    void setCotString(const std::string &cotString);

    /**
     * @brief Get the @c std::string for hyperbolic sine.
     *
     * Return the @c std::string for hyperbolic sine.
     *
     * @return The @c std::string for hyperbolic sine.
     */
    std::string sinhString() const;
    /**
     * @brief Set the @c std::string for hyperbolic sine.
     *
     * Set this @c std::string for hyperbolic sine.
     *
     * @param eqString The @c std::string to use for hyperbolic sine.
     */
    void setSinhString(const std::string &sinhString);

    /**
     * @brief Get the @c std::string for hyperbolic cosine.
     *
     * Return the @c std::string for hyperbolic cosine.
     *
     * @return The @c std::string for hyperbolic cosine.
     */
    std::string coshString() const;
    /**
     * @brief Set the @c std::string for hyperbolic cosine.
     *
     * Set this @c std::string for hyperbolic cosine.
     *
     * @param eqString The @c std::string to use for hyperbolic cosine.
     */
    void setCoshString(const std::string &coshString);

    /**
     * @brief Get the @c std::string for hyperbolic tangent.
     *
     * Return the @c std::string for hyperbolic tangent.
     *
     * @return The @c std::string for hyperbolic tangent.
     */
    std::string tanhString() const;
    /**
     * @brief Set the @c std::string for hyperbolic tangent.
     *
     * Set this @c std::string for hyperbolic tangent.
     *
     * @param eqString The @c std::string to use for hyperbolic tangent.
     */
    void setTanhString(const std::string &tanhString);

    /**
     * @brief Get the @c std::string for hyperbolic secant.
     *
     * Return the @c std::string for hyperbolic secant.
     *
     * @return The @c std::string for hyperbolic secant.
     */
    std::string sechString() const;
    /**
     * @brief Set the @c std::string for hyperbolic secant.
     *
     * Set this @c std::string for hyperbolic secant.
     *
     * @param eqString The @c std::string to use for hyperbolic secant.
     */
    void setSechString(const std::string &sechString);

    /**
     * @brief Get the @c std::string for hyperbolic cosecant.
     *
     * Return the @c std::string for hyperbolic cosecant.
     *
     * @return The @c std::string for hyperbolic cosecant.
     */
    std::string cschString() const;
    /**
     * @brief Set the @c std::string for hyperbolic cosecant.
     *
     * Set this @c std::string for hyperbolic cosecant.
     *
     * @param eqString The @c std::string to use for hyperbolic cosecant.
     */
    void setCschString(const std::string &cschString);

    /**
     * @brief Get the @c std::string for hyperbolic cotangent.
     *
     * Return the @c std::string for hyperbolic cotangent.
     *
     * @return The @c std::string for hyperbolic cotangent.
     */
    std::string cothString() const;
    /**
     * @brief Set the @c std::string for hyperbolic cotangent.
     *
     * Set this @c std::string for hyperbolic cotangent.
     *
     * @param eqString The @c std::string to use for hyperbolic cotangent.
     */
    void setCothString(const std::string &cothString);

    /**
     * @brief Get the @c std::string for inverse sine.
     *
     * Return the @c std::string for inverse sine.
     *
     * @return The @c std::string for inverse sine.
     */
    std::string asinString() const;
    /**
     * @brief Set the @c std::string for inverse sine.
     *
     * Set this @c std::string for inverse sine.
     *
     * @param eqString The @c std::string to use for inverse sine.
     */
    void setAsinString(const std::string &asinString);

    /**
     * @brief Get the @c std::string for inverse cosine.
     *
     * Return the @c std::string for inverse cosine.
     *
     * @return The @c std::string for inverse cosine.
     */
    std::string acosString() const;
    /**
     * @brief Set the @c std::string for inverse cosine.
     *
     * Set this @c std::string for inverse cosine.
     *
     * @param eqString The @c std::string to use for inverse cosine.
     */
    void setAcosString(const std::string &acosString);

    /**
     * @brief Get the @c std::string for inverse tangent.
     *
     * Return the @c std::string for inverse tangent.
     *
     * @return The @c std::string for inverse tangent.
     */
    std::string atanString() const;
    /**
     * @brief Set the @c std::string for inverse tangent.
     *
     * Set this @c std::string for inverse tangent.
     *
     * @param eqString The @c std::string to use for inverse tangent.
     */
    void setAtanString(const std::string &atanString);

    /**
     * @brief Get the @c std::string for inverse secant.
     *
     * Return the @c std::string for inverse secant.
     *
     * @return The @c std::string for inverse secant.
     */
    std::string asecString() const;
    /**
     * @brief Set the @c std::string for inverse secant.
     *
     * Set this @c std::string for inverse secant.
     *
     * @param eqString The @c std::string to use for inverse secant.
     */
    void setAsecString(const std::string &asecString);

    /**
     * @brief Get the @c std::string for inverse cosecant.
     *
     * Return the @c std::string for inverse cosecant.
     *
     * @return The @c std::string for inverse cosecant.
     */
    std::string acscString() const;
    /**
     * @brief Set the @c std::string for inverse cosecant.
     *
     * Set this @c std::string for inverse cosecant.
     *
     * @param eqString The @c std::string to use for inverse cosecant.
     */
    void setAcscString(const std::string &acscString);

    /**
     * @brief Get the @c std::string for inverse cotangent.
     *
     * Return the @c std::string for inverse cotangent.
     *
     * @return The @c std::string for inverse cotangent.
     */
    std::string acotString() const;
    /**
     * @brief Set the @c std::string for inverse cotangent.
     *
     * Set this @c std::string for inverse cotangent.
     *
     * @param eqString The @c std::string to use for inverse cotangent.
     */
    void setAcotString(const std::string &acotString);

    /**
     * @brief Get the @c std::string for inverse hyperbolic sine.
     *
     * Return the @c std::string for inverse hyperbolic sine.
     *
     * @return The @c std::string for inverse hyperbolic sine.
     */
    std::string asinhString() const;
    /**
     * @brief Set the @c std::string for inverse hyperbolic sine.
     *
     * Set this @c std::string for inverse hyperbolic sine.
     *
     * @param eqString The @c std::string to use for inverse hyperbolic sine.
     */
    void setAsinhString(const std::string &asinhString);

    /**
     * @brief Get the @c std::string for inverse hyperbolic cosine.
     *
     * Return the @c std::string for inverse hyperbolic cosine.
     *
     * @return The @c std::string for inverse hyperbolic cosine.
     */
    std::string acoshString() const;
    /**
     * @brief Set the @c std::string for inverse hyperbolic cosine.
     *
     * Set this @c std::string for inverse hyperbolic cosine.
     *
     * @param eqString The @c std::string to use for inverse hyperbolic cosine.
     */
    void setAcoshString(const std::string &acoshString);

    /**
     * @brief Get the @c std::string for inverse hyperbolic tangent.
     *
     * Return the @c std::string for inverse hyperbolic tangent.
     *
     * @return The @c std::string for inverse hyperbolic tangent.
     */
    std::string atanhString() const;
    /**
     * @brief Set the @c std::string for inverse hyperbolic tangent.
     *
     * Set this @c std::string for inverse hyperbolic tangent.
     *
     * @param eqString The @c std::string to use for inverse hyperbolic tangent.
     */
    void setAtanhString(const std::string &atanhString);

    /**
     * @brief Get the @c std::string for inverse hyperbolic secant.
     *
     * Return the @c std::string for inverse hyperbolic secant.
     *
     * @return The @c std::string for inverse hyperbolic secant.
     */
    std::string asechString() const;
    /**
     * @brief Set the @c std::string for inverse hyperbolic secant.
     *
     * Set this @c std::string for inverse hyperbolic secant.
     *
     * @param eqString The @c std::string to use for inverse hyperbolic secant.
     */
    void setAsechString(const std::string &asechString);

    /**
     * @brief Get the @c std::string for inverse hyperbolic cosecant.
     *
     * Return the @c std::string for inverse hyperbolic cosecant.
     *
     * @return The @c std::string for inverse hyperbolic cosecant.
     */
    std::string acschString() const;
    /**
     * @brief Set the @c std::string for inverse hyperbolic cosecant.
     *
     * Set this @c std::string for inverse hyperbolic cosecant.
     *
     * @param eqString The @c std::string to use for inverse hyperbolic cosecant.
     */
    void setAcschString(const std::string &acschString);

    /**
     * @brief Get the @c std::string for inverse hyperbolic cotangent.
     *
     * Return the @c std::string for inverse hyperbolic cotangent.
     *
     * @return The @c std::string for inverse hyperbolic cotangent.
     */
    std::string acothString() const;
    /**
     * @brief Set the @c std::string for inverse hyperbolic cotangent.
     *
     * Set this @c std::string for inverse hyperbolic cotangent.
     *
     * @param eqString The @c std::string to use for inverse hyperbolic cotangent.
     */
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
