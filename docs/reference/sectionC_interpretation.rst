===========================================
Section C: Interpretation of CellML models
===========================================

.. _specC_imports:

Interpretation of imports
-------------------------

#. Each :code:`import` element present in a CellML infoset (the importing
   infoset) SHALL define a new and separate instance of the CellML
   infoset referenced by the :code:`href` attribute (the imported infoset).
   See :ref:`Units reference<specC_units_reference>` and
   :ref:`Component reference<specC_component_reference>` for the specifics
   of importing units and components.

.. _specC_units_reference:

Units reference
---------------

#. A units reference SHALL be a CellML identifier and SHALL be
   interpreted dependent on the context of the CellML model in which it
   occurs, according to the units referencing rules defined later in
   this section.

#. A CellML infoset MUST NOT contain a units reference for which no
   referencing rule can be held to have been followed.

#. The units referencing rules are:

   #. Where there is a :code:`units` element with a :code:`name` attribute
      identical to the units reference, then the units reference SHALL
      refer to that :code:`units` element.

   #. Where there is an :code:`import units` element in the CellML infoset,
      such that the :code:`import units` element has a :code:`name` attribute
      identical to the units reference, then the units reference SHALL
      be treated with respect to referencing rules as if the units
      reference appeared in the imported infoset, and referring to the
      :code:`name` specified in the :code:`units_ref` attribute of the
      :code:`import units` element.

   #. Where the units reference is equal to the value in the ‘Name’
      column of the :ref:`Built-in units table<table_built_in_units>` ,
      then the units reference SHALL be a reference to the built-in units
      corresponding to that row of the table.

.. _table_built_in_units:

Table: Built-in units
~~~~~~~~~~~~~~~~~~~~~

+---------------+-------------------+--------------------------------+
| **Name**      | **Multiplier(s)** | **Unit reduction tuple**       |
|               |                   | (dimension, exponent) set      |
+---------------+-------------------+--------------------------------+
| ampere        | -                 | -                              |
+---------------+-------------------+--------------------------------+
| becquerel     | 1                 | (second, -1)                   |
+---------------+-------------------+--------------------------------+
| candela       | -                 | -                              |
+---------------+-------------------+--------------------------------+
| coulomb       | 1, 1              | (second, 1), (ampere,1)        |
+---------------+-------------------+--------------------------------+
| dimensionless | -                 | -                              |
+---------------+-------------------+--------------------------------+
| farad         | 1, 1, 1, 1        | (metre, -2), (kilogram, -1),   |
|               |                   | (second, 4), (ampere, 2)       |
+---------------+-------------------+--------------------------------+
| gram          | 0.001             | (kilogram,1 )                  |
+---------------+-------------------+--------------------------------+
| gray          | 1, 1              | (metre, 2), (second, -2)       |
+---------------+-------------------+--------------------------------+
| henry         | 1, 1, 1, 1        | (metre, 2), (kilogram, 1),     |
|               |                   | (second, -2), (ampere, -2)     |
+---------------+-------------------+--------------------------------+
| hertz         | 1                 | (second, -1)                   |
+---------------+-------------------+--------------------------------+
| joule         | 1, 1, 1           | (metre, 2), (kilogram, 1),     |
|               |                   | (second, -2)                   |
+---------------+-------------------+--------------------------------+
| katal         | 1, 1              | (second, -1), (mole, 1)        |
+---------------+-------------------+--------------------------------+
| kelvin        | -                 | -                              |
+---------------+-------------------+--------------------------------+
| kilogram      | -                 | -                              |
+---------------+-------------------+--------------------------------+
| litre         | 0.001             | (metre, 3)                     |
+---------------+-------------------+--------------------------------+
| lumen         | 1                 | (candela, 1)                   |
+---------------+-------------------+--------------------------------+
| lux           | 1, 1              | (metre, -2), (candela, 1)      |
+---------------+-------------------+--------------------------------+
| metre         | -                 | -                              |
+---------------+-------------------+--------------------------------+
| mole          | -                 | -                              |
+---------------+-------------------+--------------------------------+
| newton        | 1, 1, 1           | (metre, 1), (kilogram, 1),     |
|               |                   | (second, -2)                   |
+---------------+-------------------+--------------------------------+
| ohm           | 1, 1, 1, 1        | (metre, 2), (kilogram, 1),     |
|               |                   | (second, -3), (ampere, -2)     |
+---------------+-------------------+--------------------------------+
| pascal        | 1, 1, 1           | (metre, -1), (kilogram, 1),    |
|               |                   | (second, -2)                   |
+---------------+-------------------+--------------------------------+
| radian        | 1, 1              | (metre, 1), (metre, -1)        |
+---------------+-------------------+--------------------------------+
| second        | -                 | -                              |
+---------------+-------------------+--------------------------------+
| siemens       | 1, 1, 1, 1        | (metre, -2), (kilogram -1),    |
|               |                   | (second, 3), (ampere, 2)       |
+---------------+-------------------+--------------------------------+
| sievert       | 1, 1              | (metre, 2), (second, -2)       |
+---------------+-------------------+--------------------------------+
| steradian     | 1, 1              | (metre, 2), (metre, -2)        |
+---------------+-------------------+--------------------------------+
| tesla         | 1, 1, 1           | (kilogram, 1), (second, -2),   |
|               |                   | (ampere, -1)                   |
+---------------+-------------------+--------------------------------+
| volt          | 1, 1, 1, 1        | (metre, 2), (kilogram, 1),     |
|               |                   | (second , -3), (ampere, -1)    |
+---------------+-------------------+--------------------------------+
| watt          | 1, 1, 1           | (metre, 2), (kilogram, 1),     |
|               |                   | (second, -3)                   |
+---------------+-------------------+--------------------------------+
| weber         | 1, 1, 1, 1        | (metre, 2), (kilogram, 1),     |
|               |                   | (second, -2), (ampere, -1)     |
+---------------+-------------------+--------------------------------+

.. _specC_units:

Interpretation of units
-----------------------

#. The :code:`units` element SHALL be interpreted as the product of its
   :code:`unit` element children, according to the following rules:

   #. The prefix term is a conceptual property of :code:`unit` elements. If
      the :code:`unit` element does not have a :code:`prefix` attribute
      information item, the prefix term SHALL have value 0. If the
      :code:`prefix` attribute information item has a value which is an
      integer string, then the value of the prefix term SHALL be the
      numerical value of that string. Otherwise, the :code:`prefix`
      attribute information item MUST have a value taken from the ‘Name’
      column of the :ref:`Prefix values table<table_prefix_values>`, and the
      prefix term SHALL have the value taken from the ‘Value’ column of
      the same row.

   #. The exponent term is a conceptual property of :code:`unit` elements.
      If a :code:`unit` element has no :code:`exponent` attribute information
      item, the exponent term SHALL have value 1.0. Otherwise, the value
      of the :code:`exponent` attribute information item MUST be a real
      number string, and the value of the exponent term SHALL be the
      numerical value of that string.

   #. The multiplier term is a conceptual property of :code:`unit` elements.
      If a :code:`unit` element has no :code:`multiplier` attribute information
      item, the multiplier term SHALL have value 1.0. Otherwise, the
      value of the :code:`multiplier` attribute information item MUST be a
      real number string, and the value of the multiplier term SHALL be
      the numerical value of that string.

   #. The relationship between the product, *P,* of numerical values
      given in each and every child :code:`unit` element units, to a
      numerical value, *x,* with units given by the encompassing
      :code:`units` element, SHALL be

      .. image:: images/equation_units_expansion.png
          :align: center
          :width: 50%

      where: *u\ x* denotes the units of the :code:`units` element; *p\ i*,
      *e\ i*, *m\ i*, and *u\ i* refer to the prefix, exponent and
      multiplier terms and units of the *i*\ th :code:`unit` child element,
      respectively. Square brackets encompass the units of numerical
      values.

#. For the purposes of this specification, the “irreducible units” of a
   model SHALL consist of 1) the units defined in a model that are not
   defined in terms of other units (i.e. the set of :code:`units` elements
   in the CellML model which have no :code:`unit` child elements), and 2)
   built-in irreducible units (those built-in units with ‘-’ in the
   ‘Unit Reduction...’ column of the
   :ref:`Built-in units<table_built_in_units>`
   table) referenced by variables or other units in the model.

#. The “unit reduction” is a conceptual property of :code:`units` elements.
   It consists of a set of tuples where each tuple is composed of a) a
   unit name and b) a real-valued exponent. Tuples SHALL be determined
   as follows:

   #. If the :code:`units` element has no :code:`unit` child elements, then the
      set of tuples SHALL have a single member, which SHALL consist of
      the name of the :code:`units` element and the exponent 1.0.

   #. If the :code:`units` element has one or more :code:`unit` child elements,
      then the set of tuples SHALL consist of the entire collection of
      tuples given by all :code:`unit` child elements. Tuples for each
      :code:`unit` child element SHALL be determined as follows:

      #. Where the units reference of the :code:`unit` child element is to a
         single unit which is an irreducible unit, then the set of
         tuples SHALL have a single member, which SHALL consist of the
         name of the irreducible unit being referenced and the exponent
         1.0.

      #. Where the units reference of the :code:`unit` child element is to
         built-in units other than an irreducible unit, then the tuples
         SHALL be derived directly from the :ref:`Built-in
         units<table_built_in_units>` table. Specifically, the set of
         tuples SHALL consist of the tuples given in the ‘Unit reduction
         tuple ... set’ column of the row for which the value in the
         ‘Name’ column matches the name of the units reference.

      #. Where the units reference of the :code:`unit` child element is to a
         unit which is neither built-in, nor an irreducible unit, the
         set of tuples SHALL be defined recursively as the set of tuples
         for the :code:`units` element so referenced.

      #. The exponents of each tuple in the set for the current :code:`unit`
         element, as derived by following rule 3.2.1, 3.2.2 or 3.2.3
         above, SHALL be multiplied by the exponent term of the current,
         referencing, :code:`unit` element.

   #. Tuples which have the name element of ‘dimensionless’ SHALL be
      removed from the set of tuples. Note that this can result in the
      set of tuples being empty.

   #. Where the set of tuples consists of tuples which have the same
      name element, those tuples SHALL be combined into a single tuple
      with that name element and an exponent being the sum of the
      combined tuples’ exponents. If the resulting tuple’s exponent term
      is zero, the tuple SHALL be removed from the set of tuples. Note
      that this can result in the set of tuples being empty.

.. _table_prefix_values:

Table: Prefix values
~~~~~~~~~~~~~~~~~~~~

======== =========
**Name** **Value**
yotta    24
zetta    21
exa      18
peta     15
tera     12
giga     9
mega     6
kilo     3
hecto    2
deca     1
deci     −1
centi    −2
milli    −3
micro    −6
nano     −9
pico     −12
femto    −15
atto     −18
zepto    −21
yocto    −24
======== =========

.. _specC_component_reference:

Component reference
-------------------

#. A component reference SHALL be the name of a component, and SHALL be
   interpreted based on the context within the CellML model in which it
   occurs.

#. A component reference present in an information item which is a
   descendant of a :code:`model` element SHALL be identical to either the
   :code:`name` attribute on a :code:`component` element or to the :code:`name`
   attribute on an :code:`import component` element.

#. A component reference which is identical to the :code:`name` attribute on
   a :code:`component` element SHALL be treated as a reference to that
   :code:`component` element.

#. A component reference which is identical to the :code:`name` attribute on
   an :code:`import component` element SHALL be treated for the purposes of
   referencing as if the component reference appeared in the imported
   model, and referred to element with the :code:`name` specified in the
   :code:`component_ref` attribute of the :code:`import component` element.

#. It is noted, for the avoidance of doubt, that CellML models MAY apply
   the previous rule recursively, to reference an :code:`import component`
   element which in turn references another :code:`import component`
   element.

.. _specC_variable_reference:

Variable reference
------------------

#. When present in an information item which is a descendant of a
   :code:`component` element, a variable reference SHALL be the name of a
   variable, and SHALL refer to the :code:`variable` element in that
   component with a :code:`name` attribute identical to the variable
   reference.

#. In all other cases, a variable reference SHALL consist of a component
   reference and a variable name. In this case, the variable reference
   SHALL be treated as if it was just the variable name present in the
   :code:`component` element referenced by the component reference.

.. _specC_initial_values:

Interpretation of initial values
--------------------------------

#. The :code:`initial_value` attribute of a :code:`variable` element MUST
   either be a real number string, or a variable reference (see 19.5).

#. The conditions when initial values hold are (by design) not defined
   in a CellML model document.

#. Where the :code:`initial_value` attribute has a real number value, it
   SHALL be interpreted as a statement that the variable on which the
   attribute appears is equal to that real number value, under the
   conditions when the initial value holds.

#. Where the :code:`initial_value` attribute is a variable reference, it
   SHALL be interpreted as a statement that the variable on which the
   attribute appears is equal to the referenced variable under the
   conditions when the initial value holds.

.. _specC_effect_of_units_on_variables:

Effect of units on variables
----------------------------

#. The value of the :code:`units` attribute on every :code:`variable` element
   MUST be a valid units reference. The target of this units reference
   is referred to as the variable units, and the corresponding unit
   reduction (see :ref:`Interpretation of units<specC_units>`) is referred
   to as the variable unit reduction.

.. _specC_mathematics:

Interpretation of mathematics
-----------------------------

#. The following :code:`component` elements SHALL, for the purposes of this
   specification, be “pertinent component elements”:

   #. All :code:`component` elements in the top-level CellML infoset for the
      CellML model;

   #. All :code:`component` elements referenced by :code:`import component`
      elements (see
      :ref:`The import component element <specC_component_reference>`)
      in the top-level CellML infoset; and

   #. All :code:`component` elements which are descendants in the
      encapsulation digraph (see
      :ref:`Interpretation of encapsulation <specC_encapsulation>`)
      of a pertinent :code:`component` element.

#. Every MathML element in the CellML model which appears as a direct
   child information item of a MathML :code:`math` element information item,
   which in turn appears as a child information item of a pertinent
   :code:`component` element, SHALL be treated, in terms of the semantics of
   the mathematical model, as a statement which holds true
   unconditionally.

#. Units referenced by a :code:`units` attribute information item SHALL NOT
   affect the mathematical interpretation of the CellML model.

.. _specC_encapsulation:

Interpretation of encapsulation
-------------------------------

#. For the purposes of this specification, there SHALL be a “conceptual
   encapsulation digraph” in which there is EXACTLY one node for every
   component in the CellML model. Therefore the encapsulation digraph
   will not contain any loops.

#. Where a :code:`component_ref` element appears as a child of another
   :code:`component_ref` element, there SHALL be an arc in the encapsulation
   digraph, and that arc SHALL be from the node corresponding to the
   component referenced by the parent :code:`component_ref` element, and to
   the node corresponding to the component referenced by the child
   :code:`component_ref` element.

#. The encapsulated set for a component *A* SHALL be the set of all
   components *B* such that there exists an arc in the encapsulation
   digraph from the node corresponding to *A* to the node corresponding
   to *B*.

#. The encapsulation parent for a component *A* SHALL be the component
   corresponding to the node which is the parent node in the
   encapsulation digraph of the node corresponding to *A*.

#. The sibling set for a component *A* SHALL be the set of all
   components which have the same encapsulation parent as *A*, or in the
   case that *A* has no encapsulation parent, SHALL be the set of all
   components which do not have an encapsulation parent.

#. The hidden set for a component *A* SHALL be the set of all components
   *B* where component *B* is not in the encapsulated set for component
   *A*, and component *B* is not the encapsulation parent of component
   *A*, and component *B* is not in the sibling set for component *A*.

#. There MUST NOT be a :code:`connection` element such that the component
   referenced by the :code:`component_1` attribute is in the hidden set of
   the component referenced by the :code:`component_2` attribute, nor vice
   versa.

.. _specC_map_variables:

Interpretation of map_variables
-------------------------------

#.  For the purposes of this specification, the variable equivalence
    (conceptual) network SHALL be an undirected graph with one node for
    every :code:`variable` element in the CellML model. The arcs of this
    graph SHALL be equivalences defined in the CellML model.

#.  For each :code:`map_variables` element present in the CellML model, we
    define variables *A* and *B* for use in the rules in this section as
    follows.

    #. Variable *A* SHALL be the variable referenced by the encompassing
       :code:`connection` element’s :code:`component_1` and this
       :code:`map_variables` element’s :code:`variable_1` attribute.

    #. Variable *B* SHALL be the variable referenced by the encompassing
       :code:`connection` element’s :code:`component_2` and this
       :code:`map_variables` element’s :code:`variable_2` attribute.

#.  For every :code:`map_variables` element present in the CellML model,
    there SHALL be an arc in the variable equivalence network.

    #. One endpoint of the arc in the variable equivalence network SHALL
       be the node corresponding to variable *A*.

    #. One endpoint of the arc in the variable equivalence network SHALL
       be the node corresponding to variable *B*.

#.  CellML models MUST NOT contain any pair of :code:`map_variables`
    elements which duplicates an existing arc in the variable
    equivalence network.

#.  The variable equivalence network MUST NOT contain any cycles.

#.  For each :code:`map_variables` element present in the CellML model, the
    variable unit reduction (see
    :ref:`Effect of units on variables <specC_effect_of_units_on_variables>` )
    of variable *A* MUST have an identical set
    of tuples to the variable unit reduction of variable *B*. Two sets
    of tuples SHALL be considered identical if all of the tuples from
    each set are present in the other, or if both sets are empty. Two
    tuples are considered identical if and only if both the name and
    exponent value of each tuple are equivalent.

#.  Tuples differing by a multiplying factor in their unit reduction
    MUST be taken into account when interpreting the numerical values of
    the variables (see :ref:`Interpretation of units<specC_units>`).

#.  For a given variable, the available interfaces SHALL be determined
    by the :code:`interface` attribute information item on the corresponding
    :code:`variable` element as follows.

    #. A value of :code:`public` specifies that the variable has a public
       interface.

    #. A value of :code:`private` specifies that the variable has a private
       interface.

    #. A value of :code:`public_and_private` specifies that the variable has
       both a public and a private interface.

    #. A value of :code:`none` specifies that the variable has no interface.

    #. If the :code:`interface` attribute information item is absent, then
       the variable has no interface.

#.  The applicable interfaces for variables *A* and *B* SHALL be defined
    as follows.

    #. When the parent :code:`component` element of variable *A* is in the
       sibling set of the parent :code:`component` element of variable *B*,
       the applicable interface for both variables *A* and *B* SHALL be
       the public interface.

    #. When the parent :code:`component` element of variable *A* is in the
       encapsulated set of the parent :code:`component` element of variable
       *B*, the applicable interface for variable *A* SHALL be the
       public interface, and the applicable interface for variable *B*
       SHALL be the private interface.

    #. When the parent :code:`component` element of variable *B* is in the
       encapsulated set of the parent :code:`component` element of variable
       *A*, the applicable interface for variable *A* SHALL be the
       private interface, and the applicable interface for variable *B*
       SHALL be the public interface.

#.  CellML models MUST only contain :code:`map_variables` elements where the
    interface of variable *A* and the interface of variable *B* are
    applicable interfaces.

#.  The :code:`variable` elements in a CellML model SHALL be treated as
    belonging to a single “connected variable set”. Each set of
    connected variables is the set of all :code:`variable` elements for
    which the corresponding nodes in the variable equivalence network
    form a connected subgraph. Each set of connected variables
    represents one variable in the underlying mathematical model.

.. _specC_variable_resets:

Interpretation of variable resets
---------------------------------

#. Each :code:`reset` element describes a change to be applied to the
   variable referenced by the :code:`variable` attribute when specified
   conditions are met during the simulation of the model.

#. All :code:`reset` elements SHALL be considered sequentially for the
   connected variable set (see
   :ref:`Interpretation of map_variables<specC_map_variables>`) to which
   the referenced variable
   belongs. The sequence SHALL be determined by the value of the reset
   element’s :code:`order` attribute, lowest (least positive / most
   negative) having priority.

#. The condition under which a reset occurs SHALL be defined by the
   equality of the reset element’s :code:`test_variable` attribute and the
   evaluation of the MathML expression encoded in the :code:`test_value`.

#. When a reset occurs, the variable referenced by the reset element’s
   :code:`variable` attribute SHALL be set to the result of evaluating the
   MathML expression encoded in the :code:`reset_value`.
