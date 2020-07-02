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

#include <string>

#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The GeneratorProfile class.
 *
 * The GeneratorProfile class is for representing a CellML Generator Profile.
 */
class LIBCELLML_EXPORT GeneratorProfile
{
public:
    enum class Profile
    {
        C,
        PYTHON
    };

    ~GeneratorProfile(); /**< Destructor */
    GeneratorProfile(const GeneratorProfile &rhs) = delete; /**< Copy constructor */
    GeneratorProfile(GeneratorProfile &&rhs) noexcept = delete; /**< Move constructor */
    GeneratorProfile &operator=(GeneratorProfile rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c GeneratorProfile object.
     *
     * Factory method to create a @c GeneratorProfile.  Create a
     * generator profile with::
     *
     *   GeneratorProfilePtr generatorProfile = libcellml::GeneratorProfile::create();
     *
     * @return A smart pointer to a @c GeneratorProfile object.
     */
    static GeneratorProfilePtr create(Profile profile = Profile::C) noexcept;

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
     * @brief Get the @c std::string for the less than operator.
     *
     * Return the @c std::string for the less than operator.
     *
     * @return The @c std::string for the less than operator.
     */
    std::string ltString() const;

    /**
     * @brief Set the @c std::string for the less than operator.
     *
     * Set this @c std::string for the less than operator.
     *
     * @param ltString The @c std::string to use for the less than operator.
     */
    void setLtString(const std::string &ltString);

    /**
     * @brief Get the @c std::string for the less than or equal to operator.
     *
     * Return the @c std::string for the less than or equal to operator.
     *
     * @return The @c std::string for the less than or equal to operator.
     */
    std::string leqString() const;

    /**
     * @brief Set the @c std::string for the less than or equal to operator.
     *
     * Set this @c std::string for the less than or equal to operator.
     *
     * @param leqString The @c std::string to use for the less than or equal to
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
     * @brief Get the @c std::string for the greater than or equal to operator.
     *
     * Return the @c std::string for the greater than or equal to operator.
     *
     * @return The @c std::string for the greater than or equal to operator.
     */
    std::string geqString() const;

    /**
     * @brief Set the @c std::string for the greater than or equal to operator.
     *
     * Set this @c std::string for the greater than or equal to operator.
     *
     * @param geqString The @c std::string to use for the greater than or equal
     * to operator.
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
     * @brief Test if this @c GeneratorProfile has a less than operator.
     *
     * Test if this @c GeneratorProfile has a less than operator.
     *
     * @return @c true if the @c GeneratorProfile has a less than operator,
     * @c false otherwise.
     */
    bool hasLtOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a less than operator.
     *
     * Set whether this @c GeneratorProfile has a less than operator.
     *
     * @param hasLtOperator A @c bool to determine whether this
     * @c GeneratorProfile has a less than operator.
     */
    void setHasLtOperator(bool hasLtOperator);

    /**
     * @brief Test if this @c GeneratorProfile has a less than or equal to
     * operator.
     *
     * Test if this @c GeneratorProfile has a less than or equal to operator.
     *
     * @return @c true if the @c GeneratorProfile has a less than or equal to
     * operator,
     * @c false otherwise.
     */
    bool hasLeqOperator() const;

    /**
     * @brief Set whether this @c GeneratorProfile has a less than or equal to
     *  operator.
     *
     * Set whether this @c GeneratorProfile has a less than or equal to operator.
     *
     * @param hasLeqOperator A @c bool to determine whether this
     * @c GeneratorProfile has a less than or equal to operator.
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

    // Arithmetic functions.

    /**
     * @brief Get the @c std::string for the equivalence function.
     *
     * Return the @c std::string for the equivalence function.
     *
     * @return The @c std::string for the equivalence function.
     */
    std::string eqFunctionString() const;

    /**
     * @brief Set the @c std::string for the equivalence function.
     *
     * Set this @c std::string for the equivalence function.
     *
     * @param eqFunctionString The @c std::string to use for the equivalence
     * function.
     */
    void setEqFunctionString(const std::string &eqFunctionString);

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
     * @param neqFunctionString The @c std::string to use for the nonequivalence
     * function.
     */
    void setNeqFunctionString(const std::string &neqFunctionString);

    /**
     * @brief Get the @c std::string for the less than function.
     *
     * Return the @c std::string for the less than function.
     *
     * @return The @c std::string for the less than function.
     */
    std::string ltFunctionString() const;

    /**
     * @brief Set the @c std::string for the less than function.
     *
     * Set this @c std::string for the less than function.
     *
     * @param ltFunctionString The @c std::string to use for the less than
     * function.
     */
    void setLtFunctionString(const std::string &ltFunctionString);

    /**
     * @brief Get the @c std::string for the less than or equal to function.
     *
     * Return the @c std::string for the less than or equal to function.
     *
     * @return The @c std::string for the less than or equal to function.
     */
    std::string leqFunctionString() const;

    /**
     * @brief Set the @c std::string for the less than or equal to function.
     *
     * Set this @c std::string for the less than or equal to function.
     *
     * @param leqFunctionString The @c std::string to use for the less than or
     * equal to function.
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
     * @param gtFunctionString The @c std::string to use for the greater than
     * function.
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
     * @param geqFunctionString The @c std::string to use for the greater or
     * equal than function.
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
     * @param andFunctionString The @c std::string to use for the and function.
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
     * @param orFunctionString The @c std::string to use for the or function.
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
     * @param xorFunctionString The @c std::string to use for the xor function.
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
     * @param notFunctionString The @c std::string to use for the not function.
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
     * @param minFunctionString The @c std::string to use for the minimum
     * function.
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
     * @param maxFunctionString The @c std::string to use for the maximum
     * function.
     */
    void setMaxFunctionString(const std::string &maxFunctionString);

    // Trigonometric functions.

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
     * @param secFunctionString The @c std::string to use for the secant
     * function.
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
     * @param cscFunctionString The @c std::string to use for the cosecant
     * function.
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
     * @param cotFunctionString The @c std::string to use for the cotangent
     * function.
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
     * @param sechFunctionString The @c std::string to use for the hyperbolic
     * secant function.
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
     * @param cschFunctionString The @c std::string to use for the hyperbolic
     * cosecant function.
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
     * @param cothFunctionString The @c std::string to use for the hyperbolic
     * cotangent function.
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
     * @param asecFunctionString The @c std::string to use for the inverse
     * secant function.
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
     * @param acscFunctionString The @c std::string to use for the inverse
     * cosecant function.
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
     * @param acotFunctionString The @c std::string to use for the inverse
     * cotangent function.
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
     * @param asechFunctionString The @c std::string to use for the inverse
     * hyperbolic secant function.
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
     * @param acschFunctionString The @c std::string to use for the inverse
     * hyperbolic cosecant function.
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
     * @param acothFunctionString The @c std::string to use for the inverse
     * hyperbolic cotangent function.
     */
    void setAcothFunctionString(const std::string &acothFunctionString);

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
     * which will be replaced with some profile information and the version of
     * libCellML used.
     *
     * @param originCommentString The @c std::string to use for an origin
     * comment.
     */
    void setOriginCommentString(const std::string &originCommentString);

    /**
     * @brief Get the @c std::string for the interface file name.
     *
     * Return the @c std::string for the interface file name.
     *
     * @return The @c std::string for the interface file name.
     */
    std::string interfaceFileNameString() const;

    /**
     * @brief Set the @c std::string for the interface file name.
     *
     * Set this @c std::string for the interface file name.
     *
     * @param interfaceFileNameString The @c std::string to use the interface
     * file name.
     */
    void setInterfaceFileNameString(const std::string &interfaceFileNameString);

    /**
     * @brief Get the @c std::string for the interface of a header.
     *
     * Return the @c std::string for the interface of a header.
     *
     * @return The @c std::string for the interface of a header.
     */
    std::string interfaceHeaderString() const;

    /**
     * @brief Set the @c std::string for the interface of a header.
     *
     * Set this @c std::string for the interface of a header.
     *
     * @param interfaceHeaderString The @c std::string to use the interface of a
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
     * @brief Get the @c std::string for the interface of the version constant.
     *
     * Return the @c std::string for the interface of the version constant.
     *
     * @return The @c std::string for the interface of the version constant.
     */
    std::string interfaceVersionString() const;

    /**
     * @brief Set the @c std::string for the interface of the version constant.
     *
     * Set this @c std::string for the interface of the version constant.
     *
     * @param interfaceVersionString The @c std::string to use for the interface
     * of the version constant.
     */
    void setInterfaceVersionString(const std::string &interfaceVersionString);

    /**
     * @brief Get the @c std::string for the implementation of the version
     * constant.
     *
     * Return the @c std::string for the implementation of the version constant.
     *
     * @return The @c std::string for the implementation of the version
     * constant.
     */
    std::string implementationVersionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the version
     * constant.
     *
     * Set this @c std::string for the implementation of the version constant.
     *
     * @param implementationVersionString The @c std::string to use for the
     * implementation of the version constant.
     */
    void setImplementationVersionString(const std::string &implementationVersionString);

    /**
     * @brief Get the @c std::string for the interface of the libCellML version
     * constant.
     *
     * Return the @c std::string for the interface of the libCellML version
     * constant.
     *
     * @return The @c std::string for the interface of the libCellML version
     * constant.
     */
    std::string interfaceLibcellmlVersionString() const;

    /**
     * @brief Set the @c std::string for the interface of the libCellML version
     * constant.
     *
     * Set this @c std::string for the interface of the libCellML version
     * constant.
     *
     * @param interfaceLibcellmlVersionString The @c std::string to use for the
     * interface of the libCellML version constant.
     */
    void setInterfaceLibcellmlVersionString(const std::string &interfaceLibcellmlVersionString);

    /**
     * @brief Get the @c std::string for the implementation of the libCellML
     * version constant.
     *
     * Return the @c std::string for the implementation of the libCellML version
     * constant.
     *
     * @return The @c std::string for the implementation of the libCellML
     * version constant.
     */
    std::string implementationLibcellmlVersionString() const;

    /**
     * @brief Set the @c std::string for the implementation of the libCellML
     * version constant.
     *
     * Set this @c std::string for the implementation of the libCellML version
     * constant. To be useful, the string should contain the <LIBCELLML_VERSION>
     * tag, which will be replaced with the version of libCellML used.
     *
     * @param implementationLibcellmlVersionString The @c std::string to use for
     * the implementation of the libCellML version constant.
     */
    void setImplementationLibcellmlVersionString(const std::string &implementationLibcellmlVersionString);

    /**
     * @brief Get the @c std::string for the interface of the state count
     * constant.
     *
     * Return the @c std::string for the interface of the state count constant.
     *
     * @return The @c std::string for the interface of the state count constant.
     */
    std::string interfaceStateCountString() const;

    /**
     * @brief Set the @c std::string for the interface of the state count
     * constant.
     *
     * Set this @c std::string for the interface of the state count constant.
     *
     * @param interfaceStateCountString The @c std::string to use for the
     * interface of the state count constant.
     */
    void setInterfaceStateCountString(const std::string &interfaceStateCountString);

    /**
     * @brief Get the @c std::string for the implementation of the state count
     * constant.
     *
     * Return the @c std::string for the implementation of the state count
     * constant.
     *
     * @return The @c std::string for the implementation of the state count
     * constant.
     */
    std::string implementationStateCountString() const;

    /**
     * @brief Set the @c std::string for the implementation of the state count
     * constant.
     *
     * Set this @c std::string for the implementation of the state count
     * constant. To be useful, the string should contain the <STATE_COUNT> tag,
     * which will be replaced with the number of states in the model.
     *
     * @param implementationStateCountString The @c std::string to use for the
     * implementation of the state count constant.
     */
    void setImplementationStateCountString(const std::string &implementationStateCountString);

    /**
     * @brief Get the @c std::string for the interface of the variable count
     * constant.
     *
     * Return the @c std::string for the interface of the variable count
     * constant.
     *
     * @return The @c std::string for the interface of the variable count
     * constant.
     */
    std::string interfaceVariableCountString() const;

    /**
     * @brief Set the @c std::string for the interface of the variable count
     * constant.
     *
     * Set this @c std::string for the interface of the variable count constant.
     *
     * @param interfaceVariableCountString The @c std::string to use for the
     * interface of the variable count constant.
     */
    void setInterfaceVariableCountString(const std::string &interfaceVariableCountString);

    /**
     * @brief Get the @c std::string for the implementation of the variable
     * count constant.
     *
     * Return the @c std::string for the implementation of the variable count
     * constant.
     *
     * @return The @c std::string for the implementation of the variable count
     * constant.
     */
    std::string implementationVariableCountString() const;

    /**
     * @brief Set the @c std::string for the implementation of the variable
     * count constant.
     *
     * Set this @c std::string for the implementation of the variable count
     * constant. To be useful, the string should contain the <VARIABLE_COUNT>
     * tag, which will be replaced with the number of states in the model.
     *
     * @param implementationVariableCountString The @c std::string to use for
     * the implementation of the variable count constant.
     */
    void setImplementationVariableCountString(const std::string &implementationVariableCountString);

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
     * @brief Get the @c std::string for the interface of some information about
     * the variable of integration.
     *
     * Return the @c std::string for the interface of some information about the
     * variable of integration.
     *
     * @return The @c std::string for the interface of some information about
     * the variable of integration.
     */
    std::string interfaceVoiInfoString() const;

    /**
     * @brief Set the @c std::string for the interface of some information about
     * the variable of integration.
     *
     * Set this @c std::string for the interface of some information about the
     * variable of integration.
     *
     * @param interfaceVoiInfoString The @c std::string to use for the interface
     * of some information about the variable of integration.
     */
    void setInterfaceVoiInfoString(const std::string &interfaceVoiInfoString);

    /**
     * @brief Get the @c std::string for the implementation of some information
     * about the variable of integration.
     *
     * Return the @c std::string for the implementation of some information
     * about the variable of integration.
     *
     * @return The @c std::string for the implementation of some information
     * about the variable of integration.
     */
    std::string implementationVoiInfoString() const;

    /**
     * @brief Set the @c std::string for the implementation of some information
     * about the variable of integration.
     *
     * Set this @c std::string for the implementation of some information about
     * the variable of integration. To be useful, the string should contain the
     * <CODE> tag, which will be replaced with some information about the
     * variable of integration.
     *
     * @param implementationVoiInfoString The @c std::string to use for the
     * implementation of some information about the variable of integration.
     */
    void setImplementationVoiInfoString(const std::string &implementationVoiInfoString);

    /**
     * @brief Get the @c std::string for the interface of some information about
     * the different states.
     *
     * Return the @c std::string for the interface of some information about the
     * different states.
     *
     * @return The @c std::string for the interface of some information about
     * the different states.
     */
    std::string interfaceStateInfoString() const;

    /**
     * @brief Set the @c std::string for the interface of some information about
     * the different states.
     *
     * Set this @c std::string for the interface of some information about the
     * different states.
     *
     * @param interfaceStateInfoString The @c std::string to use for the
     * interface of some information about the different states.
     */
    void setInterfaceStateInfoString(const std::string &interfaceStateInfoString);

    /**
     * @brief Get the @c std::string for the implementation of some information
     * about the different states.
     *
     * Return the @c std::string for the implementation of some information
     * about the different states.
     *
     * @return The @c std::string for the implementation of some information
     * about the different states.
     */
    std::string implementationStateInfoString() const;

    /**
     * @brief Set the @c std::string for the implementation of some information
     * about the different states.
     *
     * Set this @c std::string for the implementation of some information about
     * the different states. To be useful, the string should contain the <CODE>
     * tag, which will be replaced with some information about the different
     * states.
     *
     * @param implementationStateInfoString The @c std::string to use for the
     * implementation of some information about the different states.
     */
    void setImplementationStateInfoString(const std::string &implementationStateInfoString);

    /**
     * @brief Get the @c std::string for the interface of some information about
     * the different variables.
     *
     * Return the @c std::string for the interface of some information about the
     * different variables.
     *
     * @return The @c std::string for the interface of some information about
     * the different variables.
     */
    std::string interfaceVariableInfoString() const;

    /**
     * @brief Set the @c std::string for the interface of some information about
     * the different variables.
     *
     * Set this @c std::string for the interface of some information about the
     * different variables.
     *
     * @param interfaceVariableInfoString The @c std::string to use for the
     * interface of some information about the different variables.
     */
    void setInterfaceVariableInfoString(const std::string &interfaceVariableInfoString);

    /**
     * @brief Get the @c std::string for the implementation of some information
     * about the different variables.
     *
     * Return the @c std::string for the implementation of some information
     * about the different variables.
     *
     * @return The @c std::string for the implementation of some information
     * about the different variables.
     */
    std::string implementationVariableInfoString() const;

    /**
     * @brief Set the @c std::string for the implementation of some information
     * about the different variables.
     *
     * Set this @c std::string for the implementation of some information about
     * the different variables. To be useful, the string should contain the
     * <CODE> tag, which will be replaced with some information about the
     * different variables.
     *
     * @param implementationVariableInfoString The @c std::string to use for the
     * implementation of some information about the different variables.
     */
    void setImplementationVariableInfoString(const std::string &implementationVariableInfoString);

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
     * @brief Get the @c std::string for the interface to create the states
     * array.
     *
     * Return the @c std::string for the interface to create the states array.
     *
     * @return The @c std::string for the interface to create the states array.
     */
    std::string interfaceCreateStatesArrayMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to create the states
     * array.
     *
     * Set this @c std::string for the interface to create the states array. To
     * be useful, the string should contain the <CODE> tag, which will be
     * replaced with some code to create the states array.
     *
     * @param interfaceCreateStatesArrayMethodString The @c std::string to use
     * for the interface to create the states array.
     */
    void setInterfaceCreateStatesArrayMethodString(const std::string &interfaceCreateStatesArrayMethodString);

    /**
     * @brief Get the @c std::string for the implementation to create the states
     * array.
     *
     * Return the @c std::string for the implementation to create the states
     * array.
     *
     * @return The @c std::string for the implementation to create the states
     * array.
     */
    std::string implementationCreateStatesArrayMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to create the states
     * array.
     *
     * Set this @c std::string for the implementation to create the states
     * array. To be useful, the string should contain the <CODE> tag, which will
     * be replaced with some code to create the states array.
     *
     * @param implementationCreateStatesArrayMethodString The @c std::string to
     * use for the implementation to create the states array.
     */
    void setImplementationCreateStatesArrayMethodString(const std::string &implementationCreateStatesArrayMethodString);

    /**
     * @brief Get the @c std::string for the interface to create variables
     * array.
     *
     * Return the @c std::string for the interface to create variables array.
     *
     * @return The @c std::string for the interface to create variables array.
     */
    std::string interfaceCreateVariablesArrayMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to create variables
     * array.
     *
     * Set this @c std::string for the interface to create variables array. To
     * be useful, the string should contain the <CODE> tag, which will be
     * replaced with some code to create the variables array.
     *
     * @param interfaceCreateVariablesArrayMethodString The @c std::string to
     * use for the interface to create variables array.
     */
    void setInterfaceCreateVariablesArrayMethodString(const std::string &interfaceCreateVariablesArrayMethodString);

    /**
     * @brief Get the @c std::string for the implementation to create the
     * variables array.
     *
     * Return the @c std::string for the implementation to create the variables
     * array.
     *
     * @return The @c std::string for the implementation to create the variables
     * array.
     */
    std::string implementationCreateVariablesArrayMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to create the
     * variables array.
     *
     * Set this @c std::string for the implementation to create the variables
     * array. To be useful, the string should contain the <CODE> tag, which will
     * be replaced with some code to create the variables array.
     *
     * @param implementationCreateVariablesArrayMethodString The @c std::string
     * to use for the implementation to create the variables array.
     */
    void setImplementationCreateVariablesArrayMethodString(const std::string &implementationCreateVariablesArrayMethodString);

    /**
     * @brief Get the @c std::string for the interface to delete an array.
     *
     * Return the @c std::string for the interface to delete an array.
     *
     * @return The @c std::string for the interface to delete an array.
     */
    std::string interfaceDeleteArrayMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to delete an array.
     *
     * Set this @c std::string for the interface to delete an array.
     *
     * @param interfaceDeleteArrayMethodString The @c std::string to use for the
     * interface to delete an array.
     */
    void setInterfaceDeleteArrayMethodString(const std::string &interfaceDeleteArrayMethodString);

    /**
     * @brief Get the @c std::string for the implementation to delete an array.
     *
     * Return the @c std::string for the implementation to delete an array.
     *
     * @return The @c std::string for the implementation to delete an array.
     */
    std::string implementationDeleteArrayMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to delete an array.
     *
     * Set this @c std::string for the implementation to delete an array.
     *
     * @param implementationDeleteArrayMethodString The @c std::string to use
     * for the implementation to delete an array.
     */
    void setImplementationDeleteArrayMethodString(const std::string &implementationDeleteArrayMethodString);

    /**
     * @brief Get the @c std::string for the interface to initialise states and
     * constants.
     *
     * Return the @c std::string for the interface to initialise states and
     * constants.
     *
     * @return The @c std::string for the interface to initialise states and
     * constants.
     */
    std::string interfaceInitializeStatesAndConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to initialise states and
     * constants.
     *
     * Set this @c std::string for the interface to initialise states and
     * constants.
     *
     * @param interfaceInitializeStatesAndConstantsMethodString The
     * @c std::string to use for the interface to initialise states and
     * constants.
     */
    void setInterfaceInitializeStatesAndConstantsMethodString(const std::string &interfaceInitializeStatesAndConstantsMethodString);

    /**
     * @brief Get the @c std::string for the implementation to initialise states
     * and constants.
     *
     * Return the @c std::string for the implementation to initialise states and
     * constants.
     *
     * @return The @c std::string for the implementation to initialise states
     * and constants.
     */
    std::string implementationInitializeStatesAndConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to initialise states
     * and constants.
     *
     * Set this @c std::string for the implementation to initialise states and
     * constants.
     *
     * @param implementationInitializeStatesAndConstantsMethodString The
     * @c std::string to use for the implementation to initialise states and
     * constants.
     */
    void setImplementationInitializeStatesAndConstantsMethodString(const std::string &implementationInitializeStatesAndConstantsMethodString);

    /**
     * @brief Get the @c std::string for the interface to compute computed
     * constants.
     *
     * Return the @c std::string for the interface to compute computed
     * constants.
     *
     * @return The @c std::string for the interface to compute computed
     * constants.
     */
    std::string interfaceComputeComputedConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to compute computed
     * constants.
     *
     * Set this @c std::string for the interface to compute computed constants.
     *
     * @param interfaceComputeComputedConstantsMethodString The @c std::string
     * to use for the interface to compute computed constants.
     */
    void setInterfaceComputeComputedConstantsMethodString(const std::string &interfaceComputeComputedConstantsMethodString);

    /**
     * @brief Get the @c std::string for the implementation to compute computed
     * constants.
     *
     * Return the @c std::string for the implementation to compute computed
     * constants.
     *
     * @return The @c std::string for the implementation to compute computed
     * constants.
     */
    std::string implementationComputeComputedConstantsMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to compute computed
     * constants.
     *
     * Set this @c std::string for the implementation to compute computed
     * constants.
     *
     * @param implementationComputeComputedConstantsMethodString The
     * @c std::string to use for the implementation to compute computed
     * constants.
     */
    void setImplementationComputeComputedConstantsMethodString(const std::string &implementationComputeComputedConstantsMethodString);

    /**
     * @brief Get the @c std::string for the interface to compute rates.
     *
     * Return the @c std::string for the interface to compute rates.
     *
     * @return The @c std::string for the interface to compute rates.
     */
    std::string interfaceComputeRatesMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to compute rates.
     *
     * Set this @c std::string for the interface to compute rates.
     *
     * @param interfaceComputeRatesMethodString The @c std::string to use for
     * the interface to compute rates.
     */
    void setInterfaceComputeRatesMethodString(const std::string &interfaceComputeRatesMethodString);

    /**
     * @brief Get the @c std::string for the implementation to compute rates.
     *
     * Return the @c std::string for the implementation to compute rates.
     *
     * @return The @c std::string for the implementation to compute rates.
     */
    std::string implementationComputeRatesMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to compute rates.
     *
     * Set this @c std::string for the implementation to compute rates.
     *
     * @param implementationComputeRatesMethodString The @c std::string to use
     * for the implementation to compute rates.
     */
    void setImplementationComputeRatesMethodString(const std::string &implementationComputeRatesMethodString);

    /**
     * @brief Get the @c std::string for the interface to compute variables.
     *
     * Return the @c std::string for the interface to compute variables.
     *
     * @return The @c std::string for the interface to compute variables.
     */
    std::string interfaceComputeVariablesMethodString() const;

    /**
     * @brief Set the @c std::string for the interface to compute variables.
     *
     * Set this @c std::string for the interface to compute variables.
     *
     * @param interfaceComputeVariablesMethodString The @c std::string to use
     * for the interface to compute variables.
     */
    void setInterfaceComputeVariablesMethodString(const std::string &interfaceComputeVariablesMethodString);

    /**
     * @brief Get the @c std::string for the implementation to compute
     * variables.
     *
     * Return the @c std::string for the implementation to compute variables.
     *
     * @return The @c std::string for the implementation to compute variables.
     */
    std::string implementationComputeVariablesMethodString() const;

    /**
     * @brief Set the @c std::string for the implementation to compute
     * variables.
     *
     * Set this @c std::string for the implementation to compute variables.
     *
     * @param implementationComputeVariablesMethodString The @c std::string to
     * use for the implementation to compute variables.
     */
    void setImplementationComputeVariablesMethodString(const std::string &implementationComputeVariablesMethodString);

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
    explicit GeneratorProfile(Profile profile = Profile::C); /**< Constructor */

    struct GeneratorProfileImpl;
    GeneratorProfileImpl *mPimpl;
};

} // namespace libcellml
