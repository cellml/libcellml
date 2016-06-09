#include <libcellml/loggererrors.h>

#include "libcellml/component.h"
#include "libcellml/units.h"

namespace libcellml {

std::string EntityError::doSerialisation() const
{
    std::string s = "";
    return s;
}

std::string VariableError::doSerialisation() const
{
    std::string s = "Variable '" + getName() + "' not found in component '" + mComponent->getName() + "'";
    return s;
}

std::string UnitsBaseUnitAttributeError::doSerialisation() const
{
    std::string s = "Unrecognised base_unit attribute in '" + getUnits()->getName() + "': should be either 'yes' or 'no'";
    return s;
}

std::string UnitsExponentAttributeError::doSerialisation() const
{
    std::string s = "Exponent attribute not convertible to decimal number in '" + getUnits()->getName() + "': given value '" + mValue + "'";
    return s;
}

}
