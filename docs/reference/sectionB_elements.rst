.. _sectionB:

.. sectnum::

====================================
Section B: Element information items
====================================

.. marker_model_start

.. _model:

The model element
=================

Top-level of CellML infosets
----------------------------

.. container:: issue-model-element

   The top-level element information item in a :ref:`CellML infoset<specA_cellml_infoset>` MUST be an
   element in the :ref:`CellML namespace<specA_cellml_namespace>` with a
   local name equal to :code:`model`. In this specification, the top-level
   element is referred to as the :code:`model` element.

Specific information items
--------------------------

.. container:: issue-model-name

   1. Every :code:`model` element MUST contain a :code:`name`
      attribute. The value of the :code:`name` attribute MUST be a
      :ref:`valid CellML identifier<specA_cellml_identifier>`.

.. marker_model_1

.. container:: issue-model-child

   2. A :code:`model` element MAY contain one or more additional specific
      element children, each of which MUST be of one of the
      following types:

      #. A :code:`component` element; or

      #. A :code:`connection` element; or

      #. An :code:`encapsulation` element; or

      #. An :code:`import` element; or

      #. A :code:`units` element;


.. marker_model_2

.. container:: issue-model-more-than-one-encapsulation

   3. A :code:`model` element MUST NOT contain more than one :code:`encapsulation`
      elements.

.. marker_model_end
.. marker_import_start

.. _import:

The import element
==================

An :code:`import` element information item (referred to in this
specification as an :code:`import` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>`
with a local name equal to :code:`import`.

Specific information items
--------------------------

.. container:: issue-import-href

   1. Every :code:`import` element MUST contain an attribute
      in the namespace :code:`http://www.w3.org/1999/xlink`, with a local
      name equal to :code:`href`.

      The value of this attribute SHALL be a valid
      locator :code:`href`, as defined in
      :href_locator:`Section 5.4 of the XLink specification`.

      The :code:`href` attribute SHALL be treated according to the
      :xlink:`XLink specification`, by applying the rules for simple-type elements.

      When describing an :code:`import` element or one of its children, the phrase
      “imported CellML infoset” SHALL refer to the
      :ref:`CellML infoset<specA_cellml_infoset>` obtained
      by parsing the document referenced by the :code:`href` attribute.

.. marker_import_1

.. container:: issue-import-child

   2. Every :code:`import` element MAY contain one or more specific element
      children, each of which MUST be of one of the following types:

      #. An :code:`import units` element; or

      #. An :code:`import component` element.

.. marker_import_2

.. container:: issue-import-circular

   3. Any :ref:`CellML infoset<specA_cellml_infoset>` imported, directly or indirectly, by the imported
      CellML infoset MUST NOT be semantically equivalent to the importing
      CellML infoset (see
      :ref:`Semantically equivalent CellML infosets <specA_semantic_equivalence>`
      ).

.. marker_import_end
.. marker_import_units_start

.. _import_units:

The import units element
========================

An :code:`import units` element information item (referred to in this
specification as an :code:`import units` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`units`, which
appears as a child of an :code:`import` element.

Specific information items
--------------------------

.. contianer:: issue-import-units-name

   1. Every :code:`import units` element MUST contain a :code:`name`
      attribute. The value of the :code:`name` attribute MUST be a
      :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of the :code:`name` attribute MUST NOT be identical
      to the :code:`name` attribute of any other :code:`units` or
      :code:`import units` element in the :ref:`CellML infoset<specA_cellml_infoset>`.

.. marker_import_units_1

.. container:: issue-import-units-ref

   2. Every :code:`import units` element MUST contain a
      :code:`units_ref` attribute. The value of the :code:`units_ref` attribute
      MUST be a
      :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of the :code:`units_ref`
      attribute MUST match the value of the :code:`name` attribute on a
      :code:`units` or :code:`import units` element in the imported CellML
      infoset.

.. marker_import_units_end
.. marker_import_component_start

.. _import_component:

The import component element
============================

An :code:`import component` element information item (referred to in this
specification as an :code:`import component` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`component`, which appears as a child of an :code:`import` element.

Specific information items
--------------------------

.. container:: issue-import-component-name

   1. Every :code:`import component` element MUST contain a
      :code:`name` attribute. The value of the :code:`name` attribute MUST be a
      :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of the :code:`name` attribute MUST NOT
      be identical to the :code:`name` attribute of any other :code:`component` or
      :code:`import component` element in the :ref:`CellML infoset<specA_cellml_infoset>`.

.. container:: issue-import-component-ref

   2. Every :code:`import component` element MUST contain a
      :code:`component_ref` attribute. The value of the :code:`component_ref`
      attribute MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of the
      :code:`component_ref` attribute MUST match the value of the :code:`name`
      attribute on a :code:`component` or :code:`import component` element in the
      imported :ref:`CellML infoset<specA_cellml_infoset>`. See also the
      :ref:`Component reference<specC_component_reference>`
      section.

.. marker_import_component_end
.. marker_units_start

.. _units:

The units element
=================

A :code:`units` element information item (referred to in this specification
as a :code:`units` element) is an element in the CellML
namespace with a local name equal to :code:`units`, and with a :code:`model`
element as its parent.

Specific information items
--------------------------

.. container:: issue-units-name

   1. Every :code:`units` element MUST contain a :code:`name`
      attribute. The value of the :code:`name` attribute MUST be a
      :ref:`valid CellML identifier<specA_cellml_identifier>`.

.. container:: issue-units-name-unique

   2. The value of the :code:`name` attribute MUST NOT be identical to the
      :code:`name` attribute of any other :code:`units` element or
      :code:`import units` element in the :ref:`CellML infoset<specA_cellml_infoset>`.

.. container:: issue-units-standard

   3. The value of the :code:`name` attribute MUST NOT be equal to the name of
      any of the units listed in the :ref:`Built-in units <table_built_in_units>`
      table.

.. container:: issue-units-child

   4. A :code:`units` element MAY contain one or more :code:`unit` element
      children.

.. marker_units_end
.. marker_unit_start

.. _unit:

The unit element
================

A :code:`unit` element information item (referred to in this specification
as a :code:`unit` element) is an element in the CellML
namespace with a local name equal to :code:`unit`, and with a :code:`units`
element as its parent.

Specific information items
--------------------------

.. container:: issue-unit-units-ref

   1. Every :code:`unit` element MUST contain a :code:`units`
      attribute. The value of the :code:`units` attribute MUST be
      a valid units reference, as defined in the
      :ref:`Units reference <units_reference>` section.

      .. contianer:: issue-unit-digraph

         1. For the purpose of the constraint in the next paragraph, the
            :code:`units` element inclusion digraph SHALL be defined as a
            conceptual digraph which SHALL contain one node for every
            :code:`units` element in the :ref:`CellML model<specA_cellml_model>`.

            The :code:`units` element
            inclusion digraph SHALL contain an arc from :code:`units` element *A*
            to :code:`units` element *B* if and only if :code:`units` element *A*
            contains a :code:`unit` element with :code:`units` attribute value that
            is a units reference to :code:`units` element *B*.

      .. container:: issue-unit-circular-ref

         2. The value of the :code:`units` attribute MUST NOT be such that the
            :code:`units` element inclusion digraph contains one or more cycles
            (in other words, units definitions must not be cyclical).

.. marker_unit_1

.. container:: issue-unit-optional-attribute

   2. A :code:`unit` element MAY contain any of the following attributes:

      .. container:: issue-unit-prefix

         1. The :code:`prefix` attribute. If present, the value of the attribute
            MUST meet the constraints specified in the
            :ref:`Interpretation of units <specC_units>` section.

      .. container:: issue-unit-multiplier

         2. The :code:`multiplier` attribute. If present, the value of the
            attribute MUST be a real number string.

      .. container:: issue-unit-exponent

         3. The :code:`exponent` attribute. If present, the value of the attribute
            MUST be a real number string.

.. marker_unit_end
.. marker_component_start

.. _component:

The component element
=====================

A :code:`component` element information item (referred to in this
specification as a :code:`component` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`component`, and
which appears as a child of a :code:`model` element.

.. marker_component_1

Specific information items
--------------------------

.. container:: issue-component-name

   1. Every :code:`component` element MUST contain a :code:`name`
      attribute. The value of the :code:`name` attribute MUST be a
      :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of the :code:`name` attribute MUST NOT be identical
      to the :code:`name` attribute on any other :code:`component` element or
      :code:`import component` element in the :ref:`CellML infoset<specA_cellml_infoset>`.

.. marker_component_2

.. container:: issue-component-child

   2. A :code:`component` element MAY contain one or more specific element
      children, each of which MUST be of one of the following types:

      #. A :code:`variable` element; or

      #. A :code:`reset` element; or

      #. A :code:`math` element.

.. marker_component_end
.. marker_variable_start

.. _variable:

The variable element
====================

A :code:`variable` element information item (referred to in this
specification as a :code:`variable` element) is an element
in the :ref:`CellML namespace<specA_cellml_namespace>` with a local name
equal to :code:`variable`, and which appears as a child of a :code:`component` element.

Specific information items
--------------------------

1. Every :code:`variable` element MUST have exactly one of each of the following
   attributes:

   .. container:: issue-variable-name

      1. The :code:`name` attribute. The value of the :code:`name` attribute MUST
         be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

         The value of the :code:`name` attribute
         MUST NOT be identical to the :code:`name` attribute on any sibling
         :code:`variable` element.

   .. container:: issue-variable-units

      2. The :code:`units` attribute. The value of the :code:`units` attribute
         MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`,
         and MUST meet the constraints described in the
         :ref:`Effect of units on variables<specC_effect_of_units_on_variables>`
         section.

2. Every :code:`variable` element MAY contain one or more of the following
   attributes:

   .. container:: issue-variable-interface

      1. The :code:`interface` attribute. If the attribute is present, it MUST
         have value of :code:`public`, :code:`private`,
         :code:`public_and_private`, or :code:`none`.

   .. container:: issue-variable-initial-value

      2. The :code:`initial_value` attribute. If the attribute is present, it
         MUST meet the requirements described by the
         :ref:`Interpretation of initial values<specC_initial_values>` section.

.. marker_variable_end
.. marker_reset_start

.. _reset:

The reset element
=================

A :code:`reset` element information item (referred to in this specification
as a :code:`reset` element) is an element in the CellML
namespace with a local name equal to :code:`reset`, and which appears as a
child of a :code:`component` element.

Specific information items
--------------------------

1. Every :code:`reset` element MUST have exactly one each each of the following
   attributes:

   .. container:: issue-reset-variable-reference

      1. The :code:`variable` attribute. The value of the :code:`variable`
         attribute MUST be a variable reference to a variable defined
         within the parent :code:`component` element of the :code:`reset` element.

   .. container:: issue-reset-test-variable-reference

      2. The :code:`test_variable` attribute. The value of the
         :code:`test_variable` attribute MUST be a variable reference to a
         variable defined within the parent :code:`component` element of the
         :code:`reset` element.

   .. container:: issue-reset-order

      3. The :code:`order` attribute. The value of the :code:`order` attribute
         MUST be an integer string.

         The value of the :code:`order` attribute MUST
         be unique for all :code:`reset` elements with :code:`variable` attributes
         that reference variables in the same connected variable set (see
         :ref:`Interpretation of map_variables<specC_map_variables>`).

.. container:: issue-reset-child

   2. A :code:`reset` element MUST contain exactly two element
      children, which MUST be one each of the following types:

      .. container:: issue-reset-test-value

         1. A :code:`test_value` element; and,

      .. container:: issue-reset-reset-value

         2. A :code:`reset_value` element.

.. marker_reset_end
.. marker_test_value_start

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

.. container:: issue-test-value-todo

   1. A :code:`test_value` element MUST contain exactly one :code:`math` element
      child.

.. marker_test_value_end
.. marker_reset_value_start

.. _reset_value:

The reset_value element
=======================

A :code:`reset_value` element information item (referred to in this
specification as a :code:`reset_value` element) is an element in the CellML
namespace with a local name equal to :code:`reset_value`,
and which appears as a child of a :code:`reset` element.

Specific information items
--------------------------

.. container:: issue-reset-value-todo

   1. A :code:`reset_value` element MUST contain exactly one :code:`math` element
      child.

.. marker_reset_value_end
.. marker_math_start

.. _math:

The math element
================

A :code:`math` element information item (referred to in this specification
as a :code:`math` element) is an element in the MathML
namespace that appears as a direct child of a :code:`component` element, a
:code:`test_value` element, or a :code:`reset_value` element.

Specific information items
--------------------------

.. container:: issue-math-mathml

   1. A :code:`math` element MUST be the top-level of a content MathML tree, as
      described in :mathml2spec:`MathML 2.0`.

.. container:: issue-math-child

   2. Each element child of a :code:`math` element MUST have
      an element-type name that is listed in the
      :ref:`Supported MathML Elements <table_supported_mathml_elements>` table.

.. container:: issue-math-ci-variable-reference

   3. Every variable name given using the MathML :code:`ci` element MUST be a
      :ref:`variable reference<specC_variable_reference>` to a :code:`variable`
      within the :code:`component` element that the :code:`math` element
      is contained.

.. container:: issue-math-cn-units-attribute

   4. Any MathML :code:`cn` elements MUST each have an attribute in the
      :ref:`CellML namespace<specA_cellml_namespace>`, with a local name equal to :code:`units`.
      The value of this attribute MUST be a valid units
      reference.

.. container:: issue-math-todo

   5. The :code:`cn` element MUST be one of the following
      :mathml2types:`types` : real or e-notation.

.. container:: issue-math-todo

   6. The :code:`cn` element MUST be of base 10.

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

.. marker_math_end
.. marker_encapsulation_start

.. _encapsulation:

The encapsulation element
=========================

An :code:`encapsulation` element information item (referred to in this
specification as an :code:`encapsulation` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to
:code:`encapsulation`, and which appears as a child of a :code:`model` element.

Specific information items
--------------------------

.. container:: issue-encapsulation-component-ref

   1. Every :code:`encapsulation` element MUST contain one or more
      :code:`component_ref` elements.

.. marker_encapsulation_end
.. marker_component_ref_start

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

.. container:: issue-component-ref-component-attribute

   1. Every :code:`component_ref` element MUST contain a
      :code:`component` attribute.

      The value of this attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`,
      and MUST match the :code:`name`
      attribute on a :code:`component` element or an :code:`import component`
      element in the :ref:`CellML infoset<specA_cellml_infoset>`.

.. container:: issue-component-ref-child

   2. Every :code:`component_ref` element MAY in turn contain one or more
      :code:`component_ref` element children.

.. container:: issue-component-ref-encapsulation

   3. A :code:`component_ref` element which is an immediate child of an
      :code:`encapsulation` element MUST each contain at least one
      :code:`component_ref` element child.

.. marker_component_ref_end
.. marker_connection_start

.. _connection:

The connection element
======================

A :code:`connection` element information item (referred to in this
specification as a :code:`connection` element) is an element in the
:ref:`CellML namespace<specA_cellml_namespace>` with a local name equal to :code:`connection`,
and which appears as a child of a :code:`model` element.

Specific information items
--------------------------

.. container:: issue-connection-component1

   1. Each :code:`connection` element MUST contain a
      :code:`component_1` attribute. The value of the :code:`component_1`
      attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of this attribute MUST
      be equal to the :code:`name` attribute on a :code:`component` or
      :code:`import component` element in the :ref:`CellML infoset<specA_cellml_infoset>`
      (see :ref:`Component reference<specC_component_reference>`).

.. container:: issue-connection-component2

   2. Each :code:`connection` element MUST contain a
      :code:`component_2` attribute. The value of the :code:`component_2`
      attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of this attribute MUST
      be equal to the :code:`name` attribute on a :code:`component` or
      :code:`import component` element in the :ref:`CellML infoset<specA_cellml_infoset>`
      (see :ref:`Component reference <specC_component_reference>`).

      It MUST NOT be equal to the value of the :code:`component_1` attribute.

.. container:: issue-connection-unique-transitive

   3. A :ref:`CellML infoset<specA_cellml_infoset>` MUST NOT contain more than one :code:`connection`
      element with a given pair of :code:`component`\ s referenced by the
      :code:`component_1` and :code:`component_2` attribute values, in any order.

.. container:: issue-connection-map-variables

   4. Every :code:`connection` element MUST contain one or more
      :code:`map_variables` elements.

.. marker_connection_end
.. marker_map_variables_start

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

.. container:: issue-map-variables-variable1

   1. Each :code:`map_variables` element MUST contain a
      :code:`variable_1` attribute.

      The value of the :code:`variable_1` attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of this attribute MUST
      be equal to the :code:`name` attribute on a :code:`variable` element child
      of the :code:`component` element or :code:`import component` element
      referenced by the :code:`component_1` attribute on the :code:`connection`
      element which is the parent of this element.

.. container:: issue-map-variables-variable2

   2. Each :code:`map_variables` element MUST contain a
      :code:`variable_2` attribute.

      The value of the :code:`variable_2` attribute
      MUST be a :ref:`valid CellML identifier<specA_cellml_identifier>`.

      The value of this attribute MUST
      be equal to the :code:`name` attribute on a :code:`variable` element child
      of the :code:`component` element or :code:`import component` element
      referenced by the :code:`component_2` attribute on the :code:`connection`
      element which is the parent of this element.

.. container:: issue-map-variables-unique

   3. A :code:`connection` element MUST NOT contain more than one
      :code:`map_variables` element with a given :code:`variable_1` attribute
      value and :code:`variable_2` attribute value pair.

.. marker_map_variables_end
