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
local name equal to :code:`model`. In this specification, the top-level
element is referred to as the :code:`model` element.

Specific information items
--------------------------

1. Every :code:`model` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

.. marker1_1

2. A :code:`model` element MAY contain one or more additional specific
   element children, each of which MUST be of one of the
   following types:

   #. A :code:`component` element; or

   #. A :code:`connection` element; or

   #. An :code:`encapsulation` element; or

   #. An :code:`import` element; or

   #. A :code:`units` element;


.. marker1_2

3. A :code:`model` element MUST NOT contain more than one :code:`encapsulation`
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

   1.

   .. container:: issue111

      Every :code:`import` element MUST contain an attribute
      in the namespace :code:`http://www.w3.org/1999/xlink`, with a local
      name equal to :code:`href`.

      The value of this attribute SHALL be a valid
      locator :code:`href`, as defined in
      :href_locator:`Section 5.4 of the XLink specification`.

      The :code:`href` attribute SHALL be treated according to the
      :xlink:`XLink specification`, by applying the rules for simple-type elements.

      When describing an :code:`import` element or one of its children, the phrase
      “imported CellML infoset” SHALL refer to the CellML infoset obtained
      by parsing the document referenced by the :code:`href` attribute.

.. marker2_1

2. Every :code:`import` element MAY contain one or more specific element
   children, each of which MUST be of one of the following types:

   #. An :code:`import units` element; or

   #. An :code:`import component` element.

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
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`units`, which
appears as a child of an :code:`import` element.

Specific information items
--------------------------

1. Every :code:`import units` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of the :code:`name` attribute MUST NOT be identical
   to the :code:`name` attribute of any other :code:`units` or
   :code:`import units` element in the CellML infoset.

.. marker3_1

2. Every :code:`import units` element MUST contain an unprefixed
   :code:`units_ref` attribute. The value of the :code:`units_ref` attribute
   MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of the :code:`units_ref`
   attribute MUST match the value of the :code:`name` attribute on a
   :code:`units` or :code:`import units` element in the imported CellML
   infoset.

   The value of the :code:`units_ref` attribute MUST NOT match the
   value of the :code:`units_ref` attribute on any sibling
   :code:`import units` element.

.. marker4

.. _import_component:

The import component element
============================

An :code:`import component` element information item (referred to in this
specification as an :code:`import component` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`component`, which appears as a child of an :code:`import` element.

Specific information items
--------------------------

1. Every :code:`import component` element MUST contain an unprefixed
   :code:`name` attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of the
   :code:`name` attribute MUST NOT
   be identical to the :code:`name` attribute of any other :code:`component` or
   :code:`import component` element in the CellML infoset.

2. Every :code:`import component` element MUST contain an unprefixed
   :code:`component_ref` attribute. The value of the :code:`component_ref`
   attribute MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of the
   :code:`component_ref` attribute MUST match the value of the :code:`name`
   attribute on a :code:`component` or :code:`import component` element in the
   imported CellML infoset. See also the
   :ref:`Component reference<specC_component_reference>`
   section.

.. marker5

.. _units:

The units element
=================

A :code:`units` element information item (referred to in this specification
as a :code:`units` element) is an element in the CellML
namespace with a local name equal to :code:`units`, and with a :code:`model`
element as its parent.

Specific information items
--------------------------

1. Every :code:`units` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

#. The value of the :code:`name` attribute MUST NOT be identical to the
   :code:`name` attribute of any other :code:`units` element or
   :code:`import units` element in the CellML infoset.

#. The value of the :code:`name` attribute MUST NOT be equal to the name of
   any of the units listed in the :ref:`Built-in units <table_built_in_units>`
   table.

#. A :code:`units` element MAY contain one or more :code:`unit` element
   children.

.. marker6

.. _unit:

The unit element
================

A :code:`unit` element information item (referred to in this specification
as a :code:`unit` element) is an element in the CellML
namespace with a local name equal to :code:`unit`, and with a :code:`units`
element as its parent.

Specific information items
--------------------------

1. Every :code:`unit` element MUST contain an unprefixed :code:`units`
   attribute. The value of the :code:`units` attribute MUST be
   a valid units reference, as defined in the
   :ref:`Units reference <units_reference>` section.

   #. For the purpose of the constraint in the next paragraph, the
      :code:`units` element inclusion digraph SHALL be defined as a
      conceptual digraph which SHALL contain one node for every
      :code:`units` element in the CellML model. **TODO infoset?**

      The :code:`units` element
      inclusion digraph SHALL contain an arc from :code:`units` element *A*
      to :code:`units` element *B* if and only if :code:`units` element *A*
      contains a :code:`unit` element with :code:`units` attribute value that
      is a units reference to :code:`units` element *B*.

   #. The value of the :code:`units` attribute MUST NOT be such that the
      :code:`units` element inclusion digraph contains one or more cycles
      (in other words, units definitions must not be cyclical).

.. marker6_1

2. A :code:`unit` element MAY contain any of the following unprefixed
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

A :code:`component` element information item (referred to in this
specification as a :code:`component` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`component`, and
which appears as a child of a :code:`model` element.

.. marker7_1

Specific information items
--------------------------

1. Every :code:`component` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a
   :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of the :code:`name` attribute MUST NOT be identical
   to the :code:`name` attribute on any other :code:`component` element or
   :code:`import component` element in the CellML infoset.

.. marker7_2

2. A :code:`component` element MAY contain one or more specific element
   children, each of which MUST be of one of the following types:

   #. A :code:`variable` element; or

   #. A :code:`reset` element; or

   #. A :code:`math` element.

.. marker8

.. _variable:

The variable element
====================

A :code:`variable` element information item (referred to in this
specification as a :code:`variable` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name
equal to :code:`variable`, and which appears as a child of a :code:`component` element.

Specific information items
--------------------------

1. Every :code:`variable` element MUST have each of the following unprefixed
   attributes:

   #. The :code:`name` attribute. The value of the :code:`name` attribute MUST
      be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of the :code:`name` attribute
      MUST NOT be identical to the :code:`name` attribute on any sibling
      :code:`variable` element.

   #. The :code:`units` attribute. The value of the :code:`units` attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`,
      and MUST meet the constraints described in the
      :ref:`Effect of units on variables<specC_effect_of_units_on_variables>`
      section.

#. Every :code:`variable` element MAY contain one or more of the following
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

A :code:`reset` element information item (referred to in this specification
as a :code:`reset` element) is an element in the CellML
namespace with a local name equal to :code:`reset`, and which appears as a
child of a :code:`component` element.

Specific information items
--------------------------

1. Every :code:`reset` element MUST have each of the following unprefixed
   attributes:

   #. The :code:`variable` attribute. The value of the :code:`variable`
      attribute MUST be a variable reference to a variable defined
      within the parent :code:`component` element of the :code:`reset` element.

   #. The :code:`test_variable` attribute. The value of the
      :code:`test_variable` attribute MUST be a variable reference to a
      variable defined within the parent :code:`component` element of the
      :code:`reset` element.

   #. The :code:`order` attribute. The value of the :code:`order` attribute
      MUST be an integer string.

      The value of the :code:`order` attribute MUST
      be unique for all :code:`reset` elements with :code:`variable` attributes
      that reference variables in the same connected variable set (see
      :ref:`Interpretation of map_variables<specC_map_variables>`).

#. A :code:`reset` element MUST contain exactly two element
   children, which MUST be one each of the following types:

   #. A :code:`test_value` element; and,

   #. A :code:`reset_value` element.

.. marker10

.. _test_value:

The test_value element
======================

A :code:`test_value` element information item (referred to in this
specification as a :code:`test_value` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name
equal to :code:`test_value`,
and which appears as a child of a :code:`reset` element.

Specific information items
--------------------------

#. A :code:`test_value` element MUST contain exactly one :code:`math` element
   child.

.. marker11

.. _reset_value:

The reset_value element
=======================

A :code:`reset_value` element information item (referred to in this
specification as a :code:`reset_value` element) is an element in the CellML
namespace with a local name equal to :code:`reset_value`,
and which appears as a child of a :code:`reset` element.

Specific information items
--------------------------

#. A :code:`reset_value` element MUST contain exactly one :code:`math` element
   child.

.. marker12

.. _math:

The math element
================

A :code:`math` element information item (referred to in this specification
as a :code:`math` element) is an element in the MathML
namespace that appears as a direct child of a :code:`component` element, a
:code:`test_value` element, or a :code:`reset_value` element.

Specific information items
--------------------------

#. A :code:`math` element MUST be the top-level of a content MathML tree, as
   described in :mathml2spec:`MathML 2.0`.

#. Each element child of a :code:`math` element MUST have
   an element-type name that is listed in the
   :ref:`Supported MathML Elements <table_supported_mathml_elements>` table.

#. Every variable name given using the MathML :code:`ci` element MUST be a
   :ref:`variable reference<specC_variable_reference>` to a :code:`variable`
   within the :code:`component` element that the :code:`math` element
   is contained.

#. Any MathML :code:`cn` elements MUST each have an attribute in the
   :ref:`CellML namespace<specA_cellml_namespace>`, with a local name equal to :code:`units`.
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

An :code:`encapsulation` element information item (referred to in this
specification as an :code:`encapsulation` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`encapsulation`, and which appears as a child of a :code:`model` element.

Specific information items
--------------------------

#. Every :code:`encapsulation` element MUST contain one or more
   :code:`component_ref` elements.

.. marker14

.. _component_ref:

The component_ref element
=========================

A :code:`component_ref` element information item (referred to in this
specification as a :code:`component_ref` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`component_ref`, and which appears as a child of an :code:`encapsulation`
element.

Specific information items
--------------------------

#. Every :code:`component_ref` element MUST contain an unprefixed
   :code:`component` attribute.

   The value of this attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`,
   and MUST match the :code:`name`
   attribute on a :code:`component` element or an :code:`import component`
   element in the CellML infoset.

#. Every :code:`component_ref` element MAY in turn contain one or more
   :code:`component_ref` element children.

#. A :code:`component_ref` element which is an immediate child of an
   :code:`encapsulation` element MUST each contain at least one
   :code:`component_ref` element child.

.. marker15

.. _connection:

The connection element
======================

A :code:`connection` element information item (referred to in this
specification as a :code:`connection` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`connection`,
and which appears as a child of a :code:`model` element.

Specific information items
--------------------------

#. Each :code:`connection` element MUST contain an unprefixed
   :code:`component_1` attribute. The value of the :code:`component_1`
   attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`component` or
   :code:`import component` element in the CellML infoset
   (see :ref:`Component reference<specC_component_reference>`).

#. Each :code:`connection` element MUST contain an unprefixed
   :code:`component_2` attribute. The value of the :code:`component_2`
   attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`component` or
   :code:`import component` element in the CellML infoset
   (see :ref:`Component reference <specC_component_reference>`).

   It MUST NOT be equal to the value of the :code:`component_1` attribute.

#. A CellML infoset MUST NOT contain more than one :code:`connection`
   element with a given pair of :code:`component`\ s referenced by the
   :code:`component_1` and :code:`component_2` attribute values, in any order.

#. Every :code:`connection` element MUST contain one or more
   :code:`map_variables` elements.

.. marker16

.. _map_variables:

The map_variables element
=========================

A :code:`map_variables` element information item (referred to in this
specification as a :code:`map_variables` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`map_variables`, and which appears as a child of a :code:`connection`
element.

Specific information items
--------------------------

#. Each :code:`map_variables` element MUST contain an unprefixed
   :code:`variable_1` attribute.

   The value of the :code:`variable_1` attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`variable` element child
   of the :code:`component` element or :code:`import component` element
   referenced by the :code:`component_1` attribute on the :code:`connection`
   element which is the parent of this element.

#. Each :code:`map_variables` element MUST contain an unprefixed
   :code:`variable_2` attribute.

   The value of the :code:`variable_2` attribute
   MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

   The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`variable` element child
   of the :code:`component` element or :code:`import component` element
   referenced by the :code:`component_2` attribute on the :code:`connection`
   element which is the parent of this element.

#. A :code:`connection` element MUST NOT contain more than one
   :code:`map_variables` element with a given :code:`variable_1` attribute
   value and :code:`variable_2` attribute value pair.

.. marker17
