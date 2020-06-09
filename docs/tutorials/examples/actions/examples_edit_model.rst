.. _examples_edit_model:

Edit items in a model
=====================

All CellML entities exist in an hierarchical structure as shown below.
In some circumstances additional links are made between items (equivalent variables, for example), but on the whole it follows a basic tree structure.

Within the structure each item has two parts:

- A set of *attributes* specific to itself.
  Some of these attribute exist for many items (for example, the :code:`name` attribute), and others are specific to the item type (for example, the :code:`initialValue` attribute on a :code:`Variable` item).
- A set of *collections* which this - the parent item - curates.
  For example, the collection of :code:`Variable` items owned by a parent :code:`Component`.

Editing attributes
------------------
For any item type, each attribute :code:`xyz` may be edited using the general :code:`setXyz` function, whose arguments vary depending on the attribute.
Note that this is distinct from editing collections of items, which is discussed below.

Some example snippets are shown below:

.. include:: ../snippets/snippet_edit_names.rst

.. include:: ../snippets/snippet_edit_mathml.rst

Editing collections
-------------------
General families of functions are avaiable for editing collections, but take the form of :code:`addXyz` and :code:`removeXyz`, :code:`takeXyz` and :code:`replaceXyz`, as explained in :ref:`Understanding collections<examples_understand_collections>`.

Some example snippets are shown below:

.. include:: ../snippets/snippet_add_thing.rst

.. include:: ../snippets/snippet_remove_thing.rst

.. include:: ../snippets/snippet_take_thing.rst

.. include:: ../snippets/snippet_replace_thing.rst

Editing special relationships
-----------------------------
Some parts of the CellML model require different treatment to those listed above; connections between equivalent variables, for example.

Editing variable equivalences
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In the situation of equivalent variable collections there is no clear "ownership" of the equivalence as an attribute of any one variable, and neither is there a central parent item with curation ability over the set of variables.
A different approach is required.

Adding and removing variable equivalence is accomplished using the :code:`addEquivalence` and :code:`removeEquivalence` functions as shown below.
These functions take arguments of the variable pointers to connect or dissociate, and return a boolean value indicating whether the operation was successful.
The success of the :code:`addEquivalence` function depends on:

- the variable pointers being non-null;
- the two variables having parent components;
- there being no previously existing conenction between the two variables already.

Creating a *valid* connection also depends on the two variables having compatible units, appropriate interface types, and being in components which are accessible to one another (parent-child or sibling relationship).

The success of the :code:`removeEquivalence` function depends on:

  - the variable pointer arguments being non-null; and
  - there being an existing connection between the two variables.

Note that the :code:`removeEquivalence` function will only remove an equivalence which was previously set using the :code:`addEquivalence` function; it does not remove any indirect connections via third-party variables between the two.

An additional :code:`removeAllEquivalences` function will completely remove the variable from any connected set.

Please see the :api:`API Variable<Variable>` page for details of these functions.

.. tabs::

  .. code-tab:: c++

    // Assuming that variables A and B are in different components, and that those components are
    // available for connection with one another (parent-child, or sibling relationship).

    // Add variables A and B to the same equivalent variable set.
    auto isAconnectedToB = libcellml::Variable::addEquivalence(A, B);

    // Remove a pre-existing equivalence between variables C and D.
    auto isCdisconnectedFromD = libcellml::Variable::removeEquivalence(C, D);

  .. code-tab:: python

    # Assuming that variables A and B are in different components, and that those components are
    # available for connection with one another (parent-child, or sibling relationship).

    # Add variables A and B to the same equivalent variable set.
    isAconnectedToB = Variable.addEquivalence(A, B)

    # Remove a pre-existing equivalence between variables C and D.
    isCdisconnectedFromD = Variable.removeEquivalence(C, D)

There are some gotchas to be explained.
A variable can belong to only one set of equivalent variables; by having more than one equivalent variable, the variable itself merges the two sets of variables into one.
Consider this example.
Variable :code:`fruit` is equivalent to variables :code:`apple`, :code:`pear`, and :code:`peach`.
Another variable :code:`vegetable` is equivalent to variables :code:`tomato`, :code:`celery`, and :code:`spinach`.
At this time, there are two sets of equivalent variables: all of the fruit are equivalent to one another, and all of the vegetables are equivalent to one another.
Adding a variable :code:`produce` with an equivalence to :code:`fruit` and to :code:`vegetable` effectively merges the two sets, so that now the variable :code:`peach` is equivalent to :code:`spinach`.

**TODO** Need better examples and use cases here once the API issue #619 is clarified.

Editing an encapsulation hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Components may be added to a model or another component to create an encapsulation hierarchy, but there are a few things to watch out for in this situation.
Components must belong to only one parent.
When adding a component from one location in the encapsulation to another, you will need to first clear the previous parent before adding into the new spot.
This is shown in the code snippet below.

.. include:: ../snippets/snippet_edit_encapsulation.rst
