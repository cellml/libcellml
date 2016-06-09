#include <libcellml/loggererrors.h>

#include "libcellml/component.h"

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

}
