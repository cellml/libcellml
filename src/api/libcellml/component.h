#ifndef LIBCELLML_LIBCELLML_COMPONENT_H
#define LIBCELLML_LIBCELLML_COMPONENT_H

#include <string>
#include <memory>

#include "libcellml/libcellml_export.h"
#include "libcellml/nameable.h"

namespace libcellml {

/**
 * @brief The Model class.
 * The Model class is for representing a CellML Model.
 */
class LIBCELLML_EXPORT Component: public Nameable
{
public:
    /**
     * @brief Component Constructor.
     * Default Component constructor.
     */
    Component();
    /**
     * @brief Component Destructor.
     * Default Component destructor.
     */
    ~Component();

    /**
     * @brief serialise the Model.
     * This method serialises the Model to a std:string representation in the
     * desired format.
     * @sa deserialise
     * @param format The format to serialise the Model to.
     * @return std::string representation of the Model in the given format.
     */
    std::string serialise(CELLML_FORMATS format) const;

    Component(Component&& rhs); /**< move constructor */
    Component& operator=(Component&& rhs); /**< move assignment */

private:

    Component(const Component&) = delete; /**< non-copyable */
    Component& operator=(const Component&) = delete; /**< non-copyable */

    struct ComponentImpl; /**< Forward declaration for pImpl idiom. */
    std::unique_ptr<ComponentImpl> mPimpl; /**< Private member to implementation pointer */

};

}

#endif // LIBCELLML_LIBCELLML_COMPONENT_H

