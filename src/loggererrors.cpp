#include <libcellml/loggererrors.h>

#include "libcellml/component.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

namespace libcellml {

std::string EntityError::doSerialisation() const
{
    std::string s = "";
    return s;
}

std::string EntityElementError::doSerialisation() const
{
    std::string s = "Invalid element '" + getType() + "' found in '" + getParentLabel() + "'";
    return s;
}

std::string VariableError::doSerialisation() const
{
    std::string s = "Variable '" + getName() + "' not found in component '" + mComponent->getName() + "'";
    return s;
}

std::string ComponentElementError::doSerialisation() const
{
    std::string s;
    if (getComponent()->getName() != "") {
        s = "Invalid child element '" + getType() + "' found in component '" + getComponent()->getName() + "'.";
    } else {
        s = "Invalid child element '" + getType() + "' found in unnamed component.";
    }
    return s;
}

std::string ComponentAttributeError::doSerialisation() const
{
    std::string s;
    if (getComponent()->getName() != "") {
        s = "Invalid attribute '" + getType() + "' found in component '" + getComponent()->getName() + "'.";
    } else {
        s = "Invalid attribute '" + getType() + "' found in unnamed component.";
    }
    return s;
}

std::string ModelError::doSerialisation() const
{
    return mDescription;
}

std::string UnitsElementError::doSerialisation() const
{
    std::string s;
    if (getUnits()->getName() != "") {
        s = "Invalid child element '" + getType() + "' found in units '" + getUnits()->getName() + "'.";
    } else {
        s = "Invalid child element '" + getType() + "' found in unnamed units.";
    }
    return s;
}

std::string VariableAttributeError::doSerialisation() const
{
    std::string s;
    if (getVariable()->getName() != "") {
        s = "Invalid attribute '" + getType() + "' found in variable '" + getVariable()->getName() + "'.";
    } else {
        s = "Invalid attribute '" + getType() + "' found in unnamed variable.";
    }
    return s;
}

std::string UnitsAttributeError::doSerialisation() const
{
    std::string s;
    if (getUnits()->getName() != "") {
        s = "Invalid attribute '" + getType() + "' found in units '" + getUnits()->getName() + "'.";
    } else {
        s = "Invalid attribute '" + getType() + "' found in unnamed units.";
    }
    return s;
}

std::string UnitsBaseUnitAttributeError::doSerialisation() const
{
    std::string s = "Invalid base_unit attribute in units '" + getUnits()->getName() + "': should be either 'yes' or 'no', and not '" + getValue() + "'";
    return s;
}

std::string UnitsExponentAttributeError::doSerialisation() const
{
    std::string s = "Exponent attribute not convertible to decimal number in units '" + getUnits()->getName() + "': given value '" + getValue() + "'";
    return s;
}

std::string UnitsMultiplierAttributeError::doSerialisation() const
{
    std::string s = "Multiplier attribute not convertible to decimal number in units '" + getUnits()->getName() + "': given value '" + getValue() + "'";
    return s;
}

std::string UnitsOffsetAttributeError::doSerialisation() const
{
    std::string s = "Offset attribute not convertible to decimal number in units '" + getUnits()->getName() + "': given value '" + getValue() + "'";
    return s;
}

}
