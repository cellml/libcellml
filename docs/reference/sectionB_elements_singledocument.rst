.. _sectionB:

.. sectnum::

====================================
Section B: Element information items
====================================

.. marker1

.. _model:

The model element
=================

Top-level of CellML infosets
----------------------------

The top-level element information item in a CellML infoset MUST be an
element in the :ref:`CellML namespace<specA_cellml_namespace>` with a
local name equal to |model|_. In this specification, the top-level
element is referred to as the |model|_ element.

Specific information items
--------------------------

1. Every |model|_ element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

.. marker1_1

2. A |model|_ element MAY contain one or more additional specific
   element children, each of which MUST be of one of the
   following types:

   #. A |component|_ element; or

   #. A |connection|_ element; or

   #. An |encapsulation|_ element; or

   #. An |import|_ element; or

   #. A |units|_ element;


.. marker1_2

3. A |model|_ element MUST NOT contain more than one |encapsulation|_
   elements.

.. marker2

.. _import:

The import element
==================

An :code:`import` element information item (referred to in this
specification as an :code:`import` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`import`.

Specific information items
--------------------------

1. Every :code:`import` element MUST contain an attribute
   in the namespace :code:`http://www.w3.org/1999/xlink`, with a local
   name equal to :code:`href`. The value of this attribute SHALL be a valid
   locator :code:`href`, as defined in :href_locator:`Section 5.4` of the
   :xlink:`XLink specification`. The
   :code:`href` attribute SHALL be treated according to the
   :xlink:`XLink specification`, by applying the rules for simple-type elements. When
   describing an :code:`import` element or one of its children, the phrase
   “imported CellML infoset” SHALL refer to the CellML infoset obtained
   by parsing the document referenced by the :code:`href` attribute.

.. marker2_1

2. Every :code:`import` element MAY contain one or more specific element
   children, each of which MUST be of one of the following types:

   #. An :code:`import units` element; or

   #. An |import_component|_ element.

.. marker2_2

3. Any CellML infoset imported, directly or indirectly, by the imported
   CellML infoset MUST NOT be semantically equivalent to the importing
   CellML infoset (see
   :ref:`Semantically equivalent CellML infosets <specA_semantic_equivalence>`
   ).

.. marker3

.. _import_units:

The import units element
========================

An :code:`import units` element information item (referred to in this
specification as an :code:`import units` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to |units|_, which
appears as a child of an :code:`import` element.

Specific information items
--------------------------

1. Every :code:`import units` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of the :code:`name` attribute MUST NOT be identical
   to the :code:`name` attribute of any other |units|_ or
   :code:`import units` element in the CellML infoset.

.. marker3_1

2. Every :code:`import units` element MUST contain an unprefixed
   :code:`units_ref` attribute. The value of the :code:`units_ref` attribute
   MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of the :code:`units_ref`
   attribute MUST match the value of the :code:`name` attribute on a
   |units|_ or :code:`import units` element in the imported CellML
   infoset. The value of the :code:`units_ref` attribute MUST NOT match the
   value of the :code:`units_ref` attribute on any sibling
   :code:`import units` element.

.. marker4

.. _import_component:

The import component element
============================

An |import_component|_ element information item (referred to in this
specification as an |import_component|_ element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
|component|_, which appears as a child of an :code:`import` element.

Specific information items
--------------------------

1. Every |import_component|_ element MUST contain an unprefixed
   :code:`name` attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`. The value of the
   :code:`name` attribute MUST NOT
   be identical to the :code:`name` attribute of any other |component|_ or
   |import_component|_ element in the CellML infoset.

2. Every |import_component|_ element MUST contain an unprefixed
   :code:`component_ref` attribute. The value of the :code:`component_ref`
   attribute MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of the
   :code:`component_ref` attribute MUST match the value of the :code:`name`
   attribute on a |component|_ or |import_component|_ element in the
   imported CellML infoset. See also the
   :ref:`Component reference<specC_component_reference>`
   section.

.. marker5

.. _units:

The units element
=================

A |units|_ element information item (referred to in this specification
as a |units|_ element) is an element in the CellML
namespace with a local name equal to |units|_, and with a |model|_
element as its parent.

Specific information items
--------------------------

1. Every |units|_ element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

#. The value of the :code:`name` attribute MUST NOT be identical to the
   :code:`name` attribute of any other |units|_ element or
   :code:`import units` element in the CellML infoset.

#. The value of the :code:`name` attribute MUST NOT be equal to the name of
   any of the units listed in the :ref:`Built-in units <table_built_in_units>`
   table.

#. A |units|_ element MAY contain one or more |unit|_ element
   children.

.. marker6

.. _unit:

The unit element
================

A |unit|_ element information item (referred to in this specification
as a |unit|_ element) is an element in the CellML
namespace with a local name equal to |unit|_, and with a |units|_
element as its parent.

Specific information items
--------------------------

1. Every |unit|_ element MUST contain an unprefixed |units|_
   attribute. The value of the |units|_ attribute MUST be
   a valid units reference, as defined in the
   :ref:`Units reference <units_reference>` section.

   #. For the purpose of the constraint in the next paragraph, the
      |units|_ element inclusion digraph SHALL be defined as a
      conceptual digraph which SHALL contain one node for every
      |units|_ element in the CellML model. **TODO infoset?**
      The |units|_ element
      inclusion digraph SHALL contain an arc from |units|_ element *A*
      to |units|_ element *B* if and only if |units|_ element *A*
      contains a |unit|_ element with |units|_ attribute value that
      is a units reference to |units|_ element *B*.

   #. The value of the |units|_ attribute MUST NOT be such that the
      |units|_ element inclusion digraph contains one or more cycles
      (in other words, units definitions must not be cyclical).

.. marker6_1

2. A |unit|_ element MAY contain any of the following unprefixed
   attributes:

   #. The :code:`prefix` attribute. If present, the value of the attribute
      MUST meet the constraints specified in the
      :ref:`Interpretation of units <specC_units>` section.

   #. The :code:`multiplier` attribute. If present, the value of the
      attribute MUST be a real number string.

   #. The :code:`exponent` attribute. If present, the value of the attribute
      MUST be a real number string.

.. marker7

.. _component:

The component element
=====================

A |component|_ element information item (referred to in this
specification as a |component|_ element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to |component|_, and
which appears as a child of a |model|_ element.

.. marker7_1

Specific information items
--------------------------

1. Every |component|_ element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of the :code:`name` attribute MUST NOT be identical
   to the :code:`name` attribute on any other |component|_ element or
   |import_component|_ element in the CellML infoset.

.. marker7_2

2. A |component|_ element MAY contain one or more specific element
   children, each of which MUST be of one of the following types:

   #. A |variable|_ element; or

   #. A |reset|_ element; or

   #. A |math|_ element.

.. marker8

.. _variable:

The variable element
====================

A |variable|_ element information item (referred to in this
specification as a |variable|_ element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name
equal to |variable|_, and which appears as a child of a |component|_ element.

Specific information items
--------------------------

1. Every |variable|_ element MUST have each of the following unprefixed
   attributes:

   #. The :code:`name` attribute. The value of the :code:`name` attribute MUST
      be a :ref:`valid CellML identifier<specA_cellml_identifier>`. The value
      of the :code:`name` attribute
      MUST NOT be identical to the :code:`name` attribute on any sibling
      |variable|_ element.

   #. The |units|_ attribute. The value of the |units|_ attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`,
      and MUST meet the constraints described in the
      :ref:`Effect of units on variables<specC_effect_of_units_on_variables>`
      section.

#. Every |variable|_ element MAY contain one or more of the following
   unprefixed attributes:

   #. The :code:`interface` attribute. If the attribute is present, it MUST
      have value of :code:`public`, :code:`private`,
      :code:`public_and_private`, or :code:`none`.

   #. The :code:`initial_value` attribute. If the attribute is present, it
      MUST meet the requirements described by the
      :ref:`Interpretation of initial values<specC_initial_values>` section.

.. marker9

.. _reset:

The reset element
=================

A |reset|_ element information item (referred to in this specification
as a |reset|_ element) is an element in the CellML
namespace with a local name equal to |reset|_, and which appears as a
child of a |component|_ element.

Specific information items
--------------------------

1. Every |reset|_ element MUST have each of the following unprefixed
   attributes:

   #. The |variable|_ attribute. The value of the |variable|_
      attribute MUST be a variable reference to a variable defined
      within the parent |component|_ element of the |reset|_ element.

   #. The :code:`test_variable` attribute. The value of the
      :code:`test_variable` attribute MUST be a variable reference to a
      variable defined within the parent |component|_ element of the
      |reset|_ element.

   #. The :code:`order` attribute. The value of the :code:`order` attribute
      MUST be an integer string. The value of the :code:`order` attribute MUST
      be unique for all |reset|_ elements with |variable|_ attributes
      that reference variables in the same connected variable set (see
      :ref:`Interpretation of map_variables<specC_map_variables>`).

#. A |reset|_ element MUST contain exactly two element
   children, which MUST be one each of the following types:

   #. A |test_value|_ element; and,

   #. A |reset_value|_ element.

.. marker10

.. _test_value:

The test_value element
======================

A |test_value|_ element information item (referred to in this
specification as a |test_value|_ element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to |test_value|_,
and which appears as a child of a |reset|_ element.

Specific information items
--------------------------

#. A |test_value|_ element MUST contain exactly one |math|_ element
   child.

.. marker11

.. _reset_value:

The reset_value element
=======================

A |reset_value|_ element information item (referred to in this
specification as a |reset_value|_ element) is an element in the CellML
namespace with a local name equal to |reset_value|_,
and which appears as a child of a |reset|_ element.

Specific information items
--------------------------

#. A |reset_value|_ element MUST contain exactly one |math|_ element
   child.

.. marker12

.. _math:

The math element
================

A |math|_ element information item (referred to in this specification
as a |math|_ element) is an element in the MathML
namespace that appears as a direct child of a |component|_ element, a
|test_value|_ element, or a |reset_value|_ element.

Specific information items
--------------------------

#. A |math|_ element MUST be the top-level of a content MathML tree, as
   described in :mathml2spec:`MathML 2.0`.

#. Each element child of a |math|_ element MUST have
   an element-type name that is listed in the
   :ref:`Supported MathML Elements <table_supported_mathml_elements>` table.

#. Every variable name given using the MathML :code:`ci` element MUST be a
   :ref:`variable reference<specC_variable_reference>` to a |variable|_
   within the |component|_ element that the |math|_ element
   is contained.

#. Any MathML :code:`cn` elements MUST each have an attribute in the
   :ref:`CellML namespace<specA_cellml_namespace>`, with a local name equal to |units|_.
   The value of this attribute MUST be a valid units
   reference.

#. The :code:`cn` element MUST be one of the following
   :mathml2types:`types` : real or e-notation.

#. The :code:`cn` element MUST be of base 10.

.. _table_supported_mathml_elements:

Table: Supported MathML Elements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

+----------------------------------+----------------------------------+
| **Element Category**             | **Element List**                 |
+----------------------------------+----------------------------------+
| Simple Operands                  | <ci>, <cn>, <sep>                |
+----------------------------------+----------------------------------+
| Basic Structural                 | <apply>, <piecewise>, <piece>,   |
|                                  | <otherwise>                      |
+----------------------------------+----------------------------------+
| Relational and Logical Operators | <eq>, <neq>, <gt>, <lt>, <geq>,  |
|                                  | <leq>, <and>, <or>, <xor>, <not> |
+----------------------------------+----------------------------------+
| Arithmetic Operators             | <plus>, <minus>, <times>,        |
|                                  | <divide>, <power>, <root>,       |
|                                  | <abs>, <exp>, <ln>, <log>,       |
|                                  | <floor>, <ceiling>, <min>,       |
|                                  | <max>, <rem>,                    |
+----------------------------------+----------------------------------+
| Calculus Elements                | <diff>                           |
+----------------------------------+----------------------------------+
| Qualifier Elements               | <bvar>, <logbase>, <degree>      |
|                                  | (child of <root> or <diff>)      |
+----------------------------------+----------------------------------+
| Trigonometric Operators          | <sin>, <cos>, <tan>, <sec>,      |
|                                  | <csc>, <cot>,                    |
|                                  |                                  |
|                                  | <sinh>, <cosh>, <tanh>, <sech>,  |
|                                  | <csch>, <coth>, <arcsin>,        |
|                                  | <arccos>, <arctan>,              |
|                                  |                                  |
|                                  | <arcsec>, <arccsc>, <arccot>,    |
|                                  | <arcsinh>, <arccosh>, <arctanh>, |
|                                  | <arcsech>, <arccsch>, <arccoth>  |
+----------------------------------+----------------------------------+
| Mathematical and Logical         | <pi>, <exponentiale>,            |
| Constants                        | <notanumber>, <infinity>,        |
|                                  | <true>, <false>                  |
+----------------------------------+----------------------------------+

.. marker13

.. _encapsulation:

The encapsulation element
=========================

An |encapsulation|_ element information item (referred to in this
specification as an |encapsulation|_ element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
|encapsulation|_, and which appears as a child of a |model|_ element.

Specific information items
--------------------------

#. Every |encapsulation|_ element MUST contain one or more
   :code:`component_ref` elements.

.. marker14

.. _component_ref:

The component_ref element
=========================

A :code:`component_ref` element information item (referred to in this
specification as a :code:`component_ref` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`component_ref`, and which appears as a child of an |encapsulation|_
element.

Specific information items
--------------------------

#. Every :code:`component_ref` element MUST contain an unprefixed
   |component|_ attribute. The value of this attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`,
   and MUST match the :code:`name`
   attribute on a |component|_ element or an |import_component|_
   element in the CellML infoset.

#. Every :code:`component_ref` element MAY in turn contain one or more
   :code:`component_ref` element children.

#. A :code:`component_ref` element which is an immediate child of an
   |encapsulation|_ element MUST each contain at least one
   :code:`component_ref` element child.

.. marker15

.. _connection:

The connection element
======================

A |connection|_ element information item (referred to in this
specification as a |connection|_ element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to |connection|_,
and which appears as a child of a |model|_ element.

Specific information items
--------------------------

#. Each |connection|_ element MUST contain an unprefixed
   :code:`component_1` attribute. The value of the :code:`component_1`
   attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of this attribute MUST
   be equal to the :code:`name` attribute on a |component|_ or
   |import_component|_ element in the CellML infoset
   (see :ref:`Component reference<specC_component_reference>`).

#. Each |connection|_ element MUST contain an unprefixed
   :code:`component_2` attribute. The value of the :code:`component_2`
   attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of this attribute MUST
   be equal to the :code:`name` attribute on a |component|_ or
   |import_component|_ element in the CellML infoset
   (see :ref:`Component reference <specC_component_reference>`).
   It MUST NOT be equal to the value of the :code:`component_1` attribute.

#. A CellML infoset MUST NOT contain more than one |connection|_
   element with a given pair of |component|_\ s referenced by the
   :code:`component_1` and :code:`component_2` attribute values, in any order.

#. Every |connection|_ element MUST contain one or more
   |map_variables|_ elements.

.. marker16

.. _map_variables:

The map_variables element
=========================

A |map_variables|_ element information item (referred to in this
specification as a |map_variables|_ element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
|map_variables|_, and which appears as a child of a |connection|_
element.

Specific information items
--------------------------

#. Each |map_variables|_ element MUST contain an unprefixed
   :code:`variable_1` attribute. The value of the :code:`variable_1` attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.
   The value of this attribute MUST
   be equal to the :code:`name` attribute on a |variable|_ element child
   of the |component|_ element or |import_component|_ element
   referenced by the :code:`component_1` attribute on the |connection|_
   element which is the parent of this element.

#. Each |map_variables|_ element MUST contain an unprefixed
   :code:`variable_2` attribute. The value of the :code:`variable_2` attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`. The
   value of this attribute MUST
   be equal to the :code:`name` attribute on a |variable|_ element child
   of the |component|_ element or |import_component|_ element
   referenced by the :code:`component_2` attribute on the |connection|_
   element which is the parent of this element.

#. A |connection|_ element MUST NOT contain more than one
   |map_variables|_ element with a given :code:`variable_1` attribute
   value and :code:`variable_2` attribute value pair.

.. marker17
