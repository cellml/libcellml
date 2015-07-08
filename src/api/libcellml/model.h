/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#ifndef LIBCELLML_LIBCELLML_MODEL_H_
#define LIBCELLML_LIBCELLML_MODEL_H_

#include <string>
#include <memory>

#include "libcellml/libcellml_export.h"
#include "libcellml/nameable.h"
#include "libcellml/component.h"

//! Everything in libCellML is in this namespace.
namespace libcellml {

/**
 * @brief The Model class.
 * The Model class is for representing a CellML Model.
 */
class LIBCELLML_EXPORT Model: public Nameable
{
public:
    /**
     * @brief Model Constructor.
     * Default Model constructor.
     */
    Model();

    /**
     * @brief Model Destructor.
     * Default Model destructor.
     */
    ~Model();

    Model(Model&& rhs); /**< Move constructor */
    Model(const Model& rhs);/**< Copy constructor */
    Model& operator=(Model rhs); /**< Assignment operator */

    /**
     * @brief serialise the Model.
     * This method serialises the Model to a std:string representation in the
     * desired format.
     * @sa deserialise
     * @param format The format to serialise the Model to.
     * @return std::string representation of the Model in the given format.
     */
    std::string serialise(libcellml::CELLML_FORMATS format) const;

    /**
     * @brief Add a component to the model.
     * Adds a copy of the given component to the model.
     * @param c The component to add.
     */
    void addComponent(const Component &c);

    /**
     * @brief Remove the component at the given index.
     * Remove the component at the given index.  If the index is
     * not in the range [0, #components) then an exception will
     * be raised.
     * @param index The index of the component to remove (zero-based).
     */
    void removeComponent(size_t index);

    /**
     * @brief Remove the component at the given index.
     * Remove the component with the given name.  This method will
     * remove the first component that is found and return.  If the
     * name is not found no component is removed.
     *
     * This is an overloaded method.
     * @param name The name of the component to remove.
     */
    void removeComponent(const std::string &name);

    /**
     * @brief Tests to see if the component is contained within the Model.
     * Tests to see if the component is contained within the Model.  Returns
     * true if the component is in the Model and false otherwise.
     * @param name The name of the component to test for existence in the Model.
     * @return 'true' if the named component is in the model and 'false' otherwise.
     */
    bool containsComponent(const std::string &name);

    /**
     * @brief Get a component at index.
     * Returns a const reference to a component at the given index.  If the
     * index is not valid std::out_of_range exception is thrown.
     *
     * This is an overloaded method.
     * @param index The index of the component to return (zero-based).
     * @return A const reference to the component at the given index.
     */
    const Component& getComponent(size_t index) const;

    /**
     * @brief Get a component at index.
     * Returns a reference to a component at the given index.  If the index
     * is not valid std::out_of_range exception is thrown.
     *
     * This is an overloaded method.
     * @param index The index of the component to return (zero-based).
     * @return A reference to the component at the given index.
     */
    Component& getComponent(size_t index);

    /**
     * @brief Take the component at the given index and return it.
     * Removes the component at the given index position and returns it.
     * If an invalid index is passed to the method a std::out_of_range
     * exception is thrown.
     * @param index The index of the component to take (zero-based).
     * @return The component at the given index.
     */
    Component takeComponent(size_t index);

    /**
     * @brief Take the component with the given name 'name' and return it.
     * Removes the component at the given index position and returns it.
     * If an invalid name is passed to the method a std::out_of_range
     * exception is thrown.
     *
     * This is an overloaded method.
     * @param name The name of the component to take.
     * @return The component identified with the given name.
     */
    Component takeComponent(const std::string &name);

    /**
     * @brief Replace a component at index.
     * Replaces the component at index with c.  Index must be a valid index
     * position.
     * @param index Index of the component to replace (zero-based).
     * @param c The component to use for replacement.
     */
    void replaceComponent(size_t index, const Component& c);

    /**
     * @brief Replace a component with the given name.
     * Replaces the component with the given name 'name' with c.  Name must be a valid name
     * of a component in the model, if it isn't a std::runtime_error is thrown.
     *
     * This is an overloaded method.
     * @param name The name of the component to replace.
     * @param c The component to use for replacement.
     */
    void replaceComponent(const std::string &name, const Component& c);

    /**
     * @brief Get the number of components in the model.
     * Returns the number of components the model directly contains.
     * @return The number of components.
     */
    size_t componentCount() const;

private:
    void swap(Model &rhs);

    struct ModelImpl; /**< Forward declaration for pImpl idiom. */
    ModelImpl *mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_MODEL_H_ */

