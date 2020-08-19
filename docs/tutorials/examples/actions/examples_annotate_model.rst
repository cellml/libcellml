.. _examples_annotate_model:

Annotate a ``Model``
====================

libCellML does not provide annotation functionality directly, but it can help with some of the things that you might need to know in order to implement your own.
Each annotation is attached to a unique ID locator which can be retrieved and edited, or created automatically if you haven't already set them yourself.
Since CellML is a subset of XML, any item may have an ID attribute, including operations within the MathML blocks, CellML entities, and CellML non-entity items (connections, encapsulations etc).
These ID attributes themselves must follow the specification rules: please see :cellml2:`1.2.5 XML ID attributes<specA2.html?issue=1.2.5>` for details.

.. container:: gotcha

  At present, items within MathML blocks which have :code:`id` attributes are not retrieved or edited by the annotation class.
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

    // Set the ID attribute for a Model item.
    model->setId("myModelId");

    // Retrieve the ID attribute from a Model item.
    std::string myModelIdString = model->id();

  .. code-tab:: py

    # Set the ID attribute for a Model item.
    model.setId("myModelId")

    # Retrieve the ID attribute from a Model item.
    my_model_id_string = model.id()

Annotation tools for other item types
-------------------------------------

Connections and variable equivalence
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Items which specify the relationship between two entities (such as connections between components, and mappings between variables) are accessed and identified by the pair of entities.
Consider the simple example shown below.

.. code:: text

  model:
    ├─ component: name = "c1", id = "c1id"
    │   └ variable: name = "v1", id = "v1id" <╴╴╴┐
    └─ component: name = "c2", id = "c2id"     equivalent variables
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

    // Set the ID of the mapping between variables v1 and v2.
    Variable::setEquivalentVariableId(v1, v2, "v1v2Id");

    // Get the ID of the mapping between variables v1 and v2. Note that
    // equivalences and connections go both ways, so the ID is the same
    // whichever order the variables are specified.
    std::string v1v2IdString = Variable::equivalentVariableId(v1, v2);

    // Since a connection item between two components will only exist
    // when there is a variable equivalence between at least one each
    // of their children.  The connection is accessed through those
    // child variable pairs, just as the equivalence mapping itself is.
    Variable::setConnectionId(v1, v2, "c1c2id");

    // Get the ID of the connection between the parent components of
    // equivalent variable pair. Note that equivalences and connections
    // go both ways, so the ID is the same whichever order the variables
    // are specified.
    std::string c1c2IdString = Variable::connectionId(v1, v2);

  .. code-tab:: py

    # Set the ID of the mapping between variables v1 and v2.
    Variable.setEquivalentVariableId(v1, v2, "v1v2Id")

    # Get the ID of the mapping between variables v1 and v2.
    # Note that equivalences and connections go both ways, so 
    # the ID is the same whichever order the variables are specified.
    v1v2_id_string = Variable.equivalentVariableId(v1, v2)

    # Since a connection item between two components will only exist
    # when there is a variable equivalence between at least one each
    # of their children.  The connection is accessed through those
    # child variable pairs, just as the equivalence mapping itself is.
    Variable.setConnectionId(v1, v2, "c1c2id")

    # Get the ID of the connection between the parent components
    # of equivalent variable pair.
    # Note that equivalences and connections go both ways, so 
    # the ID is the same whichever order the variables are specified.
    c1c2IdString = Variable.connectionId(v1, v2)

Encapsulation and component references
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The model's encapsulation and the component references which it contains may have ID attributes too. 
These are accessed through the :code:`encapsulationId()` functions, as shown below.

.. code:: text

  model:
    └ encapsulation:
        └ component: grandparent
            └ component: parent
                └ component: child

.. container:: toggle

  .. container:: header

    Show CellML syntax

  .. code-block:: xml

    <model>
      <component name="grandparent" id="grandparentComponentId" />
      <component name="parent" id="parentComponentId" />
      <component name="child" id="childComponentId" />

      <!-- The ids of the components in the encapsulation structure are distinct
           from the ids on the components themselves. -->
      <encapsulation id="encapsId">
        <component_ref component="grandparent" id="grandparentEncapsId" >
          <component_ref component="parent" id="parentEncapsId" >
            <component_ref component="child" id="childEncapsId" >
          </component_ref>
        </component_ref>
      </encapsulation>
    </model>

There is only one encapsulation in a model, and its :code:`id` attribute is accessed using the very simple functions from the model instance.
The position of each component within that encapsulation structure is referenced using the same functions, but on the component instance instead.

.. tabs::

  .. code-tab:: c++

    // Set the encapsulation ID.
    model->setEncapsulationId("encapsId");
    grandparentComponent->setEncapsulationId("grandparentEncapsId");

    // Get the encapsulation ID.
    std::string modelEncapsulationId = model->encapsulationId();
    std::string grandparentEncapsulationId = grandparentComponent->encapsulationId(); 

  .. code-tab:: py

    # Set the encapsulation ID.
    model.setEncapsulationId("encapsId")
    grandparent_component.setEncapsulationId("grandparentEncapsId")

    # Get the encapsulation ID.
    model_encapsulation_id = model.encapsulationId()
    grandparent_encapsulation_id = grandparent_component.encapsulationId()

Unit item children; reset_value, test_value item children
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Some items are most readily accessed through their entity-type parents, these being:

- :code:`unit` items, a collection of which defines a :code:`Units` item; and
- :code:`test_value` and :code:`reset_value` children of :code:`Reset` items.

Unit children of :code:`Units` items can be accessed either through the streamlined ID-only functions :code:`unitId(index)` and :code:`setUnitId(index)`, or through the :code:`unitAttributes` family of functions.
Note that there are several overloads of the arguments for this function; please see the complete documentation on the :api:`Units functions API page<Units>`.

.. tabs::

  .. code-tab:: c++

    // Create a Units item representing millimetre^3 per second.
    auto mm3PerSecond = libcellml::Units::create("mm3PerSecond");

    // Add the per second part with the ID "perSecondUnitId".
    mm3PerSecond->addUnit("second", 0, -1.0, 1.0, "perSecondUnitId");

    // Add the mm^3 part with with the ID "mmCubedUnitId".
    mm3PerSecond->addUnit("metre", "milli", 3.0, 1.0, "mmCubedUnitId");

    // Check that the ID has been assigned to the Unit children.
    auto checkId1 = mm3PerSecond->unitId(0); // returns "perSecondUnitId".
    auto checkId2 = mm3PerSecond->unitId(1); // returns "mmCubedUnitId".

    // Change the ID of the second (ie: index = 1) child to be "millimetreCubedUnitId":
    mm3PerSecond->setUnitId(1, "millimetreCubedUnitId");

    // Retrieve the unit attributes for the first (index = 0) unit item, including the ID attribute:
    std::string unitReference;
    std::string unitPrefix;
    double unitExponent;
    double unitMultiplier;
    std::string unitId;
    mm3PerSecond->unitAttributes(0, unitReference, unitPrefix, unitExponent, unitMultiplier, unitId);

  .. code-tab:: py

    # Create a Units item representing millimetre^3 per second.
    mm3_per_second = Units.create("mm3PerSecond")

    # Add the per second part with the ID "perSecondUnitId".
    mm3_per_second.addUnit("second", 0, -1.0, 1.0, "perSecondUnitId")

    # Add the mm^3 part with with the ID "mmCubedUnitId".
    mm3_per_second.addUnit("metre", "milli", 3.0, 1.0, "mmCubedUnitId")

    # Retrieve both ids from the child units.
    check_1 = mm3_per_second.unitId(0) # returns "perSecondUnitId"
    check_2 = mm3_per_second.unitId(1) # returns "mmCubedUnitId"

    # Change the ID of the second (ie: index = 1) Unit child to be "millimetreCubedUnitId".
    mm3_per_second.setUnitId(1, "millimetreCubedUnitId")

    # Retrieve the unit attributes for the second (index = 0) unit item, including the ID attribute:
    mm3PerSecond.unitAttributes(0, unitReference, unitPrefix, unitExponent, unitMultiplier, unitId)

Annotator ``Type`` and returned types
-------------------------------------

+-------------------+-----------------------------------------------------------------------------------------------------+
| enumeration value | Object type in the "any" container.                                                                 |
+-------------------+-----------------------------------------------------------------------------------------------------+
| COMPONENT         | Pointer to a :code:`Component` with the given :code:`id`.                                           |
+-------------------+-----------------------------------------------------------------------------------------------------+
| COMPONENT_REF     | Pointer to a :code:`Component`, whose encapsulation :code:`component_ref` has the given :code:`id`. |
+-------------------+-----------------------------------------------------------------------------------------------------+
| CONNECTION        | :code:`VariablePair` containing pointers to two :code:`Variable` items which span the connection.   |
+-------------------+-----------------------------------------------------------------------------------------------------+
| ENCAPSULATION     | Pointer to the :code:`Model` item with the given :code:`id`.                                        |
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

.. include:: ../snippets/snippet_annotator_auto_ids.rst

.. include:: ../snippets/snippet_annotator_clear_all_ids.rst

.. include:: ../snippets/snippet_annotator_find_item_known_type.rst

.. include:: ../snippets/snippet_annotator_find_item_unknown_type.rst

.. include:: ../snippets/snippet_annotator_find_duplicate_ids.rst

.. include:: ../snippets/snippet_annotator_retrieve_duplicated_ids.rst
