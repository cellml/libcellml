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
        CUSTOM
    };

    explicit GeneratorProfile(Profile profile = Profile::C); /**< Constructor */
    ~GeneratorProfile(); /**< Destructor */
    GeneratorProfile(const GeneratorProfile &rhs); /**< Copy constructor */
    GeneratorProfile(GeneratorProfile &&rhs) noexcept; /**< Move constructor */
    GeneratorProfile &operator=(GeneratorProfile rhs); /**< Assignment operator */

    // Whether the profile is official.

    /**
     * @brief Get the @c Profile for this @c GeneratorProfile.
     *
     * Return the @c Profile for this @c GeneratorProfile.
     *
     * @return The @c Profile for this @c GeneratorProfile.
     */
    Profile profile() const;

    /**
     * @brief Set the @c Profile.
     *
     * Set this @c GeneratorProfile to the given @c Profile .
     *
     * @param profile The @c Profile to use.
     */
    void setProfile(Profile profile);

    // Whether the profile requires an interface to be generated.

    /**
     * @brief Test if this @c GeneratorProfile requires an interface to be
     * generated.
     *
     * Test if this @c GeneratorProfile has an requires an interface to be
     * generated.
     *
     * @return @c true if the @c GeneratorProfile has an requires an interface
     * to be generated,
     * @c false otherwise.
     */
    bool hasInterface() const;

    /**
     * @brief Set whether this @c GeneratorProfile has an requires an interface
     * to be generated.
     *
     * Set whether this @c GeneratorProfile has an requires an interface to be
     * generated.
     *
     * @param hasInterface A @c bool to determine whether this
     * @c GeneratorProfile has an requires an interface to be generated.
     */
    void setHasInterface(bool hasInterface);

    // Assignment.

    /**
     * @brief Get the @c std::string for the assignment operator.
     *
     * Return the @c std::string for the assignment operator.
     *
     * @return The @c std::string for the assignment operator.
     */
    std::string assignmentString() const;

    /**
     * @brief Set the @c std::string for the assignment operator.
     *
     * Set this @c std::string for the assignment operator.
     *
     * @param assignmentString The @c std::string to use for the assignment
     * operator.
     */
    void setAssignmentString(const std::string &assignmentString);

    // Relational and logical operators.

    /**
     * @brief Get the @c std::string for the equivalence operator.
     *
     * Return the @c std::string for the equivalence operator.
     *
     * @return The @c std::string for the equivalence operator.
     */
    std::string eqString() const;

    /**
     * @brief Set the @c std::string for the equivalence operator.
     *
     * Set this @c std::string for the equivalence operator.
     *
     * @param eqString The @c std::string to use for the equivalence operator.
     */
    void setEqString(const std::string &eqString);

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
     * @param neqString The @c std::string to use for the nonequivalence
     * operator.
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
     * @param ltString The @c std::string to use for the lower than operator.
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
     * @param leqString The @c std::string to use for the lower or equal than
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
     * @param gtString The @c std::string to use for the greater than operator.
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
     * @param geqString The @c std::string to use for the greater or equal than
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
     * @param andString The @c std::string to use for the and operator.
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
     * @param orString The @c std::string to use for the or operator.
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
     * @param xorString The @c std::string to use for the xor operator.
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
     * @param notString The @c std::string to use for the not operator.
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
    bool hasEqOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has an equivalence operator.
     *
     * Set whether this @c GeneratorProfile has an equivalence operator.
     *
     * @param hasEqOperator A @c bool to determine whether this
     * @c GeneratorProfile has an equivalence operator.
     */
    void setHasEqOperator(bool hasEqOperator);

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

    // Arithmetic operators.

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
     * @param plusString The @c std::string to use for an addition.
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
     * @param minusString The @c std::string to use for a subtraction.
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
     * @param timesString The @c std::string to use for a multiplication.
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
     * @param divideString The @c std::string to use for a division.
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
     * @param powerString The @c std::string to use for a power.
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
     * @param squareRootString The @c std::string to use for a square root.
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
     * @param squareString The @c std::string to use for a square.
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
     * @param absoluteValueString The @c std::string to use for an absolute
     * value.
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
     * @param exponentialString The @c std::string to use for an exponential.
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
     * @param napierianLogarithmString The @c std::string to use for a Napierian
     * logarithm.
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
     * @param commonLogarithmString The @c std::string to use for a common
     * logarithm.
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
     * @param ceilingString The @c std::string to use for a ceiling.
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
     * @param floorString The @c std::string to use for a floor.
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
     * @param minString The @c std::string to use for a minimum.
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
     * @param maxString The @c std::string to use for a maximum.
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
     * @param remString The @c std::string to use for a remainder.
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

    // Trigonometric operators.

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
     * @param sinString The @c std::string to use for sine.
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
     * @param cosString The @c std::string to use for cosine.
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
     * @param tanString The @c std::string to use for tangent.
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
     * @param secString The @c std::string to use for secant.
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
     * @param cscString The @c std::string to use for cosecant.
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
     * @param cotString The @c std::string to use for cotangent.
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
     * @param sinhString The @c std::string to use for hyperbolic sine.
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
     * @param coshString The @c std::string to use for hyperbolic cosine.
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
     * @param tanhString The @c std::string to use for hyperbolic tangent.
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
     * @param sechString The @c std::string to use for hyperbolic secant.
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
     * @param cschString The @c std::string to use for hyperbolic cosecant.
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
     * @param cothString The @c std::string to use for hyperbolic cotangent.
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
     * @param asinString The @c std::string to use for inverse sine.
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
     * @param acosString The @c std::string to use for inverse cosine.
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
     * @param atanString The @c std::string to use for inverse tangent.
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
     * @param asecString The @c std::string to use for inverse secant.
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
     * @param acscString The @c std::string to use for inverse cosecant.
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
     * @param acotString The @c std::string to use for inverse cotangent.
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
     * @param asinhString The @c std::string to use for inverse hyperbolic sine.
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
     * @param acoshString The @c std::string to use for inverse hyperbolic
     * cosine.
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
     * @param atanhString The @c std::string to use for inverse hyperbolic
     * tangent.
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
     * @param asechString The @c std::string to use for inverse hyperbolic
     * secant.
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
     * @param acschString The @c std::string to use for inverse hyperbolic
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
     * @param acothString The @c std::string to use for inverse hyperbolic
     * cotangent.
     */
    void setAcothString(const std::string &acothString);

    // Piecewise statement.

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
     * @param conditionalOperatorIfString The @c std::string to use for the if
     * part of a condition statement.
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
     * @param conditionalOperatorElseString The @c std::string to use for the
     * else part of a condition statement.
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
     * @param piecewiseIfString The @c std::string to use for the if part of a
     * piecewise statement.
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
     * @param piecewiseElseString The @c std::string to use for the else part of
     * a piecewise statement.
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

    // Constants.

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
     * @param trueString The @c std::string to use for true.
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
     * @param falseString The @c std::string to use for false.
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
     * @param eString The @c std::string to use for exponential constant.
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
     * @param piString The @c std::string to use for π.
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
     * @param infString The @c std::string to use for infinity.
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
     * @param nanString The @c std::string to use for NaN.
     */
    void setNanString(const std::string &nanString);

    // Mathematical functions.

    /**
     * @brief Get the @c std::string for the interface of the equivalence
     * function.
     *
     * Return the @c std::string for the interface of the equivalence function.
     *
     * @return The @c std::string for the interface of the equivalence function.
     */
    std::string interfaceEqFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the equivalence
     * function.
     *
     * Set this @c std::string for the interface of the equivalence function.
     *
     * @param interfaceEqFunctionString The @c std::string to use for the
     * interface of the equivalence function.
     */
    void setInterfaceEqFunctionString(const std::string &interfaceEqFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the equivalence
     * function.
     *
     * Return the @c std::string for the implementation of the equivalence
     * function.
     *
     * @return The @c std::string for the implementation of the equivalence
     * function.
     */
    std::string implementationEqFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the equivalence
     * function.
     *
     * Set this @c std::string for the implementation of the equivalence
     * function.
     *
     * @param implementationEqFunctionString The @c std::string to use for
     * the implementation of the equivalence function.
     */
    void setImplementationEqFunctionString(const std::string &implementationEqFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the nonequivalence
     * function.
     *
     * Return the @c std::string for the interface of the nonequivalence
     * function.
     *
     * @return The @c std::string for the interface of the nonequivalence
     * function.
     */
    std::string interfaceNeqFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the nonequivalence
     * function.
     *
     * Set this @c std::string for the interface of the nonequivalence function.
     *
     * @param interfaceNeqFunctionString The @c std::string to use for the
     * interface of the nonequivalence function.
     */
    void setInterfaceNeqFunctionString(const std::string &interfaceNeqFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the
     * nonequivalence function.
     *
     * Return the @c std::string for the implementation of the nonequivalence
     * function.
     *
     * @return The @c std::string for the implementation of the nonequivalence
     * function.
     */
    std::string implementationNeqFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the
     * nonequivalence function.
     *
     * Set this @c std::string for the implementation of the nonequivalence
     * function.
     *
     * @param implementationNeqFunctionString The @c std::string to use for the
     * implementation of the nonequivalence function.
     */
    void setImplementationNeqFunctionString(const std::string &implementationNeqFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the lower than
     * function.
     *
     * Return the @c std::string for the interface of the lower than function.
     *
     * @return The @c std::string for the interface of the lower than function.
     */
    std::string interfaceLtFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the lower than function.
     *
     * Set this @c std::string for the interface of the lower than function.
     *
     * @param interfaceLtFunctionString The @c std::string to use for the
     * interface of the lower than function.
     */
    void setInterfaceLtFunctionString(const std::string &interfaceLtFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the lower than
     * function.
     *
     * Return the @c std::string for the implementation of the lower than
     * function.
     *
     * @return The @c std::string for the implementation of the lower than
     * function.
     */
    std::string implementationLtFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the lower than
     * function.
     *
     * Set this @c std::string for the implementation of the lower than
     * function.
     *
     * @param implementationLtFunctionString The @c std::string to use for the
     * implementation of the lower than function.
     */
    void setImplementationLtFunctionString(const std::string &implementationLtFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the lower or equal
     * than function.
     *
     * Return the @c std::string for the interface of the lower or equal than
     * function.
     *
     * @return The @c std::string for the interface of the lower or equal than
     * function.
     */
    std::string interfaceLeqFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the lower or equal
     * than function.
     *
     * Set this @c std::string for the interface of the lower or equal than
     * function.
     *
     * @param interfaceLeqFunctionString The @c std::string to use for the
     * interface of the lower or equal than function.
     */
    void setInterfaceLeqFunctionString(const std::string &interfaceLeqFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the lower or
     * equal than function.
     *
     * Return the @c std::string for the implementation of the lower or equal
     * than function.
     *
     * @return The @c std::string for the implementation of the lower or equal
     * than function.
     */
    std::string implementationLeqFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the lower or
     * equal than function.
     *
     * Set this @c std::string for the implementation of the lower or equal than
     * function.
     *
     * @param implementationLeqFunctionString The @c std::string to use for the
     * implementation of the lower or equal than function.
     */
    void setImplementationLeqFunctionString(const std::string &implementationLeqFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the greater than
     * function.
     *
     * Return the @c std::string for the interface of the greater than function.
     *
     * @return The @c std::string for the interface of the greater than
     * function.
     */
    std::string interfaceGtFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the greater than
     * function.
     *
     * Set this @c std::string for the interface of the greater than function.
     *
     * @param interfaceGtFunctionString The @c std::string to use for the
     * interface of the greater than function.
     */
    void setInterfaceGtFunctionString(const std::string &interfaceGtFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the greater than
     * function.
     *
     * Return the @c std::string for the implementation of the greater than
     * function.
     *
     * @return The @c std::string for the implementation of the greater than
     * function.
     */
    std::string implementationGtFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the greater than
     * function.
     *
     * Set this @c std::string for the implementation of the greater than
     * function.
     *
     * @param implementationGtFunctionString The @c std::string to use for the
     * implementation of the greater than function.
     */
    void setImplementationGtFunctionString(const std::string &implementationGtFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the greater or equal
     *  than function.
     *
     * Return the @c std::string for the interface of the greater or equal than
     * function.
     *
     * @return The @c std::string for the interface of the greater or equal than
     * function.
     */
    std::string interfaceGeqFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the greater or equal
     * than function.
     *
     * Set this @c std::string for the interface of the greater or equal than
     * function.
     *
     * @param interfaceGeqFunctionString The @c std::string to use for the
     * interface of the greater or equal than function.
     */
    void setInterfaceGeqFunctionString(const std::string &interfaceGeqFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the greater or
     * equal than function.
     *
     * Return the @c std::string for the implementation of the greater or equal
     * than function.
     *
     * @return The @c std::string for the implementation of the greater or equal
     * than function.
     */
    std::string implementationGeqFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the greater or
     * equal than function.
     *
     * Set this @c std::string for the implementation of the greater or equal
     * than function.
     *
     * @param implementationGeqFunctionString The @c std::string to use for the
     * implementation of the greater or equal than function.
     */
    void setImplementationGeqFunctionString(const std::string &implementationGeqFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the and function.
     *
     * Return the @c std::string for the interface of the and function.
     *
     * @return The @c std::string for the interface of the and function.
     */
    std::string interfaceAndFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the and function.
     *
     * Set this @c std::string for the interface of the and function.
     *
     * @param interfaceAndFunctionString The @c std::string to use for the
     * interface of the and function.
     */
    void setInterfaceAndFunctionString(const std::string &interfaceAndFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the and function.
     *
     * Return the @c std::string for the implementation of the and function.
     *
     * @return The @c std::string for the implementation of the and function.
     */
    std::string implementationAndFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the and function.
     *
     * Set this @c std::string for the implementation of the and function.
     *
     * @param implementationAndFunctionString The @c std::string to use for the
     * implementation of the and function.
     */
    void setImplementationAndFunctionString(const std::string &implementationAndFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the or function.
     *
     * Return the @c std::string for the interface of the or function.
     *
     * @return The @c std::string for the interface of the or function.
     */
    std::string interfaceOrFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the or function.
     *
     * Set this @c std::string for the interface of the or function.
     *
     * @param interfaceOrFunctionString The @c std::string to use for the
     * interface of the or function.
     */
    void setInterfaceOrFunctionString(const std::string &interfaceOrFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the or function.
     *
     * Return the @c std::string the implementation of the the or function.
     *
     * @return The @c std::string for the implementation of the or function.
     */
    std::string implementationOrFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the or function.
     *
     * Set this @c std::string for the implementation of the or function.
     *
     * @param implementationOrFunctionString The @c std::string to use for the
     * implementation of the or function.
     */
    void setImplementationOrFunctionString(const std::string &implementationOrFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the xor function.
     *
     * Return the @c std::string for the interface of the xor function.
     *
     * @return The @c std::string for the interface of the xor function.
     */
    std::string interfaceXorFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the xor function.
     *
     * Set this @c std::string for the interface of the xor function.
     *
     * @param interfaceXorFunctionString The @c std::string to use for the
     * interface of the xor function.
     */
    void setInterfaceXorFunctionString(const std::string &interfaceXorFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the xor function.
     *
     * Return the @c std::string for the implementation of the xor function.
     *
     * @return The @c std::string for the implementation of the xor function.
     */
    std::string implementationXorFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the xor function.
     *
     * Set this @c std::string for the implementation of the xor function.
     *
     * @param implementationXorFunctionString The @c std::string to use for the
     * implementation of the xor function.
     */
    void setImplementationXorFunctionString(const std::string &implementationXorFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the not function.
     *
     * Return the @c std::string for the interface of the not function.
     *
     * @return The @c std::string for the interface of the not function.
     */
    std::string interfaceNotFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the not function.
     *
     * Set this @c std::string for the interface of the not function.
     *
     * @param interfaceNotFunctionString The @c std::string to use for the
     * interface of the not function.
     */
    void setInterfaceNotFunctionString(const std::string &interfaceNotFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the not function.
     *
     * Return the @c std::string for the implementation of the not function.
     *
     * @return The @c std::string for the implementation of the not function.
     */
    std::string implementationNotFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the not function.
     *
     * Set this @c std::string for the implementation of the not function.
     *
     * @param implementationNotFunctionString The @c std::string to use for the
     * implementation of the not function.
     */
    void setImplementationNotFunctionString(const std::string &implementationNotFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the minimum function.
     *
     * Return the @c std::string for the interface of the minimum function.
     *
     * @return The @c std::string for the interface of the minimum function.
     */
    std::string interfaceMinFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the minimum function.
     *
     * Set this @c std::string for the interface of the minimum function.
     *
     * @param interfaceMinFunctionString The @c std::string to use for the
     * interface of the minimum function.
     */
    void setInterfaceMinFunctionString(const std::string &interfaceMinFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the minimum
     * function.
     *
     * Return the @c std::string for the implementation of the minimum function.
     *
     * @return The @c std::string for the implementation of the minimum
     * function.
     */
    std::string implementationMinFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the minimum
     * function.
     *
     * Set this @c std::string for the implementation of the minimum function.
     *
     * @param implementationMinFunctionString The @c std::string to use for the
     * implementation of the minimum function.
     */
    void setImplementationMinFunctionString(const std::string &implementationMinFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the maximum function.
     *
     * Return the @c std::string for the interface of the maximum function.
     *
     * @return The @c std::string for the interface of the maximum function.
     */
    std::string interfaceMaxFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the maximum function.
     *
     * Set this @c std::string for the interface of the maximum function.
     *
     * @param interfaceMaxFunctionString The @c std::string to use for the
     * interface of the maximum function.
     */
    void setInterfaceMaxFunctionString(const std::string &interfaceMaxFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the maximum function.
     *
     * Return the @c std::string for the implementation of the maximum function.
     *
     * @return The @c std::string for the implementation of the maximum function.
     */
    std::string implementationMaxFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the maximum
     * function.
     *
     * Set this @c std::string for the implementation of the maximum function.
     *
     * @param implementationMaxFunctionString The @c std::string to use for the
     * implementation of the maximum function.
     */
    void setImplementationMaxFunctionString(const std::string &implementationMaxFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the secant function.
     *
     * Return the @c std::string for the interface of the secant function.
     *
     * @return The @c std::string for the interface of the secant function.
     */
    std::string interfaceSecFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the secant function.
     *
     * Set this @c std::string for the interface of the secant function.
     *
     * @param interfaceSecFunctionString The @c std::string to use for the
     * interface of the secant function.
     */
    void setInterfaceSecFunctionString(const std::string &interfaceSecFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the secant
     * function.
     *
     * Return the @c std::string for the implementation of the secant function.
     *
     * @return The @c std::string for the implementation of the secant function.
     */
    std::string implementationSecFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the secant
     * function.
     *
     * Set this @c std::string for the implementation of the secant function.
     *
     * @param implementationSecFunctionString The @c std::string to use for the
     * implementation of the secant function.
     */
    void setImplementationSecFunctionString(const std::string &implementationSecFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the cosecant function.
     *
     * Return the @c std::string for the interface of the cosecant function.
     *
     * @return The @c std::string for the interface of the cosecant function.
     */
    std::string interfaceCscFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the cosecant function.
     *
     * Set this @c std::string for the interface of the cosecant function.
     *
     * @param interfaceCscFunctionString The @c std::string to use for the
     * interface of the cosecant function.
     */
    void setInterfaceCscFunctionString(const std::string &interfaceCscFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the cosecant
     * function.
     *
     * Return the @c std::string for the implementation of the cosecant
     * function.
     *
     * @return The @c std::string for the implementation of the cosecant
     * function.
     */
    std::string implementationCscFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the cosecant
     * function.
     *
     * Set this @c std::string for the implementation of the cosecant function.
     *
     * @param implementationCscFunctionString The @c std::string to use for the
     * implementation of the cosecant function.
     */
    void setImplementationCscFunctionString(const std::string &implementationCscFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the cotangent
     * function.
     *
     * Return the @c std::string for the interface of the cotangent function.
     *
     * @return The @c std::string for the interface of the cotangent function.
     */
    std::string interfaceCotFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the cotangent
     * function.
     *
     * Set this @c std::string for the interface of the cotangent function.
     *
     * @param interfaceCotFunctionString The @c std::string to use for the
     * interface of the cotangent function.
     */
    void setInterfaceCotFunctionString(const std::string &interfaceCotFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the cotangent
     * function.
     *
     * Return the @c std::string for the implementation of the cotangent
     * function.
     *
     * @return The @c std::string for the implementation of the cotangent
     * function.
     */
    std::string implementationCotFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the cotangent
     * function.
     *
     * Set this @c std::string for the implementation of the cotangent
     * function.
     *
     * @param implementationCotFunctionString The @c std::string to use for the
     * implementation of the cotangent function.
     */
    void setImplementationCotFunctionString(const std::string &implementationCotFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the hyperbolic secant
     * function.
     *
     * Return the @c std::string for the interface of the hyperbolic secant
     * function.
     *
     * @return The @c std::string for the interface of the hyperbolic secant
     * function.
     */
    std::string interfaceSechFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the hyperbolic secant
     * function.
     *
     * Set this @c std::string for the interface of the hyperbolic secant
     * function.
     *
     * @param interfaceSechFunctionString The @c std::string to use for the
     * interface of the hyperbolic secant function.
     */
    void setInterfaceSechFunctionString(const std::string &interfaceSechFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the hyperbolic
     * secant function.
     *
     * Return the @c std::string for the implementation of the hyperbolic secant
     * function.
     *
     * @return The @c std::string for the implementation of the hyperbolic
     * secant function.
     */
    std::string implementationSechFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the hyperbolic
     * secant function.
     *
     * Set this @c std::string for the implementation of the hyperbolic secant
     * function.
     *
     * @param implementationSechFunctionString The @c std::string to use for the
     * implementation of the hyperbolic secant function.
     */
    void setImplementationSechFunctionString(const std::string &implementationSechFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the hyperbolic
     * cosecant function.
     *
     * Return the @c std::string for the interface of the hyperbolic cosecant
     * function.
     *
     * @return The @c std::string for the interface of the hyperbolic cosecant
     * function.
     */
    std::string interfaceCschFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the hyperbolic
     * cosecant function.
     *
     * Set this @c std::string for the interface of the hyperbolic cosecant
     * function.
     *
     * @param interfaceCschFunctionString The @c std::string to use for the
     * interface of the hyperbolic cosecant function.
     */
    void setInterfaceCschFunctionString(const std::string &interfaceCschFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the hyperbolic
     * cosecant function.
     *
     * Return the @c std::string for the implementation of the hyperbolic
     * cosecant function.
     *
     * @return The @c std::string for the implementation of the hyperbolic
     * cosecant function.
     */
    std::string implementationCschFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the hyperbolic
     * cosecant function.
     *
     * Set this @c std::string for the implementation of the hyperbolic cosecant
     * function.
     *
     * @param implementationCschFunctionString The @c std::string to use for the
     * implementation of the hyperbolic cosecant function.
     */
    void setImplementationCschFunctionString(const std::string &implementationCschFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the hyperbolic
     * cotangent function.
     *
     * Return the @c std::string for the interface of the hyperbolic cotangent
     * function.
     *
     * @return The @c std::string for the interface of the hyperbolic cotangent
     * function.
     */
    std::string interfaceCothFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the hyperbolic
     * cotangent function.
     *
     * Set this @c std::string for the interface of the hyperbolic cotangent
     * function.
     *
     * @param interfaceCothFunctionString The @c std::string to use for the
     * interface of the hyperbolic cotangent function.
     */
    void setInterfaceCothFunctionString(const std::string &interfaceCothFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the hyperbolic
     * cotangent function.
     *
     * Return the @c std::string for the implementation of the hyperbolic
     * cotangent function.
     *
     * @return The @c std::string for the implementation of the hyperbolic
     * cotangent function.
     */
    std::string implementationCothFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the hyperbolic
     * cotangent function.
     *
     * Set this @c std::string for the implementation of the hyperbolic
     * cotangent function.
     *
     * @param implementationCothFunctionString The @c std::string to use for the
     * implementation of the hyperbolic cotangent function.
     */
    void setImplementationCothFunctionString(const std::string &implementationCothFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the inverse secant
     * function.
     *
     * Return the @c std::string for the interface of the inverse secant
     * function.
     *
     * @return The @c std::string for the interface of the inverse secant
     * function.
     */
    std::string interfaceAsecFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the inverse secant
     * function.
     *
     * Set this @c std::string for the interface of the inverse secant function.
     *
     * @param interfaceAsecFunctionString The @c std::string to use for the
     * interface of the inverse secant function.
     */
    void setInterfaceAsecFunctionString(const std::string &interfaceAsecFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the inverse
     * secant function.
     *
     * Return the @c std::string for the implementation of the inverse secant
     * function.
     *
     * @return The @c std::string for the implementation of the inverse secant
     * function.
     */
    std::string implementationAsecFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the inverse
     * secant function.
     *
     * Set this @c std::string for the implementation of the inverse secant
     * function.
     *
     * @param implementationAsecFunctionString The @c std::string to use for the
     * implementation of the inverse secant function.
     */
    void setImplementationAsecFunctionString(const std::string &implementationAsecFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the inverse cosecant
     * function.
     *
     * Return the @c std::string for the interface of the inverse cosecant
     * function.
     *
     * @return The @c std::string for the interface of the inverse cosecant
     * function.
     */
    std::string interfaceAcscFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the inverse cosecant
     * function.
     *
     * Set this @c std::string for the interface of the inverse cosecant
     * function.
     *
     * @param interfaceAcscFunctionString The @c std::string to use for the
     * interface of the inverse cosecant function.
     */
    void setInterfaceAcscFunctionString(const std::string &interfaceAcscFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the inverse
     * cosecant function.
     *
     * Return the @c std::string for the implementation of the inverse cosecant
     * function.
     *
     * @return The @c std::string for the implementation of the inverse cosecant
     * function.
     */
    std::string implementationAcscFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the inverse
     * cosecant function.
     *
     * Set this @c std::string for the implementation of the inverse cosecant
     * function.
     *
     * @param implementationAcscFunctionString The @c std::string to use for the
     * implementation of the inverse cosecant function.
     */
    void setImplementationAcscFunctionString(const std::string &implementationAcscFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the inverse cotangent
     * function.
     *
     * Return the @c std::string for the interface of the inverse cotangent
     * function.
     *
     * @return The @c std::string for the interface of the inverse cotangent
     * function.
     */
    std::string interfaceAcotFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the inverse cotangent
     * function.
     *
     * Set this @c std::string for the interface of the inverse cotangent
     * function.
     *
     * @param interfaceAcotFunctionString The @c std::string to use for the
     * interface of the inverse cotangent function.
     */
    void setInterfaceAcotFunctionString(const std::string &interfaceAcotFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the inverse
     * cotangent function.
     *
     * Return the @c std::string for the implementation of the inverse cotangent
     * function.
     *
     * @return The @c std::string for the implementation of the inverse
     * cotangent function.
     */
    std::string implementationAcotFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the inverse
     * cotangent function.
     *
     * Set this @c std::string for the implementation of the inverse cotangent
     * function.
     *
     * @param implementationAcotFunctionString The @c std::string to use for the
     * implementation of the inverse cotangent function.
     */
    void setImplementationAcotFunctionString(const std::string &implementationAcotFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the inverse hyperbolic
     * secant function.
     *
     * Return the @c std::string for the interface of the inverse hyperbolic
     * secant function.
     *
     * @return The @c std::string for the interface of the inverse hyperbolic
     * secant function.
     */
    std::string interfaceAsechFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the inverse hyperbolic
     * secant function.
     *
     * Set this @c std::string for the interface of the inverse hyperbolic
     * secant function.
     *
     * @param interfaceAsechFunctionString The @c std::string to use for the
     * interface of the inverse hyperbolic secant function.
     */
    void setInterfaceAsechFunctionString(const std::string &interfaceAsechFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the inverse
     * hyperbolic secant function.
     *
     * Return the @c std::string for the implementation of the inverse
     * hyperbolic secant function.
     *
     * @return The @c std::string for the implementation of the inverse
     * hyperbolic secant function.
     */
    std::string implementationAsechFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the inverse
     * hyperbolic secant function.
     *
     * Set this @c std::string for the implementation of the inverse hyperbolic
     * secant function.
     *
     * @param implementationAsechFunctionString The @c std::string to use for
     * the implementation of the inverse hyperbolic secant function.
     */
    void setImplementationAsechFunctionString(const std::string &implementationAsechFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the inverse hyperbolic
     * cosecant function.
     *
     * Return the @c std::string for the interface of the inverse hyperbolic
     * cosecant function.
     *
     * @return The @c std::string for the interface of the inverse hyperbolic
     * cosecant function.
     */
    std::string interfaceAcschFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the inverse hyperbolic
     * cosecant function.
     *
     * Set this @c std::string for the interface of the inverse hyperbolic
     * cosecant function.
     *
     * @param interfaceAcschFunctionString The @c std::string to use for the
     * interface of the inverse hyperbolic cosecant function.
     */
    void setInterfaceAcschFunctionString(const std::string &interfaceAcschFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the inverse
     * hyperbolic cosecant function.
     *
     * Return the @c std::string for the implementation of the inverse
     * hyperbolic cosecant function.
     *
     * @return The @c std::string for the implementation of the inverse
     * hyperbolic cosecant function.
     */
    std::string implementationAcschFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the inverse
     * hyperbolic cosecant function.
     *
     * Set this @c std::string for the implementation of the inverse hyperbolic
     * cosecant function.
     *
     * @param implementationAcschFunctionString The @c std::string to use for
     * the implementation of the inverse hyperbolic cosecant function.
     */
    void setImplementationAcschFunctionString(const std::string &implementationAcschFunctionString);

    /**
     * @brief Get the @c std::string for the interface of the inverse hyperbolic
     * cotangent function.
     *
     * Return the @c std::string for the interface of the inverse hyperbolic
     * cotangent function.
     *
     * @return The @c std::string for the interface of the inverse hyperbolic
     * cotangent function.
     */
    std::string interfaceAcothFunctionString() const;

    /**
     * @brief Set the @c std::string for the interface of the inverse hyperbolic
     * cotangent function.
     *
     * Set this @c std::string for the interface of the inverse hyperbolic
     * cotangent function.
     *
     * @param interfaceAcothFunctionString The @c std::string to use for the
     * interface of the inverse hyperbolic cotangent function.
     */
    void setInterfaceAcothFunctionString(const std::string &interfaceAcothFunctionString);

    /**
     * @brief Get the @c std::string for the implementation of the inverse
     * hyperbolic cotangent function.
     *
     * Return the @c std::string for the implementation of the inverse
     * hyperbolic cotangent function.
     *
     * @return The @c std::string for the implementation of the inverse
     * hyperbolic cotangent function.
     */
    std::string implementationAcothFunctionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the inverse
     * hyperbolic cotangent function.
     *
     * Set this @c std::string for the implementation of the inverse hyperbolic
     * cotangent function.
     *
     * @param implementationAcothFunctionString The @c std::string to use for
     * the implementation of the inverse hyperbolic cotangent function.
     */
    void setImplementationAcothFunctionString(const std::string &implementationAcothFunctionString);

    // Miscellaneous.

    /**
     * @brief Get the @c std::string for a comment.
     *
     * Return the @c std::string for a comment.
     *
     * @return The @c std::string for a comment.
     */
    std::string commentString() const;

    /**
     * @brief Set the @c std::string for a comment.
     *
     * Set this @c std::string for a comment. To be useful, the string should
     * contain the <CODE> tag, which will be replaced with a (proper) comment.
     *
     * @param commentString The @c std::string to use for a comment.
     */
    void setCommentString(const std::string &commentString);

    /**
     * @brief Get the @c std::string for an origin comment.
     *
     * Return the @c std::string for an origin comment.
     *
     * @return The @c std::string for an origin comment.
     */
    std::string originCommentString() const;

    /**
     * @brief Set the @c std::string for an origin comment.
     *
     * Set this @c std::string for an origin comment. To be useful, the string
     * should contain the <PROFILE_INFORMATION> and <LIBCELLML_VERSION> tags,
     * which will be replaced with some profile information and the the version
     * of libCellML used.
     *
     * @param originCommentString The @c std::string to use for an origin
     * comment.
     */
    void setOriginCommentString(const std::string &originCommentString);

    /**
     * @brief Get the @c std::string for an interface header.
     *
     * Return the @c std::string for an interface header.
     *
     * @return The @c std::string for an interface header.
     */
    std::string interfaceHeaderString() const;

    /**
     * @brief Set the @c std::string for an interface header.
     *
     * Set this @c std::string for an interface header.
     *
     * @param interfaceHeaderString The @c std::string to use for an interface
     * header.
     */
    void setInterfaceHeaderString(const std::string &interfaceHeaderString);

    /**
     * @brief Get the @c std::string for an implementation header.
     *
     * Return the @c std::string for an implementation header.
     *
     * @return The @c std::string for an implementation header.
     */
    std::string implementationHeaderString() const;

    /**
     * @brief Set the @c std::string for an implementation header.
     *
     * Set this @c std::string for an implementation header.
     *
     * @param implementationHeaderString The @c std::string to use for an
     * implementation header.
     */
    void setImplementationHeaderString(const std::string &implementationHeaderString);

    /**
     * @brief Get the @c std::string for an interface declaration.
     *
     * Return the @c std::string for an interface declaration.
     *
     * @return The @c std::string for an interface declaration.
     */
    std::string interfaceDeclarationString() const;

    /**
     * @brief Set the @c std::string for an interface declaration.
     *
     * Set this @c std::string for an interface declaration. To be useful, the
     * string should contain the <CODE> tag, which will be replaced with the
     * variable/function for which there is an implementation.
     *
     * @param interfaceDeclarationString The @c std::string to use for an
     * interface declaration.
     */
    void setInterfaceDeclarationString(const std::string &interfaceDeclarationString);

    /**
     * @brief Get the @c std::string for the libCellML version constant.
     *
     * Return the @c std::string for the libCellML version constant.
     *
     * @return The @c std::string for the libCellML version constant.
     */
    std::string libcellmlVersionString() const;

    /**
     * @brief Set the @c std::string for the libCellML version constant.
     *
     * Set this @c std::string for the libCellML version constant.
     *
     * @param versionString The @c std::string to use for the libCellML version
     * constant.
     */
    void setLibcellmlVersionString(const std::string &libcellmlVersionString);

    /**
     * @brief Get the @c std::string for the state count constant.
     *
     * Return the @c std::string for the state count constant.
     *
     * @return The @c std::string for the state count constant.
     */
    std::string stateCountString() const;

    /**
     * @brief Set the @c std::string for the state count constant.
     *
     * Set this @c std::string for the state count constant.
     *
     * @param stateCountString The @c std::string to use for the state count
     * constant.
     */
    void setStateCountString(const std::string &stateCountString);

    /**
     * @brief Get the @c std::string for the variable count constant.
     *
     * Return the @c std::string for the variable count constant.
     *
     * @return The @c std::string for the variable count constant.
     */
    std::string variableCountString() const;

    /**
     * @brief Set the @c std::string for the variable count constant.
     *
     * Set this @c std::string for the variable count constant.
     *
     * @param variableCountString The @c std::string to use for the variable
     * count constant.
     */
    void setVariableCountString(const std::string &variableCountString);

    /**
     * @brief Get the @c std::string for the data structure for the variable
     * type object.
     *
     * Return the @c std::string for the data structure for the variable type
     * object.
     *
     * @return The @c std::string for the data structure for the variable type
     * object.
     */
    std::string variableTypeObjectString() const;

    /**
     * @brief Set the @c std::string for the data structure for the variable
     * type object.
     *
     * Set this @c std::string for the data structure for the variable
     * type object.
     *
     * @param variableTypeObjectString The @c std::string to use for the data
     * structure for the variable type object.
     */
    void setVariableTypeObjectString(const std::string &variableTypeObjectString);

    /**
     * @brief Get the @c std::string for the name of the constant variable type.
     *
     * Return the @c std::string for the name of the constant variable type.
     *
     * @return The @c std::string for the name of the constant variable type.
     */
    std::string constantVariableTypeString() const;

    /**
     * @brief Set the @c std::string for the name of the constant variable type.
     *
     * Set this @c std::string for the name of the constant variable type.
     *
     * @param statesArrayString The @c std::string to use for the name of the
     * constant variable type.
     */
    void setConstantVariableTypeString(const std::string &constantVariableTypeString);

    /**
     * @brief Get the @c std::string for the name of the computed constant
     * variable type.
     *
     * Return the @c std::string for the name of the computed constant variable
     * type.
     *
     * @return The @c std::string for the name of the computed constant variable
     * type.
     */
    std::string computedConstantVariableTypeString() const;

    /**
     * @brief Set the @c std::string for the name of the computed constant
     * variable type.
     *
     * Set this @c std::string for the name of the computed constant variable
     * type.
     *
     * @param statesArrayString The @c std::string to use for the name of the
     * computed constant variable type.
     */
    void setComputedConstantVariableTypeString(const std::string &computedConstantVariableTypeString);

    /**
     * @brief Get the @c std::string for the name of the algebraic variable
     * type.
     *
     * Return the @c std::string for the name of the algebraic variable type.
     *
     * @return The @c std::string for the name of the algebraic variable type.
     */
    std::string algebraicVariableTypeString() const;

    /**
     * @brief Set the @c std::string for the name of the algebraic variable
     * type.
     *
     * Set this @c std::string for the name of the algebraic variable type.
     *
     * @param statesArrayString The @c std::string to use for the name of the
     * algebraic variable type.
     */
    void setAlgebraicVariableTypeString(const std::string &algebraicVariableTypeString);

    /**
     * @brief Get the @c std::string for the data structure for the variable
     * information object.
     *
     * Return the @c std::string for the data structure for the variable
     * information object.
     *
     * @return The @c std::string for the data structure for the variable
     * information object.
     */
    std::string variableInfoObjectString() const;

    /**
     * @brief Set the @c std::string for the data structure for the variable
     * information object.
     *
     * Set this @c std::string for the data structure for the variable
     * information object. To be useful, the string should contain the
     * <NAME_SIZE>, <UNITS_SIZE> and <COMPONENT_SIZE> tags, which will be
     * replaced with the maximum size of a string for holding the name of a
     * component, variable and units, respectively.
     *
     * @param variableInfoObjectString The @c std::string to use for the data
     * structure for the variable information object.
     */
    void setVariableInfoObjectString(const std::string &variableInfoObjectString);

    /**
     * @brief Get the @c std::string for the data structure for the variable
     * information (incl. its type) object.
     *
     * Return the @c std::string for the data structure for the variable
     * information (incl. its type) object.
     *
     * @return The @c std::string for the data structure for the variable
     * information (incl. its type) object.
     */
    std::string variableInfoWithTypeObjectString() const;

    /**
     * @brief Set the @c std::string for the data structure for the variable
     * information (incl. its type) object.
     *
     * Set this @c std::string for the data structure for the variable
     * information (incl. its type) object. To be useful, the string should
     * contain the <NAME_SIZE>, <UNITS_SIZE> and <COMPONENT_SIZE> tags, which
     * will be replaced with the maximum size of a string for holding the name
     * of a component, variable and units, respectively.
     *
     * @param variableInfoWithTypeObjectString The @c std::string to use for the
     * data structure for the variable information (incl. its type) object.
     */
    void setVariableInfoWithTypeObjectString(const std::string &variableInfoWithTypeObjectString);

    /**
     * @brief Get the @c std::string for some information about the variable of
     * integration.
     *
     * Return the @c std::string for some information about the variable of
     * integration.
     *
     * @return The @c std::string for some information about the variable of
     * integration.
     */
    std::string voiInfoString() const;

    /**
     * @brief Set the @c std::string for some information about the variable of
     * integration.
     *
     * Set this @c std::string for some information about the variable of
     * integration.
     *
     * @param voiInfoString The @c std::string to use for some information about
     * the variable of integration.
     */
    void setVoiInfoString(const std::string &voiInfoString);

    /**
     * @brief Get the @c std::string for some information about the different
     * states.
     *
     * Return the @c std::string for some information about the different
     * states.
     *
     * @return The @c std::string for some information about the different
     * states.
     */
    std::string stateInfoString() const;

    /**
     * @brief Set the @c std::string for some information about the different
     * states.
     *
     * Set this @c std::string for some information about the different states.
     *
     * @param stateInfoString The @c std::string to use for some information
     * about the different states.
     */
    void setStateInfoString(const std::string &stateInfoString);

    /**
     * @brief Get the @c std::string for some information about the different
     * variables.
     *
     * Return the @c std::string for some information about the different
     * variables.
     *
     * @return The @c std::string for some information about the different
     * variables.
     */
    std::string variableInfoString() const;

    /**
     * @brief Set the @c std::string for some information about the different
     * variables.
     *
     * Set this @c std::string for some information about the different
     * variables.
     *
     * @param variableInfoString The @c std::string to use for some information
     * about the different variables.
     */
    void setVariableInfoString(const std::string &variableInfoString);

    /**
     * @brief Get the @c std::string for an entry in an array for some
     * information about a variable.
     *
     * Return the @c std::string for an entry in an array for some information
     * about a variable.
     *
     * @return The @c std::string for an entry in an array for some information
     * about a variable.
     */
    std::string variableInfoEntryString() const;

    /**
     * @brief Set the @c std::string for an entry in an array for some
     * information about a variable.
     *
     * Set this @c std::string for an entry in an array for some information
     * about a variable. To be useful, the string should contain the
     * <COMPONENT>, <NAME> and <UNITS> tags, which will be replaced with the
     * name of the component, name and units of a variable.
     *
     * @param variableInfoEntryString The @c std::string to use for an entry in
     * an array for some information about a variable.
     */
    void setVariableInfoEntryString(const std::string &variableInfoEntryString);

    /**
     * @brief Get the @c std::string for an entry in an array for some
     * information about a variable (incl. its type).
     *
     * Return the @c std::string for an entry in an array for some information
     * about a variable (incl. its type).
     *
     * @return The @c std::string for an entry in an array for some information
     * about a variable (incl. its type).
     */
    std::string variableInfoWithTypeEntryString() const;

    /**
     * @brief Set the @c std::string for an entry in an array for some
     * information about a variable (incl. its type).
     *
     * Set this @c std::string for an entry in an array for some information
     * about a variable (incl. its type). To be useful, the string should
     * contain the <COMPONENT>, <NAME> and <UNITS> tags, which will be replaced
     * with the name of the component, name and units of a variable.
     *
     * @param variableInfoWithTypeEntryString The @c std::string to use for an
     * entry in an array for some information about a variable (incl. its type).
     */
    void setVariableInfoWithTypeEntryString(const std::string &variableInfoWithTypeEntryString);

    /**
     * @brief Get the @c std::string for the name of the variable of
     * integration.
     *
     * Return the @c std::string for the name of the variable of integration.
     *
     * @return The @c std::string for the name of the variable of integration.
     */
    std::string voiString() const;

    /**
     * @brief Set the @c std::string for the name of the variable of
     * integration.
     *
     * Set this @c std::string for the name of the variable of integration.
     *
     * @param voiString The @c std::string to use for the name of the variable
     * of integration.
     */
    void setVoiString(const std::string &voiString);

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
     * @param statesArrayString The @c std::string to use for the name of the
     * states array.
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
     * @param ratesArrayString The @c std::string to use for the name of the
     * rates array.
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
     * @param variablesArrayString The @c std::string to use for the name of the
     * variables array.
     */
    void setVariablesArrayString(const std::string &variablesArrayString);

    /**
     * @brief Get the @c std::string for returning a created array.
     *
     * Return the @c std::string for returning a created array.
     *
     * @return The @c std::string for returning a created array.
     */
    std::string returnCreatedArrayString() const;

    /**
     * @brief Set the @c std::string for returning a created array.
     *
     * Set this @c std::string for returning a created array. To be useful, the
     * string should contain the <ARRAY_SIZE> tag, which will be replaced with
     * the size of the array to be created.
     *
     * @param returnCreatedArrayString The @c std::string to use for returning
     * a created array.
     */
    void setReturnCreatedArrayString(const std::string &returnCreatedArrayString);

    /**
     * @brief Get the @c std::string for creating the states array.
     *
     * Return the @c std::string for creating the states array.
     *
     * @return The @c std::string for creating the states array.
     */
    std::string createStatesArrayMethodString() const;

    /**
     * @brief Set the @c std::string for creating the states array.
     *
     * Set this @c std::string for creating the states array. To be useful, the
     * string should contain the <CODE> tag, which will be replaced with some
     * code to create the states array.
     *
     * @param createStatesArrayMethodString The @c std::string to use for
     * creating the states array.
     */
    void setCreateStatesArrayMethodString(const std::string &createStatesArrayMethodString);

    /**
     * @brief Get the @c std::string for creating the variables array.
     *
     * Return the @c std::string for creating the variables array.
     *
     * @return The @c std::string for creating the variables array.
     */
    std::string createVariablesArrayMethodString() const;

    /**
     * @brief Set the @c std::string for creating the variables array.
     *
     * Set this @c std::string for creating the variables array. To be useful,
     * the string should contain the <CODE> tag, which will be replaced with
     * some code to create the variables array.
     *
     * @param createVariablesArrayMethodString The @c std::string to use for
     * creating the variables array.
     */
    void setCreateVariablesArrayMethodString(const std::string &createVariablesArrayMethodString);

    /**
     * @brief Get the @c std::string for deleting an array.
     *
     * Return the @c std::string for deleting an array.
     *
     * @return The @c std::string for deleting an array.
     */
    std::string deleteArrayMethodString() const;

    /**
     * @brief Set the @c std::string for deleting an array.
     *
     * Set this @c std::string for deleting an array.
     *
     * @param createVariablesArrayMethodString The @c std::string to use for
     * deleting an array.
     */
    void setDeleteArrayMethodString(const std::string &deleteArrayMethodString);

    /**
     * @brief Get the @c std::string for the method that initialises states and
     * constants.
     *
     * Return the @c std::string for the method that initialises states and
     * constants.
     *
     * @return The @c std::string for the method that initialises states and
     * constants.
     */
    std::string initializeStatesAndConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the method that initialises states and
     * constants.
     *
     * Set this @c std::string for the method that initialises states and
     * constants.
     *
     * @param initializeStatesAndConstantsMethodString The @c std::string to use
     * for the method that initialises states and constants.
     */
    void setInitializeStatesAndConstantsMethodString(const std::string &initializeStatesAndConstantsMethodString);

    /**
     * @brief Get the @c std::string for the method that computes computed
     * constants.
     *
     * Return the @c std::string for the method that computes computed
     * constants.
     *
     * @return The @c std::string for the method that computes computed
     * constants.
     */
    std::string computeComputedConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the method that computes computed
     * constants.
     *
     * Set this @c std::string for the method that computes computed constants.
     *
     * @param computeComputedConstantsMethodString The @c std::string to use for
     * the method that computes computed constants.
     */
    void setComputeComputedConstantsMethodString(const std::string &computeComputedConstantsMethodString);

    /**
     * @brief Get the @c std::string for the method that computes rates.
     *
     * Return the @c std::string for the method that computes rates.
     *
     * @return The @c std::string for the method that computes rates.
     */
    std::string computeRatesMethodString() const;

    /**
     * @brief Set the @c std::string for the method that computes rates.
     *
     * Set this @c std::string for the method that computes rates.
     *
     * @param computeRatesMethodString The @c std::string to use for the method
     * that computes rates.
     */
    void setComputeRatesMethodString(const std::string &computeRatesMethodString);

    /**
     * @brief Get the @c std::string for the method that computes variables.
     *
     * Return the @c std::string for the method that computes variables.
     *
     * @return The @c std::string for the method that computes variables.
     */
    std::string computeVariablesMethodString() const;

    /**
     * @brief Set the @c std::string for the method that computes variables.
     *
     * Set this @c std::string for the method that computes variables.
     *
     * @param computeVariablesMethodString The @c std::string to use for the
     * method that computes variables.
     */
    void setComputeVariablesMethodString(const std::string &computeVariablesMethodString);

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
     * @param emptyMethodString The @c std::string to use for an empty method.
     */
    void setEmptyMethodString(const std::string &emptyMethodString);

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
     * @param indentString The @c std::string to use for an indent.
     */
    void setIndentString(const std::string &indentString);

    /**
     * @brief Get the @c std::string for opening an array initializer.
     *
     * Return the @c std::string for opening an array initializer.
     *
     * @return The @c std::string for opening an array initializer.
     */
    std::string openArrayInitializerString() const;

    /**
     * @brief Set the @c std::string for opening an array initializer.
     *
     * Set this @c std::string for opening an array initializer.
     *
     * @param openArrayInitializerString The @c std::string to use for opening
     * an array initializer.
     */
    void setOpenArrayInitializerString(const std::string &openArrayInitializerString);

    /**
     * @brief Get the @c std::string for closing an array initializer.
     *
     * Return the @c std::string for closing an array initializer.
     *
     * @return The @c std::string for closing an array initializer.
     */
    std::string closeArrayInitializerString() const;

    /**
     * @brief Set the @c std::string for closing an array initializer.
     *
     * Set this @c std::string for closing an array initializer.
     *
     * @param closeArrayInitializerString The @c std::string to use for closing
     *  an array initializer.
     */
    void setCloseArrayInitializerString(const std::string &closeArrayInitializerString);

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
     * @param openArrayString The @c std::string to use for opening an array.
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
     * @param closeArrayString The @c std::string to use for closing an array.
     */
    void setCloseArrayString(const std::string &closeArrayString);

    /**
     * @brief Get the @c std::string for separating elements in an array.
     *
     * Return the @c std::string for separating elements in an array.
     *
     * @return The @c std::string for separating elements in an array.
     */
    std::string arrayElementSeparatorString() const;

    /**
     * @brief Set the @c std::string for separating elements in an array.
     *
     * Set this @c std::string for separating elements in an array.
     *
     * @param arrayElementSeparatorString The @c std::string to use for
     * separating elements in an array.
     */
    void setArrayElementSeparatorString(const std::string &arrayElementSeparatorString);

    /**
     * @brief Get the @c std::string for a string delimiter.
     *
     * Return the @c std::string for a string delimiter.
     *
     * @return The @c std::string for a string delimiter.
     */
    std::string stringDelimiterString() const;

    /**
     * @brief Set the @c std::string for a string delimiter.
     *
     * Set this @c std::string for a string delimiter.
     *
     * @param stringDelimiterString The @c std::string to use for a string
     * delimiter.
     */
    void setStringDelimiterString(const std::string &stringDelimiterString);

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
     * @param commandSeparatorString The @c std::string to use for a command
     * separator.
     */
    void setCommandSeparatorString(const std::string &commandSeparatorString);

private:
    void swap(GeneratorProfile &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorProfileImpl;
    GeneratorProfileImpl *mPimpl;
};

} // namespace libcellml
