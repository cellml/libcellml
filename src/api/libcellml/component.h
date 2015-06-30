#ifndef LIBCELLML_LIBCELLML_COMPONENT_H
#define LIBCELLML_LIBCELLML_COMPONENT_H

#include <string>
#include <memory>

#include "libcellml/libcellml_export.h"
#include "libcellml/nameable.h"

namespace libcellml {

/**
 * @brief The Component class.
 * The Component class is for representing a CellML Component.
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

    Component(Component&& rhs); /**< move constructor */
    Component& operator=(Component&& rhs); /**< move assignment */
    Component(const Component& rhs); /**< copy constructor */
    Component& operator=(const Component& rhs); /**< assignment */

    /**
     * @brief serialise the Model.
     * This method serialises the Model to a std:string representation in the
     * desired format.
     * @sa deserialise
     * @param format The format to serialise the Model to.
     * @return std::string representation of the Model in the given format.
     */
    std::string serialise(CELLML_FORMATS format) const;

    /**
     * @brief add a child component to this component.
     * Add a copy of the given component as a child component of this component.
     * @param c the component to add.
     */
    void addComponent(const Component &c);

private:
    struct ComponentImpl; /**< Forward declaration for pImpl idiom. */
    ComponentImpl* mPimpl; /**< Private member to implementation pointer */

};

}

#endif // LIBCELLML_LIBCELLML_COMPONENT_H

