#ifndef LIBCELLML_LIBCELLML_NAMEABLE_H
#define LIBCELLML_LIBCELLML_NAMEABLE_H

#include "libcellml/libcellml_export.h"
#include "libcellml/entity.h"

namespace libcellml {

/**
 * @brief The Nameable class.
 * Base class for all nameable libCellML classes.
 */
class LIBCELLML_EXPORT Nameable: public Entity
{
public:
    /**
     * @brief set the name for the Entity
     * This method sets the name parameter of the Entity.  It does not check
     * the validity of the name.
     * @param name A string to represent the name.
     */
    void setName(const std::string &name) {
        mName = name;
    }

    /**
     * @brief get the name of the Entity
     * Gets the name of the Entity as a string.
     * @return std::string representation of the Entity name.
     */
    std::string getName() const {
        return mName;
    }

protected:
    std::string mName;
};

}

#endif // LIBCELLML_LIBCELLML_NAMEABLE_H

