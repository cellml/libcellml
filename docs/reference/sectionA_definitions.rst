.. _sectionA_definitions:

**CellML 2.0 Specification**

**Authors:**

Michael T. Cooling\*

Michael Clerx

Jonathan Cooper

Alan Garny

Keri Moyle

David P. Nickerson

Hugh Sorby

**Contributors:**

Jesús C. Fernández

David Brooks

Koray Atalag

The authors also wish to acknowledge the significant contribution of the
(discontinued) draft CellML 1.2 specification, much of the text of which
was incorporated into this specification - although the semantics have
changed considerably. The CellML 1.2 specification was itself the result
of a collaborative effort by a number of researchers during 2008-2011:

Andrew K. Miller (who wrote the text reused here), Jonathan Cooper,
Justin Marsh, Alan Garny, Randall Britten, Poul Nielsen and David P.
Nickerson

\* corresponding author: mtcooling.research@gmail.com  **TODO what should this be?**

**Preamble**

This document is the normative version of the CellML Specification,
defining the CellML syntax and the rules by which it should be used. It
is intended primarily for the developers of software tools which
directly consume CellML syntax. Users of CellML models should read the
informative version of the CellML Specification which is available here:
https://doi.org/science/1.1.1.10.


.. sectnum::

.. marker1

.. _specA_terminology:

Terminology
===========

The keywords “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”,
“SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this
document are to be interpreted as described in
:rfc2119:`RFC 2119`.

The key phrase “information item”, as well as any specific type of
information item such as an “element information item”, are to be
interpreted as described in :xml_infoset:`XML Information Set`.

.. _specA_cellml_infoset:

**CellML infoset:** An XML information set containing a hierarchy
of information items
conforming to the rules described in this document. In this
specification such infosets are assumed to be CellML 2.0 infosets.

.. _specA_cellml_model:

**CellML model:** A mathematical model represented by a hierarchy of
one or more CellML
infosets, according to the rules described in this document. In this
specification, the topmost CellML infoset in a hierarchy is referred
to as the top-level CellML infoset.

.. _specA_namespace:

**Namespace:** An XML namespace, as defined in
:xml_namespace_1_1:`Namespaces in XML 1.1`.

.. _specA_cellml_namespace:

**CellML namespace:** The CellML 2.0 namespace.

.. _specA_cellml2_namespace:

**CellML 2.0 namespace:** The namespace http://www.cellml.org/cellml/2.0#.

.. _specA_mathml_namespace:

**MathML namespace:** The namespace http://www.w3.org/1998/Math/MathML.

.. _specA_cellml_information_item:

**CellML information item:** Any information item in the :term:`CellML namespace`.

.. _specA_basic_latin_alphabetic_character:

**Basic Latin alphabetic character:** A Unicode character in the range
:unicode:`0041` to :unicode:`005A` or in the range :unicode:`0061` to :unicode:`007A`.

.. _specA_european_numeral:

**European numeral:** A Unicode character in the range :unicode:`0030`
to :unicode:`0039`.

.. _specA_basic_latin_alphanumeric_character:

**Basic Latin alphanumeric character:** A Unicode character which is either a
:term:`Basic Latin alphabetic character` or a :term:`European numeral`.

.. _specA_basic_latin_underscore:

**Basic Latin underscore:** The Unicode character :unicode:`005F`.

.. _specA_basic_latin_plus:

**Basic Latin plus:** The Unicode character :unicode:`002B`.

.. _specA_basic_latin_minus:

**Basic Latin minus:** The Unicode character :unicode:`002D`.

.. _specA_basic_latin_full_stop:

**Basic Latin full stop:** The Unicode character :unicode:`002E`.

.. _specA_whitespace_character:

**Whitespace character:** Any one of the Unicode characters :unicode:`0020`,
:unicode:`0009`, :unicode:`000D`, or :unicode:`000A`.

..  marker2

.. _specA_cellml_information_sets:

CellML information sets
=======================

CellML and XML
--------------

#. Every CellML infoset SHALL be represented in an XML information set
   which conforms with the well-formedness requirements of
   :xml_1_1:`XML 1.1`.

#. In this document, the remaining provisions relating to CellML
   infosets SHALL be interpreted as additional constraints on the XML
   information set represented by a CellML infoset.

Specific information items
--------------------------

#. For the purposes of this specification, a specific information item
   is one of the following (see
   https://www.w3.org/TR/xml-infoset/#infoitem for definitions):

   #. A document information item;

   #. An element information item;

   #. An attribute information item;

   #. A processing instruction information item;

   #. An unexpanded entity reference information item;

   #. A document type declaration information item;

   #. An unparsed entity information item;

   #. A notational information item.

#. Specific information items MUST NOT appear in a CellML infoset except
   where explicitly allowed by this specification, or where allowed by a
   normative specification referenced by this specification.

#. The order in which specific information items appear, as children of
   an element information item defined in this specification, SHALL NOT
   affect the semantic interpretation of the CellML model.

.. _specA_semantic_equivalence:

Semantically equivalent CellML infosets
---------------------------------------

#. Two CellML infosets SHALL be deemed semantically equivalent if one
   can be transformed into the other by making zero or more of the
   following changes:

   #. Adding, removing, and/or modifying comment information items.

   #. Changing (inserting, removing, and/or modifying) one or more
      namespace information items, and/or modifying the prefix of one or
      more information items, without changing the namespace that any
      information item is in.

   #. The following paragraph applies only to character information
      items which are the direct child of an element information item in
      a :term:`CellML namespace`, or in the MathML namespace.

      Inserting or removing character information items that consist
      entirely of whitespace characters, changing the number of whitespace
      characters in such an information item, or changing the number of
      whitespace characters at the beginning or end of any character
      information item.

Character information items
---------------------------

#. An element information item in the :term:`CellML namespace` MUST NOT
   contain any character information items, except for character information
   items which consist entirely of whitespace characters.

Use of namespaces
-----------------

#. Element and attribute information items in a CellML infoset MUST
   belong to one of the following namespaces, unless explicitly
   indicated otherwise:

   #. The :term:`CellML namespace`

   #. The MathML namespace

XML ID Attributes
-----------------

#. Any element information item in the :term:`CellML namespace` MAY contain an
   unprefixed attribute information item with local name :code:`id.` This
   attribute information item SHALL be treated as having attribute type
   ID, as defined in
   `section
   3.3.1 <http://www.w3.org/TR/xml11/#sec-attribute-types>`__ of `XML
   1.1 <http://www.w3.org/TR/xml11/>`__.

.. marker3_start

.. _specA_data_representation_formats:

Data representation formats in CellML
=====================================

The following data representation formats are defined for use in this
specification:

.. _specA_cellml_identifier:

1. A CellML identifier:

   .. container:: issue-data-repr-identifier-unicode

      1. SHALL be a sequence of Unicode characters.

   .. container:: issue-data-repr-identifier-latin-alphanum

      2. SHALL NOT contain any characters except
         :term:`Basic Latin alphanumeric character`\s
         and :term:`Basic Latin underscores<Basic Latin underscore>`.

   .. container:: issue-data-repr-identifier-at-least-one-alphanum

      3. SHALL contain at least one
         :term:`alphabetic<Basic Latin alphabetic character>` character.

   .. container:: issue-data-repr-identifier-begin-euro-num

      4. SHALL NOT begin with a
         :term:`numeral<European numeral>` or an
         :term:`underscore<Basic Latin underscore>`.

   .. container:: issue-data-repr-identifier-identical

      5. SHALL, when comparing two identifiers, be considered identical to
         another identifier if and only if both identifiers have identical
         sequences of characters.

.. marker3_2

.. _specA_nonnegative_integer:

2. A non-negative integer string:

   .. container:: issue-data-repr-nneg-int-base10

      1. SHALL be a base 10 representation of a non-negative integer.

   .. container:: issue-data-repr-nneg-in-euro-num

      2. SHALL consist entirely of European numerals.

.. marker3_3

.. _specA_integer:

3. An integer string:

   #. SHALL be a base 10 representation of an integer.

   #. SHALL, when the integer being represented is negative,
      begin with the Basic Latin hyphen-minus character
      :unicode:`002D` as the sign indicator.

   #. SHALL, other than the sign indicator, consist only of European numerals.

.. marker3_4

.. _specA_basic_real_number:

4. A basic real number string:

   #. SHALL be a base 10 representation of a real number.

   #. SHALL, when the basic real number being represented is negative,
      begin with the Basic Latin hyphen-minus character
      :unicode:`002D` as the sign indicator.

   #. MAY contain a single decimal point separator, which SHALL be the
      Basic Latin full stop character :unicode:`002E`.

   #. SHALL, other than the sign indicator and the decimal point
      separator, consist only of European numerals.

.. marker3_5

.. _specA_real_number:

5. A real number string:

   #. SHALL be a base 10 representation of a real number
      *r*\ =\ *s*\ ⋅10\ *e*, where *s* is the significand, a real
      number, and *e* is the exponent, an integer.

   #. The representation of the number SHALL be the representation of
      the significand followed immediately by the representation of the
      exponent.

   #. The significand SHALL be represented as a basic real number
      string.

   #. An exponent SHALL be represented by an exponent separator
      character, followed by the integer string representation of the
      value of the exponent. Non-negative exponents MAY begin with the
      Basic Latin plus sign character :unicode:`002B` as the sign indicator.
      The exponent separator character SHALL be either the Basic Latin ‘E’
      character :unicode:`0045` or the Basic Latin ‘e’ character :unicode:`0065`.

   #. A real number string without an exponent SHALL be a basic real
      number string.

.. marker3_end
