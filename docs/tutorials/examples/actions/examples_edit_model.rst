.. _examples_edit_model:

Edit aspects of a ``Model``
===========================

Every aspect of a model can be edited and changed through the libCellML API.
The most complicated part is editing the MathML, which is discussed separately in **TODO**.

Edit direct attributes
----------------------
Where an item can contain only one version of an attribute (name, id, maths for a component, units for a variable, etc) then the standard :code:`set` prefix to the attribute is used:

- Get the attribute :code:`xyz` using the camelCase function :code:`xyx()` without arguments;
- Set its attribute using the camelCase function :code:`setXyz(arg)` with an appropriate argument.

For example:

- :code:`name()` and :code:`setName("myNewName")` to retrieve and set the item's name to :code:`"myNewName"`;
- :code:`id()` and :code:`setId("myNewID")` to retrieve and set the item's ID to :code:`"myNewID"`;

Edit collections of items
-------------------------
Where an item can contain more than one child item (for example, more than one :code:`Variable` in a :code:`Component`, more than one :code:`Units` item in a :code:`Model`, etc) the editing process for the collection follows the patterns outlined below.
NB: All of this explanation uses "thing" in place of the specific type of item (component, variable etc).

.. container:: nb

  Each of the collections is really a set of smart pointers, which keeps track of the number of references to any of its items.
  This means that the behaviour of some of the functions (in particular, the :code:`removeThing` and :code:`takeThing` functions) will depend on whether that :code:`thing` has other references to it in your code.

Count things
~~~~~~~~~~~~
Generic counting functions will return the number of child items using the :code:`thingCount()` function to get the number of :code:`thing` children.
For example, :code:`unitsCount()` returns the number of :code:`Units` items in a :code:`Model`.
This is useful when iterating through a collection or before using an index to access one of its members.

Get a thing
~~~~~~~~~~~
Pointers to items within a collection can be retrieved in two ways: by *getting* or by *taking*.
The first does not affect the collection, and returns a pointer to the item: this is accomplished using the :code:`thing` function.

There are two overloaded arguments for the get functionality:

- :code:`thing(i)` returns a pointer to the thing at the i-th index position; and
- :code:`thing("myThingName")` returns a pointer to the thing named "myThingName".

Note that in this case the retrieval of the thing does not alter it, and neither does it alter the parent which owns it.

Add a thing
~~~~~~~~~~~
To add to a collection use the :code:`addThing` functionality.
The basic form of adding is by symbol: :code:`addThing(thingToAdd)` which will append the pointer to :code:`thingToAdd` to the collection.
Special cases of this are:

- The :code:`addComponent` function will return a boolean variable telling you whether the operation was successful or not.
  In situations where the component has already been included in the collection, is present in another collection, or is not found, this operation will return false.
  Other add functions do not return any value.
- The :code:`addUnit` function has many overloaded argument lists.
  Please refer to the full :api:`API addUnit<Units>` reference for details.

Remove a thing
~~~~~~~~~~~~~~
To remove an item from the collection and detach its parent without returning a pointer to that item, use the :code:`removeThing` functions.

.. container:: nb

  Because the collections are stored as a group of smart pointers, if no references exist to the item then its contents will also be deleted.

If other references do exist, the parent pointer will be detached, but they won't otherwise be affected.

Remove everything
~~~~~~~~~~~~~~~~~
In addition to the removal of specific items from a collection as above, you can also clear the entire collection using the :code:`removeAllThings` functions.

Take a thing
~~~~~~~~~~~~
The :code:`takeThing` functions combine a little of the *remove* and a little of the *get* functionality.
It will return a pointer to the item (like the *get* :code:`thing` functionality above), but it will also remove the item from the collection (like :code:`removeThing`), updating both the collection as well as the item's parent.

Examples are shown for C++ and Python below.

.. container:: toggle

  .. container:: leftheader

    Show C++ examples

  .. code-block:: cpp

    // Consider the case where we already have a model containing a component named "myComponent" at index 0.

    // Case 1: Use the get and remove functionality together.
    auto component = model->component(0);               // Get either by index,
    auto component = model->component("componentName"); // or by name.

    bool componentWasRemoved = model->removeComponent(0);               // Remove either by index,
    bool componentWasRemoved = model->removeComponent("componentName"); // by name,
    bool componentWasRemoved = model->removeComponent(component);       // or by symbol.

    // At this point, the model's components collection no longer contains the component, and the component
    // pointer has no parent.

    // Case 2: Use the take functionality.
    auto component = model->takeComponent(0);             // Take either by index,
    auto component = model->takeComponent("myComponent"); // or by name.

    // At this point, we have the same outcome as in Case 1 above.  The model's component collection no
    // longer contains the component, and the component itself has no parent.

    // Case 3: A cautionary tale using remove without get.
    auto iAmABooleanNotAComponent = model->removeComponent(0); // Remove either by index, name or symbol as above.

    // In the situation where no other reference to the component exists (ie: we did not "get" it as in Case 1),
    // the model's collection will no longer contain the component AND the entire contents of that component
    // will be permanently deleted.

.. container:: toggle

  .. container:: leftheader

    Show Python examples

  .. code-block:: py

    # Consider the case where we already have a model containing a component named "myComponent" at index 0.

    # Case 1: Use the get and remove functionality together.
    component = model.component(0)                    # Get either by index,
    component = model.component("componentName") # or by name.

    was_removed = model.removeComponent(0)               # Remove either by index,
    was_removed = model.removeComponent("componentName") # by name,
    was_removed = model.removeComponent(component)       # or by symbol.

    # At this point, the model's components collection no longer contains the component, and the component
    # pointer has no parent.

    # Case 2: Use the take functionality.
    component = model.takeComponent(0)             # Take either by index,
    component = model.takeComponent("myComponent") # or by name.

    # At this point, we have the same outcome as in Case 1 above.  The model's component collection no
    # longer contains the component, and the component itself has no parent.

    # Case 3: A cautionary tale using remove without get.
    i_am_a_bool_not_a_component = model.removeComponent(0) # Remove either by index, name or symbol as above.

    # In the situation where no other reference to the component exists (ie: we did not "get" it as in Case 1),
    # the model's collection will no longer contain the component AND the entire contents of that component
    # will be permanently deleted.

Replace a thing
~~~~~~~~~~~~~~~
