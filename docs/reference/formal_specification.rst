.. _formal_specification:
**CellML 2.0 Specification [May 2017 Draft]**

**Authors:**

Michael T. Cooling\*

Michael Clerx

Jonathan Cooper

David P. Nickerson

**Contributors:**

Jesús C. Fernández

David Brooks

Koray Atalag

Alan Garny

The authors also wish to acknowledge the significant contribution of the
(discontinued) draft CellML 1.2 specification, much of the text of which
was incorporated into this specification - although the semantics have
changed considerably. The CellML 1.2 specification was itself the result
of a collaborative effort by a number of researchers during 2008-2011:

Andrew K. Miller (who wrote the text reused here), Jonathan Cooper,
Justin Marsh, Alan Garny, Randall Britten, Poul Nielsen and David P.
Nickerson

\* corresponding author: mtcooling.research@gmail.com

**Contents**

`1. Definitions <#_30j0zll>`__

`2. General matters <#general-matters>`__

   `2.1. CellML and XML <#cellml-and-xml>`__

   `2.2. Semantically equivalent CellML
   infosets <#semantically-equivalent-cellml-infosets>`__

   `2.3. Character information items <#character-information-items>`__

   `2.4. Use of namespaces <#use-of-namespaces>`__

   `2.5. XML Document Identifiers <#xml-id-attributes>`__

   `2.6. Specific information items <#specific-information-items>`__

`3. Data representation formats in
CellML <#data-representation-formats-in-cellml>`__

`4. The model element information
item <#the-model-element-information-item>`__

   `4.1. Top-level of CellML infosets <#top-level-of-cellml-infosets>`__

   `4.2. Specific information items <#specific-information-items-1>`__

`5. The import element information
item <#the-import-element-information-item>`__

   `5.1. Specific information items <#specific-information-items-2>`__

`6. The import units element information
item <#the-import-units-element-information-item>`__

   `6.1. Specific information items <#specific-information-items-3>`__

`7. The import component element information
item <#the-import-component-element-information-item>`__

   `7.1. Specific information items <#specific-information-items-4>`__

`8. The units element information
item <#the-units-element-information-item>`__

   `8.1. Specific information items <#specific-information-items-5>`__

`9. The unit element information
item <#the-unit-element-information-item>`__

   `9.1. Specific information items <#specific-information-items-6>`__

`10. The component element information
item <#the-component-element-information-item>`__

   `10.1. Specific information items <#specific-information-items-7>`__

`11. The variable element information
item <#the-variable-element-information-item>`__

   `11.1. Specific information items <#specific-information-items-8>`__

`12. The reset element information
item <#the-reset-element-information-item>`__

   `12.1. Specific information items <#specific-information-items-9>`__

`13. The when element information item <#section-2>`__

   `13.1. Specific information items <#_8bankyd7hcpt>`__

`14. The math element information
item <#the-math-element-information-item>`__

   `14.1. Specific information items <#specific-information-items-10>`__

   `Table: Supported MathML
   Elements <#table-supported-mathml-elements>`__

`15. The encapsulation element information
item <#the-encapsulation-element-information-item>`__

   `15.1. Specific information items <#specific-information-items-11>`__

`16. The component_ref element information
item <#the-component_ref-element-information-item>`__

   `16.1. Specific information items <#specific-information-items-12>`__

`17. The connection element information
item <#the-connection-element-information-item>`__

   `17.1. Specific information items <#specific-information-items-13>`__

`18. The map_variables element information
item <#the-map_variables-element-information-item>`__

   `18.1. Specific information items <#specific-information-items-14>`__

`19. Interpretation of CellML
models <#interpretation-of-cellml-models>`__

   `19.1. Interpretation of imports <#interpretation-of-imports>`__

   `19.2. Units reference <#units-reference>`__

   `Table: Built-in units <#table-built-in-units>`__

   `19.3. Interpretation of units <#interpretation-of-units>`__

   `Table: Prefix values <#table-prefix-values>`__

   `19.4. Component reference <#component-reference>`__

   `19.5. Variable reference <#variable-reference>`__

   `19.6. Interpretation of initial
   values <#interpretation-of-initial-values>`__

   `19.7. Effect of units on
   variables <#effect-of-units-on-variables>`__

   `19.8. Interpretation of
   mathematics <#interpretation-of-mathematics>`__

   `19.9. Interpretation of
   encapsulation <#interpretation-of-encapsulation>`__

   `19.10. Interpretation of
   map_variables <#interpretation-of-map_variables>`__

   `19.11. Interpretation of variable
   resets <#interpretation-of-variable-resets>`__

`20. References <#references>`__

`
 <about:blank>`__\

.. marker1

1. Definitions
===============

The keywords “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”,
“SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this
document are to be interpreted as described in `RFC
2119 <http://www.ietf.org/rfc/rfc2119.txt>`__.

The key phrase “information item”, as well as any specific type of
information item such as an “element information item”, are to be
interpreted as described in `XML Information
Set <http://www.w3.org/TR/2004/REC-xml-infoset-20040204/>`__.

CellML infoset

   An XML information set containing a hierarchy of information items
   conforming to the rules described in this document. In this
   specification such infosets are assumed to be CellML 2.0 infosets.

CellML model

   A mathematical model represented by a hierarchy of one or more CellML
   infosets, according to the rules described in this document. In this
   specification, the topmost CellML infoset in a hierarchy is referred
   to as the top-level CellML infoset.

Namespace

   An XML namespace, as defined in `Namespaces in XML
   1.1 <https://www.w3.org/TR/2006/REC-xml-names11-20060816/>`__.

CellML namespace

The CellML 2.0 namespace.

CellML 2.0 namespace

   The namespace http://www.cellml.org/cellml/2.0#.

MathML namespace

   The namespace http://www.w3.org/1998/Math/MathML.

CellML information item

   Any information item in the CellML namespace.

Basic Latin alphabetic character

   A Unicode character in the range
   `U+0041 <http://www.fileformat.info/info/unicode/char/0041/index.htm>`__
   to
   `U+005A <http://www.fileformat.info/info/unicode/char/005A/index.htm>`__
   or in the range
   `U+0061 <http://www.fileformat.info/info/unicode/char/0061/index.htm>`__
   to
   `U+007A <http://www.fileformat.info/info/unicode/char/007A/index.htm>`__.

European numeral

   A Unicode character in the range
   `U+0030 <http://www.fileformat.info/info/unicode/char/0030/index.htm>`__
   to
   `U+0039 <http://www.fileformat.info/info/unicode/char/0039/index.htm>`__.

Basic Latin alphanumeric character

   A Unicode character which is either a basic Latin alphabetic
   character or a European numeral.

Basic Latin underscore

   The Unicode character
   `U+005F <http://www.fileformat.info/info/unicode/char/005F/index.htm>`__.

Whitespace character

   Any one of the Unicode characters
   `U+0020 <http://www.fileformat.info/info/unicode/char/0020/index.htm>`__,
   `U+0009 <http://www.fileformat.info/info/unicode/char/0009/index.htm>`__,
   `U+000D <http://www.fileformat.info/info/unicode/char/000D/index.htm>`__
   or
   `U+000A <http://www.fileformat.info/info/unicode/char/000A/index.htm>`__.

.. marker2

2. General matters
==================

2.1. CellML and XML
-------------------

1. Every CellML infoset SHALL be represented in an XML information set
   which conforms with the well-formedness requirements of `XML
   1.1 <http://www.w3.org/TR/xml11/>`__.

2. In this document, the remaining provisions relating to CellML
   infosets SHALL be interpreted as additional constraints on the XML
   information set represented by a CellML infoset.

2.2. Semantically equivalent CellML infosets
--------------------------------------------

1. Two CellML infosets SHALL be deemed semantically equivalent if one
   can be transformed into the other by making zero or more of the
   following changes:

   1.

   2. Adding, removing, and/or modifying comment information items.

   3. Changing (inserting, removing, and/or modifying) one or more
      namespace information items, and/or modifying the prefix of one or
      more information items, without changing the namespace that any
      information item is in.

   4. The following paragraph applies only to character information
      items which are the direct child of an element information item in
      a CellML namespace, or in the MathML namespace.

..

   Inserting or removing character information items that consist
   entirely of whitespace characters, changing the number of whitespace
   characters in such an information item, or changing the number of
   whitespace characters at the beginning or end of any character
   information item.

2.3. Character information items
--------------------------------

An element information item in the CellML namespace MUST NOT contain any
character information items, except for character information items
which consist entirely of whitespace characters.

2.4. Use of namespaces
----------------------

1. Element and attribute information items in a CellML infoset MUST
   belong to one of the following namespaces, unless explicitly
   indicated otherwise:

   1. The CellML namespace

   2. The MathML namespace

2.5. XML ID Attributes
----------------------

1. Any element information item in the CellML namespace MAY contain an
   unprefixed attribute information item with local name :code:`id.` This
   attribute information item SHALL be treated as having attribute type
   ID, as defined in `section
   3.3.1 <http://www.w3.org/TR/xml11/#sec-attribute-types>`__ of `XML
   1.1 <http://www.w3.org/TR/xml11/>`__.

2.6. Specific information items
-------------------------------

1. For the purposes of this specification, a specific information item
   is one of the following (see
   https://www.w3.org/TR/xml-infoset/#infoitem for definitions):

   1. A document information item;

   2. An element information item;

   3. An attribute information item;

   4. A processing instruction information item;

   5. An unexpanded entity reference information item;

   6. A document type declaration information item;

   7. An unparsed entity information item;

   8. A notational information item.

2. Specific information items MUST NOT appear in a CellML infoset except
   where explicitly allowed by this specification, or where allowed by a
   normative specification referenced by this specification.

3. The order in which specific information items appear, as children of
   an element information item defined in this specification, SHALL NOT
   affect the semantic interpretation of the CellML model.

.. marker3

3. Data representation formats in CellML
========================================

The following data representation formats are defined for use in this
specification:

1. A CellML identifier:

   1. SHALL be a sequence of Unicode characters.

   2. SHALL NOT contain any characters except Basic Latin alphanumeric
      characters and Basic Latin underscores.

   3. SHALL contain at least one alphabetic character.

   4. SHALL NOT begin with a numeral or an underscore.

   5. SHALL, when comparing two identifiers, be considered identical to
      another identifier if and only if both identifiers have identical
      sequences of characters.

.. marker3_2

2. A non-negative integer string:

   1. SHALL be a base 10 representation of a non-negative integer.

   2. SHALL consist entirely of Basic Latin numerals.

.. marker3_3

3. An integer string:

   1. SHALL be a base 10 representation of an integer.

   2. SHALL, when the integer being represented is negative, consist of
      the Basic Latin hyphen-minus character
      `U+002D <http://www.fileformat.info/info/unicode/char/002D/index.htm>`__,
      followed by the non-negative integer string representation of the
      absolute value of the integer.

   3. SHALL, when the integer being represented is non-negative, consist
      of the non-negative integer string representation of the integer.

.. marker3_4

4. A basic real number string:

   1. SHALL be a base 10 representation of a real number.

   2. SHALL, when the basic real number being represented is negative,
      begin with the Basic Latin hyphen-minus character
      `U+002D <http://www.fileformat.info/info/unicode/char/002D/index.htm>`__
      as the sign indicator.

   3. MAY contain a single decimal point separator, which SHALL be the
      Basic Latin full stop character
      `U+002E <http://www.fileformat.info/info/unicode/char/002E/index.htm>`__.

   4. SHALL, other than the sign indicator and the decimal point
      separator, consist only of Basic Latin numerals.

.. marker3_5

5. A real number string:

   1. SHALL be a base 10 representation of a real number
      *r*\ =\ *s*\ ⋅10\ *e*, where *s* is the significand, a real
      number, and *e* is the exponent, an integer.

   2. The representation of the number SHALL be the representation of
      the significand followed immediately by the representation of the
      exponent.

   3. The significand SHALL be represented as a basic real number
      string.

   4. A non-zero exponent SHALL be represented by an exponent separator
      character, followed by the integer string representation of the
      value of the exponent. Non-negative exponents MAY begin with the
      Basic Latin plus sign character
      `U+002B <http://www.fileformat.info/info/unicode/char/002B/index.htm>`__
      as the sign indicator. The exponent separator character SHALL be
      either the Basic Latin ‘E’ character
      `U+0045 <http://www.fileformat.info/info/unicode/char/0045/index.htm>`__
      or the Basic Latin ‘e’ character
      `U+0065 <http://www.fileformat.info/info/unicode/char/0065/index.htm>`__.

   5. If the exponent is zero, the exponent MAY be represented by an
      empty string, or MAY be represented according to the rule for
      non-zero exponent.

.. marker4

4. The model element information item
=====================================

4.1. Top-level of CellML infosets
---------------------------------

The top-level element information item in a CellML infoset MUST be an
element information item in the CellML namespace with a local name equal
to :code:`model`. In this specification, the top-level element information
item is referred to as the :code:`model` element.

.. _specific-information-items-1:

4.2. Specific information items
-------------------------------

1. Every :code:`model` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a valid CellML
   identifier.

2. A :code:`model` element MAY contain one or more additional specific
   information item children, each of which MUST be of one of the
   following types:

   1. A :code:`component` element; or

   2. A :code:`connection` element; or

   3. An :code:`encapsulation` element; or

   4. An :code:`import` element; or

   5. A :code:`units` element;

3. A :code:`model` element MUST NOT contain more than one :code:`encapsulation`
   element.

.. marker5

5. The import element information item
======================================

An :code:`import` element information item (referred to in this
specification as an :code:`import` element) is an element information item
in the CellML namespace with a local name equal to :code:`import`.

.. _specific-information-items-2:

5.1. Specific information items
-------------------------------

1. Every :code:`import` element MUST contain an attribute information item
   in the namespace :code:`http://www.w3.org/1999/xlink`, and with a local
   name equal to :code:`href`. The value of this attribute SHALL be a valid
   locator :code:`href`, as defined in `section
   5.4 <http://www.w3.org/TR/2001/REC-xlink-20010627/#link-locators>`__
   of the `XLink
   specification <http://www.w3.org/TR/2001/REC-xlink-20010627/>`__. The
   :code:`href` attribute SHALL be treated according to the XLink
   specification, by applying the rules for simple-type elements. When
   describing an :code:`import` element or one of its children, the phrase
   “imported CellML infoset” SHALL refer to the CellML infoset obtained
   by parsing the document referenced by the :code:`href` attribute.

2. Every :code:`import` element MAY contain one or more specific information
   item children, each of which MUST be of one of the following types:

   1. An :code:`import units` element; or

   2. An :code:`import component` element.

3. Any CellML infoset imported, directly or indirectly, by the imported
   CellML infoset MUST NOT be semantically equivalent to the importing
   CellML infoset (see Semantically equivalent CellML infosets).

.. marker6

6. The import units element information item
============================================

An :code:`import units` element information item (referred to in this
specification as an :code:`import units` element) is an element information
item in the CellML namespace with a local name equal to :code:`units`, which
appears as a child of an :code:`import` element.

.. _specific-information-items-3:

6.1. Specific information items
-------------------------------

1. Every :code:`import units` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a valid CellML
   identifier. The value of the :code:`name` attribute MUST NOT be identical
   to the :code:`name` attribute of any other :code:`units` or :code:`import units`
   element in the CellML infoset.

2. Every :code:`import units` element MUST contain an unprefixed
   :code:`units_ref` attribute. The value of the :code:`units_ref` attribute
   MUST be a valid CellML identifier. The value of the :code:`units_ref`
   attribute MUST match the value of the :code:`name` attribute on a
   :code:`units` or :code:`import units` element in the imported CellML infoset.
   The value of the :code:`units_ref` attribute MUST NOT match the value of
   the :code:`units_ref` attribute on any sibling :code:`import units` element.

.. marker7

7. The import component element information item
================================================

An :code:`import component` element information item (referred to in this
specification as an :code:`import component` element) is an element
information item in the CellML namespace with a local name equal to
:code:`component`, which appears as a child of an :code:`import` element.

.. _specific-information-items-4:

7.1. Specific information items
-------------------------------

1. Every :code:`import component` element MUST contain an unprefixed
   :code:`name` attribute. The value of the :code:`name` attribute MUST be a
   valid CellML identifier. The value of the :code:`name` attribute MUST NOT
   be identical to the :code:`name` attribute of any other :code:`component` or
   :code:`import component` element information item in the CellML infoset.

2. Every :code:`import component` element MUST contain an unprefixed
   :code:`component_ref` attribute. The value of the :code:`component_ref`
   attribute MUST be a valid CellML identifier. The value of the
   :code:`component_ref` attribute MUST match the value of the :code:`name`
   attribute on a :code:`component` or :code:`import component` element in the
   imported CellML infoset. See also the `Component reference <\l>`__
   section.

.. marker8

8. The units element information item
=====================================

A :code:`units` element information item (referred to in this specification
as a :code:`units` element) is an element information item in the CellML
namespace with a local name equal to :code:`units`, and with a :code:`model`
element as its parent.

.. _specific-information-items-5:

8.1. Specific information items
-------------------------------

1. Every :code:`units` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a valid CellML
   identifier.

2. The value of the :code:`name` attribute MUST NOT be identical to the
   :code:`name` attribute of any other :code:`units` element or :code:`import units`
   element in the CellML infoset.

3. The value of the :code:`name` attribute MUST NOT be equal to the name of
   any of the units listed in the `Built-in
   units <#table-built-in-units>`__ table.

4. A :code:`units` element MAY contain one or more :code:`unit` element
   children.

.. marker9

9. The unit element information item
====================================

A :code:`unit` element information item (referred to in this specification
as a :code:`unit` element) is an element information item in the CellML
namespace with a local name equal to :code:`unit`, and with a :code:`units`
element as its parent.

.. _specific-information-items-6:

9.1. Specific information items
-------------------------------

1. Every :code:`unit` element MUST contain an unprefixed :code:`units` attribute
   information item. The value of the :code:`units` attribute MUST be a
   valid units reference, as defined in the `Units
   reference <#units-reference>`__ section.

   1. For the purpose of the constraint in the next paragraph, the
      :code:`units` element inclusion digraph SHALL be defined as a
      conceptual digraph which SHALL contain one node for every
      :code:`units` element in the CellML model. The :code:`units` element
      inclusion digraph SHALL contain an arc from :code:`units` element *A*
      to :code:`units` element *B* if and only if :code:`units` element *A*
      contains a :code:`unit` element with :code:`units` attribute value that is
      a units reference to :code:`units` element *B*.

   2. The value of the :code:`units` attribute MUST NOT be such that the
      :code:`units` element inclusion digraph contains one or more cycles
      (in other words, units definitions must not be cyclical).

2. A :code:`unit` element MAY contain any of the following unprefixed
   attribute information items:

   1. The :code:`prefix` attribute. If present, the value of the attribute
      MUST meet the constraints specified in the `Interpretation of
      units <#interpretation-of-units>`__ section.

   2. The :code:`multiplier` attribute. If present, the value of the
      attribute MUST be a real number string.

   3. The :code:`exponent` attribute. If present, the value of the attribute
      MUST be a real number string.

.. marker10

10. The component element information item
==========================================

A :code:`component` element information item (referred to in this
specification as a :code:`component` element) is an element information item
in the CellML namespace with a local name equal to :code:`component`, and
which appears as a child of a :code:`model` element.

.. _specific-information-items-7:

10.1. Specific information items
--------------------------------

1. Every :code:`component` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a valid CellML
   identifier. The value of the :code:`name` attribute MUST NOT be identical
   to the :code:`name` attribute on any other :code:`component` element or
   :code:`import component` element in the CellML infoset.

2. A :code:`component` element MAY contain one or more specific information
   item children, each of which MUST be of one of the following types:

   1. A :code:`variable` element; or

   2. A :code:`reset` element; or

   3. A :code:`math` element

.. marker11

11. The variable element information item
=========================================

A :code:`variable` element information item (referred to in this
specification as a :code:`variable` element) is an element information item
in the CellML namespace with a local name equal to :code:`variable`, and
which appears as a child of a :code:`component` element.

.. _specific-information-items-8:

11.1. Specific information items
--------------------------------

1. Every :code:`variable` element MUST have each of the following unprefixed
   attribute information items:

   1. The :code:`name` attribute. The value of the :code:`name` attribute MUST
      be a valid CellML identifier. The value of the :code:`name` attribute
      MUST NOT be identical to the :code:`name` attribute on any sibling
      :code:`variable` element.

   2. The :code:`units` attribute. The value of the :code:`units` attribute MUST
      be a valid CellML identifier, and MUST meet the constraints
      described in the `Effect of units on
      variables <#effect-of-units-on-variables>`__ section.

2. Every :code:`variable` element MAY contain one or more of the following
   unprefixed attribute information items:

   1. The :code:`interface` attribute. If the attribute is present, it MUST
      have one of the values :code:`public`, :code:`private`,
      :code:`public_and_private`, or :code:`none`.

   2. The :code:`initial_value` attribute. If the attribute is present, it
      MUST meet the requirements described by the `Interpretation of
      initial values <#interpretation-of-initial-values>`__ section.

.. marker12

12. The reset element information item
======================================

A :code:`reset` element information item (referred to in this specification
as a :code:`reset` element) is an element information item in the CellML
namespace with a local name equal to :code:`reset`, and which appears as a
child of a :code:`component` element.

.. _specific-information-items-9:

12.1. Specific information items
--------------------------------

1. Every :code:`reset` element MUST have each of the following unprefixed
   attribute information items:

   1. The :code:`variable` attribute. The value of the :code:`variable`
      attribute MUST be a variable reference to a variable defined
      within the :code:`component` element parent of the :code:`reset` element.

   2. The :code:`order` attribute. The value of the :code:`order` attribute MUST
      be an integer string. The value of the :code:`order` attribute MUST be
      unique for all :code:`reset` elements for variables that are in the
      same connected variable set (see `Interpretation of
      map_variables <#interpretation-of-map_variables>`__).

2. A :code:`reset` element MUST contain one or more specific information
   item children, each of which MUST be a :code:`when` element.

1. Every reset element MUST have each of the following unprefixed
   attribute information items:

   a. The variable attribute. The value of the variable attribute MUST
      be a variable reference to a variable defined within the component
      element parent of the reset element.

   b. The test_variable attribute. The value of the test_variable
      attribute MUST be a variable reference to a variable defined
      within the component element parent of the reset element.

   c. The order attribute. The value of the order attribute MUST be an
      integer string. The value of the order attribute MUST be unique
      for all reset elements for variables that are in the same
      connected variable set (see Interpretation of map_variables).

2. A reset element MUST contain two specific information item children,
   each of which MUST be a MathML state\ :code:`ue` element …

3. The :code:`reset_value`



.. marker14

14. The math element information item
=====================================

A :code:`math` element information item (referred to in this specification
as a :code:`math` element) is an element information item in the MathML
namespace that appears as a direct child of a :code:`component` element, a
:code:`test_value` element, or a :code:`reset_value` element.

.. _specific-information-items-10:

14.1. Specific information items
--------------------------------

1. A :code:`math` element MUST be the top-level of a content MathML tree, as
   described in `MathML
   2.0 <http://www.w3.org/TR/2003/REC-MathML2-20031021/>`__.

2. Each element information item child of a :code:`math` element MUST have
   an element-type name that is listed in the `Supported MathML
   Elements <#table-supported-mathml-elements>`__ table.

3. Every variable name given using the MathML :code:`ci` element MUST be a
   `variable reference <#variable-reference>`__ to a :code:`variable` within
   the :code:`component` element that the :code:`math` element is contained.

4. Any MathML :code:`cn` elements MUST each have an attribute information
   item in the CellML namespace, with a local name equal to :code:`units`.
   The value of this attribute information item MUST be a valid units
   reference.

5. The :code:`cn` element MUST be one of the following
   `types <https://www.w3.org/TR/MathML2/chapter4.html#contm.typeattrib>`__:
   real or e-notation.

6. The :code:`cn` element MUST be of base 10.

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

.. marker15

15. The encapsulation element information item
==============================================

An :code:`encapsulation` element information item (referred to in this
specification as an :code:`encapsulation` element) is an element information
item in the CellML namespace with a local name equal to
:code:`:encapsulation`, and which appears as a child of a :code:`model` element.

.. _specific-information-items-11:

15.1. Specific information items
--------------------------------

1. Every :code:`encapsulation` element MUST contain one or more
   :code:`component_ref` elements.

.. marker16

16. The component_ref element information item
==============================================

A :code:`component_ref` element information item (referred to in this
specification as a :code:`component_ref` element) is an element information
item in the CellML namespace with a local name equal to
:code:`component_ref`, and which appears as a child of an :code:`encapsulation`
element.

.. _specific-information-items-12:

16.1. Specific information items
--------------------------------

1. Every :code:`component_ref` element MUST contain an unprefixed
   :code:`component` attribute information item. The value of this attribute
   MUST be a valid CellML identifier, and MUST match the :code:`name`
   attribute on a :code:`component` element or an :code:`import component`
   element in the CellML infoset.

2. Every :code:`component_ref` element MAY in turn contain one or more
   :code:`component_ref` element children.

3. A :code:`component_ref` element which is an immediate child of an
   :code:`encapsulation` element MUST each contain at least one
   :code:`component_ref` element child.

.. marker17

17. The connection element information item
===========================================

A :code:`connection` element information item (referred to in this
specification as a :code:`connection` element) is an element information
item in the CellML namespace with a local name equal to :code:`connection`,
and which appears as a child of a :code:`model` element.

.. _specific-information-items-13:

17.1. Specific information items
--------------------------------

1. Each :code:`connection` element MUST contain an unprefixed
   :code:`component_1` attribute. The value of the :code:`component_1` attribute
   MUST be a valid CellML identifier. The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`component` or :code:`import
   component` element in the CellML infoset (see `Component
   reference <#component-reference>`__).

2. Each :code:`connection` element MUST contain an unprefixed
   :code:`component_2` attribute. The value of the :code:`component_2` attribute
   MUST be a valid CellML identifier. The value of this attribute MUST
   be equal to the name attribute on a :code:`component` or :code:`import
   component` element in the CellML infoset (see `Component
   reference <#component-reference>`__). It MUST NOT be equal to the
   value of the :code:`component_1` attribute.

3. A CellML infoset MUST NOT contain more than one :code:`connection`
   element with a given pair of :code:`component`\ s referenced by the
   :code:`component_1` and :code:`component_2` attribute values, in any order.

4. Every :code:`connection` element MUST contain one or more
   :code:`map_variables` elements.

.. marker18

18. The map_variables element information item
==============================================

A :code:`map_variables` element information item (referred to in this
specification as a :code:`map_variables` element) is an element information
item in the CellML namespace with a local name equal to
:code:`map_variables`, and which appears as a child of a :code:`connection`
element.

.. _specific-information-items-14:

18.1. Specific information items
--------------------------------

1. Each :code:`map_variables` element MUST contain an unprefixed
   :code:`variable_1` attribute. The value of the :code:`variable_1` attribute
   MUST be a valid CellML identifier. The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`variable` element child of
   the :code:`component` element or :code:`import component` element referenced
   by the :code:`component_1` attribute on the :code:`connection` element which
   is the parent of this element.

2. Each :code:`map_variables` element MUST contain an unprefixed
   :code:`variable_2` attribute. The value of the :code:`variable_2` attribute
   MUST be a valid CellML identifier. The value of this attribute MUST
   be equal to the :code:`name` attribute on a :code:`variable` element child of
   the :code:`component` element or :code:`import component` element referenced
   by the :code:`component_2` attribute on the :code:`connection` element which
   is the parent of this element.

3. A :code:`connection` element MUST NOT contain more than one
   :code:`map_variables` element with a given :code:`variable_1` attribute value
   and :code:`variable_2` attribute value pair.

.. marker19

19. Interpretation of CellML models
===================================

19.1. Interpretation of imports
-------------------------------

1. Each :code:`import` element present in a CellML infoset (the importing
   infoset) SHALL define a new and separate instance of the CellML
   infoset referenced by the :code:`href` attribute (the imported infoset).
   See `Units reference <#units-reference>`__ and `Component
   reference <#component-reference>`__ for the specifics of importing
   units and components.

19.2. Units reference
---------------------

1. A units reference SHALL be a CellML identifier and SHALL be
   interpreted dependent on the context of the CellML model in which it
   occurs, according to the units referencing rules defined later in
   this section.

2. A CellML infoset MUST NOT contain a units reference for which no
   referencing rule can be held to have been followed.

3. The units referencing rules are:

   1. Where there is a :code:`units` element with a :code:`name` attribute
      identical to the units reference, then the units reference SHALL
      refer to that :code:`units` element.

   2. Where there is an :code:`import units` element in the CellML infoset,
      such that the :code:`import units` element has a :code:`name` attribute
      identical to the units reference, then the units reference SHALL
      be treated with respect to referencing rules as if the units
      reference appeared in the imported infoset, and referring to the
      :code:`name` specified in the :code:`units_ref` attribute of the :code:`import
      units` element.

   3. Where the units reference is equal to the value in the ‘Name’
      column of the `Built-in units <#table-built-in-units>`__ table,
      then the units reference SHALL be a reference to the built-in
      units corresponding to that row of the table.

Table: Built-in units
~~~~~~~~~~~~~~~~~~~~~

+---------------+-------------------+--------------------------------+
| **Name**      | **Multiplier(s)** | **Unit reduction tuple**       |
|               |                   |  (dimension, exponent) set     |
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
|               |                   | (second, -4), (ampere,2)       |
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

19.3. Interpretation of units
-----------------------------

1. The :code:`units` element SHALL be interpreted as the product of its
   :code:`unit` element children, according to the following rules:

   1. The prefix term is a conceptual property of :code:`unit` elements. If
      the :code:`unit` element does not have a :code:`prefix` attribute
      information item, the prefix term SHALL have value 0. If the
      :code:`prefix` attribute information item has a value which is an
      integer string, then the value of the prefix term SHALL be the
      numerical value of that string. Otherwise, the :code:`prefix`
      attribute information item MUST have a value taken from the ‘Name’
      column of the `Prefix values <#_8ooet5xoo2mz>`__ table, and the
      prefix term SHALL have the value taken from the ‘Value’ column of
      the same row.

   2. The exponent term is a conceptual property of :code:`unit` elements.
      If a :code:`unit` element has no :code:`exponent` attribute information
      item, the exponent term SHALL have value 1.0. Otherwise, the value
      of the :code:`exponent` attribute information item MUST be a real
      number string, and the value of the exponent term SHALL be the
      numerical value of that string.

   3. The multiplier term is a conceptual property of :code:`unit` elements.
      If a :code:`unit` element has no :code:`multiplier` attribute information
      item, the multiplier term SHALL have value 1.0. Otherwise, the
      value of the :code:`multiplier` attribute information item MUST be a
      real number string, and the value of the multiplier term SHALL be
      the numerical value of that string.

   4. The relationship between the product, *P,* of numerical values
      given in each and every child :code:`unit` element units, to a
      numerical value, *x,* with units given by the encompassing
      :code:`units` element, SHALL be

..



   where: *u\ x* denotes the units of the :code:`units` element; *p\ i*,
   *e\ i*, *m\ i*, and *u\ i* refer to the prefix, exponent and
   multiplier terms and units of the *i*\ th :code:`unit` child element,
   respectively. Square brackets encompass the units of numerical
   values.

2. For the purposes of this specification, the “irreducible units” of a
   model SHALL consist of 1) the units defined in a model that are not
   defined in terms of other units (i.e. the set of :code:`units` elements
   in the CellML model which have no :code:`unit` child elements), and 2)
   built-in irreducible units (those built-in units with ‘-’ in the
   ‘Unit Reduction...’ column of the `Built-in
   units <#table-built-in-units>`__ Table) referenced by variables or
   other units in the model.

3. The “unit reduction” is a conceptual property of :code:`units` elements.
   It consists of a set of tuples where each tuple is composed of a) a
   unit name and b) a real-valued exponent. Tuples SHALL be determined
   as follows:

   1. If the :code:`units` element has no :code:`unit` child elements, then the
      set of tuples SHALL have a single member, which SHALL consist of
      the name of the :code:`units` element and the exponent 1.0.

   2. If the :code:`units` element has one or more :code:`unit` child elements,
      then the set of tuples SHALL consist of the entire collection of
      tuples given by all :code:`unit` child elements. Tuples for each
      :code:`unit` child element SHALL be determined as follows:

      1. Where the units reference of the :code:`unit` child element is to a
         single unit which is an irreducible unit, then the set of
         tuples SHALL have a single member, which SHALL consist of the
         name of the irreducible unit being referenced and the exponent
         1.0.

      2. Where the units reference of the :code:`unit` child element is to
         built-in units other than an irreducible unit, then the tuples
         SHALL be derived directly from the `Built-in
         units <#table-built-in-units>`__ table. Specifically, the set
         of tuples SHALL consist of the tuples given in the ‘Unit
         reduction tuple ... set’ column of the row for which the value
         in the ‘Name’ column matches the name of the units reference.

      3. Where the units reference of the :code:`unit` child element is to a
         unit which is neither built-in, nor an irreducible unit, the
         set of tuples SHALL be defined recursively as the set of tuples
         for the :code:`units` element so referenced.

      4. The exponents of each tuple in the set for the current :code:`unit`
         element, as derived by following rule 3.2.1, 3.2.2 or 3.2.3
         above, SHALL be multiplied by the exponent term of the current,
         referencing, :code:`unit` element.

   3. Tuples which have the name element of ‘dimensionless’ SHALL be
      removed from the set of tuples. Note that this can result in the
      set of tuples being empty.

   4. Where the set of tuples consists of tuples which have the same
      name element, those tuples SHALL be combined into a single tuple
      with that name element and an exponent being the sum of the
      combined tuples’ exponents. If the resulting tuple’s exponent term
      is zero, the tuple SHALL be removed from the set of tuples. Note
      that this can result in the set of tuples being empty.

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

19.4. Component reference
-------------------------

1. A component reference SHALL be the name of a component, and SHALL be
   interpreted based on the context within the CellML model in which it
   occurs.

2. A component reference present in an information item which is a
   descendant of a :code:`model` element SHALL be identical to either the
   :code:`name` attribute on a :code:`component` element or to the :code:`name`
   attribute on an :code:`import component` element.

3. A component reference which is identical to the :code:`name` attribute on
   a :code:`component` element SHALL be treated as a reference to that
   :code:`component` element.

4. A component reference which is identical to the :code:`name` attribute on
   an :code:`import component` element SHALL be treated for the purposes of
   referencing as if the component reference appeared in the imported
   model, and referred to element with the :code:`name` specified in the
   :code:`component_ref` attribute of the :code:`import component` element.

5. It is noted, for the avoidance of doubt, that CellML models MAY apply
   the previous rule recursively, to reference an :code:`import component`
   element which in turn references another :code:`import component`
   element.

19.5. Variable reference
------------------------

1. When present in an information item which is a descendant of a
   :code:`component` element, a variable reference SHALL be the name of a
   variable, and SHALL refer to the :code:`variable` element in that
   component with a :code:`name` attribute identical to the variable
   reference.

2. In all other cases, a variable reference SHALL consist of a component
   reference and a variable name. In this case, the variable reference
   SHALL be treated as if it was just the variable name present in the
   :code:`component` element referenced by the component reference.

19.6. Interpretation of initial values
--------------------------------------

1. The :code:`initial_value` attribute of a :code:`variable` element MUST either
   be a real number string, or a variable reference (see 19.5).

2. The conditions when initial values hold are (by design) not defined
   in a CellML model document.

3. Where the :code:`initial_value` attribute has a real number value, it
   SHALL be interpreted as a statement that the variable on which the
   attribute appears is equal to that real number value, under the
   conditions when the initial value holds.

4. Where the :code:`initial_value` attribute is a variable reference, it
   SHALL be interpreted as a statement that the variable on which the
   attribute appears is equal to the referenced variable under the
   conditions when the initial value holds.

19.7. Effect of units on variables
----------------------------------

1. The value of the :code:`units` attribute on every :code:`variable` element
   MUST be a valid units reference. The target of this units reference
   is referred to as the variable units, and the corresponding unit
   reduction (see `Interpretation of
   units <#interpretation-of-units>`__) is referred to as the variable
   unit reduction.

19.8. Interpretation of mathematics
-----------------------------------

1. The following :code:`component` elements SHALL, for the purposes of this
   specification, be “pertinent component elements”:

   1. All :code:`component` elements in the top-level CellML infoset for the
      CellML model;

   2. All :code:`component` elements referenced by :code:`import component`
      elements (see `The import component element information
      item <#the-import-component-element-information-item>`__) in the
      top-level CellML infoset; and

   3. All :code:`component` elements which are descendants in the
      encapsulation digraph (see `Interpretation of
      encapsulation <#interpretation-of-encapsulation>`__) of a
      pertinent :code:`component` element.

2. Every MathML element in the CellML model which appears as a direct
   child information item of a MathML :code:`math` element information item,
   which in turn appears as a child information item of a pertinent
   :code:`component` element, SHALL be treated, in terms of the semantics of
   the mathematical model, as a statement which holds true
   unconditionally.

3. Units referenced by a :code:`units` attribute information item SHALL NOT
   affect the mathematical interpretation of the CellML model.

19.9. Interpretation of encapsulation
-------------------------------------

1. For the purposes of this specification, there SHALL be a “conceptual
   encapsulation digraph” in which there is EXACTLY one node for every
   component in the CellML model. Therefore the encapsulation digraph
   will not contain any loops.

2. Where a :code:`component_ref` element appears as a child of another
   :code:`component_ref` element, there SHALL be an arc in the encapsulation
   digraph, and that arc SHALL be from the node corresponding to the
   component referenced by the parent :code:`component_ref` element, and to
   the node corresponding to the component referenced by the child
   :code:`component_ref` element.

3. The encapsulated set for a component *A* SHALL be the set of all
   components *B* such that there exists an arc in the encapsulation
   digraph from the node corresponding to *A* to the node corresponding
   to *B*.

4. The encapsulation parent for a component *A* SHALL be the component
   corresponding to the node which is the parent node in the
   encapsulation digraph of the node corresponding to *A*.

5. The sibling set for a component *A* SHALL be the set of all
   components which have the same encapsulation parent as *A*, or in the
   case that *A* has no encapsulation parent, SHALL be the set of all
   components which do not have an encapsulation parent.

6. The hidden set for a component *A* SHALL be the set of all components
   *B* where component *B* is not in the encapsulated set for component
   *A*, and component *B* is not the encapsulation parent of component
   *A*, and component *B* is not in the sibling set for component *A*.

7. There MUST NOT be a :code:`connection` element such that the component
   referenced by the :code:`component_1` attribute is in the hidden set of
   the component referenced by the :code:`component_2` attribute, nor vice
   versa.

19.10. Interpretation of map_variables
--------------------------------------

1.  For the purposes of this specification, the variable equivalence
    (conceptual) network SHALL be an undirected graph with one node for
    every :code:`variable` element in the CellML model. The arcs of this
    graph SHALL be equivalences defined in the CellML model.

2.  For each :code:`map_variables` element present in the CellML model, we
    define variables *A* and *B* for use in the rules in this section as
    follows.

    1. Variable *A* SHALL be the variable referenced by the encompassing
       :code:`connection` element’s :code:`component_1` and this
       :code:`map_variables` element’s :code:`variable_1` attribute.

    2. Variable *B* SHALL be the variable referenced by the encompassing
       :code:`connection` element’s :code:`component_2` and this
       :code:`map_variables` element’s :code:`variable_2` attribute.

3.  For every :code:`map_variables` element present in the CellML model,
    there SHALL be an arc in the variable equivalence network.

    1. One endpoint of the arc in the variable equivalence network SHALL
       be the node corresponding to variable *A*.

    2. One endpoint of the arc in the variable equivalence network SHALL
       be the node corresponding to variable *B*.

4.  CellML models MUST NOT contain any pair of :code:`map_variables`
    elements which duplicates an existing arc in the variable
    equivalence network.

5.  The variable equivalence network MUST NOT contain any cycles.

6.  For each :code:`map_variables` element present in the CellML model, the
    variable unit reduction (see `Effect of units on
    variables <#effect-of-units-on-variables>`__) of variable *A* MUST
    have an identical set of tuples to the variable unit reduction of
    variable *B*. Two sets of tuples SHALL be considered identical if
    all of the tuples from each set are present in the other, or if both
    sets are empty. Two tuples are considered identical if and only if
    both the name and exponent value of each tuple are equivalent.

7.  Tuples differing by a multiplying factor in their unit reduction
    MUST be taken into account when interpreting the numerical values of
    the variables (see `Interpretation of
    units <#interpretation-of-units>`__).

8.  For a given variable, the available interfaces SHALL be determined
    by the :code:`interface` attribute information item on the corresponding
    :code:`variable` element as follows.

    1. A value of :code:`public` specifies that the variable has a public
       interface.

    2. A value of :code:`private` specifies that the variable has a private
       interface.

    3. A value of :code:`public_and_private` specifies that the variable has
       both a public and a private interface.

    4. A value of :code:`none` specifies that the variable has no interface.

    5. If the :code:`interface` attribute information item is absent, then
       the variable has no interface.

9.  The applicable interfaces for variables *A* and *B* SHALL be defined
    as follows.

    1. When the parent :code:`component` element of variable *A* is in the
       sibling set of the parent :code:`component` element of variable *B*,
       the applicable interface for both variables *A* and *B* SHALL be
       the public interface.

    2. When the parent :code:`component` element of variable *A* is in the
       encapsulated set of the parent :code:`component` element of variable
       *B*, the applicable interface for variable *A* SHALL be the
       public interface, and the applicable interface for variable *B*
       SHALL be the private interface.

    3. When the parent :code:`component` element of variable *B* is in the
       encapsulated set of the parent :code:`component` element of variable
       *A*, the applicable interface for variable *A* SHALL be the
       private interface, and the applicable interface for variable *B*
       SHALL be the public interface.

10. CellML models MUST NOT contain a :code:`map_variables` element where the
    applicable interface of variable *A* or *B* is not defined or is not
    an available interface.

11. For the purposes of this specification, the :code:`variable` elements in
    a CellML model SHALL be treated as belonging to one of one or more
    disjoint “connected variable sets”. Each set of “connected
    variables” is the set of all :code:`variable` elements for which the
    corresponding nodes in the variable equivalence network form a
    weakly connected subgraph. Each set of connected variables
    represents one variable in the underlying mathematical model.

19.11. Interpretation of variable resets
----------------------------------------

1. Each :code:`reset` element describes a change to be applied to the
   variable referenced by the :code:`variable` attribute when specified
   conditions are met during the simulation of the model.

2. All :code:`reset` elements SHALL be considered sequentially for the
   connected variable set (see `Interpretation of
   map_variables <#interpretation-of-map_variables>`__) to which the
   referenced variable belongs. The sequence SHALL be determined by the
   value of the :code:`reset` element’s :code:`order` attribute, lowest (least
   positive) having priority.

3. The change, and conditions for the change, to a variable for a given
   :code:`reset` element SHALL be defined by the evaluation of that
   element’s :code:`when` child elements.

   a. A :code:`when` element SHALL be deemed to be true when the evaluation
      of the MathML expression encoded in first child element of the
      :code:`when` element changes from the boolean expression false to
      true.

   b. If a :code:`when` element is deemed to be true, then false, then true
      again during the same ‘instant’ or interval of integration, it
      SHALL nevertheless be held to be false.

   c. The second child element of a :code:`when` element SHALL define the
      MathML expression to be evaluated and assigned to the parent
      :code:`reset` element’s referenced variable when the :code:`when` element
      is deemed to be true.

   d. Consideration of the set of :code:`when` child elements of a given
      :code:`reset` element SHALL stop at the first occurrence of a :code:`when`
      deemed to be true.

   e. The order of consideration of the set of :code:`when` child elements
      SHALL be based on the value of the :code:`when` element’s :code:`order`
      attribute, lowest having priority.

20. References
==============

`RFC 2119: Key words for use in RFCs to Indicate Requirement
Levels <http://www.ietf.org/rfc/rfc2119.txt>`__ (March 1997)

`Extensible Markup Language (XML) 1.1 (Second
Edition) <http://www.w3.org/TR/2006/REC-xml11-20060816>`__ (16 August
2006)

`XML Information Set (Second
Edition) <http://www.w3.org/TR/2004/REC-xml-infoset-20040204/>`__ (4
February 2004)

`Namespaces in XML 1.1 (Second
Edition) <http://www.w3.org/TR/2006/REC-xml-names11-20060816/>`__ (16
August 2006)

`Mathematical Markup Language (MathML) Version 2.0 (Second
Edition) <http://www.w3.org/TR/2003/REC-MathML2-20031021/>`__ (21
October 2003)

`XML Linking Language (XLink) Version
1.0 <http://www.w3.org/TR/2001/REC-xlink-20010627/>`__ (27 June 2001)

.. |Capture.JPG| image:: media/image1.jpg
   :width: 4.87135in
   :height: 0.67261in
