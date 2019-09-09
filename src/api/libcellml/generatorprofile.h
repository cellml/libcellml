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
     * @brief Get the @c std::string for the equivalence operator.
     *
     * Return the @c std::string for the equivalence operator.
     *
     * @return The @c std::string for the equivalence operator.
     */
    std::string eqEqString() const;

    /**
     * @brief Set the @c std::string for the equivalence operator.
     *
     * Set this @c std::string for the equivalence operator.
     *
     * @param eqString The @c std::string to use for the equivalence operator.
     */
    void setEqEqString(const std::string &eqEqString);

    /**
     * @brief Get the @c std::string for the nonequivalence operator.
     *
     * Return the @c std::string for the nonequivalence operator.
     *
     * @return The @c std::string for the nonequivalence operator.
     */
    std::string neqString() const;

    /**
     * @brief Set the @c std::string for the nonequivalence operator.
     *
     * Set this @c std::string for the nonequivalence operator.
     *
     * @param eqString The @c std::string to use for the nonequivalence operator.
     */
    void setNeqString(const std::string &neqString);

    /**
     * @brief Get the @c std::string for the lower than operator.
     *
     * Return the @c std::string for the lower than operator.
     *
     * @return The @c std::string for the lower than operator.
     */
    std::string ltString() const;

    /**
     * @brief Set the @c std::string for the lower than operator.
     *
     * Set this @c std::string for the lower than operator.
     *
     * @param eqString The @c std::string to use for the lower than operator.
     */
    void setLtString(const std::string &ltString);

    /**
     * @brief Get the @c std::string for the lower or equal than operator.
     *
     * Return the @c std::string for the lower or equal than operator.
     *
     * @return The @c std::string for the lower or equal than operator.
     */
    std::string leqString() const;

    /**
     * @brief Set the @c std::string for the lower or equal than operator.
     *
     * Set this @c std::string for the lower or equal than operator.
     *
     * @param eqString The @c std::string to use for the lower or equal than
     * operator.
     */
    void setLeqString(const std::string &leqString);

    /**
     * @brief Get the @c std::string for the greater than operator.
     *
     * Return the @c std::string for the greater than operator.
     *
     * @return The @c std::string for the greater than operator.
     */
    std::string gtString() const;

    /**
     * @brief Set the @c std::string for the greater than operator.
     *
     * Set this @c std::string for the greater than operator.
     *
     * @param eqString The @c std::string to use for the greater than operator.
     */
    void setGtString(const std::string &gtString);

    /**
     * @brief Get the @c std::string for the greater or equal than operator.
     *
     * Return the @c std::string for the greater or equal than operator.
     *
     * @return The @c std::string for the greater or equal than operator.
     */
    std::string geqString() const;

    /**
     * @brief Set the @c std::string for the greater or equal than operator.
     *
     * Set this @c std::string for the greater or equal than operator.
     *
     * @param eqString The @c std::string to use for the greater or equal than
     * operator.
     */
    void setGeqString(const std::string &geqString);

    /**
     * @brief Get the @c std::string for the and operator.
     *
     * Return the @c std::string for the and operator.
     *
     * @return The @c std::string for the and operator.
     */
    std::string andString() const;

    /**
     * @brief Set the @c std::string for the and operator.
     *
     * Set this @c std::string for the and operator.
     *
     * @param eqString The @c std::string to use for the and operator.
     */
    void setAndString(const std::string &andString);

    /**
     * @brief Get the @c std::string for the or operator.
     *
     * Return the @c std::string for the or operator.
     *
     * @return The @c std::string for the or operator.
     */
    std::string orString() const;

    /**
     * @brief Set the @c std::string for the or operator.
     *
     * Set this @c std::string for the or operator.
     *
     * @param eqString The @c std::string to use for the or operator.
     */
    void setOrString(const std::string &orString);

    /**
     * @brief Get the @c std::string for the xor operator.
     *
     * Return the @c std::string for the xor operator.
     *
     * @return The @c std::string for the xor operator.
     */
    std::string xorString() const;

    /**
     * @brief Set the @c std::string for the xor operator.
     *
     * Set this @c std::string for the xor operator.
     *
     * @param eqString The @c std::string to use for the xor operator.
     */
    void setXorString(const std::string &xorString);

    /**
     * @brief Get the @c std::string for the not operator.
     *
     * Return the @c std::string for the not operator.
     *
     * @return The @c std::string for the not operator.
     */
    std::string notString() const;

    /**
     * @brief Set the @c std::string for the not operator.
     *
     * Set this @c std::string for the not operator.
     *
     * @param eqString The @c std::string to use for the not operator.
     */
    void setNotString(const std::string &notString);

    /**
     * @brief Test if this @c GeneratorProfile has an equivalence operator.
     *
     * Test if this @c GeneratorProfile has an equivalence operator.
     *
     * @return @c true if the @c GeneratorProfile has an equivalence operator,
     * @c false otherwise.
     */
    bool hasEqEqOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has an equivalence operator.
     *
     * Set whether this @c GeneratorProfile has an equivalence operator.
     *
     * @param hasEqEqOperator A @c bool to determine whether this
     * @c GeneratorProfile has an equivalence operator.
     */
    void setHasEqEqOperator(bool hasEqEqOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a nonequivalence operator.
     *
     * Test if this @c GeneratorProfile has a nonequivalence operator.
     *
     * @return @c true if the @c GeneratorProfile has a nonequivalence operator,
     * @c false otherwise.
     */
    bool hasNeqOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a nonequivalence operator.
     *
     * Set whether this @c GeneratorProfile has a nonequivalence operator.
     *
     * @param hasNeqOperator A @c bool to determine whether this
     * @c GeneratorProfile has a nonequivalence operator.
     */
    void setHasNeqOperator(bool hasNeqOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a lower than operator.
     *
     * Test if this @c GeneratorProfile has a lower than operator.
     *
     * @return @c true if the @c GeneratorProfile has a lower than operator,
     * @c false otherwise.
     */
    bool hasLtOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a lower than operator.
     *
     * Set whether this @c GeneratorProfile has a lower than operator.
     *
     * @param hasLtOperator A @c bool to determine whether this
     * @c GeneratorProfile has a lower than operator.
     */
    void setHasLtOperator(bool hasLtOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a lower or equal than
     * operator.
     *
     * Test if this @c GeneratorProfile has a lower or equal than operator.
     *
     * @return @c true if the @c GeneratorProfile has a lower or equal than
     * operator,
     * @c false otherwise.
     */
    bool hasLeqOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a lower or equal than
     *  operator.
     *
     * Set whether this @c GeneratorProfile has a lower or equal than operator.
     *
     * @param hasLeqOperator A @c bool to determine whether this
     * @c GeneratorProfile has a lower or equal than operator.
     */
    void setHasLeqOperator(bool hasLeqOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a greater than operator.
     *
     * Test if this @c GeneratorProfile has a greater than operator.
     *
     * @return @c true if the @c GeneratorProfile has a greater than operator,
     * @c false otherwise.
     */
    bool hasGtOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a greater than operator.
     *
     * Set whether this @c GeneratorProfile has a greater than operator.
     *
     * @param hasGtOperator A @c bool to determine whether this
     * @c GeneratorProfile has a greater than operator.
     */
    void setHasGtOperator(bool hasGtOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a greater or equal than
     * operator.
     *
     * Test if this @c GeneratorProfile has a greater or equal than operator.
     *
     * @return @c true if the @c GeneratorProfile has a greater or equal than
     * operator,
     * @c false otherwise.
     */
    bool hasGeqOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a greater or equal than
     *  operator.
     *
     * Set whether this @c GeneratorProfile has a greater or equal than
     * operator.
     *
     * @param hasGeqOperator A @c bool to determine whether this
     * @c GeneratorProfile has a greater or equal than operator.
     */
    void setHasGeqOperator(bool hasGeqOperator);

    /**
     * @brief Test if this @c GeneratorProfile has an and operator.
     *
     * Test if this @c GeneratorProfile has an and operator.
     *
     * @return @c true if the @c GeneratorProfile has an and operator,
     * @c false otherwise.
     */
    bool hasAndOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has an and operator.
     *
     * Set whether this @c GeneratorProfile has an and operator.
     *
     * @param hasAndOperator A @c bool to determine whether this
     * @c GeneratorProfile has an and operator.
     */
    void setHasAndOperator(bool hasAndOperator);

    /**
     * @brief Test if this @c GeneratorProfile has an or operator.
     *
     * Test if this @c GeneratorProfile has an or operator.
     *
     * @return @c true if the @c GeneratorProfile has an or operator,
     * @c false otherwise.
     */
    bool hasOrOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has an or operator.
     *
     * Set whether this @c GeneratorProfile has an or operator.
     *
     * @param hasOrOperator A @c bool to determine whether this
     * @c GeneratorProfile has an or operator.
     */
    void setHasOrOperator(bool hasOrOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a xor operator.
     *
     * Test if this @c GeneratorProfile has a xor operator.
     *
     * @return @c true if the @c GeneratorProfile has a xor operator,
     * @c false otherwise.
     */
    bool hasXorOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a xor operator.
     *
     * Set whether this @c GeneratorProfile has a xor operator.
     *
     * @param hasXorOperator A @c bool to determine whether this
     * @c GeneratorProfile has a xor operator.
     */
    void setHasXorOperator(bool hasXorOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a not operator.
     *
     * Test if this @c GeneratorProfile has a not operator.
     *
     * @return @c true if the @c GeneratorProfile has a not operator,
     * @c false otherwise.
     */
    bool hasNotOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a not operator.
     *
     * Set whether this @c GeneratorProfile has a not operator.
     *
     * @param hasNotOperator A @c bool to determine whether this
     * @c GeneratorProfile has a not operator.
     */
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
     * @brief Get the @c std::string for a power.
     *
     * Return the @c std::string for a power.
     *
     * @return The @c std::string for a power.
     */
    std::string powerString() const;

    /**
     * @brief Set the @c std::string for a power.
     *
     * Set this @c std::string for a power.
     *
     * @param eqString The @c std::string to use for a power.
     */
    void setPowerString(const std::string &powerString);

    /**
     * @brief Get the @c std::string for a square root.
     *
     * Return the @c std::string for a square root.
     *
     * @return The @c std::string for a square root.
     */
    std::string squareRootString() const;

    /**
     * @brief Set the @c std::string for a square root.
     *
     * Set this @c std::string for a square root.
     *
     * @param eqString The @c std::string to use for a square root.
     */
    void setSquareRootString(const std::string &squareRootString);

    /**
     * @brief Get the @c std::string for a square.
     *
     * Return the @c std::string for a square.
     *
     * @return The @c std::string for a square.
     */
    std::string squareString() const;

    /**
     * @brief Set the @c std::string for a square.
     *
     * Set this @c std::string for a square.
     *
     * @param eqString The @c std::string to use for a square.
     */
    void setSquareString(const std::string &squareString);

    /**
     * @brief Get the @c std::string for an absolute value.
     *
     * Return the @c std::string for an absolute value.
     *
     * @return The @c std::string for an absolute value.
     */
    std::string absoluteValueString() const;

    /**
     * @brief Set the @c std::string for an absolute value.
     *
     * Set this @c std::string for an absolute value.
     *
     * @param eqString The @c std::string to use for an absolute value.
     */
    void setAbsoluteValueString(const std::string &absoluteValueString);

    /**
     * @brief Get the @c std::string for an exponential.
     *
     * Return the @c std::string for an exponential.
     *
     * @return The @c std::string for an exponential.
     */
    std::string exponentialString() const;

    /**
     * @brief Set the @c std::string for an exponential.
     *
     * Set this @c std::string for an exponential.
     *
     * @param eqString The @c std::string to use for an exponential.
     */
    void setExponentialString(const std::string &exponentialString);

    /**
     * @brief Get the @c std::string for a Napierian logarithm.
     *
     * Return the @c std::string for a Napierian logarithm.
     *
     * @return The @c std::string for a Napierian logarithm.
     */
    std::string napierianLogarithmString() const;

    /**
     * @brief Set the @c std::string for a Napierian logarithm.
     *
     * Set this @c std::string for a Napierian logarithm.
     *
     * @param eqString The @c std::string to use for a Napierian logarithm.
     */
    void setNapierianLogarithmString(const std::string &napierianLogarithmString);

    /**
     * @brief Get the @c std::string for a common logarithm.
     *
     * Return the @c std::string for a common logarithm.
     *
     * @return The @c std::string for a common logarithm.
     */
    std::string commonLogarithmString() const;

    /**
     * @brief Set the @c std::string for a common logarithm.
     *
     * Set this @c std::string for a common logarithm.
     *
     * @param eqString The @c std::string to use for a common logarithm.
     */
    void setCommonLogarithmString(const std::string &commonLogarithmString);

    /**
     * @brief Get the @c std::string for a ceiling.
     *
     * Return the @c std::string for a ceiling.
     *
     * @return The @c std::string for a ceiling.
     */
    std::string ceilingString() const;

    /**
     * @brief Set the @c std::string for a ceiling.
     *
     * Set this @c std::string for a ceiling.
     *
     * @param eqString The @c std::string to use for a ceiling.
     */
    void setCeilingString(const std::string &ceilingString);

    /**
     * @brief Get the @c std::string for a floor.
     *
     * Return the @c std::string for a floor.
     *
     * @return The @c std::string for a floor.
     */
    std::string floorString() const;

    /**
     * @brief Set the @c std::string for a floor.
     *
     * Set this @c std::string for a floor.
     *
     * @param eqString The @c std::string to use for a floor.
     */
    void setFloorString(const std::string &floorString);

    /**
     * @brief Get the @c std::string for a minimum.
     *
     * Return the @c std::string for a minimum.
     *
     * @return The @c std::string for a minimum.
     */
    std::string minString() const;

    /**
     * @brief Set the @c std::string for a minimum.
     *
     * Set this @c std::string for a minimum.
     *
     * @param eqString The @c std::string to use for a minimum.
     */
    void setMinString(const std::string &minString);

    /**
     * @brief Get the @c std::string for a maximum.
     *
     * Return the @c std::string for a maximum.
     *
     * @return The @c std::string for a maximum.
     */
    std::string maxString() const;

    /**
     * @brief Set the @c std::string for a maximum.
     *
     * Set this @c std::string for a maximum.
     *
     * @param eqString The @c std::string to use for a maximum.
     */
    void setMaxString(const std::string &maxString);

    /**
     * @brief Get the @c std::string for a remainder.
     *
     * Return the @c std::string for a remainder.
     *
     * @return The @c std::string for a remainder.
     */
    std::string remString() const;

    /**
     * @brief Set the @c std::string for a remainder.
     *
     * Set this @c std::string for a remainder.
     *
     * @param eqString The @c std::string to use for a remainder.
     */
    void setRemString(const std::string &remString);

    /**
     * @brief Test if this @c GeneratorProfile has a power operator.
     *
     * Test if this @c GeneratorProfile has a power operator.
     *
     * @return @c true if the @c GeneratorProfile has a power operator,
     * @c false otherwise.
     */
    bool hasPowerOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a power operator.
     *
     * Set whether this @c GeneratorProfile has a power operator.
     *
     * @param hasPowerOperator A @c bool to determine whether this
     * @c GeneratorProfile has a power operator.
     */
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
     * @param eqString The @c std::string to use for inverse hyperbolic
     * cosecant.
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
     * @param eqString The @c std::string to use for inverse hyperbolic
     * cotangent.
     */
    void setAcothString(const std::string &acothString);

    // Piecewise statement
    // Note: the parentheses around #cond is not needed (because of precedence
    //       rules). It's just that it looks better/clearer to have them
    //       (somewhat subjective indeed).

    /**
     * @brief Get the @c std::string for the if part of a condition statement.
     *
     * Return the @c std::string for the if part of a condition statement.
     *
     * @return The @c std::string for the if part of a condition statement.
     */
    std::string conditionalOperatorIfString() const;

    /**
     * @brief Set the @c std::string for the if part of a condition statement.
     *
     * Set this @c std::string for the if part of a condition statement.
     *
     * @param eqString The @c std::string to use for the if part of a condition
     * statement.
     */
    void setConditionalOperatorIfString(const std::string &conditionalOperatorIfString);

    /**
     * @brief Get the @c std::string for the else part of a condition statement.
     *
     * Return the @c std::string for the else part of a condition statement.
     *
     * @return The @c std::string for the else part of a condition statement.
     */
    std::string conditionalOperatorElseString() const;

    /**
     * @brief Set the @c std::string for the else part of a condition statement.
     *
     * Set this @c std::string for the else part of a condition statement.
     *
     * @param eqString The @c std::string to use for the else part of a
     * condition statement.
     */
    void setConditionalOperatorElseString(const std::string &conditionalOperatorElseString);

    /**
     * @brief Get the @c std::string for the if part of a piecewise statement.
     *
     * Return the @c std::string for the if part of a piecewise statement.
     *
     * @return The @c std::string for the if part of a piecewise statement.
     */
    std::string piecewiseIfString() const;

    /**
     * @brief Set the @c std::string for the if part of a piecewise statement.
     *
     * Set this @c std::string for the if part of a piecewise statement.
     *
     * @param eqString The @c std::string to use for the if part of a piecewise
     * statement.
     */
    void setPiecewiseIfString(const std::string &piecewiseIfString);

    /**
     * @brief Get the @c std::string for the else part of a piecewise statement.
     *
     * Return the @c std::string for the else part of a piecewise statement.
     *
     * @return The @c std::string for the else part of a piecewise statement.
     */
    std::string piecewiseElseString() const;

    /**
     * @brief Set the @c std::string for the else part of a piecewise statement.
     *
     * Set this @c std::string for the else part of a piecewise statement.
     *
     * @param eqString The @c std::string to use for the else part of a
     * piecewise statement.
     */
    void setPiecewiseElseString(const std::string &piecewiseElseString);

    /**
     * @brief Test if this @c GeneratorProfile has a conditional operator.
     *
     * Test if this @c GeneratorProfile has a conditional operator.
     *
     * @return @c true if the @c GeneratorProfile has a conditional operator,
     * @c false otherwise.
     */
    bool hasConditionalOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a conditional operator.
     *
     * Set whether this @c GeneratorProfile has a conditional operator.
     *
     * @param hasConditionalOperator A @c bool to determine whether this
     * @c GeneratorProfile has a conditional operator.
     */
    void setHasConditionalOperator(bool hasConditionalOperator);

    // Constants

    /**
     * @brief Get the @c std::string for true.
     *
     * Return the @c std::string for true.
     *
     * @return The @c std::string for true.
     */
    std::string trueString() const;

    /**
     * @brief Set the @c std::string for true.
     *
     * Set this @c std::string for true.
     *
     * @param eqString The @c std::string to use for true.
     */
    void setTrueString(const std::string &trueString);

    /**
     * @brief Get the @c std::string for false.
     *
     * Return the @c std::string for false.
     *
     * @return The @c std::string for false.
     */
    std::string falseString() const;

    /**
     * @brief Set the @c std::string for false.
     *
     * Set this @c std::string for false.
     *
     * @param eqString The @c std::string to use for false.
     */
    void setFalseString(const std::string &falseString);

    /**
     * @brief Get the @c std::string for exponential constant.
     *
     * Return the @c std::string for exponential constant.
     *
     * @return The @c std::string for exponential constant.
     */
    std::string eString() const;

    /**
     * @brief Set the @c std::string for exponential constant.
     *
     * Set this @c std::string for exponential constant.
     *
     * @param eqString The @c std::string to use for exponential constant.
     */
    void setEString(const std::string &eString);

    /**
     * @brief Get the @c std::string for π.
     *
     * Return the @c std::string for π.
     *
     * @return The @c std::string for π.
     */
    std::string piString() const;

    /**
     * @brief Set the @c std::string for π.
     *
     * Set this @c std::string for π.
     *
     * @param eqString The @c std::string to use for π.
     */
    void setPiString(const std::string &piString);

    /**
     * @brief Get the @c std::string for infinity.
     *
     * Return the @c std::string for infinity.
     *
     * @return The @c std::string for infinity.
     */
    std::string infString() const;

    /**
     * @brief Set the @c std::string for infinity.
     *
     * Set this @c std::string for infinity.
     *
     * @param eqString The @c std::string to use for infinity.
     */
    void setInfString(const std::string &infString);

    /**
     * @brief Get the @c std::string for NaN.
     *
     * Return the @c std::string for NaN.
     *
     * @return The @c std::string for NaN.
     */
    std::string nanString() const;

    /**
     * @brief Set the @c std::string for NaN.
     *
     * Set this @c std::string for NaN.
     *
     * @param eqString The @c std::string to use for NaN.
     */
    void setNanString(const std::string &nanString);

    // Mathematical functions

    /**
     * @brief Get the @c std::string for the equivalence function.
     *
     * Return the @c std::string for the equivalence function.
     *
     * @return The @c std::string for the equivalence function.
     */
    std::string eqEqFunctionString() const;

    /**
     * @brief Set the @c std::string for the equivalence function.
     *
     * Set this @c std::string for the equivalence function.
     *
     * @param eqString The @c std::string to use for the equivalence function.
     */
    void setEqEqFunctionString(const std::string &eqEqFunctionString);

    /**
     * @brief Get the @c std::string for the nonequivalence function.
     *
     * Return the @c std::string for the nonequivalence function.
     *
     * @return The @c std::string for the nonequivalence function.
     */
    std::string neqFunctionString() const;

    /**
     * @brief Set the @c std::string for the nonequivalence function.
     *
     * Set this @c std::string for the nonequivalence function.
     *
     * @param eqString The @c std::string to use for the nonequivalence
     * function.
     */
    void setNeqFunctionString(const std::string &neqFunctionString);

    /**
     * @brief Get the @c std::string for the lower than function.
     *
     * Return the @c std::string for the lower than function.
     *
     * @return The @c std::string for the lower than function.
     */
    std::string ltFunctionString() const;

    /**
     * @brief Set the @c std::string for the lower than function.
     *
     * Set this @c std::string for the lower than function.
     *
     * @param eqString The @c std::string to use for the lower than function.
     */
    void setLtFunctionString(const std::string &ltFunctionString);

    /**
     * @brief Get the @c std::string for the lower or equal than function.
     *
     * Return the @c std::string for the lower or equal than function.
     *
     * @return The @c std::string for the lower or equal than function.
     */
    std::string leqFunctionString() const;

    /**
     * @brief Set the @c std::string for the lower or equal than function.
     *
     * Set this @c std::string for the lower or equal than function.
     *
     * @param eqString The @c std::string to use for the lower or equal than
     * function.
     */
    void setLeqFunctionString(const std::string &leqFunctionString);

    /**
     * @brief Get the @c std::string for the greater than function.
     *
     * Return the @c std::string for the greater than function.
     *
     * @return The @c std::string for the greater than function.
     */
    std::string gtFunctionString() const;

    /**
     * @brief Set the @c std::string for the greater than function.
     *
     * Set this @c std::string for the greater than function.
     *
     * @param eqString The @c std::string to use for the greater than function.
     */
    void setGtFunctionString(const std::string &gtFunctionString);

    /**
     * @brief Get the @c std::string for the greater or equal than function.
     *
     * Return the @c std::string for the greater or equal than function.
     *
     * @return The @c std::string for the greater or equal than function.
     */
    std::string geqFunctionString() const;

    /**
     * @brief Set the @c std::string for the greater or equal than function.
     *
     * Set this @c std::string for the greater or equal than function.
     *
     * @param eqString The @c std::string to use for the greater or equal than
     * function.
     */
    void setGeqFunctionString(const std::string &geqFunctionString);

    /**
     * @brief Get the @c std::string for the and function.
     *
     * Return the @c std::string for the and function.
     *
     * @return The @c std::string for the and function.
     */
    std::string andFunctionString() const;

    /**
     * @brief Set the @c std::string for the and function.
     *
     * Set this @c std::string for the and function.
     *
     * @param eqString The @c std::string to use for the and function.
     */
    void setAndFunctionString(const std::string &andFunctionString);

    /**
     * @brief Get the @c std::string for the or function.
     *
     * Return the @c std::string for the or function.
     *
     * @return The @c std::string for the or function.
     */
    std::string orFunctionString() const;

    /**
     * @brief Set the @c std::string for the or function.
     *
     * Set this @c std::string for the or function.
     *
     * @param eqString The @c std::string to use for the or function.
     */
    void setOrFunctionString(const std::string &orFunctionString);

    /**
     * @brief Get the @c std::string for the xor function.
     *
     * Return the @c std::string for the xor function.
     *
     * @return The @c std::string for the xor function.
     */
    std::string xorFunctionString() const;

    /**
     * @brief Set the @c std::string for the xor function.
     *
     * Set this @c std::string for the xor function.
     *
     * @param eqString The @c std::string to use for the xor function.
     */
    void setXorFunctionString(const std::string &xorFunctionString);

    /**
     * @brief Get the @c std::string for the not function.
     *
     * Return the @c std::string for the not function.
     *
     * @return The @c std::string for the not function.
     */
    std::string notFunctionString() const;

    /**
     * @brief Set the @c std::string for the not function.
     *
     * Set this @c std::string for the not function.
     *
     * @param eqString The @c std::string to use for the not function.
     */
    void setNotFunctionString(const std::string &notFunctionString);

    /**
     * @brief Get the @c std::string for the minimum function.
     *
     * Return the @c std::string for the minimum function.
     *
     * @return The @c std::string for the minimum function.
     */
    std::string minFunctionString() const;

    /**
     * @brief Set the @c std::string for the minimum function.
     *
     * Set this @c std::string for the minimum function.
     *
     * @param eqString The @c std::string to use for the minimum function.
     */
    void setMinFunctionString(const std::string &minFunctionString);

    /**
     * @brief Get the @c std::string for the maximum function.
     *
     * Return the @c std::string for the maximum function.
     *
     * @return The @c std::string for the maximum function.
     */
    std::string maxFunctionString() const;

    /**
     * @brief Set the @c std::string for the maximum function.
     *
     * Set this @c std::string for the maximum function.
     *
     * @param eqString The @c std::string to use for the maximum function.
     */
    void setMaxFunctionString(const std::string &maxFunctionString);

    /**
     * @brief Get the @c std::string for the secant function.
     *
     * Return the @c std::string for the secant function.
     *
     * @return The @c std::string for the secant function.
     */
    std::string secFunctionString() const;

    /**
     * @brief Set the @c std::string for the secant function.
     *
     * Set this @c std::string for the secant function.
     *
     * @param eqString The @c std::string to use for the secant function.
     */
    void setSecFunctionString(const std::string &secFunctionString);

    /**
     * @brief Get the @c std::string for the cosecant function.
     *
     * Return the @c std::string for the cosecant function.
     *
     * @return The @c std::string for the cosecant function.
     */
    std::string cscFunctionString() const;

    /**
     * @brief Set the @c std::string for the cosecant function.
     *
     * Set this @c std::string for the cosecant function.
     *
     * @param eqString The @c std::string to use for the cosecant function.
     */
    void setCscFunctionString(const std::string &cscFunctionString);

    /**
     * @brief Get the @c std::string for the cotangent function.
     *
     * Return the @c std::string for the cotangent function.
     *
     * @return The @c std::string for the cotangent function.
     */
    std::string cotFunctionString() const;

    /**
     * @brief Set the @c std::string for the cotangent function.
     *
     * Set this @c std::string for the cotangent function.
     *
     * @param eqString The @c std::string to use for the cotangent function.
     */
    void setCotFunctionString(const std::string &cotFunctionString);

    /**
     * @brief Get the @c std::string for the hyperbolic secant function.
     *
     * Return the @c std::string for the hyperbolic secant function.
     *
     * @return The @c std::string for the hyperbolic secant function.
     */
    std::string sechFunctionString() const;

    /**
     * @brief Set the @c std::string for the hyperbolic secant function.
     *
     * Set this @c std::string for the hyperbolic secant function.
     *
     * @param eqString The @c std::string to use for the hyperbolic secant
     * function.
     */
    void setSechFunctionString(const std::string &sechFunctionString);

    /**
     * @brief Get the @c std::string for the hyperbolic cosecant function.
     *
     * Return the @c std::string for the hyperbolic cosecant function.
     *
     * @return The @c std::string for the hyperbolic cosecant function.
     */
    std::string cschFunctionString() const;

    /**
     * @brief Set the @c std::string for the hyperbolic cosecant function.
     *
     * Set this @c std::string for the hyperbolic cosecant function.
     *
     * @param eqString The @c std::string to use for the hyperbolic cosecant
     * function.
     */
    void setCschFunctionString(const std::string &cschFunctionString);

    /**
     * @brief Get the @c std::string for the hyperbolic cotangent function.
     *
     * Return the @c std::string for the hyperbolic cotangent function.
     *
     * @return The @c std::string for the hyperbolic cotangent function.
     */
    std::string cothFunctionString() const;

    /**
     * @brief Set the @c std::string for the hyperbolic cotangent function.
     *
     * Set this @c std::string for the hyperbolic cotangent function.
     *
     * @param eqString The @c std::string to use for the hyperbolic cotangent
     * function.
     */
    void setCothFunctionString(const std::string &cothFunctionString);

    /**
     * @brief Get the @c std::string for the inverse secant function.
     *
     * Return the @c std::string for the inverse secant function.
     *
     * @return The @c std::string for the inverse secant function.
     */
    std::string asecFunctionString() const;

    /**
     * @brief Set the @c std::string for the inverse secant function.
     *
     * Set this @c std::string for the inverse secant function.
     *
     * @param eqString The @c std::string to use for the inverse secant function.
     */
    void setAsecFunctionString(const std::string &asecFunctionString);

    /**
     * @brief Get the @c std::string for the inverse cosecant function.
     *
     * Return the @c std::string for the inverse cosecant function.
     *
     * @return The @c std::string for the inverse cosecant function.
     */
    std::string acscFunctionString() const;

    /**
     * @brief Set the @c std::string for the inverse cosecant function.
     *
     * Set this @c std::string for the inverse cosecant function.
     *
     * @param eqString The @c std::string to use for the inverse cosecant function.
     */
    void setAcscFunctionString(const std::string &acscFunctionString);

    /**
     * @brief Get the @c std::string for the inverse cotangent function.
     *
     * Return the @c std::string for the inverse cotangent function.
     *
     * @return The @c std::string for the inverse cotangent function.
     */
    std::string acotFunctionString() const;

    /**
     * @brief Set the @c std::string for the inverse cotangent function.
     *
     * Set this @c std::string for the inverse cotangent function.
     *
     * @param eqString The @c std::string to use for the inverse cotangent
     * function.
     */
    void setAcotFunctionString(const std::string &acotFunctionString);

    /**
     * @brief Get the @c std::string for the inverse hyperbolic secant function.
     *
     * Return the @c std::string for the inverse hyperbolic secant function.
     *
     * @return The @c std::string for the inverse hyperbolic secant function.
     */
    std::string asechFunctionString() const;

    /**
     * @brief Set the @c std::string for the inverse hyperbolic secant function.
     *
     * Set this @c std::string for the inverse hyperbolic secant function.
     *
     * @param eqString The @c std::string to use for the inverse hyperbolic
     * secant function.
     */
    void setAsechFunctionString(const std::string &asechFunctionString);

    /**
     * @brief Get the @c std::string for the inverse hyperbolic cosecant
     * function.
     *
     * Return the @c std::string for the inverse hyperbolic cosecant function.
     *
     * @return The @c std::string for the inverse hyperbolic cosecant function.
     */
    std::string acschFunctionString() const;

    /**
     * @brief Set the @c std::string for the inverse hyperbolic cosecant
     * function.
     *
     * Set this @c std::string for the inverse hyperbolic cosecant function.
     *
     * @param eqString The @c std::string to use for the inverse hyperbolic
     * cosecant function.
     */
    void setAcschFunctionString(const std::string &acschFunctionString);

    /**
     * @brief Get the @c std::string for the inverse hyperbolic cotangent
     * function.
     *
     * Return the @c std::string for the inverse hyperbolic cotangent function.
     *
     * @return The @c std::string for the inverse hyperbolic cotangent function.
     */
    std::string acothFunctionString() const;

    /**
     * @brief Set the @c std::string for the inverse hyperbolic cotangent
     * function.
     *
     * Set this @c std::string for the inverse hyperbolic cotangent function.
     *
     * @param eqString The @c std::string to use for the inverse hyperbolic
     * cotangent function.
     */
    void setAcothFunctionString(const std::string &acothFunctionString);

    // Miscellaneous

    std::string beginCommentString() const;
    void setBeginCommentString(const std::string &beginCommentString);

    std::string endCommentString() const;
    void setEndCommentString(const std::string &endCommentString);

    /**
     * @brief Get the @c std::string for some header.
     *
     * Return the @c std::string for some header.
     *
     * @return The @c std::string for some header.
     */
    std::string headerString() const;

    /**
     * @brief Set the @c std::string for some header.
     *
     * Set this @c std::string for some header.
     *
     * @param eqString The @c std::string to use for some header.
     */
    void setHeaderString(const std::string &headerString);

    std::string versionString() const;
    void setVersionString(const std::string &versionString);

    /**
     * @brief Get the @c std::string for the name of the variable of
     * integration.
     *
     * Return the @c std::string for the name of the variable of integration.
     *
     * @return The @c std::string for the name of the variable of integration.
     */
    std::string variableOfIntegrationString() const;

    /**
     * @brief Set the @c std::string for the name of the variable of
     * integration.
     *
     * Set this @c std::string for the name of the variable of integration.
     *
     * @param eqString The @c std::string to use for the name of the variable of
     * integration.
     */
    void setVariableOfIntegrationString(const std::string &variableOfIntegrationString);

    /**
     * @brief Get the @c std::string for the name of the states array.
     *
     * Return the @c std::string for the name of the states array.
     *
     * @return The @c std::string for the name of the states array.
     */
    std::string statesArrayString() const;

    /**
     * @brief Set the @c std::string for the name of the states array.
     *
     * Set this @c std::string for the name of the states array.
     *
     * @param eqString The @c std::string to use for the name of the states
     * array.
     */
    void setStatesArrayString(const std::string &statesArrayString);

    /**
     * @brief Get the @c std::string for the name of the rates array.
     *
     * Return the @c std::string for the name of the rates array.
     *
     * @return The @c std::string for the name of the rates array.
     */
    std::string ratesArrayString() const;

    /**
     * @brief Set the @c std::string for the name of the rates array.
     *
     * Set this @c std::string for the name of the rates array.
     *
     * @param eqString The @c std::string to use for the name of the rates
     * array.
     */
    void setRatesArrayString(const std::string &ratesArrayString);

    /**
     * @brief Get the @c std::string for the name of the variables array.
     *
     * Return the @c std::string for the name of the variables array.
     *
     * @return The @c std::string for the name of the variables array.
     */
    std::string variablesArrayString() const;

    /**
     * @brief Set the @c std::string for the name of the variables array.
     *
     * Set this @c std::string for the name of the variables array.
     *
     * @param eqString The @c std::string to use for the name of the variables
     * array.
     */
    void setVariablesArrayString(const std::string &variablesArrayString);

    std::string beginCreateStatesArrayMethodString() const;
    void setBeginCreateStatesArrayMethodString(const std::string &beginCreateStatesArrayMethodString);
    std::string endCreateStatesArrayMethodString() const;
    void setEndCreateStatesArrayMethodString(const std::string &endCreateStatesArrayMethodString);

    std::string beginCreateVariablesArrayMethodString() const;
    void setBeginCreateVariablesArrayMethodString(const std::string &beginCreateVariablesArrayMethodString);
    std::string endCreateVariablesArrayMethodString() const;
    void setEndCreateVariablesArrayMethodString(const std::string &endCreateVariablesArrayMethodString);

    std::string deleteArrayMethodString() const;
    void setDeleteArrayMethodString(const std::string &deleteArrayMethodString);

    /**
     * @brief Get the @c std::string for the beginning of the method that
     * initialises constants.
     *
     * Return the @c std::string for the beginning of the method that
     * initialises constants.
     *
     * @return The @c std::string for the beginning of the method that
     * initialises constants.
     */
    std::string beginInitializeConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the beginning of the method that
     * initialises constants.
     *
     * Set this @c std::string for the beginning of the method that initialises
     * constants.
     *
     * @param eqString The @c std::string to use for the beginning of the method
     * that initialises constants.
     */
    void setBeginInitializeConstantsMethodString(const std::string &beginInitializeConstantsMethodString);

    /**
     * @brief Get the @c std::string for the end of the method that initialises
     * constants.
     *
     * Return the @c std::string for the end of the method that initialises
     * constants.
     *
     * @return The @c std::string for the end of the method that initialises
     * constants.
     */
    std::string endInitializeConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the end of the method that initialises
     * constants.
     *
     * Set this @c std::string for the end of the method that initialises
     * constants.
     *
     * @param eqString The @c std::string to use for the end of the method that
     * initialises constants.
     */
    void setEndInitializeConstantsMethodString(const std::string &endInitializeConstantsMethodString);

    /**
     * @brief Get the @c std::string for the beginning of the method that
     * computes computed constants.
     *
     * Return the @c std::string for the beginning of the method that computes
     * computed constants.
     *
     * @return The @c std::string for the beginning of the method that computes
     * computed constants.
     */
    std::string beginComputeComputedConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the beginning of the method that
     * computes computed constants.
     *
     * Set this @c std::string for the beginning of the method that computes
     * computed constants.
     *
     * @param eqString The @c std::string to use for the beginning of the method
     * that computes computed constants.
     */
    void setBeginComputeComputedConstantsMethodString(const std::string &beginComputeComputedConstantsMethodString);

    /**
     * @brief Get the @c std::string for the end of the method that computes
     * computed constants.
     *
     * Return the @c std::string for the end of the method that computes
     * computed constants.
     *
     * @return The @c std::string for the end of the method that computes
     * computed constants.
     */
    std::string endComputeComputedConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the end of the method that computes
     * computed constants.
     *
     * Set this @c std::string for the end of the method that computes computed
     * constants.
     *
     * @param eqString The @c std::string to use for the end of the method that
     * computes computed constants.
     */
    void setEndComputeComputedConstantsMethodString(const std::string &endComputeComputedConstantsMethodString);

    /**
     * @brief Get the @c std::string for the beginning of the method that
     * computes rates.
     *
     * Return the @c std::string for the beginning of the method that computes
     * rates.
     *
     * @return The @c std::string for the beginning of the method that computes
     * rates.
     */
    std::string beginComputeRatesMethodString() const;

    /**
     * @brief Set the @c std::string for the beginning of the method that
     * computes rates.
     *
     * Set this @c std::string for the beginning of the method that computes
     * rates.
     *
     * @param eqString The @c std::string to use for the beginning of the method
     * that computes rates.
     */
    void setBeginComputeRatesMethodString(const std::string &beginComputeRatesMethodString);

    /**
     * @brief Get the @c std::string for the end of the method that computes
     * rates.
     *
     * Return the @c std::string for the end of the method that computes rates.
     *
     * @return The @c std::string for the end of the method that computes rates.
     */
    std::string endComputeRatesMethodString() const;

    /**
     * @brief Set the @c std::string for the end of the method that computes
     * rates.
     *
     * Set this @c std::string for the end of the method that computes rates.
     *
     * @param eqString The @c std::string to use for the end of the method that
     * computes rates.
     */
    void setEndComputeRatesMethodString(const std::string &endComputeRatesMethodString);

    /**
     * @brief Get the @c std::string for the beginning of the method that
     * computes variables.
     *
     * Return the @c std::string for the beginning of the method that computes
     * variables.
     *
     * @return The @c std::string for the beginning of the method that computes
     * variables.
     */
    std::string beginComputeVariablesMethodString() const;

    /**
     * @brief Set the @c std::string for the beginning of the method that
     * computes variables.
     *
     * Set this @c std::string for the beginning of the method that computes
     * variables.
     *
     * @param eqString The @c std::string to use for the beginning of the method
     * that computes variables.
     */
    void setBeginComputeVariablesMethodString(const std::string &beginComputeVariablesMethodString);

    /**
     * @brief Get the @c std::string for the end of the method that computes
     * variables.
     *
     * Return the @c std::string for the end of the method that computes
     * variables.
     *
     * @return The @c std::string for the end of the method that computes
     * variables.
     */
    std::string endComputeVariablesMethodString() const;

    /**
     * @brief Set the @c std::string for the end of the method that computes
     * variables.
     *
     * Set this @c std::string for the end of the method that computes
     * variables.
     *
     * @param eqString The @c std::string to use for the end of the method that
     * computes variables.
     */
    void setEndComputeVariablesMethodString(const std::string &endComputeVariablesMethodString);

    /**
     * @brief Get the @c std::string for an empty method.
     *
     * Return the @c std::string for an empty method.
     *
     * @return The @c std::string for an empty method.
     */
    std::string emptyMethodString() const;

    /**
     * @brief Set the @c std::string for an empty method.
     *
     * Set this @c std::string for an empty method.
     *
     * @param eqString The @c std::string to use for an empty method.
     */
    void setEmptyMethodString(const std::string &emptyMethodString);

    std::string templateReplacementString() const;
    void setTemplateReplacementString(const std::string &templateReplacementString);

    std::string templateReturnCreatedArrayString() const;
    void setTemplateReturnCreatedArrayString(const std::string &templateReturnCreatedArrayString);

    std::string templateStateVectorSizeConstantString() const;
    void setTemplateStateVectorSizeConstantString(const std::string &templateStateVectorSizeConstantString);

    std::string templateVariableVectorSizeConstantString() const;
    void setTemplateVariableVectorSizeConstantString(const std::string &templateVariableVectorSizeConstantString);

    std::string templateVoiConstantString() const;
    void setTemplateVoiConstantString(const std::string &templateVoiConstantString);

    std::string templateOriginCommentString() const;
    void setTemplateOriginCommentString(const std::string &templateOriginCommentString);

    std::string templateVariableInformationObjectString() const;
    void setTemplateVariableInformationObjectString(const std::string &templateVariableInformationObjectString);

    std::string templateVariableInformationEntryString() const;
    void setTemplateVariableInformationEntryString(const std::string &templateVariableInformationEntryString);

    std::string beginStateVectorInformationArrayString() const;
    void setBeginStateVectorInformationArrayString(const std::string &beginStateVectorInformationArrayString);

    std::string endStateVectorInformationArrayString() const;
    void setEndStateVectorInformationArrayString(const std::string &endStateVectorInformationArrayString);

    std::string beginVariableVectorInformationArrayString() const;
    void setBeginVariableVectorInformationArrayString(const std::string &beginVariableVectorInformationArrayString);

    std::string endVariableVectorInformationArrayString() const;
    void setEndVariableVectorInformationArrayString(const std::string &endVariableVectorInformationArrayString);

    /**
     * @brief Get the @c std::string for an indent.
     *
     * Return the @c std::string for an indent.
     *
     * @return The @c std::string for an indent.
     */
    std::string indentString() const;

    /**
     * @brief Set the @c std::string for an indent.
     *
     * Set this @c std::string for an indent.
     *
     * @param eqString The @c std::string to use for an indent.
     */
    void setIndentString(const std::string &indentString);

    /**
     * @brief Get the @c std::string for opening an array.
     *
     * Return the @c std::string for opening an array.
     *
     * @return The @c std::string for opening an array.
     */
    std::string openArrayString() const;

    /**
     * @brief Set the @c std::string for opening an array.
     *
     * Set this @c std::string for opening an array.
     *
     * @param eqString The @c std::string to use for opening an array.
     */
    void setOpenArrayString(const std::string &openArrayString);

    /**
     * @brief Get the @c std::string for closing an array.
     *
     * Return the @c std::string for closing an array.
     *
     * @return The @c std::string for closing an array.
     */
    std::string closeArrayString() const;

    /**
     * @brief Set the @c std::string for closing an array.
     *
     * Set this @c std::string for closing an array.
     *
     * @param eqString The @c std::string to use for closing an array.
     */
    void setCloseArrayString(const std::string &closeArrayString);

    std::string arrayElementSeparatorString() const;
    void setArrayElementSeparatorString(const std::string &arrayElementSeparatorString);

    /**
     * @brief Get the @c std::string for a command separator.
     *
     * Return the @c std::string for a command separator.
     *
     * @return The @c std::string for a command separator.
     */
    std::string commandSeparatorString() const;

    /**
     * @brief Set the @c std::string for a command separator.
     *
     * Set this @c std::string for a command separator.
     *
     * @param eqString The @c std::string to use for a command separator.
     */
    void setCommandSeparatorString(const std::string &commandSeparatorString);

private:
    void swap(GeneratorProfile &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorProfileImpl;
    GeneratorProfileImpl *mPimpl;
};

} // namespace libcellml
