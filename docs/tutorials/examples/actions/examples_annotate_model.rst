.. _examples_annotate_model:

Annotate a ``Model``
====================

libCellML does not provide annotation functionality directly, but it can help with some of the things that you might need to know in order to implement your own.
Each annotation is attached to an unique ID locator which can be retrieved and edited.
Since CellML is a subset of XML, any item may have an ID attribute, including operations within the MathML blocks, CellML entities, and CellML non-entity items (connections, encapsulations etc).
The ID attributes themselves must follow the specification rules: please see :cellml2:`1.2.5 XML ID attributes<specA2.html?issue=1.2.5>` for details.

.. container:: gotcha

  At present, items within MathML blocks which have :code:`id` attributes are not editable by the annotation class.
  Any editing or manipulation must be done external to libCellML.

Annotation tools for entity items
---------------------------------

Entity item types are:

- :code:`Model` items;
- :code:`Component` items;
- :code:`Variable` items;
- :code:`Units` items;
- :code:`Reset` items; and
- :code:`ImportSource` items.

The :code:`id` attribute for each of these entity types can be retrieved using the :code:`id()` function for the object, or set through its :code:`setId()` function.

.. tabs::

  .. code-tab:: c++

    // Set the id attribute for a Model item.
    model->setId("myModelId");

    // Retrieve the id attribute from a Model item.
    std::string myModelIdString = model->id();

  .. code-tab:: python

    # Set the id attribute for a Model item.
    model.setId("myModelId")

    # Retrieve the id attribute from a Model item.
    my_model_id_string = model.id()

Annotation tools for other item types
-------------------------------------
Items which specify the relationship between two entities (such as connections between components, and mappings between variables) are accessed and identified by the pair of entities.
Consider the simple example shown below.

.. code:: text

  model:
    ├ component: name = "c1", id = "c1id"
    │   └ variable: name = "v1", id = "v1id" <╴╴╴┐
    └ component: name = "c2", id = "c2id"     equivalent variables
        └ variable: name = "v2", id = "v2id" <╴╴╴┘

.. container:: toggle

  .. container:: header

    Show CellML syntax

  .. code-block:: xml

    <model>
      <component name="c1" id="c1id">
        <variable name="v1" id="v1id" />
      </component>
      <component name="c2" id="c2id">
        <variable name="v2" id="v2id" />
      </component>

      <!-- The variable equivalence is stored separately to the variables themselves. -->
      <connection component1="c1" component2="c2" id="c1c2id" >
        <map_variables variable1="v1" variable2="v2" id="v1v2id" />
      </connection>
    </model>

.. tabs::

  .. code-tab:: c++

    // Set the id of the mapping between variables v1 and v2.
    Variable::setEquivalentVariableId(v1, v2, "v1v2Id");

    // Get the id of the mapping between variables v1 and v2.
    std::string v1v2IdString = Variable::equivalentVariableId(v1, v2);

    // Since a connection item between two components will only exist
    // when there is a variable equivalence between at least one each
    // of their children.  The connection is accessed through those
    // child variable pairs, just as the equivalence mapping itself is.
    Variable::setConnectionId(v1, v2, "c1c2id");

    // Get the id of the connection between the parent components of
    // equivalent variable pair.
    std::string c1c2IdString = Variable::connectionId(v1, v2);

  .. code-tab:: python

    # Set the id of the mapping between variables v1 and v2.
    Variable.setEquivalentVariableId(v1, v2, "v1v2Id")

    # Get the id of the mapping between variables v1 and v2.
    v1v2_id_string = Variable.equivalentVariableId(v1, v2)

    # Since a connection item between two components will only exist
    # when there is a variable equivalence between at least one each
    # of their children.  The connection is accessed through those
    # child variable pairs, just as the equivalence mapping itself is.
    Variable.setConnectionId(v1, v2, "c1c2id")

    # Get the id of the connection between the parent components
    # of equivalent variable pair.
    c1c2IdString = Variable.connectionId(v1, v2)

There is only one encapsulation in a model, and its :code:`id` attribute is accessed using the very simple functions from the model instance:

.. tabs::

  .. code-tab:: c++

    // Set the encapsulation id.
    model->setEncapsulationId("encapsId");

    // Get the encapsulation id.
    std::string encapsulationIdString = model->encapsulationId();

  .. code-tabs:: python

    # Set the encapsulation id.
    model.setEncapsulationId("encapsId")

    # Get the encapsulation id.
    encapsulation_id_string = model.encapsulationId()

Some items are most readily accessed through their entity-type parents, these being:

- :code:`unit` items, a collection of which defines a :code:`Units` item;
- :code:`test_value` and :code:`reset_value` children of :code:`Reset` items; and ... **TODO**

Unit children of :code:`Units` items can be accessed through the :code:`unitAttributes` family of functions.
Note that there are several overloads of the arguments for this function; please see the complete documentation on the :api:`Units functions API page<Units>`.

.. tabs::

  .. code-tab:: c++

    // Create a Units item representing millimetre^3 per second.
    auto mm3PerSecond = libcellml::Units::create("mm3PerSecond");

    // Add the per second part with the id "perSecondUnitId".
    mm3PerSecond->addUnit("second", 0, -1.0, 1.0, "perSecondUnitId");

    // Add the mm^3 part with with the id "millimetreCubedUnitId".
    mm3PerSecond->addUnit("metre", "milli", 3.0, 1.0, "millimetreCubedUnitId");

    // Retrieve the unit attributes for the second (index = 1) unit item, including the id attribute:
    std::string unitReference;
    std::string unitPrefix;
    double unitExponent;
    double unitMultiplier;
    std::string unitId;
    mm3PerSecond->unitAttributes(1, unitReference, unitPrefix, unitExponent, unitMultiplier, unitId);

  .. code-tab:: python

    # Create a Units item representing millimetre^3 per second.
    mm3_per_second = Units.create("mm3PerSecond")

    # Add the per second part with the id "perSecondUnitId".
    mm3_per_second.addUnit("second", 0, -1.0, 1.0, "perSecondUnitId")

    # Add the mm^3 part with with the id "millimetreCubedUnitId".
    mm3_per_second.addUnit("metre", "milli", 3.0, 1.0, "millimetreCubedUnitId")

    # Retrieve the unit attributes for the second (index = 1) unit item, including the id attribute:
    mm3PerSecond.unitAttributes(1, unitReference, unitPrefix, unitExponent, unitMultiplier, unitId)


+-------------------+-----------------------------------------------------------------------------------------------------+
| enumeration value | object type                                                                                         |
+-------------------+-----------------------------------------------------------------------------------------------------+
| COMPONENT         | Pointer to a :code:`Component` with the given :code:`id`.                                           |
+-------------------+-----------------------------------------------------------------------------------------------------+
| COMPONENT_REF     | Pointer to a :code:`Component`, whose encapsulation :code:`component_ref` has the given :code:`id`. |
+-------------------+-----------------------------------------------------------------------------------------------------+
| CONNECTION        | :code:`VariablePair` containing pointers to two :code:`Variable` items which span the connection.   |
+-------------------+-----------------------------------------------------------------------------------------------------+
| ENCAPSULATION     | An empty string.  The encapsulation can be retrieved from the model itself.                         |
+-------------------+-----------------------------------------------------------------------------------------------------+
| IMPORT            | Pointer to an :code:`ImportSource` item with the given :code:`id`.                                  |
+-------------------+-----------------------------------------------------------------------------------------------------+
| ISSUE             | Pointer to an :code:`Issue` item, created when something has gone wrong.                            |
+-------------------+-----------------------------------------------------------------------------------------------------+
| MAP_VARIABLES     | :code:`VariablePair` containing the two :code:`Variable` items connected by a variable              |
|                   | equivalence with the given :code:`id`.                                                              |
+-------------------+-----------------------------------------------------------------------------------------------------+
| MODEL             | Pointer to the :code:`Model` item with the given :code:`id`.                                        |
+-------------------+-----------------------------------------------------------------------------------------------------+
| RESET             | Pointer to the :code:`Reset` item with the given :code:`id`.                                        |
+-------------------+-----------------------------------------------------------------------------------------------------+
| RESET_VALUE       | Pointer to the parent :code:`Reset` item containing a reset value with the given :code:`id`.        |
+-------------------+-----------------------------------------------------------------------------------------------------+
| TEST_VALUE        | Pointer to the parent :code:`Reset` item containing a test value with the given :code:`id`.         |
+-------------------+-----------------------------------------------------------------------------------------------------+
| UNIT              | :code:`UnitItem` pair, when the first attribute is a :code:`Units` pointer to the parent of         |
|                   | the unit with the given :code:`id`, and the second attribute is the index within the                |
|                   | :code:`Units` item at which the unit can be found.                                                  |
+-------------------+-----------------------------------------------------------------------------------------------------+
| UNITS             | Pointer to a :code:`Units` item with the given :code:`id`.                                          |
+-------------------+-----------------------------------------------------------------------------------------------------+
| VARIABLE          | Pointer to a :code:`Variable` item with the given :code:`id`.                                       |
+-------------------+-----------------------------------------------------------------------------------------------------+





Useful snippets
===============

.. include:: ../snippets/snippet_annotate_auto_ids.rst

.. .. include:: ../snippets/snippet_annotate_find_item.rst
