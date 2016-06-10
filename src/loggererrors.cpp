#include <libcellml/loggererrors.h>

#include "libcellml/component.h"
#include "libcellml/units.h"

namespace libcellml {

std::string EntityError::doSerialisation() const
{
    std::string s = "";
    return s;
}

std::string EntityElementError::doSerialisation() const
{
    std::string s = "Invalid element '" + getElementType() + "' found in '" + getParentLabel() + "'";
    return s;
}

std::string VariableError::doSerialisation() const
{
    std::string s = "Variable '" + getName() + "' not found in component '" + mComponent->getName() + "'";
    return s;
}

std::string UnitsBaseUnitAttributeError::doSerialisation() const
{
    std::string s = "Unrecognised base_unit attribute in units '" + getUnits()->getName() + "': should be either 'yes' or 'no', and not '" + getValue() + "'";
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
